#include "esp32_wireshark.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <furi.h>
#include <furi_hal.h>

#define MAX_PACKET_BUFFER 1000
#define MAX_PACKET_SIZE 2048

// Global packet buffer
typedef struct {
    WiresharkPacket packets[MAX_PACKET_BUFFER];
    uint32_t count;
    uint32_t total_captured;
    uint32_t dropped;
    uint32_t start_time_ms;
} PacketBuffer;

static PacketBuffer* g_packet_buffer = NULL;

WiresharkSession* wireshark_init(void) {
    WiresharkSession* session = malloc(sizeof(WiresharkSession));
    if(!session) return NULL;
    
    memset(session, 0, sizeof(WiresharkSession));
    
    session->capture_mutex = furi_mutex_alloc(FuriMutexTypeNormal);
    if(!session->capture_mutex) {
        free(session);
        return NULL;
    }
    
    // Initialize filter to capture everything
    session->filter.capture_wifi_data = true;
    session->filter.capture_wifi_mgmt = true;
    session->filter.capture_wifi_beacon = true;
    session->filter.capture_ble_adv = true;
    session->filter.capture_ble_data = true;
    session->filter.min_signal_strength = -100; // dBm
    session->filter.target_channel = 0; // All channels
    
    // Allocate packet buffer
    if(!g_packet_buffer) {
        g_packet_buffer = malloc(sizeof(PacketBuffer));
        if(!g_packet_buffer) {
            furi_mutex_free(session->capture_mutex);
            free(session);
            return NULL;
        }
        memset(g_packet_buffer, 0, sizeof(PacketBuffer));
    }
    
    furi_log_info("WIRESHARK", "Initialized capture session");
    return session;
}

void wireshark_free(WiresharkSession* session) {
    if(!session) return;
    
    if(session->is_capturing) {
        wireshark_stop_capture(session);
    }
    
    if(session->capture_mutex) {
        furi_mutex_free(session->capture_mutex);
    }
    
    if(g_packet_buffer) {
        for(uint32_t i = 0; i < g_packet_buffer->count; i++) {
            if(g_packet_buffer->packets[i].data) {
                free(g_packet_buffer->packets[i].data);
            }
        }
        free(g_packet_buffer);
        g_packet_buffer = NULL;
    }
    
    free(session);
    furi_log_info("WIRESHARK", "Session freed");
}

bool wireshark_start_capture(WiresharkSession* session) {
    if(!session || session->is_capturing) return false;
    
    furi_mutex_acquire(session->capture_mutex, FuriWaitForever);
    
    session->is_capturing = true;
    
    if(g_packet_buffer) {
        g_packet_buffer->start_time_ms = furi_get_tick();
        g_packet_buffer->count = 0;
        g_packet_buffer->total_captured = 0;
        g_packet_buffer->dropped = 0;
    }
    
    memset(&session->stats, 0, sizeof(WiresharkStats));
    session->stats.strongest_signal = -100;
    session->stats.weakest_signal = 0;
    
    furi_mutex_release(session->capture_mutex);
    
    furi_log_info("WIRESHARK", "Capture started");
    furi_log_info("WIRESHARK", "WiFi Data: %s, WiFi Mgmt: %s, BLE Adv: %s",
        session->filter.capture_wifi_data ? "ON" : "OFF",
        session->filter.capture_wifi_mgmt ? "ON" : "OFF",
        session->filter.capture_ble_adv ? "ON" : "OFF");
    
    return true;
}

bool wireshark_stop_capture(WiresharkSession* session) {
    if(!session || !session->is_capturing) return false;
    
    furi_mutex_acquire(session->capture_mutex, FuriWaitForever);
    
    session->is_capturing = false;
    
    if(g_packet_buffer) {
        session->stats.capture_duration_ms = furi_get_tick() - g_packet_buffer->start_time_ms;
    }
    
    furi_mutex_release(session->capture_mutex);
    
    furi_log_info("WIRESHARK", "Capture stopped");
    furi_log_info("WIRESHARK", "Total packets: %ld", session->stats.total_packets);
    
    return true;
}

bool wireshark_add_packet(WiresharkSession* session, const WiresharkPacket* packet) {
    if(!session || !packet || !g_packet_buffer) return false;
    
    if(!session->is_capturing) return false;
    
    // Apply filters
    bool should_capture = false;
    
    if(packet->type == PACKET_TYPE_WIFI_DATA && session->filter.capture_wifi_data) {
        should_capture = true;
    } else if(packet->type == PACKET_TYPE_WIFI_MGMT && session->filter.capture_wifi_mgmt) {
        should_capture = true;
    } else if(packet->type == PACKET_TYPE_WIFI_BEACON && session->filter.capture_wifi_beacon) {
        should_capture = true;
    } else if(packet->type == PACKET_TYPE_BLE_ADV && session->filter.capture_ble_adv) {
        should_capture = true;
    } else if(packet->type == PACKET_TYPE_BLE_DATA && session->filter.capture_ble_data) {
        should_capture = true;
    }
    
    if(!should_capture) return true;
    
    // Signal strength filter
    if(packet->signal_strength < session->filter.min_signal_strength) {
        return true;
    }
    
    // Channel filter
    if(session->filter.target_channel != 0 && packet->channel != session->filter.target_channel) {
        return true;
    }
    
    // MAC filter
    if(session->filter.filter_mac[0] != '\0') {
        if(strcmp(packet->source_mac, session->filter.filter_mac) != 0 &&
           strcmp(packet->dest_mac, session->filter.filter_mac) != 0) {
            return true;
        }
    }
    
    furi_mutex_acquire(session->capture_mutex, FuriWaitForever);
    
    // Check if buffer is full
    if(g_packet_buffer->count >= MAX_PACKET_BUFFER) {
        g_packet_buffer->dropped++;
        session->stats.dropped_packets++;
        furi_mutex_release(session->capture_mutex);
        return false;
    }
    
    // Copy packet
    WiresharkPacket* stored_packet = &g_packet_buffer->packets[g_packet_buffer->count];
    memcpy(stored_packet, packet, sizeof(WiresharkPacket));
    
    // Copy data separately
    if(packet->data && packet->data_len > 0) {
        stored_packet->data = malloc(packet->data_len);
        if(stored_packet->data) {
            memcpy(stored_packet->data, packet->data, packet->data_len);
        } else {
            stored_packet->data_len = 0;
        }
    }
    
    // Update statistics
    session->stats.total_packets++;
    session->stats.bytes_captured += packet->length;
    g_packet_buffer->total_captured++;
    
    switch(packet->type) {
        case PACKET_TYPE_WIFI_DATA:
            session->stats.wifi_packets++;
            session->stats.data_frames++;
            break;
        case PACKET_TYPE_WIFI_MGMT:
            session->stats.wifi_packets++;
            session->stats.management_frames++;
            break;
        case PACKET_TYPE_WIFI_BEACON:
            session->stats.wifi_packets++;
            session->stats.beacons++;
            break;
        case PACKET_TYPE_BLE_ADV:
        case PACKET_TYPE_BLE_DATA:
            session->stats.ble_packets++;
            break;
        default:
            break;
    }
    
    // Update signal strength stats
    if(packet->signal_strength > session->stats.strongest_signal) {
        session->stats.strongest_signal = packet->signal_strength;
    }
    if(packet->signal_strength < session->stats.weakest_signal) {
        session->stats.weakest_signal = packet->signal_strength;
    }
    
    // Calculate average
    if(session->stats.average_signal == 0) {
        session->stats.average_signal = packet->signal_strength;
    } else {
        session->stats.average_signal = (session->stats.average_signal + packet->signal_strength) / 2;
    }
    
    g_packet_buffer->count++;
    furi_mutex_release(session->capture_mutex);
    
    return true;
}

void wireshark_set_filter(WiresharkSession* session, const WiresharkFilter* filter) {
    if(!session || !filter) return;
    
    furi_mutex_acquire(session->capture_mutex, FuriWaitForever);
    memcpy(&session->filter, filter, sizeof(WiresharkFilter));
    furi_mutex_release(session->capture_mutex);
    
    furi_log_info("WIRESHARK", "Filter updated");
}

WiresharkStats wireshark_get_stats(WiresharkSession* session) {
    WiresharkStats stats = {0};
    if(!session) return stats;
    
    furi_mutex_acquire(session->capture_mutex, FuriWaitForever);
    memcpy(&stats, &session->stats, sizeof(WiresharkStats));
    furi_mutex_release(session->capture_mutex);
    
    return stats;
}

bool wireshark_export_pcap(WiresharkSession* session, const char* filename) {
    if(!session || !filename || !g_packet_buffer) return false;
    
    FILE* file = fopen(filename, "wb");
    if(!file) {
        furi_log_error("WIRESHARK", "Failed to open file: %s", filename);
        return false;
    }
    
    // Write PCAP header
    PCAPHeader pcap_hdr = {
        .magic_number = 0xa1b2c3d4,
        .version_major = 2,
        .version_minor = 4,
        .timezone_offset = 0,
        .timestamp_accuracy = 0,
        .snaplen = MAX_PACKET_SIZE,
        .network = 127, // 802.11
    };
    
    if(fwrite(&pcap_hdr, sizeof(PCAPHeader), 1, file) != 1) {
        furi_log_error("WIRESHARK", "Failed to write PCAP header");
        fclose(file);
        return false;
    }
    
    // Write packets
    furi_mutex_acquire(session->capture_mutex, FuriWaitForever);
    
    for(uint32_t i = 0; i < g_packet_buffer->count; i++) {
        WiresharkPacket* pkt = &g_packet_buffer->packets[i];
        
        PCAPPacketHeader pkt_hdr = {
            .timestamp_sec = pkt->timestamp_ms / 1000,
            .timestamp_microsec = (pkt->timestamp_ms % 1000) * 1000,
            .packet_length = pkt->length,
            .packet_length_orig = pkt->length,
        };
        
        if(fwrite(&pkt_hdr, sizeof(PCAPPacketHeader), 1, file) != 1) {
            furi_log_error("WIRESHARK", "Failed to write packet header");
            break;
        }
        
        if(pkt->data && pkt->data_len > 0) {
            if(fwrite(pkt->data, pkt->data_len, 1, file) != 1) {
                furi_log_error("WIRESHARK", "Failed to write packet data");
                break;
            }
        }
    }
    
    furi_mutex_release(session->capture_mutex);
    fclose(file);
    
    furi_log_info("WIRESHARK", "Exported %ld packets to %s", g_packet_buffer->count, filename);
    return true;
}

bool wireshark_export_csv(WiresharkSession* session, const char* filename) {
    if(!session || !filename || !g_packet_buffer) return false;
    
    FILE* file = fopen(filename, "w");
    if(!file) {
        furi_log_error("WIRESHARK", "Failed to open file: %s", filename);
        return false;
    }
    
    // Write CSV header
    fprintf(file, "Number,Time,Source,Destination,Protocol,Length,RSSI,Channel,Type\n");
    
    furi_mutex_acquire(session->capture_mutex, FuriWaitForever);
    
    for(uint32_t i = 0; i < g_packet_buffer->count; i++) {
        WiresharkPacket* pkt = &g_packet_buffer->packets[i];
        
        fprintf(file, "%ld,%ld.%03ld,%s,%s,%s,%d,%d,%d,%s\n",
            i + 1,
            pkt->timestamp_ms / 1000,
            pkt->timestamp_ms % 1000,
            pkt->source_mac,
            pkt->dest_mac,
            pkt->protocol,
            pkt->length,
            pkt->signal_strength,
            pkt->channel,
            wireshark_packet_type_str(pkt->type)
        );
    }
    
    furi_mutex_release(session->capture_mutex);
    fclose(file);
    
    furi_log_info("WIRESHARK", "Exported CSV: %s", filename);
    return true;
}

bool wireshark_export_json(WiresharkSession* session, const char* filename) {
    if(!session || !filename || !g_packet_buffer) return false;
    
    FILE* file = fopen(filename, "w");
    if(!file) {
        furi_log_error("WIRESHARK", "Failed to open file: %s", filename);
        return false;
    }
    
    fprintf(file, "{\n  \"version\": \"1.0\",\n  \"packets\": [\n");
    
    furi_mutex_acquire(session->capture_mutex, FuriWaitForever);
    
    for(uint32_t i = 0; i < g_packet_buffer->count; i++) {
        WiresharkPacket* pkt = &g_packet_buffer->packets[i];
        
        fprintf(file, "    {\n");
        fprintf(file, "      \"number\": %ld,\n", i + 1);
        fprintf(file, "      \"timestamp_ms\": %ld,\n", pkt->timestamp_ms);
        fprintf(file, "      \"source\": \"%s\",\n", pkt->source_mac);
        fprintf(file, "      \"destination\": \"%s\",\n", pkt->dest_mac);
        fprintf(file, "      \"bssid\": \"%s\",\n", pkt->bssid);
        fprintf(file, "      \"protocol\": \"%s\",\n", pkt->protocol);
        fprintf(file, "      \"type\": \"%s\",\n", wireshark_packet_type_str(pkt->type));
        fprintf(file, "      \"length\": %d,\n", pkt->length);
        fprintf(file, "      \"rssi_dbm\": %d,\n", pkt->signal_strength);
        fprintf(file, "      \"channel\": %d,\n", pkt->channel);
        fprintf(file, "      \"encrypted\": %s,\n", pkt->encrypted ? "true" : "false");
        fprintf(file, "      \"data_rate_mbps\": %d\n", pkt->data_rate);
        fprintf(file, "    }%s\n", i < g_packet_buffer->count - 1 ? "," : "");
    }
    
    furi_mutex_release(session->capture_mutex);
    
    fprintf(file, "  ],\n");
    fprintf(file, "  \"statistics\": {\n");
    fprintf(file, "    \"total_packets\": %ld,\n", session->stats.total_packets);
    fprintf(file, "    \"wifi_packets\": %ld,\n", session->stats.wifi_packets);
    fprintf(file, "    \"ble_packets\": %ld,\n", session->stats.ble_packets);
    fprintf(file, "    \"dropped_packets\": %ld,\n", session->stats.dropped_packets);
    fprintf(file, "    \"capture_duration_ms\": %ld\n", session->stats.capture_duration_ms);
    fprintf(file, "  }\n");
    fprintf(file, "}\n");
    
    fclose(file);
    
    furi_log_info("WIRESHARK", "Exported JSON: %s", filename);
    return true;
}

void wireshark_clear_buffer(WiresharkSession* session) {
    if(!session || !g_packet_buffer) return;
    
    furi_mutex_acquire(session->capture_mutex, FuriWaitForever);
    
    for(uint32_t i = 0; i < g_packet_buffer->count; i++) {
        if(g_packet_buffer->packets[i].data) {
            free(g_packet_buffer->packets[i].data);
            g_packet_buffer->packets[i].data = NULL;
        }
    }
    
    g_packet_buffer->count = 0;
    memset(&session->stats, 0, sizeof(WiresharkStats));
    
    furi_mutex_release(session->capture_mutex);
    
    furi_log_info("WIRESHARK", "Buffer cleared");
}

void wireshark_set_channel(WiresharkSession* session, uint8_t channel) {
    if(!session) return;
    
    furi_mutex_acquire(session->capture_mutex, FuriWaitForever);
    session->filter.target_channel = channel;
    furi_mutex_release(session->capture_mutex);
    
    furi_log_info("WIRESHARK", "Channel set to: %d", channel);
}

const WiresharkPacket* wireshark_get_packets(WiresharkSession* session, uint32_t* count) {
    if(!session || !count || !g_packet_buffer) return NULL;
    
    furi_mutex_acquire(session->capture_mutex, FuriWaitForever);
    *count = g_packet_buffer->count;
    const WiresharkPacket* packets = g_packet_buffer->packets;
    furi_mutex_release(session->capture_mutex);
    
    return packets;
}

char* wireshark_analyze_packet(const WiresharkPacket* packet) {
    if(!packet) return NULL;
    
    static char analysis[256];
    snprintf(analysis, sizeof(analysis),
        "Type: %s | RSSI: %d dBm | Ch: %d | Rate: %d Mbps | Enc: %s",
        wireshark_packet_type_str(packet->type),
        packet->signal_strength,
        packet->channel,
        packet->data_rate,
        packet->encrypted ? "Yes" : "No"
    );
    
    return analysis;
}

void wireshark_format_mac(const uint8_t* mac_bytes, char* buffer, size_t buffer_len) {
    if(!mac_bytes || !buffer) return;
    snprintf(buffer, buffer_len, "%02X:%02X:%02X:%02X:%02X:%02X",
        mac_bytes[0], mac_bytes[1], mac_bytes[2],
        mac_bytes[3], mac_bytes[4], mac_bytes[5]
    );
}

const char* wireshark_packet_type_str(PacketType type) {
    switch(type) {
        case PACKET_TYPE_WIFI_DATA:
            return "WiFi Data";
        case PACKET_TYPE_WIFI_MGMT:
            return "WiFi Management";
        case PACKET_TYPE_WIFI_BEACON:
            return "WiFi Beacon";
        case PACKET_TYPE_BLE_ADV:
            return "BLE Advertisement";
        case PACKET_TYPE_BLE_DATA:
            return "BLE Data";
        default:
            return "Unknown";
    }
}

const char* wireshark_wifi_protocol_str(uint8_t data_rate) {
    if(data_rate <= 11) return "802.11b";
    if(data_rate <= 54) return "802.11g";
    if(data_rate <= 65) return "802.11n";
    return "802.11ac";
}
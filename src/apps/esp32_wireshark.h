#ifndef ESP32_WIRESHARK_H
#define ESP32_WIRESHARK_H

#include <furi.h>
#include <stdint.h>
#include <stdbool.h>

/**
 * ESP32 Wireshark - Network packet capture and analysis
 * Real-time WiFi/BLE packet sniffing with Wireshark-compatible export
 */

// Packet types
typedef enum {
    PACKET_TYPE_WIFI_DATA,
    PACKET_TYPE_WIFI_MGMT,
    PACKET_TYPE_WIFI_BEACON,
    PACKET_TYPE_BLE_ADV,
    PACKET_TYPE_BLE_DATA,
    PACKET_TYPE_UNKNOWN,
} PacketType;

// WiFi frame subtypes
typedef enum {
    WIFI_MGMT_BEACON = 0x08,
    WIFI_MGMT_PROBE_REQ = 0x04,
    WIFI_MGMT_PROBE_RESP = 0x05,
    WIFI_MGMT_ASSOC_REQ = 0x00,
    WIFI_MGMT_ASSOC_RESP = 0x01,
    WIFI_MGMT_DEAUTH = 0x0C,
    WIFI_MGMT_DISASSOC = 0x0A,
} WiFiMgmtSubtype;

// Packet capture structure
typedef struct {
    uint32_t timestamp_ms;
    uint32_t packet_number;
    PacketType type;
    uint8_t channel;
    int8_t signal_strength; // RSSI in dBm
    uint16_t length;
    uint8_t* data;
    uint32_t data_len;
    
    // Metadata
    char source_mac[18];      // "AA:BB:CC:DD:EE:FF"
    char dest_mac[18];
    char bssid[18];
    uint16_t sequence_number;
    bool encrypted;
    bool is_broadcast;
    uint8_t data_rate;        // Mbps
    char protocol[32];        // "802.11n", "BLE 5.0", etc.
} WiresharkPacket;

// Packet filter
typedef struct {
    bool capture_wifi_data;
    bool capture_wifi_mgmt;
    bool capture_wifi_beacon;
    bool capture_ble_adv;
    bool capture_ble_data;
    uint8_t min_signal_strength; // Filter by RSSI threshold
    bool filter_broadcast;
    char filter_mac[18]; // Filter by specific MAC
    uint8_t target_channel; // 0 = all channels
} WiresharkFilter;

// Statistics
typedef struct {
    uint32_t total_packets;
    uint32_t wifi_packets;
    uint32_t ble_packets;
    uint32_t dropped_packets;
    uint32_t capture_duration_ms;
    uint32_t bytes_captured;
    
    // Per-type counters
    uint32_t beacons;
    uint32_t probe_requests;
    uint32_t probe_responses;
    uint32_t data_frames;
    uint32_t management_frames;
    uint32_t deauth_frames;
    
    // Signal statistics
    int8_t strongest_signal;
    int8_t weakest_signal;
    int8_t average_signal;
} WiresharkStats;

// Capture session
typedef struct {
    bool is_capturing;
    bool is_recording_to_file;
    uint32_t packets_captured;
    WiresharkFilter filter;
    WiresharkStats stats;
    FuriMutex* capture_mutex;
} WiresharkSession;

// PCAP export format (Wireshark compatible)
typedef struct {
    uint32_t magic_number;   // 0xa1b2c3d4 for standard, 0xa1b23c4d for nanosecond
    uint16_t version_major;
    uint16_t version_minor;
    int32_t timezone_offset;
    uint32_t timestamp_accuracy;
    uint32_t snaplen;        // Max packet length
    uint32_t network;        // 127 for WiFi, 251 for BLE
} PCAPHeader;

typedef struct {
    uint32_t timestamp_sec;
    uint32_t timestamp_microsec;
    uint32_t packet_length;  // Actual length
    uint32_t packet_length_orig; // Original length
    uint8_t* packet_data;
} PCAPPacketHeader;

// Function declarations

/**
 * Initialize Wireshark capture session
 */
WiresharkSession* wireshark_init(void);

/**
 * Free Wireshark session
 */
void wireshark_free(WiresharkSession* session);

/**
 * Start packet capture
 */
bool wireshark_start_capture(WiresharkSession* session);

/**
 * Stop packet capture
 */
bool wireshark_stop_capture(WiresharkSession* session);

/**
 * Add packet to capture buffer
 */
bool wireshark_add_packet(WiresharkSession* session, const WiresharkPacket* packet);

/**
 * Set capture filter
 */
void wireshark_set_filter(WiresharkSession* session, const WiresharkFilter* filter);

/**
 * Get current statistics
 */
WiresharkStats wireshark_get_stats(WiresharkSession* session);

/**
 * Export to PCAP file (Wireshark compatible)
 */
bool wireshark_export_pcap(WiresharkSession* session, const char* filename);

/**
 * Export to CSV format
 */
bool wireshark_export_csv(WiresharkSession* session, const char* filename);

/**
 * Export to JSON format
 */
bool wireshark_export_json(WiresharkSession* session, const char* filename);

/**
 * Clear capture buffer
 */
void wireshark_clear_buffer(WiresharkSession* session);

/**
 * Set channel for capture
 */
void wireshark_set_channel(WiresharkSession* session, uint8_t channel);

/**
 * Get captured packets
 */
const WiresharkPacket* wireshark_get_packets(WiresharkSession* session, uint32_t* count);

/**
 * Analyze packet
 */
char* wireshark_analyze_packet(const WiresharkPacket* packet);

/**
 * Format MAC address from bytes
 */
void wireshark_format_mac(const uint8_t* mac_bytes, char* buffer, size_t buffer_len);

/**
 * Get packet type string
 */
const char* wireshark_packet_type_str(PacketType type);

/**
 * Get WiFi protocol string
 */
const char* wireshark_wifi_protocol_str(uint8_t data_rate);

#endif // ESP32_WIRESHARK_H
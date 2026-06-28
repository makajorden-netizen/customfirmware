# ESP32 Wireshark - Network Packet Capture & Analysis

## Overview

ESP32 Wireshark is a professional-grade network packet capture and analysis tool that runs on the ESP32 module connected to Flipper Zero. It captures WiFi and Bluetooth packets in real-time with Wireshark-compatible export formats.

**Features:**
- Real-time packet capture (WiFi 802.11 + BLE)
- Wireshark-compatible PCAP export
- CSV and JSON export formats
- Advanced filtering and statistics
- Signal strength analysis (RSSI)
- Packet sequence tracking
- Multi-threaded safe capture

## Capabilities

### Packet Capture

✅ **WiFi Packets:**
- Data frames
- Management frames (beacons, probes, authentication)
- Deauthentication frames
- Associated/Disassociation frames
- Full 802.11 frame analysis

✅ **Bluetooth Packets:**
- BLE advertisements
- BLE connection data
- Raw BLE payloads
- Device discovery

### Filtering Options

```c
WiresharkFilter filter = {
    .capture_wifi_data = true,          // Capture WiFi data frames
    .capture_wifi_mgmt = true,          // Capture management frames
    .capture_wifi_beacon = true,        // Capture beacons
    .capture_ble_adv = true,            // Capture BLE advertisements
    .capture_ble_data = true,           // Capture BLE data
    .min_signal_strength = -80,         // RSSI threshold (dBm)
    .filter_broadcast = false,          // Filter broadcast packets
    .filter_mac[18] = "AA:BB:CC:DD:EE:FF",  // Specific MAC filter
    .target_channel = 6,                // Specific channel (0 = all)
};
```

### Export Formats

#### 1. PCAP Format (Wireshark Compatible)
- Standard libpcap format
- Fully compatible with Wireshark, tcpdump, tshark
- Import directly into Wireshark for analysis
- Preserves packet metadata and timing

```bash
# Open in Wireshark
wireshark capture.pcap

# Analyze with tcpdump
tcpdump -r capture.pcap
```

#### 2. CSV Format
- Spreadsheet-compatible
- Easy filtering and sorting
- Columns: Number, Time, Source, Destination, Protocol, Length, RSSI, Channel, Type

```csv
Number,Time,Source,Destination,Protocol,Length,RSSI,Channel,Type
1,1234.567,AA:BB:CC:DD:EE:FF,FF:FF:FF:FF:FF:FF,802.11n,256,-45,6,WiFi Data
2,1234.568,AA:BB:CC:DD:EE:00,AA:BB:CC:DD:EE:FF,802.11n,128,-50,6,WiFi Data
```

#### 3. JSON Format
- Structured data export
- Include packet analysis
- Statistics embedded
- Perfect for programmatic analysis

```json
{
  "version": "1.0",
  "packets": [
    {
      "number": 1,
      "timestamp_ms": 1234567,
      "source": "AA:BB:CC:DD:EE:FF",
      "destination": "FF:FF:FF:FF:FF:FF",
      "protocol": "802.11n",
      "length": 256,
      "rssi_dbm": -45,
      "channel": 6,
      "encrypted": false
    }
  ],
  "statistics": {
    "total_packets": 1000,
    "wifi_packets": 850,
    "ble_packets": 150,
    "dropped_packets": 0,
    "capture_duration_ms": 60000
  }
}
```

## Statistics

Real-time capture statistics:

```c
WiresharkStats stats = wireshark_get_stats(session);

stats.total_packets        // Total packets captured
stats.wifi_packets         // WiFi-specific packets
stats.ble_packets          // Bluetooth packets
stats.dropped_packets      // Buffer overflow drops
stats.bytes_captured       // Total bytes captured
stats.beacons              // WiFi beacon count
stats.probe_requests       // Probe request count
stats.probe_responses      // Probe response count
stats.data_frames          // Data frame count
stats.management_frames    // Management frame count
stats.deauth_frames        // Deauthentication count
stats.strongest_signal     // Best RSSI (dBm)
stats.weakest_signal       // Worst RSSI (dBm)
stats.average_signal       // Average RSSI (dBm)
```

## Usage Examples

### Basic Capture

```c
#include "apps/esp32_wireshark.h"

// Initialize session
WiresharkSession* session = wireshark_init();

// Start capturing
wireshark_start_capture(session);

// ... capture for 60 seconds ...
furi_delay_ms(60000);

// Stop capture
wireshark_stop_capture(session);

// Export to Wireshark
wireshark_export_pcap(session, "/ext/captures/network.pcap");

// Get statistics
WiresharkStats stats = wireshark_get_stats(session);
furi_log_info("WIRESHARK", "Captured %ld packets", stats.total_packets);
furi_log_info("WIRESHARK", "Signal: %d dBm (avg)", stats.average_signal);

// Cleanup
wireshark_free(session);
```

### Advanced Filtering

```c
// Create session
WiresharkSession* session = wireshark_init();

// Set custom filter
WiresharkFilter filter = {
    .capture_wifi_data = true,
    .capture_wifi_mgmt = false,
    .capture_wifi_beacon = false,
    .capture_ble_adv = false,
    .capture_ble_data = false,
    .min_signal_strength = -60,  // Only strong signals
    .target_channel = 6,          // Channel 6 only
};
strcpy(filter.filter_mac, "AA:BB:CC:DD:EE:FF");

wireshark_set_filter(session, &filter);
wireshark_start_capture(session);
```

### Channel Hopping

```c
// Scan multiple channels
for(int channel = 1; channel <= 13; channel++) {
    wireshark_set_channel(session, channel);
    furi_log_info("WIRESHARK", "Scanning channel %d", channel);
    furi_delay_ms(2000);  // 2 seconds per channel
}
```

### Packet Analysis

```c
uint32_t count = 0;
const WiresharkPacket* packets = wireshark_get_packets(session, &count);

for(uint32_t i = 0; i < count; i++) {
    char* analysis = wireshark_analyze_packet(&packets[i]);
    furi_log_info("PACKET_%ld", i, analysis);
    
    // Advanced analysis
    if(packets[i].signal_strength > -50) {
        furi_log_info("WIRESHARK", "Strong signal from %s", packets[i].source_mac);
    }
}
```

## Channel Reference

### WiFi Channels

```
2.4 GHz Band (1-13):
Channel | Frequency | Region
--------|-----------|----------
1       | 2.412 GHz | Worldwide
2       | 2.417 GHz | Worldwide
3       | 2.422 GHz | Worldwide
4       | 2.427 GHz | Worldwide
5       | 2.432 GHz | Worldwide
6       | 2.437 GHz | Worldwide (Common)
7       | 2.442 GHz | Worldwide
8       | 2.447 GHz | Worldwide
9       | 2.452 GHz | Worldwide
10      | 2.457 GHz | Worldwide
11      | 2.462 GHz | Worldwide (Common)
12      | 2.467 GHz | Asia
13      | 2.472 GHz | Asia

5 GHz Band (36-165):
36, 40, 44, 48 (5.15-5.25 GHz)
52, 56, 60, 64 (5.25-5.35 GHz)
100-144 (5.470-5.725 GHz)
149, 153, 157, 161, 165 (5.725-5.850 GHz)
```

### Data Rates

```
802.11b:    1, 2, 5.5, 11 Mbps
802.11g:    6, 9, 12, 18, 24, 36, 48, 54 Mbps
802.11n:    6.5 - 65 Mbps (1x1), up to 150 Mbps (2x2)
802.11ac:   up to 866 Mbps
```

## RSSI Signal Strength Reference

```
RSSI (dBm) | Signal Quality
-----------|---------------
-30 to 0   | Excellent (Very close to router)
-30 to -67 | Good (Strong signal)
-67 to -70 | Fair (Usable)
-70 to -80 | Weak (Degrading)
-80 to -90 | Very Weak (Barely usable)
< -90      | No Signal
```

## Buffer Management

### Buffer Limits
- **Max packets**: 1,000 packets per session
- **Max packet size**: 2,048 bytes
- **Total buffer**: ~2 MB
- **Auto-drop**: Oldest packets dropped when buffer full

### Clear Buffer

```c
wireshark_clear_buffer(session);
furi_log_info("WIRESHARK", "Buffer cleared");
```

## Performance

### Capture Modes

**Single Channel (Fastest):**
- Can capture ~1000+ packets/second
- Minimal CPU usage
- Best for targeting specific network

**Channel Hopping:**
- ~100-200 packets/second per channel
- Moderate CPU usage
- Good for network discovery

**Full Spectrum:**
- Limited by ESP32 WiFi stack
- Used for general network monitoring

## File Storage

**Recommended Paths:**
```
/ext/captures/network.pcap      # PCAP format
/ext/captures/network.csv       # CSV format
/ext/captures/network.json      # JSON format
```

**File Size Estimates:**
- 1,000 average packets: ~500 KB (PCAP), 150 KB (CSV)
- 10,000 packets: ~5 MB (PCAP)

## Integration with Wireshark

### Import PCAP
1. Export from Flipper: `wireshark_export_pcap(session, path)`
2. Transfer file to computer
3. Open Wireshark
4. File → Open → Select .pcap file
5. Analyze traffic

### Display Filters
```
wifi.bssid == aa:bb:cc:dd:ee:ff    # Filter by BSSID
wlan.fc.type == 2                  # Data frames only
wlan.fc.type == 0                  # Management frames
frame.time_relative > 10            # Packets after 10s
wlan.sa == aa:bb:cc:dd:ee:ff       # Source MAC filter
```

## Limitations & Notes

- ⚠️ ESP32 must be connected via GPIO
- ⚠️ Channel switching takes ~100-300ms
- ⚠️ Captured data is IEEE 802.11 frame level (no IP layer)
- ⚠️ Encryption keys not recovered (encrypted packets remain encrypted)
- ⚠️ Performance limited by ESP32 WiFi stack

## Legal & Safety

✅ **Legal Use:**
- Monitor YOUR OWN networks
- Security research with authorization
- Educational purposes
- Network troubleshooting

❌ **Illegal Use:**
- Capturing others' traffic without authorization
- Extracting sensitive data
- Privacy violations
- Unauthorized network access

## Troubleshooting

### No packets captured
- Verify ESP32 connected properly
- Check target channel has activity
- Verify filter settings
- Check RSSI threshold

### Many dropped packets
- Buffer full (max 1,000 packets)
- Export and clear before continuing
- Use more selective filters
- Increase export frequency

### File export fails
- Verify /ext/captures/ directory exists
- Check available storage space
- Verify file permissions

## Resources

- **Wireshark Official**: https://www.wireshark.org/
- **tcpdump Manual**: https://www.tcpdump.org/
- **802.11 Frame Format**: https://en.wikipedia.org/wiki/802.11_frame_types
- **BLE Specifications**: https://www.bluetooth.com/specifications/
- **ESP32 WiFi Documentation**: https://docs.espressif.com/

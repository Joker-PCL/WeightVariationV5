import pywifi
from pywifi import const
import json
import time

CONNECTED = 1
DISCONNECTED = 0

def get_current_wifi():
    wifi = pywifi.PyWiFi()
    iface = wifi.interfaces()[0]
    print("Interface status:", iface.status())
    if iface.status() == pywifi.const.IFACE_CONNECTED:
        return iface.name()
    else:
        return "Not connected to any WiFi network"

def scan_wifi_networks():
    wifi = pywifi.PyWiFi()
    iface = wifi.interfaces()[0]

    iface.scan()
    time.sleep(5)  # รอเวลาสักครู่ให้แน่ใจว่าการสแกนเครือข่ายเสร็จสิ้น
    results = iface.scan_results()

    seen_ssids = set()
    sorted_results = sorted(results, key=lambda x: x.signal, reverse=True)
    wifi_lists = []
    for network in sorted_results:
        if network.ssid not in seen_ssids:
            wifi_info = {"SSID": network.ssid, "Signal_Strength": network.signal}
            print(wifi_info)
            wifi_lists.append(wifi_info)
            seen_ssids.add(network.ssid)
    
    wifi_json = {"wifi": wifi_lists}
    return json.dumps(wifi_json)
            
def connect_to_wifi(ssid, password):
    print("Connecting to wifi...")
    wifi = pywifi.PyWiFi()
    iface = wifi.interfaces()[0]

    iface.disconnect()
    time.sleep(1)

    profile = pywifi.Profile()
    profile.ssid = ssid
    profile.auth = const.AUTH_ALG_OPEN
    profile.akm.append(const.AKM_TYPE_WPA2PSK)
    profile.cipher = const.CIPHER_TYPE_CCMP
    profile.key = password

    iface.remove_all_network_profiles()
    tmp_profile = iface.add_network_profile(profile)

    iface.connect(tmp_profile)
    time.sleep(5)

    if iface.status() == const.IFACE_CONNECTED:
        print(f"Connected to {ssid} successfully!")
        return CONNECTED
    else:
        print("Connection failed.")
        return DISCONNECTED


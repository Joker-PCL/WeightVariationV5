import serial
import json
import random
from time import sleep
import threading
from datetime import datetime

from src import WiFi 
from src import SyncTime 

# เปิดการใช้งาน Serial port
ser = serial.Serial(port='COM4', baudrate=115200)

def read_serial():
    print("Starting sync with serial...")
    while True:
        try:
            serial_data  = ser.readline().decode('utf-8').strip()
            print(serial_data)
            result_json = json.loads(serial_data)
            _wifi = result_json["WiFi"]

            if(_wifi == "Scan"):
                wifi_lists = WiFi.scan_wifi_networks()
                # print(wifi_lists)
                wifi_lists_json = wifi_lists.encode('utf-8')
                ser.write(wifi_lists_json)
                ser.write(b'\n')
            elif(_wifi == "connect"):
                ssid = result_json["ssid"]
                password = result_json["password"]
                wifi_begin = WiFi.connect_to_wifi(ssid, password)
               
                if(wifi_begin == WiFi.CONNECTED):
                    json_string = json.dumps({"wifi_result": "success"})
                else:
                    json_string = json.dumps({"wifi_result": "failed"})

                
                serial.write(json_string.encode('utf-8'))
                serial.write(b'\n')
                    
        except Exception as e:
            pass

def main():
    SyncTime.sync(ser)
    serial_thread = threading.Thread(target=read_serial)
    serial_thread.start()

    while True:
        rfid = random.randrange(0, 9999999999)
        rfid = format(rfid, '010d')
        # print("rfid: ", rfid)
        json_string = json.dumps({"page": "LoginPage", "rfid": rfid})
        # ส่งข้อมูล JSON ไปยัง Arduino
        ser.write(json_string.encode('utf-8'))
        ser.write(b'\n')
        sleep(5)
        weight_set = {
            "page": 'WeightingPage',
            "details": {
                "product": 'TRAVAN 0.5',
                "lot": '21500R',
                "balanceID": 'PI-227',
                "tabletID": 'T17',
                "mean_weight": '6.700',
                "percent_weight": '2.00',
                "weight_inhouse_min": '6.570',
                "weight_inhouse_max": '6.830',
                "weight_reg_min": '6.370',
                "weight_reg_max": '7.030',
                "thickness_min": '5.30',
                "thickness_max": '5.75'
            }
        }
        
        try:
            weight_set_json = json.dumps(weight_set)
            ser.write(weight_set_json.encode('utf-8'))
            ser.write(b'\n')  # เพิ่ม '\n' เพื่อบอก Arduino ว่าข้อมูลจบ
            sleep(5)

            json_string = json.dumps({"page": "ThicknessPage"})
            # ส่งข้อมูล JSON ไปยัง Arduino
            ser.write(json_string.encode('utf-8'))
            ser.write(b'\n')
            sleep(5)
            
            json_string = json.dumps({"page": "TabletCharacteristicsPage"})
            # ส่งข้อมูล JSON ไปยัง Arduino
            ser.write(json_string.encode('utf-8'))
            ser.write(b'\n')
            sleep(5)

            json_string = json.dumps({"page": "SummaryPage"})
            # ส่งข้อมูล JSON ไปยัง Arduino
            ser.write(json_string.encode('utf-8'))
            ser.write(b'\n')
            sleep(5)

            json_string = json.dumps({"page": "loading_page"})
            # ส่งข้อมูล JSON ไปยัง Arduino
            ser.write(json_string.encode('utf-8'))
            ser.write(b'\n')
            sleep(5)
        except Exception as e:
                print(f"Error writing to serial port: {e}")
                continue
                              
if __name__ == "__main__":
    main()
    #current_wifi = get_current_wifi()
    #print("Currently connected to:", current_wifi)
    # แสดงรายชื่อเครือข่ายไวไฟทั้งหมดที่พบ
    # scan_wifi_networks()

    # เชื่อมต่อกับเครือข่ายไวไฟ
    # ssid = input("Enter SSID: ")
    # password = input("Enter password: ")
    # connect_to_wifi(ssid, password)
            
            
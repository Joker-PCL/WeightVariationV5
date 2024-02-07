import json
from time import sleep
from datetime import datetime

def sync(serial):
    print("Starting sync with serial...")
    while True:
        current_time = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        json_string = json.dumps({"datetime": current_time})
        serial.write(json_string.encode('utf-8'))
        serial.write(b'\n')
        sleep(1)
        # อ่านข้อมูลจาก Serial
        try:
            serial_data  = serial.readline().decode('utf-8').strip()
            result_json = json.loads(serial_data)
            result = result_json["result"]
            print(result)
            if(result == "success"):
                return
            
        except Exception as e:
            pass

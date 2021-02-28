import serial
import gspread
import re
from datetime import datetime
from oauth2client.service_account import ServiceAccountCredentials

ser = serial.Serial('/dev/ttyACM0', 9600)

scope = ['https://spreadsheets.google.com/feeds', 'https://www.googleapis.com/auth/drive']
credentials = ServiceAccountCredentials.from_json_keyfile_name('client_secret.json', scope)
gc = gspread.authorize(credentials)
wks = gc.open('liiketunnistin').sheet1
print(wks.get_all_records())

while True:
    luettuRivi = str(ser.readline())
    movementDetectedString = "Liiketta tunnistettu"
    if movementDetectedString in luettuRivi:
        print(luettuRivi, " Movement detected")
        now = datetime.now()
        dt_string = now.strftime("%d/%m/%Y %H:%M:%S")
        print("date and time =", dt_string)
        wks.append_row([dt_string])
        with open('MovementDetectorLog.txt','a') as oLog:
            oLog.write(dt_string)
            oLog.write("\n")
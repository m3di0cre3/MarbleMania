import serial
import time

arduino = serial.Serial('com7', 115200)
time.sleep(2)
beatFile = open(r"C:\Users\anand\OneDrive\Documents\Heartless.txt", "r")
line = beatFile.readline().strip()
if (line != ""):
    lineAfter = beatFile.readline().strip()
    while (lineAfter != ""):
        arduino.write(bytes(line + '\r\n', 'utf-8'))
        line = lineAfter
        lineAfter = beatFile.readline().strip()
    arduino.write(bytes(line, 'utf-8'))

while True:
    #line = beatFile.readline().strip()
    #if (line == ""): break
    #arduino.write(bytes(line, 'utf-8'))
    #print(line)
    while (arduino.inWaiting()==0):
        pass
    dataPacket = arduino.readline()
    data = int(str(dataPacket, 'utf-8').strip('\r\n'))
    print(data)
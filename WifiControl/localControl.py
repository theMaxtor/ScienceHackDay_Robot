import struct
import socket
import serial

host = "10.48.1.239"
port = 3017

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.connect((host, port))

ser = serial.Serial('/dev/ttyUSB1', 9600)
while True:
    l = ser.readline()
    x,y,b = [int(w) for w in l.split()]

    js = struct.pack("<iii", x, y, b)
    server.send(js)


js = struct.pack("<iii", 33, 66, 55)
s.send(js)


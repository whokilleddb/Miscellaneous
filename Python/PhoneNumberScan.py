#!/usr/bin/python3
import phonenumbers
from phonenumbers import carrier
from phonenumbers import geocoder
from tabulate import tabulate

def scanNum(num):
	number=phonenumbers.parse(num)
	des=geocode.description_for_number(num,'en')
	supplier=carrier.name_for_supplier(num,'en')
	info=[["Country","Supplier"],[des,supplier]]
	data= str(tabulate(info, headers='firstrow',tablefmt='github'))
	return data

if __name__ == '__main__':
	num=input("[+] Enter Number : ")
	print(scanNum(num))

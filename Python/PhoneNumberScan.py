#!/usr/bin/python3
import phonenumbers
from phonenumbers import geocoder, carrier
from tabulate import tabulate

def scanNum(num):
	number=phonenumbers.parse(num)
	if phonenumbers.is_valid_number(number):
		des=geocoder.description_for_number(number,'en')
		supplier=carrier.name_for_number(number,'en')
		info=[["Number","Country","Supplier"],[num,des,supplier]]
		data= str(tabulate(info, headers='firstrow',tablefmt='pretty'))
		return data
	else :
		return "[-] Not A Valid Number"

if __name__ == '__main__':
	num=input("[+] Enter Number : ")
	print('\n'+scanNum(num))

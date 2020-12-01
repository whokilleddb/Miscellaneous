#!/usr/bin/python3
from playsound import playsound
from gtts import gTTS
import os

def cleanUP(filename):
	if os.path.exists(filename):
		os.remove(filename)

def bokBOK(stuffToSpeak):
	cleanUP("TxtToVoice.mp3")
	toSpeak=gTTS(text=stuffToSpeak, lang ='en')
	toSpeak.save("TxtToVoice.mp3") #sets the file's current position at the offset ; here refernce point is set at the beginning of the file
	playsound("TxtToVoice.mp3")

if __name__ == '__main__' :
    print("[+] Text To Speech Converter")
    txt=input("[+] Enter Text : ")
    bokBOK(txt)

#!/usr/bin/python3
import io
import pygame
from gtts import gTTS

def bokBOK(stuffToSpeak):
    with io.BytesIO() as f : #Produce Bytes Object
        gTTS(text=stuffToSpeak, lang ='en').write_to_fp(f)
        f.seek(0) #sets the file's current position at the offset ; here refernce point is set at the beginning of the file
        pygame.mixer.init()
        pygame.mixer.music.load(f)
        pygame.mixer.music.play()
        while pygame.mixer.music.get_busy():
            continue
        
if __name__ == '__main__' :
    print("[+] Text To Speech Converter")
    txt=input("[+] Enter Text : ")
    bokBOK(txt)

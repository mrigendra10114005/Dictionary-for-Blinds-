import speech_recognition as sr
from gtts import gTTS
from pygame import *
import sc1
r=sr.Recognizer()
with sr.Microphone() as source:
	print("Say something")
	audio=r.listen(source)
try:
	word=r.recognize_google(audio)
	sc1.d.setdefault(word,"word not found")
	result=sc1.d[word]
	print(result)
	tts=gTTS(text=result,lang='hi')
	tts.save("hello5.mp3")
	mixer.init()
	mixer.music.load('C:\\Users\\USER\\Desktop\\new f1\\hello5.mp3')
	mixer.music.play()
	while mixer.music.get_busy():
		time.Clock().tick(1)
except sr.UnkownValueError:
	print("not able to understand")
except sr.RequestError as e:
	print("could not request results; {0}".format(e))	
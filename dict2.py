from PyDictionary import PyDictionary
from gtts import gTTS
from pygame import * 
import sc1
dictionary=PyDictionary()
word=input()
result=(sc1.d[word])
#word=input()

#print(dictionary.meaning(wordsb))
#print(dictionary.synonym(wordsb))
#result=dictionary.translate(wordsb,'hi')
tts = gTTS(text=result, lang='hi')
tts.save("hello2.mp3")
# Load the required library

mixer.init()
mixer.music.load('C:\\Users\\USER\\Desktop\\new f1\\hello2.mp3')
mixer.music.play()
while mixer.music.get_busy():
	time.Clock().tick(1)


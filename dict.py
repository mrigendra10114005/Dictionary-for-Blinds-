from PyDictionary import PyDictionary
from gtts import gTTS
import os
dictionary=PyDictionary()
wordsb=input()
print(dictionary.meaning(wordsb))
print(dictionary.synonym(wordsb))
result=dictionary.translate(wordsb,'hi')
tts = gTTS(text=result, lang='hi')
tts.save("hello1.mp3")


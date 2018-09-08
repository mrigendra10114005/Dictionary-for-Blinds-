from gtts import gTTS
import os
tts = gTTS(text='mrigendra', lang='hi')
tts.save("hello3.ogg")
#os.system("mpg321 hello1.mp3")


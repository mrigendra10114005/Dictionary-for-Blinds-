from pygame import * # Load the required library

mixer.init()
mixer.music.load('C:\\Users\\USER\\Desktop\\new f1\\hello2.mp3')
mixer.music.play()
while mixer.music.get_busy():
	time.Clock().tick(10)
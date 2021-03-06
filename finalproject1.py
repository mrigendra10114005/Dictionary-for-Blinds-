from gtts import gTTS
from pygame import *
import sc1
import tkinter
large_font=('Verdana',30)
class simpleapp_tk(tkinter.Tk):
	def __init__(self,parent):
		tkinter.Tk.__init__(self,parent)
		self.parent=parent
		self.initialize()
	def initialize(self):
		self.grid()
		self.entryVariable=tkinter.StringVar(value='Large Font!')
		self.entry=tkinter.Entry(self,textvariable=self.entryVariable,font=large_font)
		self.entry.grid(column=0,row=0,sticky='EW')
		self.entry.bind("<Return>",self.OnPressEnter)
		self.entryVariable.set(u"")
		button=tkinter.Button(self,text=u"click me",command=self.OnButtonClick,font=large_font)
		button.grid(column=1,row=0)
		self.labelVariable=tkinter.StringVar()
		label=tkinter.Label(self,textvariable=self.labelVariable,anchor="w",fg="white",bg="red",font=large_font)
		label.grid(column=0,row=1,columnspan=2,sticky='EW')
		self.labelVariable.set(u"")
		self.grid_columnconfigure(0,weight=1)
		self.resizable(True,False)
	def OnButtonClick(self):
		word=self.entryVariable.get()
		sc1.d.setdefault(word,"word not found")
		result=sc1.d[word]
		self.labelVariable.set(result)
		tts=gTTS(text=result,lang='hi')
		tts.save("hello4.mp3")
		mixer.init()
		mixer.music.load('C:\\Users\\USER\\Desktop\\new f1\\hello4.mp3')
		mixer.music.play()
		while mixer.music.get_busy():
			time.Clock().tick(1)
	def OnPressEnter(self,event):
		word=self.entryVariable.get()
		sc1.d.setdefault(word,"word not found")
		result=sc1.d[word]
		self.labelVariable.set(result)
		tts=gTTS(text=result,lang='hi')
		tts.save("hello4.mp3")
		mixer.init()
		mixer.music.load('C:\\Users\\USER\\Desktop\\new f1\\hello4.mp3')
		mixer.music.play()
		while mixer.music.get_busy():
			time.Clock().tick(1)
if __name__=="__main__":
	app=simpleapp_tk(None)
	app.title('my dictionary')
	app.mainloop()
	
		
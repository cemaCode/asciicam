# asciicam
Turn your webcam video into ascii art, like a Zoom filter 

#  ❓What is this?
This little progrm in C++ is supposed to turn your webcam feed into ASCII art. 
Like this:
![screenshot](https://github.com/cemaCode/asciicam/blob/main/screensh0t.png?raw=true "screenshot")
Pretty cool, huh?
The idea behind this would be to use it as a sort of funny webcam filter for videocalls on platforms such as Zoom or Skype, by sharing your screen and specifically the window with the code running.  
#  ⏩How to run it?
In the file [main.cpp](https://github.com/cemaCode/asciicam/blob/main/main.cpp "main.cpp") you will find the source code.   
Feel free to modify it for your use.   
Once you have the code you will need to compile it using your prefed C++ compilier and you will need to use the OpenCV library.  
If you need help installing OpenCV check out their docs [here](https://docs.opencv.org/master/df/d65/tutorial_table_of_content_introduction.html "here").   The version i used was the latest one 4.5.
## ⚙Options

### 📹Internal Webcam or external Webcam
If you are using an external webcam pluged in via USB you will need to change[ line 145 ](https://github.com/cemaCode/asciicam/blob/5641c550c6ae31c27592ea32529ec5dbb98c3621/main.cpp#L145 " line 145 ")from source code from:  
		`VideoCapture capture(0)`  
		to   
		`VideoCapture capture(1)`  
### 📊Background color and character color 
By default the background color will be black and the text color green to give it the H4k3r effect😁. If you want to change that you can do so in [line 146](https://github.com/cemaCode/asciicam/blob/5641c550c6ae31c27592ea32529ec5dbb98c3621/main.cpp#L167 "line 146") :   
`display = TextWindow(result, BLACK, GREEN);`  
As you can see the function` TextWindow()` takes 2 parameters for color:  
	- The first one is the background color  
	- The second one is the text color  
By changing thoses parameters you can effectively change the color on display.  
Right now the program can only handle three colors:  
`enum COLOR { BLACK, WHITE, GREEN };`  
I will be adding more colors later, or you can easily add them yourself.  
*Note: If you wish to add your own colors remember that OpenCV uses BGR instead of RBG so keep that in mind.* 

# ✅ What is left to be done?
This little project is far from done and I will be adding more features.  
Right now this is the todo list for the next features:  
- [ ] Add argument parsing from command line to change source, color and ascii grayscale 
- [ ] Add different ascii grayscales for different effects and different styles
- [ ] Add more colors for background and text
- [ ] Add multithreading to reduce latency as right now it is almost unusable 

If you wish to see more features please do ask or even add them yourself.  

# 📑 References 
Just a quick paragraph to recomend checking out this website : http://paulbourke.net/dataformats/asciiart/  
It helped me understand ascii art and the way it works and I also stole my ascii grayscale from there 😅 so check it out if you are interested. 

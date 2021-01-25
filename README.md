# TTGO Watch sketch

An arduino sketch for the lilygo ttgo t-watch 2020.  A really cool little ESP32 based smart watch.

This all borrows *heavily* from Dan Geiger's work here: https://www.instructables.com/Lilygo-T-Watch-2020-Arduino-Framework/

And from Lewis He's work here: https://github.com/Xinyuan-LilyGO/TTGO_TWatch_Library/blob/master/examples/BasicUnit/BMA423_Feature/BMA423_Feature.ino

This sketch has both gesture-wake (flip your wrist to wake the watch), as well as tap to wake (tap the watch twice to wake it up).  Both of these use the accelerometer. 

## Menu System

Thanks to Dan for putting together the menu system.  To activate the menu, touch the screen.  Be aware that the watch will only timeout and go to sleep on its own when it is displaying the time.  So be sure to exit whatever app you open, or you will drain your battery.

Generally to use this: look in "menu.ino".  In there is an array of strings like "exit", "demoApp", "demoApp1", etc.  These will return their index to the switch statement in loop(), which will call a function that you specify in loop().  For instance, selecing "demoApp" will return a 1 to the switch case, which will run the function demoApp().  See the "demoApp" function (in demoApp.ino) for a good stub of what an app could look like.

## Sleep states
The watch will automatically go to sleep 5 seconds after waking, but only if it is on the "main" screen displaying the time.  You can wake it either by flicking your wrist and looking at the watch, or by tapping the watch face twice.  The tapping uses the accelerometer, so you do have to tap it, not just touch it.

## Step counter
The step counter doesn't *seem* to be working for me, but I haven't tested it much.  A lot of this is taken from Lewis He's sketch linked above, and I might just be missing something.


## Smart Lights
This will now control both hue lights and WIZ lights.  For wiz lights, it will set ALL lights to the same colors/brightness at once.  If you want to see how to control individual lights, check the
porchlight.ino file, and look at how it is being called inside of "redAlert.ino".  You must be connected to WiFi, and then you can send the UDP messages to change the lights.

Hue lights aren't nearly as hacker friendly.  See the "secrets.h" file for an example of how to get a username for your hue bridge, then specify it in that file.  See the file "hueLights.ino" 
for an example of how I am controlling the lights.  The colors are controlled as an XY coordinate.  I used the hue app on my phone along with the API explorer specified in that file to 
get XY values to set the colors that I want.

One thing about the hue lights that you'll notice.  I'm basically spamming the HTTP requests in rapid succession until they succeed.  Not sure why this is necessary.  Yes this is hacky.

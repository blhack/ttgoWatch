An arduino sketch for the lilygo ttgo t-watch 2020.  A really cool little ESP32 based smart watch.

This all borrows *heavily* from Dan Geiger's work here: https://www.instructables.com/Lilygo-T-Watch-2020-Arduino-Framework/

And from Lewis He's work here: https://github.com/Xinyuan-LilyGO/TTGO_TWatch_Library/blob/master/examples/BasicUnit/BMA423_Feature/BMA423_Feature.ino

This sketch has both gesture-wake (flip your wrist to wake the watch), as well as tap to wake (tap the watch twice to wake it up).  Both of these use the accelerometer. 

Thanks to Dan for putting together the menu system.  To activate the menu, touch the screen.  Be aware that the watch will only timeout and go to sleep on its own when it is displaying the time.  So be sure to exit whatever app you open, or you will drain your battery.

Generally to use this: look in "menu.ino".  In there is an array of strings like "exit", "demoApp", "demoApp1", etc.  These will return their index to the switch statement in loop(), which will call a function that you specify in loop().  For instance, selecing "demoApp" will return a 1 to the switch case, which will run the function demoApp().  See the "demoApp" function (in demoApp.ino) for a good stub of what an app could look like.
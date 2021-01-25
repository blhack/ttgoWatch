#define MYSSID ""
#define WIFIKEY ""
#define HUEUSER ""
#define HUEIP ""
#define BROADCASTIP {192, 168, 0, 255} //change this to your network.

//Check out this guide for how to interact with the HUE API: https://www.makeuseof.com/tag/control-philips-hue-lights-arduino-and-motion-sensor/
//however this is outdated.  Instead of specifying a username by posting: {"devicetype":"test user","username":"newdeveloper"}
//post {"devicetype":"test user"} instead (omit the username).  HUE will respond with a username, which you should then specify in this file as HUEUSER
//post this to the API URL (by default it will show /api/1234 == erase the 1234 part.
//make sure you press the hue button first.

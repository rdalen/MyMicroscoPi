# MyMicroscoPi
This DIY microscope design combines many of my hobbies; Lego, electronics, 3D printing, Arduino, Raspberry Pi, etc.

My design is a remix of a great and well documented [design of Yuksel Temizon](https://github.com/IBM/MicroscoPy).
My version is also built of LEGO bricks, but uses also LEGO Technic beams because they are light and strong.
For capturing images it uses a Raspberry Pi 3B+ with an 8MP camera and modified lens. The six stepper motors for the camera & sample movements and the power LED for illumination are controlled by two PCB's with an [Arduino Pro mini](https://www.arduino.cc/en/Guide/ArduinoProMini) on each PCB.
* One PCB (Mainboard) contains all the driver hardware for the steppers and power LED
* The other PCB (Controller board) contains the human interface elements for controlling the microscope. Such as; Three joysticks to control the X, Y, Rotary, Tilt (Camera-angle), Magnitude and Focus, a Rotary encoder to control the Power LED and a small OLED display to indicate the brightness of the power LED

I used the 3D printed LEGO gears and adapters of the [original design](https://github.com/IBM/MicroscoPy)

So, after many hours of building pleasure, I'm going to do some nice experiments now

### Information & Documentation
* [HackIO artikel; IBM Researcher Makes a Microscope Using LEGO, Arduino, and Raspberry Pi](https://www.hackster.io/news/ibm-researcher-makes-a-microscope-using-lego-arduino-and-raspberry-pi-cbc58cb69a20?utm_source=Hackster+Marketing&utm_campaign=7e2e7b20ec-EMAIL_CAMPAIGN_2019_02_14_02_53_COPY_01&utm_medium=email&utm_term=0_86d76c4d75-7e2e7b20ec-144680307&mc_cid=7e2e7b20ec&mc_eid=ea3c09e980)
* [Github IBM/MicroscoPy](https://github.com/IBM/MicroscoPy)
* [YouTube link MyMicroscoPi](https://youtu.be/3TL11zC14ig)

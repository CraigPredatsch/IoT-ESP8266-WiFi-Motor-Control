# IoT-ESP8266-WiFi-Motor-Control

For this project, I developed the hardware and firmware to operate a motor through a web browser
on a computer or a cell phone connected to WiFi.

## Hardware

* NodeMCU 1.0 (ESP8266 development board)
* Arduino Uno
* 6V DC motor
* L293D H-Bridge IC
* 4 AA battery holder
* FTDI Serial TTL-232 USB Cable (Optional)
* Breadboard
* Wire

## Hardware Setup

For a schematic view of the setup, open up the file "IoT ESP8266 WiFi Motor Control_schem.pdf". The setup is, for
the most part, fairly self explanatory. However, there are a few things I would like to go into more detail on.

One aspect that I would like to explain in this setup, I connected my computer to the NodeMCU board via the FTDI 
cable mentioned above in the "Hardware" section. I went this route instead of connecting directly to the board with
a USB-micro USB cable because of some interesting features on my NodeMCU board. I discovered that I needed to hold down 
the "Flash" button on the board before powering on every single time that I wanted to upload a new script. From what
I've read, this is not the case on most NodeMCU boards and is a somewhat unique feature to the brand of board I bought.
I decided to go with an FTDI cable connection to my computer because I could break out the power line to an individual wire 
and connect/remove power in that way; as opposed to constant plugging and unplugging of the micro USB connector, which 
would cause some unnecessary physical stress to the board.

Another thing I would like to note is that the output of the NodeMCU from GPIO 13 and 14 is connected to the analog inputs
of the Arduino. The NodeMCU can only output at 3.3V, which may be too low for the Arduino to read through a digital input.
The Arduino can, however, determine analog inputs from 0 - 5 V. In firmware I have the Arduino perfrom an analogRead at the
two analog inputs and set a condition to be met at a 2V threshold that the 3.3V output of the NodeMCU could easily surpass.

## Firmware

* NodeMCU_GUI_Motor_test.ino (Arduino IDE script for NodeMCU)
* Arduino_ESP_Motor.ino (Arduino IDE script for Arduino Uno) 

## Firmware Operation

I recommend opening up the two Arduino scripts I have provided and reading through them. Below, I am providing a description
of how they work, but I have left comments in the scripts that give line by line detail on how the scripts work.

The NodeMCU_GUI_Motor_test.ino script runs the NodeMCU. It will connect to WiFi via the router information provided and
connect to a web server. It will print out, via serial connection, the IP address that the user can enter into their web
browser to reach the GUI that will operate the NodeMCU. The GUI is also created in this script in HTML via the client.println()
function. This script will then take the responses genrated from user interaction with the GUI (clicking the buttons that have
been created) and it will turn GPIO pins 13 and/or 14 High or Low. These outputs are connected to the Arduino, and they will
determine the next steps of the process on the Arduino side.

The Arduino_ESP_Motor.ino script runs the Arduino Uno.

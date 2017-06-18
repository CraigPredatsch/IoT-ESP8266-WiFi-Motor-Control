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

* Arduino IDE (Used for Arduino Uno and NodeMCU)

## Firmware Operation


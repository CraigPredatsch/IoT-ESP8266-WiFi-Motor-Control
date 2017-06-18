#include <ESP8266WiFi.h>
 
const char* ssid = "Router_name";       //Enter the name of the router you wish to connect with
const char* password = "Password";      //Enter the password of the router
 
int forwardPin = 13;                    //GPIO 13 is now "forwardPin"
int reversePin = 14;                    //GPIO 14 is now "reversePin"
WiFiServer server(80);                  //Opens up web server connection

int forward = LOW;                      //Initialize pins Low.
int backwards = LOW;
 
void setup() {
  Serial.begin(115200);                 //Open Serial connection
  delay(10);

  pinMode(forwardPin, OUTPUT);          //Set pins to output and keep them low
  digitalWrite(forwardPin, LOW);
  pinMode(reversePin, OUTPUT);
  digitalWrite(reversePin, LOW);
 
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);                   //Connect to the WiFi via the router provided earlier
 
  while (WiFi.status() != WL_CONNECTED) {       //While WiFi is not connected
    delay(500);
    Serial.print(".");                          //Print a period to let the user know the ESP8266 is trying to connect to WiFi
  }
  Serial.println("");
  Serial.println("WiFi connected");             //When WiFi is onnected, print "WiFi connected"
 
  
  server.begin();                               //Start the server
  Serial.println("Server started");
 
  
  Serial.print("Use this URL to connect: ");    //Print the IP address. The user opens the link in their browser to reach the GUI
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
 
}
 
void loop() {
  WiFiClient client = server.available();              //Check if a client has connected to the web server
  if (!client) {                                       //If not, return and run the loop again
    return;
  }
 
  Serial.println("new client");                       //Wait until the client sends data
  while(!client.available()){
    delay(1);
  }
 
  
  String request = client.readStringUntil('\r');      //Read the first line of the request from the server
  Serial.println(request);
  client.flush();
 
//The following are actions brought on by the request

  
  if (request.indexOf("/FORWARD=ON") != -1)  {        //This will spin the motor forward
    digitalWrite(forwardPin, HIGH);
    digitalWrite(reversePin, LOW);
    forward = HIGH;                                   //This is an extra set of values that will let the GUI display what state the motor is in
    backwards = LOW;
  }
  if (request.indexOf("/REVERSE=ON") != -1)  {        //This will spin the motor in reverse
    digitalWrite(forwardPin, LOW);
    digitalWrite(reversePin, HIGH);
    forward = LOW;
    backwards = HIGH;
  }
  if (request.indexOf("/STOP=ON") != -1) {            //This will stop the motor.
    digitalWrite(forwardPin, LOW);
    digitalWrite(reversePin, LOW);
    forward = LOW;
    backwards = LOW;
  }
 
 
  client.println("HTTP/1.1 200 OK");                  //Server uses HTTP version 1.1 200
  client.println("Content-Type: text/html");          //GUI will be HTML text based
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");                  //Beginning of HTML Document
  client.println("<html>");
 
  client.print("Motor Direction: ");                  //Displays on the GUI the current motor direction
 
  if(forward == HIGH) {
    client.print("Forward");
  }
  else if (backwards == HIGH) {
    client.print("Reverse");
  }
  else {
    client.print("Stopped");
  }

  
  
  client.println("<br><br>");                                                         //Line break
  client.println("<a href=\"/FORWARD=ON\"\"><button>Forward </button></a>");          //Button in GUI that says "Forward". Its output is received in line 68.
  client.println("<a href=\"/STOP=ON\"\"><button>Stop </button></a>");                //Button in GUI that says "Stop". Its output is received in line 80.
  client.println("<a href=\"/REVERSE=ON\"\"><button>Reverse </button></a><br />");    //Button in GUI that says "Reverse". Its output is received in line 74.
  client.println("</html>");
 
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
 
}

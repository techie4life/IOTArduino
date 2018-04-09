//this code sends data through a wifi module to thingspeak
const int numReadings= 10;
int temp;
int readIndex;              // the index of the current reading
int totaltemp; // the running total
int totallux;
int averagetemp;  // the average
int averagelux;
float voltagetemp;
int voltagelux;
int luxread [numReadings];
String apikey = "15C451V2V2935TSZ"; //api key
String host = String("Host: api.thingspeak.com"); //still part of get command
String start = String("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80");//starts the TCP connection to thingspeak through the wifi module
int val;

  void setup() {
  Serial1.begin(115200); //initializes the serial1 ports
  Serial.begin(9600);
  pinMode(6,INPUT);
  pinMode(7, INPUT);
  pinMode(15, OUTPUT);
  digitalWrite(15,HIGH);
  }




void loop() {

    /*for(readIndex=0; readIndex< numReadings; readIndex++){
        readings[readIndex]=analogRead(6);
        totaltemp+=readings[readIndex];
    }
*/
    temp=analogRead(6);
       //averagetemp = totaltemp/numReadings;

           voltagetemp = temp * (3.3/1023.0); //converts analog values to voltage

       val = voltagetemp * (100.0); //changes voltage to temperature, conversion from data sheet


     String get = String("GET /update?api_key=")+String(apikey)+String("&field1=")+String(val) //get command
             delay(10); //10ms second delay to start, allows the wifi module to setup if needed

     Serial1.println(start); //sends the start command to the wifi module
             delay(20); //20ms second delay so the wifi chip does not get overwhelmed

     String bytes = String("AT+CIPSEND=")+String(get.length()+6);//tells wifi module how many bytes will be sent

     Serial1.println(bytes); //sends the bytes command to the wifi module
             delay(10);//lots of delays..

     Serial1.println(get);//sends the get command with the data to the server
             delay(10);

    Serial1.println(host);//sends the host string to server

    Serial1.println();//space

    Serial1.println();//space

        delay(300000); // 5 minute delay between loops

}

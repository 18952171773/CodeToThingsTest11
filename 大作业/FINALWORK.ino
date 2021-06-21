/*
  SparkFun Inventor’s Kit
  Circuit 1D-RGB Nightlight

  Turns an RGB LED on or off based on the light level read by a photoresistor.
  Change colors by turning the potentiometer.

  This sketch was written by SparkFun Electronics, with lots of help from the Arduino community.
  This code is completely free for any use.

  View circuit diagram and instructions at: https://learn.sparkfun.com/tutorials/sparkfun-inventors-kit-experiment-guide---v41
  Download drawings and code at: https://github.com/sparkfun/SIK-Guide-Code
*/
#define Do 262  
#define Re 294  
#define Mi 330  
#define Fa 349  
#define Sol 392  
#define La 440  
#define Si 494  
int scale[]={Do,Re,Mi,Fa,Sol,La,Si};
int pu[100]={5,100,3,4,5,100,3,4,5,5,6,7,1,2,3,4,3,100,1,2,3,100,3,4,5,6,5,4,5,3,4,5,4,100,6,5,4,100,32,3,2,12,34,5,6,4,100,6,5,6,100,7,1,5,6,7,1,2,3,4,5};
int photoresistor = A0;          //variable for storing the photoresistor value
int potentiometer = A1;          //this variable will hold a value based on the position of the knob
int threshold = 700;            //if the photoresistor reading is lower than this value the light will turn on

//LEDs are connected to these pins
int speakerPin = 10;
void setup() {
  Serial.begin(9600);           //start a serial connection with the computer
  //set the LED pins to output
  pinMode(speakerPin, OUTPUT);
}

void loop() {
  photoresistor = analogRead(A0);         //read the value of the photoresistor

  Serial.print("Photoresistor value:");
  Serial.print(photoresistor);          //print the photoresistor value to the serial monitor
  Serial.print("  Potentiometer value:");
  Serial.println(potentiometer);          //print the potentiometer value to the serial monitor

  if(photoresistor < threshold) {        //if it's dark (the photoresistor value is below the threshold) turn the LED on
    //These nested if statements check for a variety of ranges and
    //call different functions based on the current potentiometer value.
    //Those functions are found at the bottom of the sketch.
    //if (potentiometer > 0 && potentiometer <= 900)
    turnOff();
  }
  else {                                //if it isn't dark turn the LED off
    red();                  //call the turn off function
  }

  delay(100);                             //short delay so that the printout is easier to read
}

void red () { //背景音乐
  for(int i=0;i<61;i++){
    if(pu[i]!=100) 
    {
      tone(speakerPin,scale[pu[i]-1]); 
    }
    else noTone(speakerPin);  
    delay(200);
    noTone(speakerPin);  
    delay(100);  
    photoresistor = analogRead(A0);
    if (photoresistor <= threshold) break;
  }
  delay(500);
}

void turnOff () { //关灯播放生日快乐歌
  play('g', 2);       //ha
  play('g', 1);       //ppy
  play('a', 4);       //birth
  play('g', 4);       //day
  play('C', 4);       //to
  play('b', 4);       //you

  play(' ', 2);       //pause for 2 beats
  //光线检测
  photoresistor = analogRead(A0);
  if (photoresistor > threshold)  return;

  play('g', 2);       //ha
  play('g', 1);       //ppy
  play('a', 4);       //birth
  play('g', 4);       //day
  play('D', 4);       //to
  play('C', 4);       //you

  play(' ', 2);       //pause for 2 beats
  photoresistor = analogRead(A0);
  if (photoresistor > threshold)  return;

  play('g', 2);       //ha
  play('g', 1);       //ppy
  play('G', 4);       //birth
  play('E', 4);       //day

  photoresistor = analogRead(A0);
  if (photoresistor > threshold)  return;

  play('C', 4);       //dear
  play('b', 4);       //your
  play('a', 6);       //name

  play(' ', 2);       //pause for 2 beats
  photoresistor = analogRead(A0);
  if (photoresistor > threshold)  return;
  
  play('F', 2);       //ha
  play('F', 1);       //ppy
  play('E', 4);       //birth
  play('C', 4);       //day
  play('D', 4);       //to
  play('C', 6);       //you
}

void play( char note, int beats)
{
  int numNotes = 14;  // number of notes in our note and frequency array (there are 15 values, but arrays start at 0)

  //Note: these notes are C major (there are no sharps or flats)

  //this array is used to look up the notes
  char notes[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C', 'D', 'E', 'F', 'G', 'A', 'B', ' '};
  //this array matches frequencies with each letter (e.g. the 4th note is 'f', the 4th frequency is 175)
  int frequencies[] = {131, 147, 165, 175, 196, 220, 247, 262, 294, 330, 349, 392, 440, 494, 0};

  int currentFrequency = 0;    //the frequency that we find when we look up a frequency in the arrays
  int beatLength = 100;   //the length of one beat (changing this will speed up or slow down the tempo of the song)

  //look up the frequency that corresponds to the note
  for (int i = 0; i < numNotes; i++)  // check each value in notes from 0 to 14
  {
    if (notes[i] == note)             // does the letter passed to the play function match the letter in the array?
    {
      currentFrequency = frequencies[i];   // Yes! Set the current frequency to match that note
    }
  }

  //play the frequency that matched our letter for the number of beats passed to the play function
  tone(speakerPin, currentFrequency, beats * beatLength);
  delay(beats * beatLength);  //wait for the length of the tone so that it has time to play
  delay(50);                  //a little delay between the notes makes the song sound more natural

}

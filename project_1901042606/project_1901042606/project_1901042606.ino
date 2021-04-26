/* Emre YILMAZ 1901042606 GTU */

void setup() {
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
  pinMode(13, OUTPUT);
  pinMode(5,  INPUT);
}

void loop() {

  if (Serial.available() > 0) // reply only when you receive data:
  {

    char choice; // Menu choice   
    choice = Serial.read(); // read the incoming menu choice

    if (choice == '1') // CASE: CHOICE '1'
    {
      digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
    }

    else if (choice == '2') // CASE: CHOICE '2'
    {
      digitalWrite(13, LOW);   // turn the LED off (LOW is the voltage level
    }

    else if (choice == '3') // CASE: CHOICE '3'
    {
      digitalWrite(LED_BUILTIN, LOW); // turn the LED off (LOW is the voltage level
      int i = 0;
      for (i = 0; i < 3; i++) // Flashing the led 3 times
      {
        delay(1000);
        digitalWrite(13, HIGH);
        delay(1000);
        digitalWrite(13, LOW);
      }
    }

    else if (choice == '4')
    {

      Serial.flush();
      delay(1000);
      String input_number; // This string will keep the number that come from C code.
      int int_input_number; // String above will turn into this integer variable

      while (true)
      {
        Serial.read();
        input_number = Serial.readString();
        int_input_number;
        int_input_number  = input_number.toInt();
        if (int_input_number != 0) break;   // If int_input_number = 0, it means that we could not read the number that come from C code yet.    
      }

      int_input_number = int_input_number * int_input_number;
      String output  = String(int_input_number);
      char arr[4];
      output.toCharArray(arr, 4);
      delay(1000);
      Serial.write(arr);
      Serial.flush();
    }

    else if (choice == '5')
    {
      Serial.flush();
      delay(2000);
      char ON[2] = "1";
      char OFF[2] = "0";
      delay(200);
      int ct = 0;
      delay(100);
      int check =0;
      check = digitalRead(5);
      delay(100);
      if (check == HIGH)
      {
        Serial.flush();
        delay(200);
        Serial.write(ON);
      }

      else if (check == LOW)
      {
        Serial.flush();
        delay(200);
        Serial.write(OFF);
      }
      Serial.flush();

    }
  }


}

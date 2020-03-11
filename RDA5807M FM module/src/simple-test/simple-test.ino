#include <Wire.h>
#include <RDA5807M.h>
#include <RDSParser.h>

RDA5807M radio;
RDSParser rds;

RADIO_FREQ initialFrequency = 9050;

String input_string;

void RDS_process(uint16_t block1, uint16_t block2, uint16_t block3, uint16_t block4) {
  rds.processData(block1, block2, block3, block4);
}

void DisplayServiceName(char *name) {
  Serial.print("RDS:");
  Serial.println(name);
}

void DisplayTime(uint8_t hour, uint8_t minute) {
  Serial.print("RDS-Time:");
  if (hour < 10) Serial.print('0');
  Serial.print(hour);
  Serial.print(':');
  if (minute < 10) Serial.print('0');
  Serial.print(minute);
  Serial.println();
}

bool is_number(String line) {
    char* p;
    strtol(line.c_str(), &p, 10);
    return *p == 0;
}

/*
 * set freequency by string representation
*/
void SetFrequency(String frequency_string) {
  int frequency_string_len = frequency_string.length();
  
  switch(frequency_string_len) {
    case 5:
    case 4: {
      String human_readable_frequency = GetHumanReadableFreequency(input_string);

      bool isNumber = is_number(input_string);
      if(isNumber){
        // set frequency
        long frq = atol(input_string.c_str());

        Serial.print("set frequency ");
        Serial.println(human_readable_frequency);
        
        radio.setFrequency(frq);

        char s[12];
        radio.formatFrequency(s, sizeof(s));
        Serial.print("Station:"); 
        Serial.println(s);
      } else {
        Serial.println("only numbers");
      }
    } break;

    default: {
      Serial.print("command '");
      Serial.print(input_string);
      Serial.print("' more than ");
      Serial.print(5);
      Serial.println(" symbols");
    }
  }
}


/*
 * transform string with numbers representation of freequency to formatted string
 * 
 * todo: pars strings in format '90.5', '104.5'; detect this format by dot
*/
String GetHumanReadableFreequency(String frequency) {
  int frequency_string_len = frequency.length();
  String human_readable_frequency = "";

  for(int i = 0; i < frequency_string_len; i++) {
    char current_char = input_string.charAt(i);

    /*
     * 10480 -> 104.80
     * 9050  -> 90.50
    */
    if (i == frequency_string_len - 2) {
      human_readable_frequency.concat('.');
    }
    
    human_readable_frequency.concat(current_char);
  }  
          
  human_readable_frequency.concat(" MHz");
  
  return human_readable_frequency;
}

void ShowRadioState(RDA5807M radio) {
  RADIO_FREQ fMin = radio.getMinFrequency();
  RADIO_FREQ fMax = radio.getMaxFrequency();

  Serial.print("Min. Frq.: ");
  Serial.println(fMin);

  Serial.print("Max. Frq.: ");
  Serial.println(fMax);

  char s[12];
  radio.formatFrequency(s, sizeof(s));
  Serial.print("Station:"); 
  Serial.println(s);
  
  Serial.print("Radio:"); 
  radio.debugRadioInfo();
  
  Serial.print("Audio:"); 
  radio.debugAudioInfo();

  Serial.print("Status:");
  radio.debugStatus();
}

void setup(void) {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("-= radio =-");
  
  //radio.debugEnable(true);
  
  Serial.print("Init result: ");
  Serial.println(radio.init());

  radio.setBandFrequency(RADIO_BAND_FM, initialFrequency);

  radio.setVolume(3);
  radio.setMono(true);
  radio.setMute(false);
  radio.setSoftMute(false);

  ShowRadioState(radio);

  // setup the information chain for RDS data.
  radio.attachReceiveRDS(RDS_process);
  rds.attachServicenNameCallback(DisplayServiceName);
  rds.attachTimeCallback(DisplayTime);
}

void ShowCommandInfo(String command) {
  int command_len = command.length();
  
  Serial.print("command: '");
  Serial.print(command);
  Serial.println("'");

  Serial.print("command len.: ");
  Serial.println(command_len);
}

void ProcessCommands() {
  if (Serial.available()) {
    char c = Serial.read();
    bool isNewLine = false;

    // detect new line
    if (c == '\r' || c == '\n') {
      isNewLine = true;
    }

    // process string
    int input_string_len = input_string.length();
    if(input_string_len > 0 && isNewLine) { // commands separated by new line chars
      ShowCommandInfo(input_string);
      SetFrequency(input_string);

      input_string = ""; // reset parsed command
    }

    // skip new line
    if(isNewLine == false) {
      input_string += c;
    }


    /*
    unsigned long startSeek; // after 300 msec must be tuned. after 500 msec must have RDS.
    RADIO_FREQ fSave, fLast;
    char sFreq[12];
    RADIO_INFO ri;
    */
  }
}

void loop(void) {  
  ProcessCommands();
  
  radio.checkRDS();
}

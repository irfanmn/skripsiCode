/* Copyright 2019 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#if defined(ARDUINO) && !defined(ARDUINO_ARDUINO_NANO33BLE) && !defined(ARDUINO_SEEED_XIAO_NRF52840_SENSE)
#define ARDUINO_EXCLUDE_CODE
#endif  // defined(ARDUINO) && !defined(ARDUINO_ARDUINO_NANO33BLE)

#ifndef ARDUINO_EXCLUDE_CODE

#include "Arduino.h"
#include "command_responder.h"

//Kebutuhan Remote Control IR
#include <IRremote.hpp>
#include "PinDefinitionsAndMore.h"  // Define macros for input and output pin etc.
#define DELAY_AFTER_SEND 2000
#define DELAY_AFTER_LOOP 5000
#define IR_SEND_PIN     0

// Toggles the built-in LED every inference, and lights a colored LED depending
// on which word was detected.
void RespondToCommand(tflite::ErrorReporter* error_reporter,
                      int32_t current_time, const char* found_command,
                      uint8_t score, bool is_new_command) {
  static bool is_initialized = false;
  if (!is_initialized) {
    pinMode(LED_BUILTIN, OUTPUT);
    // Pins for the built-in RGB LEDs on the Arduino Nano 33 BLE Sense
    pinMode(LEDR, OUTPUT);
    pinMode(LEDG, OUTPUT);
    pinMode(LEDB, OUTPUT);
    // Ensure the LED is off by default.
    // Note: The RGB LEDs on the Arduino Nano 33 BLE
    // Sense are on when the pin is LOW, off when HIGH.
    digitalWrite(LEDR, HIGH);
    digitalWrite(LEDG, HIGH);
    digitalWrite(LEDB, HIGH);
    is_initialized = true;
  }
  static int32_t last_command_time = 0;
  static int count = 0;

//Kebutuhan Remote Control IR
  uint32_t sAddress;
  uint8_t sCommand;
  uint8_t sRepeats;

  if(found_command[0] == 'n' && found_command[1] == 'y')
  {
    if(score > 50)
    {
      TF_LITE_REPORT_ERROR(error_reporter, "Heard %s (%d) ", found_command,
                         score);
      
      Serial.print(F("POWER Kipas"));
      
      sAddress = 0xEF00;
      sCommand = 0xFF;
      sRepeats = 0;
      IrSender.sendNEC(0xEF00, 0xFF, 0);
      delay(1000);
    }
  }
  else if (found_command[0] == 'm' && found_command[1] == 'a')
  {
    if(score > 130)
    {
    TF_LITE_REPORT_ERROR(error_reporter, "Heard %s (%d) ", found_command,
                         score);
      
    Serial.print(F("POWER Kipas"));
    sAddress = 0xEF00;
    sCommand = 0xFF;
    sRepeats = 0;
    IrSender.sendNEC(0xEF00, 0xFF, 0);
    delay(1000);
    }
  }
  else if (found_command[0] == 'n' && found_command[1] == 'a')
    {
      if(score > 50)
      { 
        TF_LITE_REPORT_ERROR(error_reporter, "Heard %s (%d) ", found_command,
                         score);
        
        Serial.print(F("Fan Naik"));
        sAddress = 0xEF00;
        sCommand = 0x7F;
        sRepeats = 0;
        IrSender.sendNEC(0xEF00, 0x7F, 0);
        delay(1000);
        }
    }
    else if(found_command[0] == 't')
      {
        if(score > 50)
        {
          TF_LITE_REPORT_ERROR(error_reporter, "Heard %s (%d) ", found_command,
                         score);
            
          Serial.print(F("Fan Turun"));
          sAddress = 0xEF00;
          sCommand = 0x3F;
          sRepeats = 0;
          IrSender.sendNEC(0xEF00, 0x3F, 0);
          delay(1000);
          }
      }
  else if(score > 150)
  {
    TF_LITE_REPORT_ERROR(error_reporter, "Heard %s (%d) ", found_command,
                         score);
  }

  //   if(found_command[0] == 'n' && found_command[1] == 'y')
  // {
  //   if(score > 50)
  //   {
  //     TF_LITE_REPORT_ERROR(error_reporter, "Heard %s (%d) ", found_command,
  //                        score);
      
  //     Serial.print(F("POWER TV"));
      
  //     sAddress = 0x707;
  //     sCommand = 0x2;
  //     sRepeats = 0;
  //     IrSender.sendSamsung(0x707, 0x2, 0);
  //     delay(5000);
  //   }
  //   else if (found_command[0] == 'm' && found_command[1] == 'a')
  //   {
  //     if(score > 150)
  //     {
  //     TF_LITE_REPORT_ERROR(error_reporter, "Heard %s (%d) ", found_command,
  //                        score);
      
  //     Serial.print(F("POWER TV"));
  //     sAddress = 0x707;
  //     sCommand = 0x2;
  //     sRepeats = 0;
  //     IrSender.sendSamsung(0x707, 0x2, 0);
  //     delay(5000);
  //   }
  //     else if (found_command[0] == 'n' && found_command[1] == 'a')
  //     {
  //       if(score > 50)
  //       { 
  //         TF_LITE_REPORT_ERROR(error_reporter, "Heard %s (%d) ", found_command,
  //                        score);
        
  //         Serial.print(F("VOL UP TV"));
  //         sAddress = 0x707;
  //         sCommand = 0x7;
  //         sRepeats = 0;
  //         IrSender.sendSamsung(0x707, 0x7, 0);
  //         delay(4000);
  //       }
  //       else if(found_command[0] == 't')
  //       {
  //         if(score > 50)
  //         {
  //           TF_LITE_REPORT_ERROR(error_reporter, "Heard %s (%d) ", found_command,
  //                        score);
            
  //           Serial.print(F("VOL DOWN TV"));
  //         sAddress = 0x707;
  //         sCommand = 0xB;
  //         sRepeats = 0;
  //         IrSender.sendSamsung(0x707, 0xB, 0);
  //         delay(4000);
  //         }
  //       }
  //     }
  //   }
  // }
  // else if(score > 150)
  // {
  //   TF_LITE_REPORT_ERROR(error_reporter, "Heard %s (%d) ", found_command,
  //                        score);
  // }
  // if(found_command[0] != 'u')
  // {
  //   if(score > 50)
  //   {
  //     TF_LITE_REPORT_ERROR(error_reporter, "Heard %s (%d) ", found_command,
  //                        score);
  //   }
  //   else if (found_command[0] =='n' && score > 50)
  //   {
  //     TF_LITE_REPORT_ERROR(error_reporter, "Heard %s (%d) ", found_command,
  //                        score);
  //   }
  // }


  // if (is_new_command) {
  //   TF_LITE_REPORT_ERROR(error_reporter, "Heard %s (%d) @%dms", found_command,
  //                        score, current_time);
  //   // If we hear a command, light up the appropriate LED
  //   digitalWrite(LEDR, HIGH);
  //   digitalWrite(LEDG, HIGH);
  //   digitalWrite(LEDB, HIGH);

  //   if (found_command[0] == 'y') {
  //     digitalWrite(LEDG, LOW);  // Green for yes
  //   } else if (found_command[0] == 'n') {
  //     digitalWrite(LEDR, LOW);  // Red for no
  //   } else if (found_command[0] == 'u') {
  //     digitalWrite(LEDB, LOW);  // Blue for unknown
  //   } else {
  //     // silence
  //   }

  //   last_command_time = current_time;
  // }

  // If last_command_time is non-zero but was >3 seconds ago, zero it
  // and switch off the LED.
  if (last_command_time != 0) {
    if (last_command_time < (current_time - 3000)) {
      last_command_time = 0;
      digitalWrite(LEDR, HIGH);
      digitalWrite(LEDG, HIGH);
      digitalWrite(LEDB, HIGH);
    }
  }

  // Otherwise, toggle the LED every time an inference is performed.
  ++count;
  if (count & 1) {
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }
}

#endif  // ARDUINO_EXCLUDE_CODE

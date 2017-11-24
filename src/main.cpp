/**
Arduino Mega 2560 pin configuration

D0  -> RX0                     *
D1  -> TX0                     *
D2  -> Interrupt 0 | PWM       *
D3  -> Interrupt 1 | PWM       *
D4  -> PWM                     *
D5  -> PWM                     *
D6  -> PWM                     *
D7  -> PWM                     *
D8  -> PWM                     *
D9  -> PWM                     *
D10 -> PWM                     *
D11 -> PWM                     *
D12 -> PWM                     *
D13 -> PWM                     *
D14 -> TX3                     *
D15 -> RX3                     *
D16 -> TX2                     *
D17 -> RX2                     *
D18 -> Motion sensor 1 | Interrupt 5
D19 -> Motion sensor 2 | Interrupt 4
D20 -> Interrupt 3 | SDA       *
D21 -> Interrupt 2 | SCL       *
D22 ->                         *
D23 ->                         *
D24 ->                         *
D25 ->                         *
D26 ->                         *
D27 ->                         *
D28 ->                         *
D29 ->                         *
D30 ->                         *
D31 ->                         *
D32 ->                         *
D33 -> Ultrasonic trigger
D34 -> Ultrasonic echo
D35 -> Start/stop alarm button
D36 ->                         *
D37 ->                         *
D38 ->                         *
D39 ->                         *
D40 ->                         *
D41 ->                         *
D42 ->                         *
D43 ->                         *
D44 -> PWM                     *
D45 -> PWM                     *
D46 -> PWM                     *
D47 ->                         *
D48 ->                         *
D49 ->                         *
D50 -> MISO                    *
D51 -> MOSI                    *
D52 -> SCK                     *
D53 -> SS                      *
##
A0  ->                         *
A1  ->                         *
A2  ->                         *
A3  ->                         *
A4  ->                         *
A5  ->                         *
A6  ->                         *
A7  ->                         *
A8  ->                         *
A9  ->                         *
A10 ->                         *
A11 ->                         *
A12 ->                         *
A13 ->                         *
A14 ->                         *
A15 ->                         *
**/

// Headers
#include <Arduino.h>
#include <setjmp.h> // For error handling only

// Degug code will only work when the line below is uncomented
// #define DEBUG

// Return the size of the array
// Equivalent method: sizeof (arr) / sizeof (size_t);
template <class T, size_t tSize>
T arraySize (T (&array) [tSize] ) {
    return tSize;
}

// Macros
#define MINUTES_TO_MILLIS(x) x*60000

// Flags         12345678
#define BOARD_1 B00000001 // 1
#define BOARD_2 B00000010 // 2
#define BOARD_3 B00000100 // 4
#define BOARD_4 B00001000 // 8

// #define BOARD_TEMPLATE B00000000

#define BOARD_DEFINED B10000000 // No board selected
#define BOARD_OVERLOAD  B01000000 // Multiple boards selected

#define ERROR_UNDEFINED 0x1
#define ERROR_OVERLOAD 0x2
#define ERROR_UNKNOW 0x3


#ifdef DEBUG
#define BOARD 0 // Default board for debuging
#endif


// Variabes
int boardSelectionPins [] = {22, 23, 24, 25};
static int motionSensorPin_1 = 18;
static int motionSensorPin_2 = 19;


unsigned long previousMillis = 0;
unsigned long currentMillis = 0;
unsigned long motionSensorInterval = MINUTES_TO_MILLIS (5);

bool runCode = false; // by default, just for safe measures, don't run any code
bool startSensing = false;
bool alarmActivated = false;

static jmp_buf jmpBuff; // Jmp buffer

byte board = B00000000;
byte boardList [] = {BOARD_1, BOARD_2, BOARD_3, BOARD_4};
// Variables


// Functions
void motionSensorTriggered (int sensorReference) {
    // Send mail
}
void motionSensorTriggered_1 () {
    motionSensorTriggered (1);
}
void motionSensorTriggered_2 () {
    motionSensorTriggered (2);
}
// Functions

void setup () {
    attachInterrupt (digitalPinToInterrupt (motionSensorPin_1), motionSensorTriggered_1, RISING);
    attachInterrupt (digitalPinToInterrupt (motionSensorPin_2), motionSensorTriggered_2, RISING);

    #ifdef DEBUG
    Serial.begin (9600);
    #endif

    #ifndef BOARD
    // If no default board was defined...
    // Set the pins for defining the board
    for (int i = 0; i < arraySize (boardSelectionPins); i++)
        pinMode (boardSelectionPins [i], INPUT);

    for (int i = 0; i < arraySize (boardSelectionPins); i++) {
        // This seems to work better
        if (digitalRead(boardSelectionPins [i])) {
            // If the board is not defined and there is a pin defined, then define the board and mark the board based in th eboard list
            if (!(board & BOARD_DEFINED)) board |= (BOARD_DEFINED | boardList [i]);
            else board |= BOARD_OVERLOAD; // If the board is already defined and there is another pin defined, then is an overload
        }
            // board |= boardList [i]; // this seems to work I gues
    }

    switch (setjmp(jmpBuff)) {
        case 0: {
            if (board & BOARD_OVERLOAD) longjmp (jmpBuff, ERROR_OVERLOAD); // If the board presents overloaded pins ...
            else if (!(board & BOARD_DEFINED)) longjmp (jmpBuff, ERROR_UNDEFINED); // If the board present undefined pins ...
            else longjmp (jmpBuff, ERROR_UNKNOW);
            break;
        }
        case ERROR_OVERLOAD: {
            // Show that there is an overload
            runCode = false;
            break;
        }
        case ERROR_UNDEFINED: {
            // Show that the board is undefined
            runCode = false;
            break;
        }
        case ERROR_UNKNOW: {
            // Unknow error, must inspect
            runCode = false;
            break;
        }
        default: {
            // Default code runs if no error is present
            runCode = true;
            break;
        }
    } // Try - catch - trow

    #endif
}

void loop () {
    if (runCode) {
        currentMillis = millis ();

        if (currentMillis - previousMillis >= motionSensorInterval) {}
    }
}

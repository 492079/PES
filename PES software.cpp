
#include "mbed.h"
#include "platform/mbed_thread.h"

//led definities
DigitalOut LED_LEFT_FW(PC_7);
DigitalOut LED_LEFT_RV(PB_6);
DigitalOut LED_RIGHT_FW(PA_7);
DigitalOut LED_RIGHT_RV(PB_3);

//knop definities
DigitalIn BUTTON_LF(PA_10, PullUp);
DigitalIn BUTTON_RF(PB_10, PullUp);
DigitalIn BUTTON_BOTTOM(PA_8, PullUp);

int state = -1; //initialiseer state
enum states{FORWARD, TURN_RIGHT, TURN_LEFT, REVERSE, REVERSE_TURN}; //enum met alle states

int main(){

    while(true){

        switch(state){ //state machine

            case FORWARD: //case voor naar voren rijden
            LED_LEFT_FW = 1; //elke case heeft waarden voor alle leds
            LED_RIGHT_FW = 1;
            LED_LEFT_RV = 0;
            LED_RIGHT_RV = 0;
            wait(0.1); //wait 0.1 zodat de stofzuigerrobot iets langer doorrijdt
            break; //break zodat de andere states worden overgeslagen

            case REVERSE: //case voor achteruit rijden
            LED_LEFT_FW = 0;
            LED_RIGHT_FW = 0;
            LED_LEFT_RV = 1;
            LED_RIGHT_RV = 1;
            wait(0.1);   
            break;  

            case TURN_RIGHT: //case voor naar rechts draaien
            LED_LEFT_FW = 1;
            LED_RIGHT_FW = 0;
            LED_LEFT_RV = 0;
            LED_RIGHT_RV = 1;      
            wait(0.1);
            break;   

            case TURN_LEFT: //case voor naar links draaien.
            LED_LEFT_FW = 0;
            LED_RIGHT_FW = 1;
            LED_LEFT_RV = 1;
            LED_RIGHT_RV = 0;
            wait(0.1);
            break;

            case REVERSE_TURN: //speciale case waarbij eerst achteruit gereden wrordt en daarna gedraaid
            LED_LEFT_FW = 0;
            LED_RIGHT_FW = 0;
            LED_LEFT_RV = 1;
            LED_RIGHT_RV = 1;
            wait(1);
            LED_LEFT_FW = 1;
            LED_RIGHT_FW = 0;
            LED_LEFT_RV = 0;
            LED_RIGHT_RV = 1;
            wait(1);
            break;

            default: //default case, alles uit
            LED_LEFT_FW = 0;
            LED_RIGHT_FW = 0;
            LED_LEFT_RV = 0;
            LED_RIGHT_RV = 0;
            break;            
        }

        if(BUTTON_LF && BUTTON_RF && BUTTON_BOTTOM){ //als geen sensoren aan
            state = FORWARD; //naar voren
        }
        else if(!BUTTON_LF && BUTTON_RF && BUTTON_BOTTOM){ //als sensor links hoog
            state = TURN_RIGHT;//naar rechts
        }
        else if(BUTTON_LF && !BUTTON_RF && BUTTON_BOTTOM){ //als sensor rechts hoog
            state = TURN_LEFT;//naar links
        }
        else if(!BUTTON_LF && !BUTTON_RF && BUTTON_BOTTOM){ //als sensor links en rechts hoog
            state = REVERSE;//naar achter
        }
        else if(BUTTON_LF && BUTTON_RF && !BUTTON_BOTTOM){ //als sensor onderkant hoog
            state = REVERSE_TURN;//naar achter en draaien
        }

    }

}



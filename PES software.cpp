//Giel Kikkert, 483040
//Sander Lodewijk, 479038
//Alan de Roo, 484283
//Bryan van Vilsteren, 481060
//Joost Reumer, 492079
//EMT1V.B, SAXION ENSCHEDE

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

enum states{FORWARD, TURN_RIGHT, TURN_LEFT, REVERSE, REVERSE_TURN}; //enum met alle states
int state = FORWARD; //initialiseer state

bool entry = 1;
bool exiting = 0;

int main(){

    while(true){

        switch(state){ //state machine

            case FORWARD: //case voor naar voren rijden
            //entry
            if(entry){
                entry = 0;
                LED_LEFT_FW = 1; //elke case heeft waarden voor alle leds
                LED_RIGHT_FW = 1;
                LED_LEFT_RV = 0;
                LED_RIGHT_RV = 0;
            }

            //during
            if(!BUTTON_LF && BUTTON_RF && BUTTON_BOTTOM){ //als sensor links hoog
                state = TURN_RIGHT;//naar rechts
                exiting = 1;
            }
            else if(BUTTON_LF && !BUTTON_RF && BUTTON_BOTTOM){ //als sensor rechts hoog
                state = TURN_LEFT;//naar links
                exiting = 1;
            }
            else if(!BUTTON_LF && !BUTTON_RF && BUTTON_BOTTOM){ //als sensor links en rechts hoog
                state = REVERSE;//naar achter
                exiting = 1;
            }
            else if(BUTTON_LF && BUTTON_RF && !BUTTON_BOTTOM){ //als sensor onderkant hoog
                state = REVERSE_TURN;//naar achter en draaien
                exiting = 1;
            }

            //exit
            if(exiting){
                exiting = 0;
                entry = 1;
            }


            break; //break zodat de andere states worden overgeslagen

            case REVERSE: //case voor achteruit rijden
            //entry
            if(entry){
                entry = 0;

                LED_LEFT_FW = 0;
                LED_RIGHT_FW = 0;
                LED_LEFT_RV = 1;
                LED_RIGHT_RV = 1;
            }

            //during
            if(BUTTON_LF && BUTTON_RF && BUTTON_BOTTOM){ //als geen sensoren aan
                state = FORWARD; //naar voren
                exiting = 1;
            }
            else if(!BUTTON_LF && BUTTON_RF && BUTTON_BOTTOM){ //als sensor links hoog
                state = TURN_RIGHT;//naar rechts
                exiting = 1;
            }
            else if(BUTTON_LF && !BUTTON_RF && BUTTON_BOTTOM){ //als sensor rechts hoog
                state = TURN_LEFT;//naar links
                exiting = 1;
            }

            //exit
            if(exiting){
                exiting = 0;
                entry = 1;
            }

            break;  

            case TURN_RIGHT: //case voor naar rechts draaien
            //entry
            if(entry){
                entry = 0;

                LED_LEFT_FW = 1;
                LED_RIGHT_FW = 0;
                LED_LEFT_RV = 0;
                LED_RIGHT_RV = 1;  
            }


            //during
            if(BUTTON_LF && BUTTON_RF && BUTTON_BOTTOM){ //als geen sensoren aan
                state = FORWARD; //naar voren
                exiting = 1;
            }
            else if(BUTTON_LF && !BUTTON_RF && BUTTON_BOTTOM){ //als sensor rechts hoog
                state = TURN_LEFT;//naar links
                exiting = 1;
            }
            else if(!BUTTON_LF && !BUTTON_RF && BUTTON_BOTTOM){ //als sensor links en rechts hoog
                state = REVERSE;//naar achter
                exiting = 1;
            }
            else if(BUTTON_LF && BUTTON_RF && !BUTTON_BOTTOM){ //als sensor onderkant hoog
                state = REVERSE_TURN;//naar achter en draaien
                exiting = 1;
            }

            //exit
            if(exiting){
                exiting = 0;
                entry = 1;
            }

            break;   

            case TURN_LEFT: //case voor naar links draaien.
            //entry
            if(entry){
                entry = 0;

                LED_LEFT_FW = 0;
                LED_RIGHT_FW = 1;
                LED_LEFT_RV = 1;
                LED_RIGHT_RV = 0;
            }

            //during
            if(BUTTON_LF && BUTTON_RF && BUTTON_BOTTOM){ //als geen sensoren aan
                state = FORWARD; //naar voren
                exiting = 1;
            }
            else if(!BUTTON_LF && BUTTON_RF && BUTTON_BOTTOM){ //als sensor links hoog
                state = TURN_RIGHT;//naar rechts
                exiting = 1;
            }
            else if(!BUTTON_LF && !BUTTON_RF && BUTTON_BOTTOM){ //als sensor links en rechts hoog
                state = REVERSE;//naar achter
                exiting = 1;
            }
            else if(BUTTON_LF && BUTTON_RF && !BUTTON_BOTTOM){ //als sensor onderkant hoog
                state = REVERSE_TURN;//naar achter en draaien
                exiting = 1;
            }

            //exit
            if(exiting){
                exiting = 0;
                entry = 1;
            }
            break;

            case REVERSE_TURN: //speciale case waarbij eerst achteruit gereden wrordt en daarna gedraaid
            //entry&exit
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
            
            state = FORWARD;
            break;

            default: //default case, alles uit
            LED_LEFT_FW = 0;
            LED_RIGHT_FW = 0;
            LED_LEFT_RV = 0;
            LED_RIGHT_RV = 0;
            break;            
        }

    }

}



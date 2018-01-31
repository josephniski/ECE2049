
//Drew Robert & Joseph Niski
//ECE 2049
//Lab 2

#include <msp430.h>
#include "peripherals.h"

// Function Prototypes
void swDelay(char numLoops);
void configBoardButtons();
void configLaunchButtons();
char buttonStates();



// Declare globals here
int state = 0;
char pressed = 0xFF;
unsigned char currKey=0;
int once = 1;


// Main
void main(void)
{

    WDTCTL = WDTPW | WDTHOLD;    // Stop watchdog timer. Always need to stop this!!
                                 // You can then configure it properly, if desired
    pressed = 0xFF;

    initLeds();

    configDisplay();
    configKeypad();
    configBoardButtons();
    configLaunchButtons();

    // *** Intro Screen ***
    Graphics_clearDisplay(&g_sContext); // Clear the display

    while(1){

    switch (state){
    case 0: // Display Welcome Screen

        currKey = getKey();

        while(once == 1)
        {
        // Write some text to the display
        Graphics_drawStringCentered(&g_sContext, "Welcome", AUTO_STRING_LENGTH, 48, 15, TRANSPARENT_TEXT);
        Graphics_drawStringCentered(&g_sContext, "to", AUTO_STRING_LENGTH, 48, 25, TRANSPARENT_TEXT);
        Graphics_drawStringCentered(&g_sContext, "M-HESS-P430.", AUTO_STRING_LENGTH, 48, 35, TRANSPARENT_TEXT);
        Graphics_drawStringCentered(&g_sContext, "Press '*'", AUTO_STRING_LENGTH, 48, 55, TRANSPARENT_TEXT);
        Graphics_drawStringCentered(&g_sContext, "to Start", AUTO_STRING_LENGTH, 48, 65, TRANSPARENT_TEXT);

        // Draw a box around everything because it looks nice
        Graphics_Rectangle box = {.xMin = 5, .xMax = 91, .yMin = 5, .yMax = 91 };
        Graphics_drawRectangle(&g_sContext, &box);

        // Update display
        Graphics_flushBuffer(&g_sContext);
        once = 0;
        }

        if (currKey == '*'){
            state = 1;
            once = 1;
            Graphics_clearDisplay(&g_sContext); // Clear the display
        }

        break;

    case 1: // Select Grade

        currKey = getKey();
        //once = 1;
        while(once == 1)
        {
        Graphics_drawStringCentered(&g_sContext, "Select Grade", AUTO_STRING_LENGTH, 48, 15, TRANSPARENT_TEXT);
        Graphics_drawStringCentered(&g_sContext, "1 = Diesel", AUTO_STRING_LENGTH, 48, 25, TRANSPARENT_TEXT);
        Graphics_drawStringCentered(&g_sContext, "2 = Super", AUTO_STRING_LENGTH, 48, 35, TRANSPARENT_TEXT);
        Graphics_drawStringCentered(&g_sContext, "3 = Premium", AUTO_STRING_LENGTH, 48, 45, TRANSPARENT_TEXT);
        Graphics_drawStringCentered(&g_sContext, "4 = Regular", AUTO_STRING_LENGTH, 48, 55, TRANSPARENT_TEXT);

        Graphics_flushBuffer(&g_sContext);
        once = 0;
        }

        pressed = buttonStates();

        if (pressed == 0x01){
            state = 2;
            Graphics_clearDisplay(&g_sContext); // Clear the display
        }

        else if (pressed == 0x04){
            state = 3;
            Graphics_clearDisplay(&g_sContext); // Clear the display
        }

        else if (pressed == 0x10){
            state = 4;
            Graphics_clearDisplay(&g_sContext); // Clear the display
        }

        else if (pressed == 0x40){
            state = 5;
            Graphics_clearDisplay(&g_sContext); // Clear the display
        }


        break;


    case 2: //Diesel

        currKey = getKey();


        Graphics_drawStringCentered(&g_sContext, "Diesel Selected", AUTO_STRING_LENGTH, 48, 15, TRANSPARENT_TEXT);
        Graphics_drawStringCentered(&g_sContext, "Correct?", AUTO_STRING_LENGTH, 48, 25, TRANSPARENT_TEXT);
        Graphics_drawStringCentered(&g_sContext, "'*' Continue", AUTO_STRING_LENGTH, 48, 35, TRANSPARENT_TEXT);
        Graphics_drawStringCentered(&g_sContext, "'#' Restart", AUTO_STRING_LENGTH, 48, 45, TRANSPARENT_TEXT);

        // Update display
        Graphics_flushBuffer(&g_sContext);

        if (currKey == '*')
        {
            state = 6;
            Graphics_clearDisplay(&g_sContext); // Clear the display
        }
        if (currKey == '#')
        {
            state = 1;
            Graphics_clearDisplay(&g_sContext); // Clear the display
        }

        break;



    case 3: //Super


        Graphics_drawStringCentered(&g_sContext, "Super Selected", AUTO_STRING_LENGTH, 48, 15, TRANSPARENT_TEXT);
        Graphics_drawStringCentered(&g_sContext, "Correct?", AUTO_STRING_LENGTH, 48, 25, TRANSPARENT_TEXT);
        Graphics_drawStringCentered(&g_sContext, "'*' Continue", AUTO_STRING_LENGTH, 48, 35, TRANSPARENT_TEXT);
        Graphics_drawStringCentered(&g_sContext, "'#' Restart", AUTO_STRING_LENGTH, 48, 45, TRANSPARENT_TEXT);

        // Update display
        Graphics_flushBuffer(&g_sContext);

        if (currKey == '*'){
            state = 6;
            Graphics_clearDisplay(&g_sContext); // Clear the display
        }
        if (currKey == '#'){
            state = 1;
            Graphics_clearDisplay(&g_sContext); // Clear the display
        }

        break;



    case 4: //Regular


        Graphics_drawStringCentered(&g_sContext, "Regular Selected", AUTO_STRING_LENGTH, 48, 15, TRANSPARENT_TEXT);
        Graphics_drawStringCentered(&g_sContext, "Correct?", AUTO_STRING_LENGTH, 48, 25, TRANSPARENT_TEXT);
        Graphics_drawStringCentered(&g_sContext, "'*' Continue", AUTO_STRING_LENGTH, 48, 35, TRANSPARENT_TEXT);
        Graphics_drawStringCentered(&g_sContext, "'#' Restart", AUTO_STRING_LENGTH, 48, 45, TRANSPARENT_TEXT);

        // Update display
        Graphics_flushBuffer(&g_sContext);

        if (currKey == '*'){
            state = 6;
            Graphics_clearDisplay(&g_sContext); // Clear the display
        }
        if (currKey == '#'){
            state = 1;
            Graphics_clearDisplay(&g_sContext); // Clear the display
        }

        break;



    case 5: //Premium


        Graphics_drawStringCentered(&g_sContext, "Premium Selected", AUTO_STRING_LENGTH, 48, 15, TRANSPARENT_TEXT);
        Graphics_drawStringCentered(&g_sContext, "Correct?", AUTO_STRING_LENGTH, 48, 25, TRANSPARENT_TEXT);
        Graphics_drawStringCentered(&g_sContext, "'*' Continue", AUTO_STRING_LENGTH, 48, 35, TRANSPARENT_TEXT);
        Graphics_drawStringCentered(&g_sContext, "'#' Restart", AUTO_STRING_LENGTH, 48, 45, TRANSPARENT_TEXT);

        // Update display
        Graphics_flushBuffer(&g_sContext);

        if (currKey == '*'){
            state = 6;
            Graphics_clearDisplay(&g_sContext); // Clear the display
        }
        if (currKey == '#'){
            state = 1;
            Graphics_clearDisplay(&g_sContext); // Clear the display
        }

        break;



    case 6: // Pump Ready
        Graphics_drawStringCentered(&g_sContext, "Pump Ready.", AUTO_STRING_LENGTH, 48, 15, TRANSPARENT_TEXT);
        Graphics_drawStringCentered(&g_sContext, "Begin Fueling", AUTO_STRING_LENGTH, 48, 25, TRANSPARENT_TEXT);

    }//end the switch state
    }//end the while loop



}


void swDelay(char numLoops)
{
	// This function is a software delay. It performs
	// useless loops to waste a bit of time
	//
	// Input: numLoops = number of delay loops to execute
	// Output: none
	//
	// smj, ECE2049, 25 Aug 2013

	volatile unsigned int i,j;	// volatile to prevent removal in optimization
			                    // by compiler. Functionally this is useless code

	for (j=0; j<numLoops; j++)
    {
    	i = 50000 ;					// SW Delay
   	    while (i > 0)				// could also have used while (i)
	       i--;
    }
}

void configBoardButtons(){
    //4 Board Buttons: P7.0, P3.6, P2.2, P7.4

    P7SEL &= (BIT7|BIT6|BIT5|BIT3|BIT2|BIT1); //xxx0 xxx0
    P3SEL &= (BIT7|BIT5|BIT4|BIT3|BIT2|BIT1|BIT0); //x0xx xxxx
    P2SEL &= (BIT7|BIT6|BIT5|BIT4|BIT3|BIT1|BIT0); //xxxx x0xx

    P7DIR &= (BIT7|BIT6|BIT5|BIT3|BIT2|BIT1); //xxx0 xxx0
    P3DIR &= (BIT7|BIT5|BIT4|BIT3|BIT2|BIT1|BIT0); //x0xx xxxx
    P2DIR &= (BIT7|BIT6|BIT5|BIT4|BIT3|BIT1|BIT0); //xxxx x0xx

    P7REN |= (BIT0|BIT4);
    P3REN |= (BIT6);
    P2REN |= (BIT2);

    P7OUT |= (BIT0|BIT4);
    P3OUT |= (BIT6);
    P2OUT |= (BIT2);
}

void configLaunchButtons(){
    //2 Launchpd Buttons: P1.1, P2.1

    P2SEL &= (BIT7|BIT6|BIT5|BIT4|BIT3|BIT2|BIT0); //xxxx xx0x
    P1SEL &= (BIT7|BIT6|BIT5|BIT4|BIT3|BIT2|BIT0); //xxxx xx0x

    P2DIR &= (BIT7|BIT6|BIT5|BIT4|BIT3|BIT2|BIT0); //xxxx xx0x
    P1DIR &= (BIT7|BIT6|BIT5|BIT4|BIT3|BIT2|BIT0); //xxxx xx0x
}

char buttonStates(){
    //1 is not pressed
    //0 is pressed

    char inBits7, inBits3, inBits2;
    char out72=0, out71=0, out3=0, out2=0, out=0;

    inBits7 = P7IN & (BIT0|BIT4); //000x 000x, keep bits 0 and 4
    inBits3 = P3IN & (BIT6); //0x00 0000, keep bit 6
    inBits2 = P2IN & (BIT2); //0000 0x00, keep bit 2

    if (!(inBits7 & BIT0))
        out71 = 0x01; //0000 0001
    else if (!(inBits7 & BIT4))
        out72 = 0x04;
    else if (!(inBits3 & BIT6))
        out3 = 0x10;
    else if (!(inBits2 & BIT2))
        out2 = 0x40;

    out = (out71|out72|out3|out2);

    return out;
}

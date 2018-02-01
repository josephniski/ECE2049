
//Drew Robert & Joseph Niski
//ECE 2049
//Lab 1

#include <msp430.h>
#include <stdlib.h>
#include "stdbool.h"
#include "peripherals.h"
#include <string.h>
#include <time.h>

// Function Prototypes
void swDelay(char numLoops);
void dealHand(int cutNum);

// Global Variables
unsigned char currKey = 0, dispSz = 3;
unsigned char cutVals[2] = {0, 0};
int state = 0;
int i = 0;
unsigned char yourBetVal;
unsigned char cpuBetVal;
int difference;
unsigned char handCPU[5] = {0, 0, 0, 0, 0};
unsigned char handPlayer[5]= {0, 0, 0, 0, 0};
int pastNumbers[52];
int card;
unsigned char suit[4][1] = { "H", "D", "C", "S" };
int cardVal;
int i, j, k;
int random_index;
int inputVal;
int cutNumber;
int cardVal;
int deck[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int num = 0;
int n = 0;
int once = 1;

// Main
void main(void)

{
    WDTCTL = WDTPW | WDTHOLD; // Stop watchdog timer. Always need to stop this!!
                              // You can then configure it properly, if desired

    initLeds();
    configDisplay();
    configKeypad();

    currKey = getKey();

    //populateDeck();

    // *** Intro Screen ***
    Graphics_clearDisplay(&g_sContext); // Clear the display

    while (1)
    {


        switch (state)
        {
        case 0: // Display Welcome Screen

            currKey = getKey();

            while (once == 1){
            // Write some text to the display
            Graphics_drawStringCentered(&g_sContext, "MSP430",
            AUTO_STRING_LENGTH,
                                        48, 15,
                                        TRANSPARENT_TEXT);
            Graphics_drawStringCentered(&g_sContext, "Blackjack",
            AUTO_STRING_LENGTH,
                                        48, 25,
                                        TRANSPARENT_TEXT);
            Graphics_drawStringCentered(&g_sContext, "Press '*'",
            AUTO_STRING_LENGTH,
                                        48, 35,
                                        TRANSPARENT_TEXT);
            Graphics_drawStringCentered(&g_sContext, "to Start",
            AUTO_STRING_LENGTH,
                                        48, 45,
                                        TRANSPARENT_TEXT);

            // Draw a box around everything because it looks nice
            Graphics_Rectangle box = { .xMin = 3, .xMax = 93, .yMin = 3, .yMax =
                                               93 };
            Graphics_drawRectangle(&g_sContext, &box);

            // We are now done writing to the display.  However, if we stopped here, we would not
            // see any changes on the actual LCD.  This is because we need to send our changes
            // to the LCD, which then refreshes the display.
            // Since this is a slow operation, it is best to refresh (or "flush") only after
            // we are done drawing everything we need.
            Graphics_flushBuffer(&g_sContext);
            once = 0;
            } //end once loop

            if (currKey == '*')
            {
                state = 1;
                Graphics_clearDisplay(&g_sContext); // Clear the display
                once = 1;
            }

            break;

        case 1: // Cut

            currKey = getKey();

            // Write some text to the display
            Graphics_drawStringCentered(&g_sContext, "Enter a Number",
            AUTO_STRING_LENGTH,
                                        48, 15,
                                        TRANSPARENT_TEXT);
            Graphics_drawStringCentered(&g_sContext, "00 - 15",
            AUTO_STRING_LENGTH,
                                        48, 25,
                                        TRANSPARENT_TEXT);
            Graphics_drawStringCentered(&g_sContext, "to Cut.",
            AUTO_STRING_LENGTH,
                                        48, 35,
                                        TRANSPARENT_TEXT);
            Graphics_drawStringCentered(&g_sContext, "Cut Number:",
            AUTO_STRING_LENGTH,
                                        48, 55,
                                        TRANSPARENT_TEXT);
            Graphics_drawStringCentered(&g_sContext, "Press '#' to",
            AUTO_STRING_LENGTH,
                                        48, 75,
                                        TRANSPARENT_TEXT);
            Graphics_drawStringCentered(&g_sContext, "Lock in Cut",
            AUTO_STRING_LENGTH,
                                        48, 85,
                                        TRANSPARENT_TEXT);




            Graphics_flushBuffer(&g_sContext);



            while (i < 2)
            {

                currKey = getKey();

                if ((currKey >= '0') && (currKey <= '9'))
                {
                    cutVals[i] = currKey;
                    i++;
                    swDelay(1);
                } //end if statement

            } //end while loop

            inputVal = ((cutVals[0] * 10) - 0x30) + (cutVals[1] - 0x30);

            setLeds(inputVal);

            // Draw the new character to the display
            Graphics_drawStringCentered(&g_sContext, cutVals, 2, 48, 65,
            OPAQUE_TEXT);

            // Refresh the display so it shows the new data
            Graphics_flushBuffer(&g_sContext);

            if (currKey == '#')
            {
                Graphics_clearDisplay(&g_sContext); // Clear the display
                state = 2;
                once = 1;
            }

            break;

        case 2: // Shuffle & Deal

            currKey = getKey();

            dealHand(inputVal);

            //Display Deal
            Graphics_drawStringCentered(&g_sContext, "CPU Hand:",
                                        AUTO_STRING_LENGTH, 48, 15,
                                        TRANSPARENT_TEXT);
            Graphics_drawStringCentered(&g_sContext, handCPU, 2, 48, 25,
                                        OPAQUE_TEXT);
            Graphics_drawStringCentered(&g_sContext, "XXX:", AUTO_STRING_LENGTH,
                                        48, 35, TRANSPARENT_TEXT);
            Graphics_drawStringCentered(&g_sContext, "Your Hand:",
                                        AUTO_STRING_LENGTH, 48, 55,
                                        TRANSPARENT_TEXT);
            Graphics_drawStringCentered(&g_sContext, (handPlayer[0] + '0'), 1, 48, 65,
                                        OPAQUE_TEXT);
            Graphics_drawStringCentered(&g_sContext, (handPlayer[1] + '0'), 1, 48, 75,
                                        OPAQUE_TEXT);
            Graphics_drawStringCentered(&g_sContext, "'#' to Cont.",
                                        AUTO_STRING_LENGTH, 48, 85,
                                        TRANSPARENT_TEXT);

            // Refresh the display so it shows the new data
            Graphics_flushBuffer(&g_sContext);

            if (currKey == '#')
            {
                Graphics_clearDisplay(&g_sContext); // Clear the display
                state = 3;
            }

            break;

        case 3: // Betting 1

            currKey = getKey();

            Graphics_drawStringCentered(&g_sContext, "Enter Bet:",
            AUTO_STRING_LENGTH,
                                        48, 15,
                                        TRANSPARENT_TEXT);
            Graphics_drawStringCentered(&g_sContext, "1,2,4,or 8",
            AUTO_STRING_LENGTH,
                                        48, 25,
                                        TRANSPARENT_TEXT);
            Graphics_drawStringCentered(&g_sContext, "Your Bet:",
            AUTO_STRING_LENGTH,
                                        48, 45,
                                        TRANSPARENT_TEXT);
            Graphics_drawStringCentered(&g_sContext, "Press '#' to",
            AUTO_STRING_LENGTH,
                                        48, 75,
                                        TRANSPARENT_TEXT);
            Graphics_drawStringCentered(&g_sContext, "Lock in Bet",
            AUTO_STRING_LENGTH,
                                        48, 85,
                                        TRANSPARENT_TEXT);

            currKey = getKey();

            if ((currKey >= '0') && (currKey <= '9'))
            {
                yourBetVal = currKey;
            }

            Graphics_drawStringCentered(&g_sContext, yourBetVal, 1, 48, 55,
            OPAQUE_TEXT);

            // Refresh the display so it shows the new data
            Graphics_flushBuffer(&g_sContext);

            setLeds(yourBetVal - 0x30);

            //CPU Fixed Bets
            //if(CPU HAND <10 bet 1)
            //cpuBetVal
            //if(CPU HAND >10 <14 2)
            //if(CPU HAND >14 <18 bet 4)
            //if(CPU HAND >18 <21  bet 8)

            if (currKey == '#')
            {
                Graphics_clearDisplay(&g_sContext); // Clear the display
                Graphics_drawStringCentered(&g_sContext, "CPU Bet:",
                AUTO_STRING_LENGTH,
                                            48, 15,
                                            TRANSPARENT_TEXT);
                Graphics_drawStringCentered(&g_sContext, cpuBetVal, 1, 48, 25,
                OPAQUE_TEXT);
                swDelay(5);
                state = 4;
                Graphics_clearDisplay(&g_sContext); // Clear the display
            }

            break;

        case 4: //Betting 2
            currKey = getKey();

            setLeds(yourBetVal - 0x30);

            if (cpuBetVal > yourBetVal)
            {
                difference = cpuBetVal - yourBetVal;
                Graphics_drawStringCentered(&g_sContext, "Meet CPU Bet:",
                AUTO_STRING_LENGTH,
                                            48, 15,
                                            TRANSPARENT_TEXT);
                Graphics_drawStringCentered(&g_sContext, "Input:",
                AUTO_STRING_LENGTH,
                                            48, 25,
                                            TRANSPARENT_TEXT);
                Graphics_drawStringCentered(&g_sContext, difference, 1, 48, 35,
                OPAQUE_TEXT);

                Graphics_drawStringCentered(&g_sContext, "or Press '*'",
                AUTO_STRING_LENGTH,
                                            48, 25,
                                            TRANSPARENT_TEXT);
                Graphics_drawStringCentered(&g_sContext, "to Fold.",
                AUTO_STRING_LENGTH,
                                            48, 25,
                                            TRANSPARENT_TEXT);

                if (currKey == difference)
                {
                    setLeds(0);
                    setLeds((difference + yourBetVal) - 0x30);
                    swDelay(5);
                    state = 5;
                    Graphics_clearDisplay(&g_sContext); // Clear the display
                }

                if (currKey == '*')
                { //Fold
                    state = 7; //CHANGE TO LOSING STATE
                    Graphics_clearDisplay(&g_sContext); // Clear the display
                }
            } //end if loop

            else if (yourBetVal > cpuBetVal)
            {
                state = 7; //CHANGE TO WINNING STATE
                Graphics_clearDisplay(&g_sContext); // Clear the display
            }

            else if (yourBetVal == cpuBetVal)
            { //Bets were made equal, move on
                state = 5;
                Graphics_clearDisplay(&g_sContext); // Clear the display
            }

            break;

        case 5: //Dealing more cards, etc

            currKey = getKey();

            Graphics_drawStringCentered(&g_sContext, "CPU Hand:",
            AUTO_STRING_LENGTH,
                                        48, 15,
                                        TRANSPARENT_TEXT);
            Graphics_drawStringCentered(&g_sContext, "XXX", AUTO_STRING_LENGTH,
                                        48, 35, TRANSPARENT_TEXT);
            Graphics_drawStringCentered(&g_sContext, "Your Hand:",
            AUTO_STRING_LENGTH,
                                        48, 55,
                                        TRANSPARENT_TEXT);

            if (currKey == '1')
            {
                //another card
            }

            else if (currKey == '#')
            {
                //holds
            }

            break;

        case 6: //End game

            //if(/* player wins */){

        } //end switch statement
    } // end case while loop

} // end main

void swDelay(char numLoops)
{
    // This function is a software delay. It performs
    // useless loops to waste a bit of time
    //
    // Input: numLoops = number of delay loops to execute
    // Output: none
    //
    // smj, ECE2049, 25 Aug 2013

    volatile unsigned int i, j;  // volatile to prevent removal in optimization
                                 // by compiler. Functionally this is useless code

    for (j = 0; j < numLoops; j++)
    {
        i = 50000;                 // SW Delay
        while (i > 0)               // could also have used while (i)
            i--;
    }
}

//0-12 = A-K Hearts, 13-25 = Clubs, 26-38 = Diamonds, 39-51 = Spades
/*Checking Suit*/
unsigned char* checkSuit(int card)
{
    if (card >= 0 && card <= 12)
    {
        return suit[0][0];
    }
    else if (card >= 13 && card <= 25)
    {
        return suit[1][0];
    }
    else if (card >= 26 && card <= 38)
    {
        return suit[2][0];
    }
    else if (card >= 39 && card <= 51)
    {
        return suit[3][0];
    }


}

/*Checking Card Val*/
//A = 0, 2 = 1, ... , K = 13.
int checkCard(int cardInput)
{
    card = cardInput % 13;
    if (card > 0 && card < 10)
    {
        cardVal = card + 1;
    }
    else if (card == 0)
    {
        cardVal = 1;
    }
    else if (card >= 10)
    {
        cardVal = 10;
    }
    return cardVal;
}


void dealHand(int cutNum)
{
    int n = 11;
   /* Initializes random number generator */
    srand((unsigned) cutNum);
    for( i = 0 ; i < n ; i++ )
    {
        num = rand() % 52;
        for(j = 0; j < 52; j++)
        {
            if(deck[j] != num)
            {
                deck[i] = num;
            }
        }
   }

   handPlayer[0] = deck[0] % 13; //need to convert to ascii
   handCPU[0] = deck[1] % 13;
   handPlayer[1] = deck[2] % 13;
   handCPU[1] = deck[3] % 13;

}





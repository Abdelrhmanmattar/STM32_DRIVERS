#include "KEY_PAD.h"

const uint8_t KEY_ROWS[4]={R0 , R1 , R2 , R3};
const uint8_t KEY_COLS[4]={C0 , C1 , C2 , C3};
const uint8_t arr[4][4]={{'7','8','9','/'},{'4','5','6','*'},{'1','2','3','-'},{'A','0','=','+'}};



void Keypad_init(void)
{
    GPIOB_ClockEnable();
    PIN_CONFIG_t Keypad_PinConfig;
    //start with ROWS are output and COLUMNS are input
    Keypad_PinConfig.GPIO_PinMode = Output_General_PushPull;
    Keypad_PinConfig.GPIO_Direction = Output_10MHz;
    for(uint8_t i=0;i<4;i++)
    {
        Keypad_PinConfig.GPIO_PinNumber = KEY_ROWS[i];
        MCAL_GPIO_Init(KEYPAD_PORT,&Keypad_PinConfig);
    }

    Keypad_PinConfig.GPIO_PinMode = Input_PullUp;
    Keypad_PinConfig.GPIO_Direction = Input;
    for(uint8_t i=0;i<4;i++)
    {
        Keypad_PinConfig.GPIO_PinNumber = KEY_COLS[i];
        MCAL_GPIO_Init(KEYPAD_PORT,&Keypad_PinConfig);
    }
}

uint8_t Keypad_getkey(void)
{
    uint8_t row,coloumn,x;
	uint8_t  returnval=0xff;

    for(row=0;row<4;row++)
    {
        //make all row pins high except the current row
        MCAL_GPIO_WritePin(KEYPAD_PORT,KEY_ROWS[0],GPIO_PIN_SET);
        MCAL_GPIO_WritePin(KEYPAD_PORT,KEY_ROWS[1],GPIO_PIN_SET);
        MCAL_GPIO_WritePin(KEYPAD_PORT,KEY_ROWS[2],GPIO_PIN_SET);
        MCAL_GPIO_WritePin(KEYPAD_PORT,KEY_ROWS[3],GPIO_PIN_SET);
        MCAL_GPIO_WritePin(KEYPAD_PORT,KEY_ROWS[row],GPIO_PIN_RESET);

        //check the columns
        for(coloumn=0;coloumn<4;coloumn++)
        {
            x=MCAL_GPIO_ReadPin(KEYPAD_PORT,KEY_COLS[coloumn]);
            if(x==0)
            {
                returnval=arr[row][coloumn];
                while(x==0)
                {
                    x=MCAL_GPIO_ReadPin(KEYPAD_PORT,KEY_COLS[coloumn]);
                }
            }
        }
    }
    return returnval;
}

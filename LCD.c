#include"LCD.h"


static void delay_ms(uint32_t time) {
	uint32_t i, j;
	for (i = 0; i < time; i++){
		for (j = 0; j < 255; j++)
		{}
	}
}

static void LCD_PINS_INIT(void) {
    // Initialize LCD pins
    #if defined EIGHT_BIT_MODE
    // Initialize LCD data pins
    PIN_CONFIG_t data_pins;
    data_pins.GPIO_PinNumber = DATA_PIN_START;
    data_pins.GPIO_PinMode = Output_General_PushPull;
    data_pins.GPIO_Direction = Output_10MHz;

    for(uint8_t i=0; i<EIGHT_BIT_MODE ;i++)
    {
        data_pins.GPIO_PinNumber = DATA_PIN_START + i;
        MCAL_GPIO_Init(LCD_CONTROL_PORT, &data_pins);
    }

    // Initialize LCD control pins
    PIN_CONFIG_t control_pins;
    control_pins.GPIO_PinNumber = RS_PIN;
    control_pins.GPIO_PinMode = Output_General_PushPull;
    control_pins.GPIO_Direction = Output_10MHz;
    MCAL_GPIO_Init(LCD_CONTROL_PORT, &control_pins);

    control_pins.GPIO_PinNumber = RW_PIN;
    MCAL_GPIO_Init(LCD_CONTROL_PORT, &control_pins);

    control_pins.GPIO_PinNumber = EN_PIN;
    MCAL_GPIO_Init(LCD_CONTROL_PORT, &control_pins);

    #elif defined FOUR_BIT_MODE

    // Initialize LCD data pins
    PIN_CONFIG_t data_pins;
    data_pins.GPIO_PinNumber = DATA_PIN_START;
    data_pins.GPIO_PinMode = Output_General_PushPull;
    data_pins.GPIO_Direction = Output_10MHz;

    for(uint8_t i=0; i<4 ;i++)
    {
        data_pins.GPIO_PinNumber = DATA_PIN_START + i;
        MCAL_GPIO_Init(LCD_CONTROL_PORT, &data_pins);
    }

    // Initialize LCD control pins
    PIN_CONFIG_t control_pins;
    control_pins.GPIO_PinNumber = RS_PIN;
    control_pins.GPIO_PinMode = Output_General_PushPull;
    control_pins.GPIO_Direction = Output_10MHz;
    MCAL_GPIO_Init(LCD_CONTROL_PORT, &control_pins);

    control_pins.GPIO_PinNumber = RW_PIN;
    MCAL_GPIO_Init(LCD_CONTROL_PORT, &control_pins);

    control_pins.GPIO_PinNumber = EN_PIN;
    MCAL_GPIO_Init(LCD_CONTROL_PORT, &control_pins);



    #endif

    MCAL_GPIO_WritePin(LCD_CONTROL_PORT, RS_PIN, GPIO_PIN_RESET);
    MCAL_GPIO_WritePin(LCD_CONTROL_PORT, RW_PIN, GPIO_PIN_RESET);
    MCAL_GPIO_WritePin(LCD_CONTROL_PORT, EN_PIN, GPIO_PIN_RESET);
}

void LCD_ENABLE_PULSE(void) {
    // Enable pulse
    MCAL_GPIO_WritePin(LCD_CONTROL_PORT, EN_PIN, GPIO_PIN_SET);
    delay_ms(20);
    MCAL_GPIO_WritePin(LCD_CONTROL_PORT, EN_PIN, GPIO_PIN_RESET);
    delay_ms(20);
}

void LCD_Init(void)
{
    // Initialize LCD AS 8-bit mode
    //delay for 20ms
    delay_ms(30);
    LCD_PINS_INIT();
    delay_ms(30);
    #if defined EIGHT_BIT_MODE
    LCD_SendCommand(LCD_CLEAR_SCREEN);
    LCD_SendCommand(LCD_FUNCTION_8BIT_2LINES);
    LCD_SendCommand(LCD_ENTRY_MODE);
    LCD_SendCommand(LCD_BEGIN_AT_FIRST_ROW);
    LCD_SendCommand(LCD_DISP_ON_CURSOR_BLINK);
    #elif defined FOUR_BIT_MODE
    LCD_SendCommand(LCD_RETURN_HOME);
    LCD_SendCommand(LCD_FUNCTION_4BIT_2LINES);
    LCD_SendCommand(LCD_ENTRY_MODE);
    LCD_SendCommand(LCD_BEGIN_AT_FIRST_ROW);
    LCD_SendCommand(LCD_DISP_ON_CURSOR_BLINK);
    #endif
}

void LCD_SendCommand(uint8_t command)
{
    // SEND COMMAND TO LCD
    MCAL_GPIO_WritePin(LCD_CONTROL_PORT, RS_PIN, GPIO_PIN_RESET);
    MCAL_GPIO_WritePin(LCD_CONTROL_PORT, RW_PIN, GPIO_PIN_RESET);

    #if defined EIGHT_BIT_MODE
    LCD_DATA_OUT_PORT &= ~(0xFF<<DATA_PIN_START);
    LCD_DATA_OUT_PORT |=  (((uint16_t)command<<DATA_PIN_START));
    LCD_ENABLE_PULSE();
    #elif defined FOUR_BIT_MODE
    LCD_DATA_OUT_PORT &= ~(0X000F<<DATA_PIN_START);
    LCD_DATA_OUT_PORT |= (uint16_t)(command>>4)<<DATA_PIN_START;
    LCD_ENABLE_PULSE();

    LCD_DATA_OUT_PORT &= ~(0X000F<<DATA_PIN_START);
    LCD_DATA_OUT_PORT |= ((uint16_t)(command & 0X0F)<<DATA_PIN_START);
    LCD_ENABLE_PULSE();
    #endif
    delay_ms(30);
}

void LCD_Sendchar(uint8_t data)
{
    MCAL_GPIO_WritePin(LCD_CONTROL_PORT, RS_PIN, GPIO_PIN_SET);
    MCAL_GPIO_WritePin(LCD_CONTROL_PORT, RW_PIN, GPIO_PIN_RESET);

    #if defined EIGHT_BIT_MODE
    LCD_DATA_OUT_PORT &= ~(0xFF<<DATA_PIN_START);
    LCD_DATA_OUT_PORT |= ( ((uint16_t)data<<DATA_PIN_START));
    LCD_ENABLE_PULSE();
    #elif defined FOUR_BIT_MODE
    LCD_DATA_OUT_PORT &= ~(0X000F<<DATA_PIN_START);
    LCD_DATA_OUT_PORT |= (uint16_t)(data>>4)<<DATA_PIN_START;
    LCD_ENABLE_PULSE();

    LCD_DATA_OUT_PORT &= ~(0X000F<<DATA_PIN_START);
    LCD_DATA_OUT_PORT |= ((uint16_t)(data & 0X0F)<<DATA_PIN_START);
    LCD_ENABLE_PULSE();
    #endif
}

void LCD_SendString(const uint8_t *data)
{
    uint8_t count = 0;
    while(*data)
    {
        LCD_Sendchar(*data);
        data++;
        count++;
        if(count == 16)
        {
            LCD_SendCommand(LCD_BEGIN_AT_SECOND_ROW);
        }
        if (count == 32)
        {
            LCD_SendCommand(LCD_BEGIN_AT_FIRST_ROW);
            count =0;
        }        
    }
}

void LCD_GoToXY(uint8_t x, uint8_t y)
{
    if(x == 0)
    {
        LCD_SendCommand(LCD_BEGIN_AT_FIRST_ROW + y);
    }
    else if(x == 1)
    {
        LCD_SendCommand(LCD_BEGIN_AT_SECOND_ROW + y);
    }
}

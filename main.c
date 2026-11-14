#include"header.h"
#define SAFE   0
#define HOT    1
#define DARK   2
#define WATER  3
#define ALERT  4

int main()
{
    unsigned int temp;
    unsigned int light;
    unsigned int soil;
    unsigned char water;
    float temperature;
    unsigned char status;

    //GPIO_Init();
	  IODIR0|=7<<17;
	  IODIR|=1<<5;
	IOSET0|=7<<17;
	IOSET0|=1<<5;
    ADC_Init();
    UART_Init(9600);
    LCD_Init();

    while(1)
    {
        / *Read_adc sensors */
        temp = adc_Read(1);
        light = adc_Read(2);
        soil = adc_Read(3);
        water = Water_Sensor_Read();

        /*  Convert temperature */
        temperature = (temp*3.3)/1023;
			temparature=(temparature-0.05)/0.1;

        /* Determine status */

        if(water == 1)
        {
            status = ALERT;
        }
        else if(temperature > TEMP_THRESHOLD)
        {
            status = HOT;
        }
        else if(light< LDR_THRESHOLD)
        {
            status = DARK;
        }
        else if(soil < SOIL_THRESHOLD)
        {
            status = WATER;
        }
        else
        {
            status = SAFE;
        }

        /*  Control LEDs */
        switch(status)
    {
        case SAFE:
            // Green ON
				IOCLR0=1<<17;
            break;

        case HOT:
        case DARK:
        case WATER:
            // Yellow ON
				IOCLR0=1<<18;
            break;

        case ALERT:
            // Red ON
				IOCLR0=1<<19;
            break;
    }

		
		lcd_Cmd(0x01);

    lcd_String("TEMP:");
    // Display temperature
    lcd_float(temparature);
    lcd_Cmd(0xC0);
		switch(status)
    {
        case SAFE:
					lcd_string("STAUS : SAFE");
				 uart0_string_tx("---------------------------------\r\n");
							 uart0_string_tx("Temparature : ");
							 uart0_float(temparature);
							 uart0_string_t("C\r\n");
				uart0_string_tx("Light level : ");
				if(light< LDR_THRESHOLD)
					uart0_string_tx("NOT NORMAL");
				
				else
					uart0_string_tx("NORMAL");
				uart0_string_tx("Soil Moisture : ");
				uart0_int(soil);
				uart0_string_tx("%\r\n");
				uart0_string_tx("Water Sensor : ");
				if(water==1)
					uart0_string_tx("DETECTED\r\n");
				else
					uart0_string_tx("NOT DETECTED\r\n");
				uart0_string_tx("System Status : SAFE");
				uart0_string_tx("----------------------\r\n");
            break;

        case HOT:
					lcd_string("STAUS : HOT");
				lcd_string("STAUS : SAFE");
				 uart0_string_tx("---------------------------------\r\n");
							 uart0_string_tx("Temparature : ");
							 uart0_float(temparature);
							 uart0_string_t("C\r\n");
				uart0_string_tx("Light level : ");
				if(light< LDR_THRESHOLD)
					uart0_string_tx("NOT NORMAL");
				else
					uart0_string_tx("NORMAL");
				uart0_string_tx("Soil Moisture : ");
				uart0_int(soil);
				uart0_string_tx("%\r\n");
				uart0_string_tx("Water Sensor : ");
				if(water==1)
					uart0_string_tx("DETECTED\r\n");
				else
					uart0_string_tx("NOT DETECTED\r\n");
				uart0_string_tx("System Status : SAFE");
				uart0_string_tx("----------------------\r\n");
				break;
				
        case DARK:
					lcd_string("STAUS : DARK");
				lcd_string("STAUS : SAFE");
				 uart0_string_tx("---------------------------------\r\n");
							 uart0_string_tx("Temparature : ");
							 uart0_float(temparature);
							 uart0_string_t("C\r\n");
				uart0_string_tx("Light level : ");
				if(light< LDR_THRESHOLD)
					uart0_string_tx("NOT NORMAL");
				else
					uart0_string_tx("NORMAL");
				uart0_string_tx("Soil Moisture : ");
				uart0_int(soil);
				uart0_string_tx("%\r\n");
				uart0_string_tx("Water Sensor : ");
				if(water==1)
					uart0_string_tx("DETECTED\r\n");
				else
					uart0_string_tx("NOT DETECTED\r\n");
				uart0_string_tx("System Status : SAFE");
				uart0_string_tx("----------------------\r\n");
				break;
				
        case WATER:
            lcd_string("STAUS : WATER");
				lcd_string("STAUS : SAFE");
				 uart0_string_tx("---------------------------------\r\n");
							 uart0_string_tx("Temparature : ");
							 uart0_float(temparature);
							 uart0_string_t("C\r\n");
				uart0_string_tx("Light level : ");
				if(light< LDR_THRESHOLD)
					uart0_string_tx("NOT NORMAL");
				else
					uart0_string_tx("NORMAL");
				uart0_string_tx("Soil Moisture : ");
				uart0_int(soil);
				uart0_string_tx("%\r\n");
				uart0_string_tx("Water Sensor : ");
				if(water==1)
					uart0_string_tx("DETECTED\r\n");
				else
					uart0_string_tx("NOT DETECTED\r\n");
				uart0_string_tx("System Status : SAFE");
				uart0_string_tx("----------------------\r\n");
            break;

        case ALERT:
            lcd_string("STAUS : ALERT");
				lcd_string("STAUS : SAFE");
				 uart0_string_tx("---------------------------------\r\n");
							 uart0_string_tx("Temparature : ");
							 uart0_float(temparature);
							 uart0_string_t("C\r\n");
				uart0_string_tx("Light level : ");
				if(light< LDR_THRESHOLD)
					uart0_string_tx("NOT NORMAL");
				else
					uart0_string_tx("NORMAL");
				uart0_string_tx("Soil Moisture : ");
				uart0_int(soil);
				uart0_string_tx("%\r\n");
				uart0_string_tx("Water Sensor : ");
				if(water==1)
					uart0_string_tx("DETECTED\r\n");
				else
					uart0_string_tx("NOT DETECTED\r\n");
				uart0_string_tx("System Status : SAFE");
				uart0_string_tx("----------------------\r\n");
            break;
        /*  Display on LCD */
        LCD_Display(temperature,status);

        /* Display on UART */
        UART_Display(temperature,
                     light,
                     soil,
                     water,status);

        delay_ms(1000);
    }
}

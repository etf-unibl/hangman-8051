unsigned short keydata = 0, special = 0, down = 0;

///Define pin 1.0 as receiver for Soft UART.

sbit Soft_Uart_RX at P1_0_bit;

///Define pin 1.1 as transceiver for Soft UART

sbit Soft_Uart_TX at P1_1_bit;

/// PS2 module connections
sbit PS2_DATA  at P0_0_bit;
sbit PS2_CLOCK at P0_1_bit;

/// LCD pinout settings

sbit LCD_RS at P2_0_bit;
sbit LCD_EN at P2_1_bit;
sbit LCD_D7 at P2_5_bit;
sbit LCD_D6 at P2_4_bit;
sbit LCD_D5 at P2_3_bit;
sbit LCD_D4 at P2_2_bit;

char buffer[20];

/// Auxiliary variable for Soft UART initialization.

char error1

///Variable for moving of cursor on the LCD.

int i;

///Define which player is giving the task, and which player plays the game.

char player;

void main()
{
/// Initialize PS/2 Keyboard.
  Ps2_Config(); 

/// Wait for keyboard to finish.  
  Delay_ms(100);
  
  Soft_UART_Init(4800, 0);
  
/// Initialize SoftUART.
  Lcd_Init();
  while(1)
  {
    i=0;
    Ps2_Config();             
    Delay_ms(100);            

    error1=Soft_UART_Init(4800,0);
        
/// Player gets the information if he needs to guess or give the word.
    do                                      
      player = Soft_UART_Read(&error1);
    while (error1);

/// Clear LCD-a.
    Lcd_Cmd(_LCD_CLEAR);
        
/// In dependence of variable player on LCD is written which player gives the word. If there is some mistake, on LCD is shown error message.
    if(player == 0x01)
    {
      LCD_Out_CP("zadaje igrac A");
    }


    else if(player == 0x02)
    LCD_Out_CP("zadaje igrac B");

    else LCD_Out_CP("greska");
    
       memset(buffer,0,20);
       keydata=0;
       Ps2_Config();             
       Delay_ms(100);
            

///Word is issued only when on keyboard is pressed button "."

/// By pressing BACKSPACE button on the keyboard, last letter in the word is deleted.
       while(keydata!='.')
       {

           if (Ps2_Key_Read(&keydata, &special, &down))
           {
              if (down && (keydata == 16))
              {
               Soft_UART_Write(0x08);
               Lcd_Cmd(_LCD_MOVE_CURSOR_LEFT );
               i--;
              }

              else if (down && !special && keydata)
              {
                 if(keydata >= 97 && keydata <= 122 || keydata == 46 || keydata == 44)
                 Soft_UART_Write(keydata);
                 LCD_Chr(2,1+i,keydata);
                 i++;
               }

           }
        }
        memset(buffer,0,20);




 }
}
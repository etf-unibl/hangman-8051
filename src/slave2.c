#define ACK     0xac


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

/// Length of the given word.

char duzina;

/// Row in which is placed everything that comes over Soft Uart.

char buffer[20];

char error1;

char end;

int i;

/// Variable in which is placed integer value of the length.

int n;

char player;

void main()
{
  Ps2_Config();             
  Delay_ms(100);            
  Soft_UART_Init(4800, 0);
  Lcd_Init();
  j=0;


  while(1)
  {
    i=0;
    Ps2_Config();             
    Delay_ms(100);            

    error1=Soft_UART_Init(4800,0);

    do                                      
      player = Soft_UART_Read(&error1);
    while (error1);


    Lcd_Cmd(_LCD_CLEAR);
    if(player == 0x01)
    {
      LCD_Out_CP("igra igrac A");
    }
    
     else if(player == 0x02)
     LCD_Out_CP("Igra igrac B");
     
     else LCD_Out_CP("greska");
    
/// For writing underline (_) on the slaves LCD
      do                                         
        {
           duzina =Soft_Uart_Read(&error1);
        }
      while(error1);

        LCD_Out_CP("1");

/// Receive end character from master device.
      do
      {
        do                                      
           end=Soft_Uart_Read(&error1);
        while(error1);

        if (Ps2_Key_Read(&keydata, &special, &down))
        {
          if (down && !special && keydata)
            {

               if(keydata >= 97 && keydata <= 122 || keydata == 46)
                Soft_UART_Write(keydata);

               n=(int)duzina;
               for(i=0;i<(2*n);i++)
                 {
                   do
                   {
                    buffer[i] = Soft_Uart_Read(&error1);
                   }
                    while(error1);
                 }

                 buffer[i]='\0';
                 Lcd_Cmd(_LCD_CLEAR);
                 LCD_Out_CP(buffer);

                 
             }
        }
       }
       while(end==0x67);

/// Signifies end of game.
       if(end==0x55)
        {
          Lcd_Cmd(_LCD_CLEAR);
          LCD_Out_CP("kraj");
          delay_ms(100);
          i=0;
        }






 }
}
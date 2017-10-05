#include "Functions.h"

int k;
int j;
extern char lines[16];
extern char error1;

const code char pic2[1024];
const code char pic1[1024];
const code char pic3[1024];
const code char pic4[1024];
const code char pic5[1024];
const code char pic6[1024];
const code char pic7[1024];

/// Glcd module connections
char GLCD_DataPort at P0;
sbit GLCD_CS1 at P2_0_bit;
sbit GLCD_CS2 at P2_1_bit;
sbit GLCD_RS  at P2_2_bit;
sbit GLCD_RW  at P2_3_bit;
sbit GLCD_EN  at P2_4_bit;
sbit GLCD_RST at P2_5_bit;


sbit Soft_Uart_RX at P1_0_bit;
sbit Soft_Uart_TX at P1_1_bit;


void Init()
  {
/// Initialize Uart
    UART1_Init(4800);
/// Initialize Soft Uart        
    error1 =  Soft_UART_Init(4800, 0);
/// Initialize GLCD        
    Glcd_Init();                       
/// Clear GLCD        
    Glcd_Fill(0x00);                    
  }


void Write_lines(int lenght)
{
  Glcd_Init();
  
  /// Creates array of characters underline (_) on even and space ( ) on odd positions
    
  /// Number of positions is defined by the length of given word and it is double bigger from number of characters of that word
  for(k=0;k<lenght * 2;k++)
    {
      lines[k++] = '_';
      lines[k] = ' ';
    }
  
  /// Indicates the end of a row and creates a string (by '\0')
  
  lines[k] = '\0';
   
  /// Prints the resulting string on GLCD
  
  Glcd_Write_Text(lines, 2, 2, 1);
  delay_ms(2000);
}

void Is_there_this_character(char character,int lenght, char* text)
{
  UART1_Init(4800);
  
  ///Check if inserted character is presented in the given word
  
  /// If inserted character is presented in the given word, that letter is printed on the ordinal number (_) which fits ordinal number of hit letter
  for (j = 0; j < lenght; j++)
  {
      if (character == text[j]  || character == text[j]+32)
      {
       lines[2 * j] = character;
      }
  }
   
  /// Send previously changed string on auxiliary board which is connected to the main board over UART interface
  
  UART1_Write_Text(lines);

}

int End_of_game(char* lines,int lenght)
{
 ///Auxiliary variable for recognizing end of the game
 
 ///Assumption on the start is that game is over
 
 int end_bit=1;
 
 ///Checks if on even positions of the string there are underline (_)
 
 ///If on some of the even positions is in front of the underline (_) variable changes the value to 0 and game is not over.
 for(j=0;j<lenght;j++)
  {
   if(lines[2*j]=='_')
    {
      end_bit=0;
      j=lenght;
    }
  }

   return end_bit;
}

int Check_error(char* text, char character,int lenght)
{
 /// Variable for error detection. 
 int  error=1;
 
 ///Checks if letter which is inserted same as some of the letter in default word.
 
 /// If player guessed the letter error is 0.
 
 for (j = 0; j < lenght; j++)
  {
      if (character == text[j])
      error=0;

  }
  return error;
}


void Draw(int n)
{
   Glcd_Init();                        
   
   /// Clear GLCD
   Glcd_Fill(0x00);
    
   /// In dependence of inserted argument, the picture on the screen is drawn.
   
   /// Inserted argument fits number of remaining try for player which try to guess the word.
    
   ///Picture is assembled to get the hangman. It is drawn on GLCD of the main board.

   switch(n)
  {
     case 0 :
     Glcd_Image(pic7);
     break;

     case 1 :
     Glcd_Image(pic6);
     break;

     case 2 :
     Glcd_Image(pic5);
     break;

     case 3 :
     Glcd_Image(pic4);
     break;

     case 4 :
     Glcd_Image(pic3);
     break;
     
     case 5 :
     Glcd_Image(pic2);
     break;

     case 6 :
     Glcd_Image(pic1);
     break;
  }
  }
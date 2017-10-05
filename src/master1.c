#include "Functions.h"

/// Array for saving of inserted word.

char text[8];

///Array for saving everything that comes over Soft UART.

char buffer[8];

char lines[16];

/// Array for saving the result.

char x[4];

///Variable in which it can be found last inserted character which player is guessing in the moment.

char character;

/// Auxiliary variable for Soft UART initialization.

char error1;

///Number of attempts remain for guessing.

int  number_of_try;

///Length of the given word.

int  lenght;

/// Auxiliary variable which is used for loops.

int  i;

/// Defines which player gives the word, and which one is guessing.

int  number_of_game;

///Number of wins of the player B.

int  a;

///Number of wins of the player A.

int  c;

void main()
{
  Init();
  number_of_game=0;
  a=0;
  c=0;
  x[0]='0';
  x[1]=':';
  x[2]='0';
  x[3]='\0';
  while(1)
  {
            /// Function for empty the array before each new game.
            
        memset(text,0,8);
        memset(lines,0,8);
        memset(buffer,0,8);
        number_of_try=6;
        
        Glcd_Fill(0x00);
          
                /// In dependence of value of variable number_of_game, main board sends information who gives the word, and who guess the word.
        switch(number_of_game){
          case 0:
           
                  /// Player A gives the word, player B is guessing the word.
                  
                  Soft_UART_Write(0x01);
          delay_ms(100);
          UART1_Write(0x02);
          delay_ms(100);
          break;

          case 1:
                        
                  /// Player B gives the word, player A is guessing the word.
				  
          Soft_UART_Write(0x02);
          delay_ms(100);
          UART1_Write(0x01);
          delay_ms(100);
          break;
        }

                /// Receive characters over SOFT UART-a which inserts in array buffer.
                
        for(i=0;i<10;i++)
        {
           do
          {
             buffer[i] = Soft_Uart_Read(&error1);
          }
           while(error1);

                /// If BACKSPACE button is pressed, character that is received before is deleted from the buffer.
				
          if(buffer[i]==0x08)                
         {
          i-=2;
         }

        /// If character "." is received, algorithm stops insertion of characters into the buffer and defines length which fits current number of character in buffer.

         if(buffer[i]==0x2E)                
          {
            lenght=i;
            i=10;
          }

        }
                
                /// Coping received word from array into the text.
        for(i=0;i<lenght;i++)               
          {
           text[i]=buffer[i];
          }
         text[i]='\0';

         memset(buffer,0,8);                
                 
         Write_lines(lenght);               
         
                 /// Send length of word with UART-a module on the board which is used for guessing the word.
				 
         UART1_Write((char)lenght);
         delay_ms(10);


                
         while(number_of_try!=0 && !End_of_game(lines,lenght))
        {
                        
            /// Send information that game is not over yet.
			
         UART1_Write(0x67);
         delay_ms(10);
  
        /// Send character for guessing the letter. If the letter is correct, number of attempts is changed, otherwise  
        ///number of the attempts is decreased and on GLCD part by part of hangman is drawn
        /// In the same time, on GLCD current score (A:B) is written
		
          if(UART1_Data_Ready())
          {
            character = UART1_Read();

            Is_there_this_character(character,lenght,text);
            number_of_try -= Check_error(text,character,lenght);
            Draw(number_of_try);
            Glcd_Write_Text(x,110,6,1);
            Glcd_Write_Text("A B",110,5,1);
          }
        }

         UART1_Write(0x55);
         delay_ms(100);
          
                /// If game is over (number of atempts is different than 0), that means that player who guess the word won

         if(number_of_try!=0)
         {
            
                /// Player A has won, number of wins is increased by 1.
				
           if (number_of_game==1)
              {
                number_of_game=0;
                c++;
              }
        
                /// Player B has won, number of wins is increased by 1.
           else
               {
                number_of_game=1;
                a++;
               }

         }

                /// Number of attempts is 0, which means that player didn't guess any given word, player that was giving the word is winner
         else
           {
                
                /// Player B has won, number of wins is increased by 1.
                
             if (number_of_game==1)
                a++;
			
                /// Player A has won, number of wins is increased by 1.
				
             else
                c++;
           }
           
          Delay_ms(1000);
                  
                /// Converting number from type int into char.
				
           x[0]=c+'0';
           x[1]=':';
           x[2]=a+'0';
           x[3]='\0';
           
                ///Current score is drawn.
                
          Glcd_Write_Text(x,110,6,1);
          Glcd_Write_Text("A B",110,5,1);

         delay_ms(5000);
          


     }



}
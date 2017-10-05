/*/ \file functions.h
 *  Function prototyes for the game.
 *  All functions for playing the game(start game, end of game and game logic) is in this file.  
 *  Also, functions for drawing correct quessed letters and hangman are in this file.
 */
#ifndef _Functions_H_
#define _Functions_H_

/**
 * @brief Function draws underline(_) on GLCD.
 *
 *        This function needs to draw underline(_) on every place where is letter of given word.
 *
 * @param lenght Word lenght which needs to be drawn on GLCD.
 */
void Write_lines(int lenght);                                           
/**
 * @brief Function for letter check.
 *		  Inserted letter is compared with letters in given word, player which quess through UART interface sends word 
 *        which is assembled from correctly quessed letters. In place where letters are not quessed stays underline(_).
 *        When all letters are correct whole word is drawn on GLCD.
 *
 * @param character Letter which is inserted and checked in given word.
 * @param lenght    Given word lenght.
 * @param text      Word to quess. 
 * 		 
 */
void Is_there_this_character(char character,int lenght, char* text);   
/**
 * @brief Function for game end.
 *  	  Checks if all underline(_) are filled, ie. is number of tryes are reached.
 * @param crtice	Inserted letters     
 */
int End_of_game(char* crtice,int lenght);                               
/**
 * @brief Function that checks if letter is in given word.			
 *		  Letter which player insert is compared with letters in given word.
 *        According with that, number of remaining tryes is changed. If letter is correct, it is written on GLCD, if not
 *        then underline(_) stays while on GLCD part of hangman is drawn.
 * @param text      Word that is quessed .
 * @param character Letter that insert player which qusses word.
 * @param lenght    Given word lenght.
 */
int Check_error(char* text, char character,int lenght);                 
void Draw(int n);
/**
 * @brief Function for initialization of nedeed modules
 * 		  In this function UART1 interface, software UART and GLCD are initialized.
 *
 */
void Init();                                                       

#endif
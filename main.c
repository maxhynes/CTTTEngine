//COMP120 TicTacToe Project - Kayla (Max) Hynes - 03/25/24
// https://replit.com/@max295/TicTacToe#main.c

/*
Welcome to my feild programmable two-dimensional TTT game, witten in C.
While it is not perfect, I thought it would be interesting to exceed the project specifications to design arbitrary dimenions into the program, and build all of the functions accordingly. 

*/



#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Constants for TTT game board symbols. */
#define EMPTY ' '
#define USER 'X'
#define COMPUTER 'O'
const int x2max = 46340;

#define TRUE 1
#define FALSE 0



/* function prototypes

*/

// Game engine function protos'
  
void initializeStrings(int arrLength, char gameArr[]);
void renderTemplateBoard(int width, int height);
void renderBoardState(int width, int height, char gameArr[]);
void displayRows(int arrLength, char gameArr[]);
char isWinCondition(int width, int height, char gameArr[]);
int gameOver(char gameArr[], int addressMax);
int userMove(char gameArr[], int addressMax);
int aiMove(char gameArr[], int addressMax);

/* I/O functions*/
void displayHorizontalLine();
int getIntInputInRange(int min, int max);
int valueInRange(int value, int min, int max);
int getIntInput();

void clearInputStream();
int userSaysYes(char[]);
char getCharInput();






// Main Function

int main() {


  printf("Welcome to the Tic-Tac-Toe Game!\n\n\n");
  // Instantiate vars
  printf("Please specify number of rows: \n");
  // Get desired rows
  int rows = getIntInputInRange(1, x2max);
  printf("Please specify number of columns: \n");
  //Get desired columns
  int columns = getIntInputInRange(1, x2max);
  printf("\nBoard dimesnions sucessfully set! \n");
  // Calculate game memory alloc
  int addressMax = (rows * columns);
  //Allocate memory
  char gameArr[addressMax];
  char input = '\0';

  int gameState = 0;
  //Clear game array
  initializeStrings(addressMax, gameArr);
  //Render template board
  renderTemplateBoard(columns, rows);
  //Being main game loop
  while(1){
    //Get first turn
    printf("\nWould you like to go first? (Y/N): ");
    input = getCharInput();
    if(input == ('N') || input == ('n')) {
      aiMove(gameArr, addressMax);
      renderBoardState(columns, rows, gameArr);
    }
    //Begin in-play loop until win/draw
    while(1) {   
     renderTemplateBoard(columns, rows);  
     printf("Please choose a position on the board to place your mark.\n");
     userMove(gameArr, addressMax);
     renderBoardState(columns, rows, gameArr);
     if(isWinCondition(columns, rows, gameArr) == 'X'){
       printf("\nYou win!");
       break;
     }
     aiMove(gameArr, addressMax);
     printf("\nAI has moved");
     renderBoardState(columns, rows, gameArr);
     if(isWinCondition(columns, rows, gameArr) == 'O'){
       printf("\nAI wins!");
       break;
       }
     if(gameOver(gameArr, addressMax) == 0){
       printf("\nGame Over, nobody won! xD");
       break;
      }
    }
    //Kill game if finsihed
  printf("\nWould you like to play again? (Y/N): ");
    input = getCharInput();
    if(input == ('N') || input == ('n')) {
    break;
    }
  initializeStrings(addressMax, gameArr);
  } 
}

//Function Definitions:

//If all spaces taken, kill game
int gameOver(char gameArr[], int addressMax){
  int vacantSpaces = 0;
  
  for(int i = 0; i <= addressMax; i++){
    if(gameArr[i] == ' '){
      vacantSpaces++;
    }
  }
  if(vacantSpaces > 0){
    return 1;
  } 
    else {
      return 0;
    }
  
}

  //If game still vaid, permit user to move
int userMove(char gameArr[], int addressMax) { 
  while(gameOver(gameArr, addressMax) == 1) {
    int userPosition = getIntInputInRange(0, addressMax - 1);
    if (gameArr[userPosition] == EMPTY) {
      gameArr[userPosition] = USER;
      printf("You have successfully chosen position %d.\n", userPosition);
      return 1;
    }
    else {
      printf("That position is already taken. Please choose another position.\n");
      }
    }
  return(0);
  }
//Permit 
int aiMove(char gameArr[], int addressMax) {
  
  int computerPosition;

  while(gameOver(gameArr, addressMax) == 1) {
    computerPosition = rand() % addressMax;
    if (gameArr[computerPosition] == EMPTY) {
      gameArr[computerPosition] = COMPUTER;
      return 1;
      break;
    }
  }
}


void initializeStrings(int arrLength, char gameArr[]){
  for(int i = 0; i < arrLength; i++) {
    gameArr[i] = ' ';
  }
}


char getCharInput() {
  char input;
  input = getchar();
  while (input == '\n') {
    input = getchar();
  }
  return input;
}

int getIntInput() {
  int num;
  char term;

  while (scanf("%d%c", &num, &term) != 2 || term != '\n') {
    printf("\nImproper input. Please enter an integer: ");
    clearInputStream();
  }
  return num;
}

int valueInRange(int value, int min, int max) {
  /* Your code goes here */
  if (value >= min && value <= max) {
    return TRUE;
  } 
  else {
    return FALSE;
  }
}

//Get int from user and validate
int getIntInputInRange(int min, int max) {

  int i;
  printf("Please enter a value between %d and %d: ", min, max);
  
  while(1){
    i = getIntInput();
    if (valueInRange(i, min, max)) {
      return i; 
      break;
    }
    else {
      printf("Invalid input range! Please enter a value between %d and %d: ", min, max); 
    }
  }
}



// Detects if board is in a win state, and returns winner if true.
char isWinCondition(int width, int height, char gameArr[]) {
  int oCount = 0;
  int xCount = 0;
  //Check for horizontal wins
  for (int i = 0; i <= height; i++){
    // Re-Zero counters 
    oCount = 0;
    xCount = 0;
    //Generate Y-offset
    int yPos = i * width;
    
    for (int j = 0; j < width; j++){
      if(gameArr[(yPos + j)] == 'O') {
        oCount++;
        }
      if(gameArr[(yPos + j)] == 'X'){
        xCount++;
        }
      if (oCount == width) {
        printf("O Wins with a horizontal of %d Spaces!", oCount);
        return 'O';
      }
      if (xCount == width) {
        printf("X Wins with a horizontal of %d Spaces!", xCount);
        return 'X';
      } 
    }
  }

  // Check for vertical wins
  
    for (int i = 0; i <= width; i++){
      // Re-Zero counters 
      oCount = 0;
      xCount = 0;
      
      for (int j = 0; j < height; j++){
        if(gameArr[(i + (j*width))] == 'O') {
          oCount++;
          }
        if(gameArr[(i + (j*width))] == 'X') {
          xCount++;
          }
        
        if (oCount == height) {
          printf("O Wins with a vertical of %d Spaces!", oCount);
          return 'O';
          }
        if (xCount == height) {
          printf("X Wins with a vertical of %d Spaces!", xCount);
          return 'X';
      
        }
      }
    }
    
  // Check for diagonal wins
    // Check for right diagonal wins

  for (int i = 0; i <= (height - width); i++){
    // Re-Zero counters 
    oCount = 0;
    xCount = 0; 
    for (int j = 0; j < width; j++){
      //Generate y-offset
      int yPos = ((i * width) + (j * width + j));
        
        if(gameArr[yPos] == 'O') {
          oCount++;
          }
        if(gameArr[yPos] == 'X') {
          xCount++;
          }
        
        if (oCount == width) {
          printf("O Wins with a right diagonal of %d Spaces!", oCount);
          return 'O';
        }
        if (xCount == width) {
          printf("X Wins with a right diagonal of %d Spaces!", xCount);
          return 'X';
      }
    }
  }

  // Check for left diagonal wins.
    // Re-Zero counters 
  for (int i = 0; i <= (height - width); i++){
    // Re-Zero counters 
    oCount = 0;
    xCount = 0; 
    for (int j = 0; j < width; j++){
      //Generate y-offset
      int yPos = ((i * width) + ((j * width) + width - j - 1));

        if(gameArr[yPos] == 'O') {
          oCount++;
          }
        if(gameArr[yPos] == 'X') {
          xCount++;
          }

        if (oCount == width) {
          printf("O Wins with a left diagonal of %d Spaces!", oCount);
          return 'O';
        }
        if (xCount == width) {
          printf("X Wins with a left diagonal of %d Spaces!", xCount);
          return 'X';
      }
    }
  }

  return 0;
}
    
//It display's lines horizontally lol
void displayHorizontalLines(int width) {
  printf("\n");
  for(int i = 0; i < width; i++) {
    printf("------");
  }
  printf("\n");
}


// Renders gameboard from gameArr[] array to shell

void renderBoardState(int width, int height, char gameArr[]) {
  
  for (int i = 0; i < height; i++) {
    displayHorizontalLines(width);

    int offset = i * width;
    for (int z = 0; z < width; z++) {
      if (gameArr[offset + z] == ' ') {
        printf("     ");
      }
      else {
        printf("  %c  ", gameArr[offset + z]);
      }
      if (z < width - 1) 
      printf("|");
    }
  }
  displayHorizontalLines(width);
}

// Render address display board to shell

void renderTemplateBoard(int width, int height) {
  int address;
  for (int i = 0; i < height; i++) {
    displayHorizontalLines(width);
       for (int j = 0; j < width; j++) {
         address = (i * width + j);
         printf("  %d ", address);

        if (j < width - 1) {
          if(address < 10) {
              printf(" |");
            }
           else {
              printf("|");
            }
          }
        }
  }
  displayHorizontalLines(width);
}

//Clears input

void clearInputStream() {
  char input = getchar();
  while (input != '\n') {
    input = getchar();
  }
}
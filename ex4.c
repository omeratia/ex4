/******************
Name: Omer Atia
ID: 206667958
Assignment:
*******************/
#include <stdio.h>
#include <string.h>

#define ZERO 0
#define ADJUST_ONE 1
#define THREE 3
#define PYRAMID_SIZE 5
#define HALF_SPECIFIER 0.5000005
#define ASCII_SIZE 128
#define QUEEN_SIZE 20
#define WORD_SIZE 16
#define CROSSWORD_SIZE 30
#define SLOTS_SIZE 100

typedef struct Slot {
    int row; //row num
    int column; // col num
    char direction; // h or v
    int length; // length of slot
    int assignedWord; // will be initialzied as -1 and will be adjusted to a word index of the word that inhabits it
    }Slot;

typedef struct Word {
    char letters[WORD_SIZE + ADJUST_ONE]; //max size+ one more char for the /0
    int length;
    int index;
}Word;

void task1_robot_paths(int column, int row);
int robotRecursion(int column, int row);
void task2_human_pyramid(float weights[PYRAMID_SIZE][PYRAMID_SIZE], int pyramidSize);
float pyramidRecursion(float weights[PYRAMID_SIZE][PYRAMID_SIZE], int row, int column);
void task3_parenthesis_validator();
int termValidation();
int findClosing(char opener);
int isOpen(char c);
int isClosing(char c);
int pairChecker(char opener, char closer);
void task4_queens_battle();
void markQueen(int y, int x,
                int regions[ASCII_SIZE],
                int queenRows[QUEEN_SIZE],
                int queenColumns[QUEEN_SIZE],
                char regionsBoard[QUEEN_SIZE][QUEEN_SIZE],
                char queenBoard[QUEEN_SIZE][QUEEN_SIZE]);
void unmarkQueen(int y, int x,
                int regions[ASCII_SIZE],
                int queenRows[QUEEN_SIZE],
                int queenColumns[QUEEN_SIZE],
                char regionsBoard[QUEEN_SIZE][QUEEN_SIZE],
                char queenBoard[QUEEN_SIZE][QUEEN_SIZE]);
int check(int y, int x, 
                int queenRows[QUEEN_SIZE], 
                int queenColumns[QUEEN_SIZE],
                int regions[ASCII_SIZE],
                char regionsBoard[QUEEN_SIZE][QUEEN_SIZE],
                char queenBoard[QUEEN_SIZE][QUEEN_SIZE]);
int diagonalChecker(int y, int x, 
                char queenBoard[QUEEN_SIZE][QUEEN_SIZE]);
int queenRec(int y, int x, int regions[ASCII_SIZE], 
                int queenRows[QUEEN_SIZE],
                int queenColumns[QUEEN_SIZE],
                char regionsBoard[QUEEN_SIZE][QUEEN_SIZE],
                char queenBoard[QUEEN_SIZE][QUEEN_SIZE], 
                int boardSize);
//Case 5 functions:
void task5_crossword_generator();
int verticalCompare(Word word, Slot slot,
                    char crossword[CROSSWORD_SIZE][CROSSWORD_SIZE],int index,int row,int column);
int horizonCompare(Word word, Slot slot, 
                    char crossword[CROSSWORD_SIZE][CROSSWORD_SIZE],
                    int index,int row,int column);
int comparison(Word word, Slot slot,   
                    char crossword[CROSSWORD_SIZE][CROSSWORD_SIZE],int index);
int canWordFitSlot(Word word, Slot slot,   
                    int usedWords[SLOTS_SIZE],char crossword[CROSSWORD_SIZE][CROSSWORD_SIZE]);
void insertWordHorizon(Slot slot, Word word, 
                    char crossword[CROSSWORD_SIZE][CROSSWORD_SIZE],
                    int step,int row,int column, int usedWords[SLOTS_SIZE]);
void insertWordVert(Slot slot, Word word, 
                    char crossword[CROSSWORD_SIZE][CROSSWORD_SIZE],
                    int step,int row,int column, int usedWords[SLOTS_SIZE]);
void insertWord(Slot slots[SLOTS_SIZE], int slotIndex, Word word,
                    char crossword[CROSSWORD_SIZE][CROSSWORD_SIZE],int step,
                    int row,int column, int usedWords[SLOTS_SIZE]);
void removeWordVert(Slot slot, Word word,
                    char crossword[CROSSWORD_SIZE][CROSSWORD_SIZE],
                    int step,int row,int column, int usedWords[SLOTS_SIZE]);
void removeWordHorizon(Slot slot, Word word, 
                    char crossword[CROSSWORD_SIZE][CROSSWORD_SIZE],
                    int step,int row,int column, int usedWords[SLOTS_SIZE]);
void removeWord(Slot slots[SLOTS_SIZE],int slotIndex, Word word, 
                    char crossword[CROSSWORD_SIZE][CROSSWORD_SIZE],
                    int step,int row,int column, int usedWords[SLOTS_SIZE]);
int crosswordRec(Slot slots[SLOTS_SIZE],
                 Word words[SLOTS_SIZE], 
                    char crossword[CROSSWORD_SIZE][CROSSWORD_SIZE],
                    int usedWords[SLOTS_SIZE], 
                    int slotIndex, 
                    int wordIndex, 
                    int numOfSlots, 
                    int numOfWords);
void reinsertWords(Slot slots[SLOTS_SIZE],
                    Word words[SLOTS_SIZE], 
                    char crossword[CROSSWORD_SIZE][CROSSWORD_SIZE],
                    int usedWords[SLOTS_SIZE], 
                    int currentSlot,
                    int index);


int main()
{
    int task = -1;
    int robotCol, robotRow; //variables for inputs for first task
    float weights[PYRAMID_SIZE][PYRAMID_SIZE]; //2D array to keep our dancers weights

    do
    {
        printf("Choose an option:\n"
               "1. Robot Paths\n"
               "2. The Human Pyramid\n"
               "3. Parenthesis Validation\n"
               "4. Queens Battle\n"
               "5. Crossword Generator\n"
               "6. Exit\n");

        if (scanf("%d", &task))
        {
            switch (task)
            {
            case 6:
                printf("Goodbye!\n");
                break;
            case 1:
                printf("Please enter the coordinates of the robot (column, row):\n");
                scanf("%d %d", &robotCol, &robotRow);
                task1_robot_paths(robotCol, robotRow);
                break;
            case 2:
                task2_human_pyramid(weights, PYRAMID_SIZE);
                break;
            case 3:
                task3_parenthesis_validator();
                break;
            case 4:
                task4_queens_battle();
                break;
            case 5:
                task5_crossword_generator();
                break;
            default:
                printf("Please choose a task number from the list.\n");
                break;
            }
        }
        else
        {
            scanf("%*s");
        }

    } while (task != 6);
}

void task1_robot_paths(int column, int row){
    //in a condition our user inserted negative values, we shall return that the answer is 0 pathes
    if (column < ZERO || row < ZERO){
        printf("The total number of paths the robot can take to reach home is: 0\n");
        return;
    }
    //starting the location from the user's desired position
    int paths = robotRecursion(column, row);
    printf("The total number of paths the robot can take to reach home is: %d\n", paths);
};

int robotRecursion(int column, int row){
    //first stop condition: if we got an negative index, it means we reached an invlid postion, and we shall return 0 
    //as this is not a valid path through our room.
    if (row < ZERO || column < ZERO){
        return 0;
    }
    //if we reached the desired position, we shall return 1 as this is a valid path.
    else if (row == ZERO && column == ZERO){
        return 1;
    }
    //the recursion goes as follows: checking the paths from our current location in 2 different ways: 
    //either we are moving left (column-1) or either we are moving down (row-1)
    //the returned value is the number of valid paths from our current location 
    return robotRecursion(column-ADJUST_ONE, row) + robotRecursion (column, row-ADJUST_ONE); 
}
    


void task2_human_pyramid(float weights[PYRAMID_SIZE][PYRAMID_SIZE], int pyramidSize){
    printf("Please enter the weights of the cheerleaders:\n");
    //using loop to get inputs
    for (int i=0;i<pyramidSize;i++){
        for (int j=0; j<=i;j++){
            float weightInput;
            scanf("%f", &weightInput);
            if (weightInput<0){
                //breaking the task if the user entered negative weight
                printf("Negative weights are not supported.\n");
                return;
            }
            //adding each weight to our 2D array: at top (first row) we have the sole upper dancer,
            //and so go on each row has the number of her index as the number of dancers
            weights[i][j] = weightInput;
        }
    }
    printf("The total weight on each cheerleader is:\n");

    for (int i=0;i<pyramidSize;i++){
        //implementing the recurrsion to each dancer according to his position
        for (int j=0;j<=i;j++){
            float weightLoad = pyramidRecursion(weights, i, j);
            printf("%.2f ",weightLoad);
        }
        printf("\n");
    }
}

float pyramidRecursion(float weights[PYRAMID_SIZE][PYRAMID_SIZE], int row, int column){
    //our stop conditions as follow: either go out of bounds (to the negative size) or if the row is bigger 
    //than the column, which should never happen beacuse we moving up and to the left.
    if (row < 0 || column < 0 || row<column){
        return 0;
    }
    //each dancer would return its own weight and half of each of one of the dacner above her's weight. 
    //the recurrsion always check the dancer right above you and the dancer above and left to you.
    return weights[row][column] + 
            HALF_SPECIFIER*pyramidRecursion(weights, row-1, column-1) + 
            HALF_SPECIFIER*pyramidRecursion(weights, row-1,column);
}

void task3_parenthesis_validator()
{
    scanf("%*[^ \n]");
    scanf("%*c");
    printf("Please enter a term for validation:\n");
    //recieving input until enter is being pressed
    scanf("[^\n]");
    if (termValidation()){
        printf("The parentheses are balanced correctly.\n");
    }
    else {
        printf("The parentheses are not balanced correctly.\n");
        
    }
}

int termValidation(){
    //each time getting the current latest character from the term, from the buffer
    char c;
    scanf("%c",&c);
    //if we got a new line, it means the term is balanced, because in this function we are not meant to meet a closer
    if (c == '\n'){
        return 1;
    }
    //if the lastest character is an opener, we need to close it (find closing) and keep working on the term
    //(termValidation)
    if (isOpen(c)){
        return findClosing(c) && termValidation();
    }
    //if its a closer we are sending 0, because according to our code logic we are not suppose to find closers here,
    //only openers
    if (isClosing(c)){
        scanf("%*[^ \n]");
        return 0;
    }
    //if we got here it means none of the stop conditions was applied, so we need to go on looking for openers 
    return termValidation();
    
};

int findClosing(char opener){
    //this function handles finding a closer to a specific opener it recieved, or it meet another opener and then 
    //trigger itself in recursion to find a closer to him first 
    char c1;
    scanf("%c",&c1);
    //if we meet a new line it means we didnt closed a opener, so the term failed
    if (c1 == '\n'){
        return 0;
    }
    //if we found closing ,we are triggering function to compare opener to a closer (pairChecker)
    else if (isClosing(c1)){
        return pairChecker(opener, c1);
    }
    //if its an opener we must close it first now, so we applying another recursion of this function
    else if (isOpen(c1)){
        return findClosing(c1) && findClosing(opener);
    }
    return findClosing(opener);
}

int isOpen(char c){
    //basic function to determine if a character is a closer
    if (c == '{' || c == '(' || c == '[' || c == '<'){
        return 1;
    }
    else return 0;
}
int isClosing(char c){
    //basic function to determine if a character is a closer
    if (c == '}' || c == ')' || c == ']' || c == '>'){
        return 1;
    }
    else return 0;
}
int pairChecker(char opener, char closer){
    //recieves two char, and check if they match each other
    if (opener == '(' && closer == ')'){
        return 1;
    }
    else if (opener == '{' && closer == '}'){
        return 1;
    }
    else if (opener == '[' && closer == ']'){
        return 1;
    }
    else if (opener == '<' && closer == '>'){
        return 1;
    }
    else {
        return 0;}
}

void task4_queens_battle(){
    int regions[ASCII_SIZE]={0}; //regions are char, so we are using an int array the size of all possible asci
    //values to inidcate which region is taken. we will use the decimal value of a char as the index of our array.
    int queenRows[QUEEN_SIZE] = {0}; //array to keep track of what rows are taken
    int queenColumns[QUEEN_SIZE]={0}; //array to keep track of what column is taken
    char regionsBoard[QUEEN_SIZE][QUEEN_SIZE]; //the board to represnts the regions as taken from the user
    char queenBoard[QUEEN_SIZE][QUEEN_SIZE]; //our board to represent queen and *
    int boardSize;
    printf("Please enter the board dimensions:\n");
    scanf("%d", &boardSize); //user input for dimensions
    printf("Please enter a %d*%d puzzle board:\n", boardSize, boardSize);
    //initiating the regions board from the users input
    for (int i=0;i<boardSize;i++){
        for (int j=0; j<boardSize;j++){
            scanf(" %c", &regionsBoard[i][j]);
        }
    }
    //initiating the recursion here, the returned value (1 or 0) will determine the output
    if (queenRec(0,0,regions,queenRows,queenColumns,regionsBoard,queenBoard,boardSize)){
        printf("Solution:\n");
        for (int i=0; i<boardSize;i++){
            for (int j=0; j<boardSize;j++){
               //printing according our array and according to queen positions
                if (queenBoard[i][j] != 'X'){
                    printf("* ");
                    continue;
                }
                printf("%c ", queenBoard[i][j]);
                
            }
            printf("\n");
        };
    }
    else {
        printf("This puzzle cannot be solved.\n");
    }

    

}



int check(int y, int x, int queenRows[QUEEN_SIZE], 
                        int queenColumns[QUEEN_SIZE],
                        int regions[ASCII_SIZE],
                        char regionsBoard[QUEEN_SIZE][QUEEN_SIZE],
                        char queenBoard[QUEEN_SIZE][QUEEN_SIZE]){
    //our main checking function. it deploying check to see the row,column and region isnt taken yet.
    //also deplyoing the diagonal checker function to check the close-diagonals of the position given.
    //returns 1 if all checks went good.
    int currentRegion = (int)regionsBoard[y][x];
    return (!queenRows[y] && !queenColumns[x] && !regions[currentRegion] 
    && diagonalChecker(y,x,queenBoard));
}


int diagonalChecker(int y, int x,char queenBoard[QUEEN_SIZE][QUEEN_SIZE]){
    //test case for position (0,0) which only has one diagonal in the grid (others are out of bounds)
    if (y==0 && x==0){
        return !(queenBoard[y][x] == 'X');
    }
    //if our column is 0 we only have two specific diagonals
    else if (x==0){
        return !(queenBoard[y+1][x-1]=='X' || queenBoard[y+1][x+1]=='X');
    }
    //if our row is 0 we only have 2 specific diagonals to check
    else if (y==0){
        return !(queenBoard[y+1][x-1]=='X' || queenBoard[y+1][x+1]=='X');
    }
    //if we got here it means our position have 4 diagonals to check
    else {
        return !(queenBoard[y-1][x+1]=='X' || 
        queenBoard[y+1][x+1]=='X' || 
        queenBoard[y-1][x-1]=='X' || 
        queenBoard[y+1][x-1]=='X');
    }
}

void markQueen(int y, int x,
                int regions[ASCII_SIZE],
                int queenRows[QUEEN_SIZE],
                int queenColumns[QUEEN_SIZE],
                char regionsBoard[QUEEN_SIZE][QUEEN_SIZE],
                char queenBoard[QUEEN_SIZE][QUEEN_SIZE]){

                    //function to mark the position of a queen on the grid.
                    //also marking the row and column as taken, and the region being taken(in the ascii regions array)
                    queenColumns[x] = 1;
                    queenRows[y] = 1;
                    //getting the region symbol
                    int currentRegion = (int)regionsBoard[y][x];
                    regions[currentRegion] = 1;
                    //marking the queen
                    queenBoard[y][x] = 'X';
};

void unmarkQueen(int y, int x,
                int regions[ASCII_SIZE],
                int queenRows[QUEEN_SIZE],
                int queenColumns[QUEEN_SIZE],
                char regionsBoard[QUEEN_SIZE][QUEEN_SIZE],
                char queenBoard[QUEEN_SIZE][QUEEN_SIZE]){

                    //reverse version of marking queen
                    //making the rows and columns free, also the region being free again.
                    //om the grid, replacing the queen with an *
                    queenColumns[x] = 0;
                    queenRows[y] = 0;
                    int currentRegion = (int)regionsBoard[y][x];
                    regions[currentRegion] = 0;
                    queenBoard[y][x] = '*';
                }

int queenRec(int y, int x, int regions[ASCII_SIZE], int queenRows[QUEEN_SIZE],int queenColumns[QUEEN_SIZE],
                char regionsBoard[QUEEN_SIZE][QUEEN_SIZE],char queenBoard[QUEEN_SIZE][QUEEN_SIZE], int boardSize){
            //stop conidtion number one: any grid in size 3 or below won't have a sulotion(not possinble
            //with the diagonals)
            if (boardSize<=THREE){
                return 0;
            }
            //stop condition number two: if we got over the board size by rows (because we are moving vertically),
            //it means we put a queen in each row, hence we completed the board with valid queen positions
            if (y == boardSize && queenRows[y-1]){
                return 1;
            }
            //stop condition number three: if we got out of bounds horizonally, it means we tried putting queen in 
            //every tile in the row, which means we can positon a queen in this row and we need to backtrack 
            else if (x == boardSize){
                return 0;
            }

            //starting the recursion- if the check for a free position was good, we are putting a queen there.
            if (check(y,x,queenRows,queenColumns,regions,regionsBoard,queenBoard)){
                markQueen(y,x,regions,queenRows,queenColumns,regionsBoard,queenBoard);
                //sub-level of our recursion, we triggered the recursion for trying in the next row (y+1),
                //and for every completion of a row it will trigger another recursion down the rows, 
                //and so go on until either we completed the puzzle or we ger returned 0
                if (!(queenRec(y+ADJUST_ONE,0,regions,queenRows,queenColumns,regionsBoard,queenBoard,boardSize))){
                    //if we got a 0 from the sub-recursion, we need to unamrk the current queen, and return the 
                    //value of trying putting a queen in this row but one position ahead horizonally
                    unmarkQueen(y,x,regions,queenRows,queenColumns,regionsBoard,queenBoard);
                    return queenRec(y,x+ADJUST_ONE,regions,queenRows,queenColumns,regionsBoard,queenBoard,boardSize);
                }
            }
            
            //if we got here, it meant the initial check wasnt good, and we need to try other postions in the row
            //so are moving foraward horizonally (x+1)
            else {
                return queenRec(y,x+ADJUST_ONE,regions, queenRows, queenColumns, regionsBoard, queenBoard, boardSize);
    };
    return 1;
                    
}
void task5_crossword_generator(){
    char crossword[CROSSWORD_SIZE][CROSSWORD_SIZE]={0}; //grid for the game
    Slot slots[SLOTS_SIZE]; //an array of slots, to handle efficiently with all the data each slot holds
    Word words[SLOTS_SIZE]; //an array of words to hold data for the words we recieve from the user
    int usedWords[SLOTS_SIZE] = {0}; //thisa rray will help us indicate whereas a word is already being used
    //so we wont place it again on the grid
    int gridSize, numOfSlots, numOfWords;
    printf("Please enter the dimensions of the crossword grid:\n");
    //recieving inputs from the user
    scanf("%d",&gridSize);
    printf("Please enter the number of slots in the crossword:\n");
    scanf("%d",&numOfSlots);
    printf("Please enter the details for each slot (Row, Column, Length, Direction):\n");
    //each of the slots we recieved enters to the slots array 
    for (int i=0; i<numOfSlots;i++){
        int row,column,length;
        char direction;
        scanf(" %d %d %d %c", &row, &column, &length, &direction);
        slots[i].row = row;
        slots[i].column = column;
        slots[i].length = length;
        slots[i].direction = direction;
        slots[i].assignedWord = -1; //starts at negative, will be changed to the index of the word that inhabits it
    };
    printf("Please enter the number of words in the dictionary:\n");
    scanf("%d",&numOfWords);
    //making sure we are not getting illegal number of words 
    while (numOfWords<numOfSlots){
        printf("The dictionary must contain at least %d words. Please enter a valid dictionary size:\n", numOfSlots);
        scanf("%d",&numOfWords);
    };
    printf("Please enter the words for the dictionary:\n");
    //each word from the user input enters to the words array
    for (int i=0;i<numOfWords;i++){
        char word[WORD_SIZE];
        scanf("%s",word);
        words[i].index = i;
        int length = strlen(word); //keeping the length so we can understand if a word can enter
        //to a specific slot
        words[i].length = length;
        strcpy(words[i].letters, word);
    };

    if (crosswordRec(slots,words,crossword,usedWords,0,0,numOfSlots,numOfWords)){
        //if we got a solution to the crossword, we are printing the grid
        for (int i=0;i<gridSize;i++){
            printf("| ");
            for (int j=0; j<gridSize;j++){
                if (crossword[i][j] == '\0'){
                    printf("# ");
                }
                else {
                    printf("%c ",crossword[i][j]);
                }
                printf("| ");
            }
            printf("\n");
        }
    }
    else {
        printf("This crossword cannot be solved.\n");
    }

}

int crosswordRec(Slot slots[SLOTS_SIZE],
                 Word words[SLOTS_SIZE], 
                 char crossword[CROSSWORD_SIZE][CROSSWORD_SIZE],
                 int usedWords[SLOTS_SIZE], 
                 int slotIndex, 
                 int wordIndex, 
                 int numOfSlots, 
                 int numOfWords) 
{
    //first stop condition: if we inhabited all slots with word so we got to the number of total slots
    //it means success and we can return 1
    if (slotIndex == numOfSlots) {
        return 1;
        
    };
    //second stop condition: if we tried all words for a slot and didnt get a match, we must return a failure
    if (wordIndex >= numOfWords) {//
        return 0;
        
    };

    //starting the recursion: if our current word can fit to our current slot, we are inserting the word and marking
    //all needed markings
    if (canWordFitSlot(words[wordIndex], slots[slotIndex], usedWords, crossword)) {
        
        insertWord(slots,
                    slotIndex, 
                   words[wordIndex],
                   crossword, 
                   0, 
                   slots[slotIndex].row, 
                   slots[slotIndex].column, 
                   usedWords);
        //sub-recursion : trying the next slot. it will also trigger sub-recursions until we will get to the last slot
        //(or it will fail before and return 0)
        //if it succseed it means we can return 1 as all of the slots under this current slot have found 
        //their match
        if (crosswordRec(slots, words, crossword, usedWords, slotIndex + ADJUST_ONE, 0, numOfSlots, numOfWords)) {
            return 1;
        
    } 
        //if we got here it means we marked a word in a slot, but all other sub-recursions followed by
        //this specific combination didnt work, so we need to remove the current word.
        //also, we are using the reinsertWords function that reinserts again all words until before the
        //current slot to their slot, so if this removal of word will affect mutual letters, our grid won't
        //be affected
        removeWord(slots,slotIndex, words[wordIndex], crossword, 0,
                   slots[slotIndex].row, slots[slotIndex].column, usedWords);
        reinsertWords(slots,words,crossword,usedWords,slotIndex,0);
    }
    
    //if we got here it means the sub-recursions didnt work and we need to try this current slot with the next word
    return crosswordRec(slots, words, crossword, usedWords, slotIndex, wordIndex + ADJUST_ONE, numOfSlots, numOfWords);

    
};

int canWordFitSlot(Word word, Slot slot, int usedWords[SLOTS_SIZE],char crossword[CROSSWORD_SIZE][CROSSWORD_SIZE]){
    //if this specific word is already taken we cut the loop  
    if (usedWords[word.index]){
        return 0;
    }
    //if the lengths are not matching we are cutting the loop
    else if (slot.length != word.length){
        return 0;
    }
    //checking if we already have letters in the slot and that they are matching our current word
    else if (!comparison(word,slot,crossword,0)){
        return 0;
    }
    return 1;
}

int comparison(Word word, Slot slot, char crossword[CROSSWORD_SIZE][CROSSWORD_SIZE],int index){
    //this function redirectes to the right comparison function, depends on the direction of the slot 
    int row = slot.row;
    int column = slot.column;
    if (slot.direction == 'H'){
        return horizonCompare(word, slot, crossword, index,row,column);
    };
    return verticalCompare(word,slot,crossword,index,row, column);
};

int horizonCompare(Word word, Slot slot, char crossword[CROSSWORD_SIZE][CROSSWORD_SIZE],int index,int row,int column){
    //if the index aka the steps we checked got over the word length it means we checked all the
    //char slots for the word and they available or matching it
    if (index>word.length){
        return 1;
    };
    //if we have a 0 in the frid it means the space is available and we shall move on to the next chat slot,
    //moving by column becuase this is horizontal
    if (crossword[row][column]== '\0'){
        return horizonCompare(word, slot, crossword, index+ADJUST_ONE, row, column+ADJUST_ONE);
    };
    //if we got here it means there is a letter in the slot, and we need to check that it matches the current index
    //letter in our word
    if (crossword[row][column] != word.letters[index]){
        return 0;
    };
    return 1;
};

int verticalCompare(Word word, Slot slot, 
                    char crossword[CROSSWORD_SIZE][CROSSWORD_SIZE],int index,int row,int column){
    //if the index aka the steps we checked got over the word length it means we checked all the
    //char slots for the word and they available or matching it
    if (index>word.length){
        return 1;
    };
    //if we have a 0 in the frid it means the space is available and we shall move on to the next chat slot,
    //moving by row becuase this is vertical
    if (crossword[row][column]== '\0'){
        return verticalCompare(word, slot, crossword, index+ADJUST_ONE, row+ADJUST_ONE, column);
    };
    //if we got here it means there is a letter in the slot, and we need to check that it matches the current index
    //letter in our word
    if (crossword[row][column] != word.letters[index]){
        return 0;
    };
    return 1;
};

void reinsertWords(Slot slots[SLOTS_SIZE],
                 Word words[SLOTS_SIZE], 
                 char crossword[CROSSWORD_SIZE][CROSSWORD_SIZE],
                 int usedWords[SLOTS_SIZE], 
                 int currentSlot,
                 int index){
    //stop condition- if we got to the slot we were supposed to reinsert until before it, we must stop
    if (index>=currentSlot){
        return;
    };
    //if the current slot have a value of a word's index in the assignedWord attribute, it means it have
    //an attached word and we need to reinsert it
    if (slots[index].assignedWord>=ZERO){
        //getting the word object safely 
        Word assignedWord = words[slots[index].assignedWord];
        //inserting the word (again) to it slot
        insertWord(slots,index, assignedWord,crossword,ZERO,slots[index].row,slots[index].column,usedWords);
        
    };
    //keeping the recursion to the next slot
    reinsertWords(slots,words,crossword,usedWords,currentSlot,index+ADJUST_ONE);
};

void insertWord(Slot slots[SLOTS_SIZE],int slotIndex, Word word, 
                char crossword[CROSSWORD_SIZE][CROSSWORD_SIZE],
                int step,int row,int column, int usedWords[SLOTS_SIZE]){
    //function to redirect to the right inserting function depends on the direction of the slot
    if (slots[slotIndex].direction == 'H'){
        insertWordHorizon(slots[slotIndex],word,crossword,step,row,column,usedWords);
    }
    else {
        insertWordVert(slots[slotIndex], word, crossword, step, row, column, usedWords);
    }
    usedWords[word.index] = 1;
    slots[slotIndex].assignedWord= word.index;
};

void insertWordVert(Slot slot, Word word, char crossword[CROSSWORD_SIZE][CROSSWORD_SIZE],
                    int step,int row,int column, int usedWords[SLOTS_SIZE]){
    //if we did number of steps as the length of the word, it means we inserted all letters to the slot and we can
    //end the function. also we will insert 1 in the usedWords array so we will know this word is taken,
    //and add the index of the word to its matching slot
    if (step == word.length){
        usedWords[word.index] =1;
        return;
    }
    //inserting our letter to the slot
    crossword[row][column] = word.letters[step];
    //moving the recurssion to next word, vertically
    insertWordVert(slot,word,crossword,step+ADJUST_ONE,row+ADJUST_ONE,column,usedWords);
};

void insertWordHorizon(Slot slot, Word word, char crossword[CROSSWORD_SIZE][CROSSWORD_SIZE],
                        int step,int row,int column, int usedWords[SLOTS_SIZE]){
    //if we did number of steps as the length of the word, it means we inserted all letters to the slot and we can
    //end the function. also we will insert 1 in the usedWords array so we will know this word is taken
    if (step == word.length){
        usedWords[word.index] =1;
        slot.assignedWord = word.index;
        return;
    }
    //inserting our letter to the slot
    crossword[row][column] = word.letters[step];
    //moving the recurssion to next word, vertically, incrementing our step count
    insertWordHorizon(slot,word,crossword,step+ADJUST_ONE,row,column+ADJUST_ONE,usedWords);
};

void removeWord(Slot slots[SLOTS_SIZE], int slotIndex, Word word,
                char crossword[CROSSWORD_SIZE][CROSSWORD_SIZE],
                int step,int row,int column, int usedWords[SLOTS_SIZE]){
    //function to redirect to the right removing function depends on the direction of the slot
    if (slots[slotIndex].direction == 'H'){
        removeWordHorizon(slots[slotIndex],word,crossword,step,row,column,usedWords);
    }
     else {
        removeWordVert(slots[slotIndex], word, crossword, step, row, column, usedWords);
    }

    
    usedWords[word.index] = 0;
    slots[slotIndex].assignedWord = -1;

    
}

void removeWordHorizon(Slot slot, Word word, char crossword[CROSSWORD_SIZE][CROSSWORD_SIZE],
                        int step,int row,int column, int usedWords[SLOTS_SIZE]){
    //if we did number of steps as the length of the word, it means we removed all letters from the slot and we can
    //end the function. also we will insert 0 in the usedWords array so we will know this word is not taken anymore,
    //and return the value of assigned word to be -1 as its not attached to this slot anymore
    if (step == word.length){
        usedWords[word.index] =0;
        slot.assignedWord = -1;
        return;
    }
    //returning to default value
    crossword[row][column] = '\0';
    //next stop in the recurrsion moving forward horizonally
    removeWordHorizon(slot,word,crossword,step+ADJUST_ONE,row,column+ADJUST_ONE,usedWords);
};

void removeWordVert(Slot slot, Word word, char crossword[CROSSWORD_SIZE][CROSSWORD_SIZE],
                    int step,int row,int column, int usedWords[SLOTS_SIZE]){
    //if we did number of steps as the length of the word, it means we removed all letters from the slot and we can
    //end the function. also we will insert 0 in the usedWords array so we will know this word is not taken anymore
    //and return the value of assigned word to be -1 as its not attached to this slot anymore
    if (step == word.length){
        usedWords[word.index] =0;
        slot.assignedWord = -1;
        return;
    }
    //returning to default value
    crossword[row][column] = '\0';
    //next step at the recurrsion moving down the rows vertically
    removeWordVert(slot,word,crossword,step+ADJUST_ONE,row+ADJUST_ONE,column,usedWords);
};






/******************
Name: Omer Atia
ID: 206667958
Assignment:
*******************/
#include <stdio.h>
#include <string.h>

#define ZERO 0
#define ADJUST_ONE 1
#define PYRAMID_SIZE 5
#define ASCII_SIZE 128
#define QUEEN_SIZE 20
#define WORD_SIZE 15
#define CROSSWORD_SIZE 30
#define SLOTS_SIZE 100

typedef struct Slot {
    int row; //row num
    int column; // col num
    char direction; // h or v
    int length; // length of slot
    int assignedWord; // will be initialzied as -1 and will be adjusted to a word index of the word that inhabits him
    }Slot;

typedef struct Word {
    char letters[QUEEN_SIZE + ADJUST_ONE]; //max size+ one more char for the /0
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
                int queenRows[QUEEN_SIZE], 
                int queenColumns[QUEEN_SIZE],
                char queenBoard[QUEEN_SIZE][QUEEN_SIZE]);
int queenRec(int y, int x, int regions[ASCII_SIZE], 
                int queenRows[QUEEN_SIZE],
                int queenColumns[QUEEN_SIZE],
                char regionsBoard[QUEEN_SIZE][QUEEN_SIZE],
                char queenBoard[QUEEN_SIZE][QUEEN_SIZE], 
                int boardSize);
//Case 5 functions:
void task5_crossword_generator();
int verticalCompare(Word word, Slot slot, char crossword[CROSSWORD_SIZE][CROSSWORD_SIZE],int index,int row,int column);
int horizonCompare(Word word, Slot slot, char crossword[CROSSWORD_SIZE][CROSSWORD_SIZE],int index,int row,int column);
int comparison(Word word, Slot slot, char crossword[CROSSWORD_SIZE][CROSSWORD_SIZE],int index);
int canWordFitSlot(Word word, Slot slot, int usedWords[SLOTS_SIZE],char crossword[CROSSWORD_SIZE][CROSSWORD_SIZE]);
void insertWordHorizon(Slot slot, Word word, char crossword[CROSSWORD_SIZE][CROSSWORD_SIZE],int step,int row,int column, int usedWords[SLOTS_SIZE]);
void insertWordVert(Slot slot, Word word, char crossword[CROSSWORD_SIZE][CROSSWORD_SIZE],int step,int row,int column, int usedWords[SLOTS_SIZE]);
void insertWord(Slot slot, Word word, char crossword[CROSSWORD_SIZE][CROSSWORD_SIZE],int step,int row,int column, int usedWords[SLOTS_SIZE]);
void removeWordVert(Slot slot, Word word, char crossword[CROSSWORD_SIZE][CROSSWORD_SIZE],int step,int row,int column, int usedWords[SLOTS_SIZE]);
void removeWordHorizon(Slot slot, Word word, char crossword[CROSSWORD_SIZE][CROSSWORD_SIZE],int step,int row,int column, int usedWords[SLOTS_SIZE]);
void removeWord(Slot slot, Word word, char crossword[CROSSWORD_SIZE][CROSSWORD_SIZE],int step,int row,int column, int usedWords[SLOTS_SIZE]);
int crosswordRec(Slot slots[SLOTS_SIZE],
                 Word words[SLOTS_SIZE], 
                 char crossword[CROSSWORD_SIZE][CROSSWORD_SIZE],
                 int usedWords[SLOTS_SIZE], 
                 int slotIndex, 
                 int wordIndex, 
                 int numOfSlots, 
                 int numOfWords);


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
                // scanf("%*[^\n]");
                break;
            case 4:
                {
                task4_queens_battle();}
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
            0.5000005*pyramidRecursion(weights, row-1, column-1) + 0.5000005*pyramidRecursion(weights, row-1,column);
}

void task3_parenthesis_validator()
{
    scanf("%*[^\n]");
    scanf("%*c");
    printf("Please enter a term for validation:\n");
    scanf("[^\n]");
    if (termValidation()){
        printf("The parentheses are balanced correctly.\n");
    }
    else {
        
        printf("The parentheses are not balanced correctly\n");
        
    }
}

int termValidation(){
    char c;
    scanf("%c",&c);
    if (c == '\n'){
        return 1;
    }
    if (isOpen(c)){
        return findClosing(c) && termValidation();
    }
    if (isClosing(c)){
        // scanf("%*[^\n]");
        return 0;
    }
    return termValidation();
    
};

int findClosing(char opener){
    char c1;
    scanf("%c",&c1);
    if (c1 == '\n'){
        return 0;
    }
    else if (isClosing(c1)){
        return pairChecker(opener, c1);
    }
    else if (isOpen(c1)){
        return findClosing(c1) && findClosing(opener);
    }
    return findClosing(opener);
}

int isOpen(char c){
    if (c == '{' || c == '(' || c == '[' || c == '<'){
        return 1;
    }
    else return 0;
}
int isClosing(char c){
    if (c == '}' || c == ')' || c == ']' || c == '>'){
        return 1;
    }
    else return 0;
}
int pairChecker(char opener, char closer){
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
    int regions[ASCII_SIZE]={0};
    int queenRows[QUEEN_SIZE] = {0};
    int queenColumns[QUEEN_SIZE]={0};
    char regionsBoard[QUEEN_SIZE][QUEEN_SIZE];
    char queenBoard[QUEEN_SIZE][QUEEN_SIZE];
    int boardSize;
    printf("Please enter the board dimensions:\n");
    scanf("%d", &boardSize);
    printf("Please enter the %d*%d puzzle board\n", boardSize, boardSize);
    for (int i=0;i<boardSize;i++){
        for (int j=0; j<boardSize;j++){
            scanf(" %c", &regionsBoard[i][j]);
        }
    }

    if (queenRec(0,0,regions,queenRows,queenColumns,regionsBoard,queenBoard,boardSize)){
        printf("success for the queens\n");
        for (int i=0; i<boardSize;i++){
            for (int j=0; j<boardSize;j++){
                if (queenBoard[i][j] != 'X'){
                    printf("*");
                    continue;
                }
                printf("%c", queenBoard[i][j]);
            }
            printf("\n");
        };
    }
    else {
        printf("no success\n");
    }

    

}



int check(int y, int x, int queenRows[QUEEN_SIZE], int queenColumns[QUEEN_SIZE],int regions[ASCII_SIZE],char regionsBoard[QUEEN_SIZE][QUEEN_SIZE],char queenBoard[QUEEN_SIZE][QUEEN_SIZE]){
    char currentRegion = regionsBoard[y][x];
    return (!queenRows[y] && !queenColumns[x] && !regions[currentRegion] && diagonalChecker(y,x,queenRows,queenColumns,queenBoard));
}


int diagonalChecker(int y, int x, int queenRows[QUEEN_SIZE], int queenColumns[QUEEN_SIZE],char queenBoard[QUEEN_SIZE][QUEEN_SIZE]){
    //1 if not free
    if (y==0 && x==0){
        return !(queenBoard[y][x] == 'X');
    }
    else if (x==0){
        return !(queenBoard[y+1][x-1]=='X' || queenBoard[y+1][x+1]=='X');
    }
    else if (y==0){
        return !(queenBoard[y-1][x+1]=='X' || queenBoard[y+1][x+1]=='X');
    }
    else {
        return !(queenBoard[y-1][x+1]=='X' || queenBoard[y+1][x+1]=='X' || queenBoard[y-1][x-1]=='X' || queenBoard[y+1][x-1]=='X');
    }
}

void markQueen(int y, int x,
                int regions[ASCII_SIZE],
                int queenRows[QUEEN_SIZE],
                int queenColumns[QUEEN_SIZE],
                char regionsBoard[QUEEN_SIZE][QUEEN_SIZE],
                char queenBoard[QUEEN_SIZE][QUEEN_SIZE]){

                    queenColumns[x] = 1;
                    queenRows[y] = 1;
                    char currentRegion = regionsBoard[y][x];
                    regions[currentRegion] = 1;
                    queenBoard[y][x] = 'X';
                    printf("marking queen at %d,%d on region %c\n", y,x,currentRegion);
};

void unmarkQueen(int y, int x,
                int regions[ASCII_SIZE],
                int queenRows[QUEEN_SIZE],
                int queenColumns[QUEEN_SIZE],
                char regionsBoard[QUEEN_SIZE][QUEEN_SIZE],
                char queenBoard[QUEEN_SIZE][QUEEN_SIZE]){

                    queenColumns[x] = 0;
                    queenRows[y] = 0;
                    char currentRegion = regionsBoard[y][x];
                    regions[currentRegion] = 0;
                    queenBoard[y][x] = '*';
                    printf("unmarking queen at %d,%d on region %c\n", y,x,currentRegion);
                }

int queenRec(int y, int x, int regions[ASCII_SIZE], int queenRows[QUEEN_SIZE],int queenColumns[QUEEN_SIZE],
                char regionsBoard[QUEEN_SIZE][QUEEN_SIZE],char queenBoard[QUEEN_SIZE][QUEEN_SIZE], int boardSize){
            if (y == boardSize && queenRows[y-1]){
                printf("y got to the boardSize, returning 1\n");
                return 1;
            }
            else if (x == boardSize){
                printf("x got to the boardSize, returning 0\n");
                return 0;
            }


            if (check(y,x,queenRows,queenColumns,regions,regionsBoard,queenBoard)){
                printf("check for %d,%d was good!\n",y,x);
                markQueen(y,x,regions,queenRows,queenColumns,regionsBoard,queenBoard);
                
                if (!(queenRec(y+1,0,regions,queenRows,queenColumns,regionsBoard,queenBoard,boardSize))){
                    printf("queenRec at %d,%d failed\n",y+1,0);
                    unmarkQueen(y,x,regions,queenRows,queenColumns,regionsBoard,queenBoard);
                    printf("now trying queenRec with %d,%d\n", y,x+1);
                    return queenRec(y,x+1,regions,queenRows,queenColumns,regionsBoard,queenBoard,boardSize);
                }
            }
            
            
            else {
                printf("check for %d,%d was bad\n", y, x);
                return queenRec(y, x + 1, regions, queenRows, queenColumns, regionsBoard, queenBoard, boardSize);
    };
    return 1;
                    
}
void task5_crossword_generator(){
    char crossword[CROSSWORD_SIZE][CROSSWORD_SIZE]={0};
    Slot slots[SLOTS_SIZE];
    Word words[SLOTS_SIZE];
    int usedWords[SLOTS_SIZE] = {0};
    int gridSize, numOfSlots, numOfWords;
    printf("Please enter the dimensions of the crossword grid:\n");
    scanf("%d",&gridSize);
    printf("Please enter the number of slots in the crossword:\n");
    scanf("%d",&numOfSlots);
    printf("Please enter the details for each slot (Row, Column, Length, Direction):\n");
    for (int i=0; i<numOfSlots;i++){
        int row,column,length;
        char direction;
        scanf(" %d %d %d %c", &row, &column, &length, &direction);
        slots[i].row = row;
        slots[i].column = column;
        slots[i].length = length;
        slots[i].direction = direction;
        slots[i].assignedWord = -1;
    };
    printf("Please enter the number of words in the dictionary:\n");
    scanf("%d",&numOfWords);
    while (numOfWords<numOfSlots){
        printf("The dictionary must contain at least %d words. Please enter a valid dictionary size:\n", numOfSlots);
        scanf("%d",&numOfWords);
    };
    printf("Please enter words for the dictionary:\n");
    for (int i=0;i<numOfWords;i++){
        char word[WORD_SIZE];
        scanf("%s",word);
        words[i].index = i;
        int length = strlen(word);
        words[i].length = length;
        strcpy(words[i].letters, word);
    };

    if (crosswordRec(slots,words,crossword,usedWords,0,0,numOfSlots,numOfWords)){
        for (int i=0;i<gridSize;i++){
            for (int j=0; j<gridSize;j++){
                printf("| ");
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
        printf("No success for crossword\n");
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
    if (slotIndex == numOfSlots) {
        return 1;
        printf("slotIndex got to numOfSlots, returning 1\n");
    };

    if (wordIndex >= numOfWords-ADJUST_ONE) {
        return 0;
        printf("wordIndex got to numOfWords, returning 0\n");
    };

    if (canWordFitSlot(words[wordIndex], slots[slotIndex], usedWords, crossword)) {
        printf("word %s can fit slot %d\n",words[wordIndex].letters, slotIndex);
        insertWord(slots[slotIndex], 
                   words[wordIndex],
                   crossword, 
                   0, 
                   slots[slotIndex].row, 
                   slots[slotIndex].column, 
                   usedWords);
        if (crosswordRec(slots, words, crossword, usedWords, slotIndex + ADJUST_ONE, 0, numOfSlots, numOfWords)) {
            return 1;
        //     printf("Slot %d didn't find a word\n", slotIndex + ADJUST_ONE);
        //     int lastInsertedWord = slots[slotIndex].assignedWord;
        //     printf("Removing word %s from slot %d\n", words[wordIndex].letters, slotIndex);
        //     removeWord(slots[slotIndex], words[wordIndex], crossword, 0, slots[slotIndex].row, slots[slotIndex].column, usedWords);
        //     printf("Now trying recursion for slot %d starting from the word %s\n", slotIndex, words[lastInsertedWord + ADJUST_ONE].letters);
        //     return crosswordRec(slots, words, crossword, usedWords, slotIndex, lastInsertedWord + ADJUST_ONE, numOfSlots, numOfWords);
        // }
    } 
        printf("Slot %d didn't find a word\n", slotIndex);
        removeWord(slots[slotIndex], words[wordIndex], crossword, 0, slots[slotIndex].row, slots[slotIndex].column, usedWords);
    }
    else {
        printf("Doing recursion for slot %d starting with word %s\n", slotIndex, words[wordIndex + ADJUST_ONE].letters);
        return crosswordRec(slots, words, crossword, usedWords, slotIndex, wordIndex + ADJUST_ONE, numOfSlots, numOfWords);
    };
    return 1;
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
    else if (comparison(word,slot,crossword,0)){
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
    if (crossword[row][column]== '0'){
        return horizonCompare(word, slot, crossword, index+ADJUST_ONE, row, column+ADJUST_ONE);
    };
    //if we got here it means there is a letter in the slot, and we need to check that it matches the current index
    //letter in our word
    if (crossword[row][column] != word.letters[index]){
        return 0;
    };
    return 1;
};

int verticalCompare(Word word, Slot slot, char crossword[CROSSWORD_SIZE][CROSSWORD_SIZE],int index,int row,int column){
    //if the index aka the steps we checked got over the word length it means we checked all the
    //char slots for the word and they available or matching it
    if (index>word.length){
        return 1;
    };
    //if we have a 0 in the frid it means the space is available and we shall move on to the next chat slot,
    //moving by row becuase this is vertical
    if (crossword[row][column]== '0'){
        return horizonCompare(word, slot, crossword, index+ADJUST_ONE, row+ADJUST_ONE, column);
    };
    //if we got here it means there is a letter in the slot, and we need to check that it matches the current index
    //letter in our word
    if (crossword[row][column] != word.letters[index]){
        return 0;
    };
    return 1;
};

void insertWord(Slot slot, Word word, char crossword[CROSSWORD_SIZE][CROSSWORD_SIZE],int step,int row,int column, int usedWords[SLOTS_SIZE]){
    //function to redirect to the right inserting function depends on the direction of the slot
    if (slot.direction == 'H'){
        insertWordHorizon(slot,word,crossword,step,row,column,usedWords);
    }
    else insertWordVert(slot,word,crossword,step,row,column,usedWords);
}

void insertWordVert(Slot slot, Word word, char crossword[CROSSWORD_SIZE][CROSSWORD_SIZE],int step,int row,int column, int usedWords[SLOTS_SIZE]){
    //if we did number of steps as the length of the word, it means we inserted all letters to the slot and we can
    //end the function. also we will insert 1 in the usedWords array so we will know this word is taken,
    //and add the index of the word to its matching slot
    if (step == word.length){
        usedWords[word.index] =1;
        slot.assignedWord = word.index;
        return;
    }
    //inserting our letter to the slot
    crossword[row][column] = word.letters[step];
    //moving the recurssion to next word, vertically
    insertWordVert(slot,word,crossword,step+ADJUST_ONE,row+ADJUST_ONE,column,usedWords);
};

void insertWordHorizon(Slot slot, Word word, char crossword[CROSSWORD_SIZE][CROSSWORD_SIZE],int step,int row,int column, int usedWords[SLOTS_SIZE]){
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

void removeWord(Slot slot, Word word, char crossword[CROSSWORD_SIZE][CROSSWORD_SIZE],int step,int row,int column, int usedWords[SLOTS_SIZE]){
    //function to redirect to the right removing function depends on the direction of the slot
    if (slot.direction == 'H'){
        removeWordHorizon(slot,word,crossword,step,row,column,usedWords);
    }
    else removeWordVert(slot,word,crossword,step,row,column,usedWords);
}

void removeWordHorizon(Slot slot, Word word, char crossword[CROSSWORD_SIZE][CROSSWORD_SIZE],int step,int row,int column, int usedWords[SLOTS_SIZE]){
    //if we did number of steps as the length of the word, it means we removed all letters from the slot and we can
    //end the function. also we will insert 0 in the usedWords array so we will know this word is not taken anymore,
    //and return the value of assigned word to be -1 as its not attached to this slot anymore
    if (step == word.length){
        usedWords[word.index] =0;
        slot.assignedWord = -1;
        return;
    }
    //returning to default value
    crossword[row][column] = '0';
    //next stop in the recurrsion moving forward horizonally
    insertWordVert(slot,word,crossword,step+ADJUST_ONE,row,column+ADJUST_ONE,usedWords);
};

void removeWordVert(Slot slot, Word word, char crossword[CROSSWORD_SIZE][CROSSWORD_SIZE],int step,int row,int column, int usedWords[SLOTS_SIZE]){
    //if we did number of steps as the length of the word, it means we removed all letters from the slot and we can
    //end the function. also we will insert 0 in the usedWords array so we will know this word is not taken anymore
    //and return the value of assigned word to be -1 as its not attached to this slot anymore
    if (step == word.length){
        usedWords[word.index] =0;
        slot.assignedWord = -1;
        return;
    }
    //returning to default value
    crossword[row][column] = '0';
    //next step at the recurrsion moving down the rows vertically
    insertWordVert(slot,word,crossword,step+ADJUST_ONE,row+ADJUST_ONE,column,usedWords);
};






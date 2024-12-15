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
void task5_crossword_generator();

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
    for (int i=0;i<pyramidSize;i++){
        for (int j=0; j<=i;j++){
            float weightInput;
            scanf("%f", &weightInput);
            if (weightInput<0){
                printf("Negative weights are not supported.\n");
                return;
            }
            weights[i][j] = weightInput;
        }
    }

    for (int i=0;i<pyramidSize;i++){
        for (int j=0;j<=i;j++){
            float weightLoad = pyramidRecursion(weights, i, j);
            printf("%.2f ",weightLoad);
        }
        printf("\n");
    }
}

float pyramidRecursion(float weights[PYRAMID_SIZE][PYRAMID_SIZE], int row, int column){
    if (row < 0 || column < 0 || row<column){
        return 0;
    }
    return weights[row][column] + 
            0.5*pyramidRecursion(weights, row-1, column-1) + 0.5*pyramidRecursion(weights, row-1,column);
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
        findClosing(c1);
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
    else return 0;
}

void task4_queens_battle()
{
    // Todo
}

void task5_crossword_generator()
{
    // Todo
}
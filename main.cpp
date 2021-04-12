#include <cstdlib>
#include <ncurses.h>

bool gameOver;
//game map dimensions 20 x 20
const int width = 20, height = 20;
// x y = coordinates for head position
// fruitX fruitY = coordinates for fruit position
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100]; //snake coordinates
int nTail = 0;
// for direction, when you press a key, it keeps going in that direction
// no need to keep pressing direction key to move position
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN, EXIT}; //controls
eDirecton dir; // function holds direction of the snake

void Setup()
{
    initscr();
    clear();
    noecho();
    cbreak();
    curs_set(0);
    
    //how the game starts
    gameOver = false;
    dir = STOP; // the snake will not move until user starts moving it
    x = width / 2;
    y = height / 2;
    // width and height / 2 so starting point = middle of game map
    fruitX = (rand() % width) + 1; //display fruit in a random place
    fruitY = (rand() % height) + 1;
    // randomly placing fruits in game
    score = 0;
}

void Draw()
{
    clear(); //clear the screen
    //borders/walls of the game map
    for (int i = 0; i < width + 2; i++)
        mvprintw(0,i,"+");
    //printing the map
    for (int i = 0; i < height + 2; i++){
        for (int j = 0; j < width + 2; j++){
            if (i == 0 | i == 21)
                mvprintw(i,j,"*");
            else if (j == 0 | j == 21)
                mvprintw(i,j,"*");
            else if (i == y && j == x)
                mvprintw(i,j,"O");
            else if (i == fruitY && j == fruitX)
                mvprintw(i,j,"0");
            else
                for (int k = 0; k < nTail; k++){
                    if(tailX[k] == j && tailY[k] == i)
                        mvprintw(i,j,"o");
                }
        }
    }
    mvprintw(23,0,"Score %d",score);
    
    refresh();
}
void Input(){
    keypad(stdscr, TRUE);
    halfdelay(1);
    
    int c = getch();
    
    switch(c){
        case KEY_LEFT:
            dir = LEFT;
            break;
        case KEY_RIGHT:
            dir = RIGHT;
            break;
        case KEY_UP:
            dir = UP;
            break;
        case KEY_DOWN:
            dir = DOWN;
            break;
        case 113:
            gameOver = true;
            break;
    }
}

void Logic(){
    
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    
    for (int i = 1; i < nTail; i++){
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
        
    }
     
    
    switch (dir){
    case LEFT:
            x--;
            break;
    case RIGHT:
            x++;
            break;
    case UP:
            y--;
            break;
    case DOWN:
            y++;
            break;
    default:
            break;
    }
    if (x > width || x < 1 || y > height || y < 1)
    gameOver = true;
    
    if (x == fruitX && y == fruitY){
        score += 10;
        fruitX = (rand() % width) + 1;
        fruitY = (rand() % height) + 1;
        nTail++;
    }
    
    for (int i = 0; i < nTail; i++)
        if(tailX[i] == x && tailY[i] == y){
            gameOver = true;
        }
}
  
int main()
{
    Setup();
    while (!gameOver)
    {
        Draw();
        Input();
        Logic();
    }
    getch();
    endwin();
    return 0;
}

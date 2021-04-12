#include <iostream>
#include <conio.h> // for Mac users it is no possible to include conio.h
using namespace std;
bool gameOver;

//game map dimensions 20 x 20
const int width = 20;
const int height = 20;

// x y = coordinates for head position
// fruitX fruitY = coordinates for fruit position
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;

// for direction, when you press a key, it keeps going in that direction
// no need to keep pressing direction key to move position
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirecton dir; // function holds direction of the snake
void Setup()
{
    //how the game starts
    gameOver = false;
    dir = STOP; // the snake will not move until user starts moving it
    x = width / 2;
    y = height / 2;
    // width and height / 2 so starting point = middle of game map
    fruitX = rand() % width;
    fruitY = rand() % height;
    // randomly placing fruits in game
    score = 0;
}
void Draw()
{
    system("cls"); //clear the screen
    //borders/walls of the game map
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    //printing the map
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
                cout << "#";
            if (i == y && j == x)
                cout << "O";
            //printing head of snake

            else if (i == fruitY && j == fruitX)
                cout << "F";
            else
            {
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }


            if (j == width - 1)
                cout << "#";
            //printing walls
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++)
        cout << "#";
    //width + 2, to line up the borders properly
    cout << endl;
    cout << "Score:" << score << endl;
}
void input()
{
    if(_kbhit()) // we are using kbhit() to determine if a key has been pressed or not.
    {
        switch(_getch()) // getch() takes a single character from the input and returns an integer.
        {
        case 'a':
                dir = LEFT;
                break;
        case 'd':
                dir = RIGHT;
                break;
        case 'w':
                dir = UP;
                break;
        case 's':
                dir = DOWN;
                break;
        case 'x':
                gameOver = true;
                break;
//we have chosen the keys that will allow the user to move the snake.
        }
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
        Sleep(10); //slows down the game a bit
    }
    return 0;
}

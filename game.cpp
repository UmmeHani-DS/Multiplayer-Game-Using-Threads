#include <iostream>
#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include <pthread.h>
#include <unistd.h>

using namespace std;

int Boardsize;

int**  gameBoard;

pair<int, int> * playerPositions;  // used to store x and y coordiantes

int playerScores[2];

bool isGameOver = false;

// Function to update the game board with items

void Boardsetup()
{
    srand(time(0));

    // Allocate memory for the game board

    gameBoard = new int*[Boardsize];

    for (int i = 0; i < Boardsize; ++i) 
    {
        gameBoard[i] = new int[Boardsize];

        for (int j = 0; j < Boardsize; ++j) 
        {
            gameBoard[i][j] = rand() % 2;
        }
    }

}

// Function to display the game board using ncurses
void displayBoard() 
{
    for (int i = 0; i < Boardsize; ++i) 
    {
        for (int j = 0; j < Boardsize; ++j)
        {
            if (playerPositions[0].first == i && playerPositions[0].second == j)
                printw("P1 "); // Represents Player 1

            else if (playerPositions[1].first == i && playerPositions[1].second == j)
                printw("P2 "); // Represents Player 2

            else if (gameBoard[i][j] == 0)
                printw(". "); // To represent the square grid

            else
                printw("X "); // To represent an item
        }

        printw("\n");
    }

    printw("P1 Score: %d | P2 Score: %d\n", playerScores[0], playerScores[1]);
    refresh(); // Refresh the screen
}

void moveP1(int playID, int input)
{
    int x = playerPositions[playID].first;
    int y = playerPositions[playID].second;

    switch (input)
    {
        case KEY_UP: // Move up
            if (x > 0)
                playerPositions[playID].first--;
            break;

        case KEY_DOWN: // Move down
            if (x < Boardsize - 1)
                playerPositions[playID].first++;
            break;

        case KEY_LEFT: // Move left
            if (y > 0)
                playerPositions[playID].second--;
            break;

        case KEY_RIGHT: // Move right
            if (y < Boardsize - 1)
                playerPositions[playID].second++;
            break;

        default:
            break;
    }

    if (gameBoard[x][y] == 1) 
    {
        playerScores[playID]++;
        gameBoard[x][y] = 0;
    }
}

// Function to handle player movements

void moveP2(int playID, int input) 
{
    int x = playerPositions[playID].first;
    int y = playerPositions[playID].second;

    switch (input) 
    {
        case 'w': // Move up
            if (x > 0)
                playerPositions[playID].first--;
            break;

        case 's': // Move down
            if (x < Boardsize - 1)
                playerPositions[playID].first++;
            break;

        case 'a': // Move left
            if (y > 0)
                playerPositions[playID].second--;
            break;
        case 'd': // Move right
            if (y < Boardsize - 1)
                playerPositions[playID].second++;
            break;

        default:
            break;
    }

    if (gameBoard[x][y] == 1) 
    {
        playerScores[playID]++;
        gameBoard[x][y] = 0;
    }
}

// Function to get player input using ncurses

void * getInput(void* playID)
{
    int playId = *((int*)playID);

    while (!isGameOver)
    {
        int input = getch();  // Using ncurses for input

        if(playID == 0)
        {
            moveP1(playId, input);
        }
        else
        {
            moveP2(playId, input);
        }
       
    }

    return nullptr;

}



int main()
{

    // Intialize ncurses

        initscr(); // To intialize the screen and allocate memory
        keypad(stdscr, true);
        noecho();
        cbreak();

        // Board Size

            srand(time(0));

            int num = rand() % 90 + 10;

            num = num * 5; // 21I-1715

            int roll = 211715;

            Boardsize = roll / num;

            Boardsize = Boardsize % 25;

            if(Boardsize < 10)
            {
                Boardsize += 15;
            }

        Boardsetup();

        // Allocate memory for player positions

        playerPositions = new pair<int, int>[2];

        pthread_t P1, P2;

        int P1ID = 0, P2ID = 1;

        pthread_create(&P1, nullptr, getInput, (void*)&P1ID);
        pthread_create(&P2, nullptr, getInput, (void*)&P2ID);

        while(!isGameOver)
        {
            clear(); 

            displayBoard(); 

            if (playerScores[0] >= 10) 
            {
                printw("Player 1 wins!\n");
                isGameOver = true;
                usleep(10000); 
            } 
            
            else if (playerScores[1] >= 10)
            {
                printw("Player 2 wins!\n");
                isGameOver = true;
                usleep(10000); 
            }

            usleep(10000); 
        }

            pthread_join(P1, nullptr);
            pthread_join(P2, nullptr);

            printw("Game Over!\n");
            refresh();

            endwin(); // Terminate ncurses

            // Deallocate memory
            for (int i = 0; i < Boardsize; ++i)
            {
                delete[] gameBoard[i];
            }

            delete[] gameBoard;
            delete[] playerPositions;

        return 0;
}
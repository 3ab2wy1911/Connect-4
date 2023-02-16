#include <bits/stdc++.h>
#include<windows.h>
#include <stdio.h>
#define row 6
#define column 7
using namespace std;
class player
{
protected:
    string name;
    char symbol;
public:
    player(string n, char s)
    {
        name = n;
        symbol = s;
    }

    char get_symbol()
    {
        return symbol;
    }
    string get_name()
    {
        return name;
    }

};
class Board
{
    char grid[row][column];
public:
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    Board()
    {
        for (auto & i : grid)
            for (char & j : i)
                j=' ';
    }
    bool in_range(int y)
    {
        if (y<column and y>=0)
            return true;
        cout<<"Out of Range!!!";
        return false;
    }
    bool update_board (int y, char symbol)
    {
        for (int i=row-1;i>=0;i--)
        {
            if (grid[i][y] == ' ' and in_range(y))
            {
                grid [i][y] = symbol;
                return true;
            }
        }
        cout<<"Wrong move ,please enter again:";
        return false;
    }
    bool is_winner(char symbol) {
        // Check horizontal
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 4; j++) {
                if (grid[i][j] == symbol && grid[i][j+1] == symbol && grid[i][j+2] == symbol && grid[i][j+3] == symbol) {
                    return true;
                }
            }
        }

        // Check vertical
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 7; j++) {
                if (grid[i][j] == symbol && grid[i+1][j] == symbol && grid[i+2][j] == symbol && grid[i+3][j] == symbol) {
                    return true;
                }
            }
        }

        // Check diagonal (top left to bottom right)
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 4; j++) {
                if (grid[i][j] == symbol && grid[i+1][j+1] == symbol && grid[i+2][j+2] == symbol && grid[i+3][j+3] == symbol) {
                    return true;
                }
            }
        }

        // Check diagonal (top right to bottom left)
        for (int i = 0; i < 3; i++) {
            for (int j = 3; j < 7; j++) {
                if (grid[i][j] == symbol && grid[i+1][j-1] == symbol && grid[i+2][j-2] == symbol && grid[i+3][j-3] == symbol) {
                    return true;
                }
            }
        }

        // If no winning combination is found, return false
        return false;
    }

    bool is_Draw(char symbol1, char symbol2)
    {
        for(int i= 0 ;i<row;i++)
        {
            for (int j =0 ;j<column; j++)
            {
                if (grid[i][j] ==' ')
                    return false;
            }
        }
        return (!is_winner(symbol1) and !is_winner(symbol2));
    }
    void print_board()
    {
        for (int i=0;i<row;i++)
        {
            for (int j =0 ;j<column;j++)
            {
                cout<<" | ";
                if (grid[i][j]=='0')
                {
                    SetConsoleTextAttribute(hConsole,10);

                }
                else if (grid[i][j]=='O')
                {
                    SetConsoleTextAttribute(hConsole,5);
                }
                cout<<grid[i][j];
                SetConsoleTextAttribute(hConsole,15);
            }

            cout<<" |"<<endl;
        }
    }
};
class game
{
private:
    Board board;
    int turn =0 ;
public:
    game()
    {
    };

    void play()
    {
        cout<<"Enter first player name:";
        string name;
        cin>>name;
        player p1(name,'O');
        cout<<"Enter Second player name:";
        cin>>name;
        player p2 (name,'0');
        board.print_board();
        while (!board.is_Draw(p1.get_symbol(),p2.get_symbol()) and !(board.is_winner(p1.get_symbol()) or board.is_winner(p2.get_symbol())))
        {
            cout<<"Please enter the the position you want to put your symbol in :\n";
            int y;
            if (turn ==0) {
                cout << p1.get_name() << " turn!";
                cin >> y;
                while (!board.update_board( y-1, p1.get_symbol()))
                {
                    cin>>y;
                }
                board.print_board();
                turn = 1;
            }
            else if (turn == 1)
            {
                cout<<p2.get_name()<<" turn!";
                cin>>y;
                while (!board.update_board( y-1, p2.get_symbol()))
                {
                    cin>>y;
                }
                board.print_board();
                turn = 0;
            }
        }
        if (board.is_winner(p1.get_symbol()))
            cout<<p1.get_name()<<" win !!!";
        else if (board.is_winner(p2.get_symbol()))
            cout<<p2.get_name()<<" win !!!";
        else
            cout<<"Tie!";
    }
};

int main()
{
    game Game;
    Game.play();

}


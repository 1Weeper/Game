#include <iostream>
#include <windows.h>




using namespace std;

bool game_running = true;

const int xres=13;
const int yres=24;

char map[xres][yres] =
{
    "###################",
    "#x      ##        #",
    "#   $$  ##        #####",
    "#   $$  ##            #",
    "#       ##        #   #",
    "#       ##        #   #",
    "##   ########   ###   #",
    "#               $$#   #",
    "#                 # $ #",
    "###################   #",
    "                  #   #",
    "                  #@@@#",
    "                  #####"

};
int x=1;
int y=1;

char plr = 'x';
char enemy = 'M';

int cash = 0;

int frame = 1;

void clr()
{
    HANDLE                     hStdOut;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD                      count;
    DWORD                      cellCount;
    COORD                      homeCoords = { 0, 0 };

    hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
    if (hStdOut == INVALID_HANDLE_VALUE) return;

    /* Get the number of cells in the current buffer */
    if (!GetConsoleScreenBufferInfo( hStdOut, &csbi )) return;
    cellCount = csbi.dwSize.X *csbi.dwSize.Y;

    /* Fill the entire buffer with spaces */
    if (!FillConsoleOutputCharacter(
                hStdOut,
                (TCHAR) ' ',
                cellCount,
                homeCoords,
                &count
            )) return;

    /* Fill the entire buffer with the current colors and attributes */
    if (!FillConsoleOutputAttribute(
                hStdOut,
                csbi.wAttributes,
                cellCount,
                homeCoords,
                &count
            )) return;

    /* Move the cursor home */
    SetConsoleCursorPosition( hStdOut, homeCoords );
}


int win()
{
    cout << endl << "Congrats you past level 1!" << endl;
    game_running = false;
    cin.get();
}
int lost()
{
    cout << endl << "YOU DIED!" << endl;
    cin.get();
}


int main()
{
    while(game_running == true)
    {
        clr();
        for(int display=0; display<xres; display++)
        {
            cout << map[display] << endl;
        }
        cout<<"cash: "<<cash<<endl;
        system("pause>nul");

        if (GetAsyncKeyState(VK_UP)!= 0 || (GetAsyncKeyState(VK_DOWN)!= 0) || (GetAsyncKeyState(VK_LEFT)!= 0) || (GetAsyncKeyState(VK_RIGHT)!= 0))
        {

            if (frame < 3)
            {
                map[8][7] = enemy;
                map[7][7] = ' ';
                frame++;
            }
            else if (frame < 6)
            {
                map[8][7] = ' ';
                map[7][7] = enemy;
                frame ++;
            }
            else if (frame == 6)
            {
                frame = 0;
            }
        }




        if(GetAsyncKeyState(VK_UP)!= 0)
        {
            if(map[y-1][x]==' ')
            {
                map[y][x]=' ';
                y--;
                map[y][x]=plr;
            }
            else if(map[y-1][x]==enemy)
            {
                lost();
            }
        }

        if(GetAsyncKeyState(VK_DOWN)!= 0)
        {
            if(map[y+1][x]==' ')
            {
                map[y][x]=' ';
                y++;
                map[y][x]=plr;
            }
            else if(map[y+1][x]==enemy)
            {
                lost();
            }
        }
        if(GetAsyncKeyState(VK_RIGHT)!= 0)
        {
            if(map[y][x+1]==' ')
            {
                map[y][x]=' ';
                x++;
                map[y][x]=plr;
            }
            else if(map[y][x+1]==enemy)
            {
                lost();
            }
        }
        if(GetAsyncKeyState(VK_LEFT)!= 0)
        {
            if(map[y][x-1]==' ')
            {
                map[y][x]=' ';
                x--;
                map[y][x]=plr;
            }
            else if(map[y][x-1]==enemy)
            {
                lost();
            }
        }


        if(GetAsyncKeyState(VK_SPACE)!= 0)
        {
            if(map[y][x+1]=='$' || map[y][x-1]=='$' || map[y+1][x]=='$' || map[y-1][x]=='$')
            {

                if(map[y][x+1]=='$')
                {
                    map[y][x+1]=' ';
                    cash++;
                }
                if(map[y][x-1]=='$')
                {
                    map[y][x-1]=' ';
                    cash++;
                }
                if(map[y+1][x]=='$')
                {
                    map[y+1][x]=' ';
                    cash++;
                }
                if(map[y-1][x]=='$')
                {
                    map[y-1][x]=' ';
                    cash++;
                }
            }


            if(map[y+1][x]=='@')
            {
                win();
            }
        }
    }
}

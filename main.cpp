#include <iostream>
#include <unistd.h>
#include <windows.h>

using namespace std;

bool game_running = true;

const int xres=13;
const int yres=24;

char map[xres][yres] =
{
    "###################",
    "#x      ## $$$$   #",
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

int win()
{
    cout << endl << "Congrats you past level 1!" << endl;
    game_running = false;
    system("pause");
}
int lost()
{
    cout << endl << "YOU DIED!" << endl;
    system("pause");
}


int main()
{
    while(game_running == true)
    {
        system("cls");
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
        }

        if(GetAsyncKeyState(VK_DOWN)!= 0)
        {
            if(map[y+1][x]==' ')
            {
                map[y][x]=' ';
                y++;
                map[y][x]=plr;
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

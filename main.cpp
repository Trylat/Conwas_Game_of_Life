// Following tutorial from TheBuilder: https://www.youtube.com/watch?v=9NK5holxvOw&list=PLYmIsLVSssdIOn5J71CVBblPlXici1_2A&index=7&ab_channel=TheBuilder

#include "screen.h"
#include <array>

const int GAME_WIDTH = 640;
const int GAME_HEIGHT = 480;

bool isAlive(
                std::array<std::array<int, GAME_HEIGHT>, GAME_WIDTH>& game,
                const int x,
                const int y)
{
    int alive = 0;
    // Testing the Left cell
    if(x > 0 && game[x-1][y] == 1) alive+=1;
    // Testing the Right cell
    if(x < GAME_WIDTH && game[x+1][y] == 1) alive+=1;
    // Testing the Top cell
    if(y > 0 && game[x][y-1] == 1) alive+=1;
    // Testing the Bottom cell
    if(y < GAME_HEIGHT && game[x][y+1] == 1) alive+=1;

    // Testing the Top Left cell
    if(y > 0 && x > 0 && game[x-1][y-1] == 1) alive+=1;
    // Testing the Top Right cell
    if(y > 0 && x < GAME_WIDTH && game[x+1][y-1] == 1) alive+=1;
    // Testing the Bottom Left cell
    if(y < GAME_HEIGHT && x > 0 && game[x-1][y+1] == 1) alive+=1;
    // Testing the Bottom Right cell
    if(y < GAME_HEIGHT && x < GAME_WIDTH  && game[x+1][y+1] == 1) alive+=1;

    // live and fewer than 2 die
    if(game[x][y] == 1 && alive < 2) return false;
    // live and 2 or 3 then live
    if(game[x][y] == 1 && (alive == 2 || alive == 3)) return true;
    // dead and 3 than live
    if(game[x][y] == 0 && alive == 3) return true;
    // live and more than 3 than die
    if(alive > 3) return false;

    else return false;

}

int main(){
    G screen;
    std::array<std::array<int, GAME_HEIGHT>, GAME_WIDTH> display {};
    std::array<std::array<int, GAME_HEIGHT>, GAME_WIDTH> swap {};

    // Create Random Points
    for(auto& row : display){
        std::generate(row.begin(), row.end(), []() { return rand()%10 == 0 ? 1 : 0; });
    }

    while(true){
        // Check for alive points
        if(screen.play){
            for (int i = 0; i < GAME_WIDTH; i++){
                for(int j = 0; j <GAME_HEIGHT; j++){
                    swap[i][j] = isAlive(display, i, j) ? 1 : 0;
                }
            }
        }

        //Draw
        for (int i = 0; i < GAME_WIDTH; i++){
            for(int j = 0; j <GAME_HEIGHT; j++){
                if(swap[i][j]){
                    screen.drawpixel(i,j);
                }
            }
        }


        //Copy Swap Buffer to Display
        std::copy(swap.begin(), swap.end(), display.begin());

        // Display to screen
        screen.update();
        SDL_Delay(20);
        screen.input();
        screen.clearpixels();
    }
}
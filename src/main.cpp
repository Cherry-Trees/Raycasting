#include <SFML/Graphics.hpp>
#include "globals.h"
#include "Player.h"

#define PI 3.1415f

int main() {

    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!");

    Sprite cell_sprite[MAP_WIDTH][MAP_HEIGHT];
    Texture floor_texture, wall_texture;
  
    floor_texture.loadFromFile("res/Floor.png");
    wall_texture.loadFromFile("res/Wall.png");

    for (int i=0; i<MAP_WIDTH; i++) {
        for (int j=0; j<MAP_HEIGHT; j++) {

            if (map[i][j] == '+')
                cell_sprite[i][j].setTexture(floor_texture);
            else
                cell_sprite[i][j].setTexture(wall_texture);
                
            cell_sprite[i][j].setTextureRect(IntRect(0, 0, WINDOW_CELL_SIZE, WINDOW_CELL_SIZE));
            cell_sprite[i][j].setPosition(j*WINDOW_CELL_SIZE, i*WINDOW_CELL_SIZE);
        }
    }


    Player p = Player(WINDOW_WIDTH/2, WINDOW_HEIGHT/2);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {   
            switch(event.type)
            {
                case Event::Closed:
                {
                    window.close();
                    break;
                }

            }
        }

        

        window.clear();

        for (int i=0; i<MAP_WIDTH; i++) {
            for (int j=0; j<MAP_HEIGHT; j++) {
                window.draw(cell_sprite[i][j]);
            }
        }
        //p.move(map, window);
        //p.update(map, window);
        p.update(window);

        window.display();
    }

    return 0;
}


// TO RUN:

// g++ -I"C:\SFML-2.6.1\include" -c main.cpp -o main.o
// g++ main.o -o app.exe -L"C:\SFML-2.6.1\lib" -lsfml-graphics -lsfml-window -lsfml-system -lsfml-main -mwindows

// OR

// MinGW32-make compile
// MinGW32-make link

// OR

// MinGW32-make all

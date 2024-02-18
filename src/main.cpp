#include <SFML/Graphics.hpp>
#include "globals.h"
#include "Player.h"

int main() {

    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!");

    RectangleShape floor = RectangleShape(Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT/2));
    floor.setFillColor(Color(10,10,12));
    floor.setPosition(0, WINDOW_HEIGHT/2);

    RectangleShape sky = RectangleShape(Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT/2));
    sky.setFillColor(Color(67, 105, 202));
    sky.setPosition(0, 0);

    Player p = Player(WINDOW_WIDTH/2, WINDOW_HEIGHT/2);

    while (window.isOpen())
    {       
        window.clear();
        window.draw(floor);
        window.draw(sky);
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

#include <SFML/Graphics.hpp>
#include <math.h>
#include "globals.h"
#include "functions.h"
using namespace sf;

class Player {

    public:
        Vector2f pos;
        Vector2f dir;

        Player(float x, float y);
        void update(RenderWindow &window);

    private:
        RectangleShape slices[WINDOW_WIDTH];

        Vector2i cellStep;
        Vector2i cellIndices;
        Vector2f plane;
        Vector2f dr;
        Vector2f ds;
        Vector2f ray;
        Vector2f rayDir;

        float moveSpeed;
        float angularSpeed;
        float angle;
        float rayLength;
        float verticalFov;
        float verticalDistance;
        float renderDistance;

        void handleEvents(RenderWindow &window);
        bool isCollidingWithWall(Vector2f nextPos);
        void render(RenderWindow &window);
};

Player::Player(float x, float y) : pos(x, y), dir(0, 1), plane(-1.f, 0), sprite(WINDOW_CELL_SIZE/2), dirSprite(5.f)
{
    moveSpeed=0.6f; 
    angularSpeed=0.011f;
    verticalFov = 3.1415f / 4.f;

    verticalDistance = 0.5f * WINDOW_CELL_SIZE / tan(0.5f * verticalFov);
    renderDistance = 9000;
}

bool Player::isCollidingWithWall(Vector2f nextPos) 
{
    float row = nextPos.y / (float)WINDOW_CELL_SIZE;
    float col = nextPos.x / (float)WINDOW_CELL_SIZE;

    int rowIndex, colIndex;
    for (int side=0; side<4; side++) 
    {
        switch (side)
        {
            case 0:
            {
                rowIndex = floor(row);
                colIndex = floor(col);
                break;
            }

            case 1:
            {
                rowIndex = ceil(row);
                colIndex = ceil(col);
                break;
            }

            case 2:
            {
                rowIndex = floor(row);
                colIndex = ceil(col);
                break;
            }

            case 3:
            {
                rowIndex = ceil(row);
                colIndex = floor(col);
                break;
            }
        }

        if (map[rowIndex][colIndex] == '#') {return true;}
        
    }

    return false;
}

void Player::handleEvents(RenderWindow &window) 
{
    angle = atan(dir);
    dr = Vector2f(0, 0);

    Event event;
    while (window.pollEvent(event)) {
        switch(event.type)
        {
            case Event::Closed:
            {
                window.close();
                break;
            }
    
    if (Keyboard::isKeyPressed(Keyboard::W)) {dr = -moveSpeed * dir;}
    else if(Keyboard::isKeyPressed(Keyboard::S)) {dr = moveSpeed * dir;}

    if (Keyboard::isKeyPressed(Keyboard::D)) 
    {
        dir = Vector2f(cos(angle - angularSpeed), sin(angle - angularSpeed));
        plane = rotate(plane, - angularSpeed);
    }
    else if (Keyboard::isKeyPressed(Keyboard::A)) 
    {
        dir = Vector2f(cos(angle + angularSpeed), sin(angle + angularSpeed));
        plane = rotate(plane, angularSpeed);
    }

    if (!isCollidingWithWall(Vector2f(pos.x + dr.x, pos.y + dr.y))) {pos += dr;}
    if (!isCollidingWithWall(Vector2f(pos.x + dr.x, pos.y))) {pos.x += dr.x;}
    if (!isCollidingWithWall(Vector2f(pos.x, pos.y + dr.y))) {pos.y += dr.y;}
}

// DDA
void Player::render(RenderWindow &window) 
{
    for (int x=0; x<WINDOW_WIDTH; x++)
    {

        float cameraX = 2 * x / (float)WINDOW_WIDTH - 1;
        rayDir = -dir + plane * cameraX;
        
        Vector2f rayStart = pos + 0.5f * (float)WINDOW_CELL_SIZE;

        cellIndices.x = floor(rayStart.x / (float)WINDOW_CELL_SIZE);
        cellIndices.y = floor(rayStart.y / (float)WINDOW_CELL_SIZE);

        ds.x = WINDOW_CELL_SIZE / abs(rayDir.x);
        ds.y = WINDOW_CELL_SIZE / abs(rayDir.y);

        if (rayDir.x < 0)
        {
            cellStep.x = -1;
            ray.x = ds.x * ((rayStart.x / (float)WINDOW_CELL_SIZE) - cellIndices.x);
        }
        else
        {
            cellStep.x = 1;
            ray.x = ds.x * (1 + cellIndices.x - (rayStart.x / (float)WINDOW_CELL_SIZE));
        }
        if (rayDir.y < 0)
        {
            cellStep.y = -1;
            ray.y = ds.y * ((rayStart.y / (float)WINDOW_CELL_SIZE) - cellIndices.y);
        }
        else
        {
            cellStep.y = 1;
            ray.y = ds.y * (1 + cellIndices.y - (rayStart.y / (float)WINDOW_CELL_SIZE));
        }

        bool hit = false;
        bool side;
        float rayLength;
        while (!hit)
        {
            if (ray.x < ray.y)
            {
                rayLength = ray.x;
                ray.x += ds.x;
                
                cellIndices.x += cellStep.x;
                side = false;
            }
            else if (ray.x > ray.y)
            {
                rayLength = ray.y;
                ray.y += ds.y;
                
                cellIndices.y += cellStep.y;
                side = true;
            }
            else
            {
                rayLength = ray.x;
                ray.x += ds.x;
                ray.y += ds.y;

                cellIndices.x += cellStep.x;
                cellIndices.y += cellStep.y;
            }
            if (map[cellIndices.y][cellIndices.x] == '#') {hit = true;}
        }

        float sliceHeight = round(WINDOW_HEIGHT * verticalDistance / rayLength);

        slices[x] = RectangleShape(Vector2f(1, sliceHeight));
        slices[x].setFillColor(Color(
            std::min((renderDistance * 255) / (float)(rayLength*rayLength), 220.f),
            std::min((renderDistance * 255) / (float)(rayLength*rayLength), 220.f),
            std::min((renderDistance * 255) / (float)(rayLength*rayLength), 220.f)
            ));
        
        slices[x].setPosition(x, 0.5f * (WINDOW_HEIGHT - sliceHeight));
        window.draw(slices[x]);
    }
}

void Player::update(RenderWindow &window) 
{
    handleEvents(window);
    render(window);
}

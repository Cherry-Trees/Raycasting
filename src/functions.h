#include <SFML/Graphics.hpp>
#include <math.h>
using namespace sf;

Vector2f operator*(Vector2f A, Vector2f B) {return Vector2f(A.x*B.x, A.y*B.y);}
Vector2f operator+(Vector2f A, float c) {return Vector2f(A.x + c, A.y + c);}

Vector2f rotate(Vector2f A, float theta)
{
    return Vector2f(
        A.x * cos(theta) - A.y * sin(theta),
        A.x * sin(theta) + A.y * cos(theta)
    );
}
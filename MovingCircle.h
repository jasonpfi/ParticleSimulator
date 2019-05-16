#include <SFML/Graphics.hpp>

class MovingCircle
{
private:
    
    float x_velocity;
    float y_velocity;

public:
    MovingCircle(float x_velocity = 0, float y_velocity = 0, float radius = 10)
        : x_velocity(x_velocity), y_velocity(y_velocity), circle(sf::CircleShape(radius))
    {}
}

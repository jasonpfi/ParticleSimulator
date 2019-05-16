#include <SFML/Graphics.hpp>
#include <cmath>
//#include <Keyboard.hpp>

#define X_WIDTH 1600
#define Y_WIDTH 1000

void WallDetection(sf::CircleShape& circle, float& x_vel, float& y_vel, int wall_x, int wall_y)
{
    float overflow_x = 0.0f;
    float overflow_y = 0.0f;

    if (circle.getPosition().x + circle.getRadius() >= wall_x || circle.getPosition().x - circle.getRadius() <= 0)
    {
        x_vel *= -0.80f;
        overflow_x = (circle.getPosition().x  - circle.getRadius() < 0 ? -1 * circle.getPosition().x + circle.getRadius() : wall_x - (circle.getPosition().x + circle.getRadius()));
    }
    if (circle.getPosition().y + circle.getRadius() >= wall_y || circle.getPosition().y - circle.getRadius() <= 0)
    {
        y_vel *= -0.80f;
        overflow_y = (circle.getPosition().y - circle.getRadius() < 0 ? -1 * circle.getPosition().y + circle.getRadius() : wall_y - (circle.getPosition().y + circle.getRadius()));
    }

    circle.setPosition(circle.getPosition().x + x_vel + overflow_x, circle.getPosition().y + y_vel + overflow_y);
}

float WallDetection2(float position, float radius, float& velocity, int wall)
{
    if (position + radius >= wall || position - radius <= 0)
    {
        velocity *= -0.8;
    }

    return fmax(0 + radius, fmin(wall - radius, position + velocity));
}

int main()
{
    sf::RenderWindow window{ {X_WIDTH, Y_WIDTH }, "Main loop test" };
    window.setFramerateLimit(60);

    float x_velocity = 0;
    float y_velocity = 0;
    float acceleration = 0.5;

    sf::CircleShape circle{ 50 };
    circle.setOrigin(circle.getRadius(), circle.getRadius());
    circle.setFillColor(sf::Color::White);
    circle.setPosition({X_WIDTH / 2, Y_WIDTH / 2 });

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Left)
                {
                    x_velocity -= acceleration;
                }
                else if (event.key.code == sf::Keyboard::Right)
                {
                    x_velocity += acceleration;
                }
                else if (event.key.code == sf::Keyboard::Down)
                {
                    y_velocity += acceleration;
                }
                else if (event.key.code == sf::Keyboard::Up)
                {
                    y_velocity -= acceleration;
                }
                else if (event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
            }
        }

        float new_x = WallDetection2(circle.getPosition().x, circle.getRadius(), x_velocity, window.getSize().x);
        float new_y = WallDetection2(circle.getPosition().y, circle.getRadius(), y_velocity, window.getSize().y);
        circle.setPosition(new_x, new_y);

        // WallDetection(circle, x_velocity, y_velocity, window.getSize().x, window.getSize().y);
        // printf("%f, %f : %f, %f\n", circle.getPosition().x, circle.getPosition().y + circle.getRadius(), x_velocity, y_velocity);

        window.clear();
        window.draw(circle);
        window.display();
    }
}


#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

namespace GLD
{

namespace Math {

    inline float distance(const sf::Vector2f& vec1, const sf::Vector2f& vec2) {
        return std::sqrt(std::pow(vec1.x - vec2.x, 2) + std::pow(vec1.y - vec2.y, 2));
    }
    inline float distance(const sf::Shape& shape1, const sf::Shape& shape2) {
        return distance(shape1.getPosition(), shape2.getPosition());
    }

    inline sf::Vector2f distance2f(const sf::Vector2f& vec1, const sf::Vector2f& vec2){
        return {vec1.x - vec2.x, vec1.y - vec2.y};
    }
    inline sf::Vector2f distance2f(const sf::Shape& shape1, const sf::Shape& shape2){
        return distance2f(shape1.getPosition(), shape2.getPosition());
    }

    inline float angle(const sf::Vector2f& vec1, const sf::Vector2f& vec2){
        return std::atan2(vec1.y - vec2.y, vec1.x - vec2.x) * 180.0f/M_PI;
    }
    inline float angle(const sf::Shape& shape1, const sf::Shape& shape2){
        return angle(shape1.getPosition(), shape2.getPosition());
    }
}

}

#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <vector>
#include "Common.h"

class Animation
{
    sf::Sprite m_sprite;
    size_t m_animCount = 1; // total anim count
    size_t m_currentAnim = 0;
    size_t m_currentFrame = 0; // number of frame passed since beginning of anim
    size_t m_speed = 0; // play speed of animation 
    Vec2 m_size = { 1, 1 }; // size of anim frame
    std::string m_name = "none";

public:

    Animation();
    Animation(const std::string & name, const sf::Texture & t);
    Animation(const std::string & name, const sf::Texture & t,
             size_t animCount, size_t speed);

    void update();
    bool hasEnded() const;
    const std::string & getName() const { return m_name; }
    const Vec2 & getSize() const { return m_size; }
    sf::Sprite & getSprite() { return m_sprite; }

};

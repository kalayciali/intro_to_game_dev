#include <SFML/Graphics/Rect.hpp>
#include <cmath>
#include "Animation.h"

// by default repeat same frame over and over
Animation::Animation(const std::string & name, const sf::Texture & t)
    : Animation(name, t, 1, 0) {}

Animation::Animation(const std::string & name, const sf::Texture & t,
        size_t animCount, size_t speed)
    : m_name(name),
    m_sprite(t),
    m_animCount(animCount),
    m_currentFrame(0),
    m_currentAnim(0),
    m_speed(speed)
{
    m_size = Vec2((float)t.getSize().x / animCount, (float)t.getSize().y);
    m_sprite.setOrigin(m_size.x / 2, m_size.y / 2);
    m_sprite.setTextureRect(
            sf::IntRect(m_currentAnim * m_size.x, 0, m_size.x, m_size.y));
}

// update animation to show next frame 
void Animation::update()
{
    m_currentFrame++;
    size_t animNow = (m_currentFrame / m_speed) % m_animCount;
    // calculate correct frame of animation
    // set texture rectangle accordingly
    if (m_currentAnim != animNow)
    {
        m_currentAnim = animNow;
        m_sprite.setTextureRect(
                sf::IntRect(m_currentAnim * m_size.x, 0, m_size.x, m_size.y));
    }
}

bool Animation::hasEnded() const
{
    // if animCount is 1 assume repeated animation
    if (m_animCount != 1 && m_currentAnim == m_animCount)
        return true;
    return false;
}


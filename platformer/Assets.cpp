#include "Assets.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <cassert>

void Assets::loadFromFile(const std::string & base, const std::string & path)
{
    std::ifstream fin(base + path);
    std::string inputType;
    // load from file file
    while(fin >> inputType)
    {
        if (inputType == "Texture")
        {
            std::string texName, path;
            fin >> texName >> path;
            addTexture(texName, base + path);
        } 
        else if (inputType == "Animation")
        {
            std::string animName, texName;
            size_t animCount, animSpeed;
            fin >> animName >> texName >> animCount >> animSpeed;
            addAnimation(animName, texName,
                    animCount, animSpeed);
        }
        else if (inputType == "Font")
        {
            std::string fontName, path;
            fin >> fontName >> path;
            addFont(fontName, base + path);
        }
    }

}

void Assets::addTexture(
        const std::string & textureName, 
        const std::string & path, 
        bool smooth
        )
{
    m_textureMap[textureName] = sf::Texture();

    if (!m_textureMap[textureName].loadFromFile(path))
    {
        std::cerr << "Could not load texture file: " << path << std::endl;
        m_textureMap.erase(textureName);
    }
    else
    {
        m_textureMap[textureName].setSmooth(smooth);
        std::cout << "Loaded texture: " << path << std::endl;
    }
}

void Assets::addAnimation(
        const std::string & animName, 
        const std::string & texName, 
        size_t animCount, 
        size_t animSpeed
        )
{

    m_animationMap[animName] = animSpeed ? 
        Animation(animName, m_textureMap[texName]) :
        Animation(animName, m_textureMap[texName], animCount, animSpeed);
}

void Assets::addFont(
        const std::string & fontName, 
        const std::string & path 
        )
{
    m_fontMap[fontName] = sf::Font();

    if (!m_fontMap[fontName].loadFromFile(path))
    {
        std::cerr << "Could not load font file: " << path << std::endl;
        m_textureMap.erase(fontName);
    }
    else
    {
        std::cout << "Loaded font: " << path << std::endl;
    }

}


const sf::Texture & Assets::getTexture(const std::string & textureName) const
{
    assert(m_textureMap.find(textureName) != m_textureMap.end());
    return m_textureMap.at(textureName);
}

const Animation & Assets::getAnimation(const std::string & animName) const
{
    assert(m_animationMap.find(animName) != m_animationMap.end());
    return m_animationMap.at(animName);
}

const sf::Font & Assets::getFont(const std::string & fontName) const
{
    assert(m_fontMap.find(fontName) != m_fontMap.end());
    return m_fontMap.at(fontName);
}

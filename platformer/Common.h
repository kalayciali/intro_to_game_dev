#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <map>
#include <memory>
#include <string>
#include <ifstream>
#include <iostream>

#include "Vec2.h"
#include "Physics.h"

template <class T> using ptr = std::shared_ptr<T>

#include "Time.h"

pong::Time::Time()
{
    // Create a clock.
    clock = sf::Clock();
}

pong::Time::~Time()
{
}

pong::Time& pong::Time::getInstance()
{
    // Create singleton instance.
    static pong::Time instance;
    return instance;
}

void pong::Time::init()
{
    getInstance().clock.restart();
}

float pong::Time::getSecondsDelta()
{
    return getInstance().deltaTime.asSeconds();
}

void pong::Time::tick()
{
    getInstance().deltaTime = getInstance().clock.restart();
}


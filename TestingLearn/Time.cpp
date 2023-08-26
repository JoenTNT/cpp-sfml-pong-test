#include "Time.h"

pong::Time::Time()
{
    // Initialize clock.
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

float pong::Time::getFixedDelta()
{
    return getInstance().fixedDeltaTime;
}

void pong::Time::setFixedDelta(float fixedDeltaTime)
{
    getInstance().fixedDeltaTime = fixedDeltaTime;
}

float pong::Time::getElapsedDelta()
{
    return getInstance().t;
}

void pong::Time::tick()
{
    // Get only instance.
    auto& time = getInstance();

    // Add tick time with delta time.
    time.t += time.fixedDeltaTime;

    // TODO: Create realistic tick.
    /*std::cout << "Elapsed: " << time.clock.getElapsedTime().asSeconds();
    time.time = time.clock.restart();
    std::cout << "; Delta Time: " << time.time.asSeconds() << std::endl;*/
}


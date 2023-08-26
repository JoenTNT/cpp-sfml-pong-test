#include "GameApp.h"

// Main function.
int main() {
	// Get app instance.
	pong::GameApp& app = pong::GameApp::getInstance();

	// Make the app awake.
	app.onAwake();

	// Loop run.
	while (app.isRunning()) {
		// Updating the app interface.
		app.onUpdate();
	}

	// End process.
	app.onEnd();

	// Safe exit.
	return 0;
}



//#include <iostream>
//#include <string>
//
//#include <SFML/Graphics.hpp>
//#include <SFML/System.hpp>
//
//using namespace sf;
//using namespace std;
//
//Mutex mutex;
////string filePath = "image.jpg";
//
//void sampleFunc(int value) {
//    mutex.lock();
//
//    for (int i = 0; i < 3; i++) {
//        cout << "Hello World, this is thread: " << value << "; Currently Running at index: " << i << endl;
//    }
//
//    mutex.unlock();
//}
//
//void runThreads() {
//    for (int i = 0; i < 10; i++) {
//        Thread thread(&sampleFunc, i);
//        thread.launch();
//
//        mutex.lock();
//
//        cout << "Running Thread (" << i << ")" << endl;
//
//        mutex.unlock();
//    }
//}
//
//int main()
//{
//    RenderWindow window(VideoMode(1280, 720), "SFML works!");
//    window.setVerticalSyncEnabled(true);
//    window.setFramerateLimit(60);
//
//    CircleShape shape(100.f);
//    shape.setFillColor(Color::Green);
//    shape.setPosition(Vector2f(20.f, 20.f));
//
//    // Running threads.
//    runThreads();
//
//    /*sf::FileInputStream stream;
//    if (stream.open(filePath))
//    {
//        char buffer[256];
//        stream.getSize()
//        stream.read(buffer, sizeof(buffer));
//    }*/
//
//    Texture texture;
//    if (!texture.loadFromFile("image.jpg"))
//    {
//        cout << "Load Texture File Failed! File not exists." << endl;
//        return -1;
//    }
//    texture.setSmooth(true);
//
//    // Create sprite.
//    Sprite sprite;
//    sprite.setTexture(texture);
//    sprite.scale(Vector2f(.5f, .8f));
//
//    // Main clock.
//    Clock clock;
//    while (window.isOpen())
//    {
//        // Delta time.
//        Time deltaTime = clock.restart();
//        
//        Event ev;
//        while (window.pollEvent(ev))
//        {
//            if (ev.type == Event::Closed)
//                window.close();
//        }
//
//        // Update texture in runtime.
//        //texture.update(window);
//
//        window.clear();
//
//        // Render sprite in window.
//        window.draw(sprite);
//
//        window.draw(shape);
//        window.display();
//    }
//
//    return 0;
//}
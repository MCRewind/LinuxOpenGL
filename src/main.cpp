
#include "GamePanel.h"
#include "Window.h"
#include "Camera.h"
#include "Panel.h"

#include <GLFW/glfw3.h>

#include <iostream>
#include <stdio.h>

void update();
void render();
void checkState();
void init();
int state;
Panel* panels[1];
Window* window;
Camera* camera;

int main()
{
	/*double lastTime = glfwGetTime();
	int nbFrames = 0;

	init();

	while (!window->shouldClose())
	{
		double currentTime = glfwGetTime();
		nbFrames++;
		if (currentTime - lastTime >= 1.0)
		{
			printf("%f ms/frame\n", 1000.0 / double(nbFrames));
			nbFrames = 0;
			lastTime += 1.0;
		}
		update();
		render();
	}*/
	static double limitFPS = 1.0 / 60.0;

	double lastTime = glfwGetTime(), timer = lastTime;
	double deltaTime = 0, nowTime = 0;
	int frames = 0, updates = 0;

	init();

	// - While window is alive
	while (!window->shouldClose()) {

		// - Measure time
		nowTime = glfwGetTime();
		deltaTime += (nowTime - lastTime) / limitFPS;
		lastTime = nowTime;

		// - Only update at 60 frames / s
		while (deltaTime >= 1.0) {
			update();   // - Update function
			updates++;
			deltaTime--;
		}
		// - Render at maximum possible frames
		render(); // - Render function
		frames++;

		// - Reset after one second
		if (glfwGetTime() - timer > 1.0) {
			timer++;
			std::cout << "FPS: " << frames << " Updates:" << updates << std::endl;
			updates = 0, frames = 0;
		}

	}
	delete window;
	delete camera;
}

void init()
{
	window = new Window(1080, 720, "test", true, true);
	camera = new Camera(1080, 720);
	panels[0] = new GamePanel(window, camera);
	state = 0;
}

void update()
{
	checkState();
	window->update();
	panels[state]->update();
	if (window->isKeyPressed(GLFW_KEY_ESCAPE))
		window->close();
}

void render()
{
	window->clear();
	panels[state]->render();
	window->swap();
}

void checkState()
{
	int tempState = panels[state]->getState();
	if (state != tempState)
	{
		switch(tempState)
		{
			default:
				panels[tempState]->setActive();
		}
		state = tempState;
	}
}

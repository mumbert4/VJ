#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"


void Game::init()
{
	bPlay = true;
	glClearColor(.0f, .0f, .0f, 1.0f);
	/*SoundManager::instance().init();
	engine = SoundManager::instance().getSoundEngine();
	irrklang::ISound* sound = engine->play2D("sounds/menu-sound.mp3", true, false, true);*/
	//sound->setVolume(0.5f);
	//scene.init();
	pos = 0;
	state = 0;
	menu.init();
}

bool Game::update(int deltaTime)
{
	//scene.update(deltaTime);
	menu.update(deltaTime);
	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//scene.render();
	menu.render();
}

void Game::keyPressed(int key)
{
	

	if (key == 27) { // Escape code
		if (state == 1 || state == 2) {
			menu.changeState(0);
			state = 0;
		}
		else
			bPlay = false;
	}
	keys[key] = true;

	if (key == 13) {//tecla enter-> per seleccionar la pantalla que volem
		if (pos == 0) {
			Scene.init()
		}
		else {

		}
		menu.changeState(pos);
		state = pos;
	}
	/*if (key == 112)engine->setAllSoundsPaused(true); //p-> pausa tots els renous
	if (key == 117)engine->setAllSoundsPaused(false);*/ //u -> activa tots els renous


}

void Game::keyReleased(int key)
{
	keys[key] = false;
}

void Game::specialKeyPressed(int key)
{
	if (key == GLUT_KEY_UP) {
		if (pos > 0) {
			pos -= 1;
			menu.setPosIndex(pos);
		}
	}
	else if (key == GLUT_KEY_DOWN) {
		if (pos < 2) {
			pos += 1;
			menu.setPosIndex(pos);
			
		}
	}
	else if (key == GLUT_KEY_LEFT && state==2){
		menu.changeInstruction(0);
		
	}
	else if (key == GLUT_KEY_LEFT && state==2) {
		menu.changeInstruction(1);
		
	}

		

	
	
	specialKeys[key] = true;

}

void Game::specialKeyReleased(int key)
{
	specialKeys[key] = false;
}

void Game::mouseMove(int x, int y)
{

}

void Game::mousePress(int button)
{
}

void Game::mouseRelease(int button)
{
}

bool Game::getKey(int key) const
{
	return keys[key];
}

bool Game::getSpecialKey(int key) const
{
	return specialKeys[key];
}






#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"

#define _USE_MATH_DEFINES
#include <math.h>


#define SCREEN_X 32
#define SCREEN_Y 16

#define INIT_PLAYER_X_TILES 10
#define INIT_PLAYER_Y_TILES 4






Scene::Scene()
{
	map = NULL;
	player = NULL;
}

Scene::~Scene()
{
	if(map != NULL)
		delete map;
	if(player != NULL)
		delete player;
	for (int i = 0; i < 10; i++)
		if (enemies[i] != NULL)
			delete enemies[i];
}


void Scene::init()
{
	initShaders();
	map = TileMap::createTileMap("levels/level01.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	player = new Player();
	enemies[0] = new Enemy();
	enemies[1] = new Enemy();
	enemies[2] = new Enemy();
	enemies[3] = new Enemy();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	player->setTileMap(map);
	enemies[0]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	enemies[0]->setPosition(glm::vec2(25 * map->getTileSize(),12 * map->getTileSize()));
	enemies[0]->setTileMap(map);
	enemies[1]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	enemies[1]->setPosition(glm::vec2(10 * map->getTileSize(), 12 * map->getTileSize()));
	enemies[1]->setTileMap(map);
	enemies[2]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	enemies[2]->setPosition(glm::vec2(27 * map->getTileSize(), 24 * map->getTileSize()));
	enemies[2]->setTileMap(map);
	enemies[3]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	enemies[3]->setPosition(glm::vec2(8 * map->getTileSize(), 24* map->getTileSize()));
	enemies[3]->setTileMap(map);
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;

	if (!text.init("fonts/OpenSans-Regular.ttf"))
		cout << "Could not load font!!!" << endl;

	temps_ini = currentTime;
	puntuacio = 0;
	player->setVides(3);


}

void Scene::comprovar_temps(int deltaTime) {
	currentTime += deltaTime;
	temps_actual = 60 - ((currentTime - temps_ini) / 1000);
	if (temps_actual <= 0) derrota = true;

}

void Scene::comprovar_victoria_derrota() {
	if (derrota || player->getVides() <= 0) {
		//////////////// CONDICIO DERROTA
		/*
		Reiniciar o saltar a menu
		
		*/
		temps_actual = -666;

	}
	else if (victoria) {
		/////////////// CONDICIO VICTORIA
		/*
		puntuacio += temps_actual * 10;
		Saltar al seeguent o menu
		
		*/

	}
}


bool Scene::comprovar_mort(Player* jugador, Enemy* enemics) {

	if (player->getMorint()) return true;

	else {
		glm::vec2 pos = player->getPosition();

		for (int i = 0; i < 10; i++) {
			if (enemies[i] != NULL) {
				glm::vec2 posE = enemies[i]->getPosition();

				if (pos.x == posE.x && pos.y == posE.y) return true;

			}
		}

	}
	return false;
}






void Scene::update(int deltaTime)
{
	comprovar_temps(deltaTime);
	player->update(deltaTime);
	enemies[0]->update(deltaTime);
	enemies[1]->update(deltaTime);
	enemies[2]->update(deltaTime);
	enemies[3]->update(deltaTime);

	bool morint = comprovar_mort(player, *enemies);
	player->setMorint(morint);
	
	if (player->getMorint()) {
		player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
		player->setVides(player->getVides() - 1);
		player->setMorint(false);
	}

	comprovar_victoria_derrota();
}

void Scene::render()
{
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);

	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);

	map->render();
	player->render();

	float enemy_pos = (sin(currentTime / 500.f) / 10);
	float enemy_pos_aux = -(sin(currentTime / 500.f) / 10);
	enemies[0]->setPosition(glm::vec2((25 * map->getTileSize() + 400 * enemy_pos_aux), 12 * map->getTileSize()));
	enemies[0]->setOrientation(-cos(currentTime / 500.f) / 10);
	enemies[0]->render();
	enemies[1]->setPosition(glm::vec2((10 * map->getTileSize() + 400 * enemy_pos), 12 * map->getTileSize()));
	enemies[1]->setOrientation(cos(currentTime / 500.f) / 10);
	enemies[1]->render();
	enemies[2]->setPosition(glm::vec2((27 * map->getTileSize() + 400 * enemy_pos_aux), 24 * map->getTileSize()));
	enemies[2]->setOrientation(-cos(currentTime / 500.f) / 10);
	enemies[2]->render();
	enemies[3]->setPosition(glm::vec2((8 * map->getTileSize() + 400 * enemy_pos), 24 * map->getTileSize()));
	enemies[3]->setOrientation(cos(currentTime / 500.f) / 10);
	enemies[3]->render();

	text.render(to_string(int(temps_actual)), glm::vec2(CAMERA_WIDTH / 2, 50), 30, glm::vec4(1, 1, 1, 1));
	text.render("Vides: " + to_string(int(player->getVides())), glm::vec2(CAMERA_WIDTH - 150, 50), 30, glm::vec4(1, 1, 1, 1));
	text.render("Puntuacio: " + to_string(puntuacio), glm::vec2(50, 50), 30, glm::vec4(1, 1, 1, 1));

	//text.render("Enemic", glm::vec2(enemy_pos + 235.f, 280.f), 20, glm::vec4(1, 1, 1, 1));
}

void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if(!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if(!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if(!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}




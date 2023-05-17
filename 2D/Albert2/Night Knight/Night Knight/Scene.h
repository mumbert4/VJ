#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "Enemy.h"
#include "Text.h"

#define CAMERA_WIDTH 640
#define CAMERA_HEIGHT 480


class Scene
{

public:
	Scene();
	~Scene();

	void init();
	void update(int deltaTime);
	void render();
	void comprovar_temps(int deltaTime);
	void comprovar_victoria_derrota();
	bool comprovar_mort(Player* jugador, Enemy* enemics);

private:
	void initShaders();

private:
	TileMap *map;
	Player *player;
	Enemy *enemies[10];
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
	Text text;
	float temps_ini, temps_actual;
	bool victoria, derrota;
	int puntuacio;
};


#endif // _SCENE_INCLUDE


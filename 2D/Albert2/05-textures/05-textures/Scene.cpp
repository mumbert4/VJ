#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"


Scene::Scene()
{
	quad = NULL;
}

Scene::~Scene()
{
	if(quad != NULL)
		delete quad;
	for(int i=0; i<3; i++)
		if(texQuad[i] != NULL)
			delete texQuad[i];
}


void Scene::init()
{
	glm::vec2 geom[2] = {glm::vec2(0.f, 0.f), glm::vec2(128.f, 128.f)};
	glm::vec2 texCoords[2] = {glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f)};

	//cel
	initShaders();
	quad = Quad::createQuad(0.f, 0.f, 1.f, 1.f, simpleProgram);

	//bolet
	texCoords[0] = glm::vec2(0.f, 0.5f); texCoords[1] = glm::vec2(0.5f, 1.f);
	texQuad[0] = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);

	//terra
	texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(5.f, 1.f);
	texQuad[1] = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);

	// Load textures
	texs[0].loadFromFile("images/varied.png", TEXTURE_PIXEL_FORMAT_RGBA);
	texs[1].loadFromFile("images/brick.png", TEXTURE_PIXEL_FORMAT_RGBA);
	projection = glm::ortho(0.f, float(CAMERA_WIDTH - 1), float(CAMERA_HEIGHT - 1), 0.f);
	currentTime = 0.0f;

}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
}

void Scene::render()
{
	glm::mat4 modelview;

	simpleProgram.use();
	simpleProgram.setUniformMatrix4f("projection", projection);
	simpleProgram.setUniform4f("color", 0.2f, 0.8f, 0.8f, 1.0f);

	//cel
	modelview = glm::scale(modelview, glm::vec3(640, 480, 0.f));
	simpleProgram.setUniformMatrix4f("modelview", modelview);
	quad->render();

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);

	//bolet
	modelview = glm::translate(glm::mat4(1.0f), glm::vec3(195.f, 255.f, 0.f));
	modelview = glm::translate(modelview, glm::vec3((sin(currentTime / 500.f)) * 285.f + 60.f, 0.0f, 0.0f));
	texProgram.setUniformMatrix4f("modelview", modelview);
	texQuad[0]->render(texs[0]);

	//terra
	modelview = glm::translate(glm::mat4(1.0f), glm::vec3(0.f, 352.f, 0.f));
	modelview = glm::scale(modelview, glm::vec3(5.f, 1.f, 0.f));
	texProgram.setUniformMatrix4f("modelview", modelview);
	texQuad[1]->render(texs[1]);

}

void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/simple.vert");
	if(!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/simple.frag");
	if(!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	simpleProgram.init();
	simpleProgram.addShader(vShader);
	simpleProgram.addShader(fShader);
	simpleProgram.link();
	if(!simpleProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << simpleProgram.log() << endl << endl;
	}
	simpleProgram.bindFragmentOutput("outColor");

	vShader.free();
	fShader.free();
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
}


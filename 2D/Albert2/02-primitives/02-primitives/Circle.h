#ifndef _CIRCLE_INCLUDE
#define _CIRCLE_INCLUDE


#include "ShaderProgram.h"


class Circle
{

private:
	Circle(float x, float y, float r, ShaderProgram& program);

public:

	static Circle* createCircle(float x, float y, float r, ShaderProgram& program);

	void render() const;
	void free();

private:
	GLuint vao;
	GLuint vbo;
	GLint posLocation;
	int num_tri = 64;

};


#endif // _CIRCLE_INCLUDE
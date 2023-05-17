#include <GL/glew.h>
#include <GL/gl.h>
#include "Circle.h"

#define _USE_MATH_DEFINES
#include <math.h>


Circle* Circle::createCircle(float x, float y, float r, ShaderProgram& program)
{
	Circle* circle = new Circle(x, y, r, program);

	return circle;
}


Circle::Circle(float x, float y, float r, ShaderProgram& program)
{
	float *vertices = new float[num_tri*6];
	float angle = 2*M_PI/num_tri;
	int i = 0;
	int add = 0;

	while (i < num_tri*6) {
		vertices[i++] = x;
		vertices[i++] = y;
		vertices[i++] = x + r*sin(angle*add);
		vertices[i++] = y + r*cos(angle*add);
		++add;
		vertices[i++] = x + r*sin(angle*add);
		vertices[i++] = y + r*cos(angle*add);
	}

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, num_tri*6*sizeof(float), vertices, GL_STATIC_DRAW);
	posLocation = program.bindVertexAttribute("position", 2);
}

void Circle::render() const
{
	glBindVertexArray(vao);
	glEnableVertexAttribArray(posLocation);


	glDrawArrays(GL_TRIANGLES, 0, num_tri*3);


}

void Circle::free()
{
	glDeleteBuffers(1, &vbo);
}
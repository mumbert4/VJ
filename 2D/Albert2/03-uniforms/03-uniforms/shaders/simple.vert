#version 330

in vec2 position;
uniform vec2 scalar ;

void main()
{
	gl_Position = vec4(position*scalar, 0.0, 1.0);
}

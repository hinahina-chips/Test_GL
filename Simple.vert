#version 330 core

varying vec3 v_normal;


void main(void)
{
  v_normal = normalize(gl_NormalMatrix * gl_Normal);

  gl_Position = ftransform();

  gl_FrontColor = gl_Color;

  gl_ClipVertex = gl_ModelViewMatrix * gl_Vertex;
}
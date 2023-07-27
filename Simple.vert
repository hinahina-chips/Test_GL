#version 330 core

in vec3 vertexPosition;
in vec3 vertexNormal;
in vec2 vertexUv;

out vec3 position;
out vec3 normal;
out vec2 uv;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main(void)
{
  normal = mat3(transpose(inverse(modelMatrix))) * vertexNormal;
  uv = vertexUv;

  // モデル行列、ビュー行列、プロジェクション行列を使ってMVP行列を計算する
  mat4 mvpMatrix = projectionMatrix * viewMatrix * modelMatrix;
  position = (mvpMatrix * vec4(vertexPosition, 1.0)).xyz;

  gl_Position = vec4(vertexPosition, 1.0);
}

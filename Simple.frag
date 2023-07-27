#version 330 core

in vec3 position; // 頂点シェーダーから受け取る頂点座標
in vec3 normal;   // 頂点シェーダーから受け取る法線ベクトル
in vec2 uv;       // 頂点シェーダーから受け取るテクスチャ座標

out vec4 fragColor;

uniform sampler2D texture;


float NormToUV(float n)
{
  float t = 0.5 + n * 0.5;
  if (!gl_FrontFacing)
    t = 1.0 - t;

  return t;
}

vec4 GetMatcapColor()
{
  vec3 n = normalize(normal);
  float tx = NormToUV(n.x);
  float ty = NormToUV(-n.y);

  vec4 env_texcoord = vec4(tx, ty, 0.0, 1.0);
  return texture2DProj(texture, env_texcoord);
}

void main (void)
{
  fragColor = GetMatcapColor();
}
#version 330 core

in vec3 position; // ���_�V�F�[�_�[����󂯎�钸�_���W
in vec3 normal;   // ���_�V�F�[�_�[����󂯎��@���x�N�g��
in vec2 uv;       // ���_�V�F�[�_�[����󂯎��e�N�X�`�����W

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
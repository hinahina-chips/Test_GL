#version 330 core

varying vec3 v_normal;

uniform sampler2D tex_matcap;


float NormToUV(float n)
{
  float t = 0.5 + n * 0.5;
  if (!gl_FrontFacing)
    t = 1.0 - t;

  return t;
}

vec4 GetMatcapColor()
{
  vec3 n = normalize(v_normal);
  float tx = NormToUV(n.x);
  float ty = NormToUV(-n.y);

  vec4 env_texcoord = vec4(tx, ty, 0.0, 1.0);
  return texture2DProj(tex_matcap, env_texcoord);
}

void main (void)
{
  gl_FragColor = GetMatcapColor();
}
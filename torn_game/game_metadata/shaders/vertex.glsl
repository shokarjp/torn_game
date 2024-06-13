#version 330
layout (location = 0) in vec3 i_pos;
layout (location = 1) in vec4 i_color;
layout (location = 2) in vec2 i_uv;
layout (location = 3) in vec4 i_normals;
uniform mat4 orthographic;
uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;
out vec4 v_pos;
out mat4 mvp;
out vec4 v_color;
out vec2 v_uv;


void main()
{
  v_uv = i_uv;
  v_color = i_color;
  mvp = orthographic * model * view;
  v_pos = vec4(i_pos, 1.0) * mvp;
  gl_Position = mvp * vec4(i_pos, 1);
}
    
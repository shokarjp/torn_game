
#version 330
out vec4 f_color;
in vec4 v_color;
in vec2 v_uv;
in vec4 v_pos;
in mat4 mvp;

uniform sampler2D t_texture2d;
uniform vec2 u_lightpos;
uniform vec2 u_res;
 
void main() {
        
    vec4 pixel = texture(t_texture2d, v_uv);      
     // oversaturation (*1.3) to mimic old CRT monitors oversaturation.
     f_color = v_color * pixel   *1.3;
 
 
 

 
   
}
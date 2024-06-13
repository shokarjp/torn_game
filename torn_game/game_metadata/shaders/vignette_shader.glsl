
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
        
    vec4 color = texture(t_texture2d, v_uv);
    float dist_from_origin = distance(v_uv, vec2(0.5,0.5));
    color.rgb *= smoothstep(0.8, 0.0799, (dist_from_origin * 1.5f)-0.25F);
    f_color = color;
 
 

 
   
}
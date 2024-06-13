
#version 330
out vec4 f_color;
in vec4 v_color;
in vec2 v_uv;
in vec4 v_pos;
in mat4 mvp;

uniform sampler2D t_texture2d;
uniform vec2 u_lightpos;
uniform vec2 u_res;
 
  // Attributions: https://babylonjs.medium.com/retro-crt-shader-a-post-processing-effect-study-1cb3f783afbc
  vec4 scanLineIntensity(float uv, float resolution, float opacity)
 {
     float intensity = 0.50 * sin(uv * resolution * 3.14 * 2.0);
     intensity = ((0.5 * intensity) + 0.5);
     return vec4(vec3(pow(intensity, opacity)), 1.0);
 }
void main() {
        
    vec4 ambient = vec4(0.02, 0.02, 0.2, 0);
    vec2 light_pos = vec2(u_res.x,u_res.y);
    light_pos = ( mvp * vec4(light_pos, 0, 1) ).xy;        
    vec2 light_frag = light_pos - v_pos.xy;
    light_frag.y /= 1.0;    
    float vec_length = clamp(length(light_frag) / 1.5, 0, 1);   



    // Attributions: https://babylonjs.medium.com/retro-crt-shader-a-post-processing-effect-study-1cb3f783afbc
    vec2 new_uv;
    new_uv = v_uv * 2.0 - 1.0;
    vec2 offset = abs(new_uv.yx) / vec2(3.0,3.0);
    new_uv = new_uv + new_uv * offset * offset;
    new_uv = new_uv * 0.5 + 0.5;


    vec4 pixel = texture(t_texture2d, new_uv); 
              pixel *= scanLineIntensity(new_uv.x, u_res.y, 0.25);
     pixel *= scanLineIntensity(new_uv.y, u_res.x, 0.25);

    f_color = (pixel * v_color * ( clamp(ambient + vec4(1-vec_length, 1-vec_length, 1-vec_length, 1), 0, 1))) * 2.0;
}
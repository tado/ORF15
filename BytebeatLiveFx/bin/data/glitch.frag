#extension GL_EXT_gpu_shader4 : enable
#extension GL_ARB_texture_rectangle : enable

uniform sampler2DRect u_tex_unit0;
uniform float u_time;
uniform float rand;
varying vec3 pos;

void main( void ){
  float level = 0.0;
  float freq = 1000.;
  vec2 texCoord = vec2(pos.x, pos.y);
  vec4 col = texture2DRect(u_tex_unit0, texCoord);
  vec4 col_s = texture2DRect(u_tex_unit0, texCoord
                             + vec2(floor((sin(pos.y/freq+rand*level)-0.5)*2.),0.0)*level
                             - vec2(floor((cos(pos.x/freq-rand*level)-0.5)*2.),0.0)*level
                             );
  col = col_s;
  gl_FragColor.rgba = col.rgba;
}

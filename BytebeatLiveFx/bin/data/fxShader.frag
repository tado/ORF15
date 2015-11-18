#version 120
#extension GL_ARB_texture_rectangle : enable

uniform sampler2DRect u_tex_unit0;
uniform float u_time;

void main( void ){
  float newTime = u_time * 0.1;

  vec2 newTexCoord;
  newTexCoord.s = gl_TexCoord[0].s + (cos(newTime + (gl_TexCoord[0].s*0.1)) * 10.0);
  newTexCoord.t = gl_TexCoord[0].t + (sin(newTime + (gl_TexCoord[0].t*0.1)) * 10.0);

  vec2 texCoordRed 	= newTexCoord;
  vec2 texCoordGreen 	= newTexCoord;
  vec2 texCoordBlue 	= newTexCoord;

  texCoordRed 	+= vec2( cos((newTime * 2.76)), sin((newTime * 2.12)) ) * 10.0;
  texCoordGreen	+= vec2( cos((newTime * 2.23)), sin((newTime * 2.40)) ) * 10.0;
  texCoordBlue 	+= vec2( cos((newTime * 2.98)), sin((newTime * 2.82)) ) * 10.0;

  float colorR = texture2DRect( u_tex_unit0, texCoordRed ).r;
  float colorG = texture2DRect( u_tex_unit0, texCoordGreen).g;
  float colorB = texture2DRect( u_tex_unit0, texCoordBlue).b;

  gl_FragColor = vec4( colorR, colorG, colorB, 1.0 );
}

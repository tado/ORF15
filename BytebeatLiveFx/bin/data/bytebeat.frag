#extension GL_EXT_gpu_shader4 : enable
const int width = 1920*1080;
void main() {
  int t = int(gl_FragCoord.y) * width + int(gl_FragCoord.x);

  int v =
    (t>>6|t<<1)
    ^ (t<<2)
    ;

  gl_FragColor = vec4(vec3(float(v % 256) / 256.),1.);

}

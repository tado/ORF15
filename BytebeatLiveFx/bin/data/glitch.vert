varying vec3 pos;
void main(void){
    pos = gl_Vertex.xyz;
    gl_TexCoord[0] = gl_MultiTexCoord0;
    gl_Position    = ftransform();
}

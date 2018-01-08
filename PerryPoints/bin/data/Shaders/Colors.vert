#version 120
#extension GL_ARB_texture_rectangle : enable
#extension GL_EXT_gpu_shader4 : enable

varying vec2 texCoord;

void main() {
	vec4 pos = gl_Vertex;
    gl_Position = gl_ModelViewProjectionMatrix * pos;
    gl_TexCoord[0] = gl_MultiTexCoord0;
    gl_FrontColor = gl_Color;
    vec2 baseCoord = gl_Vertex.xy;
    texCoord = baseCoord;
}

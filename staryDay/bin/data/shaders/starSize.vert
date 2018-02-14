#version 120
#extension GL_ARB_texture_rectangle : enable
#extension GL_EXT_gpu_shader4 : enable

attribute float point_size;
varying float col;

void main() {
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    gl_PointSize = point_size;
    col = point_size / 3.0; 
    //gl_TexCoord[0] = gl_MultiTexCoord0;
    //gl_FrontColor = gl_Color;
}

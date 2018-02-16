#version 120
#extension GL_ARB_texture_rectangle : enable
#extension GL_EXT_gpu_shader4 : enable

attribute float point_size;
varying vec3 col;
uniform float distanceToCenter;
uniform float starDensity;
uniform float maxSize;

float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main() {
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    float pointSize = point_size;
    float r = rand(gl_Vertex.xy);
    if(r > starDensity)
        pointSize = 0.0;
    gl_PointSize = pointSize * distanceToCenter * maxSize + r;
    col = gl_Color.rgb;
}

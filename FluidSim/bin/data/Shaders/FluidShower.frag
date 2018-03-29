#version 120

#define RotNum 5
#define angRnd 0.0
#define posRnd 0.0

#define SQRT2 1.4142135

uniform sampler2DRect texSolver;
uniform vec3 col1;
uniform vec3 col2;
uniform vec3 col3;
uniform vec3 col4;

float map(float value, float low1, float high1, float low2, float high2) {
    return low2 + (value - low1) * (high2 - low2) / (high1 - low1);
}

float length(vec2 v) {
    return sqrt(v.x*v.x + v.y*v.y);
}

float average(vec2 v) {
    return (v.x + v.y) / 2;
}

void main() {
    vec2 uv = gl_FragCoord.xy;
    
    vec3 vel = texture2DRect(texSolver, uv).xyz;
    
    vec2 v = vel.xy;
    
    v.x = map(vel.x, 0.0, 1.0, -1.0, 1.0);
    v.y = map(vel.y, 0.0, 1.0, -1.0, 1.0);
    
    v = abs(v);

    vec3 col;
    vec3 colY;
    vec3 colX;

    colY = mix(col3, col4, vel.y);
    
    // colX = mix(col1, col2, vel.x);
    
    col = colY;//(v.x > v.y) ? colX : colY;
    
//    float mag = length(vel);

    col = mix(vec3(1.0), col, length(v));
    
    gl_FragColor = vec4(col, 1.0);
}

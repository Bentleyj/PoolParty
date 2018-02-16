#version 120

#define RotNum 5
#define angRnd 0.0
#define posRnd 0.0

uniform sampler2DRect texSolver;
uniform vec3 col1;
uniform vec3 col2;
uniform vec3 col3;
uniform vec3 col4;

float map(float value, float low1, float high1, float low2, float high2) {
    return low2 + (value - low1) * (high2 - low2) / (high1 - low1);
}

void main() {
    vec2 uv = gl_FragCoord.xy;
    
    vec3 vel = texture2DRect(texSolver, uv).xyz;
    
    vec3 col;
    vec3 colY;
    vec3 colX;

    colY = mix(col3, col4, vel.y);
    
    colX = mix(col1, col2, abs(vel.x));
    
    col = mix(colX, colY, vel.y);
    
    float mag = (vel.x + vel.y) / 2.0;

    col = mix(col, vec3(0.0), map(abs(0.5 - mag), 0.0, 0.05, 1.0, 0.0));
    
    gl_FragColor = vec4(col, 1.0);
}

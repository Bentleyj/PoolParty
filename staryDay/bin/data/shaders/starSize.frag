#version 120

varying vec3 col;

void main() {
    
    vec2 uv = gl_FragCoord.xy;
    
    gl_FragColor = vec4(col, 1.0);
}

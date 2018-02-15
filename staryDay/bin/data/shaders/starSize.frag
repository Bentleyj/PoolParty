#version 120

varying float col;
uniform float maxSize;

void main() {
    
    vec2 uv = gl_FragCoord.xy;
    
    float c = col * maxSize;
        
    gl_FragColor = vec4(vec3(c), 1.0);
}

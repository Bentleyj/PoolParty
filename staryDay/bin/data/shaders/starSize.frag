#version 120

varying float col;

void main() {
    
    vec2 uv = gl_FragCoord.xy;
        
    gl_FragColor = vec4(vec3(col), 1);
}

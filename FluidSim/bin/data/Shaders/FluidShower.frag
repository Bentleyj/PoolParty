#version 120

#define RotNum 5
#define angRnd 0.0
#define posRnd 0.0

uniform sampler2DRect inputTexture1;
uniform vec2 resolution;

void main() {
    
    vec2 uv = gl_FragCoord.xy;
    //vec2 uvAbs = uv * resolution;
    
    vec3 vel = texture2DRect(inputTexture1, uv).xyz;
    
    
    
    gl_FragColor = vec4(vel.y, vel.y, vel.y, 1.0);
}

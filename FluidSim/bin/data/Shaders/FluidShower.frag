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
    
//    vel.y = abs(vel.y);
//    if(vel.y < 0.5)
//        vel.y = 0.0;
    
    //vel.y = map(vel.y, 0.0, 1.0, -1.0, 1.0);
    
    gl_FragColor = vec4(vel.y, vel.y, vel.y, 1.0);
}

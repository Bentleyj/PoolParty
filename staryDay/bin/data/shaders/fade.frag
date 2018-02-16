#version 120

uniform sampler2DRect lastFrame;
uniform sampler2DRect thisFrame;
uniform float percent;
uniform float threshold;

float length(vec3 v) {
    return (v.x + v.y + v.z) / 3.0;
}

void main() {
    
    vec2 uv = gl_FragCoord.xy;
    
    vec3 lastCol = texture2DRect(lastFrame, uv).rgb;
    vec3 thisCol = texture2DRect(thisFrame, uv).rgb;

    
    vec3 col = thisCol + lastCol * percent;
    if(length(col) < threshold)
        col = vec3(0.0);
    
    gl_FragColor = vec4(col, 1.0);
}

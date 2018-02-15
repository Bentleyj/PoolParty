#version 120

uniform sampler2DRect lastFrame;
uniform sampler2DRect thisFrame;
uniform float percent;

void main() {
    
    vec2 uv = gl_FragCoord.xy;
    
    vec3 lastCol = texture2DRect(lastFrame, uv).rgb;
    vec3 thisCol = texture2DRect(thisFrame, uv).rgb;

    
    vec3 col = thisCol + lastCol * percent;
    
    gl_FragColor = vec4(col, 1.0);
}

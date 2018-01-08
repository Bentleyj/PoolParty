#version 120
#extension GL_ARB_texture_rectangle : enable
#extension GL_EXT_gpu_shader4 : enable

uniform sampler2DRect diffuseTexture;
uniform vec4 areas[20];
uniform vec3 colors[20];

varying vec2 texCoord;

bool isInside(vec2 p, vec4  b) {
    if(p.x < b.x + b.z && p.x > b.x) {
        if(p.y < b.y + b.w && p.y > b.y) {
            return true;
        }
    }
    return false;
}

void main() {
   
	vec4 col = texture2DRect(diffuseTexture, texCoord);
    
    gl_FragColor = col;
}

#version 120
#extension GL_ARB_texture_rectangle : enable
#extension GL_EXT_gpu_shader4 : enable

uniform sampler2DRect diffuseTexture;

varying vec2 texCoord;

void main() {
   
	vec4 col = texture2DRect(diffuseTexture, texCoord);

	//float prob = smoothstep(800, 0.0, dist);

    gl_FragColor = col;
}

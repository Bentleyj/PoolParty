#version 120
#extension GL_ARB_texture_rectangle : enable
#extension GL_EXT_gpu_shader4 : enable

uniform sampler2DRect diffuseTexture;
uniform vec2 midPointDiff;
uniform vec2 midPointVal;
uniform float rot;
uniform float scale;

varying vec2 texCoord;

mat2 rotate2d(float _angle){
    return mat2(cos(_angle),-sin(_angle),
                sin(_angle),cos(_angle));
}

mat2 scale2d(vec2 _scale){
    return mat2(_scale.x,0.0,
                0.0,_scale.y);
}

void main() {
    
	vec2 pos = texCoord;
	pos -= midPointDiff;

	pos -= midPointVal;
	pos = rotate2d(rot) * pos;
	pos = scale2d(vec2(scale)) * pos;
	pos += midPointVal;

	vec4 col;

	//if(pos.x < bounds[0] || pos.x > bounds[1] || pos.y < bounds[2] || pos.y > bounds[3]) {
	//	col = vec4(0, 0, 0, 1);
	//} else {
	col = texture2DRect(diffuseTexture, pos);
	//}

	gl_FragColor = col;
}
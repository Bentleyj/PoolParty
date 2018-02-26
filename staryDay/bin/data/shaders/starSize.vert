uniform float starDensity;
uniform float maxSize;

float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main() {

    gl_Position   = gl_ModelViewProjectionMatrix * gl_Vertex;
	float size    = gl_Normal.x;
	float r = rand(gl_Vertex.xy);
	if(r > starDensity)
		size = 0.0;
    gl_PointSize  = size * maxSize;
    gl_FrontColor = gl_Color;

}
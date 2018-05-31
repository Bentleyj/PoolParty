uniform float starDensity;
uniform float maxSize;
uniform float offsets[32];

float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

vec3 cartToSpher(vec3 p) {
    float ro = sqrt(p.x*p.x+p.y*p.y+p.z*p.z);
    float theta = acos(p.z / ro);
    float phi = atan(p.y, p.x);
    return vec3(ro, theta, phi);
}

vec3 sphereToCart(vec3 p) {
    float x = p.x*sin(p.y)*cos(p.z);
    float y = p.x*sin(p.y)*sin(p.z);
    float z = p.x * cos(p.y);
    return vec3(x, y, z);
}

void main() {

    //gl_Position   = gl_ModelViewProjectionMatrix * gl_Vertex;
    vec4 pos = gl_ModelViewProjectionMatrix * gl_Vertex;
    vec3 sphere = cartToSpher(pos.xyz);
//    sphere.x -= 20.0;
    pos.xyz = sphereToCart(sphere);
    gl_Position = pos;
	float size    = gl_Normal.x;
	float r = rand(gl_Vertex.xy);
	if(r > starDensity)
		size = 0.0;
    gl_PointSize  = size * maxSize;
    gl_FrontColor = gl_Color;

}

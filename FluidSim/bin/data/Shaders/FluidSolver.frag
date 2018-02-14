#version 120

#define RotNum 5
#define angRnd 0.0
#define posRnd 0.0

uniform sampler2DRect inputTexture1;
uniform sampler2DRect randomTexture;
uniform vec2 resolution;

const float ang = 2.0*3.1415926535/float(RotNum);
mat2 m = mat2(cos(ang),sin(ang),-sin(ang),cos(ang));

float hash(float seed) { return fract(sin(seed)*158.5453 ); }
vec4 getRand4(float seed) { return vec4(hash(seed),hash(seed+123.21),hash(seed+234.32),hash(seed+453.54)); }
vec4 randS(vec2 uv)
{
    return texture2DRect(randomTexture,uv*resolution.xy)-vec4(0.5);
}

float getRot(vec2 uv, float sc)
{
    float ang2 = angRnd*randS(uv).x*ang;
    vec2 p = vec2(cos(ang2),sin(ang2));
    float rot=0.0;
    for(int i=0;i<RotNum;i++)
    {
        vec2 p2 = (p+posRnd*randS(uv+p*sc).xy)*sc;
        vec2 v = texture2DRect(inputTexture1,fract(uv+p2) * resolution.xy).xy-vec2(0.5);
        rot+=cross(vec3(v,0.0),vec3(p2,0.0)).z/dot(p2,p2);
        p = m*p;
    }
    rot/=float(RotNum);
    return rot;
}

void main() {
    
    vec2 uv = gl_FragCoord.xy / resolution;
    vec2 uvAbs = uv * resolution;
    
    vec2 scr=uv*2.0-vec2(1.0);
    
    float sc=1.0/max(resolution.x,resolution.y);
    vec2 v=vec2(0);
    for(int level=0;level<20;level++)
    {
        if ( sc > 0.7 ) break;
        float ang2 = angRnd*ang*randS(uv).y;
        vec2 p = vec2(cos(ang2),sin(ang2));
        for(int i=0;i<RotNum;i++)
        {
            vec2 p2=p*sc;
            float rot=getRot(uv+p2,sc);
            v+=p2.yx*rot*vec2(-1,1);
            p = m*p;
        }
        sc*=2.0;
    }
    
    vec3 tc = texture2DRect(inputTexture1,fract(uv+v*3.0/resolution.x) * resolution.xy).rgb;
    
    
    // Motor
    if(uv.y < 0.1)
        tc.y = 0.1;
    if(uv.y > 0.9)
        tc.y = 0.9;
    
    gl_FragColor = vec4(tc, 1.0);
}

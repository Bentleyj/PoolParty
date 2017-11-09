#version 120
#extension GL_ARB_texture_rectangle : enable
#extension GL_EXT_gpu_shader4 : enable

uniform sampler2DRect tex0;
uniform sampler2DRect curveTex;
uniform float curveWidth;
uniform float curveHeight;


varying vec2 texCoord;

void main() {
    vec2 pos = gl_TexCoord[0].xy;

    vec3 curvesColor;

    vec4 pixelColor = texture2DRect(tex0, pos);

    curvesColor.r = texture2DRect(curveTex, vec2(pixelColor.r * curveWidth, curveHeight/2)).r;//vec2(pixelColor.r * 0.1, 0)).r;
    curvesColor.g = texture2DRect(curveTex, vec2(pixelColor.g * curveWidth, curveHeight/2)).g;//vec2(pixelColor.g, 0)).g;
    curvesColor.b = texture2DRect(curveTex, vec2(pixelColor.b * curveWidth, curveHeight/2)).b;//vec2(pixelColor.b, 0)).b;

    
    // vec4 col0 = sharp(diffuseTexture, texCoord);
    
    //vec4 weird = abs( col0 - col1 ) * weirdness * 100.0;
    //weird = vec4(1.0) - weird;
    //weird.a = 1.0;

    gl_FragColor = vec4(curvesColor, 1.0);
}
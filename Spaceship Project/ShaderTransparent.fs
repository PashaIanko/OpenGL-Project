#version 110

varying vec2 uv1;
varying vec4 transparency;
uniform sampler2D texture1;


void main()
{
	vec2 uv1Scale = vec2(1.0, 1.0);
	vec4 col = texture2D( texture1, uv1.xy * uv1Scale ).rgba;
    
	
	/*if(col.a < 0.1)
        discard;*/ // if alpha component < 0.1
	
	gl_FragColor.rgb = col.rgb * col.a;
	//gl_FragColor.a = 0.5; // Setting the alpha-component
    gl_FragColor.a = transparency.a; 
}

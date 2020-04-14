#version 110

varying vec2 uv1;
varying float texture_flag;

uniform sampler2D textureEarth;

uniform sampler2D TextureSpaceUp;
uniform sampler2D TextureSpaceBottom;
uniform sampler2D TextureSpaceLeft;
uniform sampler2D TextureSpaceRight;
uniform sampler2D TextureSpaceFront;
uniform sampler2D TextureSpaceBack;


// ���������� ������� ���
//void main()
//{
//    vec2 uv1Scale = vec2(1, 1); // � 50 ��� ������������ �������� uv ���������
//    // vec2 uv1scale = vec2(1 10) * vec2(3 3 );
//    vec3 color1 = texture2D( textureEarth, uv1.xy * uv1Scale ).rgb; // ������ �������, ����� � color, uvScale - �� ����� ���������� ����� ������� ������� � � � - �� 0 �� 1
//    //vec3 color1 = texture2D( TextureSpaceBottom, uv1.xy * uv1Scale ).rgb; 
//    //	vec3 color2 = texture2D( texture2, uv1.xy * uv1Scale ).rgb; - ���������� ������ ������
//    // ��� ��������� - ����� - �� 0 �� 1. ����� �� ���������� � �� ��� ������, ����� ������������ � FragColor. ���� �����������, �� �� ����������� ��������� ��� ��������� �������. 
//    // ���� �����������

//    gl_FragColor.rgb = color1;
//    gl_FragColor.a = 1.0;
//}

void main()
{
    vec2 uv1Scale = vec2(1, 1); // � 50 ��� ������������ �������� uv ���������
    vec3 color1 = vec3(0.0f, 0.0f, 0.0f);

    if(abs(texture_flag - 1.0f) < 0.01)
    {
        color1 = texture2D( textureEarth, uv1.xy * uv1Scale ).rgb; // ������ �������, ����� � color, uvScale - �� ����� ���������� ����� ������� ������� � � � - �� 0 �� 1
    }
    else
    {
        color1 = texture2D( TextureSpaceLeft, uv1.xy * uv1Scale ).rgb;
    }
    
    
    // ��� ��������� - ����� - �� 0 �� 1. ����� �� ���������� � �� ��� ������, ����� ������������ � FragColor. ���� �����������, �� �� ����������� ��������� ��� ��������� �������. 
    // ���� �����������

    gl_FragColor.rgb = color1;
    gl_FragColor.a = 1.0;
}

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


// Предыдущий рабочий код
//void main()
//{
//    vec2 uv1Scale = vec2(1, 1); // в 50 раз растягиваешь растяжка uv координат
//    // vec2 uv1scale = vec2(1 10) * vec2(3 3 );
//    vec3 color1 = texture2D( textureEarth, uv1.xy * uv1Scale ).rgb; // Доатсёт тексель, кладёт в color, uvScale - по каким текстурным коорд достать тексель х и у - от 0 до 1
//    //vec3 color1 = texture2D( TextureSpaceBottom, uv1.xy * uv1Scale ).rgb; 
//    //	vec3 color2 = texture2D( texture2, uv1.xy * uv1Scale ).rgb; - добавление других цветов
//    // Все параметры - цвета - от 0 до 1. Можно их складывать и на три делить, перед запихиванием в FragColor. Либо перемножать, но на коэффициент домножать для повышения яркости. 
//    // Чаще перемножают

//    gl_FragColor.rgb = color1;
//    gl_FragColor.a = 1.0;
//}

void main()
{
    vec2 uv1Scale = vec2(1, 1); // в 50 раз растягиваешь растяжка uv координат
    vec3 color1 = vec3(0.0f, 0.0f, 0.0f);

    if(abs(texture_flag - 1.0f) < 0.01)
    {
        color1 = texture2D( textureEarth, uv1.xy * uv1Scale ).rgb; // Доатсёт тексель, кладёт в color, uvScale - по каким текстурным коорд достать тексель х и у - от 0 до 1
    }
    else
    {
        color1 = texture2D( TextureSpaceLeft, uv1.xy * uv1Scale ).rgb;
    }
    
    
    // Все параметры - цвета - от 0 до 1. Можно их складывать и на три делить, перед запихиванием в FragColor. Либо перемножать, но на коэффициент домножать для повышения яркости. 
    // Чаще перемножают

    gl_FragColor.rgb = color1;
    gl_FragColor.a = 1.0;
}

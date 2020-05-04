#version 330 core

in vec2 aTexCoord;
out vec4 FragColor;
uniform sampler2D tex;

void main(){
    vec4 color = texture(tex, aTexCoord);
    if(color==vec4(1, 1, 0, 1))
        discard;
    FragColor = color;
}


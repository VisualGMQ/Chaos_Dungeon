#version 330 core
layout (location = 0) in vec2 Pos;
layout (location = 1) in vec2 TexCoord;

out vec2 aTexCoord;

uniform mat4 Ortho;
uniform mat4 Rotate;
uniform mat4 Translate;
uniform mat4 Scale;
uniform mat4 Camera;

void main(){
    gl_Position = Ortho*Translate*Camera*Rotate*Scale*vec4(Pos, 0 ,1);
    aTexCoord = TexCoord;
}

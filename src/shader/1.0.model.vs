#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;
 
out vec3     ourColor;
out vec2     TexCoord;
 
out vec3     FragPos;
out vec3     Normal;
 
uniform mat4  mvp;
uniform mat4   model;
uniform bool  greyMode;
 
void main()
{
  FragPos = vec3(vec4(aPos, 1.0f) * model);
  Normal = mat3(transpose(inverse(model))) * aColor;
 
    gl_Position = vec4(aPos, 1.0f) * mvp;
 
    TexCoord = aTexCoord;
 
    if (greyMode)
      ourColor = vec3((aColor.r + aColor.g + aColor.b) / 3);  
    else
      ourColor = aColor;
}
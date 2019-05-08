#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

in vec3	FragPos;
in vec3	Normal;

uniform sampler2D	myTexture;
uniform float		textureMode;
uniform bool		lightMode;
uniform float		colorMode;


uniform mat4 lightPos;
uniform mat4 viewPos;


void main()
{
	vec3 cMode;
	if (colorMode == 1)
		cMode = vec3((0.5686 + ourColor.x) / 2, (0.6588 + ourColor.y) / 2, (0.8156 + ourColor.z) / 2);
	else if(colorMode == 2)
		cMode = vec3(0.5333, 0.6901, 0.2941) *  Normal;
	else if(colorMode == 3)
		cMode = mix(vec3(0.9686, 0.7921, 0.7882), vec3((Normal.x, Normal.y, Normal.z) / 3), 0.50);
	else
		cMode = ourColor;
	vec3 result = cMode;
	if (lightMode)
	{
		vec3 lightColor = vec3(1.0);
		float ambientStrength = 0.1;
	    vec3 ambient = ambientStrength * lightColor;

	    vec3 lPos = vec3(vec4(0.0, 0.0, 0.0, 1.0) * lightPos);
	    vec3 vPos = vec3(vec4(0.0, 0.0, 10.0, 1.0) * viewPos);


	    float diffuseStrenght = 1;
	    vec3 norm = normalize(Normal);
	    vec3 lightDir = normalize(lPos - FragPos);
	    float diff = max(dot(norm, lightDir), 0.0);
	    vec3 diffuse = diff * lightColor * diffuseStrenght;

	    float specularStrength = 0.5;
	    vec3 viewDir = normalize(vPos - FragPos);
	    vec3 reflectDir = reflect(-lightDir, norm);
	    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	    vec3 specular = specularStrength * spec * lightColor;
	    result = (ambient + diffuse + specular) * cMode;
	}

    FragColor = mix(vec4(result, 1.0f), texture(myTexture, TexCoord), textureMode);
}

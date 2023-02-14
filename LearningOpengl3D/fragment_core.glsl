#version 440

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	sampler2D diffuseTex;
	sampler2D specularTex;
};

////////// Variables //////////
in vec3 vs_position;
in vec3 vs_color;
in vec2 vs_texcoord;
in vec3 vs_normal;

out vec4 fs_color;

////////// Uniforms //////////
uniform Material material;
uniform vec3 lightPos0;
uniform vec3 cameraPos;

////////// Functions //////////
vec4 calculateAmbient(Material material)
{
	return vec4(material.ambient, 1.f);
}
vec4 calculateDiffuse(Material material, vec3 vs_position, vec3 lightPos0, vec3 vs_normal)
{
	vec3 posToLightDirVec = normalize(lightPos0 - vs_position);
	float diffuse = clamp(dot(posToLightDirVec, vs_normal), 0, 1);
	vec3 diffuseFinal = material.diffuse * diffuse;
	return vec4(diffuseFinal, 1.f);
}
vec4 calculateSpecular(Material material, vec3 vs_position, vec3 lightPos0, vec3 vs_normal, vec3 cameraPos)
{
	vec3 lightToPosDirVec = normalize(vs_position - lightPos0);
	vec3 reflectDirVec = normalize(reflect(lightToPosDirVec, normalize(vs_normal)));
	vec3 posToViewDirVec = normalize(cameraPos-vs_position);
	float specularConst = pow(max(dot(posToViewDirVec, reflectDirVec), 0), 20);
	vec3 specularFinal = material.specular * specularConst * texture(material.specularTex, vs_texcoord).rgb;	
	return vec4(specularFinal,1.f);
}
void main()
{
	vec4 ambientFinal = calculateAmbient(material);
	vec4 diffuseFinal = calculateDiffuse(material, vs_position, lightPos0, vs_normal);
	vec4 specularFinal = calculateSpecular(material, vs_position, lightPos0, vs_normal, cameraPos);

	

	fs_color = (
		mix(texture(material.diffuseTex, vs_texcoord),
		texture(material.specularTex, vs_texcoord), 0) *
		(ambientFinal + diffuseFinal + specularFinal)
	);

	/*
	fs_color = (
		mix(texture(material.diffuseTex, vs_texcoord) *
		vec4(vs_color, 1.f), texture(material.specularTex, vs_texcoord) *
		vec4(vs_color, 1.f), 0.4) *
		(ambientFinal + diffuseFinal + specularFinal)
	);
	*/
}
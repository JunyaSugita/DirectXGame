#include "OBJShaderHeader.hlsli"

VSOutput main(float4 pos : POSITION, float3 normal : NORMAL, float2 uv : TEXCOORD)
{
	//float4 wnormal = normalize(mul(world, float4(normal, 0)));
	//float4 wpos = mul(world, pos);

	//VSOutput output;
	//output.svpos = mul(mul(viewproj,world), pos);

	//float3 ambient = m_ambient;
	//float3 diffuse = dot(lightv, wnormal.xyz) * m_diffuse;
	//const float shininess = 4.0f;
	//float3 eyedir = normalize(cameraPos - wpos.xyz);
	//float3 reflect = normalize(-lightv + 2 * dot(-lightv, wnormal.xyz) * wnormal.xyz);
	//float3 specular = pow(saturate(dot(reflect, eyedir)), shininess) * m_specular;
	//output.color.rgb = (ambient + diffuse + specular) * lightcolor;
	//output.color.a = m_alpha;
	//output.uv = uv;

	float4 wnormal = normalize(mul(world, float4(normal, 0)));
	float wpos = mul(world, pos);

	VSOutput output;
	output.svpos = mul(mul(viewproj, world), pos);
	output.worldpos = wpos;
	output.normal = wnormal.xyz;
	output.uv = uv;

	return output;
}
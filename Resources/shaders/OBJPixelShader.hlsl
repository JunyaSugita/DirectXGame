#include "OBJShaderHeader.hlsli"

Texture2D<float4> tex : register(t0);  // 0番スロットに設定されたテクスチャ
SamplerState smp : register(s0);      // 0番スロットに設定されたサンプラー

float4 main(VSOutput input) : SV_TARGET
{
	//テクスチャマッピング
	float4 texcolor = tex.Sample(smp,input.uv);
	//シェーディングによる色

	//光沢度
	const float shininess = 4.0f;
	//頂点から視点のベクトル
	float3 eyedir = normalize(cameraPos - input.worldpos.xyz);
	//ライトに向かうベクトルと法線
	//float3 dotlightnormal = dot(lightv, input.normal);
	//反射光ベクトル
	//float3 reflect = normalize(-lightv + 2 * dotlightnormal * input.normal);
	//環境反射光
	float3 ambient = m_ambient;
	//拡散反射光
	//float3 diffuse = dotlightnormal * m_diffuse;
	//鏡面反射光
	//float3 specular = pow(saturate(dot(reflect, eyedir)), shininess) * m_specular;
	//全てを加算
	float4 shadecolor = float4(ambientColor * ambient, m_alpha);

	for (int i = 0; i < DIRLIGHT_NUM; i++) {
		if (dirLights[i].active) {
			float3 dotlightnormal = dot(dirLights[i].lightv, input.normal);
			float3 reflect = normalize(-dirLights[i].lightv + 2 * dotlightnormal * input.normal);
			float3 diffuse = dotlightnormal * m_diffuse;
			float3 specular = pow(saturate(dot(reflect, eyedir)), shininess) * m_specular;

			shadecolor.rgb += (diffuse + specular) * dirLights[i].lightcolor;
		}
	}

	//シェーディングによる色で描画
	return shadecolor * texcolor;
}
#pragma once
#include <DirectXMath.h>
#include "DirectionalLight.h"
#include "PointLight.h"

class LightGroup
{
	//エイリアス
private:
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

private:
	static ID3D12Device* device;

public:
	//平行光
	static const int DirLightNum = 3;
	//点光源
	static const int PointLightNum = 3;

public:
	struct ConstBufferData
	{
		//環境光の色
		XMFLOAT3 ambientColor;
		float pad1;
		//平行光線用
		DirectionalLight::ConstBufferData dirLights[DirLightNum];
		//点光源
		PointLight::ConstBufferData pointLights[PointLightNum];
	};

	static void StaticInitialize(ID3D12Device* device);

	static LightGroup* Create();

private:
	//定数バッファ
	ComPtr<ID3D12Resource>constBuff_;
	//環境光の色
	XMFLOAT3 ambientColor_ = { 1,1,1 };
	//平行光線の配列
	DirectionalLight dirLights_[DirLightNum];
	//点光源の配列
	PointLight pointLights_[PointLightNum];
	//ダーティフラグ
	bool dirty_ = false;

public:
	void Initialize();

	void TransferConstBuffer();

	void Update();

	void DefaultLightSetting();

	void Draw(ID3D12GraphicsCommandList* cmdList, UINT rootParameterIndex);

	void SetAmbientColor(const XMFLOAT3& color);
	//平行光
	void SetDirLightActive(int index, bool active);
	void SetDirLightDir(int index,const XMVECTOR& lightdir);
	void SetDirLightColor(int index, const XMFLOAT3& lightcolor);
	//点光源
	void SetPointLightActive(int index, bool active);
	void SetPointLightPos(int index,const XMFLOAT3& lightpos);
	void SetPointLightColor(int index, const XMFLOAT3& lightcolor);
	void SetPointLightAtten(int index, const XMFLOAT3& lightAtten);

};


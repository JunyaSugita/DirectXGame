#pragma once
#include <DirectXMath.h>
#include "DirectionalLight.h"
#include "PointLight.h"

class LightGroup
{
	//�G�C���A�X
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
	//���s��
	static const int DirLightNum = 3;
	//�_����
	static const int PointLightNum = 3;

public:
	struct ConstBufferData
	{
		//�����̐F
		XMFLOAT3 ambientColor;
		float pad1;
		//���s�����p
		DirectionalLight::ConstBufferData dirLights[DirLightNum];
		//�_����
		PointLight::ConstBufferData pointLights[PointLightNum];
	};

	static void StaticInitialize(ID3D12Device* device);

	static LightGroup* Create();

private:
	//�萔�o�b�t�@
	ComPtr<ID3D12Resource>constBuff_;
	//�����̐F
	XMFLOAT3 ambientColor_ = { 1,1,1 };
	//���s�����̔z��
	DirectionalLight dirLights_[DirLightNum];
	//�_�����̔z��
	PointLight pointLights_[PointLightNum];
	//�_�[�e�B�t���O
	bool dirty_ = false;

public:
	void Initialize();

	void TransferConstBuffer();

	void Update();

	void DefaultLightSetting();

	void Draw(ID3D12GraphicsCommandList* cmdList, UINT rootParameterIndex);

	void SetAmbientColor(const XMFLOAT3& color);
	//���s��
	void SetDirLightActive(int index, bool active);
	void SetDirLightDir(int index,const XMVECTOR& lightdir);
	void SetDirLightColor(int index, const XMFLOAT3& lightcolor);
	//�_����
	void SetPointLightActive(int index, bool active);
	void SetPointLightPos(int index,const XMFLOAT3& lightpos);
	void SetPointLightColor(int index, const XMFLOAT3& lightcolor);
	void SetPointLightAtten(int index, const XMFLOAT3& lightAtten);

};


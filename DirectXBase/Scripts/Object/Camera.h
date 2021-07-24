#pragma once
#include <DirectXMath.h>
/**
* @file Camera.h
* @breif �J����
*
* @date 2021/06/20
* @author �җI��
*/

class Camera
{
public:
	Camera(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 targetPos, DirectX::XMFLOAT3 upVec);
	~Camera();

	void Update();
	void Terminate();

	DirectX::XMFLOAT4X4 GetWorld() { return m_mtxWorld; }
	DirectX::XMFLOAT4X4 GetView() { return m_mtxView; }
	DirectX::XMFLOAT4X4 GetProj() { return m_mtxProj; }

private:
	DirectX::XMFLOAT3 m_targetPos;	//! ���Ă���Ώۂ̈ʒu
	DirectX::XMFLOAT3 m_pos;		//! ���g�̈ʒu
	DirectX::XMFLOAT3 m_upVec;		//! �A�b�v�x�N�g��

	int	  m_screenW;
	int	  m_screenH;
	float m_fFovY;			//! ����p
	float m_fNearZ;			//! �j�A�N���b�v
	float m_fFarZ;			//! �t�@�[�N���b�v

	DirectX::XMFLOAT4X4 m_mtxWorld;	//! ���[���h�}�g���N�X
	DirectX::XMFLOAT4X4 m_mtxView;	//! �r���[�}�g���N�X
	DirectX::XMFLOAT4X4 m_mtxProj;	//! �v���W�F�N�V�����}�g���N�X

	// �萔
	static constexpr float VIEW_ANGLE = DirectX::XM_PI / 3.f;	// ����p
	static constexpr float VIEW_NEAR_Z = 0.1f;
	static constexpr float VIEW_FAR_Z = 10000.0f;

private:
	void CalcWorldMatrix();
	void UpdateMatrix();

};
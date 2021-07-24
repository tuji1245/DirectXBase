#pragma once
#include <DirectXMath.h>
/**
* @file Camera.h
* @breif カメラ
*
* @date 2021/06/20
* @author 辻悠希
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
	DirectX::XMFLOAT3 m_targetPos;	//! 見ている対象の位置
	DirectX::XMFLOAT3 m_pos;		//! 自身の位置
	DirectX::XMFLOAT3 m_upVec;		//! アップベクトル

	int	  m_screenW;
	int	  m_screenH;
	float m_fFovY;			//! 視野角
	float m_fNearZ;			//! ニアクリップ
	float m_fFarZ;			//! ファークリップ

	DirectX::XMFLOAT4X4 m_mtxWorld;	//! ワールドマトリクス
	DirectX::XMFLOAT4X4 m_mtxView;	//! ビューマトリクス
	DirectX::XMFLOAT4X4 m_mtxProj;	//! プロジェクションマトリクス

	// 定数
	static constexpr float VIEW_ANGLE = DirectX::XM_PI / 3.f;	// 視野角
	static constexpr float VIEW_NEAR_Z = 0.1f;
	static constexpr float VIEW_FAR_Z = 10000.0f;

private:
	void CalcWorldMatrix();
	void UpdateMatrix();

};
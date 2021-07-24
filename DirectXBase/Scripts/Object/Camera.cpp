#include "Camera.h"
#include <System/Input/input.h>
#include <System/DX11Manager.h>

Camera::Camera(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 targetPos, DirectX::XMFLOAT3 upVec) :
	m_pos(pos), m_targetPos(targetPos), m_upVec(upVec),
	m_screenW(defWindowRECT.right), m_screenH(defWindowRECT.bottom),
	m_fFovY(VIEW_ANGLE),
	m_fNearZ(VIEW_NEAR_Z), m_fFarZ(VIEW_FAR_Z)
{	
	CalcWorldMatrix();
}
Camera::~Camera()
{
	Terminate();
}

void Camera::Update()
{
#if 0
	bool isMouseL = GetKeyPress(KeyCode::LBUTTON);
	bool isMouseM = GetKeyPress(KeyCode::MBUTTON);
	bool isMouseR = GetKeyPress(KeyCode::RBUTTON);
	static POINT MousePos = { 0,0 };
	static POINT prevMousePos;
	prevMousePos = MousePos;
	MousePos = GetMousePos();

	float valueX = prevMousePos.x - MousePos.x;
	float valueY = prevMousePos.y - MousePos.y;

	if (isMouseL)
	{
		DirectX::XMVECTOR camera_pos, camera_up;
		camera_pos = DirectX::XMVectorSet(m_pos.x - m_targetPos.x, m_pos.y - m_targetPos.y, m_pos.z - m_targetPos.z, 0.0f);
		camera_up = DirectX::XMLoadFloat3(&m_upVec);

		DirectX::XMVECTOR axis; //��]�p��
		//XZ����]�p�N�I�[�^�j�I���쐬
		axis = DirectX::XMVector3Normalize(DirectX::XMVector3Cross(camera_pos, camera_up));
		DirectX::XMVECTOR qt_xz = DirectX::XMQuaternionRotationAxis(axis, DirectX::XMConvertToRadians(valueY));
		//Y����]�p�N�I�[�^�j�I���쐬
		axis = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
		DirectX::XMVECTOR qt_y = DirectX::XMQuaternionRotationAxis(axis, DirectX::XMConvertToRadians(valueX));
		//��]�̊|�����킹
		DirectX::XMVECTOR qt = DirectX::XMQuaternionMultiply(qt_xz, qt_y);
		//�N�I�[�^�j�I������]�p�s��쐬
		DirectX::XMMATRIX mat = DirectX::XMMatrixRotationQuaternion(qt);
		//�J������]
		camera_pos = DirectX::XMVector3Transform(camera_pos, mat);;
		camera_pos = DirectX::XMVector3Rotate(camera_pos, qt);
		DirectX::XMVectorAdd(camera_pos, DirectX::XMLoadFloat3(&m_targetPos));
		DirectX::XMStoreFloat3(&m_pos, camera_pos);
		//Up�x�N�g����]
		camera_up = DirectX::XMVector3Transform(camera_up, mat);
		camera_up = DirectX::XMVector3Rotate(camera_up, qt);
		DirectX::XMStoreFloat3(&m_upVec, camera_up);
	}
#endif
	UpdateMatrix();
}
void Camera::Terminate()
{

}

void Camera::CalcWorldMatrix()
{
	DirectX::XMMATRIX world;
	world = DirectX::XMMatrixIdentity();
	DirectX::XMStoreFloat4x4(&m_mtxWorld, world);
}

void Camera::UpdateMatrix()
{
	DirectX::XMMATRIX view = DirectX::XMMatrixLookAtLH(
		DirectX::XMLoadFloat3(&m_pos),
		DirectX::XMLoadFloat3(&m_targetPos),
		DirectX::XMLoadFloat3(&m_upVec)
	);
	DirectX::XMMATRIX proj = DirectX::XMMatrixPerspectiveFovLH(
		m_fFovY,
		(float)m_screenW / m_screenH, //m_fAspectRatio,
		m_fNearZ, m_fFarZ
	);
	DirectX::XMStoreFloat4x4(&m_mtxView, view);
	DirectX::XMStoreFloat4x4(&m_mtxProj, proj);
}
/*
* TODO: Update�̒��́@�uif (FrameRate <= MIN);	// ����0���͂����v �������̑����j�Q���Ă��ăo�O��\������
*/
#pragma once
#include <windows.h>
#include <System/Debug/DebugWindow.h>
class FrameManagerWindow  final : public DebugWindow
{
public:
	FrameManagerWindow(std::string windowName, bool flag = true, ImGuiWindowFlags windowFlags = 0);
	~FrameManagerWindow();

	void Update() override;
	void Draw() override;

	void SetFrameRate(int val);
	bool GetFlag();


private:
	static constexpr int FRAMERATE_MAX = 120;
	static constexpr int FRAMERATE_MIN =   0;

	DWORD m_dwUpdateLastTime;
	DWORD m_dwExecLastTime;
	DWORD m_dwFPSLastTime;
	DWORD m_dwCurTime;
	DWORD m_dwFrameCount;
	int	  m_nCountFPS;

	int m_FrameRate;
	float m_deltaTime;
	float m_fixedDeltaTime;

	bool m_updateFlag;
};
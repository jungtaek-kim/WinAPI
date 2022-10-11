#pragma once
class CCore
{
public:
	void Init();		// 게임시작시 초기화 작업
	void Update();		// 프레임마다 게임로직 진행
	void Render();		// 프레임마다 게임표현 진행
	void Release();		// 게임종료시 마무리 작업
};


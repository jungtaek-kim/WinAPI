#include "framework.h"
#include "CCameraController.h"

#include "CInputManager.h"
#include "CCameraManager.h"

CCameraController::CCameraController()
{
}

CCameraController::~CCameraController()
{
}

void CCameraController::Init()
{
}

void CCameraController::Update()
{
	if (BUTTONDOWN(VK_LBUTTON))
	{
		CAMERA->SetTargetPos(MOUSEWORLDPOS);
	}
}

void CCameraController::Render()
{
}

void CCameraController::Release()
{
}

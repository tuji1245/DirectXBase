#pragma once
/**
* @file main.h
* @breif
*
* @author �җI��
* @date 2021/06/28
* 
* @details
*/
#include <windows.h>

HRESULT Initialize(HWND hwnd);
void Terminate();
void Update();
void FixedUpdate();
void Draw();
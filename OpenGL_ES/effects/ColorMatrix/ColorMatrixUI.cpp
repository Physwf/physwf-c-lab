#include "ColorMatrixUI.h"
#include <stdio.h>

LRESULT CColorMatrixFrame::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;

	if( uMsg == WM_CREATE ) 
	{
		m_PaintManager.Init(m_hWnd);
		CDialogBuilder builder;
		CControlUI* pRoot = builder.Create(_T("./Data/ColorMatrixFrame.xml"), (UINT)0, NULL, &m_PaintManager);  
		ASSERT(pRoot && "Failed to parse XML\n");
		m_PaintManager.AttachDialog(pRoot);
		printf("WM_CREATE\n");
		return lRes;
	}

	if( m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes) ) 
	{
		return lRes;
	}

	return __super::HandleMessage(uMsg, wParam, lParam);
};
#include "ColorMatrixUI.h"

LPCTSTR GetWindowClassName() { return _T("ColorMatrixFrame"); };

void Notify(TNotifyUI& msg) {};

LRESULT CColorMatrixFrame::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;

	if( uMsg == WM_CREATE ) 
	{
		m_PaintManager.Init(m_hWnd);
		CDialogBuilder builder;
		CControlUI* pRoot = builder.Create(_T("duilib.xml"), (UINT)0, NULL, &m_PaintManager);   // duilib.xml需要放到exe目录下
		ASSERT(pRoot && "Failed to parse XML");
		m_PaintManager.AttachDialog(pRoot);
		return lRes;
	}

	if( m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes) ) 
	{
		return lRes;
	}

	return __super::HandleMessage(uMsg, wParam, lParam);
};
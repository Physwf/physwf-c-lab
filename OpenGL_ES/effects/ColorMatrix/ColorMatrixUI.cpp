#include "ColorMatrixUI.h"
#include <stdio.h>

LRESULT CColorMatrixFrame::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;

	if( uMsg == WM_CREATE ) 
	{
		m_PaintManager.Init(m_hWnd);
		if(m_hWnd) printf("not null\n");
		CDialogBuilder builder;
		CControlUI* pRoot = builder.Create(_T("./Data/ColorMatrixFrame.xml"), (UINT)0, NULL, &m_PaintManager);  
		ASSERT(pRoot && "Failed to parse XML\n");
		m_PaintManager.AttachDialog(pRoot);
		m_PaintManager.AddNotifier(this);
		// CSliderUI *slider = new CSliderUI();
		// RECT rect;
		// rect.left = 0;
		// rect.right = 123L;
		// rect.top = 300;
		// rect.bottom = 14L;
		// slider->SetPos(rect);
		// slider->SetBkImage(_T("./Data/Controls/Slider/bk.png"));
		// SIZE s = {14,14};
		// slider->SetThumbSize(s);
		// slider->SetThumbImage(_T("./Data/Controls/Slider/thumb.png"));
		// m_PaintManager.AttachDialog(slider);
		// m_PaintManager.AddNotifier(this); 
		printf("WM_CREATE child\n");
		return lRes;
	}
	if( m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes) ) 
	{
		return lRes;
	}

	return __super::HandleMessage(uMsg, wParam, lParam);
};

void CColorMatrixFrame::Notify(TNotifyUI& msg) 
{
	if(msg.sType == _T("valuechanged"))
	{
		printf("value changed\n");
	}
};

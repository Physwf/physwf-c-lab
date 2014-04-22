#include "ColorMatrixUI.h"
#include <stdio.h>
#include "ColorMatrix.h"

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
		CSliderUI* slider = dynamic_cast<CSliderUI*>(msg.pSender);
		float value = slider->GetValue();
		float max = slider->GetMaxValue();
		if(slider->GetName() == _T("Hue"))
			updateHue(value/max*2.0 - 1.0);
		else if(slider->GetName() == _T("Sat"))
			updateSat(value/max*2.0 - 1.0);
		else if(slider->GetName() == _T("Val"))
			updateBri(value/max*2.0 - 1.0);
		printf("value/max:%d/%d\n",slider->GetValue(),slider->GetMaxValue() );
	}
};

#pragma once
#include <DuiLib/UIlib.h>
using namespace DuiLib;

#ifdef _DEBUG
#   ifdef _UNICODE
#       pragma comment(lib, "DuiLib_ud.lib")
#   else
#       pragma comment(lib, "DuiLib_d.lib")
#   endif
#else
#   ifdef _UNICODE
#       pragma comment(lib, "DuiLib_u.lib")
#   else
#       pragma comment(lib, "DuiLib.lib")
#   endif
#endif

class CDuiFrameWnd : public CWindowWnd, public INotifyUI
{
public:
    virtual LPCTSTR GetWindowClassName() const { return _T("DUIFrame"); }
    virtual void    Notify(TNotifyUI& msg) {}

    virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        LRESULT lRes = 0;

        if( uMsg == WM_CREATE ) 
        {
            m_PaintManager.Init(m_hWnd);
			CDialogBuilder builder;
            CControlUI* pRoot = builder.Create(_T("duilib.xml"), (UINT)0, NULL, &m_PaintManager);   // duilib.xml需要放到exe目录下
            ASSERT(pRoot && "Failed to parse XML");
            m_PaintManager.AttachDialog(pRoot);
			m_PaintManager.AddNotifier(this); 
            return lRes;
        }

        if( m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes) ) 
        {
            return lRes;
        }

        return __super::HandleMessage(uMsg, wParam, lParam);
    }

protected:
    CPaintManagerUI m_PaintManager;
};

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
    CPaintManagerUI::SetInstance(hInstance);
	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath());
    CDuiFrameWnd duiFrame;
    duiFrame.Create(NULL, _T("DUIWnd"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE,0, 0, 500, 400);
    duiFrame.ShowModal();
    return 0;
}
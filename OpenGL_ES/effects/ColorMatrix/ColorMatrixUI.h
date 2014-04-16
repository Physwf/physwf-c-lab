#include <DuiLib/UILib.h>

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

using namespace DuiLib;

class CColorMatrixFrame : public CWindowWnd, public INotifyUI
{
	public:
		virtual LPCTSTR GetWindowClassName();
		virtual void Notfiy(TNotifyUI& msg);
		virtual LRESULT HandleMessage(UINT msg, WPARAM wparam, LPARAM lparam);
	protected:
		CPaintManagerUI m_PaintManager;
};
// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� VC_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// VC_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef VC_EXPORTS
#define VC_API __declspec(dllexport)
#else
#define VC_API __declspec(dllimport)
#endif

// �����Ǵ� VC.dll ������
class VC_API CVC {
public:
	CVC(void);
	// TODO:  �ڴ�������ķ�����
};

extern VC_API int nVC;

VC_API int fnVC(void);

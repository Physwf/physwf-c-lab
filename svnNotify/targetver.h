#pragma once

// ���� SDKDDKVer.h ��������߰汾�Ŀ��� Windows ƽ̨��

// ���ҪΪ��ǰ�� Windows ƽ̨����Ӧ�ó�������� WinSDKVer.h������
// WIN32_WINNT ������ΪҪ֧�ֵ�ƽ̨��Ȼ���ٰ��� SDKDDKVer.h��
#ifndef WINVER // ָ��Ҫ������ƽ̨�� Windows Vista��
#define WINVER 0x0501 // ����ֵ����Ϊ��Ӧ��ֵ���������� Windows �������汾��
#endif

#ifndef _WIN32_WINNT // ָ��Ҫ������ƽ̨�� Windows Vista��
#define _WIN32_WINNT 0x0501 // ����ֵ����Ϊ��Ӧ��ֵ���������� Windows �������汾��
#endif
#include <SDKDDKVer.h>
#include "stdafx.h"

#include "stdafx.h"
#include "stdio.h"
#include "direct_01.h"
//#include "d3d.h"
//ȫ�ֱ�������
HINSTANCE hInst;
HBITMAP hbmp;
HBITMAP sprite;
HDC		mdc;
HDC	hdc;
HBITMAP arrow[13];
int     num;
//ȫ�ֺ���������
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
void				MyPaint(HDC hdc);

//****�D�DWinmain������������ڵ㺯��**************************************
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	MSG msg;

	MyRegisterClass(hInstance);

	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	//��Ϣѭ��
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	return msg.wParam;
}

//****�w���һ�������࣬��������⣬ʹ�ô��ڽṹ��*************************
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= NULL;
	wcex.hCursor		= NULL;
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= "canvas";
	wcex.hIconSm		= NULL;

	return RegisterClassEx(&wcex);
}

//****��ʼ������*************************************
// 1.�����봰��DC���ݵ��ڴ�DC
// 2.���ļ�����λͼ�������ڴ�DC��
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	HDC hdc;
	char filename[50]="";
	hInst = hInstance;

	hWnd = CreateWindow("canvas", "��ͼ����" , WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	MoveWindow(hWnd,10,10,800,600,true);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	hdc = GetDC(hWnd);
	mdc = CreateCompatibleDC(hdc);

	hbmp = (HBITMAP)LoadImage(NULL,"bg.bmp",IMAGE_BITMAP,800,600,LR_LOADFROMFILE); 
    sprite = (HBITMAP)LoadImage(NULL,"sprite.bmp",IMAGE_BITMAP,225,225,LR_LOADFROMFILE); 
    for(int i=1;i<14;i++)
	{
		sprintf(filename,"%d.bmp",i);
	   arrow[i]=(HBITMAP)LoadImage(NULL,filename,IMAGE_BITMAP,200,200,LR_LOADFROMFILE);
	}
	TextOut(mdc,0,0,"fnsdf",5); 
	num=1;
    SetTimer(hWnd,1,500,NULL);
	MyPaint(hdc);
	//MessageBox( NULL, "First blood! ��ã�Visual Studio��", " ��Ϣ����", 0 );//��ʾһ����Ϣ��
	//ReleaseDC(hWnd,hdc);
	printf("fd");
	return TRUE;
}

//****�Զ����ͼ����*********************************
void MyPaint(HDC hdc)
{
	SelectObject(mdc,hbmp);
    BitBlt(hdc,0,0,800,600,mdc,0,0,SRCCOPY);	//����BitBlt������ͼ

	SelectObject(mdc,sprite);

	BitBlt(hdc,50,50,225,225,mdc,225,0,SRCAND);	//����BitBlt������ͼ

	BitBlt(hdc,50,50,225,225,mdc,0,0,SRCPAINT);
	if(num>=13)
		num=1;
	
	SelectObject(mdc,arrow[num]);
	BitBlt(hdc,0,0,200,200,mdc,0,0,SRCPAINT);
	num++;
	//MessageBox( NULL, "First blood! ��ã�Visual Studio��", " ��Ϣ����", 0 );//��ʾһ����Ϣ��
	TextOut(mdc,0,0,"fnsdf",5);  
}

//****��Ϣ������**********************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	/*PAINTSTRUCT ps;
	HDC hdc;*/

	switch (message)
	{
	    case WM_TIMER:                      //ʱ����Ϣ  
            MyPaint(hdc);                   //����Ϣѭ���м��봦��WM_TIMER��Ϣ�������յ�����Ϣʱ�����MyPaint�����������д��ڻ�ͼ  
           printf("fd");
		  // MessageBox( NULL, "First blood! ��ã�Visual Studio��", " ��Ϣ����", 0 );//��ʾһ����Ϣ��
			break;  
		//case WM_PAINT:						//�����ػ���Ϣ
		//	hdc = BeginPaint(hWnd, &ps);
		//	//MyPaint(hdc);
		//	EndPaint(hWnd, &ps);
		//	break;
		case WM_DESTROY:					//���ڽ�����Ϣ
			DeleteDC(mdc);
			DeleteObject(hbmp);
			DeleteObject(sprite);
			ReleaseDC(hWnd,hdc);
			for(int i=0;i<13;i++)
			{
				DeleteObject(arrow[i]);
			}
			KillTimer(hWnd,1);
			PostQuitMessage(0);
			break;
		default:							//������Ϣ
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}




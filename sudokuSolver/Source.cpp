#include "solver.h"
#include "resource1.h"
#include <windows.h>

#pragma comment(lib, "comctl32.lib") // for visual styles
#pragma comment(linker, "/manifestdependency:\"type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' \
language='*'\"")
#include <commctrl.h>

#define hE1 123
#define hS 124

int matrix[9][9];
const char g_szClassName[] = "SudokuSolverClass";

HWND hEditControls[81],hSearch;
HFONT font;

void initializeControls(HWND hwnd)
{
	font=CreateFont(20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Times New Roman");
	for(int i=0; i<9; i++)
	{
		for(int j=0; j<9; j++)
		{
			hEditControls[9*i+j]=CreateWindowExW(WS_EX_CLIENTEDGE,L"EDIT",L"",
				WS_TABSTOP|WS_CHILD|WS_VISIBLE|SS_CENTER|ES_NUMBER,
				24+(30*j),24+(30*i),24,24,hwnd,(HMENU)hE1,GetModuleHandle(NULL),NULL);
			SendMessage(hEditControls[9*i+j],EM_LIMITTEXT,1,0);
			SendMessage(hEditControls[9*i+j],WM_SETFONT,(WPARAM)font,0);
		}

	}
	hSearch=CreateWindowExW(NULL,L"BUTTON",L"Solve!",
		WS_TABSTOP|WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,
		24,300,265,30,hwnd,(HMENU)hS,GetModuleHandle(NULL),NULL);
}

void clearCells()
{
	for(int i=0; i<9; i++)
	{
		for(int j=0; j<9; j++)
		{
			SendMessage(hEditControls[9*i+j],WM_SETTEXT,0,(LPARAM)L"");
		}
	}
}
void startSolver()
{
	char temp[2];
	for(int i=0; i<9; i++)
	{
		for(int j=0; j<9; j++)
		{
			GetWindowText(hEditControls[9*i+j],temp,2);
			if(strcmp(temp,"")) matrix[i][j]=0;
			matrix[i][j]=atoi(temp);
		}
	}
	solveSudoku(matrix);
	for(int i=0; i<9; i++)
	{
		for(int j=0; j<9; j++)
		{
			//GetWindowText(hEditControls[9*i+j],temp,5);
			//SetWindowText(hEditControls[9*i+j],std::to_string(matrix[i][j]).c_str());
			//SendMessage(hEditControls[9*i+j],WM_SETTEXT,0,(LPARAM)"");
			SendMessage(hEditControls[9*i+j],WM_SETTEXT,0,(LPARAM)std::to_string(matrix[i][j]).c_str());
			//if(strcmp(temp,"")) matrix[i][j]=0;
			//matrix[i][j]=atoi(temp);
		}
	}
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
	case WM_CREATE:
		initializeControls(hwnd);
		break;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case hS:
			startSolver();
			break;
		case ID_HELP_ABOUT:
			MessageBox(hwnd,"Sudoku Solver\nby Teodor Merodiyski (c) 2013\n","About",MB_OK);
			break;
		case ID_FILE_CLEAR:
			clearCells();
			break;
		case ID_FILE_EXIT:
			exit(0);
			break;
		}
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
				   LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;
	HWND hwnd;
	MSG Msg;
	InitCommonControls();   

	wc.cbSize        = sizeof(WNDCLASSEX);
	wc.style         = 0;
	wc.lpfnWndProc   = WndProc;
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = hInstance;
	wc.hIcon         = LoadIcon(NULL, MAKEINTRESOURCE(IDI_ICON1));//IDI_APPLICATION);
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+2);
	wc.lpszMenuName  = MAKEINTRESOURCE(IDR_MENU1);//NULL;
	wc.lpszClassName = g_szClassName;
	wc.hIconSm       = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));//IDI_APPLICATION);

	if(!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Window Registration Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		g_szClassName,
		"Sudoku Solver",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 330, 400,
		NULL, NULL, hInstance, NULL);

	if(hwnd == NULL)
	{
		MessageBox(NULL, "Window Creation Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while(GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}
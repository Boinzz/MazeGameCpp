INCLUDE Irvine32.inc
INCLUDE GraphWin.inc

ErrorHandler proto

.data
	className byte "MazeGame", 0
	windowTitle byte "Maze Game", 0
	errorTitle byte "Error", 0

	hInstance DWORD ?
	wc WNDCLASS <NULL,\
				 WindowProc,\
				 NULL,\
				 NULL,\
				 NULL,\
				 NULL,\
				 NULL,\
				 COLOR_WINDOW,\
				 NULL,\
				 className>
	wm_hwnd DWORD ?
	wm_msg MSGStruct <>

.code
WinMain PROC
	invoke GetModuleHandle, NULL
	mov hInstance, eax
	mov wc.hInstance, eax
	invoke RegisterClass, offset wc
	
	.IF eax == NULL
		invoke ErrorHandler
		ret
	.ENDIF

	invoke CreateWindowEx,\
		0,\
		offset className,\
		offset windowTitle,\
		MAIN_WINDOW_STYLE,\
		20, 20, 1280, 768,\
		NULL, NULL, hInstance, NULL

	.IF eax == NULL
		invoke ErrorHandler
		ret
	.ENDIF

	mov wm_hwnd, eax

	invoke ShowWindow, wm_hwnd, SW_SHOW

	wm_messageLoop:
		invoke GetMessage, offset wm_msg, NULL, 0, 0
		.IF eax > 0
			invoke DispatchMessage, offset wm_msg
			jmp wm_messageLoop
		.ENDIF

	mov eax, 0
	ret
WinMain ENDP

WindowProc PROC,
	wp_hwnd: DWORD, wp_uMsg: DWORD, wp_wParam: DWORD, wp_lParam: DWORD
	ret
WindowProc ENDP


ErrorHandler PROC
.data
eh_errorMsg DWORD ?
messageID DWORD ?
.code
	invoke GetLastError
	mov messageID, eax

	invoke FormatMessage, FORMAT_MESSAGE_ALLOCATE_BUFFER + \
	  FORMAT_MESSAGE_FROM_SYSTEM,NULL,messageID,NULL,
	  ADDR eh_errorMsg,NULL,NULL

	invoke MessageBox,NULL, eh_errorMsg, offset errorTitle,
	  MB_ICONERROR+MB_OK

	invoke LocalFree, eh_errorMsg
	ret
ErrorHandler ENDP

END WinMain
/* 
** $Id: helloworld.c 793 2010-07-28 03:36:29Z dongjunjie $
**
** Listing 1.1
**
** helloworld.c: Sample program for MiniGUI Programming Guide
**      The first MiniGUI application.
**
** Copyright (C) 2004 ~ 2009 Feynman Software.
**
** License: GPL
*/

#include <stdio.h>
#include <string.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>

#ifdef _LANG_ZHCN
#include "helloworld_res_cn.h"
#elif defined _LANG_ZHTW
#include "helloworld_res_tw.h"
#else
#include "helloworld_res_en.h"
#endif

#ifdef _LANG_ZHCN
#include "dialogbox_rec_cn.h"
#elif defined _LANG_ZHTW
#include "dialogbox_rec_tw.h"
#else
#include "dialogbox_rec_en.h"
#endif
#include <minigui/control.h>

static DLGTEMPLATE DlgInitProgress =
{
    WS_BORDER | WS_CAPTION, 
    WS_EX_NONE,
    120, 150, 400, 140, 
    the_system_is_initializing,
    0, 0,
    3, NULL,
    0
};

#define IDC_PROMPTINFO	100
#define IDC_PROGRESS  	110

static CTRLDATA CtrlInitProgress [] =
{ 
    {
        "static",
        WS_VISIBLE | SS_SIMPLE,
        10, 10, 380, 16, 
        IDC_PROMPTINFO, 
        Initializing,
        0
    },
    {
        "progressbar",
        WS_VISIBLE,
        10, 40, 380, 20,
        IDC_PROGRESS,
        NULL,
        0
    },
    {
        "button",
        WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON, 
        10, 70, 60, 25,
        IDOK, 
        OK,
        0
    },
 {
        "button",
        WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON, 
        10+100, 70+10, 60, 25,
        IDOK, 
        OK,
        0
    }
};

static int InitDialogBoxProc (HWND hDlg, int message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
    case MSG_INITDIALOG:
        return 1;
        
    case MSG_COMMAND:
        switch (wParam) {
        case IDOK:
        case IDCANCEL:
            EndDialog (hDlg, wParam);
            break;
        }
        break;

    case MSG_CLOSE:
        EndDialog (hDlg, IDCANCEL);
        break;
    }
    
    return DefaultDialogProc (hDlg, message, wParam, lParam);
}

static void InitDialogBox (HWND hWnd)
{
    DlgInitProgress.controls = CtrlInitProgress;
    
    DialogBoxIndirectParam (&DlgInitProgress, hWnd, InitDialogBoxProc, 0L);
}

static char welcome_text [512];
static char msg_text [256];
static RECT welcome_rc = {10, 100, 600, 400};
static RECT msg_rc = {10, 100, 600, 400};

static const char* syskey = "";

static int last_key = -1;
static int last_key_count = 0;

static void make_welcome_text (void)
{
    const char* sys_charset = GetSysCharset (TRUE);
    const char* format;

    if (sys_charset == NULL)
        sys_charset = GetSysCharset (FALSE);

    SetRect (&welcome_rc,  10, 10, g_rcScr.right - 10, g_rcScr.bottom / 2 - 10);
    SetRect (&msg_rc, 10, welcome_rc.bottom + 10, g_rcScr.right - 10, g_rcScr.bottom - 20);

    if (strcmp (sys_charset, FONT_CHARSET_GB2312_0) == 0 
            || strcmp (sys_charset, FONT_CHARSET_GBK) == 0
            || strcmp (sys_charset, FONT_CHARSET_GB18030_0) == 0) {
        format = "欢迎来到 MiniGUI 的世界! 如果您能看到该文本, 则说明 MiniGUI Version %d.%d.%d 可在该硬件上运行!";
    }
    else if (strcmp (sys_charset, FONT_CHARSET_BIG5) == 0) {
        format = "欢迎来到 MiniGUI 的世界! 如果您能看到该文本, 则说明 MiniGUI Version %d.%d.%d 可在该硬件上运行!";
    }
    else {
        format = "Welcome to the world of MiniGUI. \nIf you can see this text, MiniGUI Version %d.%d.%d can run on this hardware board.";
    }
    printf("%s.\n", sys_charset);
    sprintf (welcome_text, format, MINIGUI_MAJOR_VERSION, MINIGUI_MINOR_VERSION, MINIGUI_MICRO_VERSION);

    strcpy (msg_text, HL_ST_NOMES);
}

static int HelloWinProc(HWND hWnd, int message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;

    syskey = "";

    switch (message) {
        case MSG_CREATE:
printf("%s:%d MSG_CREATE:\n", __FUNCTION__,__LINE__);
            make_welcome_text ();
            SetTimer (hWnd, 100, 2000);
	    InitDialogBox (hWnd);
            break;

        case MSG_TIMER:
	  //printf("%s:%d MSG_TIMER:\n", __FUNCTION__,__LINE__);
            sprintf (msg_text, HL_ST_TIMER, 
                            GetTickCount ());
            InvalidateRect (hWnd, &msg_rc, TRUE);
            break;
            
        case MSG_LBUTTONDOWN:
printf("%s:%d MSG_LBUTTONDOWN:\n", __FUNCTION__,__LINE__);
            strcpy (msg_text, HL_ST_LBD);
            InvalidateRect (hWnd, &msg_rc, TRUE);
            break;

        case MSG_LBUTTONUP:
printf("%s:%d MSG_LBUTTONUP:\n", __FUNCTION__,__LINE__);
            strcpy (msg_text, HL_ST_LBU);
            InvalidateRect (hWnd, &msg_rc, TRUE);
            break;

        case MSG_RBUTTONDOWN:
printf("%s:%d  MSG_RBUTTONDOWN:\n", __FUNCTION__,__LINE__);
            strcpy (msg_text, HL_ST_RBD);
            InvalidateRect (hWnd, &msg_rc, TRUE);
            break;

        case MSG_RBUTTONUP:
printf("%s:%d  MSG_RBUTTONUP:\n", __FUNCTION__,__LINE__);
            strcpy (msg_text, HL_ST_RBU);
            InvalidateRect (hWnd, &msg_rc, TRUE);
            break;

        case MSG_PAINT:
	  //printf("%s:%d MSG_PAINT:\n", __FUNCTION__,__LINE__);
            hdc = BeginPaint (hWnd);
            DrawText (hdc, welcome_text, -1, &welcome_rc, DT_LEFT | DT_WORDBREAK);
            DrawText (hdc, msg_text, -1, &msg_rc, DT_LEFT | DT_WORDBREAK);
            EndPaint (hWnd, hdc);
            return 0;

        case MSG_SYSKEYDOWN:
printf("%s:%d MSG_SYSKEYDOWN:\n", __FUNCTION__,__LINE__);
            syskey = HL_ST_SYS;
        case MSG_KEYDOWN:
 printf("%s:%d  MSG_KEYDOWN:\n", __FUNCTION__,__LINE__);
            if(last_key == wParam)
                last_key_count++;
            else
            {
                last_key = wParam;
                last_key_count = 1;
            }
            sprintf (msg_text, HL_ST_KEYD, 
                            wParam, syskey, last_key_count);
            InvalidateRect (hWnd, &msg_rc, TRUE);
            return 0;

        case MSG_KEYLONGPRESS:
 printf("%s:%d MSG_KEYLONGPRESS\n", __FUNCTION__,__LINE__);
            sprintf (msg_text, HL_ST_KEYLONG, wParam);
            InvalidateRect (hWnd, &msg_rc, TRUE);
            break;

        case MSG_KEYALWAYSPRESS:
 printf("%s:%d MSG_KEYALWAYSPRESS\n", __FUNCTION__,__LINE__);
            sprintf (msg_text, HL_ST_KEYALWAY, wParam);
            InvalidateRect (hWnd, &msg_rc, TRUE);
            break;

        case MSG_KEYUP:
 printf("%s:%d MSG_KEYUP\n", __FUNCTION__,__LINE__);
            sprintf (msg_text, HL_ST_KEYU, wParam);
            InvalidateRect (hWnd, &msg_rc, TRUE);
            return 0;

        case MSG_CLOSE:
 printf("%s:%d  MSG_CLOSE\n", __FUNCTION__,__LINE__);
            KillTimer (hWnd, 100);
            DestroyMainWindow (hWnd);
            PostQuitMessage (hWnd);
            return 0;
    }

    return DefaultMainWinProc(hWnd, message, wParam, lParam);
}

int MiniGUIMain (int argc, const char* argv[])
{
    MSG Msg;
    HWND hMainWnd;
    MAINWINCREATE CreateInfo;

#ifdef _MGRM_PROCESSES
    JoinLayer(NAME_DEF_LAYER , "helloworld" , 0 , 0);
#endif

    CreateInfo.dwStyle //= WS_VISIBLE | WS_THICKFRAME; 
             = WS_VISIBLE | WS_BORDER | WS_CAPTION;
    CreateInfo.dwExStyle //= WS_EX_NONE;
      = WS_EX_AUTOSECONDARYDC;
    CreateInfo.spCaption = HL_ST_CAP;
    CreateInfo.hMenu = 0;
    CreateInfo.hCursor = GetSystemCursor(0);
    CreateInfo.hIcon = 0;
    CreateInfo.MainWindowProc = HelloWinProc;
    CreateInfo.lx = 0;
    CreateInfo.ty = 0;
    CreateInfo.rx = g_rcScr.right;
    CreateInfo.by = g_rcScr.bottom;
    CreateInfo.iBkColor = COLOR_lightwhite;
    CreateInfo.dwAddData = 0;
    CreateInfo.hHosting = HWND_DESKTOP;
    
    hMainWnd = CreateMainWindow (&CreateInfo);
    
    if (hMainWnd == HWND_INVALID)
        return -1;

    ShowWindow(hMainWnd, SW_SHOWNORMAL);

    while (GetMessage(&Msg, hMainWnd)) {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }

    MainWindowThreadCleanup (hMainWnd);

    return 0;
}

#ifdef _MGRM_THREADS
#include <minigui/dti.c>
#endif


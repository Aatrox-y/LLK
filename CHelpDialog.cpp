// CHelpDialog.cpp: 实现文件
//
#include "pch.h"
#include "LLK.h"
#include "CHelpDialog.h"
#include "afxdialogex.h"


// CHelpDialog 对话框

IMPLEMENT_DYNAMIC(CHelpDialog, CDialogEx)

CHelpDialog::CHelpDialog(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_HELP_DIALOG, pParent)
    , m_nScrollPos(0)
    , m_bmpHelp(nullptr)
{
}

CHelpDialog::~CHelpDialog()
{
    // 释放资源
    if (m_dcHelp.GetSafeHdc()) m_dcHelp.DeleteDC();
    if (m_dcMem.GetSafeHdc()) m_dcMem.DeleteDC();
    if (m_bmpHelp) DeleteObject(m_bmpHelp);
}

void CHelpDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_SCROLLBAR_HELP, m_scrollHelp);
}


BEGIN_MESSAGE_MAP(CHelpDialog, CDialogEx)
    ON_WM_PAINT()
    ON_WM_VSCROLL()
    ON_WM_DESTROY()
END_MESSAGE_MAP()


// CHelpDialog 消息处理程序

BOOL CHelpDialog::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // 设置对话框图标
    /*SetIcon(m_hIcon, TRUE);    // 设置大图标
    SetIcon(m_hIcon, FALSE);   // 设置小图标*/

    // 初始化设备上下文
    CClientDC dc(this);

    // 加载帮助图片
    m_bmpHelp = (HBITMAP)::LoadImage(
        NULL,
        _T("theme\\picture\\basic_help.bmp"),
        IMAGE_BITMAP,
        0,
        0,
        LR_LOADFROMFILE | LR_CREATEDIBSECTION
    );

    if (m_bmpHelp == NULL)
    {
        CString strError;
        strError.Format(_T("无法加载帮助图片！\n错误代码: %d"), GetLastError());
        MessageBox(strError, _T("错误"), MB_ICONERROR);
        EndDialog(IDCANCEL);
        return FALSE;
    }

    // 获取图片尺寸
    BITMAP bmpInfo;
    GetObject(m_bmpHelp, sizeof(BITMAP), &bmpInfo);
    m_sizeHelp = CSize(bmpInfo.bmWidth, bmpInfo.bmHeight);

    // 创建图片内存DC
    if (!m_dcHelp.CreateCompatibleDC(&dc))
    {
        MessageBox(_T("创建内存DC失败！"), _T("错误"), MB_ICONERROR);
        return FALSE;
    }
    m_dcHelp.SelectObject(m_bmpHelp);

    // 获取显示区域
    CWnd* pHelpWnd = GetDlgItem(IDC_STATIC_HELP);
    if (pHelpWnd == NULL)
    {
        MessageBox(_T("找不到帮助显示区域！"), _T("错误"), MB_ICONERROR);
        return FALSE;
    }
    pHelpWnd->GetWindowRect(&m_rtHelp);
    ScreenToClient(&m_rtHelp);

    // 创建双缓冲内存DC
    if (!m_dcMem.CreateCompatibleDC(&dc))
    {
        MessageBox(_T("创建双缓冲DC失败！"), _T("错误"), MB_ICONERROR);
        return FALSE;
    }

    CBitmap bmpMem;
    if (!bmpMem.CreateCompatibleBitmap(&dc, m_sizeHelp.cx, m_rtHelp.Height()))
    {
        MessageBox(_T("创建兼容位图失败！"), _T("错误"), MB_ICONERROR);
        return FALSE;
    }
    m_dcMem.SelectObject(&bmpMem);

    // 设置滚动条
    m_scrollHelp.SetScrollRange(0, max(0, bmpInfo.bmHeight - m_rtHelp.Height()));
    m_scrollHelp.SetScrollPos(0);

    // 初始绘制
    UpdateHelp(0);

    // 强制重绘确保显示
    InvalidateRect(&m_rtHelp, FALSE);
    UpdateWindow();

    return TRUE;
}


void CHelpDialog::OnPaint()
{
    CPaintDC dc(this);

    // 双缓冲绘制
    CDC memDC;
    memDC.CreateCompatibleDC(&dc);
    CBitmap bmp;
    bmp.CreateCompatibleBitmap(&dc, m_rtHelp.Width(), m_rtHelp.Height());
    memDC.SelectObject(&bmp);

    // 绘制背景
    memDC.FillSolidRect(0, 0, m_rtHelp.Width(), m_rtHelp.Height(), RGB(255, 255, 255));

    // 从内存DC复制内容
    memDC.BitBlt(0, 0,
        min(m_rtHelp.Width(), m_sizeHelp.cx),
        min(m_rtHelp.Height(), m_sizeHelp.cy),
        &m_dcMem, 0, 0, SRCCOPY);

    // 输出到屏幕
    dc.BitBlt(m_rtHelp.left, m_rtHelp.top,
        m_rtHelp.Width(), m_rtHelp.Height(),
        &memDC, 0, 0, SRCCOPY);
}

void CHelpDialog::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    int nOldPos = m_nScrollPos;
    int nMinPos, nMaxPos;
    m_scrollHelp.GetScrollRange(&nMinPos, &nMaxPos);

    switch (nSBCode)
    {
    case SB_LINEUP:        m_nScrollPos -= 10; break;
    case SB_LINEDOWN:      m_nScrollPos += 10; break;
    case SB_PAGEUP:        m_nScrollPos -= m_rtHelp.Height(); break;
    case SB_PAGEDOWN:      m_nScrollPos += m_rtHelp.Height(); break;
    case SB_THUMBTRACK:    m_nScrollPos = nPos; break;
    case SB_THUMBPOSITION: m_nScrollPos = nPos; break;
    }

    // 限制范围
    m_nScrollPos = max(nMinPos, min(m_nScrollPos, nMaxPos));

    if (m_nScrollPos != nOldPos)
    {
        m_scrollHelp.SetScrollPos(m_nScrollPos);
        UpdateHelp(m_nScrollPos);
        InvalidateRect(&m_rtHelp, FALSE);
    }

    CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CHelpDialog::UpdateHelp(int nPos)
{
    if (!m_dcHelp.GetSafeHdc()) return;

    // 更新内存DC内容
    m_dcMem.BitBlt(0, 0,
        m_sizeHelp.cx, m_rtHelp.Height(),
        &m_dcHelp, 0, nPos, SRCCOPY);

    // 立即刷新显示
    InvalidateRect(&m_rtHelp, FALSE);
    UpdateWindow();
}
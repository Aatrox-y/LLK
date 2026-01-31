// CHelpDialog.h: 头文件
//

#pragma once

#include "afxdialogex.h"

// CHelpDialog 对话框

class CHelpDialog : public CDialogEx
{
    DECLARE_DYNAMIC(CHelpDialog)

public:
    CHelpDialog(CWnd* pParent = nullptr);   // 标准构造函数
    virtual ~CHelpDialog();

    // 对话框数据
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_HELP_DIALOG };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

    DECLARE_MESSAGE_MAP()

public:
    // 控件变量
    CScrollBar m_scrollHelp;  // 滚动条控件

protected:
    // 成员变量
    HBITMAP m_bmpHelp;      // 帮助图片句柄
    CDC m_dcHelp;           // 图片内存DC
    CDC m_dcMem;            // 双缓冲内存DC
    CRect m_rtHelp;         // 显示区域
    CSize m_sizeHelp;       // 图片实际尺寸
    int m_nScrollPos;       // 当前滚动位置

    // 成员函数
    void UpdateHelp(int nPos);  // 更新帮助显示

public:
    afx_msg void OnPaint();
    afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    virtual BOOL OnInitDialog();
};
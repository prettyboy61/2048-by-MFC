// 2048Dlg.h : 头文件
//

#pragma once


// CMy2048Dlg 对话框
class CMy2048Dlg : public CDialog
{
// 构造
public:
	CMy2048Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MY2048_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	int _num[16];
	int _count;
	bool _down;
	bool _up;
	bool _left;
	bool _right;

public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	BOOL PreTranslateMessage(MSG* pMsg);
	void InitialNum();
	void ShowCurrentNum();
	void CreateANumAtVoid(); // 在空白出产生一个2或4
	afx_msg void OnBnClickedButton21();
	void TotalScore();
	afx_msg void OnBnClickedButton17();
	afx_msg void OnBnClickedButton18();
	afx_msg void OnBnClickedButton20();
	afx_msg void OnBnClickedButton19();

	bool CheckDown();
	bool CheckUp();
	bool CheckLeft();
	bool CheckRight();
};

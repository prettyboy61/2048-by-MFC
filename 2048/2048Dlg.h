// 2048Dlg.h : ͷ�ļ�
//

#pragma once


// CMy2048Dlg �Ի���
class CMy2048Dlg : public CDialog
{
// ����
public:
	CMy2048Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY2048_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
	void CreateANumAtVoid(); // �ڿհ׳�����һ��2��4
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

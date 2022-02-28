// 2048Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "2048.h"
#include "2048Dlg.h"
#include <ctime>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy2048Dlg �Ի���

CMy2048Dlg::CMy2048Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMy2048Dlg::IDD, pParent)
	, _count(0)
	, _up(true)
	, _down(true)
	, _left(true)
	, _right(true)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	 srand( unsigned( time(0) ) );
}

void CMy2048Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMy2048Dlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDCANCEL, &CMy2048Dlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CMy2048Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON21, &CMy2048Dlg::OnBnClickedButton21)
	ON_BN_CLICKED(IDC_BUTTON17, &CMy2048Dlg::OnBnClickedButton17)
	ON_BN_CLICKED(IDC_BUTTON18, &CMy2048Dlg::OnBnClickedButton18)
	ON_BN_CLICKED(IDC_BUTTON20, &CMy2048Dlg::OnBnClickedButton20)
	ON_BN_CLICKED(IDC_BUTTON19, &CMy2048Dlg::OnBnClickedButton19)
END_MESSAGE_MAP()


// CMy2048Dlg ��Ϣ�������

BOOL CMy2048Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	
	InitialNum();

	return FALSE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMy2048Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CMy2048Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMy2048Dlg::OnBnClickedCancel()
{
	int mes = MessageBox( _T("ȷ��Ҫ�˳���"),  _T("������ʾ"), MB_OKCANCEL );
	if ( mes == IDOK)
	{
		OnCancel();
	}
	
}

void CMy2048Dlg::OnBnClickedOk()
{
	int mes = MessageBox( _T("ȷ��Ҫ���¿�ʼ��"),  _T("������ʾ"), MB_OKCANCEL );
	if ( mes == IDOK)
	{
		InitialNum();
	}
}

BOOL CMy2048Dlg::PreTranslateMessage( MSG* pMsg )
{
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_ESCAPE) return TRUE;
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_RETURN) return TRUE;
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam=='R') 
	{
		OnBnClickedOk();
		return TRUE;
	}
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam=='Q') 
	{
		OnBnClickedCancel();
		return TRUE;
	}
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_UP)
	{
		OnBnClickedButton18();
		return TRUE;
	}
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_DOWN)
	{
		OnBnClickedButton17();
		return TRUE;
	}
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_LEFT)
	{
		OnBnClickedButton19();
		return TRUE;
	}
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RIGHT)
	{
		OnBnClickedButton20();
		return TRUE;
	}
	else
		return CDialog::PreTranslateMessage(pMsg);
}

void CMy2048Dlg::InitialNum()
{
	memset( _num, 0, sizeof(_num) );

	CreateANumAtVoid();
	CreateANumAtVoid();

	ShowCurrentNum();
}

void CMy2048Dlg::ShowCurrentNum()
{
	CString str[16];
	for ( int i = 0; i <16; i++ )
	{
		if ( _num[i] == 0 )
		{
			str[i] = "";
		}
		else
		{
			str[i].Format( _T("%d"), _num[i] );
		}
	}
	GetDlgItem(IDC_BUTTON1)->SetWindowText(str[0]);
	GetDlgItem(IDC_BUTTON2)->SetWindowText(str[1]);
	GetDlgItem(IDC_BUTTON3)->SetWindowText(str[2]);
	GetDlgItem(IDC_BUTTON4)->SetWindowText(str[3]);
	GetDlgItem(IDC_BUTTON5)->SetWindowText(str[4]);
	GetDlgItem(IDC_BUTTON6)->SetWindowText(str[5]);
	GetDlgItem(IDC_BUTTON7)->SetWindowText(str[6]);
	GetDlgItem(IDC_BUTTON8)->SetWindowText(str[7]);
	GetDlgItem(IDC_BUTTON9)->SetWindowText(str[8]);
	GetDlgItem(IDC_BUTTON10)->SetWindowText(str[9]);
	GetDlgItem(IDC_BUTTON11)->SetWindowText(str[10]);
	GetDlgItem(IDC_BUTTON12)->SetWindowText(str[11]);
	GetDlgItem(IDC_BUTTON13)->SetWindowText(str[12]);
	GetDlgItem(IDC_BUTTON14)->SetWindowText(str[13]);
	GetDlgItem(IDC_BUTTON15)->SetWindowText(str[14]);
	GetDlgItem(IDC_BUTTON16)->SetWindowText(str[15]);

	GetDlgItem(IDC_STATIC3)->SetFocus();

	TotalScore();

	_up = CheckUp();
	_down = CheckDown();
	_left = CheckLeft();
	_right = CheckRight();

	if ( _up )
	{
		GetDlgItem(IDC_BUTTON18)->EnableWindow(TRUE);
	}
	else
		GetDlgItem(IDC_BUTTON18)->EnableWindow(FALSE);

	if (_down)
	{
		GetDlgItem(IDC_BUTTON17)->EnableWindow(TRUE);
	}
	else
		GetDlgItem(IDC_BUTTON17)->EnableWindow(FALSE);

	if (_left)
	{
		GetDlgItem(IDC_BUTTON19)->EnableWindow(TRUE);
	}
	else
		GetDlgItem(IDC_BUTTON19)->EnableWindow(FALSE);

	if (_right)
	{
		GetDlgItem(IDC_BUTTON20)->EnableWindow(TRUE);
	}
	else
		GetDlgItem(IDC_BUTTON20)->EnableWindow(FALSE);

	if ( !_up && !_down && !_left && !_right  && _count != 0 )
	{
		int mes = MessageBox(_T("���ˣ�Ҫ���¿�ʼ��"), _T("���в��а�"), MB_OKCANCEL);
		if (mes == IDOK)
		{
			InitialNum();
		}
	}
	
}

void CMy2048Dlg::CreateANumAtVoid()
{
	// �ڿհ׵����λ�ò���2����4
	int row = rand() % 4;
	int col = rand() % 4;
	while (_num[row * 4 + col] != 0) //������λ��������ֵ��
	{
		row = rand() % 4;
		col = rand() % 4;
	}

	int temp = rand() % 4;
	if ( temp < 3 )
	{
		_num[row * 4 + col] = 2;
	}
	else
	{
		_num[row * 4 + col] = 4;
	}

}

//һ���ƽ⣡
void CMy2048Dlg::OnBnClickedButton21()
{
	int mes = MessageBox(_T("������ĺ���"), _T("������ʾ"), MB_OKCANCEL);
	if (mes == IDCANCEL)
		return;

	for (int i = 0; i < 16; i++ )
	{
		_num[i] = pow( 2.0, i+1 );
	}
	_count = 0;
	ShowCurrentNum();
}

void CMy2048Dlg::TotalScore()
{
	int score = 0;
	for (int i = 0; i < 16; i++ )
	{
		score += _num[i];
	}

	CString str;
	str.Format(_T("%d"), score );
	GetDlgItem(IDC_STATIC2)->SetWindowText(str);

	str.Format(_T("%d"), _count);
	GetDlgItem(IDC_STATIC1)->SetWindowText(str);
}

// ��
void CMy2048Dlg::OnBnClickedButton17()
{
	if ( _down == false )
		return;

	for (int k = 0; k < 3; k++ )
	{
		for (int i = 2; i >= 0; i--)
		{
			for (int j = 0; j < 4; j++)
			{
				if (_num[(i + 1) * 4 + j] == 0)
				{
					_num[(i + 1) * 4 + j] = _num[i * 4 + j];
					_num[i * 4 + j] = 0;
				}

			}
		}
	}

	for (int i = 2; i >= 0; i--)
	{
		for (int j = 0; j < 4; j++)
		{
			if (_num[(i + 1) * 4 + j] == _num[i * 4 + j])
			{
				_num[(i + 1) * 4 + j] += _num[i * 4 + j];
				_num[i * 4 + j] = 0;
			}

		}
	}

	for (int k = 0; k < 3; k++)
	{
		for (int i = 2; i >= 0; i--)
		{
			for (int j = 0; j < 4; j++)
			{
				if (_num[(i + 1) * 4 + j] == 0)
				{
					_num[(i + 1) * 4 + j] = _num[i * 4 + j];
					_num[i * 4 + j] = 0;
				}

			}
		}
	}

	CreateANumAtVoid();

	for (int k = 0; k < 3; k++)
	{
		for (int i = 2; i >= 0; i--)
		{
			for (int j = 0; j < 4; j++)
			{
				if (_num[(i + 1) * 4 + j] == 0)
				{
					_num[(i + 1) * 4 + j] = _num[i * 4 + j];
					_num[i * 4 + j] = 0;
				}

			}
		}
	}


	_count++;
	ShowCurrentNum();

}

// ��
void CMy2048Dlg::OnBnClickedButton18()
{
	if ( _up == false)
		return;

	// ������
	for (int k = 0; k < 3; k++)
	{
		for (int i = 1; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (_num[(i - 1) * 4 + j] == 0)
				{
					_num[(i - 1) * 4 + j] = _num[i * 4 + j];
					_num[i * 4 + j] = 0;
				}

			}
		}
	}

	// ���
	for (int i = 1; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (_num[(i - 1) * 4 + j] == _num[i * 4 + j])
			{
				_num[(i - 1) * 4 + j] += _num[i * 4 + j];
				_num[i * 4 + j] = 0;
			}

		}
	}

	// ������
	for (int k = 0; k < 3; k++)
	{
		for (int i = 1; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (_num[(i - 1) * 4 + j] == 0)
				{
					_num[(i - 1) * 4 + j] = _num[i * 4 + j];
					_num[i * 4 + j] = 0;
				}

			}
		}
	}

	CreateANumAtVoid();
	// ������
	for (int k = 0; k < 3; k++)
	{
		for (int i = 1; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (_num[(i - 1) * 4 + j] == 0)
				{
					_num[(i - 1) * 4 + j] = _num[i * 4 + j];
					_num[i * 4 + j] = 0;
				}

			}
		}
	}

	_count++;
	ShowCurrentNum();
}

//��
void CMy2048Dlg::OnBnClickedButton20()
{
	if ( _right == false)
		return;

	for (int k = 0; k < 3; k++)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 2; j >= 0; j--)
			{
				if (_num[i * 4 + j + 1] == 0)
				{
					_num[i * 4 + j + 1] = _num[i * 4 + j];
					_num[i * 4 + j] = 0;
				}

			}
		}
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 2; j >= 0; j--)
		{
			if (_num[i * 4 + j + 1] == _num[i * 4 + j] )
			{
				_num[i * 4 + j + 1] += _num[i * 4 + j];
				_num[i * 4 + j] = 0;
			}

		}
	}

	for (int k = 0; k < 3; k++)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 2; j >= 0; j--)
			{
				if (_num[i * 4 + j + 1] == 0)
				{
					_num[i * 4 + j + 1] = _num[i * 4 + j];
					_num[i * 4 + j] = 0;
				}

			}
		}
	}

	CreateANumAtVoid();

	for (int k = 0; k < 3; k++)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 2; j >= 0; j--)
			{
				if (_num[i * 4 + j + 1] == 0)
				{
					_num[i * 4 + j + 1] = _num[i * 4 + j];
					_num[i * 4 + j] = 0;
				}

			}
		}
	}


	_count++;
	ShowCurrentNum();

}

//��
void CMy2048Dlg::OnBnClickedButton19()
{
	if ( _left == false)
		return;

	for (int k = 0; k < 3; k++)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 1; j < 4; j++)
			{
				if (_num[i * 4 + j - 1] == 0)
				{
					_num[i * 4 + j - 1] = _num[i * 4 + j];
					_num[i * 4 + j] = 0;
				}

			}
		}
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 1; j < 4; j++)
		{
			if (_num[i * 4 + j - 1] == _num[i * 4 + j] )
			{
				_num[i * 4 + j - 1] += _num[i * 4 + j];
				_num[i * 4 + j] = 0;
			}

		}
	}

	for (int k = 0; k < 3; k++)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 1; j < 4; j++)
			{
				if (_num[i * 4 + j - 1] == 0)
				{
					_num[i * 4 + j - 1] = _num[i * 4 + j];
					_num[i * 4 + j] = 0;
				}

			}
		}
	}

	CreateANumAtVoid();

	for (int k = 0; k < 3; k++)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 1; j < 4; j++)
			{
				if (_num[i * 4 + j - 1] == 0)
				{
					_num[i * 4 + j - 1] = _num[i * 4 + j];
					_num[i * 4 + j] = 0;
				}

			}
		}
	}

	_count++;
	ShowCurrentNum();
}

//������²����Ŀ�����
bool CMy2048Dlg::CheckDown()
{
	for (int i = 2; i >= 0; i--)
	{
		for (int j = 0; j < 4; j++)
		{
			if ( _num[i*4+j] !=0 && 
				(_num[(i + 1) * 4 + j] == _num[i * 4 + j] || _num[(i + 1) * 4 + j] ==0 ) )
			{
				return true;
			}

		}
	}

	return false;
}

bool CMy2048Dlg::CheckUp()
{
	for (int i = 1; i <4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (_num[i * 4 + j] != 0 &&
				(_num[(i - 1) * 4 + j] == _num[i * 4 + j] || _num[(i - 1) * 4 + j] == 0))
			{
				return true;
			}

		}
	}

	return false;
}

bool CMy2048Dlg::CheckLeft()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 1; j < 4; j++)
		{
			if (_num[i * 4 + j] != 0 &&
				(_num[i * 4 + j - 1 ] == _num[i * 4 + j] || _num[i * 4 + j - 1] == 0))
			{
				return true;
			}

		}
	}

	return false;
}

bool CMy2048Dlg::CheckRight()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 2; j >= 0; j--)
		{
			if (_num[i * 4 + j] != 0 &&
				(_num[i * 4 + j + 1] == _num[i * 4 + j] || _num[i * 4 + j + 1] == 0))
			{
				return true;
			}

		}
	}

	return false;
}

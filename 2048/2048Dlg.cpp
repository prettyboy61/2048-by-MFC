// 2048Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "2048.h"
#include "2048Dlg.h"
#include <ctime>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy2048Dlg 对话框

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


// CMy2048Dlg 消息处理程序

BOOL CMy2048Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	
	InitialNum();

	return FALSE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMy2048Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CMy2048Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMy2048Dlg::OnBnClickedCancel()
{
	int mes = MessageBox( _T("确定要退出吗？"),  _T("友情提示"), MB_OKCANCEL );
	if ( mes == IDOK)
	{
		OnCancel();
	}
	
}

void CMy2048Dlg::OnBnClickedOk()
{
	int mes = MessageBox( _T("确定要重新开始吗？"),  _T("友情提示"), MB_OKCANCEL );
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
		int mes = MessageBox(_T("挂了！要重新开始吗？"), _T("你行不行啊"), MB_OKCANCEL);
		if (mes == IDOK)
		{
			InitialNum();
		}
	}
	
}

void CMy2048Dlg::CreateANumAtVoid()
{
	// 在空白的随机位置产生2或者4
	int row = rand() % 4;
	int col = rand() % 4;
	while (_num[row * 4 + col] != 0) //如果随机位置是有数值的
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

//一键破解！
void CMy2048Dlg::OnBnClickedButton21()
{
	int mes = MessageBox(_T("这样真的好吗？"), _T("友情提示"), MB_OKCANCEL);
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

// 下
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

// 上
void CMy2048Dlg::OnBnClickedButton18()
{
	if ( _up == false)
		return;

	// 向上移
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

	// 求和
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

	// 向上移
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
	// 向上移
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

//右
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

//左
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

//检查向下操作的可行性
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

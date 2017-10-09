
// GateCircuitDemoView.cpp : CGateCircuitDemoView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "GateCircuitDemo.h"
#endif
#include"resource.h"
#include "GateCircuitDemoDoc.h"
#include "GateCircuitDemoView.h"
#include "Gate.h"
#include"Pin.h"
#include "NotGate.h"
#include"ANDGate.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define _Min(x,y) (x<y?x:y)
#define _Max(x,y) (x<y?y:x)
CRect test;
// CGateCircuitDemoView

IMPLEMENT_DYNCREATE(CGateCircuitDemoView, CView)

BEGIN_MESSAGE_MAP(CGateCircuitDemoView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CGateCircuitDemoView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_SELECTED, &CGateCircuitDemoView::OnSelected)
	ON_COMMAND(ID_NOTGATE, &CGateCircuitDemoView::OnNotgate)
	ON_UPDATE_COMMAND_UI(ID_NOTGATE, &CGateCircuitDemoView::OnUpdateNotgate)
	ON_UPDATE_COMMAND_UI(ID_SELECTED, &CGateCircuitDemoView::OnUpdateSelected)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_AND_GATE, &CGateCircuitDemoView::OnAndGate)
	ON_UPDATE_COMMAND_UI(ID_AND_GATE, &CGateCircuitDemoView::OnUpdateAndGate)
END_MESSAGE_MAP()

// CGateCircuitDemoView 构造/析构

CGateCircuitDemoView::CGateCircuitDemoView()
{
	// TODO: 在此处添加构造代码
	m_Type = 0;
	m_selectPin = NULL;
	m_IsMouseDown = false;
	lastSelectGate = NULL;
}

CGateCircuitDemoView::~CGateCircuitDemoView()
{
}

BOOL CGateCircuitDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CGateCircuitDemoView 绘制

void CGateCircuitDemoView::OnDraw(CDC* pDC)
{
	CGateCircuitDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	POSITION pos = m_Gates.GetHeadPosition();
	while(pos)
	{
		((CGate *)(m_Gates.GetNext(pos)))->Draw(pDC);
	}
	if (m_selectPin != NULL)
	{
		pDC->MoveTo(m_LineStartPoint);
		pDC->LineTo(m_LineEndPoint);
	}
}


// CGateCircuitDemoView 打印


void CGateCircuitDemoView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CGateCircuitDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CGateCircuitDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CGateCircuitDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CGateCircuitDemoView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CGateCircuitDemoView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CGateCircuitDemoView 诊断

#ifdef _DEBUG
void CGateCircuitDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CGateCircuitDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGateCircuitDemoDoc* CGateCircuitDemoView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGateCircuitDemoDoc)));
	return (CGateCircuitDemoDoc*)m_pDocument;
}
#endif //_DEBUG


// CGateCircuitDemoView 消息处理程序


void CGateCircuitDemoView::OnSelected()
{
	m_Type = 0;
}


void CGateCircuitDemoView::OnNotgate()
{
	m_Type = 1;
}


void CGateCircuitDemoView::OnUpdateNotgate(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(m_Type == 1);
}


void CGateCircuitDemoView::OnUpdateSelected(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(m_Type == 0);
}


void CGateCircuitDemoView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	switch(m_Type)
	{
	case 1:
		m_Gates.AddHead(new CNotGate(point));
		break;
	case 2:
		m_Gates.AddHead(new CANDGate(point));
		break;
	}
	this->Invalidate();
	CView::OnLButtonDblClk(nFlags, point);
}


void CGateCircuitDemoView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_IsMouseDown = true;
	// 以下顺序不能更改 
	SingleGateSelect(point); // 根据点选中一个元器件
	if (lastSelectGate != NULL)
	{
		// 记录一个鼠标点击位置和元器件位置的偏移量 以解决鼠标在移动过程始终在左上角的问题
		m_selectOffset = point - lastSelectGate->GetPosition(); 
	}
	
	CView::OnLButtonDown(nFlags, point);
}

void CGateCircuitDemoView::SingleGateSelect(CPoint & point)
{
	POSITION pos = m_Gates.GetHeadPosition();
	
	CGate* newselectGate = NULL;
	while (pos)
	{
		if (newselectGate == NULL)
			newselectGate = ((CGate *)(m_Gates.GetNext(pos)))->Selected(point);
		else
			((CGate *)(m_Gates.GetNext(pos)))->NotSelected();
	}
	if (lastSelectGate != NULL)
	{
		InvalidateRect(lastSelectGate->GetRect());
	}
	if (newselectGate != NULL)
	{
		InvalidateRect(newselectGate->GetRect());
	}
	m_selectPin = NULL;
	if(lastSelectGate == newselectGate && newselectGate!=NULL)
	{
		m_selectPin = newselectGate->SelectedPin(point);
		if (m_selectPin != NULL)
		{
			m_LineEndPoint = m_LineStartPoint = m_selectPin->GetPosition();
		}
	}
	lastSelectGate = newselectGate;
}


void CGateCircuitDemoView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_IsMouseDown = false;
	//SingleGateSelect(point); // 处理单个元件选中
	if (m_selectPin != NULL)
	{
		POSITION pos = m_Gates.GetHeadPosition();
		CGate* linkGate = NULL;
		while (pos)
		{
			linkGate = ((CGate *)(m_Gates.GetNext(pos)))->Selected(point);
			if (linkGate != NULL)
				break;
		}
		if (linkGate != NULL)
		{
			CPin *pin = linkGate->FindLatePin(point);
			if (pin != NULL)
			{
				pin->AddLinkPin(m_selectPin);
			}
			
		}
		m_selectPin = NULL;
		Invalidate();
	}
	CView::OnLButtonUp(nFlags, point);
}


void CGateCircuitDemoView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_IsMouseDown && lastSelectGate != NULL /*&& lastSelectGate->Selected(point-m_selectOffset)*/)
	{
		if (m_selectPin != NULL)
		{
			// 引脚连线
			CRect rect;
			rect.left = _Min(point.x, _Min(m_LineEndPoint.x, m_LineStartPoint.x));
			rect.right = _Max(point.x, _Max(m_LineEndPoint.x, m_LineStartPoint.x))+5;
			rect.top = _Min(point.y, _Min(m_LineEndPoint.y, m_LineStartPoint.y));
			rect.bottom = _Max(point.y, _Max(m_LineEndPoint.y, m_LineStartPoint.y))+5;
			m_LineEndPoint = point;
			InvalidateRect(&rect);
			//Invalidate();
			//test = rect;
		}
		else
		{
			CRect rect = lastSelectGate->GetRect();
			lastSelectGate->MoveTo(point - m_selectOffset);
			rect.left = _Min(lastSelectGate->GetRect().left, rect.left);
			rect.right = _Max(lastSelectGate->GetRect().right, rect.right);
			rect.bottom = _Max(lastSelectGate->GetRect().bottom, rect.bottom);
			rect.top = _Min(lastSelectGate->GetRect().top, rect.top);
			//InvalidateRect(&rect);
			Invalidate();
		}
	}
	CView::OnMouseMove(nFlags, point);
}


void CGateCircuitDemoView::OnAndGate()
{
	// TODO: 在此添加命令处理程序代码
	m_Type = 2;
}


void CGateCircuitDemoView::OnUpdateAndGate(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetRadio(m_Type == 2);
}

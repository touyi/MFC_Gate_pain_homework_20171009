
// GateCircuitDemoView.cpp : CGateCircuitDemoView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
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

// CGateCircuitDemoView ����/����

CGateCircuitDemoView::CGateCircuitDemoView()
{
	// TODO: �ڴ˴���ӹ������
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
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CGateCircuitDemoView ����

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


// CGateCircuitDemoView ��ӡ


void CGateCircuitDemoView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CGateCircuitDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CGateCircuitDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CGateCircuitDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
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


// CGateCircuitDemoView ���

#ifdef _DEBUG
void CGateCircuitDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CGateCircuitDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGateCircuitDemoDoc* CGateCircuitDemoView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGateCircuitDemoDoc)));
	return (CGateCircuitDemoDoc*)m_pDocument;
}
#endif //_DEBUG


// CGateCircuitDemoView ��Ϣ�������


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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_IsMouseDown = true;
	// ����˳���ܸ��� 
	SingleGateSelect(point); // ���ݵ�ѡ��һ��Ԫ����
	if (lastSelectGate != NULL)
	{
		// ��¼һ�������λ�ú�Ԫ����λ�õ�ƫ���� �Խ��������ƶ�����ʼ�������Ͻǵ�����
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_IsMouseDown = false;
	//SingleGateSelect(point); // ������Ԫ��ѡ��
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (m_IsMouseDown && lastSelectGate != NULL /*&& lastSelectGate->Selected(point-m_selectOffset)*/)
	{
		if (m_selectPin != NULL)
		{
			// ��������
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
	// TODO: �ڴ���������������
	m_Type = 2;
}


void CGateCircuitDemoView::OnUpdateAndGate(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetRadio(m_Type == 2);
}

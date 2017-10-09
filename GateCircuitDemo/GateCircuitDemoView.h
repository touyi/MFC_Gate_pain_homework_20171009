
// GateCircuitDemoView.h : CGateCircuitDemoView 类的接口
//

#pragma once

class CGate;
class CPin;
class CGateCircuitDemoView : public CView
{
protected: // 仅从序列化创建
	CGateCircuitDemoView();
	DECLARE_DYNCREATE(CGateCircuitDemoView)

// 特性
public:
	CGateCircuitDemoDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CGateCircuitDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	bool m_IsMouseDown;
	int m_Type;
	CPoint m_LineStartPoint;
	CPoint m_LineEndPoint;
	CPoint m_selectOffset;
	CPin* m_selectPin;
	CGate* lastSelectGate;
	CObList m_Gates;




// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSelected();
	afx_msg void OnNotgate();
	afx_msg void OnUpdateNotgate(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSelected(CCmdUI *pCmdUI);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	void SingleGateSelect(CPoint& point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnAndGate();
	afx_msg void OnUpdateAndGate(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // GateCircuitDemoView.cpp 中的调试版本
inline CGateCircuitDemoDoc* CGateCircuitDemoView::GetDocument() const
   { return reinterpret_cast<CGateCircuitDemoDoc*>(m_pDocument); }
#endif


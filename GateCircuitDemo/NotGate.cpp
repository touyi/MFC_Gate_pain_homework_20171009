// NotGate.cpp : 实现文件
//

#include "stdafx.h"
#include "GateCircuitDemo.h"
#include "NotGate.h"
#include "Pin.h"


// CNotGate
 

CNotGate::CNotGate()
{

}

CNotGate::CNotGate(CPoint p):CGate(p)
{
	m_Rect.right = p.x + 64;
	m_Rect.bottom = p.y + 44;
	m_Rect.left -= 4;

	p.y += 20;
	CPin *inp = new CPin(p);
	m_InPins.AddHead(inp);
	p.x += 60;
	CPin * outp = new CPin(p);
	m_OutPins.AddHead(outp);
}


CNotGate::~CNotGate()
{
}

void CNotGate::Draw(CDC * pDC)
{
	CPoint point[5];
	point[0].x = m_Position.x;
	point[0].y = m_Position.y + 20;
	point[1] = point[0];
	point[1].x += 20;
	point[2] = point[1];
	point[2].y += 20;
	point[3] = point[2];
	point[3].x += 20;
	point[3].y -= 20;
	point[4] = point[3];
	point[4].x += 20;

	CPoint point2[3]; 
	point2[0] = point[1];
	point2[1] = point2[0];
	point2[1].y -= 20;
	point2[2] = point[3];

	CPen * oldpen;
	if (m_IsSelected)
	{
		oldpen = pDC->SelectObject(&m_SelectedPen);
	}else
	{
		oldpen = pDC->SelectObject(&m_Pen);
	}
	//pDC->Rectangle(m_Rect);
	pDC->Polyline(point, 5);
	pDC->Polyline(point2, 3);
	pDC->Ellipse(point[3].x - 3, point[3].y - 3,
		point[3].x + 3, point[3].y + 3);
	
	pDC->SelectObject(oldpen);

	POSITION pos = m_InPins.GetHeadPosition();
	while(pos)
	{
		CPin * pin = (CPin*) m_InPins.GetNext(pos);
		pin->Draw(pDC);
	}
	pos = m_OutPins.GetHeadPosition();
	while(pos)
	{
		CPin * pin = (CPin*) m_OutPins.GetNext(pos);
		pin->Draw(pDC);
	}
}

 

 



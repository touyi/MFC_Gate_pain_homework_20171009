#include "stdafx.h"
#include "ANDGate.h"
#include"Pin.h"

CANDGate::CANDGate()
{
}

CANDGate::CANDGate(CPoint point):CGate(point)
{
	m_Rect.right = point.x + 64;
	m_Rect.bottom = point.y + 44;
	m_Rect.left -= 4;
	point.y += 15;
	m_InPins.AddHead(new CPin(point));

	point.y += 10;
	m_InPins.AddHead(new CPin(point));

	point.y -= 5;
	point.x += 60;
	m_OutPins.AddHead(new CPin(point));
}


CANDGate::~CANDGate()
{
}

void CANDGate::Draw(CDC * pDC)
{
	CPoint point[4];
	point[0].x = 32 + m_Position.x;
	point[0].y = 5 + m_Position.y;
	point[1] = point[0];
	point[1].x -= 20;
	point[2] = point[1];
	point[2].y += 30;
	point[3] = point[2];
	point[3].x += 20;
	CPen * oldpen;
	if (m_IsSelected)
	{
		oldpen = pDC->SelectObject(&m_SelectedPen);
	}
	else
	{
		oldpen = pDC->SelectObject(&m_Pen);
	}

	pDC->Polyline(point, 4);

	pDC->MoveTo(12 + m_Position.x, 15 + m_Position.y);
	pDC->LineTo(0 + m_Position.x, 15 + m_Position.y);

	pDC->MoveTo(12 + m_Position.x, 25 + m_Position.y);
	pDC->LineTo(0 + m_Position.x, 25 + m_Position.y);

	pDC->MoveTo(47 + m_Position.x, 20 + m_Position.y);
	pDC->LineTo(60 + m_Position.x, 20 + m_Position.y);
	pDC->MoveTo(32 + m_Position.x, 35 + m_Position.y);
	pDC->AngleArc(32 + m_Position.x, 20 + m_Position.y, 15, -90, 180);

	pDC->SelectObject(oldpen);

	POSITION pos = m_InPins.GetHeadPosition();
	while (pos)
	{
		CPin * pin = (CPin*)m_InPins.GetNext(pos);
		pin->Draw(pDC);
	}
	pos = m_OutPins.GetHeadPosition();
	while (pos)
	{
		CPin * pin = (CPin*)m_OutPins.GetNext(pos);
		pin->Draw(pDC);
	}
}

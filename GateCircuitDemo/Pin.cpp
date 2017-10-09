// Pin.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GateCircuitDemo.h"
#include "Pin.h"


// CPin

CPin::CPin()
{
	m_Position.x = 0; //λ��
	m_Position.y = 0;
	m_IsSelected = false;//�Ƿ�ѡ��
	//ѡ��ʱ���Ƶı�
	m_SelectedPen.CreatePen(PS_SOLID, 1, RGB(0,0,255)); 
}
CPin::CPin(CPoint point)
{
	m_Position = point; //λ��
	m_IsSelected = false;//�Ƿ�ѡ��
	//ѡ��ʱ���Ƶı�
	m_SelectedPen.CreatePen(PS_SOLID, 1, RGB(0,0,255)); 
}



CPin::~CPin()
{
}


// CPin ��Ա����

void CPin::Draw(CDC * pDC)  //����
{
	//��������
	POSITION pos = m_LinkPins.GetHeadPosition();
	while(pos)
	{
		pDC->MoveTo(m_Position);

		CPin * pin = (CPin *)m_LinkPins.GetNext(pos);
		pDC->LineTo(pin->GetPosition());
	}
	//����ѡ��״̬
	if(m_IsSelected)
	{
		CPen * oldp = pDC->SelectObject(&m_SelectedPen);
		CRect r(m_Position.x - 4,m_Position.y - 4,
			m_Position.x + 4,m_Position.y + 4);
		pDC->Ellipse(r);
		pDC->SelectObject(oldp);
	}
}

CPoint CPin::GetPosition()
{
	return m_Position;
}

void CPin::Move(int offsetx, int offsety) //�ƶ�
{
	m_Position.x += offsetx;
	m_Position.y += offsety;
}
CPin * CPin::Selected(CPoint point) //ѡ��
{
	CRect r(m_Position.x - 5,m_Position.y - 5,
			m_Position.x + 5,m_Position.y + 5);

	if(r.PtInRect(point))
	{
		m_IsSelected = true;
		return this;
	}else
	{
		m_IsSelected = false;
		return NULL;
	}
}
CPin * CPin::NearMe(CPoint point) //�Ƿ����Լ��ܽ�
{
	CRect r(m_Position.x - 5,m_Position.y - 5,
			m_Position.x + 5,m_Position.y + 5);

	if(r.PtInRect(point))
	{ 
		return this;
	}else
	{ 
		return NULL;
	}

}
void CPin::NotSelected() //����ѡ�У��������ö�ѡ����Բ�ʹ�á�
{
	m_IsSelected = false;
}
void CPin::SetPoint(CPoint point) //����λ��
{
	m_Position = point;
}
void CPin::AddLinkPin(CPin * ppin)  //����������ţ�
{
	m_LinkPins.AddHead(ppin);
}

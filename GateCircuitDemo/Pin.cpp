// Pin.cpp : 实现文件
//

#include "stdafx.h"
#include "GateCircuitDemo.h"
#include "Pin.h"


// CPin

CPin::CPin()
{
	m_Position.x = 0; //位置
	m_Position.y = 0;
	m_IsSelected = false;//是否被选中
	//选中时绘制的笔
	m_SelectedPen.CreatePen(PS_SOLID, 1, RGB(0,0,255)); 
}
CPin::CPin(CPoint point)
{
	m_Position = point; //位置
	m_IsSelected = false;//是否被选中
	//选中时绘制的笔
	m_SelectedPen.CreatePen(PS_SOLID, 1, RGB(0,0,255)); 
}



CPin::~CPin()
{
}


// CPin 成员函数

void CPin::Draw(CDC * pDC)  //绘制
{
	//绘制连线
	POSITION pos = m_LinkPins.GetHeadPosition();
	while(pos)
	{
		pDC->MoveTo(m_Position);

		CPin * pin = (CPin *)m_LinkPins.GetNext(pos);
		pDC->LineTo(pin->GetPosition());
	}
	//绘制选中状态
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

void CPin::Move(int offsetx, int offsety) //移动
{
	m_Position.x += offsetx;
	m_Position.y += offsety;
}
CPin * CPin::Selected(CPoint point) //选中
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
CPin * CPin::NearMe(CPoint point) //是否离自己很近
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
void CPin::NotSelected() //不被选中，后续采用多选后可以不使用。
{
	m_IsSelected = false;
}
void CPin::SetPoint(CPoint point) //设置位置
{
	m_Position = point;
}
void CPin::AddLinkPin(CPin * ppin)  //添加连接引脚；
{
	m_LinkPins.AddHead(ppin);
}

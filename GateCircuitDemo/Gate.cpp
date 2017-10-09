// Gate.cpp : 实现文件
//

#include "stdafx.h"
#include "GateCircuitDemo.h"
#include "Gate.h"
#include "Pin.h"

// CGate
CGate::CGate()
{
	m_Position.x = 0; //位置
	m_Position.y = 0;
	m_Rect.left = 0; //外接矩形框
	m_Rect.right = 0;
	m_Rect.top = 0;
	m_Rect.bottom = 0;
	m_IsSelected = 0; //是否选中；
	m_Pen.CreatePen(PS_SOLID, 1, RGB(0,0,0));        //未选中时绘制笔
	m_SelectedPen.CreatePen(PS_SOLID, 2, RGB(255,0,255));//选中时绘制用笔

}
CGate::CGate(CPoint point)
{
	m_Position= point; //位置
	m_Rect.left = point.x; //外接矩形框
	m_Rect.right = point.x;
	m_Rect.top = point.y;
	m_Rect.bottom = point.y;
	m_IsSelected = 0; //是否选中；
	m_Pen.CreatePen(PS_SOLID, 1, RGB(0,0,0));        //未选中时绘制笔
	m_SelectedPen.CreatePen(PS_SOLID, 2, RGB(255,0,255));//选中时绘制用笔
}


CGate::~CGate()
{
	POSITION pos = m_InPins.GetHeadPosition();
	while(pos)
	{
		delete m_InPins.GetNext(pos);
	}

	pos = m_OutPins.GetHeadPosition();
	while(pos)
	{
		delete m_OutPins.GetNext(pos);
	}

}


// CGate 成员函数

//移动
void CGate::MoveTo(CPoint to)
{
	//position 的移动
	int offsetx = m_Position.x - to.x;
	int offsety = m_Position.y - to.y;
	m_Position = to;
	//外接矩形的移动
	m_Rect.left = m_Position.x-4; //外接矩形框
	m_Rect.right = m_Rect.right - offsetx;
	m_Rect.top = m_Position.y;
	m_Rect.bottom = m_Rect.bottom - offsety;
	//pin的移动
	POSITION pos = m_InPins.GetHeadPosition();
	while(pos)
	{
		CPin * pin = (CPin*) m_InPins.GetNext(pos);
		pin->Move(-offsetx, -offsety);
	}

	pos = m_OutPins.GetHeadPosition();
	while(pos)
	{
		CPin * pin = (CPin*) m_OutPins.GetNext(pos);
		pin->Move(-offsetx, -offsety);
	}

}
//根据点选中门
CGate * CGate::Selected(CPoint point)
{

	if (m_Rect.PtInRect(point))
	{
		m_IsSelected = true;		
	}else
	{
		m_IsSelected = false;
	}
	//如果没有选中，清除所有引脚选中
	if (!m_IsSelected)
	{
		POSITION pos = m_InPins.GetHeadPosition();
		while(pos)
		{
			CPin * pin = (CPin*) m_InPins.GetNext(pos);
			pin->NotSelected();
		}

		pos = m_OutPins.GetHeadPosition();
		while(pos)
		{
			CPin * pin = (CPin*) m_OutPins.GetNext(pos);
			pin->NotSelected();
		} 
	}

	if (m_IsSelected)
		return this;
	else
		return NULL;



}
//引脚的选中
 CPin * CGate::SelectedPin(CPoint point)
{
	//记录要找的Pin 初始为NULL没有找到
	CPin * selectedPin = NULL;
	if (m_IsSelected)
	{ 

		POSITION pos = m_InPins.GetHeadPosition();
		while(pos)
		{
			CPin * pin = (CPin*) m_InPins.GetNext(pos);
			//如果没有找到，查找，
			//如果找到了，设置所有pin都不选中
			if (selectedPin == NULL)
			{
				if (pin->Selected(point))
				{
					selectedPin = pin;
				}
			}else
			{
				pin->NotSelected();
			}
		}

		pos = m_OutPins.GetHeadPosition();
		while(pos)
		{
			CPin * pin = (CPin*) m_OutPins.GetNext(pos);
			if (selectedPin == NULL)
			{
				if (pin->Selected(point))
				{
					selectedPin = pin;
				}
			}else
			{
				pin->NotSelected();
			}
		}

	}
	return selectedPin;
}
//不选中
void CGate::NotSelected()
{
	m_IsSelected = false;
	if (!m_IsSelected)
	{
		POSITION pos = m_InPins.GetHeadPosition();
		while(pos)
		{
			CPin * pin = (CPin*) m_InPins.GetNext(pos);
			pin->NotSelected();
		}

		pos = m_OutPins.GetHeadPosition();
		while(pos)
		{
			CPin * pin = (CPin*) m_OutPins.GetNext(pos);
			pin->NotSelected();
		} 
	}
}
//查找最近的引脚
CPin * CGate::FindLatePin(CPoint point)
{
	POSITION pos = m_InPins.GetHeadPosition();
	while(pos)
	{
		CPin * pin = (CPin*) m_InPins.GetNext(pos);
		if (pin->NearMe(point))
		{
			return pin;
		}
	}
	pos = m_OutPins.GetHeadPosition();
	while(pos)
	{
		CPin * pin = (CPin*) m_OutPins.GetNext(pos);
		if (pin->NearMe(point))
		{
			return pin;
		} 
	} 
	return NULL;

}

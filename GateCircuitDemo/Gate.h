#pragma once

// CGate 命令目标
class CPin;
class CGate : public CObject
{
public:
	CGate();
	CGate(CPoint point);
	virtual ~CGate();

protected:
	CPoint m_Position; //位置
	CRect m_Rect; //外接矩形框

	CObList m_InPins; //输入引脚
	CObList m_OutPins;//输出引脚

	bool m_IsSelected; //是否选中；

	CPen m_Pen;        //未选中时绘制笔
	CPen m_SelectedPen;//选中时绘制用笔
public:
	// 得到矩形大小
	CRect& GetRect() { return m_Rect; }
	CPoint& GetPosition() { return m_Position; }
	//绘制
	virtual void Draw(CDC * pDC) = 0;
	//移动
	virtual void MoveTo(CPoint to);
	//根据点选中门
	virtual CGate * Selected(CPoint point);
	//引脚的选中
	virtual CPin * SelectedPin(CPoint point);

	//不选中
	void NotSelected();

	//查找最近的引脚
	virtual CPin * FindLatePin(CPoint point);
};



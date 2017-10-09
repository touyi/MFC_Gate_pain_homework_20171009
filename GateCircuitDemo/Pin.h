#pragma once

// CPin 命令目标
//引脚
class CPin : public CObject
{
public:
	CPin();
	CPin(CPoint point);//直接设置位置
	virtual ~CPin();


protected:
	CPoint m_Position; //位置
	CObList m_LinkPins; //连接的引脚
	bool m_IsSelected;//是否被选中
	CPen m_SelectedPen; //选中时绘制的笔

public:
	void Draw(CDC * pDC); //绘制
	void Move(int offsetx, int offsety);//移动
	CPin * Selected(CPoint point);//选中
	CPin * NearMe(CPoint point);//是否离自己很近

	void NotSelected();//不被选中，后续采用多选后可以不使用。

	void SetPoint(CPoint point);//设置位置
	CPoint GetPosition();
	void AddLinkPin(CPin * ppin);//添加连接引脚；
	
};



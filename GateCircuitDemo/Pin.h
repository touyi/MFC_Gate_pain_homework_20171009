#pragma once

// CPin ����Ŀ��
//����
class CPin : public CObject
{
public:
	CPin();
	CPin(CPoint point);//ֱ������λ��
	virtual ~CPin();


protected:
	CPoint m_Position; //λ��
	CObList m_LinkPins; //���ӵ�����
	bool m_IsSelected;//�Ƿ�ѡ��
	CPen m_SelectedPen; //ѡ��ʱ���Ƶı�

public:
	void Draw(CDC * pDC); //����
	void Move(int offsetx, int offsety);//�ƶ�
	CPin * Selected(CPoint point);//ѡ��
	CPin * NearMe(CPoint point);//�Ƿ����Լ��ܽ�

	void NotSelected();//����ѡ�У��������ö�ѡ����Բ�ʹ�á�

	void SetPoint(CPoint point);//����λ��
	CPoint GetPosition();
	void AddLinkPin(CPin * ppin);//����������ţ�
	
};



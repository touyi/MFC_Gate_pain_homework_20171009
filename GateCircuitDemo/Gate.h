#pragma once

// CGate ����Ŀ��
class CPin;
class CGate : public CObject
{
public:
	CGate();
	CGate(CPoint point);
	virtual ~CGate();

protected:
	CPoint m_Position; //λ��
	CRect m_Rect; //��Ӿ��ο�

	CObList m_InPins; //��������
	CObList m_OutPins;//�������

	bool m_IsSelected; //�Ƿ�ѡ�У�

	CPen m_Pen;        //δѡ��ʱ���Ʊ�
	CPen m_SelectedPen;//ѡ��ʱ�����ñ�
public:
	// �õ����δ�С
	CRect& GetRect() { return m_Rect; }
	CPoint& GetPosition() { return m_Position; }
	//����
	virtual void Draw(CDC * pDC) = 0;
	//�ƶ�
	virtual void MoveTo(CPoint to);
	//���ݵ�ѡ����
	virtual CGate * Selected(CPoint point);
	//���ŵ�ѡ��
	virtual CPin * SelectedPin(CPoint point);

	//��ѡ��
	void NotSelected();

	//�������������
	virtual CPin * FindLatePin(CPoint point);
};



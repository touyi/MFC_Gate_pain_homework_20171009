#pragma once
#include "Gate.h"
class CANDGate :
	public CGate
{
public:
	CANDGate();
	CANDGate(CPoint point);
	virtual ~CANDGate();

	virtual void Draw(CDC * pDC);
};


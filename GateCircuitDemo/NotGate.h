#pragma once
#include "Gate.h"

// CNotGate

class CNotGate : public CGate
{ 

public:
	CNotGate();
	CNotGate(CPoint p);
	virtual ~CNotGate();

	virtual void Draw(CDC * pDC);
	 
};



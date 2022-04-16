#pragma once

class CStaticX : public CStatic
{
	DECLARE_DYNAMIC(CStaticX)

public:
	CStaticX();
	virtual ~CStaticX();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};



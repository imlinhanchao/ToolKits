#pragma once

#include "Base.h"

namespace Lib {

class Cvt : public Base
{
public:
	static COleDateTime ToDateTime(CString sDateTime);
	static long ToNumber(CString sNumber, int nRadix);
	static double ToNumber(CString sNumber);

	static CString ToString(bool bValue, CString sTrue=_T("1"), CString sFalse=_T("0"));
	static CString ToString(int nValue, bool bHex=false);	
	static CString ToString(long nValue, bool bHex=false);
	static CString ToString(UINT nValue, bool bHex=false);
	static CString ToString(DWORD dwValue, bool bHex=false);
	static CString ToString(float fValue, int nPrecision=0);
	static CString ToString(double fValue, int nPrecision=0);	
	static CString ToString(COleDateTime date);
	static CString ToString( const wchar_t* pszFormat, ... );
};

}
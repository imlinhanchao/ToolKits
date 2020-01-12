#include "StdAfx.h"
#include "Cvt.h"

namespace Lib {

COleDateTime Cvt::ToDateTime( CString sDateTime )
{
	COleDateTime dt;
	return dt.ParseDateTime(sDateTime) ? dt : COleDateTime(0, 0, 0, 0, 0, 0);
}

long Cvt::ToNumber( CString sNumber, int nRadix )
{
	long dwNumber = _tcstoul(sNumber.GetBuffer(), NULL, nRadix);
	sNumber.ReleaseBuffer();

	return dwNumber;
}

double Cvt::ToNumber( CString sNumber )
{
	return _ttof(sNumber);
}

CString Cvt::ToString( bool bValue, CString sTrue/*=_T("1")*/, CString sFalse/*=_T("1")*/ )
{
	return bValue ? sTrue : sFalse;
}

CString Cvt::ToString( int nValue, bool bHex/*=false*/ )
{
	CString sValue = _T("");
	sValue.Format(bHex ? _T("%x") : _T("%d"), nValue);

	return sValue;
}

CString Cvt::ToString( long nValue, bool bHex/*=false*/ )
{
	CString sValue = _T("");
	sValue.Format(bHex ? _T("%x") : _T("%ld"), nValue);

	return sValue;
}

CString Cvt::ToString( UINT nValue, bool bHex/*=false*/ )
{
	CString sValue = _T("");
	sValue.Format(bHex ? _T("%x") : _T("%u"), nValue);

	return sValue;
}

CString Cvt::ToString( DWORD dwValue, bool bHex/*=false*/ )
{
	CString sValue = _T("");
	sValue.Format(bHex ? _T("%x") : _T("%u"), dwValue);

	return sValue;
}

CString Cvt::ToString( float fValue, int nPrecision/*=0*/ )
{
	CString sValue = _T("");
	CString sFormat = _T("%f");
	if(nPrecision > 0)
	{
		sFormat.Format(_T("%%0.%df"), nPrecision);
	}

	sValue.Format(sFormat, fValue);

	return sValue;
}

CString Cvt::ToString( double fValue, int nPrecision/*=0*/ )
{
	CString sValue = _T("");
	CString sFormat = _T("%f");
	if(nPrecision > 0)
	{
		sFormat.Format(_T("%%0.%df"), nPrecision);
	}

	sValue.Format(sFormat, fValue);
	return sValue;
}

CString Cvt::ToString( COleDateTime date )
{
	CString sValue = _T("");
	sValue.Format(_T("%d-%02d-%02d %02d:%02d:%02d"), date.GetYear(), 
		date.GetMonth(), date.GetDay(), date.GetHour(), date.GetMinute(), date.GetSecond());

	return sValue;
}

CString Cvt::ToString( const wchar_t* pszFormat, ... )
{
	ASSERT(pszFormat && *pszFormat);

	wchar_t  szMsg[1024];	
	va_list  vargs;

	va_start(vargs, pszFormat);

	_vsnwprintf_s( szMsg, sizeof(szMsg) - 1, pszFormat, vargs);

	va_end(vargs);

	return CString(szMsg);
}


}
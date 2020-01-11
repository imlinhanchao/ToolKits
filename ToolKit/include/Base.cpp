#include "StdAfx.h"
#include "Base.h"


CBase::CBase(void)
{
	m_sLastError = _T("");
	m_nLastError = 0;
}

CBase::~CBase(void)
{
}

CString CBase::GetLastErrorMsg()
{
	return  m_sLastError;
}

DWORD CBase::GetLastError()
{
	return  m_nLastError;
}

CString CBase::FormatLastError( DWORD dwLastError )
{
	LPVOID lpMsgBuf;
	CString sErrMsg = _T("");

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | 
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		dwLastError,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR) &lpMsgBuf,
		0, NULL);

	sErrMsg.Format(_T("%s"), lpMsgBuf);
	LocalFree(lpMsgBuf);

	return sErrMsg;
}

void CBase::GetSystemError()
{
	LPVOID lpMsgBuf;
	m_nLastError = ::GetLastError(); 

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | 
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		m_nLastError,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR) &lpMsgBuf,
		0, NULL);

	m_sLastError.Format(_T("Error Code: %d.\r\nError Message: %s"), m_nLastError, lpMsgBuf);
	LocalFree(lpMsgBuf);
}

void CBase::SetLastError( DWORD dwErrCode, CString sErrMsg )
{
	if (sErrMsg.IsEmpty()) {
		m_nLastError = dwErrCode;
		GetSystemError();
		return;
	}

	m_nLastError = 0x4000 + dwErrCode; // not system error
	m_sLastError = sErrMsg;
}

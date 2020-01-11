#include "StdAfx.h"
#include "Base.h"

namespace Lib {

Base::Base(void)
{
	m_sLastError = _T("");
	m_nLastError = 0;
}

Base::~Base(void)
{
}

CString Base::GetLastErrorMsg()
{
	return  m_sLastError;
}

DWORD Base::GetLastError()
{
	return  m_nLastError;
}

CString Base::FormatLastError( DWORD dwLastError )
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

void Base::GetSystemError()
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

void Base::SetLastError( DWORD dwErrCode, CString sErrMsg )
{
	if (sErrMsg.IsEmpty()) {
		m_nLastError = dwErrCode;
		GetSystemError();
		return;
	}

	m_nLastError = 0x4000 + dwErrCode; // not system error
	m_sLastError = sErrMsg;
}

}
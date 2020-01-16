#include "StdAfx.h"
#include "ini.h"

namespace Lib {

Ini::Ini(void)
{
}

Ini::Ini( CString sPath )
{
	SetFile(sPath);
}

Ini::~Ini(void)
{
}

void Ini::SetFile( CString sPath )
{
	m_sIniFile = sPath;
}

bool Ini::GetAllSections( CString sSections[], int& nCount )
{
	const int nBufferSize = 10240;
	TCHAR szValue[nBufferSize] = {0};
	DWORD dwBuffer = GetPrivateProfileString(NULL, NULL, NULL, szValue, nBufferSize, m_sIniFile.GetBuffer());
	m_sIniFile.ReleaseBuffer();

	if(dwBuffer == 0)
	{
		nCount = 0;
		GetSystemError();
		return false;
	}

	int nIndex = 0;
	if(sSections != NULL) sSections[nIndex] = CString(szValue);
	for (DWORD nPos = 0; nPos < dwBuffer; nPos++)
	{
		if (szValue[nPos] == _T('\0'))
		{
			nIndex++;
			if (nIndex >= nCount) continue;
			if(sSections != NULL) sSections[nIndex] = CString(szValue + nPos + 1);
		}
	}
	nCount = nIndex;
	return true;
}

bool Ini::GetAllKeys( CString sSection, CString sKeys[], int& nCount )
{
	const int nBufferSize = 10240;
	TCHAR szValue[nBufferSize] = {0};
	DWORD dwBuffer = GetPrivateProfileString(sSection.GetBuffer(), NULL, NULL, szValue, nBufferSize, m_sIniFile.GetBuffer());
	sSection.ReleaseBuffer();
	m_sIniFile.ReleaseBuffer();

	if(dwBuffer == 0)
	{
		nCount = 0;
		GetSystemError();
		return false;
	}

	int nIndex = 0;
	if(sKeys != NULL) sKeys[nIndex] = CString(szValue);
	for (DWORD nPos = 0; nPos < dwBuffer; nPos++)
	{
		if (szValue[nPos] == _T('\0'))
		{
			nIndex++;
			if (nIndex == nCount) break;
			if(sKeys != NULL) sKeys[nIndex] = CString(szValue + nPos + 1);
		}
	}
	nCount = nIndex;
	return true;
}

bool Ini::Read( CString sSection, CString sKeyName, CString& sValue )
{
	DWORD dwBuffer = GetPrivateProfileString(sSection.GetBuffer(), sKeyName.GetBuffer(), NULL, sValue.GetBuffer(1024), 1024, m_sIniFile.GetBuffer());

	sSection.ReleaseBuffer();
	sKeyName.ReleaseBuffer();
	sValue.ReleaseBuffer();
	m_sIniFile.ReleaseBuffer();

	if(dwBuffer != 0)
	{
		return true;
	}

	GetSystemError();
	return false;
}

bool Ini::Read( CString sSection, CString sKeyName, DWORD& dwValue )
{
	CString sValue;
	bool bSuccess = Read(sSection, sKeyName, sValue);

	if(bSuccess) dwValue = _ttol(sValue);
	return bSuccess;
}

bool Ini::Read( CString sSection, CString sKeyName, int& nValue )
{
	CString sValue;
	bool bSuccess = Read(sSection, sKeyName, sValue);

	if(bSuccess) nValue = _ttoi(sValue);
	return bSuccess;
}

bool Ini::Read( CString sSection, CString sKeyName, UINT& nValue )
{
	CString sValue;
	bool bSuccess = Read(sSection, sKeyName, sValue);

	if(bSuccess) nValue = _ttol(sValue);
	return bSuccess;
}

bool Ini::Read( CString sSection, CString sKeyName, long& nValue )
{
	CString sValue;
	bool bSuccess = Read(sSection, sKeyName, sValue);

	if(bSuccess) nValue = _ttol(sValue);
	return bSuccess;
}

bool Ini::Read( CString sSection, CString sKeyName, bool& bValue )
{
	CString sValue;
	bool bSuccess = Read(sSection, sKeyName, sValue);

	if(bSuccess) bValue = _ttol(sValue) != 0;
	return bSuccess;
}

bool Ini::Write( CString sSection, CString sKeyName, CString sValue )
{
	bool bSuccess = WritePrivateProfileString(sSection.GetBuffer(), sKeyName.GetBuffer(), sValue.GetBuffer(), m_sIniFile.GetBuffer());

	sSection.ReleaseBuffer();
	sKeyName.ReleaseBuffer();
	sValue.ReleaseBuffer();
	m_sIniFile.ReleaseBuffer();

	if(!bSuccess) GetSystemError();
	return bSuccess;
}

bool Ini::Write( CString sSection, CString sKeyName, DWORD dwValue )
{
	CString sValue;
	_ultot_s(dwValue, sValue.GetBuffer(100), 100, 10);
	sValue.ReleaseBuffer();

	return Write(sSection, sKeyName, sValue);
}

bool Ini::Write( CString sSection, CString sKeyName, int nValue )
{
	CString sValue;
	_itot_s(nValue, sValue.GetBuffer(100), 100, 10);
	sValue.ReleaseBuffer();

	return Write(sSection, sKeyName, sValue);
}

bool Ini::Write( CString sSection, CString sKeyName, UINT nValue )
{
	CString sValue;
	_ltot_s(nValue, sValue.GetBuffer(100), 100, 10);
	sValue.ReleaseBuffer();

	return Write(sSection, sKeyName, sValue);
}

bool Ini::Write( CString sSection, CString sKeyName, long nValue )
{
	CString sValue;
	_ltot_s(nValue, sValue.GetBuffer(100), 100, 10);
	sValue.ReleaseBuffer();

	return Write(sSection, sKeyName, sValue);
}

bool Ini::Write( CString sSection, CString sKeyName, bool bValue )
{
	return Write(sSection, sKeyName, CString(bValue ? _T("1") : _T("0")));
}

bool Ini::Remove( CString sSection, CString sKeyName )
{
	bool bSuccess = WritePrivateProfileString(sSection.GetBuffer(), sKeyName.GetBuffer(), NULL, m_sIniFile.GetBuffer());

	sSection.ReleaseBuffer();
	sKeyName.ReleaseBuffer();
	m_sIniFile.ReleaseBuffer();

	if(!bSuccess) GetSystemError();
	return bSuccess;
}

bool Ini::Remove( CString sSection )
{
	bool bSuccess = WritePrivateProfileString(sSection.GetBuffer(), NULL, NULL, m_sIniFile.GetBuffer());

	sSection.ReleaseBuffer();
	m_sIniFile.ReleaseBuffer();

	if(!bSuccess) GetSystemError();
	return bSuccess;
}

}
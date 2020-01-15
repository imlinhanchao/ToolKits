#include "StdAfx.h"
#include "Config.h"

void CConfig::Init( void )
{
	Path::Create(GetConfigPath());
	Path::Create(GetExecutePath());
}

CString CConfig::GetConfigPath( void )
{
	return Path::GetAppDataDirectory(_T("ToolKit"));
}

CString CConfig::GetExecutePath( void )
{
	return _pr(GetConfigPath(), _T("Execute"));
}

CString CConfig::GetHotKeyPath( void )
{
	return _pr(GetConfigPath(), _T("HotKeys.ini"));
}

EXECUTE_ITEM CConfig::ReadExecute( CString sName )
{
	EXECUTE_ITEM item;
	
	Ini ini(_pr(CConfig::GetExecutePath(), sName + _T(".ini")));

	if(ini.Read(_T("Setting"), _T("Path"), item.sPath))
		item.sName = sName;
	ini.Read(_T("Setting"), _T("Argv"), item.sArgv);
	ini.Read(_T("Setting"), _T("ExecPath"), item.sExecPath);
	ini.Read(_T("Setting"), _T("Delay"), item.dwDelay);
	ini.Read(_T("Setting"), _T("Visible"), item.bVisible);

	return item;
}

void CConfig::WriteExecute( EXECUTE_ITEM item )
{
	Ini ini(_pr(CConfig::GetExecutePath(), item.sName + _T(".ini")));

	ini.Write(_T("Setting"), _T("Path"), item.sPath);
	ini.Write(_T("Setting"), _T("Argv"), item.sArgv);
	ini.Write(_T("Setting"), _T("ExecPath"), item.sExecPath);
	ini.Write(_T("Setting"), _T("Delay"), item.dwDelay);
	ini.Write(_T("Setting"), _T("Visible"), item.bVisible);
}

HOTKEY_ITEM CConfig::ReadHotKey( DWORD dwHotKey )
{
	HOTKEY_ITEM item;
	Ini ini(CConfig::GetHotKeyPath());

	CString sSection = Cvt::ToString(dwHotKey);

	if(ini.Read(sSection, _T("Program"), item.sName))
		item.dwHotKey = dwHotKey;
	ini.Read(sSection, _T("ExecWay"), item.nExecWay);
	ini.Read(sSection, _T("Times"), item.nTimes);

	return item;
}

void CConfig::WriteHotKey( HOTKEY_ITEM item )
{
	Ini ini(CConfig::GetHotKeyPath());

	CString sSection = Cvt::ToString(item.dwHotKey);

	ini.Write(sSection, _T("Program"), item.sName);
	ini.Write(sSection, _T("ExecWay"), item.nExecWay);
	ini.Write(sSection, _T("Times"), item.nTimes);
}

void CConfig::RemoveHotKey( DWORD dwHotKey )
{
	Ini ini(CConfig::GetHotKeyPath());
	CString sSection = Cvt::ToString(dwHotKey);
	ini.Remove(sSection);
}

vector<DWORD> CConfig::GetAllHotKeys()
{
	vector<DWORD> lstHotKeys;
	Ini ini(CConfig::GetHotKeyPath());

	CString* arrString = new CString[1];
	int nCount = 1;
	ini.GetAllSections(arrString, nCount);
	delete[] arrString;

	if(nCount == 0) return lstHotKeys;

	arrString = new CString[nCount];
	ini.GetAllSections(arrString, nCount);

	for (int i = 0; i < nCount; i++)
		lstHotKeys.push_back(_ttol(arrString[i]));

	delete[] arrString;

	return lstHotKeys;
}

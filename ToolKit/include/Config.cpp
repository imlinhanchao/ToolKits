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

EXECUTE_ITEM CConfig::ReadExecute( CString sName )
{
	EXECUTE_ITEM item;
	
	Ini ini(_pr(CConfig::GetExecutePath(), sName + _T(".ini")));

	item.sName = sName;
	ini.Read(_T("Setting"), _T("Path"), item.sPath);
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

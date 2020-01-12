#include "StdAfx.h"
#include "Config.h"


CConfig::CConfig(void)
{
}


CConfig::~CConfig(void)
{
}

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

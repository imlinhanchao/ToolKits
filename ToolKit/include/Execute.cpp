#include "StdAfx.h"
#include "Execute.h"


CExecute::CExecute(void)
{
}


CExecute::~CExecute(void)
{
}

bool CExecute::Exists( CString sName )
{
	return Path::Exists(_pr(CConfig::GetExecutePath(), sName));
}

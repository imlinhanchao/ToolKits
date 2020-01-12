#pragma once

typedef struct _EXECUTE_ITEM
{
	CString sName;
	CString sPath;
	CString sArgv;
	CString sExecPath;
	DWORD dwDelay;
	bool bVisible;

} EXECUTE_ITEM, *PEXECUTE_ITEM;

typedef vector<EXECUTE_ITEM> EXECUTE_LIST, *PEXECUTE_LIST;
typedef map<CString, EXECUTE_ITEM> EXECUTE_MAP, *PEXECUTE_MAP;

typedef struct _HOTKEY_ITEM
{
	DWORD dwHotKey;
	CString sName;
	int nExecWay;
	int nTimes;

} HOTKEY_ITEM, *PHOTKEY_ITEM;

#include "Config.h"
#include "Execute.h"
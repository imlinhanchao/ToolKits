#pragma once

typedef struct _EXECUTE_ITEM
{
	CString sName;
	CString sPath;
	CString sArgv;
	CString sExecPath;
	DWORD dwDelay;
	bool bVisible;

	_EXECUTE_ITEM() {
		dwDelay = 0;
		bVisible = true;
	}

	_EXECUTE_ITEM& _EXECUTE_ITEM::operator = (const _EXECUTE_ITEM& item)
	{
		sName = item.sName;
		sPath = item.sPath;
		sArgv = item.sArgv;
		sExecPath = item.sExecPath;
		dwDelay = item.dwDelay;
		bVisible = item.bVisible;

		return *this;
	}

} EXECUTE_ITEM, *PEXECUTE_ITEM;

typedef vector<EXECUTE_ITEM> EXECUTE_LIST, *PEXECUTE_LIST;
typedef map<CString, EXECUTE_ITEM> EXECUTE_MAP, *PEXECUTE_MAP;

#include "Execute.h"

typedef struct _HOTKEY_ITEM
{
	DWORD dwHotKey;
	CString sName;
	int nExecWay;
	int nTimes;
	CExecute execute;

	_HOTKEY_ITEM() {
		dwHotKey = 0;
		nExecWay = 0;
		nTimes = 0;
	}

	_HOTKEY_ITEM& _HOTKEY_ITEM::operator = (const _HOTKEY_ITEM& item)
	{
		dwHotKey = item.dwHotKey;
		sName = item.sName;
		nExecWay = item.nExecWay;
		nTimes = item.nTimes;

		return *this;
	}

} HOTKEY_ITEM, *PHOTKEY_ITEM;
typedef vector<HOTKEY_ITEM> HOTKEY_LIST, *PHOTKEY_LIST;
typedef map<DWORD, HOTKEY_ITEM> HOTKEY_MAP, *PHOTKEY_MAP;

#include "Config.h"
#include "HotKey.h"
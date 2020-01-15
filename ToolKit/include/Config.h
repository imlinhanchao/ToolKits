#pragma once

class CConfig
{
public:
	static void Init(void);
	static inline CString GetConfigPath(void);
	static inline CString GetExecutePath(void);
	static inline CString GetHotKeyPath(void);

	static EXECUTE_ITEM ReadExecute(CString sName);
	static void WriteExecute(EXECUTE_ITEM item);

	static HOTKEY_ITEM ReadHotKey(DWORD dwHotKey);
	static void WriteHotKey(HOTKEY_ITEM item);
	static void RemoveHotKey(DWORD dwHotKey);
	static vector<DWORD> GetAllHotKeys();
};


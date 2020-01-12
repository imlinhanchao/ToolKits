#pragma once

class CConfig
{
public:
	static void Init(void);
	static inline CString GetConfigPath(void);
	static inline CString GetExecutePath(void);

	static EXECUTE_ITEM ReadExecute(CString sName);
	static void WriteExecute(EXECUTE_ITEM item);
};


#pragma once

class CExecute
{
public:
	CExecute(void);
	CExecute(EXECUTE_ITEM item);
	~CExecute(void);

	CExecute& operator = (const CExecute& exec);

	void Run(void);
	bool IsRunning(void);
	void Stop(void);

	static enum { ONCE = 0, LOOP, TIMES };
	static CString WAY[];

	static EXECUTE_MAP Load(void);
	static bool Exists(CString sName);
	static void Write(EXECUTE_ITEM item);
	static EXECUTE_ITEM Read(CString sName);
	static bool Modify(CString sName, EXECUTE_ITEM item);
	static bool Remove(CString sName);
	static EXECUTE_LIST GetList(void);

private:
	bool _Run(void);
	static DWORD WINAPI ExecThread( LPVOID lpParam );

	EXECUTE_ITEM m_execute;
	Lib::Shell m_shell;

	static EXECUTE_MAP m_mapExecutes;
};


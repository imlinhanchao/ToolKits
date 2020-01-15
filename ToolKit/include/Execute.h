#pragma once

class CExecute
{
public:
	CExecute(void);
	CExecute(EXECUTE_ITEM item);
	~CExecute(void);

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
	static EXECUTE_MAP m_mapExecutes;
	EXECUTE_ITEM m_execute;
};


#include "StdAfx.h"
#include "Execute.h"

map<CString, EXECUTE_ITEM> CExecute::m_mapExecutes;
CString CExecute::WAY[] = { _T("Once"), _T("Loop"), _T("Times") };

CExecute::CExecute(void)
{
}


CExecute::CExecute( EXECUTE_ITEM item )
{
	m_execute = item;
}

CExecute::~CExecute(void)
{
}

CExecute& CExecute::operator = (const CExecute& exec)
{
	m_execute = exec.m_execute;
	return *this;
}

void CExecute::Run( void )
{
	HANDLE hThread = CreateThread(NULL, 0, ExecThread, this, 0, NULL);

	if (hThread != NULL) 
	{
		CloseHandle(hThread);
	}
}

bool CExecute::IsRunning( void )
{
	return m_shell.IsRunning();
}

void CExecute::Stop( void )
{
	m_shell.Stop();
}

EXECUTE_MAP CExecute::Load( void )
{
	m_mapExecutes.clear();
	vector<CString> lstPath;
	lstPath = Path::Traversing(CConfig::GetExecutePath());
	for (size_t i = 0; i < lstPath.size(); i++)
	{
		CString sName = Path::GetFileName(lstPath.at(i));
		sName.Replace(_T(".ini"), _T(""));

		EXECUTE_ITEM item = CConfig::ReadExecute(sName);
		m_mapExecutes[item.sName] = item;
	}

	return m_mapExecutes;
}

bool CExecute::Exists( CString sName )
{
	return Path::Exists(_pr(CConfig::GetExecutePath(), sName + _T(".ini")));
}

void CExecute::Write( EXECUTE_ITEM item )
{
	m_mapExecutes[item.sName] = item;
	CConfig::WriteExecute(item);
}

EXECUTE_ITEM CExecute::Read( CString sName )
{
	if (m_mapExecutes.find(sName) == m_mapExecutes.end())
		m_mapExecutes[sName] = CConfig::ReadExecute(sName);

	return m_mapExecutes[sName];
}

EXECUTE_LIST CExecute::GetList( void )
{
	EXECUTE_LIST lstExecute;
	for (EXECUTE_MAP::iterator it = m_mapExecutes.begin(); it != m_mapExecutes.end(); ++it)
	{
		lstExecute.push_back(it->second);
	}

	return lstExecute;
}

bool CExecute::Modify( CString sName, EXECUTE_ITEM item )
{
	if(Remove(sName))
		Write(item);
	return false;
}

bool CExecute::Remove( CString sName )
{
	if (m_mapExecutes.find(sName) == m_mapExecutes.end()) return false;
	m_mapExecutes.erase(m_mapExecutes.find(sName));
	DeleteFile(_pr(CConfig::GetExecutePath(), sName + _T(".ini")));
	return true;
}

bool CExecute::_Run( void )
{
	Sleep(m_execute.dwDelay);
	return m_shell.Execute(m_execute.sPath, m_execute.sArgv, m_execute.bVisible, m_execute.sExecPath);
}

DWORD CExecute::ExecThread( LPVOID lpParam )
{
	CExecute* pThis = (CExecute*) lpParam;
	pThis->_Run();
	return 0;
}

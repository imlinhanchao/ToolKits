#include "StdAfx.h"
#include "Execute.h"

map<CString, EXECUTE_ITEM> CExecute::m_mapExecutes;

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

inline EXECUTE_ITEM CExecute::Read( CString sName )
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

bool CExecute::Remove( CString sName )
{
	if (m_mapExecutes.find(sName) == m_mapExecutes.end()) return false;
	m_mapExecutes.erase(m_mapExecutes.find(sName));
	DeleteFile(_pr(CConfig::GetExecutePath(), sName + _T(".ini")));
	return true;
}

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

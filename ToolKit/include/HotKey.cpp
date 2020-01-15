#include "StdAfx.h"
#include "HotKey.h"

HOTKEY_MAP CHotKey::m_mapHotKey;

CHotKey::CHotKey(void)
{
}


CHotKey::~CHotKey(void)
{
}

HOTKEY_MAP CHotKey::Load( void )
{
	m_mapHotKey.clear();
	vector<DWORD> lstHotKey;
	lstHotKey = CConfig::GetAllHotKeys();
	for (size_t i = 0; i < lstHotKey.size(); i++)
	{
		HOTKEY_ITEM item = CConfig::ReadHotKey(lstHotKey.at(i));
		m_mapHotKey[lstHotKey.at(i)] = item;
		SetHotKey(item.dwHotKey);
	}

	return m_mapHotKey;
}

bool CHotKey::Exists( DWORD dwHotKey )
{
	return !CConfig::ReadHotKey(dwHotKey).sName.IsEmpty();
}

void CHotKey::Write( HOTKEY_ITEM item )
{
	m_mapHotKey[item.dwHotKey] = item;
	CConfig::WriteHotKey(item);
}

HOTKEY_ITEM CHotKey::Read( DWORD dwHotKey )
{
	if (m_mapHotKey.find(dwHotKey) == m_mapHotKey.end())
		m_mapHotKey[dwHotKey] = CConfig::ReadHotKey(dwHotKey);

	return m_mapHotKey[dwHotKey];
}

bool CHotKey::Modify( DWORD dwHotKey, HOTKEY_ITEM item )
{
	if(Remove(dwHotKey))
		Write(item);
	return false;
}

bool CHotKey::Remove( DWORD dwHotKey )
{
	if (m_mapHotKey.find(dwHotKey) == m_mapHotKey.end()) return false;
	m_mapHotKey.erase(m_mapHotKey.find(dwHotKey));
	CConfig::RemoveHotKey(dwHotKey);
}

HOTKEY_LIST CHotKey::GetList( void )
{
	HOTKEY_LIST lstHotKey;
	for (HOTKEY_MAP::iterator it = m_mapHotKey.begin(); it != m_mapHotKey.end(); ++it)
	{
		lstHotKey.push_back(it->second);
	}

	return lstHotKey;
}

bool CHotKey::RemoveHotKey( DWORD dwHotKey )
{
	return UnregisterHotKey(AfxGetMainWnd()->GetSafeHwnd(), dwHotKey);
}

bool CHotKey::SetHotKey( DWORD dwHotKey )
{
	return RegisterHotKey(AfxGetMainWnd()->GetSafeHwnd(), dwHotKey, GetModifiers(dwHotKey), dwHotKey & 0xff);
}

UINT CHotKey::GetModifiers( DWORD dwHotKey )
{
	UINT uModifiers = 0;
	dwHotKey >>= 0x08;
	if(dwHotKey & HOTKEYF_ALT)		uModifiers |= MOD_ALT;
	if(dwHotKey & HOTKEYF_SHIFT)	uModifiers |= MOD_SHIFT;
	if(dwHotKey & HOTKEYF_CONTROL)	uModifiers |= MOD_CONTROL;
	return uModifiers;
}

CString CHotKey::GetHotKeyName( DWORD dwHotKey )
{
	DWORD dwKeyCode = dwHotKey & 0xff;
	CString sKey = CHotKeyCtrl::GetKeyName(dwKeyCode, IsExtendedKey(dwKeyCode));

	if (dwKeyCode == VK_PAUSE)
	{
		sKey = _T("Pause");
	}

	if(_T(" ") == sKey) 
	{
		sKey = _T("Space");
	}
	else if(sKey.IsEmpty())
	{
		sKey = CHotKeyCtrl::GetKeyName(dwKeyCode, TRUE);
	}

	dwHotKey >>= 0x08;
	if(dwHotKey & HOTKEYF_ALT)		sKey = _T("Alt + ") + sKey;
	if(dwHotKey & HOTKEYF_SHIFT)	sKey = _T("Shift + ") + sKey;
	if(dwHotKey & HOTKEYF_CONTROL)	sKey = _T("Ctrl + ") + sKey;

	return sKey;
}

bool CHotKey::IsExtendedKey(DWORD vKey)
{
	DWORD dwKeyCodes[] = {
		VK_DELETE,
		VK_HOME,
		VK_PRIOR,
		VK_NEXT,
		VK_END,

		VK_NUMLOCK,
		VK_INSERT,

		VK_LEFT,
		VK_UP,
		VK_RIGHT,
		VK_DOWN,
	};

	int nCount = sizeof(dwKeyCodes) / sizeof(DWORD);
	for (int i = 0; i < nCount; i++)
	{
		if (vKey == dwKeyCodes[i]) return true;
	}
	return false;
}
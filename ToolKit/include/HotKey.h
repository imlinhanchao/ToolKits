#pragma once
class CHotKey
{
public:
	CHotKey(void);
	~CHotKey(void);

	static HOTKEY_MAP Load(void);
	static bool Exists(DWORD dwHotKey);
	static void Write(HOTKEY_ITEM item);
	static HOTKEY_ITEM Read(DWORD dwHotKey);
	static bool Modify(DWORD dwHotKey, HOTKEY_ITEM item);
	static bool Remove(DWORD dwHotKey);
	static HOTKEY_LIST GetList(void);

	static bool RemoveHotKey(DWORD dwHotKey);
	static bool SetHotKey(DWORD dwHotKey);
	static CString GetHotKeyName(DWORD dwHotKey);

protected:
	static UINT GetModifiers(DWORD dwHotKey);
	static bool IsExtendedKey(DWORD vKey);

	static HOTKEY_MAP m_mapHotKey;
};


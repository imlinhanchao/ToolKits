#pragma once
#include "Base.h"

namespace Lib {

typedef struct _CONTEXTMENU{
	enum TYPE { UNKNOWN, FILE, FOLDER, CONTEXT };

	CString sName;
	CString sDesc;
	CString sIcon;

	CString sProgramRegistryKey;
	CString sRegistryKey;
	CString sProgram;
	CString sCommand;

	vector<CString> sExtensions;
	bool bEnable;
	TYPE eType;

} CONTEXTMENU, *PCONTEXTMENU;

class CContextMenu : public Base
{
public:
	CContextMenu(void);
	~CContextMenu(void);

private:
	vector<CONTEXTMENU> m_menus;
};

}
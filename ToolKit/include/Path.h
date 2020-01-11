#pragma once
#include "Base.h"


namespace Lib {

class Path : public Base
{
public:

	static CString GetFileName(CString sPath);
	static CString GetDirectory(CString sPath);
	static CString GetExtName(CString sPath);

	static CString Resolve(CString sPath, CString sPathNext);
	static CString Omit(CString sPath, int nSize);

	static CString GetCurDirectory(CString sPath=_T(""));
	static CString GetTmpDirectory(CString sPath=_T(""));
	static CString GetUserDirectory(CString sPath=_T(""));
	static CString GetAppDataDirectory(CString sPath=_T(""));
	static CString GetDesktopDirectory(CString sPath=_T(""));
	static CString GetStartupDirectory(CString sPath=_T(""));
	static CString GetStartMenuDirectory(CString sPath=_T(""));

	static CString GetProgramPath(void);
	static CString GetProgramName(void);

	static bool IsDirectory(CString sPath);
	static bool Exists(CString sPath);
};

#define _ph(_x_) Path::Resolve(_x_)

}

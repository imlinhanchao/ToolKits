#include "StdAfx.h"
#include "Path.h"
#include <Shlwapi.h>

namespace Lib {

CString Path::GetFileName( CString sPath )
{
	CString sFilename(PathFindFileName(sPath.GetBuffer()));
	sPath.ReleaseBuffer();
	return sFilename;
}

CString Path::GetDirectory( CString sPath )
{
	PathRemoveFileSpec(sPath.GetBuffer());
	sPath.ReleaseBuffer();
	return sPath + _T("\\");
}

CString Path::GetExtName( CString sPath )
{
	CString sFilename(PathFindExtension(sPath.GetBuffer()));
	sPath.ReleaseBuffer();
	return sFilename;
}

CString Path::Resolve( CString sPath, CString sPathNext )
{
	CString sPathFull = PathAddBackslash(sPath.GetBuffer()) + sPathNext;
	CString sPathFinal;
	sPath.ReleaseBuffer();

	PathCanonicalize(sPathFinal.GetBuffer(sPathFull.GetLength() + 100), sPathFull.GetBuffer());
	sPathFinal.ReleaseBuffer();
	sPathFull.ReleaseBuffer();

	sPath = sPathFinal;
	if (IsDirectory(sPathFinal)) sPathFinal = PathAddBackslash(sPath.GetBuffer());
	sPath.ReleaseBuffer();

	return sPathFinal;
}

CString Path::Omit( CString sPath, int nSize )
{
	CString sOmitPath;
	PathCompactPathEx(sOmitPath.GetBuffer(sPath.GetLength() + 100), sPath.GetBuffer(), nSize, 0);
	sOmitPath.ReleaseBuffer();
	sPath.ReleaseBuffer();

	return sOmitPath;
}

CString Path::GetCurDirectory( CString sPath/*=_T("")*/ )
{
	return Resolve(GetDirectory(GetProgramPath()), sPath);
}

CString Path::GetTmpDirectory( CString sPath/*=_T("")*/ )
{
	DWORD dwLen = 1024;
	TCHAR szPath[1024] = {0};
	if(0 != GetTempPath(dwLen, szPath)) 
	{
		return Resolve(CString(szPath), sPath);
	}
	return _T("");
}

CString Path::GetUserDirectory( CString sPath/*=_T("")*/ )
{
	return Resolve(GetDesktopDirectory()  + _T(".."), sPath);
}

CString Path::GetAppDataDirectory( CString sPath/*=_T("")*/ )
{
	TCHAR szPath[MAX_PATH];
	SHGetSpecialFolderPath(NULL, szPath, CSIDL_LOCAL_APPDATA, FALSE);
	return Resolve(CString(szPath), sPath);
}

CString Path::GetDesktopDirectory( CString sPath/*=_T("")*/ )
{
	TCHAR szPath[MAX_PATH];
	SHGetSpecialFolderPath(NULL, szPath, CSIDL_DESKTOPDIRECTORY, FALSE);
	return Resolve(CString(szPath), sPath);
}

CString Path::GetStartupDirectory( CString sPath/*=_T("")*/ )
{
	TCHAR szPath[MAX_PATH];
	SHGetSpecialFolderPath(NULL, szPath, CSIDL_STARTUP, FALSE);
	return Resolve(CString(szPath), sPath);
}

CString Path::GetStartMenuDirectory( CString sPath/*=_T("")*/ )
{
	TCHAR szPath[MAX_PATH];
	SHGetSpecialFolderPath(NULL, szPath, CSIDL_STARTMENU, FALSE);
	return Resolve(CString(szPath), sPath);
}

CString Path::GetProgramPath(void)
{
	CString sPath = _T("");
	GetModuleFileName(NULL, sPath.GetBuffer(MAX_PATH), MAX_PATH);
	sPath.ReleaseBuffer();
	return sPath;
}

CString Path::GetProgramName(void)
{
	return GetFileName(GetProgramPath());
}

bool Path::IsDirectory( CString sPath )
{
	bool bDirectory = PathIsDirectory(sPath.GetBuffer());
	sPath.ReleaseBuffer();
	return bDirectory;
}

bool Path::Exists( CString sPath )
{
	bool bExists = PathFileExists(sPath.GetBuffer());
	sPath.ReleaseBuffer();
	return bExists;
}

}
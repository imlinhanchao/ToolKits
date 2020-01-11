#pragma once
#include "Base.h"


namespace Lib {

/*!
 * @class Path
 * @brief Path Tools
 * 
 * Used to get different path
 */
class Path : public Base
{
public:

	/*!
	 * @brief GetFileName 
	 * 
	 * Get filename from path
	 * @param sPath The path.
	 * @return CString The filename
	 */
	static CString GetFileName(CString sPath);

	/*!
	 * @brief GetDirectory 
	 * 
	 * Get directory from path
	 * @param sPath The path.
	 * @return CString The directory
	 */
	static CString GetDirectory(CString sPath);
		
	/*!
	 * @brief GetExtName 
	 * 
	 * Get extension from path
	 * @param sPath The path.
	 * @return CString The extension
	 */
	static CString GetExtName(CString sPath);


	/*!
	 * @brief Resolve 
	 * 
	 * Stitching path
	 * @param sPath The path of one.
	 * @param sPathNext The path of next. You can use `..` to indicate the parent directory
	 * @return CString The final path
	 */
	static CString Resolve(CString sPath, CString sPathNext);

	/*!
	 * @brief Omit 
	 * 
	 * Compressed path
	 * @param sPath The path.
	 * @param nSize The path length you want to compressed.
	 * @return CString The final path, like as `C:\...\sample.txt`
	 */
	static CString Omit(CString sPath, int nSize);


	/*!
	 * @brief GetCurDirectory 
	 * 
	 * The Directory of Program
	 * @param sPath The path you want to expand.
	 * @return CString The final path
	 */
	static CString GetCurDirectory(CString sPath=_T(""));

	/*!
	 * @brief GetTmpDirectory 
	 * 
	 * System temporary directory
	 * @param sPath The path you want to expand.
	 * @return CString The final path
	 */
	static CString GetTmpDirectory(CString sPath=_T(""));

	/*!
	 * @brief GetUserDirectory 
	 * 
	 * The user root directory
	 * @param sPath The path you want to expand.
	 * @return CString The final path
	 */
	static CString GetUserDirectory(CString sPath=_T(""));

	/*!
	 * @brief GetAppDataDirectory 
	 * 
	 * The user application data directory
	 * @param sPath The path you want to expand.
	 * @return CString The final path
	 */
	static CString GetAppDataDirectory(CString sPath=_T(""));

	/*!
	 * @brief GetDesktopDirectory 
	 * 
	 * The user desktop path
	 * @param sPath The path you want to expand.
	 * @return CString The final path
	 */
	static CString GetDesktopDirectory(CString sPath=_T(""));

	/*!
	 * @brief GetStartupDirectory 
	 * 
	 * The user startup path
	 * @param sPath The path you want to expand.
	 * @return CString The final path
	 */
	static CString GetStartupDirectory(CString sPath=_T(""));

	/*!
	 * @brief GetStartMenuDirectory 
	 * 
	 * The system start menu path
	 * @param sPath The path you want to expand.
	 * @return CString The final path
	 */
	static CString GetStartMenuDirectory(CString sPath=_T(""));

	/*!
	 * @brief GetProgramPath 
	 * 
	 * Get program path
	 * @return CString The program path
	 */
	static CString GetProgramPath(void);

	/*!
	 * @brief GetProgramName 
	 * 
	 * Get program filename
	 * @return CString The program filename
	 */
	static CString GetProgramName(void);


	/*!
	 * @brief IsDirectory 
	 * 
	 * Check Path is directory or not
	 * @return bool is directory or not
	 */
	static bool IsDirectory(CString sPath);

	/*!
	 * @brief Exists 
	 * 
	 * Check Path is exists or not
	 * @return bool is exists or not
	 */
	static bool Exists(CString sPath);
};

/*!
	* @brief _pr 
	* 
	* Stitching path macro define
	* @param sPath The path of one.
	* @param sPathNext The path of next. You can use `..` to indicate the parent directory
	* @return CString The final path
	*/
#define _pr(_x_,_y_) Path::Resolve(_x_,_y_)

}

#pragma once

#include <shlwapi.h>

namespace Lib {

/*!
 * @class Base
 * @brief Base Class, all class libraries will inherit from it
 * 
 * Used to get execute function error
 */
class Base
{
public:
	Base(void);
	~Base(void);

	/*!
	 * @brief GetLastError
	 * 
	 * Get the last error code
	 * @return DWORD the error code
	 */
	DWORD GetLastError();

	/*!
	 * @brief GetLastErrorMsg 
	 * 
	 * Get the last error message
	 * @return CString the error message
	 */
	CString GetLastErrorMsg();

	/*!
	 * @brief FormatLastError 
	 * 
	 * format the last error code to string
	 * @param dwLastError the error code want to format
	 * @return CString the error message
	 */
	static CString FormatLastError(DWORD dwLastError);

protected:
	/*!
	 * @brief GetSystemError 
	 * 
	 * used to get system error and save it
	 */
	void GetSystemError();
	
	/*!
	 * @brief SetLastError 
	 * 
	 * used to set last error
	 * @param dwErrCode the error code want to set
	 * @param sErrMsg the error message want to set. Skip it if the error code was system error
	 */
	void SetLastError(DWORD dwErrCode, CString sErrMsg=_T(""));

protected:
	CString m_sLastError;
	DWORD m_nLastError;
};

}
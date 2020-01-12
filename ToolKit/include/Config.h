#pragma once

class CConfig
{
public:
	CConfig(void);
	~CConfig(void);

	static void Init(void);
	static inline CString GetConfigPath(void);
	static inline CString GetExecutePath(void);
};


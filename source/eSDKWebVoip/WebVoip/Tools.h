#pragma once

class CTools
{
private:
	CTools(void);
	~CTools(void);
public:
	static std::wstring UTF2UNICODE(const std::string& str);
	static std::string UNICODE2UTF(const std::wstring& cstr);
	static void CTools::getCurrentPath(std::string& strPath);
	static void GetIPPort(const std::string& serverURL,std::string& ip,int& port);
};

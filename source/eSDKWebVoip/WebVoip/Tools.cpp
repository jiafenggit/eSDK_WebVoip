#include "StdAfx.h"
#include "Tools.h"

const std::string modulename = "WebVoip.dll";

CTools::CTools(void)
{
}

CTools::~CTools(void)
{
}
std::wstring CTools::UTF2UNICODE(const std::string& str)
{
	//确定转换为Unicode需要多少缓冲区(返回值也包含了最后一个NULL字符)。
	int nLen = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
	wchar_t *pUnicode =  new  wchar_t[nLen+1];  
	memset(pUnicode,0,(nLen+1)*sizeof(wchar_t));  
	::MultiByteToWideChar( CP_UTF8,0,str.c_str(),-1,(LPWSTR)pUnicode,nLen );  
	std::wstring  rt;  
	rt = ( wchar_t* )pUnicode;
	delete  pUnicode; 
	return rt;
}
std::string CTools::UNICODE2UTF(const wstring& cstr)
{
	char*     pElementText;
	int    iTextLen;
	std::wstring wstr = cstr;
	// wide char to multi char
	iTextLen = WideCharToMultiByte( CP_UTF8,
		0,
		wstr.c_str(),
		-1,
		NULL,
		0,
		NULL,
		NULL );
	pElementText = new char[iTextLen + 1];
	memset( ( void* )pElementText, 0, sizeof( char ) * ( iTextLen + 1 ) );
	::WideCharToMultiByte( CP_UTF8,
		0,
		wstr.c_str(),
		-1,
		pElementText,
		iTextLen,
		NULL,
		NULL );
	std::string strText;
	strText = pElementText;
	delete[] pElementText;
	return strText;
}

void CTools::getCurrentPath(std::string& strPath)
{
	HMODULE hModule = GetModuleHandleA(modulename.c_str());
	char path[MAX_PATH+1] = {0};
	::GetModuleFileNameA(hModule, path, MAX_PATH);
	std::string strModulePath = path;
	unsigned int loc = strModulePath.find_last_of("\\");
	if( loc != string::npos )
	{
		strPath = strModulePath.substr(0,loc);
	}
}

void CTools::GetIPPort(const std::string& serverURL,std::string& ip,int& port)
{
	ip.clear();
	std::string instr = serverURL;
	string::size_type pos = instr.find(':');
	if( pos != string::npos )
	{
		ip = instr.substr(0,pos);
		std::string outPort = instr.substr(pos+1);
		port =  atoi(outPort.c_str());
	}
	else
	{
		ip = "";
		port = 0;
	}
	return;
}
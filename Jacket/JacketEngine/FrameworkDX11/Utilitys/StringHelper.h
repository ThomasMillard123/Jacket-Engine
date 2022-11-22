#pragma once
#include<string>
#include<locale>
#include<codecvt>
namespace Engine::Utilitys::StringFunc {

	static std::wstring StringToWide(const std::string& str)
	{
		std::wstring wideString(str.begin(), str.end());
		return wideString;
	}

	static  std::string WideToString(const std::wstring& wstr)
		    {
		        //using convert_typeX = std::codecvt_utf8<wchar_t>;
		        std::wstring_convert< std::codecvt_utf8<wchar_t>, wchar_t> converterX;
		
		        return converterX.to_bytes(wstr);
		    }


	static std::string LPCSTRToString(const LPCSTR lpcstr) {
		return std::string(lpcstr);
	}

}
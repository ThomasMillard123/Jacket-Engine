#pragma once
#include<string>
namespace Engine::Utilitys::StringFunc {

	static std::wstring StringToWide(const std::string& str)
	{
		std::wstring wideString(str.begin(), str.end());
		return wideString;
	}




}
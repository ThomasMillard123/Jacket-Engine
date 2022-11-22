#pragma once
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include<unordered_map>
#include<string>


#include"Shader/Shader.h"
namespace Engine::Core::Graphics {
	/// <summary>
	/// resource manager for all shaders
	/// </summary>
	class ShaderResource
	{
	public:
		ShaderResource();
		~ShaderResource();

		void LoadShaders();
		void LoadShadersFromFile(std::string fileName);

		std::unordered_map<std::string, Shader> GetShaderFile(std::string fileName);
		Shader GetShaderFile(std::string fileName, std::string type);

		void SetCurrentShader(std::string fileName);

	private:
		std::unordered_map<std::string, std::unordered_map<std::string,Shader>> ShaderResorces;// shaders stored by file then there components 
	};

}
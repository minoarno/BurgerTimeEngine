#pragma once
#include "Singleton.h"
#include <unordered_map>

namespace dae
{
	class Texture2D;
	class Font;
	class ResourceManager final : public Singleton<ResourceManager>
	{
	public:
		/// <summary>
		/// Clean up of the resource manager.
		/// </summary>
		void CleanUp();

		/// <summary>
		/// Initialize the resource manager
		/// </summary>
		/// <param name="data"> is the datapath.</param>
		void Init(const std::string& data);
		
		/// <param name="file"> of the texture.</param>
		/// <returns>Returns a pointer to the 2D texture.</returns>
		Texture2D* LoadTexture(const std::string& file);

		/// <summary>Loads a new font into the resource manager.</summary>
		/// <param name="file"> of the font.</param>
		/// <param name="size"> of the font.</param>
		/// <returns>Returns a pointer to the font.</returns>
		Font* LoadFont(const std::string& file, unsigned int size);
	private:
		friend class Singleton<ResourceManager>;
		ResourceManager() = default;
		std::string m_DataPath;
		std::unordered_map<std::string, Texture2D*> m_pTextures;
		std::unordered_map<std::string, Font*> m_pFonts;
	};
}

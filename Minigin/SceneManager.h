#pragma once
#include "Singleton.h"
#include <vector>
#include <memory>

namespace dae
{
	class GameObject;
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		~SceneManager() = default;

		Scene& CreateScene(const std::string& name);
		Scene& AddScene(Scene* pScene);
		std::shared_ptr<Scene> GetActiveScene()const;
		void SetActiveScene(const int index);

		void InitializeActiveScene();

		void FixedUpdate();
		void Update();
		void LateUpdate();

		void NextScene();
		void LoadScene(int index);

		void AddGameObject(int index, const std::shared_ptr<GameObject>& go);
		
		void Render();
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_Scenes;
		int m_CurrentIndex = 0;
	};
}

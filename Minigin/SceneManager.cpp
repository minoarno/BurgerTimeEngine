#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::FixedUpdate()
{
	m_Scenes[m_CurrentIndex]->FixedUpdate();
}

void dae::SceneManager::Update()
{
	m_Scenes[m_CurrentIndex]->Update();
}

void dae::SceneManager::LateUpdate()
{
	m_Scenes[m_CurrentIndex]->LateUpdate();
}

void dae::SceneManager::Render()
{
	m_Scenes[m_CurrentIndex]->Render();
}

void dae::SceneManager::NextScene()
{
	if (m_Scenes.size() > 1)
	{
		m_Scenes[m_CurrentIndex]->Unload();
		m_CurrentIndex = ++m_CurrentIndex % m_Scenes.size();
		m_Scenes[m_CurrentIndex]->Initialize();
	}
}


void dae::SceneManager::LoadScene(int index)
{
	if (index != m_CurrentIndex)
	{
		if (index >= 0 && index < int(m_Scenes.size()))
		{
			m_Scenes[m_CurrentIndex]->Unload();
			m_CurrentIndex = index;
			m_Scenes[m_CurrentIndex]->Initialize();
		}
		else
		{
			// out of range
		}
	}
	else
	{
		// Same scene	
	}
}

void dae::SceneManager::AddGameObject(int index, const std::shared_ptr<dae::GameObject>& go)
{
	m_Scenes[index]->Add(go);
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const std::shared_ptr<Scene>& scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);
	return *(scene);
}

dae::Scene& dae::SceneManager::AddScene(dae::Scene* pScene)
{
	const std::shared_ptr<Scene>& scene = std::shared_ptr<Scene>(pScene);
	m_Scenes.push_back(scene);
	return *(scene);
}

std::shared_ptr<dae::Scene> dae::SceneManager::GetActiveScene() const
{
	return m_Scenes[m_CurrentIndex];
}

void dae::SceneManager::SetActiveScene(const int index)
{
	if (index < int(m_Scenes.size()))
	{
		if (index != m_CurrentIndex)
		{
			m_CurrentIndex = index;
			InitializeActiveScene();
		}
	}
	else
	{
	}
}

void dae::SceneManager::InitializeActiveScene()
{
	m_Scenes[m_CurrentIndex]->Initialize();
}

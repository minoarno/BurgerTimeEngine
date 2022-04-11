#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"
#include "Transform.h"
#include "Texture2D.h"
#include "Scene.h"
#include "SceneManager.h"

dae::GameObject::GameObject()
	: GameObject{ nullptr }
{
}

dae::GameObject::GameObject(Scene* pScene)
	: m_pTexture{ nullptr }
	, m_pScene{ pScene }
{
	AddComponent(new dae::Transform{});
}

dae::GameObject::~GameObject()
{
	for (BaseComponent* baseComponent : m_pBaseComponents)
	{
		delete baseComponent;
		baseComponent = nullptr;
	}
	m_pBaseComponents.clear();

	for (GameObject* child : m_pChildren)
	{
		delete child;
		child = nullptr;
	}
	m_pChildren.clear();
}

BaseComponent* dae::GameObject::AddComponent(BaseComponent* newComponent)
{
	m_pBaseComponents.push_back(newComponent);
	newComponent->SetGameObject(this);
	return newComponent;
}

void dae::GameObject::AddChild(GameObject* newChildObject)
{
	//GameObject* oldParent = newChildObject->GetParent();

	//Checking if the the newChildObject isn't one of this object's parents
	GameObject* pObject = this;
	if (pObject != nullptr && pObject != newChildObject)
	{
		pObject->m_pChildren.push_back(newChildObject);
	}
}

void dae::GameObject::SetParent(GameObject* newParentObject)
{
	//GameObject* oldParent = this->GetParent();

	//Checking if the the newParentObject isn't one of this object's children
	GameObject* pObject = newParentObject;
	while (pObject != nullptr && pObject != this)
	{
		pObject = newParentObject->GetParent();
	}

	
}

void dae::GameObject::RemoveChild(GameObject* childObject)
{
	for (int i = int(m_pChildren.size()) - 1; i >= 0; i--)
	{
		if (m_pChildren[i] == childObject)
		{
			delete m_pChildren[i];
			m_pChildren[i] = nullptr;
			m_pChildren.erase(m_pChildren.begin() + i);
		}
	}
}

void dae::GameObject::SetScene(Scene* pScene)
{
	m_pScene = pScene;
}

const dae::Scene* dae::GameObject::GetScene() const
{
	return m_pScene;
}

dae::GameObject* dae::GameObject::GetChild(int index)
{
	if (index >= int(m_pChildren.size()))
	{
		return nullptr;
	}

	return m_pChildren[index];
}

void dae::GameObject::Initialize()
{
	for (size_t i = 0; i < m_pBaseComponents.size(); i++)
	{
		m_pBaseComponents[i]->Initialize();
	}

	for (size_t i = 0; i < m_pChildren.size(); i++)
	{
		m_pChildren[i]->Initialize();
	}
}

void dae::GameObject::FixedUpdate()
{
	for (size_t i = 0; i < m_pBaseComponents.size(); i++)
	{
		m_pBaseComponents[i]->FixedUpdate();
	}

	for (size_t i = 0; i < m_pChildren.size(); i++)
	{
		m_pChildren[i]->FixedUpdate();
	}
}

void dae::GameObject::Update()
{
	for (size_t i = 0; i < m_pBaseComponents.size(); i++)
	{
		m_pBaseComponents[i]->Update();
	}

	for (size_t i = 0; i < m_pChildren.size(); i++)
	{
		m_pChildren[i]->Update();
	}
}

void dae::GameObject::LateUpdate()
{
	for (size_t i = 0; i < m_pBaseComponents.size(); i++)
	{
		m_pBaseComponents[i]->LateUpdate();
	}

	for (size_t i = 0; i < m_pChildren.size(); i++)
	{
		m_pChildren[i]->LateUpdate();
	}
}

void dae::GameObject::Render() const
{
	const glm::vec3 pos = GetComponent<Transform>()->GetPosition();
	if (m_pTexture != nullptr)
	{
		Renderer::GetInstance().RenderTexture(m_pTexture, pos.x, pos.y);
	}

	for (size_t i = 0; i < m_pBaseComponents.size(); i++)
	{
		m_pBaseComponents[i]->Render();
	}

	for (size_t i = 0; i < m_pChildren.size(); i++)
	{
		m_pChildren[i]->Render();
	}
}

void dae::GameObject::SetTexture(const std::string& filename)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::GameObject::SetPosition(float x, float y)
{
	GetComponent<Transform>()->SetPosition(x, y, 0.0f);
}

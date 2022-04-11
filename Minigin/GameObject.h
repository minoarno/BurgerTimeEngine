#pragma once
#include "Transform.h"
#include "Texture2D.h"
#include <vector>
#include <typeindex>
#include "BaseComponent.h"
#include <string>

namespace dae
{
	class Scene;
	class Texture2D;
	class GameObject
	{
	public:
		void Initialize();
		void FixedUpdate();
		void Update();
		void LateUpdate();

		void Render() const;

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

		GameObject();
		GameObject(Scene* pScene);
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		BaseComponent* AddComponent(BaseComponent* newComponent);
		void AddChild(GameObject* newChildObject);
		void SetParent(GameObject* newParentObject);
		void RemoveChild(GameObject* childObject);

		void SetScene(Scene* pScene);
		const Scene* GetScene()const;
		GameObject* GetParent()const { return m_pParent; };
		GameObject* GetChild(int index);
		const std::vector<GameObject*>& GetChildren()const { return m_pChildren; };
		
		template<class T>
		T* GetComponent() const;
		template<class T>
		void SetComponent(T* value);

		void SetTag(const std::string& tag) { m_Tag = tag; };
		std::string GetTag()const { return m_Tag; };
	private:
		Texture2D* m_pTexture;
		std::vector<BaseComponent*> m_pBaseComponents;
		std::vector<GameObject*> m_pChildren;
		GameObject* m_pParent = nullptr;
		dae::Scene* m_pScene;
		std::string m_Tag;
	};

	template<class T>
	inline T* GameObject::GetComponent() const
	{
		for (BaseComponent* c : m_pBaseComponents)
		{
			if (typeid(T).name() == typeid(*c).name())
			{
				return reinterpret_cast<T*>(c);
			}
		}
		return nullptr;
	}

	template<class T>
	inline void GameObject::SetComponent(T* value)
	{
		for (BaseComponent*& c : m_pBaseComponents)
		{
			if (typeid(T) == typeid(*c))
			{
				delete c;
				c = reinterpret_cast<BaseComponent*>(value);
				return;
			}
		}
		
	}
}

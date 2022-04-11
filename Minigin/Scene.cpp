#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

using namespace dae;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name)
	: m_Name{ name }
{
}

Scene::~Scene()
{
}

void Scene::Initialize()
{
	for (std::shared_ptr<GameObject>& pObject : m_pObjects)
	{
		pObject->Initialize();
	}
}

void Scene::Unload()
{

}

void Scene::Add(const std::shared_ptr<GameObject> pObject)
{
	m_pObjects.push_back(pObject);
	pObject->SetScene(this);
}

void Scene::FixedUpdate()
{
	for (const std::shared_ptr<GameObject>& pObject : m_pObjects)
	{
		pObject->FixedUpdate();
	}
}

void Scene::Update()
{
	for (const std::shared_ptr<GameObject>& pObject : m_pObjects)
	{
		pObject->Update();
	}
}

void Scene::LateUpdate()
{
	for (const std::shared_ptr<GameObject>& pObject : m_pObjects)
	{
		pObject->LateUpdate();
	}
}

void Scene::Render() const
{
	for (const std::shared_ptr<GameObject>& pObject : m_pObjects)
	{
		pObject->Render();
	}
}
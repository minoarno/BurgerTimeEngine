#include "MiniginPCH.h"
#include "FPSComponent.h"
#include "EngineTime.h"

FPSComponent::FPSComponent(dae::Font* pFont, float refreshRate)
	: m_pTextComponent{ new TextComponent{ pFont," " } }
	, m_RefreshRate{ refreshRate }
	, m_TotalTime{ 0.f }
{
	m_pTextComponent->SetText("FPS: ");
}

FPSComponent::FPSComponent(std::shared_ptr<dae::Font>& pFont, float refreshRate)
	: FPSComponent{ pFont.get(),refreshRate}
{
}

FPSComponent::~FPSComponent()
{
	delete m_pTextComponent;
	m_pTextComponent = nullptr;
}

void FPSComponent::Update()
{
	const double elapsedSec = Time::GetInstance().GetElapsedSeconds();
	m_TotalTime += elapsedSec;
	if (m_TotalTime >= m_RefreshRate)
	{
		const int fpsValue = static_cast<int>(1.0 / elapsedSec);
		m_pTextComponent->SetText("FPS: " + std::to_string(fpsValue));
		m_TotalTime -= m_RefreshRate;
	}
}

void FPSComponent::Render() const
{
	m_pTextComponent->Render();
}

void FPSComponent::LateUpdate()
{
	m_pTextComponent->LateUpdate();
}

void FPSComponent::SetGameObject(dae::GameObject* ownerGameObject)
{
	m_pGameObject = ownerGameObject;
	m_pTextComponent->SetGameObject(m_pGameObject);
}

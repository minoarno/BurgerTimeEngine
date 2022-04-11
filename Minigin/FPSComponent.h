#pragma once
#include "TextComponent.h"

class FPSComponent final : public BaseComponent
{
public:
	FPSComponent(dae::Font* pFont, float refreshRate = 1.f);
	FPSComponent(std::shared_ptr<dae::Font>& pFont, float refreshRate = 1.f);
	FPSComponent(const FPSComponent& other) = default;
	FPSComponent& operator=(const FPSComponent& other) = default;
	FPSComponent(FPSComponent&& other) = default;
	FPSComponent& operator=(FPSComponent&& other) = default;
	~FPSComponent();

	void Update() override;
	void Render()const override;
	void LateUpdate() override;
	void SetGameObject(dae::GameObject* ownerGameObject) override;
private:
	double m_RefreshRate;
	double m_TotalTime;

	TextComponent* m_pTextComponent;
};


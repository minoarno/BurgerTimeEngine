#pragma once
#include "BaseComponent.h"
#include <string>

namespace dae
{
	class Font;
	class Texture2D;
}

class TextComponent : public BaseComponent
{
public:
	explicit TextComponent(dae::Font* font, const std::string& text = "Text");
	explicit TextComponent(const std::shared_ptr<dae::Font>& font, const std::string& text = "Text");
	TextComponent(const TextComponent& other) = default;
	TextComponent& operator=(const TextComponent& other) = default;
	TextComponent(TextComponent&& other) = default;
	TextComponent& operator=(TextComponent&& other) = default;
	virtual ~TextComponent() = default;

	virtual void Initialize() override;
	virtual void FixedUpdate() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() const override;

	void SetText(const std::string& text);
protected:
	bool m_NeedsUpdate;
	std::string m_Text;
	dae::Font* m_Font;
};


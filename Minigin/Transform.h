#pragma once
#include "BaseComponent.h"
namespace dae
{
	class Transform final : public BaseComponent
	{
	public:
		Transform(const glm::vec3& pos = {0,0,0});

		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(float x, float y, float z);
	private:
		glm::vec3 m_Position;
	};
}

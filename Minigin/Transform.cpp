#include "MiniginPCH.h"
#include "Transform.h"

dae::Transform::Transform(const glm::vec3& pos)
	: BaseComponent{}
	, m_Position{pos}
{
}

void dae::Transform::SetPosition(const float x, const float y, const float z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}

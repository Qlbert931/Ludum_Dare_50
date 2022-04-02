#pragma once
#include "Collision.hpp"

class DynamicNode : public Collidable
{
protected:
	sf::Vector2f velocity;
	sf::Vector2f acceleration;

public:
	void setVelocity(sf::Vector2f _velocity);
	sf::Vector2f getVelocity();

protected:
	virtual void onUpdate(const sf::Time &delta) override;
};


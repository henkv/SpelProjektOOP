#pragma once
#include <SFML\Window\Keyboard.hpp>
#include <SFML\System\Vector2.hpp>

class DirectionalInput
{
	private:
	sf::Keyboard::Key upKey_;
	sf::Keyboard::Key downKey_;
	sf::Keyboard::Key leftKey_;
	sf::Keyboard::Key rightKey_;

	public:
	DirectionalInput();
	virtual ~DirectionalInput();

	sf::Vector2f const& getInput() const;
};


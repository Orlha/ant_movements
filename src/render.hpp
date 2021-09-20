#pragma once
#include <mutex>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "config.hpp"

class Render {
	public:
	Render():
		window(sf::VideoMode(config::window_width, config::window_height), "Ant World")
	{
		window.clear(sf::Color::Black);
		window.setFramerateLimit(60);
		window.display();
		//window.setActive(false);
	}
	void process() {
		while (window.isOpen()) {
			sf::Event event;
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					window.close();
				}
			}
			window.clear();
			auto points = [&] {
				std::lock_guard l { m };
				return good_points;
			} ();
			for(auto position: points) {
				sf::RectangleShape shape(sf::Vector2f(config::block_size, config::block_size));
				shape.setFillColor(sf::Color(100, 250, 50));
				shape.setPosition(sf::Vector2f(config::block_size * (position.x - 995), config::block_size * (position.y - 995)));
				window.draw(shape);
			}
			points = [&] {
				std::lock_guard l { m };
				return bad_points;
			} ();
			for(auto position: points) {
				sf::RectangleShape shape(sf::Vector2f(config::block_size, config::block_size));
				shape.setFillColor(sf::Color(250, 50, 50));
				shape.setPosition(sf::Vector2f(config::block_size * (position.x - 995), config::block_size * (position.y - 995)));
				window.draw(shape);
			}
			window.display();
		}
	}
	void draw_valid_point(Position pos) {
		std::lock_guard l { m };
		good_points.push_back(pos);
	}
	void draw_invalid_point(Position pos) {
		std::lock_guard l { m };
		bad_points.push_back(pos);
	}
	private:
	std::mutex m;
	std::vector<Position> good_points;
	std::vector<Position> bad_points;
	sf::RenderWindow window;
};

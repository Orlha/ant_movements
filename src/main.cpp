#include <cstdio>
#include <unordered_set>
#include <cstdint>
#include <thread>
#include <functional>
#include <chrono>

#include "utility.hpp"
#include "position.hpp"
#ifdef RENDER
#include "render.hpp"
#endif

void calculate_movements(std::function<void(bool,Position)> render_callback) {
	auto good_tiles = 0;
	config::container<Position> path_points;
	std::unordered_set<Position> visited_points;
	// Set starting position;
	path_points.push({ config::starting_x, config::starting_y });
	while(!path_points.empty()) {
		// Extract next path point;
		auto position = utility::access(path_points);
		path_points.pop();
		// Ignore the tile if it is already visited;
		if(visited_points.find(position) != visited_points.end()) {
			continue;
		}
		// Mark tile as visited if it isn't;
		visited_points.insert(position);
		// Ignore that tile if it can't be visited;
		if(!position.validity()) {
			if constexpr(config::rendering) render_callback(false, position);
			continue;
		}
		if constexpr(config::rendering) render_callback(true, position);
		++good_tiles;
		// Construct possible directions from the correctly visited tile;
		auto left = position.left();
		auto right = position.right();
		auto up = position.up();
		auto down = position.down();
		path_points.push(left);
		path_points.push(right);
		path_points.push(up);
		path_points.push(down);
		if constexpr(config::rendering) std::this_thread::sleep_for(std::chrono::microseconds(config::sleep_time_ms));
	}
	std::printf("Good tiles: %d\n", good_tiles);
}

int main() {
#ifdef RENDER
	Render render;
	auto render_callback = [&render] (bool object, Position position) {
		if(object) {
			render.draw_valid_point(position);
		} else {
			render.draw_invalid_point(position);
		}
	};
	auto thread = std::thread(calculate_movements, std::ref(render_callback));
	render.process();
	thread.join();
#else
	calculate_movements([](bool object, Position position) -> void {});
#endif
}

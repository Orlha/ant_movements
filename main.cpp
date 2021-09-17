#include <cstdio>
#include <queue>
#include <unordered_set>
#include <cstdint>

constexpr auto validity_threshold = 25;

template<typename T>
T accumulate_numbers(T n) {
	T result = 0;
	while(n != 0) {
		result += n % 10;
		n /= 10;
	}
	return result;
}

template<typename T, typename... Args>
T accumulate_numbers(T first, Args... args) {
	return accumulate_numbers(first) + accumulate_numbers(args...);
}

struct Position {
	int x;
	int y;
	Position left() const {
		auto pos = *this;
		--pos.x;
		return pos;
	}
	Position right() const {
		auto pos = *this;
		++pos.x;
		return pos;
	}
	Position up() const {
		auto pos = *this;
		--pos.y;
		return pos;
	}
	Position down() const {
		auto pos = *this;
		++pos.y;
		return pos;
	}
	bool operator==(const Position& pos) const = default;
};

bool position_validity(Position pos) {
	return accumulate_numbers(pos.x, pos.y) <= 25;
}

namespace std {

template <> struct hash<Position> {
	size_t operator()(const Position& pos) const {
		uint64_t val = static_cast<uint64_t>(pos.x);
		val <<= 32;
		val |= static_cast<uint64_t>(pos.y);
		return val;
	}
};

}

class Render {
	public:
	Render() = default;
	void draw_valid_point(Position pos) {

	}
	void draw_invalid_point(Position pos) {

	}
	private:
};

int main() {
	Render render;
	int good_tiles = 0;
	std::queue<Position> path_points;
	std::unordered_set<Position> visited_points;
	path_points.push({ 1000, 1000 });
	while(!path_points.empty()) {
		// Extract next path point;
		auto position = path_points.front();
		path_points.pop();
		if(visited_points.find(position) != visited_points.end()) {
			continue;
		}
		visited_points.insert(position);
		if(!position_validity(position)) {
			render.draw_invalid_point(position);
			continue;
		}
		render.draw_valid_point(position);
		++good_tiles;
		// Construct possible directions from there;
		auto left = position.left();
		auto right = position.right();
		auto up = position.up();
		auto down = position.down();
		path_points.push(left);
		path_points.push(right);
		path_points.push(up);
		path_points.push(down);
	}
	std::printf("Good tiles: %d\n", good_tiles);
}

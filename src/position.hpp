#pragma once
#include "utility.hpp"
#include "config.hpp"

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
	bool validity() const {
		return utility::accumulate_numbers(x, y) <= config::validity_threshold;
	}
};

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

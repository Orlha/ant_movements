#pragma once
#include <stack>
#include <queue>

namespace config {
// Tiles whose weight is above this value can't be visited;
constexpr static auto validity_threshold = 25;
// Tile size in pixels for rendering;
constexpr static auto block_size = 1.f;
// Container for path-finding type, stack for dfs, queue for bfs;
template<typename T>
using container = std::stack<T>;
// Starting coordinates;
constexpr static auto starting_x = 1000;
constexpr static auto starting_y = 1000;
// Sleep value for interval between algorithm steps when used with render;
constexpr static auto sleep_time_ms = 100;
#ifdef RENDER
constexpr static auto rendering = true;
constexpr static auto window_width = 1920;
constexpr static auto window_height = 1080;
#else
constexpr static auto rendering = false;
#endif
}

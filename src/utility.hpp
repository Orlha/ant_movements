#pragma once
#include <stack>
#include <queue>

namespace utility {

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

template<typename T>
T& access(std::queue<T>& q) {
	return q.front();
}

template<typename T>
T& access(std::stack<T>& s) {
	return s.top();
}

}

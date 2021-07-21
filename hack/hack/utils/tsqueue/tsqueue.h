#pragma once

//Related header,
//#include "../headers/common_headers.h"
//C system headers
#include <queue>
#include <mutex>
//C++ standard library headers
#include <optional>
//other libraries' headers
//#include "../define/common_define.h"

namespace hack {

template<typename T>
class TSQueue {

//factory functions, constructors and assignment operators, destructor
public:
	TSQueue() = default;
	TSQueue(const TSQueue<T>&) = delete;
	TSQueue& operator=(const TSQueue<T>&) = delete;

	TSQueue(TSQueue<T>&& other) noexcept(false) {
		std::lock_guard<std::mutex> lock(mutex_);
		if (!Empty()) {
			return;
		}
		queue_ = std::move(other.queue_);
	}

	virtual ~TSQueue() noexcept(false) {
		std::lock_guard<std::mutex> lock(mutex_);
		if (!Empty()) {
			return;
		}
	}


//all other methods
public:
	[[nodiscard]] unsigned long Size() const {
		std::lock_guard<std::mutex> lock(mutex_);
		return queue_.size();
	}

	std::optional<T> Pop() {
		std::lock_guard<std::mutex> lock(mutex_);
		if (queue_.empty()) {
			return std::nullopt;
		}
		T tmp = queue_.front();
		queue_.pop();
		return tmp;
	}

	void Push(const T& item) {
		std::lock_guard<std::mutex> lock(mutex_);
		queue_.push(item);
	}

//private methods	
private:
	// Moved out of public interface to prevent races between this
	// and pop().
	[[nodiscard]] bool Empty() const {
		return queue_.empty();
	}

	//private data members	
private:
	mutable std::mutex mutex_;
	std::queue<T> queue_;

};
	//class TSQueue
}; //namespace hack

#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include <optional>

namespace snake {

template <typename T, size_t N>
class RingBuffer {
public:
    explicit RingBuffer() = default;

    std::optional<T> pop_back() {
        if (head_ == tail_) {
            return std::nullopt;
        }
        std::optional<T> result = data_[tail_];
        tail_ = (tail_ + 1) % N;
        return result;
    }

    bool push_front(T value) {
        const size_t new_head = (head_ + 1) % N;
        if (new_head == tail_) {
            return false;
        }
        data_[head_] = value;
        head_ = new_head;
        return true;
    }

    bool pop_front() {
        if (head_ == tail_) {
            return false;
        }
        head_ = head_ == 0 ? N - 1 : head_ - 1;
        return true;
    }

    [[nodiscard]] bool empty() const {
        return head_ == tail_;
    }

    std::optional<T> front() const {
        if (head_ == tail_) {
            return std::nullopt;
        }
        if (head_ == 0) {
            return data_[N - 1];
        }
        return data_[head_ - 1];
    }

    class Iterator {
    public:
        explicit Iterator(
            T (&data)[N],
            const size_t position) : data_(data), position_(position) {}

        T& operator*() const {
            return data_[position_];
        }

        Iterator& operator++() {
            position_ = (position_ + 1) % N;
            return *this;
        }

        bool operator==(const Iterator& other) const {
            return position_ == other.position_;
        }

    private:
        T (&data_)[N];
        size_t position_ = 0;
    };

    Iterator begin() {
        return Iterator(data_, tail_);
    }

    Iterator end() {
        return Iterator(data_, head_);
    }

private:
    T data_[N];
    size_t head_ = 0;
    size_t tail_ = 0;
};

} // snake

#endif //RINGBUFFER_H

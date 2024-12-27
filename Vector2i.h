#ifndef VECTOR2I_H
#define VECTOR2I_H

class Vector2i {

public:
    constexpr Vector2i(const int x, const int y) : x_(x), y_(y) {}
    Vector2i() : x_(0), y_(0) {}

    [[nodiscard]] int x() const { return x_; }

    [[nodiscard]] int y() const { return y_; }

    [[nodiscard]] Vector2i negative() const { return {-x_, -y_}; }

    bool operator==(const Vector2i& other) const {
        return (x_ == other.x_) && (y_ == other.y_);
    }

private:
    int x_;
    int y_;
};

constexpr Vector2i UP(0, -1);
constexpr Vector2i DOWN(0, 1);
constexpr Vector2i LEFT(-1, 0);
constexpr Vector2i RIGHT(1, 0);

#endif //VECTOR2I_H

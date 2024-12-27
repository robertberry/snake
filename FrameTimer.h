#ifndef FRAMETIMER_H
#define FRAMETIMER_H

namespace snake {

class FrameTimer {

public:
    explicit FrameTimer(const int frames_per_event) : frames_per_event_(frames_per_event) {}

    bool Tick() {
        frame_++;
        if (frame_ >= frames_per_event_) {
            frame_ = 0;
            return true;
        }
        return false;
    }

    void set_frames_per_event(const int frames_per_event) {
        frames_per_event_ = frames_per_event;
    }

    [[nodiscard]] int get_frames_per_event() const {
        return frames_per_event_;
    }

private:
    int frame_ = 0;
    int frames_per_event_;
};

}

#endif //FRAMETIMER_H

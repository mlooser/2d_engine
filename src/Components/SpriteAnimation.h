#pragma once

struct SpriteAnimation {
    int numFrames = 0;
    int framesPerSecond = 0;
    bool loop = false;
    double lastUpdate = 0;
    int currentFrame = 0;

    explicit SpriteAnimation(
        const int numFrames = 1,
        const int frameSpeedRate = 1,
        const bool loop = true)
        : numFrames(numFrames),
          framesPerSecond(frameSpeedRate),
          loop(loop)
           {
        lastUpdate = 0.0;
    }
};
#pragma once

#include <basis/seadTypes.h>
#include <hostio/seadHostIONode.h>

namespace gsys {

class Model;

// Partial layout: the frame rate is consumed by update_(ModelNW*, f32).
class ModelAutoAnimation : public sead::hostio::Node {
public:
    // 0x7100c00724 (declared only): sets the current frame (Model::forceAutoAnimationFrame).
    void forceFrame(f32 frame);
    // 0x7100c00718 (declared only): updates the animation right away (Model::forceUpdateAutoAnimation).
    void forceUpdate();

private:
    friend class Model;

    u8 _8[0x30 - 8];
    f32 mFrameRate;
};

}  // namespace gsys

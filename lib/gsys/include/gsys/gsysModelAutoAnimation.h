#pragma once

#include <basis/seadTypes.h>
#include <hostio/seadHostIONode.h>

namespace gsys {

class Model;
class ModelNW;

// Partial layout: the frame rate is consumed by update_(ModelNW*, f32).
class ModelAutoAnimation : public sead::hostio::Node {
public:
    // 0x7100c00724 (declared only): sets the current frame (Model::forceAutoAnimationFrame).
    void forceFrame(f32 frame);
    // 0x7100c00718: updates the animation right away (Model::forceUpdateAutoAnimation).
    void forceUpdate();
    // 0x7100c00784 (CSV name; declared only)
    void update_(ModelNW* model, f32 delta_frame);

private:
    friend class Model;

    ModelNW* mModel;
    u8 _10[0x30 - 0x10];
    f32 mFrameRate;
};

}  // namespace gsys

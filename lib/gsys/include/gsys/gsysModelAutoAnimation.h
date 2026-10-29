#pragma once

#include <basis/seadTypes.h>
#include <container/seadPtrArray.h>
#include <hostio/seadHostIONode.h>

namespace gsys {

class Model;
class ModelNW;

// Partial layout: the frame rate is consumed by update_(ModelNW*, f32).
class ModelAutoAnimation : public sead::hostio::Node {
public:
    // Constructor 0x7100bffa14 calls setBuffer(32, ...) on three 0x110-byte fixed arrays at
    // +0, +0x110 and +0x220 and zeros the word at +0x3b0. The element types are unrecovered.
    struct AnimationRecord;
    struct InitArg {
        InitArg();
        sead::FixedPtrArray<AnimationRecord, 32> mArrays[3];
        u8 _330[0x3b0 - 0x330];
        u32 _3b0 = 0;
    };
    static_assert(sizeof(InitArg) == 0x3b8);

    // 0x7100c00724 (declared only): sets the current frame (Model::forceAutoAnimationFrame).
    void forceFrame(f32 frame);
    // 0x7100c00718: updates the animation right away (Model::forceUpdateAutoAnimation).
    void forceUpdate();
    // 0x7100c00784 (CSV name; declared only)
    void update_(ModelNW* model, f32 delta_frame);

private:
    friend class Model;

    ModelNW* mModel;
    u64 _10 = 0;
    u64 _18 = 0;
    u64 _20 = 0;
    u64 _28 = 0;
    f32 mFrameRate = 1.0f;
    u8 _34 = 8;

public:
    // 0x7100bfffd8
    ModelAutoAnimation();
    virtual ~ModelAutoAnimation();
};

}  // namespace gsys

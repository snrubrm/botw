#pragma once

#include "Game/UI/euiControlBase.h"

namespace sead {
class Heap;
}

namespace nn::ui2d {
class ControlSrc;
}

namespace eui {

class Animator;
class LayoutEx;

// A gauge whose value trails the target value (CSV eui::TraceGaugeControl; 0x70 bytes, vtable 0x24c78f0). Field names
// are guesses.
class TraceGaugeControl : public ControlBase {
public:
    NN_RUNTIME_TYPEINFO(ControlBase)
    const char* getClassName() const override { return "TraceGaugeControl"; }

    TraceGaugeControl();
    TraceGaugeControl(const TraceGaugeControl& other, LayoutEx* layout, sead::Heap* heap);

    void Update(f32 dt) override;

    // 0x7100bda308
    void initialize(const nn::ui2d::ControlSrc& src, LayoutEx* layout);
    // 0x7100bda840 / 0x7100bda880 (values outside [0, 100] / [0, 1] are ignored)
    void setTracingSpeed(f32 speed);
    void setTracingFraction(f32 fraction);

    /* 0x28 */ Animator* mAnimA = nullptr;
    /* 0x30 */ Animator* mAnimB = nullptr;
    /* 0x38 */ Animator* mAnimC = nullptr;
    /* 0x40 */ Animator* mAnimD = nullptr;
    /* 0x48 */ f32 mTracingSpeed = 100.0f;
    /* 0x4c */ f32 _4c = 100.0f;
    /* 0x50 */ f32 _50 = 100.0f;
    /* 0x54 */ f32 _54 = 2.0f;
    /* 0x58 */ f32 mTracingFraction = 0.0f;
    /* 0x5c */ f32 _5c = 20.0f;
    /* 0x60 */ f32 _60 = 0.0f;
    /* 0x64 */ f32 _64 = 0.0f;
    /* 0x68 */ f32 _68 = 0.0f;
    /* 0x6c */ bool _6c = true;
};
static_assert(sizeof(TraceGaugeControl) == 0x70);

}  // namespace eui

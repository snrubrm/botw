#include "Game/UI/euiTraceGaugeControl.h"
#include "Game/UI/euiAnimator.h"
#include "Game/UI/euiLayoutEx.h"

namespace eui {

// 0x7100bda170
TraceGaugeControl::TraceGaugeControl() = default;

// 0x7100bda1d0
TraceGaugeControl::TraceGaugeControl(const TraceGaugeControl& other, LayoutEx* layout,
                                     sead::Heap* heap)
    : _54(other._54), mTracingFraction(other.mTracingFraction), _68(other._68) {
    mLayout = layout;
    mName = other.mName;
    mAnimA = layout->createAnimatorAuto(other.mAnimA->mName, true);
    mAnimB = layout->createAnimatorAuto(other.mAnimB->mName, true);
    mAnimA->mFlags &= ~0x20;
    mAnimB->mFlags &= ~0x20;
    if (other.mAnimC) {
        mAnimC = layout->createAnimatorAuto(other.mAnimC->mName, true);
        mAnimC->mFlags &= ~0x20;
    }
    if (other.mAnimD) {
        mAnimD = layout->createAnimatorAuto(other.mAnimD->mName, true);
        mAnimD->mFlags &= ~0x20;
    }
}

// 0x7100bda840
void TraceGaugeControl::setTracingSpeed(f32 speed) {
    if (speed >= 0.0f && speed <= 100.0f)
        mTracingSpeed = speed;
}

// 0x7100bda880
void TraceGaugeControl::setTracingFraction(f32 fraction) {
    if (fraction >= 0.0f && fraction <= 1.0f)
        mTracingFraction = fraction;
}

}  // namespace eui

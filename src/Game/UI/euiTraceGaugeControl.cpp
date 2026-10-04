#include "Game/UI/euiTraceGaugeControl.h"
#include <nn/ui2d/Pane.h>
#include <nn/ui2d/ResExtUserData.h>
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

// 0x7100bda308
void TraceGaugeControl::initialize(const nn::ui2d::ControlSrc& src, LayoutEx* layout) {
    mLayout = layout;
    mName = layout->GetPane()->GetParent() ? layout->GetPane()->GetName() : layout->mName;
    mAnimA = layout->createAnimatorAuto(src.FindFunctionalAnimName("GaugeRatio"), true);
    mAnimB = layout->createAnimatorAuto(src.FindFunctionalAnimName("TraceRatio"), true);
    mAnimA->mFlags &= ~0x20;
    mAnimB->mFlags &= ~0x20;
    const char* color = src.FindFunctionalAnimName("TraceColor");
    if (color && *color) {
        mAnimC = layout->tryCreateAnimatorAutoWithWarning(color, true);
        if (mAnimC)
            mAnimC->mFlags &= ~0x20;
    }
    const char* shortage = src.FindFunctionalAnimName("Shortage");
    if (shortage && *shortage) {
        mAnimD = layout->tryCreateAnimatorAutoWithWarning(shortage, true);
        if (mAnimD)
            mAnimD->mFlags &= ~0x20;
    }
    const auto* speed = layout->GetPane()->FindExtUserDataByName("TracingSpeed");
    if (!speed)
        speed = src.FindExtUserDataByName("TracingSpeed");
    if (speed && speed->GetCount())
        _54 = speed->GetFloatArray()[0];
    const auto* fraction = layout->GetPane()->FindExtUserDataByName("TracingFraction");
    if (!fraction)
        fraction = src.FindExtUserDataByName("TracingFraction");
    if (fraction && fraction->GetCount())
        mTracingFraction = fraction->GetFloatArray()[0];
    const auto* wait = layout->GetPane()->FindExtUserDataByName("TracingWait");
    if (!wait)
        wait = src.FindExtUserDataByName("TracingWait");
    if (wait && wait->GetCount())
        _68 = wait->GetFloatArray()[0];
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

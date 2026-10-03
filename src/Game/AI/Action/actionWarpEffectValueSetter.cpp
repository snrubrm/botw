#include "Game/AI/Action/actionWarpEffectValueSetter.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "math/seadMathCalcCommon.h"

namespace uking::action {

WarpEffectValueSetter::WarpEffectValueSetter(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WarpEffectValueSetter::~WarpEffectValueSetter() = default;

bool WarpEffectValueSetter::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WarpEffectValueSetter::enter_(ksys::act::ai::InlineParamPack* params) {
    const f32 frame = *mSetFrame_d;
    const f32 time = frame > 0.0f ? frame : 1.0f;
    _3c = time;
    _30 = ksys::Timer(time, time);
    const f32 ratio = sead::Mathf::clamp(_30.value / _3c, 0.0f, 1.0f);
    if (mActor) {
        if (*mChangeType_d)
            mActor->x_3(1.0f - ratio);
        else
            mActor->x_3(ratio);
    }
}

void WarpEffectValueSetter::leave_() {
    ksys::act::ai::Action::leave_();
}

void WarpEffectValueSetter::loadParams_() {
    getDynamicParam(&mChangeType_d, "ChangeType");
    getDynamicParam(&mSetFrame_d, "SetFrame");
}

void WarpEffectValueSetter::calc_() {
    if (isFinished() || isFailed())
        return;
    _30.update();
    const f32 ratio = sead::Mathf::clamp(_30.value / _3c, 0.0f, 1.0f);
    if (mActor) {
        if (*mChangeType_d)
            mActor->x_3(1.0f - ratio);
        else
            mActor->x_3(ratio);
    }
    if (_30.value <= sead::Mathf::epsilon())
        setFinished();
}

}  // namespace uking::action

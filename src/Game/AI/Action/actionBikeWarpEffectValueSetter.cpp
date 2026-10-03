#include "Game/AI/Action/actionBikeWarpEffectValueSetter.h"
#include "Game/Actor/actMotorcycle.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "math/seadMathCalcCommon.h"

namespace uking::action {

BikeWarpEffectValueSetter::BikeWarpEffectValueSetter(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

BikeWarpEffectValueSetter::~BikeWarpEffectValueSetter() = default;

bool BikeWarpEffectValueSetter::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void BikeWarpEffectValueSetter::enter_(ksys::act::ai::InlineParamPack* params) {
    const f32 frame = *mSetFrame_d;
    const f32 time = frame > 0.0f ? frame : 1.0f;
    _3c = time;
    _30 = ksys::Timer(time, time);
    sub_71000509C4();
}

void BikeWarpEffectValueSetter::leave_() {
    ksys::act::ai::Action::leave_();
}

void BikeWarpEffectValueSetter::loadParams_() {
    getDynamicParam(&mChangeType_d, "ChangeType");
    getDynamicParam(&mSetFrame_d, "SetFrame");
}

void BikeWarpEffectValueSetter::sub_71000509C4() {
    const f32 ratio = sead::Mathf::clamp(_30.value / _3c, 0.0f, 1.0f);
    if (auto* motorcycle = sead::DynamicCast<uking::act::Motorcycle>(mActor)) {
        if (*mChangeType_d)
            motorcycle->sub_710007A74C(1.0f - ratio);
        else
            motorcycle->sub_710007A74C(ratio);
    }
}

void BikeWarpEffectValueSetter::calc_() {
    if (isFinished() || isFailed())
        return;
    _30.update();
    sub_71000509C4();
    if (_30.value <= sead::Mathf::epsilon())
        setFinished();
}

}  // namespace uking::action

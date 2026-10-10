#include "Game/AI/Action/actionMotorcycleAppear.h"
#include "Game/Actor/actMotorcycle.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/System/Timer.h"
#include "math/seadMathCalcCommon.h"

namespace uking::action {

MotorcycleAppear::MotorcycleAppear(const InitArg& arg) : ksys::act::ai::Action(arg) {}

MotorcycleAppear::~MotorcycleAppear() = default;

bool MotorcycleAppear::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void MotorcycleAppear::enter_(ksys::act::ai::InlineParamPack* params) {
    xlinkSearchAndEmit(mActor, "DLC2_Bike_WarpAppear", 2, nullptr);
    if (auto* motorcycle = sead::DynamicCast<uking::act::Motorcycle>(mActor)) {
        motorcycle->sub_710007A938();
        motorcycle->sub_7100071998();
    }
    _38 = 0.0f;
}

void MotorcycleAppear::leave_() {
    auto* actor = mActor;
    if (sead::DynamicCast<uking::act::Motorcycle>(actor))
        mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_20);
}

void MotorcycleAppear::loadParams_() {
    getStaticParam(&mHideFrames_s, "HideFrames");
    getStaticParam(&mModelWarpEffectFrames_s, "ModelWarpEffectFrames");
    getStaticParam(&mEndFrames_s, "EndFrames");
}

void MotorcycleAppear::calc_() {
    // NON_MATCHING: the original loads mHideFrames_s once for the compare and the sum, and reloads
    // mActor / the flags before the second compare (load scheduling differs)
    auto* actor = mActor;
    auto* motorcycle = sead::DynamicCast<uking::act::Motorcycle>(actor);
    if (!motorcycle) {
        setFailed();
        return;
    }
    motorcycle->setAccelMaybe(0.0f);
    motorcycle->_e40 = 1.0f;
    motorcycle->setLeftStickX(0.0f);
    motorcycle->setLeftStickY(0.0f);
    const f32 time = _38;
    if (time < *mHideFrames_s) {
        mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_20);
    } else {
        mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_20);
        if (time < *mHideFrames_s + *mModelWarpEffectFrames_s) {
            const f32 ratio = sead::Mathf::clamp(
                1.0f - (time - *mHideFrames_s) / *mModelWarpEffectFrames_s, 0.0f, 1.0f);
            mActor->x_3(ratio);
        } else {
            mActor->x_3(0.0f);
            setFinished();
            return;
        }
    }
    if (time >= *mEndFrames_s)
        setFinished();
    ksys::Timer::update(&_38, 1.0f);
}

}  // namespace uking::action

#include "Game/AI/Action/actionMotorcycleDisappear.h"
#include "Game/Actor/actMotorcycle.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/System/Timer.h"
#include "math/seadMathCalcCommon.h"

namespace uking::action {

MotorcycleDisappear::MotorcycleDisappear(const InitArg& arg) : ksys::act::ai::Action(arg) {}

MotorcycleDisappear::~MotorcycleDisappear() = default;

bool MotorcycleDisappear::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void MotorcycleDisappear::enter_(ksys::act::ai::InlineParamPack* params) {
    xlinkSearchAndEmit(mActor, mDisappearEffectName_d.cstr(), 2, nullptr);
    if (auto* motorcycle = sead::DynamicCast<uking::act::Motorcycle>(mActor))
        motorcycle->sub_710007F8F8();
    _38 = 0.0f;
}

void MotorcycleDisappear::leave_() {
    auto* actor = mActor;
    if (sead::DynamicCast<uking::act::Motorcycle>(actor)) {
        actor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_20);
        actor->x_3(1.0f);
    }
}

void MotorcycleDisappear::loadParams_() {
    getStaticParam(&mModelWarpEffectFrames_s, "ModelWarpEffectFrames");
    getDynamicParam(&mDisappearEffectName_d, "DisappearEffectName");
}

void MotorcycleDisappear::calc_() {
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
    if (_38 < *mModelWarpEffectFrames_s) {
        const f32 ratio = sead::Mathf::clamp(_38 / *mModelWarpEffectFrames_s, 0.0f, 1.0f);
        actor->x_3(ratio);
        ksys::Timer::update(&_38, 1.0f);
        return;
    }
    actor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_20);
    actor->x_3(1.0f);
    setFinished();
    motorcycle->sub_710007A928();
}

}  // namespace uking::action

#include "Game/AI/Action/actionWaterEmitter.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "gsys/gsysModelAccessKey.h"
#include "gsys/gsysModel.h"

namespace uking::action {

WaterEmitter::WaterEmitter(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WaterEmitter::~WaterEmitter() = default;

bool WaterEmitter::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WaterEmitter::enter_(ksys::act::ai::InlineParamPack* params) {
    if (!mBindNodeName_s.isEmpty()) {
        if (auto* model = mActor->getModel())
            _70.search(model, mBindNodeName_s);
    }
    _68 = 1.0f;
    _60 = 0;
    mFlags.set(Flag::Changeable);
}

void WaterEmitter::leave_() {
    ksys::act::ai::Action::leave_();
}

void WaterEmitter::loadParams_() {
    getStaticParam(&mEffectType_s, "EffectType");
    getStaticParam(&mRadius_s, "Radius");
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mInterval_s, "Interval");
    getStaticParam(&mBindNodeName_s, "BindNodeName");
    getStaticParam(&mOffset_s, "Offset");
    getStaticParam(&mVelocityDir_s, "VelocityDir");
}

void WaterEmitter::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

#include "Game/AI/Action/actionForceGetUpWaterFloatFreeze.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::action {

ForceGetUpWaterFloatFreeze::ForceGetUpWaterFloatFreeze(const InitArg& arg)
    : WaterFloatFreeze(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
ForceGetUpWaterFloatFreeze::~ForceGetUpWaterFloatFreeze() {
    ;
}

bool ForceGetUpWaterFloatFreeze::init_(sead::Heap* heap) {
    return WaterFloatFreeze::init_(heap);
}

void ForceGetUpWaterFloatFreeze::enter_(ksys::act::ai::InlineParamPack* params) {
    WaterFloatFreeze::enter_(params);
}

void ForceGetUpWaterFloatFreeze::leave_() {
    WaterFloatFreeze::leave_();
}

void ForceGetUpWaterFloatFreeze::loadParams_() {
    WaterFloatFreeze::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void ForceGetUpWaterFloatFreeze::calc_() {
    if (_88 == 2) {
        WaterFloatFreeze::calc_();
        return;
    }
    if (_88 == 1) {
        ksys::act::sub_7100EE5980(mActor, sead::Vector3f::zero);
        ksys::act::sub_7100EE5A14(mActor, sead::Vector3f::zero);
        ++_88;
    } else {
        _88 = 1;
    }
}

}  // namespace uking::action

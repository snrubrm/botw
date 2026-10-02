#include "Game/AI/AI/aiRemainsWindBatteryAttack.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::ai {

RemainsWindBatteryAttack::RemainsWindBatteryAttack(const InitArg& arg)
    : GuardianBeamAttackBase(arg) {}

RemainsWindBatteryAttack::~RemainsWindBatteryAttack() {
    for (s32 i = 0; i < 5; ++i) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&_38[i], &accessor);
        accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    }
}

bool RemainsWindBatteryAttack::init_(sead::Heap* heap) {
    return GuardianBeamAttackBase::init_(heap);
}

void RemainsWindBatteryAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    GuardianBeamAttackBase::enter_(params);
    changeChild("待機");
}

void RemainsWindBatteryAttack::leave_() {
    GuardianBeamAttackBase::leave_();
}

void RemainsWindBatteryAttack::loadParams_() {
    GuardianBeamAttackBase::loadParams_();
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai

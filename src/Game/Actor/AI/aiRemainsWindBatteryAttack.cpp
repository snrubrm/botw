#include "Game/Actor/AI/aiRemainsWindBatteryAttack.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"

namespace uking::ai {

RemainsWindBatteryAttack::RemainsWindBatteryAttack(const InitArg& arg)
    : GuardianCommonBeamAttack(arg) {}

RemainsWindBatteryAttack::~RemainsWindBatteryAttack() {
    for (s32 i = 0; i < 5; ++i) {
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&_38[i], &accessor);
        accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    }
}

bool RemainsWindBatteryAttack::init_(sead::Heap* heap) {
    return GuardianCommonBeamAttack::init_(heap);
}

void RemainsWindBatteryAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    GuardianCommonBeamAttack::enter_(params);
    changeChild("待機");
}

void RemainsWindBatteryAttack::leave_() {
    GuardianCommonBeamAttack::leave_();
}

void RemainsWindBatteryAttack::loadParams_() {
    GuardianCommonBeamAttack::loadParams_();
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai

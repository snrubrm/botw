#include "Game/AI/Action/actionStopCliffTongueAttack.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::action {

StopCliffTongueAttack::StopCliffTongueAttack(const InitArg& arg) : OnCliffWait(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
StopCliffTongueAttack::~StopCliffTongueAttack() {
    ;
}

bool StopCliffTongueAttack::init_(sead::Heap* heap) {
    return OnCliffWait::init_(heap);
}

void StopCliffTongueAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    OnCliffWait::enter_(params);
    _68 = sub_71005DB4DC(mActor);
    _6c = sub_71005DB4FC(mActor);
    _64 = 0;
}

void StopCliffTongueAttack::leave_() {
    OnCliffWait::leave_();
    sub_71007A2D7C(mActor, mRigidName_s);
    sub_71005DB3EC(mActor);
}

// NON_MATCHING: the original computes both member addresses (this + 0x48 / 0x58) and the SafeString vtable
// into callee-saved registers up front (one more spilled register than ours).
void StopCliffTongueAttack::loadParams_() {
    OnCliffWait::loadParams_();
    getStaticParam(&mRigidName_s, "RigidName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void StopCliffTongueAttack::calc_() {
    OnCliffWait::calc_();
}

}  // namespace uking::action

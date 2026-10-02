#include "Game/AI/AI/aiSnowOctarockBattle.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"

namespace uking::ai {

SnowOctarockBattle::SnowOctarockBattle(const InitArg& arg) : EnemyBattle(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
SnowOctarockBattle::~SnowOctarockBattle() {
    ;
}

bool SnowOctarockBattle::init_(sead::Heap* heap) {
    return EnemyBattle::init_(heap);
}

void SnowOctarockBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    _b0 = 0;
    EnemyBattle::enter_(params);
}

void SnowOctarockBattle::leave_() {
    EnemyBattle::leave_();
}

void SnowOctarockBattle::loadParams_() {
    EnemyBattle::loadParams_();
    getStaticParam(&mVacuumPartsKey_s, "VacuumPartsKey");
    getStaticParam(&mShootActorKey_s, "ShootActorKey");
}

void SnowOctarockBattle::m38() {
    if (!sub_710072E1B4(mActor, true))
        ++_b0;
    EnemyBattle::m38();
}

// NON_MATCHING: block placement (the original moves the setFailed path to the end)
void SnowOctarockBattle::calc_() {
    if (isFinished() || isFailed())
        return;

    if (isCurrentChild("戦闘攻撃")) {
        auto* child = getCurrentChild();
        if ((child->isFinished() || child->isFailed()) && _b0 >= 5) {
            setFailed();
            return;
        }
    }

    EnemyBattle::calc_();
    if (_b0 > 0 && sub_710072E1B4(mActor, true))
        _b0 = 0;
    getCurrentChild()->setDynamicParam(sub_71005D9548(mActor), "TargetVel");
}

void SnowOctarockBattle::m43(ksys::act::ai::InlineParamPack* params) {
    params->addVec3(sub_71005D9548(mActor), "TargetVel", -1);
}

}  // namespace uking::ai

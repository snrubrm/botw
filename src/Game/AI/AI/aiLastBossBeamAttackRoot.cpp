#include "Game/AI/AI/aiLastBossBeamAttackRoot.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::ai {

LastBossBeamAttackRoot::LastBossBeamAttackRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

// NON_MATCHING: the original builds the name arguments before computing `enemy + 0x1128` (scheduling)
LastBossBeamAttackRoot::~LastBossBeamAttackRoot() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        if (enemy->getActorPartsActor("Beam").hasProcInCalcState()) {
            ksys::act::ActorConstDataAccess accessor;
            ksys::act::acquireActor(&enemy->getActorPartsActor("Beam"), &accessor);
            accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
        }
        enemy->sub_7100D3CFEC("Beam");
    }
}

bool LastBossBeamAttackRoot::init_(sead::Heap* heap) {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->sub_7100D3CED8("Beam", heap);
    sub_710047555C();
    return true;
}

void LastBossBeamAttackRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

// NON_MATCHING: branch layout (the original returns the constants 1 / 0 from separate blocks; ours
// ends with `and w0, w0, #1` on isFailed's result)
bool LastBossBeamAttackRoot::isFinished() const {
    if (getCurrentChild()) {
        if (isCurrentChild("発射")) {
            auto* child = getCurrentChild();
            if (child->isFinished() || child->isFailed())
                return true;
        }
    }
    return false;
}

bool LastBossBeamAttackRoot::isChangeable() const {
    return *mIsChangeable_s;
}

void LastBossBeamAttackRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LastBossBeamAttackRoot::loadParams_() {
    getStaticParam(&mAttackPowerForPlayer_s, "AttackPowerForPlayer");
    getStaticParam(&mAttackPower_s, "AttackPower");
    getStaticParam(&mAtMinDamage_s, "AtMinDamage");
    getStaticParam(&mAddAttackPower_s, "AddAttackPower");
    getStaticParam(&mWaitTime_s, "WaitTime");
    getStaticParam(&mKeepDistance_s, "KeepDistance");
    getStaticParam(&mMoveSpeed_s, "MoveSpeed");
    getStaticParam(&mInitSpeed_s, "InitSpeed");
    getStaticParam(&mAccel_s, "Accel");
    getStaticParam(&mKeepDistanceRand_s, "KeepDistanceRand");
    getStaticParam(&mRandKeepFrame_s, "RandKeepFrame");
    getStaticParam(&mBrakeStartFrame_s, "BrakeStartFrame");
    getStaticParam(&mMoveYSpeed_s, "MoveYSpeed");
    getStaticParam(&mIsMove_s, "IsMove");
    getStaticParam(&mIsChangeable_s, "IsChangeable");
    getStaticParam(&mIsCreateGuardEffect_s, "IsCreateGuardEffect");
    getStaticParam(&mReflectOffset_s, "ReflectOffset");
}

}  // namespace uking::ai

#include "Game/AI/AI/aiDashAndAttack.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

DashAndAttack::DashAndAttack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

DashAndAttack::~DashAndAttack() = default;

bool DashAndAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: Target vector and parameter-pack stack placement differs.
void DashAndAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    sead::Vector3f target;
    sub_710035B9E0(&target);
    if (*mParams.mIsAbleSkipNear_s && sub_710035BB34()) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(target, "TargetPos", -1);
        changeChild("斬り付け", &pack);
    } else {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(target, "TargetPos", -1);
        changeChild("駆け寄り", &pack);
    }
}

void DashAndAttack::leave_() {
    ksys::act::ai::Ai::leave_();
}

void DashAndAttack::loadParams_() {
    getStaticParam(&mParams.mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mParams.mAttackFrame_s, "AttackFrame");
    getStaticParam(&mParams.mOffsetLR_s, "OffsetLR");
    getStaticParam(&mParams.mAttackRange_s, "AttackRange");
    getStaticParam(&mParams.mTiredAngle_s, "TiredAngle");
    getStaticParam(&mParams.mTargetSpeedClampMax_s, "TargetSpeedClampMax");
    getStaticParam(&mParams.mIsAbleSkipNear_s, "IsAbleSkipNear");
    getDynamicParam(&mParams.mTargetPos_d, "TargetPos");
    getDynamicParam(&mParams.mTargetVel_d, "TargetVel");
}

}  // namespace uking::ai

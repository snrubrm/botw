#include "Game/AI/AI/aiWolfLinkRushAttack.h"
#include "Game/Actor/actWolfLink.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

WolfLinkRushAttack::WolfLinkRushAttack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WolfLinkRushAttack::~WolfLinkRushAttack() = default;

bool WolfLinkRushAttack::init_(sead::Heap* heap) {
    _58 = sead::DynamicCast<act::WolfLink>(mActor);
    return _58 != nullptr;
}

void WolfLinkRushAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* controller = mActor->getCharacterController();
    mActor->m45();
    if (!controller) {
        setFailed();
        return;
    }

    if (!sub_710060C1E4(true))
        setFailed();

    _60 = ksys::Timer(*mAllowUpdateTimerLength_s, *mAllowUpdateTimerLength_s);

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(_6c, "TargetPos", -1);
    changeChild("突進", &pack);
}

void WolfLinkRushAttack::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WolfLinkRushAttack::loadParams_() {
    getStaticParam(&mAttackPosOffsetLength_s, "AttackPosOffsetLength");
    getStaticParam(&mAllowUpdateTimerLength_s, "AllowUpdateTimerLength");
    getStaticParam(&mCheckSafeGround_s, "CheckSafeGround");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai

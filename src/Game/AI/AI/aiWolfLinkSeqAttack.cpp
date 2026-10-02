#include "Game/AI/AI/aiWolfLinkSeqAttack.h"
#include "Game/Actor/actWolfLink.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::ai {

WolfLinkSeqAttack::WolfLinkSeqAttack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WolfLinkSeqAttack::~WolfLinkSeqAttack() = default;

bool WolfLinkSeqAttack::init_(sead::Heap* heap) {
    _60 = sead::DynamicCast<act::WolfLink>(mActor);
    return _60 != nullptr;
}

void WolfLinkSeqAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void WolfLinkSeqAttack::leave_() {
    if (auto* nav = mActor->m45())
        nav->sub_7100F7D350();
    else
        setFailed();
}

void WolfLinkSeqAttack::loadParams_() {
    getStaticParam(&mDistBeginAttackAnimation_s, "DistBeginAttackAnimation");
    getStaticParam(&mAngleReqBeginAttackAnimationMin_s, "AngleReqBeginAttackAnimationMin");
    getStaticParam(&mAngleReqBeginAttackAnimationMax_s, "AngleReqBeginAttackAnimationMax");
    getStaticParam(&mPlayOnMissAI_s, "PlayOnMissAI");
    getStaticParam(&mChargeChainAttackOnHit_s, "ChargeChainAttackOnHit");
}

}  // namespace uking::ai

#include "Game/AI/AI/aiWolfLinkSeqAttack.h"
#include "Game/Actor/actWolfLink.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::ai {

WolfLinkSeqAttack::WolfLinkSeqAttack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WolfLinkSeqAttack::~WolfLinkSeqAttack() = default;

bool WolfLinkSeqAttack::init_(sead::Heap* heap) {
    _60 = sead::DynamicCast<act::WolfLink>(mActor);
    return _60 != nullptr;
}

// NON_MATCHING: the navigation-result flag uses a separate null comparison.
void WolfLinkSeqAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    _68 = false;
    ksys::act::ActorConstDataAccess accessor;
    if (ksys::act::acquireActor(&_60->_c48._8, &accessor)) {
        auto* nav = mActor->m45();
        auto* other = accessor.sub_7100D0F57C();
        if (nav) {
            if (other)
                nav->sub_7100F7D1B4(other);
            _69 = other != nullptr;
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(_60->_c48._18, "TargetPos", -1);
            changeChild("攻撃前", &pack);
            return;
        }
    }
    setFailed();
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

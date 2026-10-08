#include "Game/AI/AI/aiWolfLinkChainAttack.h"
#include "Game/Actor/actWolfLink.h"
#include "Game/AI/aiAwarenessFilters.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::ai {

// NON_MATCHING: store scheduling (the target writes _a8/_b0/_c0.. before the array)
WolfLinkChainAttack::WolfLinkChainAttack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WolfLinkChainAttack::~WolfLinkChainAttack() = default;

bool WolfLinkChainAttack::init_(sead::Heap* heap) {
    _c8 = sead::DynamicCast<act::WolfLink>(mActor);
    return _c8 != nullptr;
}

void WolfLinkChainAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void WolfLinkChainAttack::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WolfLinkChainAttack::loadParams_() {
    getStaticParam(&mNumAttacks_s, "NumAttacks");
    getStaticParam(&mAnimalUnitRate_s, "AnimalUnitRate");
    getStaticParam(&mBeginEndAnimASPlayRate_s, "BeginEndAnimASPlayRate");
    getStaticParam(&mTurnAnimPlayRate_s, "TurnAnimPlayRate");
    getStaticParam(&mAttackAnimPlayRate_s, "AttackAnimPlayRate");
    getStaticParam(&mAttackAnimMinDistance_s, "AttackAnimMinDistance");
    getStaticParam(&mAttackDistanceOffset_s, "AttackDistanceOffset");
    getStaticParam(&mIsInvincible_s, "IsInvincible");
    getStaticParam(&mIsIncrementHitOnMiss_s, "IsIncrementHitOnMiss");
}

// NON_MATCHING: the original keeps the awareness pointer in a scratch register and forms &_8 later (no pre-index).
// 0x71006041a8 (placeholder name): the number of living actors in the wolf's awareness list
s32 WolfLinkChainAttack::sub_71006041A8() {
    auto* awareness = _c8->getAwareness();
    if (!awareness || awareness->_8.size() < 1)
        return 0;
    const s32 count = awareness->_8.size();
    s32 num_alive = 0;
    Unk_7102451830 filter;
    for (s32 i = 0; i < count; ++i) {
        auto* entry = ksys::act::sub_7100D7EEE8(&awareness->_8, &filter);
        if (!entry)
            break;
        ksys::act::ActorConstDataAccess accessor;
        if (ksys::act::acquireActor(&entry->_0.mLink, &accessor) && accessor.getLife() > 0)
            ++num_alive;
    }
    return num_alive;
}

}  // namespace uking::ai

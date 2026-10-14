#include "Game/Actor/AI/aiWolfLinkChainAttack.h"
#include "Game/Actor/actWolfLink.h"
#include "Game/Actor/aiAwarenessFilters.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "Game/Actor/actRideable.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include <math/seadMathCalcCommon.h>

namespace uking::ai {

// NON_MATCHING: store scheduling (the target writes _a8/_b0/_c0.. before the array)
WolfLinkChainAttack::WolfLinkChainAttack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WolfLinkChainAttack::~WolfLinkChainAttack() = default;

bool WolfLinkChainAttack::init_(sead::Heap* heap) {
    _c8 = sead::DynamicCast<act::WolfLink>(mActor);
    return _c8 != nullptr;
}

void WolfLinkChainAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    _c4 = 0;
    _80.fill(-1);
    _c0 = false;
    if (*mIsInvincible_s)
        _c8->sub_71002F3148(0, false);
    _c8->_1698 |= 0x200;
    auto* controller = mActor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }
    controller->enableContactLayer(ksys::phys::ContactLayer::EntityNPC);
    controller->enableContactLayer(ksys::phys::ContactLayer::EntityRagdoll);
    auto* rideable = mActor->m132();
    rideable->_154 = *mAnimalUnitRate_s;
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("攻撃前", &pack);
}

// NON_MATCHING: regalloc (the original keeps the per-attack delta in s0 and loads _1688 into s1)
void WolfLinkChainAttack::leave_() {
    if (*mIsInvincible_s)
        _c8->sub_71002F31BC();
    _c8->_1698 &= ~0x200;
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F60604();
        controller->sub_7100F62DD0(1.0f);
    }
    mActor->m132()->_154 = 1.0f;
    _c8->_1688 = sead::Mathf::clamp(_c8->_1688 + (-100.0f / *mNumAttacks_s) * _c4, 0.0f, 100.0f);
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
        ksys::act::ActorLinkConstDataAccess accessor;
        if (ksys::act::acquireActor(&entry->_0.mLink, &accessor) && accessor.getLife() > 0)
            ++num_alive;
    }
    return num_alive;
}

}  // namespace uking::ai

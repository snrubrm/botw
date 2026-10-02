#include "Game/AI/AI/aiAssassinBossFirstBattle.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include <prim/seadSafeString.h>
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

AssassinBossFirstBattle::AssassinBossFirstBattle(const InitArg& arg) : EnemyBattle(arg) {}

AssassinBossFirstBattle::~AssassinBossFirstBattle() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        sead::FixedSafeString<32> name;
        for (int i = 0; i < *mIronBallNum_s; ++i) {
            name.format("%s%d", mIronBallKeyName_s.cstr(), i);
            enemy->sub_7100D3CFEC(name);
        }
    }
    _b8.freeBuffer();
}

// NON_MATCHING: the original computes &_b8[i] before loading mActor in the last loop
bool AssassinBossFirstBattle::init_(sead::Heap* heap) {
    const s32 num = *mIronBallNum_s;
    if (num > 0)
        _b8.tryAllocBuffer(num, heap);
    if (!_b8.getBufferPtr())
        return false;

    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        sead::FixedSafeString<32> name;
        for (int i = 0; i < *mIronBallNum_s; ++i) {
            name.format("%s%d", mIronBallKeyName_s.cstr(), i);
            enemy->sub_7100D3CED8(name, heap);
        }
    }

    for (int i = 0; i < *mIronBallNum_s; ++i)
        _b8[i]._8 = &mActor->getMessageTransceiver();
    return true;
}

void AssassinBossFirstBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyBattle::enter_(params);
    _cc = 10;
    _d0 = 15;
}

// NON_MATCHING: scheduling of the y*y = 0 term (same as m40)
void AssassinBossFirstBattle::calc_() {
    if (getCurrentChild()->isChangeable() && isCurrentChild("戦闘攻撃")) {
        auto* actor = mActor;
        sead::Vector3f diff = sub_71005D9330(actor) - actor->getMtx().getTranslation();
        diff.y = 0.0f;
        if (diff.length() <= *mAttackInterseptDist_s) {
            sub_710031657C(5, 45);
            m37();
            return;
        }
    }
    EnemyBattle::calc_();
}

void AssassinBossFirstBattle::leave_() {
    EnemyBattle::leave_();
    sub_710031657C(6, 0);
}

void AssassinBossFirstBattle::loadParams_() {
    EnemyBattle::loadParams_();
    getStaticParam(&mIronBallNum_s, "IronBallNum");
    getStaticParam(&mIronBallKeyName_s, "IronBallKeyName");
    getStaticParam(&mGuardAngle_s, "GuardAngle");
    getStaticParam(&mAttackInterseptDist_s, "AttackInterseptDist");
}

// NON_MATCHING: scheduling of the y*y = 0 term
bool AssassinBossFirstBattle::m40() {
    auto* actor = mActor;
    sead::Vector3f diff = sub_71005D9330(actor) - actor->getMtx().getTranslation();
    diff.y = 0.0f;
    if (diff.length() <= *mAttackInterseptDist_s)
        return false;
    return EnemyBattle::m40();
}

bool AssassinBossFirstBattle::m41() {
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy)
        return true;

    sead::FixedSafeString<32> name;
    for (int i = 0; i < *mIronBallNum_s; ++i) {
        name.format("%s%d", mIronBallKeyName_s.cstr(), i);
        auto& link = enemy->getActorPartsActor(name);
        if (!link.hasProc() || link.hasProcInCalcState())
            return false;
    }
    return true;
}

}  // namespace uking::ai

#include "Game/AI/AI/aiAssassinBossRoot.h"
#include <prim/seadSafeString.h>
#include "Game/Actor/actEnemy.h"
#include "Game/Damage/dmgDamageManagerBase.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::ai {

// NON_MATCHING: store scheduling (the original zeroes mBattleAvoidNum_s first)
AssassinBossRoot::AssassinBossRoot(const InitArg& arg) : AssassinBossRootBase(arg) {}

AssassinBossRoot::~AssassinBossRoot() {
    if (!mIronBallNum_s)
        return;

    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy)
        return;

    sead::FixedSafeString<32> name;
    for (int i = 0; i < *mIronBallNum_s; ++i) {
        name.format("IronBall%d", i);
        auto& link = enemy->getActorPartsActor(name);
        if (link.hasProc()) {
            ksys::act::ActorConstDataAccess accessor;
            ksys::act::acquireActor(&link, &accessor);
            accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
        }
        enemy->sub_7100D3CFEC(name);
    }

    auto& link = enemy->getActorPartsActor("SpareBall0");
    if (link.hasProc()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&link, &accessor);
        accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    }
    enemy->sub_7100D3CFEC("SpareBall0");
}

bool AssassinBossRoot::init_(sead::Heap* heap) {
    if (!AssassinBossRootBase::init_(heap))
        return false;

    for (int i = 0; i < *mIronBallNum_s; ++i)
        sub_710031BBC4("IronBall", "AssassinRockBall", i, heap);
    sub_710031BBC4("SpareBall", "AssassinIronBall", 0, heap);
    return true;
}

void AssassinBossRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    AssassinBossRootBase::enter_(params);
    sub_7100319AB4();
    setDamageCallbackTiming(mActor, 0, &_310);
    sub_71007A3910(mActor, "TgtBarrier");
    _400 = false;
    _310._24 = false;
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F63388(true, -1);
}

void AssassinBossRoot::sub_7100319AB4() {
    auto& callback = _2c0;
    const s32* life_ptr = mActor->getLife();
    const s32 life = life_ptr ? *life_ptr : 1;
    callback._27 = life < s32(f32(mActor->getMaxLife()) * *mChangeModeLifeRatio_s);
    setDamageCallbackTiming(mActor, 0, &callback);
    setDamageCallbackTiming(mActor, 2, &_2e8);
    if (auto* mgr = sead::DynamicCast<dmg::DamageManagerBase>(mActor->getDamageMgr()))
        mgr->setField64LowNibble(10);
}

void AssassinBossRoot::calc_() {
    if (_310._25 || _2e8._24) {
        _310._25 = false;
        _2e8._24 = false;
    }

    const s32* life_ptr = mActor->getLife();
    const s32 life = life_ptr ? *life_ptr : 1;
    if (life < s32(f32(mActor->getMaxLife()) * *mChangeModeLifeRatio_s)) {
        setDamageCallbackTiming(mActor, 4, &_338);
        sub_710031BB3C();
    } else {
        sub_710031C2C8(s32(f32(mActor->getMaxLife()) * *mChangeModeLifeRatio_s));
    }

    if (isCurrentChild("奈落")) {
        auto* child = getCurrentChild();
        if (!child->isFinished() && !child->isFailed())
            return;
        if (auto* controller = mActor->getCharacterController())
            controller->sub_7100F63388(true, -1);
    }

    AssassinBossRootBase::calc_();
    if (isCurrentChild("撤退"))
        return;

    auto* actor = mActor;
    bool b = false;
    if (actor->getASList()->x(14, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011638DC, true)) {
        b = true;
        if (!_400) {
            sub_71007A3778(actor, "TgtBarrier");
            _400 = true;
        }
    } else if (_400) {
        sub_71007A3910(actor, "TgtBarrier");
        _400 = false;
    }
    _310._24 = b;

    if (isCurrentChild("リアクション")) {
        sub_71005DA114(mActor, &_2c0);
        sub_71005DA114(mActor, &_2e8);
        if (auto* mgr = sead::DynamicCast<dmg::DamageManagerBase>(mActor->getDamageMgr()))
            mgr->setField64LowNibble(0);
    } else if (auto* controller = mActor->getCharacterController()) {
        if (!isCurrentChild("奈落"))
            controller->sub_7100F63388(true, -1);
    }
}

void AssassinBossRoot::leave_() {
    AssassinBossRootBase::leave_();
}

void AssassinBossRoot::loadParams_() {
    AssassinBossRootBase::loadParams_();
    getStaticParam(&mIronBallNum_s, "IronBallNum");
    getStaticParam(&mBattleAvoidNum_s, "BattleAvoidNum");
}

// NON_MATCHING: instruction scheduling of the final and
bool AssassinBossRoot::m35() {
    const s32 type = mActor->getDamageMgr()->getField54();
    return EnemyRoot::m35() && type != 12 && type != 13 && type != 11;
}

void AssassinBossRoot::m42() {
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F63388(false, -1);
    EnemyRoot::m42();
}

bool AssassinBossRoot::m45() {
    if (_2c0._26)
        return true;
    if (_2c0._25)
        return true;
    return _2c0._24;
}

void AssassinBossRoot::m47() {
    m38();
}

}  // namespace uking::ai

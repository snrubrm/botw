#include "Game/AI/AI/aiAssassinBossRoot.h"
#include <cmath>
#include <math/seadMathCalcCommon.h>
#include <prim/seadSafeString.h>
#include "Game/AI/aiUnk_71007368A4.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Damage/dmgDamageManagerBase.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::ai {

// 0x710031a970
void Unk_71023d7c40::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5,
                          dmg::DamageCallbackInfo* a6) {
    if (*a1 <= 0)
        return;
    auto* manager = sead::DynamicCast<dmg::DamageManagerBase>(mDamageManager);
    if (!manager)
        return;
    if (_24 && manager->getField50() == 4) {
        *a1 = 0;
        *a5 = 0xc;
        return;
    }
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(manager->getAttacker(), &accessor);
    if (accessor.getName() == "AssassinIronBall") {
        *a5 = 0x16;
        auto* info = sead::DynamicCast<dmg::DamageCallbackInfo>(a6);
        if (info)
            info->mFlags |= 2;
    } else if (accessor.getName() == "Explode") {
        *a1 = 0;
        *a5 = -1;
        auto* info = sead::DynamicCast<dmg::DamageCallbackInfo>(a6);
        if (info)
            info->mFlags = 0;
        return;
    }
    if (manager->checkDamageFlags(1))
        return;
    if (const auto* attack = sub_7100739578(mDamageManager->mActor)) {
        auto* body = attack->_c0;
        if (body == manager->mActor->findPhysicsBodyByName(sub_71007A24D0()->cstr(), "TgtBarrier")) {
            *a1 = 0;
            *a5 = 0xc;
            _25 = true;
        }
    }
}

// NON_MATCHING: register allocation (the original keeps the cast result in two registers, one of them null when the cast fails)
// 0x710031a6fc
void Unk_71023d7bd0::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5,
                          dmg::DamageCallbackInfo* a6) {
    if (*a1 <= 0)
        return;
    auto* manager = sead::DynamicCast<dmg::DamageManagerBase>(mDamageManager);
    bool has_manager = false;
    if (manager) {
        if (sub_71007368A4(manager->getAttacker()))
            return;
        has_manager = true;
        if (manager->checkDamageFlags(1)) {
            *a1 = static_cast<s32>(static_cast<f32>(manager->mActor->getMaxLife()) / 6.0f + 1.0f);
            return;
        }
    }
    if (!_27)
        return;
    *a5 = -1;
    s32 attack_type = -1;
    if (has_manager) {
        manager->m40(&attack_type);
        auto* actor = manager->mActor;
        if (actor->getASList()->x(0xe, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011638DC,
                                  true)) {
            sead::Vector3f attack_pos;
            manager->getAttackPos(&attack_pos);
            attack_pos = -attack_pos;
            if (*a4 == 3 ||
                actor->getMtx().getBase(2).dot(attack_pos) >= -4.371139e-08f) {
                *a1 = 0;
                *a5 = 0xc;
                _24 = false;
                _26 = false;
                return;
            }
        }
    }
    *a1 = 0;
    if (*a4 == 3) {
        _24 = true;
        _26 = true;
    } else if (u32(attack_type) < 5 && ((1 << attack_type) & 0x13)) {
        _24 = true;
    } else {
        _25 = true;
    }
}

AssassinBossRoot::AssassinBossRoot(const InitArg& arg) : AssassinBossRootBase(arg) {}

AssassinBossRoot::~AssassinBossRoot() {
    if (!mParams.mIronBallNum_s)
        return;

    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy)
        return;

    sead::FixedSafeString<32> name;
    for (int i = 0; i < *mParams.mIronBallNum_s; ++i) {
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

    for (int i = 0; i < *mParams.mIronBallNum_s; ++i)
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
    callback._27 = life < s32(f32(mActor->getMaxLife()) * *AssassinBossRootBase::mParams.mChangeModeLifeRatio_s);
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
    if (life < s32(f32(mActor->getMaxLife()) * *AssassinBossRootBase::mParams.mChangeModeLifeRatio_s)) {
        setDamageCallbackTiming(mActor, 4, &_338);
        sub_710031BB3C();
    } else {
        sub_710031C2C8(s32(f32(mActor->getMaxLife()) * *AssassinBossRootBase::mParams.mChangeModeLifeRatio_s));
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
    if (_2c0.mDamageManager) {
        sub_71005DA114(mActor, &_2c0);
        sub_71005DA114(mActor, &_2e8);
        if (auto* manager = sead::DynamicCast<dmg::DamageManagerBase>(mActor->getDamageMgr()))
            manager->setField64LowNibble(0);
    }
    sub_71005DA114(mActor, &_310);
    sub_71007A3910(mActor, "TgtBarrier");
    _400 = false;
    _310._24 = false;
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F63388(false, -1);
    sub_71005DA114(mActor, &_338);
    AssassinBossRootBase::leave_();
}

void AssassinBossRoot::loadParams_() {
    AssassinBossRootBase::loadParams_();
    getStaticParam(&mParams.mIronBallNum_s, "IronBallNum");
    getStaticParam(&mParams.mBattleAvoidNum_s, "BattleAvoidNum");
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

// NON_MATCHING: same instructions, but the original loads the matrix terms (0x3a0 / 0x3b0) before the attack
// direction and the third one between the multiplies.
void Unk_71023d7c08::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5,
                          dmg::DamageCallbackInfo* a6) {
    if (*a1 < 1)
        return;

    auto* damage_manager = sead::DynamicCast<dmg::DamageManagerBase>(mDamageManager);
    s32 field_40 = -1;
    if (!damage_manager)
        return;

    if (sub_71007368A4(damage_manager->getAttacker())) {
        *a5 = -1;
        return;
    }
    if (damage_manager->checkDamageFlags(1))
        return;

    damage_manager->m40(&field_40);
    auto* actor = damage_manager->mActor;
    if (!actor->getASList()->x(14, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011638DC, true))
        return;

    sead::Vector3f dir;
    damage_manager->getAttackPos(&dir);
    const auto& mtx = actor->getMtx();
    if (!(mtx.m[0][2] * -dir.x + mtx.m[1][2] * -dir.y + mtx.m[2][2] * -dir.z >=
          std::cos(sead::Mathf::pi() / 2)))
        return;

    *a1 = 0;
    *a5 = 12;
    _24 = true;
}

// Keeps the actor's life above zero: damage that would be lethal is reduced to life - 1.
void Unk_71023d7c78::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5,
                          dmg::DamageCallbackInfo* a6) {
    if (*a1 < 1)
        return;

    auto* damage_manager = sead::DynamicCast<dmg::DamageManagerBase>(mDamageManager);
    if (!damage_manager || damage_manager->checkDamageFlags(1))
        return;

    const s32 damage = *a1;
    const s32* life = damage_manager->mActor->getLife();
    if (damage < (life ? *life : 1))
        return;

    life = damage_manager->mActor->getLife();
    *a1 = life ? *life - 1 : 0;
}

}  // namespace uking::ai

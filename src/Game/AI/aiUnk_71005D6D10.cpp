#include "Game/AI/aiUnk_71005D6D10.h"
#include <prim/seadRuntimeTypeInfo.h>
#include "Game/Actor/actEnemy.h"
#include "Game/Damage/dmgDamageCallback.h"
#include "Game/Damage/dmgDamageManager.h"
#include "Game/Damage/dmgDamageManagerBase.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actBoneControl.h"

using uking::act::Enemy;

void callDeleteAndCreateDropAndEmit(ksys::act::Actor* actor, int a1) {
    if (actor->isDeletedOrDeleting())
        return;
    actor->killWithDropsAndEffects(a1);
}

void sub_71005D7014(ksys::act::Actor* actor) {
    if (!sead::IsDerivedFrom<Enemy>(actor))
        return;
    auto* enemy = static_cast<Enemy*>(actor);
    ksys::act::acc::PlayerBase accessor;
    ksys::act::acquireActor(&enemy->_d70._98, &accessor);
    accessor.x_0(actor);
}

void sub_71005D8DE8(ksys::act::Actor* actor, const ksys::act::BaseProcLink& link,
                    const sead::Matrix34f* mtx, const sead::Vector3f* pos) {
    if (!sead::IsDerivedFrom<Enemy>(actor))
        return;
    auto* enemy = static_cast<Enemy*>(actor);
    enemy->_c48.sub_71002DBC8C(link, mtx, pos);
}

void sub_71005D8E9C(ksys::act::Actor* actor) {
    if (!sead::IsDerivedFrom<Enemy>(actor))
        return;
    auto* enemy = static_cast<Enemy*>(actor);
    enemy->_c48._8.reset();
    enemy->_c48._7c = 0;
}

bool sub_71005D8F28(ksys::act::Actor* actor) {
    if (!sead::IsDerivedFrom<Enemy>(actor))
        return false;
    auto* enemy = static_cast<Enemy*>(actor);
    return enemy->_c48._8.hasProc();
}

bool sub_71005D8FBC(ksys::act::Actor* actor) {
    if (!sead::IsDerivedFrom<Enemy>(actor))
        return false;
    auto* enemy = static_cast<Enemy*>(actor);
    return ksys::act::isPlayerProfile(&enemy->_c48._8);
}

ksys::act::BaseProcLink* sub_71005D9050(ksys::act::Actor* actor) {
    if (!sead::IsDerivedFrom<Enemy>(actor))
        return nullptr;
    auto* enemy = static_cast<Enemy*>(actor);
    return &enemy->_c48._8;
}

const sead::Vector3f& sub_71005D9330(ksys::act::Actor* actor) {
    if (sead::IsDerivedFrom<Enemy>(actor))
        return static_cast<Enemy*>(actor)->_c48._18;
    return sead::Vector3f::zero;
}

// NON_MATCHING: the original's csel has the operands swapped (eq: global, ne: field)
ksys::act::BaseProcLink& sub_71005D94AC(ksys::act::Actor* actor) {
    if (!sead::IsDerivedFrom<Enemy>(actor))
        return ksys::act::sUnk_71026505e0;
    auto* enemy = static_cast<Enemy*>(actor);
    return enemy->_c48._8;
}

// NON_MATCHING: the original branches to pick the link (field or global) instead of a csel
const sead::Vector3f& sub_71005D93CC(ksys::act::Actor* actor) {
    auto& link = sub_71005D94AC(actor);
    if (!link.hasProc())
        return sead::Vector3f::zero;
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&link, &accessor);
    return accessor.getField44C_Vec3();
}

const sead::Vector3f& sub_71005D9548(ksys::act::Actor* actor) {
    if (!sead::IsDerivedFrom<Enemy>(actor))
        return sead::Vector3f::zero;
    auto* enemy = static_cast<Enemy*>(actor);
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&enemy->_c48._8, &accessor);
    return accessor.getVelocity();
}

const sead::Vector3f& sub_71005D960C(ksys::act::Actor* actor) {
    if (!sead::IsDerivedFrom<Enemy>(actor))
        return sead::Vector3f::zero;
    auto* enemy = static_cast<Enemy*>(actor);
    return enemy->_c48._54;
}

const sead::Matrix34f& sub_71005D96A8(ksys::act::Actor* actor) {
    if (!sead::IsDerivedFrom<Enemy>(actor))
        return sead::Matrix34f::ident;
    auto* enemy = static_cast<Enemy*>(actor);
    return enemy->_c48._24;
}

s32 sub_71005D9744(ksys::act::Actor* actor) {
    if (!sead::IsDerivedFrom<Enemy>(actor))
        return 0;
    auto* enemy = static_cast<Enemy*>(actor);
    return enemy->_c48._7c;
}

// NON_MATCHING: the state load goes through a separately computed &_c48 (add + ldr) instead of a
// single ldr at 0xcc4
bool sub_71005D97D0(ksys::act::Actor* actor) {
    if (!sub_71005D8F28(actor))
        return false;
    switch (sub_71005D9744(actor)) {
    case 2:
    case 3:
    case 4:
        return false;
    default:
        return true;
    }
}

const sead::Vector3f& sub_71005D98D8(ksys::act::Actor* actor) {
    if (!sead::IsDerivedFrom<Enemy>(actor))
        return sead::Vector3f::zero;
    auto* enemy = static_cast<Enemy*>(actor);
    return enemy->_c48._70;
}

void sub_71005D9974(ksys::act::Actor* actor, u32 mask, bool set) {
    if (sead::IsDerivedFrom<Enemy>(actor)) {
        auto& flags = static_cast<Enemy*>(actor)->_c48._120;
        if (set)
            flags |= mask;
        else
            flags &= ~mask;
    }
}

bool setDamageCallbackTiming(ksys::act::Actor* actor, s32 timing,
                             uking::dmg::DamageCallback* callback) {
    auto* damage_mgr = actor->getDamageMgr();
    if (!damage_mgr)
        return false;
    if (damage_mgr == callback->mDamageManager)
        return true;
    auto* mgr = sead::DynamicCast<uking::dmg::DamageManager>(damage_mgr);
    if (!mgr)
        return false;
    mgr->addDamageCallback(timing, callback);
    return true;
}

bool sub_71005DA114(ksys::act::Actor* actor, uking::dmg::DamageCallback* callback) {
    if (!callback->mDamageManager)
        return false;
    auto* damage_mgr = actor->getDamageMgr();
    if (!damage_mgr)
        return false;
    damage_mgr->removeDamageCallback(callback);
    return true;
}

bool sub_71005DAFB0(ksys::act::Actor* actor) {
    auto* enemy = sead::DynamicCast<Enemy>(actor);
    if (!enemy || !enemy->_e84.isOnBit(0))
        return false;
    auto* damage_mgr = enemy->getDamageMgr();
    if (!damage_mgr)
        return false;
    return damage_mgr->getField54() > 0;
}

// NON_MATCHING: the original loads _d4 before the _8c store (scheduling)
void sub_71005D73F8(ksys::act::Actor* actor, const sead::Vector3f& pos) {
    auto* bone_control = actor->getBoneControl();
    if (!bone_control)
        return;
    auto* unk = bone_control->_0;
    if (!unk)
        return;
    unk->_10._8c |= 0x10;
    unk->_10._d4 |= 2;
    unk->_10._d4 &= ~0xc0;
    unk->_10._8 = pos;
}

// NON_MATCHING: the original loads _d4 before the _8c store (scheduling)
void sub_71005D7444(ksys::act::Actor* actor, const sead::Vector3f& pos, bool a3, bool a4) {
    auto* bone_control = actor->getBoneControl();
    if (!bone_control)
        return;
    auto* unk = bone_control->_0;
    if (!unk)
        return;
    unk->_10._8c |= 0x10;
    unk->_10._d4 |= 2;
    if (a3)
        unk->_10._d4 &= ~0x80;
    else
        unk->_10._d4 |= 0x80;
    if (a4) {
        unk->_10._d4 &= ~0x40;
    } else {
        unk->_10._d4 &= ~0xc00;
        unk->_10._d4 |= 0x40;
    }
    unk->_10._8 = pos;
}

void sub_71005D74B8(ksys::act::Actor* actor) {
    auto* bone_control = actor->getBoneControl();
    if (!bone_control)
        return;
    auto* unk = bone_control->_0;
    if (!unk)
        return;
    unk->_10._8c &= ~0x10;
    unk->_10._d4 &= ~0xc0;
}

void sub_71005D74E8(ksys::act::Actor* actor) {
    auto* bone_control = actor->getBoneControl();
    if (!bone_control)
        return;
    auto* unk = bone_control->_0;
    if (!unk)
        return;
    unk->_10._8c &= ~0x10;
    unk->_10._d4 &= ~0xc0;
}

void sub_71005DB068(ksys::act::Actor* actor, const sead::Vector3f& pos) {
    auto* bone_control = actor->getBoneControl();
    if (!bone_control)
        return;
    auto* unk = bone_control->_0;
    if (!unk)
        return;
    unk->sub_7100D8571C(pos);
    unk->sub_7100D85750();
}

void sub_71005DB0A8(ksys::act::Actor* actor, const sead::Vector3f& pos) {
    auto* bone_control = actor->getBoneControl();
    if (!bone_control)
        return;
    auto* unk = bone_control->_0;
    if (!unk)
        return;
    unk->_10._8c |= 0x20;
    unk->_10._d4 |= 2;
    unk->_10._8 = pos;
}

void sub_71005DB110(ksys::act::Actor* actor, const sead::Vector3f& pos) {
    sead::Vector3f target = pos;
    sub_71005DB198(&target, actor);
    sub_71005DB0A8(actor, target);
}

void sub_71005DB198(sead::Vector3f* pos, ksys::act::Actor* actor) {
    sead::Vector3f offset;
    ksys::act::sub_7100D83014(&offset, actor->getBoneControl());
    pos->y += offset.y;
}

void sub_71005DB1D8(ksys::act::Actor* actor, const sead::Vector3f& pos) {
    auto* bone_control = actor->getBoneControl();
    if (!bone_control)
        return;
    auto* unk = bone_control->_0;
    if (!unk)
        return;
    sead::Vector3f offset;
    sead::Vector3f target = pos;
    ksys::act::sub_7100D83014(&offset, bone_control);
    target.y += offset.y;
    unk->sub_7100D8571C(target);
    unk->sub_7100D85750();
}

void sub_71005DB248(ksys::act::Actor* actor) {
    const auto& pos = sub_71005D9330(actor);
    const auto& pos2 = sub_71005D960C(actor);
    auto* bone_control = actor->getBoneControl();
    if (!bone_control)
        return;
    auto* unk = bone_control->_0;
    if (!unk)
        return;
    sead::Vector3f offset;
    sead::Vector3f target = pos;
    ksys::act::sub_7100D83014(&offset, bone_control);
    target.y += offset.y;
    unk->sub_7100D8571C(target);
    unk->sub_7100D85750();
    unk->_e8._8 = pos2;
}

void sub_71005DB3B8(ksys::act::Actor* actor) {
    auto* bone_control = actor->getBoneControl();
    if (!bone_control)
        return;
    auto* unk = bone_control->_0;
    if (!unk)
        return;
    unk->_10._8c &= ~0x20;
    unk->_10._d4 &= ~0xc02;
}

void sub_71005DB3EC(ksys::act::Actor* actor) {
    auto* bone_control = actor->getBoneControl();
    if (!bone_control)
        return;
    auto* unk = bone_control->_0;
    if (!unk)
        return;
    unk->sub_7100D85774();
}

void sub_71005DB404(ksys::act::Actor* actor, const sead::Vector3f& pos) {
    auto* bone_control = actor->getBoneControl();
    if (!bone_control)
        return;
    auto* unk = bone_control->_0;
    if (!unk)
        return;
    unk->sub_7100D8571C(pos);
}

void sub_71005DB41C(ksys::act::Actor* actor) {
    auto* bone_control = actor->getBoneControl();
    if (!bone_control)
        return;
    auto* unk = bone_control->_0;
    if (!unk)
        return;
    unk->sub_7100D85794();
}

void sub_71005DB434(ksys::act::Actor* actor) {
    auto* bone_control = actor->getBoneControl();
    if (!bone_control)
        return;
    auto* unk = bone_control->_0;
    if (!unk)
        return;
    unk->sub_7100D857B0();
}

void sub_71005DB44C(ksys::act::Actor* actor, f32 a2, f32 a3) {
    auto* bone_control = actor->getBoneControl();
    if (!bone_control)
        return;
    auto* unk = bone_control->_0;
    if (!unk)
        return;
    unk->_10.sub_7100D89348(a2, a3);
    unk->_10._d4 |= 2;
}

void sub_71005DB498(ksys::act::Actor* actor) {
    auto* bone_control = actor->getBoneControl();
    if (!bone_control)
        return;
    auto* unk = bone_control->_0;
    if (!unk)
        return;
    unk->_10._d4 &= ~0x3000;
}

f32 sub_71005DB4DC(ksys::act::Actor* actor) {
    auto* bone_control = actor->getBoneControl();
    if (!bone_control)
        return 0.0f;
    auto* unk = bone_control->_0;
    if (!unk)
        return 0.0f;
    return unk->_10.sub_7100D8A6DC();
}

f32 sub_71005DB4FC(ksys::act::Actor* actor) {
    auto* bone_control = actor->getBoneControl();
    if (!bone_control)
        return 0.0f;
    auto* unk = bone_control->_0;
    if (!unk)
        return 0.0f;
    return unk->_10.sub_7100D8A76C();
}

void sub_71005DB51C(ksys::act::Actor* actor, f32 a2, bool a3) {
    auto* bone_control = actor->getBoneControl();
    if (!bone_control)
        return;
    auto* unk = bone_control->_0;
    if (!unk)
        return;
    unk->_10.sub_7100D8A830(a2, a3);
}

void sub_71005DB558(ksys::act::Actor* actor, f32 a2, bool a3) {
    auto* bone_control = actor->getBoneControl();
    if (!bone_control)
        return;
    auto* unk = bone_control->_0;
    if (!unk)
        return;
    unk->_10.sub_7100D8A904(a2, a3);
}

void sub_71005DB594(ksys::act::Actor* actor, const sead::Vector3f& pos) {
    auto* bone_control = actor->getBoneControl();
    if (!bone_control)
        return;
    auto* unk = bone_control->_0;
    if (!unk)
        return;
    unk->_10._74 = pos;
}

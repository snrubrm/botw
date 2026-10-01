#include "Game/AI/aiUnk_71005D6D10.h"
#include <prim/seadRuntimeTypeInfo.h>
#include "Game/Actor/actEnemy.h"
#include "Game/Damage/dmgDamageManagerBase.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

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

bool sub_71005DAFB0(ksys::act::Actor* actor) {
    auto* enemy = sead::DynamicCast<Enemy>(actor);
    if (!enemy || !enemy->_e84.isOnBit(0))
        return false;
    auto* damage_mgr = enemy->getDamageMgr();
    if (!damage_mgr)
        return false;
    return damage_mgr->getField54() > 0;
}

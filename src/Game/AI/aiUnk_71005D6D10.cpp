#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/Attention/actActorAttention.h"
#include "KingSystem/ActorSystem/Attention/actAttClient.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include <cmath>
#include "Game/AI/aiUnk_7102357d20.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/ActorSystem/actAiParam.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Physics/Ragdoll/physRagdollInstance.h"
#include "KingSystem/ActorSystem/actTag.h"
#include "KingSystem/World/worldWeatherMgr.h"
#include "KingSystem/World/worldEnvMgr.h"
#include "KingSystem/World/worldManager.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include <gsys/gsysModelAccessKey.h>
#include <gsys/gsysModel.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/actHorseRideInfo.h"
#include "Game/Actor/actNPC.h"
#include "Game/Actor/actWeapon.h"
#include "Game/Damage/dmgDamageCallback.h"
#include "Game/Damage/dmgDamageManager.h"
#include "Game/Damage/dmgDamageManagerBase.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actBoneControl.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/ActorSystem/actDropData.h"
#include "KingSystem/ActorSystem/actUnk_7100e4e084.h"
#include "KingSystem/Map/mapAutoPlacementMgr.h"
#include "KingSystem/ActorSystem/LOD/actLodState.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/Map/mapObject.h"

using uking::act::Enemy;
using uking::act::NPC;

void callDeleteAndCreateDropAndEmit(ksys::act::Actor* actor, int a1) {
    if (actor->isDeletedOrDeleting())
        return;
    actor->killWithDropsAndEffects(a1);
}

bool sub_71005D6D10() {
    return ksys::act::ActorCreator::instance()->isBlockSpawns();
}

void sub_71005D6D48(ksys::act::Actor* actor) {
    if (actor->getDropData()) {
        if (auto* drop_data = sead::DynamicCast<ksys::act::DropData>(actor->getDropData()))
            drop_data->_c |= 1;
    }
    callDeleteAndCreateDropAndEmit(actor, false);
}

void sub_71005D7014(ksys::act::Actor* actor) {
    if (!sead::IsDerivedFrom<Enemy>(actor))
        return;
    auto* enemy = static_cast<Enemy*>(actor);
    ksys::act::acc::PlayerBase accessor;
    ksys::act::acquireActor(&enemy->_e08._0, &accessor);
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

bool sub_71005D8748(ksys::act::Actor* actor, const sead::Vector3f& velocity, bool a3, bool a4,
                    void* a5, bool a6) {
    if (sead::IsDerivedFrom<ksys::act::PlayerOrEnemy>(actor))
        return static_cast<ksys::act::PlayerOrEnemy*>(actor)->sub_7100007A1C(velocity, a3, a4, a5,
                                                                              a6);
    if (sead::IsDerivedFrom<NPC>(actor))
        return static_cast<NPC*>(actor)->sub_7100022554(velocity, a3, a4, a5, a6);
    return false;
}

bool sub_71005D88AC(ksys::act::Actor* actor, const sead::Vector3f& target, const sead::Vector3f& pos,
                    bool a3, bool a4, void* a5, bool a6) {
    if (sead::IsDerivedFrom<ksys::act::PlayerOrEnemy>(actor)) {
        return static_cast<ksys::act::PlayerOrEnemy*>(actor)->sub_7100007A78(target, pos, a3, a4,
                                                                             a5, a6);
    }
    return false;
}

bool playerOrEnemyDropWeapon(ksys::act::Actor* actor, const sead::Vector3f* velocity, int idx,
                             bool a4, bool a5, void* a6, bool a7) {
    if (sead::IsDerivedFrom<ksys::act::PlayerOrEnemy>(actor))
        return static_cast<ksys::act::PlayerOrEnemy*>(actor)->dropWeapon(idx, *velocity, a4, a5,
                                                                          a6, a7);
    if (sead::IsDerivedFrom<NPC>(actor))
        return static_cast<NPC*>(actor)->sub_71000224F0(idx, *velocity, a4, a5, a6, a7);
    return false;
}

bool playerOrEnemyDropAllWeapons(ksys::act::Actor* actor, const sead::Vector3f& velocity) {
    if (!sead::IsDerivedFrom<ksys::act::PlayerOrEnemy>(actor))
        return false;
    return static_cast<ksys::act::PlayerOrEnemy*>(actor)->dropAllWeapons(velocity);
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

bool sub_71005DA434(ksys::act::Actor* actor, int idx) {
    if (idx < 0)
        return false;
    auto* weapons = actor->getWeapons();
    if (idx > 5 || !weapons)
        return false;
    auto* weapon = sead::DynamicCast<uking::act::Weapon>(weapons->getEquippedWeapon(idx));
    if (!weapon)
        return false;
    return weapon->sub_71002ED274();
}

bool sub_71005DA4F0(ksys::act::Actor* actor, int idx) {
    if (idx < 0)
        return false;
    auto* weapons = actor->getWeapons();
    if (idx > 5 || !weapons)
        return false;
    auto* weapon = sead::DynamicCast<uking::act::Weapon>(weapons->getEquippedWeapon(idx));
    if (!weapon)
        return false;
    return weapon->sub_71002E9A7C();
}

bool sub_71005DA738(ksys::act::Actor* actor, int idx) {
    if (idx < 0)
        return false;
    auto* weapons = actor->getWeapons();
    if (idx > 5 || !weapons)
        return false;
    auto* weapon = sead::DynamicCast<uking::act::Weapon>(weapons->getEquippedWeapon(idx));
    if (!weapon)
        return false;
    return weapon->sub_71002EA0C8();
}

bool sub_71005DAA70(ksys::act::Actor* actor, int idx) {
    if (idx < 0)
        return false;
    auto* weapons = actor->getWeapons();
    if (idx > 5 || !weapons)
        return false;
    auto* weapon = sead::DynamicCast<uking::act::Weapon>(weapons->getEquippedWeapon(idx));
    if (!weapon)
        return false;
    return hasAttackInfo(weapon);
}

bool sub_71005DA5AC(ksys::act::Actor* actor, int idx) {
    if (idx < 0)
        return false;
    auto* weapons = actor->getWeapons();
    if (idx > 5 || !weapons)
        return false;
    auto* weapon = sead::DynamicCast<uking::act::Weapon>(weapons->getEquippedWeapon(idx));
    if (!weapon)
        return false;
    return weapon->sub_71002E9A50();
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

void sub_71005D8D4C(ksys::act::Actor* actor, f32 value, int idx, bool a3) {
    if (!actor)
        return;
    auto* unit = actor->get548();
    if (!unit)
        return;
    unit->m8()->m9(idx, value);
    if (a3)
        unit->m8()->m10(true, true);
}

bool sub_71005D9F04(ksys::act::Actor* actor) {
    auto* object = actor->getMapObject();
    if (object && object->getRails_0() && *object->getRails_0())
        return true;
    return false;
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

void sub_71005DB4B8(sead::Vector3f* out, ksys::act::Actor* actor) {
    auto* bone_control = actor->getBoneControl();
    if (!bone_control)
        return;
    auto* unk = bone_control->_0;
    if (!unk)
        return;
    unk->_10.sub_7100D88CF4(out);
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

void sub_71005D7518(ksys::act::Actor* actor, bool set) {
    if (sead::IsDerivedFrom<NPC>(actor)) {
        auto& flags = static_cast<NPC*>(actor)->_fe8;
        if (!set)
            flags &= ~0x80;
        else
            flags |= 0x80;
    }
}

bool sub_71005D75B4(ksys::act::Actor* actor) {
    if (!sead::IsDerivedFrom<NPC>(actor))
        return false;
    auto* npc = static_cast<NPC*>(actor);
    return npc->_fe8 >> 7 & 1;
}

void sub_71005D7644(ksys::act::Actor* actor, bool set) {
    if (sead::IsDerivedFrom<NPC>(actor)) {
        auto& flags = static_cast<NPC*>(actor)->_fe8;
        if (!set)
            flags &= ~0x400;
        else
            flags |= 0x400;
    }
}

void sub_71005D76E0(ksys::act::Actor* actor, bool set) {
    if (sead::IsDerivedFrom<NPC>(actor)) {
        auto& flags = static_cast<NPC*>(actor)->_fe8;
        if (!set)
            flags &= ~0x2000;
        else
            flags |= 0x2000;
    }
}

uking::act::Unk_71002dccbc* sub_71005D9D68(ksys::act::Actor* actor) {
    if (sead::IsDerivedFrom<Enemy>(actor))
        return &static_cast<Enemy*>(actor)->_d70;
    return sead::IsDerivedFrom<NPC>(actor) ? &static_cast<NPC*>(actor)->_e90 : nullptr;
}

void sub_71005DB5C0(ksys::act::Actor* actor, int idx) {
    if (!sead::IsDerivedFrom<ksys::act::PlayerOrEnemy>(actor) && !sead::IsDerivedFrom<NPC>(actor))
        return;
    actor->getWeapons()->mWeapons[idx]._10 = false;
}

void sub_71005DB6D0(ksys::act::Actor* actor, int idx) {
    if (!sead::IsDerivedFrom<ksys::act::PlayerOrEnemy>(actor) && !sead::IsDerivedFrom<NPC>(actor))
        return;
    actor->getWeapons()->mWeapons[idx]._10 = true;
}

bool sub_71005DB7E4(ksys::act::Actor* actor, int idx) {
    if (!sead::IsDerivedFrom<ksys::act::PlayerOrEnemy>(actor) && !sead::IsDerivedFrom<NPC>(actor))
        return false;
    return actor->getWeapons()->mWeapons[idx]._10;
}

bool sub_71005D777C(ksys::act::BaseProcLink* link) {
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(link, &accessor);
    return accessor.sub_7100022FD0();
}

void sub_71005D787C(ksys::act::Actor* actor, int idx, const uking::act::Unk_71002eda38& arg) {
    if (idx < 0)
        return;
    if (sead::IsDerivedFrom<ksys::act::PlayerOrEnemy>(actor)) {
        static_cast<ksys::act::PlayerOrEnemy*>(actor)->sub_7100007CA8(idx, arg);
        return;
    }
    if (sead::IsDerivedFrom<NPC>(actor))
        static_cast<NPC*>(actor)->sub_71000225B0(idx, arg);
}

void sub_71005D79AC(ksys::act::Actor* actor, int idx, const uking::act::Unk_71002edaec& arg) {
    if (idx < 0)
        return;
    if (sead::IsDerivedFrom<ksys::act::PlayerOrEnemy>(actor)) {
        static_cast<ksys::act::PlayerOrEnemy*>(actor)->sub_7100007D58(idx, arg);
        return;
    }
    if (sead::IsDerivedFrom<NPC>(actor))
        static_cast<NPC*>(actor)->sub_7100022660(idx, arg);
}

void sub_71005D80FC(ksys::act::Actor* actor, int idx, const sead::Vector3f& pos, int a3, f32 a4,
                    const sead::Vector3f* pos2, const ksys::act::BaseProcLink* link) {
    uking::act::Unk_71002eda38 arg;
    arg._0 = 6;
    arg._4 = a3;
    arg._30 = a4;
    arg._14 = pos;
    if (pos2) {
        arg._8 = *pos2;
        arg._3c = true;
    } else {
        arg._3c = false;
    }
    if (link)
        arg._20 = *link;
    sub_71005D787C(actor, idx, arg);
}

void sub_71005D8210(ksys::act::Actor* actor, int idx, const sead::Vector3f& pos, int a3, f32 a4,
                    const sead::Vector3f* pos2, const ksys::act::BaseProcLink* link) {
    uking::act::Unk_71002eda38 arg;
    arg._0 = 7;
    arg._4 = a3;
    arg._30 = a4;
    arg._14 = pos;
    if (pos2) {
        arg._8 = *pos2;
        arg._3c = true;
    } else {
        arg._3c = false;
    }
    if (link)
        arg._20 = *link;
    sub_71005D787C(actor, idx, arg);
}

s32 sub_71005D7854(ksys::act::Actor* actor) {
    auto* weapons = actor->getWeapons();
    if (!weapons)
        return 0;
    return weapons->mWeapons.size();
}

bool sub_71005D8324(ksys::act::Actor* actor, int idx) {
    if (!sead::IsDerivedFrom<ksys::act::PlayerOrEnemy>(actor))
        return false;
    return static_cast<ksys::act::PlayerOrEnemy*>(actor)->m163(idx);
}

uking::act::Unk_71002dccbc* sub_71005D9E64(ksys::act::Actor* actor) {
    return sub_71005D9D68(actor);
}

bool sub_71005D9E68(ksys::act::Actor* actor) {
    if (!sead::IsDerivedFrom<ksys::act::PlayerOrEnemy>(actor))
        return false;
    return static_cast<ksys::act::PlayerOrEnemy*>(actor)->m173();
}

bool sub_71005D9F4C(const sead::Vector3f& pos) {
    auto* mgr = ksys::map::AutoPlacementMgr::instance();
    if (!mgr)
        return false;
    return mgr->isNonAutoPlacement(pos, true);
}

bool sub_71005D9FC0(ksys::act::BaseProcLink* link) {
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(link, &accessor);
    sead::Vector3f pos;
    accessor.getActorMtx().getTranslation(pos);
    auto* mgr = ksys::map::AutoPlacementMgr::instance();
    if (!mgr)
        return false;
    return mgr->isNonAutoPlacement(pos, true);
}

void sub_71005D8C94(ksys::act::Actor* actor, int idx, const u32& value) {
    if (idx < 0)
        return;
    auto* weapons = actor->getWeapons();
    if (!weapons)
        return;
    if (auto* weapon = sead::DynamicCast<uking::act::Weapon>(weapons->getEquippedWeapon(idx)))
        weapon->sub_71002EDBCC(value);
}

bool sub_71005D90E0(ksys::act::Actor* actor) {
    if (!sead::IsDerivedFrom<Enemy>(actor))
        return false;
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&static_cast<Enemy*>(actor)->_c48._8, &accessor);
    return accessor.sub_7100D12E64();
}

bool sub_71005D9F70(ksys::act::Actor* actor) {
    sead::Vector3f pos;
    actor->getMtx().getTranslation(pos);
    auto* mgr = ksys::map::AutoPlacementMgr::instance();
    if (!mgr)
        return false;
    return mgr->isNonAutoPlacement(pos, true);
}

// NON_MATCHING: block order (the original falls through into `return true` and branches to a shared
// `return false`)
bool sub_71005E0384(ksys::act::Actor* actor) {
    auto* lod = actor->getLodState();
    if (lod && lod->_1c != 1) {
        const sead::Vector3f pos = actor->getMtx().getTranslation();
        if ((getPlayerPosition() - pos).length() > 100.0f)
            return true;
    }
    return false;
}

ksys::act::Unk_7100d860d8* sub_71005DB0EC(ksys::act::Actor* actor) {
    auto* bone_control = actor->getBoneControl();
    if (!bone_control)
        return nullptr;
    auto* unk = bone_control->_0;
    if (!unk)
        return nullptr;
    return &unk->_10;
}

void* sub_71005D77C8(ksys::act::Actor* actor) {
    if (!sead::IsDerivedFrom<uking::act::NPCBase>(actor))
        return nullptr;
    return static_cast<uking::act::NPCBase*>(actor)->_840;
}

uking::act::Weapon* sub_71005D83E8(ksys::act::Actor* actor, int idx) {
    auto* weapons = actor->getWeapons();
    if (!weapons)
        return nullptr;
    auto* proc = weapons->mWeapons[idx].link.getProc(nullptr, nullptr);
    auto* weapon = sead::DynamicCast<ksys::act::WeaponBase>(proc);
    return sead::DynamicCast<uking::act::Weapon>(weapon);
}

// NON_MATCHING: when there are no weapons, ours returns the null pointer register as false; the
// original branches to a separate `return false` block
bool sub_71005D8514(ksys::act::Actor* actor, int idx) {
    auto* weapons = actor->getWeapons();
    if (!weapons)
        return false;
    auto* weapon = sead::DynamicCast<uking::act::Weapon>(weapons->getEquippedWeapon(idx));
    if (!weapon)
        return false;
    return weapon->_d54 == 1 || weapon->_d54 == 2;
}

bool sub_71005D8B60(ksys::act::Actor* actor) {
    auto* weapons = actor->getWeapons();
    if (!weapons)
        return false;
    for (int i = 0; i < weapons->mWeapons.size(); ++i) {
        auto* weapon = sead::DynamicCast<ksys::act::WeaponBase>(
            weapons->mWeapons(i).link.getProc(nullptr, nullptr));
        if (sead::IsDerivedFrom<uking::act::Weapon>(weapon))
            return false;
    }
    return true;
}

bool sub_71005DB904(ksys::act::Actor* actor, int idx) {
    auto* weapons = actor->getWeapons();
    if (idx < 0 || !weapons)
        return false;
    if (!weapons->getEquippedWeapon(idx))
        return false;
    return !weapons->mWeapons[idx]._10;
}

s32 sub_71005DBB60(ksys::act::Actor* actor, s32 idx) {
    if (idx < 0)
        return -1;
    auto* weapons = actor->getWeapons();
    if (idx > 5 || !weapons)
        return -1;
    auto* proc = weapons->mWeapons[idx].link.getProc(nullptr, nullptr);
    auto* weapon = sead::DynamicCast<ksys::act::WeaponBase>(proc);
    if (auto* sword = sead::DynamicCast<uking::act::Weapon>(weapon))
        return sword->_cf0;
    return -1;
}

void sub_71005DC270(ksys::act::Actor* actor, const sead::Vector3f& pos) {
    if (auto* obj = actor->m100())
        obj->sub_7100E5007C(1, pos);
}

void sub_71005DC2B0(ksys::act::Actor* actor, const sead::Vector3f& pos, f32 a3, f32 a4) {
    if (auto* obj = actor->m100())
        obj->sub_7100E500F8(1, pos, a3, a4);
}

void sub_71005DC30C(ksys::act::Actor* actor, const sead::Vector3f& pos) {
    if (auto* obj = actor->m100())
        obj->sub_7100E50010(1, pos, false);
}

void sub_71005DC350(ksys::act::Actor* actor, const sead::Vector3f& pos) {
    if (auto* obj = actor->m100())
        obj->sub_7100E50010(1, pos, true);
}

void sub_71005DC394(ksys::act::Actor* actor) {
    if (auto* obj = actor->m100())
        obj->sub_7100E50010(4, sead::Vector3f::zero, false);
}

void sub_71005DC3CC(ksys::act::Actor* actor) {
    if (auto* obj = actor->m100())
        obj->sub_7100E50220();
}

void sub_71005DC3F4(ksys::act::Actor* actor) {
    if (auto* obj = actor->m100())
        obj->sub_7100E50288();
}

void sub_71005DC41C(ksys::act::Actor* actor) {
    if (auto* obj = actor->m100())
        obj->sub_7100E50254();
}

bool sub_71005DC444(ksys::act::Actor* actor) {
    auto* obj = actor->m100();
    return obj && obj->_bc != 0;
}

bool sub_71005DC470(ksys::act::Actor* actor) {
    auto* obj = actor->m100();
    return obj && obj->_100 == 1;
}

bool sub_71005DC49C(ksys::act::Actor* actor) {
    auto* obj = actor->m100();
    return obj && obj->_100 == 2;
}

bool sub_71005DC4C8(ksys::act::Actor* actor) {
    auto* obj = actor->m100();
    return obj && obj->_100 == 4;
}

bool sub_71005DC4F4(ksys::act::Actor* actor) {
    auto* obj = actor->m100();
    return obj && obj->_100 == 3;
}

bool sub_71005DC520(ksys::act::Actor* actor) {
    auto* obj = actor->m100();
    return obj && obj->_100 == 0;
}

const sead::Vector3f& sub_71005DC54C(ksys::act::Actor* actor) {
    auto* obj = actor->m100();
    if (!obj)
        return sead::Vector3f::zero;
    return obj->_104;
}

const sead::Matrix34f& sub_71005DC57C(ksys::act::Actor* actor) {
    auto* obj = actor->m100();
    if (!obj)
        return sead::Matrix34f::ident;
    return obj->_80;
}

const sead::SafeString& sub_71005DC5AC(ksys::act::Actor* actor) {
    auto* obj = actor->m100();
    if (!obj)
        return sead::SafeString::cEmptyString;
    return obj->_48;
}

void sub_71005DC5DC(ksys::act::Actor* actor) {
    if (auto* obj = actor->m100())
        obj->sub_7100E4E084();
}

void sub_71005DC604(ksys::act::Actor* actor, ksys::act::BaseProc* proc) {
    if (auto* obj = actor->m100())
        obj->sub_7100E502EC(proc);
}

f32 sub_71005DA668(ksys::act::Actor* actor, int idx) {
    if (idx < 0)
        return 0.0f;
    auto* weapons = actor->getWeapons();
    if (idx > 5 || !weapons)
        return 0.0f;
    auto* weapon = sead::DynamicCast<uking::act::Weapon>(weapons->getEquippedWeapon(idx));
    if (!weapon)
        return 0.0f;
    auto* chemical = weapon->getChemicalStuff();
    if (!chemical)
        return 0.0f;
    return chemical->_1b8;
}

bool sub_71005DA7F4(ksys::act::Actor* actor, int idx) {
    if (idx < 0)
        return false;
    auto* weapons = actor->getWeapons();
    if (idx > 5 || !weapons)
        return false;
    auto* weapon = sead::DynamicCast<uking::act::Weapon>(weapons->getEquippedWeapon(idx));
    if (!weapon)
        return false;
    auto* chemical = weapon->getChemicalStuff();
    if (!chemical)
        return false;
    return chemical->_b8 >> 2 & 1;
}

bool sub_71005DA8CC(ksys::act::Actor* actor, int idx) {
    if (idx < 0)
        return false;
    auto* weapons = actor->getWeapons();
    if (idx > 5 || !weapons)
        return false;
    auto* weapon = sead::DynamicCast<uking::act::Weapon>(weapons->getEquippedWeapon(idx));
    if (!weapon)
        return false;
    auto* chemical = weapon->getChemicalStuff();
    if (!chemical)
        return false;
    return chemical->_1b8 > 0.0f;
}

void sub_71005DDA44(ksys::act::Actor* actor) {
    if (auto* attention = actor->getAttention()) {
        if (auto* client = attention->getClientByName("LockOn"))
            client->sub_7100D724FC(1);
    }
}

void sub_71005DDA94(ksys::act::Actor* actor) {
    if (auto* attention = actor->getAttention()) {
        if (auto* client = attention->getClientByName("LockOn"))
            client->sub_7100D7250C(1);
    }
}

void sub_71005DD2E8(ksys::act::Actor* actor) {
    ksys::act::disableAllAttClients(actor);
    ksys::act::enableAttClient(actor, "LockOn");
    ksys::act::enableAttClient(actor, "AutoAim");
}

void sub_71005DD34C(ksys::act::Actor* actor, bool on) {
    if (!actor)
        return;
    auto* chemical = actor->getChemicalStuff();
    if (!chemical)
        return;
    chemical->sub_7100D90AF4(on);
    if (!on)
        chemical->sub_7100D91978(0.0f);
}

ksys::act::Actor* sub_71005D7348(ksys::act::Actor* actor) {
    auto* ride_info = actor->getPlayerRideInfo();
    if (!ride_info)
        return nullptr;
    return sead::DynamicCast<ksys::act::Actor>(
        ride_info->_18.getProc(nullptr, ride_info->mActor));
}

bool sub_71005D83C8(ksys::act::Actor* actor, int idx) {
    auto* weapon = sub_71005D83E8(actor, idx);
    return weapon && (weapon->_e50 >> 6 & 1);
}

bool sub_71005D723C() {
    auto* wm = ksys::world::Manager::instance();
    if (!wm)
        return false;
    auto* weather = wm->getWeatherMgr();
    if (!weather)
        return false;
    return weather->isRaining();
}

bool sub_71005DD734(ksys::act::Actor* actor, int a1, ksys::as::ASList::Unk4* query, int slot,
                    int bank) {
    return actor->getASList()->x(a1, query, slot, bank,
                                 &ksys::as::ASList::Unk2::sub_710116388C, true);
}

bool sub_71005DD74C(ksys::act::Actor* actor, ksys::as::ASList::Unk4* query, int slot, int bank) {
    return actor->getASList()->x(3, query, slot, bank, &ksys::as::ASList::Unk2::sub_710116388C,
                                 true);
}

bool sub_71005DD780(ksys::act::Actor* actor, int a1, ksys::as::ASList::Unk4* query, int slot,
                    int bank) {
    return actor->getASList()->x(a1, query, slot, bank,
                                 &ksys::as::ASList::Unk2::sub_71011637EC, true);
}

bool sub_71005DD798(ksys::act::Actor* actor, int a1, ksys::as::ASList::Unk4* query, int slot,
                    int bank) {
    return actor->getASList()->x(a1, query, slot, bank,
                                 &ksys::as::ASList::Unk2::sub_71011638DC, true);
}

bool sub_71005DD7B0(ksys::act::Actor* actor, ksys::as::ASList::Unk4* query, int slot, int bank) {
    return actor->getASList()->x(3, query, slot, bank, &ksys::as::ASList::Unk2::sub_71011638DC,
                                 true);
}

bool sub_71005E1064(ksys::act::Actor* actor) {
    sead::Vector3f pos;
    actor->getMtx().getTranslation(pos);
    if (actor->getVelocity().y >= 0.0f)
        return false;
    sead::Vector3f end = pos;
    end += actor->getVelocity() * ksys::VFR::instance()->getDeltaFrame();
    return sub_710072E5F8(pos, end, 0, nullptr, nullptr, nullptr, 0.0f);
}

bool sub_71005E116C(ksys::act::BaseProcLink* link) {
    if (ksys::act::hasTag(link, ksys::act::tags::BeeTarget))
        return true;
    return ksys::act::isPlayerProfile(link);
}

int sub_71005E2B28(int value) {
    switch (value) {
    case 0:
        return 0;
    case 1:
        return 1;
    case 2:
        return 2;
    case 3:
        return 3;
    case 4:
        return 4;
    case 5:
        return 5;
    case 6:
        return 8;
    case 7:
        return 9;
    case 8:
        return 10;
    default:
        return 3;
    }
}

void sub_71005E22D4(sead::Vector3f* out, ksys::act::Actor* actor, const sead::Vector3f& dir,
                    f32 scale) {
    if (!out || !actor)
        return;
    *out = dir * scale + actor->getVelocity();
}

void sub_71005E2318(sead::Vector3f* out, ksys::act::Actor* actor, uking::dmg::DamageManager* mgr) {
    sead::Vector3f dir = sead::Vector3f::zero;
    if (!(mgr && mgr->m30(&dir))) {
        actor->getMtx().getBase(dir, 2);
        dir.normalize();
        dir = -dir;
    }
    *out = dir;
}

void sub_71005E242C(sead::Vector3f* out, ksys::act::Actor* actor, uking::dmg::DamageManager* mgr) {
    sead::Vector3f dir = sead::Vector3f::zero;
    if (!(mgr && mgr->m29(&dir))) {
        actor->getMtx().getBase(dir, 2);
        dir.normalize();
        dir = -dir;
    }
    *out = dir;
}

void sub_71005E01CC(ksys::act::Actor* actor, int a1, int a2) {
    auto* model = actor->getModel();
    if (!model)
        return;
    auto& units = model->getUnits();
    if (sead::Mathi::max(a2, a1) >= units.size())
        return;
    if (a2 >= 0 && units[a2]->mModelUnit)
        units[a2]->_1e |= 0x20;
    if (a1 >= 0 && units[a1]->mModelUnit)
        units[a1]->_1e &= ~0x20;
}

uking::act::Weapon* sub_71005DA374(ksys::act::Actor* actor, int idx) {
    if (idx < 0)
        return nullptr;
    auto* weapons = actor->getWeapons();
    if (idx > 5 || !weapons)
        return nullptr;
    return sead::DynamicCast<uking::act::Weapon>(weapons->getEquippedWeapon(idx));
}

bool sub_71005DAF0C(ksys::act::Actor* actor, ksys::as::ASList::Unk4* query, int slot, int bank,
                    bool a5) {
    if (actor->getASList()->x(3, query, slot, bank, &ksys::as::ASList::Unk2::sub_71011638DC, a5))
        return true;
    return actor->getASList()->x(0x10, query, slot, bank,
                                 &ksys::as::ASList::Unk2::sub_71011638DC, a5);
}

bool sub_71005DD5B0(ksys::act::Actor* actor, int a1, ksys::as::ASList::Unk4* query, int slot,
                    int bank) {
    auto* as_list = actor->getASList();
    if (as_list->x(a1, query, slot, bank, &ksys::as::ASList::Unk2::sub_710116383C, true))
        return true;
    if (!as_list->x_7(0, 0, &ksys::as::ASList::Unk2::sub_7101163940))
        return false;
    return as_list->x(a1, query, slot, bank, &ksys::as::ASList::Unk2::sub_71011638DC, true);
}

void sub_71005E1B7C(ksys::act::Actor* actor, bool enable) {
    auto* physics = actor->getPhysics();
    if (!physics)
        return;
    auto* ragdoll = physics->getRagdollInstance();
    if (!ragdoll)
        return;
    const int num = ragdoll->getNumConstraints();
    for (int i = 0; i < num; ++i)
        ragdoll->enableConstraint(i, enable);
}

void sub_71005E21E8(ksys::act::Actor* actor) {
    if (auto* enemy = sead::DynamicCast<Enemy>(actor))
        enemy->_f4c = 0;
}

void sub_71005E226C(ksys::act::Actor* actor, const sead::SafeString& bone_name, bool keyframed) {
    if (auto* ragdoll = actor->getRagdollInstance()) {
        const int idx = ragdoll->getBoneIndexByName(bone_name);
        if (idx >= 0)
            ragdoll->setKeyframed(idx, keyframed, ksys::phys::RagdollInstance::SyncToThisBone{true});
    }
}

bool sub_71005DA9A8(ksys::act::Actor* actor, int idx) {
    if (idx < 0)
        return false;
    auto* weapons = actor->getWeapons();
    if (idx > 5 || !weapons)
        return false;
    auto* weapon = sead::DynamicCast<uking::act::Weapon>(weapons->getEquippedWeapon(idx));
    if (!weapon)
        return false;
    return weapon->_d54 == 1;
}

bool sub_71005D7270(ksys::act::ai::InlineParamPack* params, const char* key) {
    auto& link = ksys::act::PlayerInfo::getSomeProcLink();
    if (link.hasProc()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&link, &accessor);
        sead::Vector3f pos;
        accessor.getActorMtx().getTranslation(pos);
        params->addVec3(pos, key, -1);
        return true;
    }
    params->addVec3(sead::Vector3f::zero, key, -1);
    return false;
}

bool sub_71005DD66C(ksys::act::Actor* actor, ksys::as::ASList::Unk4* query, int slot, int bank) {
    auto* as_list = actor->getASList();
    if (as_list->x(3, query, slot, bank, &ksys::as::ASList::Unk2::sub_710116383C, true))
        return true;
    if (!as_list->x_7(0, 0, &ksys::as::ASList::Unk2::sub_7101163940))
        return false;
    return as_list->x(3, query, slot, bank, &ksys::as::ASList::Unk2::sub_71011638DC, true);
}

// NON_MATCHING: the original branches on both exposure compares; ours folds them into cset + and
bool sub_71005DA304(ksys::act::BaseProcLink* link) {
    if (!ksys::act::hasTag(link, ksys::act::tags::ObjectNightGlow))
        return false;
    const f32 exposure = ksys::world::Manager::instance()->getEnvMgr()->getExposure();
    return exposure <= sead::Mathf::epsilon() && exposure >= -sead::Mathf::epsilon();
}

Enemy::Unk_12d0* sub_71005E2BCC(ksys::act::Actor* actor) {
    if (!sead::IsDerivedFrom<Enemy>(actor))
        return nullptr;
    return static_cast<Enemy*>(actor)->_12d0;
}

void sub_71005E2C58(ksys::act::Actor* actor) {
    if (auto* enemy = sead::DynamicCast<Enemy>(actor))
        enemy->_e82 |= 0x40;
}

// NON_MATCHING: register allocation and operand order in the cross product
void sub_71005E0230(sead::Vector3f* out, const ksys::act::Actor* actor, const sead::Vector3f& dir) {
    if (!actor)
        return;
    sead::Vector3f v;
    v.setCross(sead::Vector3f::ey, dir);
    v.y = 0.0f;
    v.normalize();
    out->set(v);
}

bool sub_71005E02E0(ksys::act::Actor* actor, Unk_7102357d20* sender, ksys::act::BaseProcLink* link) {
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::findLinkedActor(&accessor, actor, "RegistedActorMessageBroadCastTag");
    bool sent = false;
    if (accessor.hasProc()) {
        if (link)
            accessor.linkAcquire(link);
        sender->sub_710070DD78(accessor, true);
        sent = true;
    }
    return sent;
}

// NON_MATCHING: scheduling / register allocation only (same operations)
bool sub_71005DF66C(sead::Vector3f* out, ksys::act::Actor* actor, const sead::Vector3f* target,
                    f32* out_time, f32 height, f32 gravity) {
    if (!actor)
        return false;
    const f32 neg_height = 0.0f - height;
    if (neg_height <= 1.1920929e-07f && neg_height >= -1.1920929e-07f)
        return false;
    const f32 neg_gravity = 0.0f - gravity;
    if (neg_gravity <= 1.1920929e-07f && neg_gravity >= -1.1920929e-07f)
        return false;

    const sead::Matrix34f& mtx = actor->getMtx();
    const f32 dx = target->x - mtx.m[0][3];
    const f32 dz = target->z - mtx.m[2][3];
    const f32 dy = target->y - mtx.m[1][3];
    sead::Vector3f dir = {dx, 0.0f, dz};
    const f32 dist = std::sqrt(dx * dx + dz * dz);
    const f32 up_speed = std::sqrt(sead::Mathf::abs(2.0f * (height * gravity)));
    const f32 fall = sead::Mathf::clampMin(height - dy, 0.0f);
    const f32 time = -up_speed / gravity + std::sqrt(fall * -2.0f / gravity);
    const f32 speed = dist / time;
    dir.normalize();
    *out = dir * speed;
    if (out_time)
        *out_time = time;
    return true;
}

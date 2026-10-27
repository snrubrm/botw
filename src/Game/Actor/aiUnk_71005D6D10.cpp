#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/aiAwarenessFilters.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Camera/CameraMgr.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actPhysicsUserTag.h"
#include "KingSystem/ActorSystem/actUnk_71006e45c4.h"
#include "KingSystem/Graphics/gfxUnk_710260af28.h"
#include "KingSystem/ActorSystem/Attention/actActorAttention.h"
#include "KingSystem/ActorSystem/actGlobalParameter.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectGlobal.h"
#include "KingSystem/ActorSystem/Attention/actAttClient.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include <cmath>
#include "Game/Actor/aiUnk_7102357d20.h"
#include "Game/Actor/aiUnk_7100EDD26C.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "Game/Actor/aiUnk_71007368A4.h"
#include "Game/Actor/aiUnk_71006F1DF0.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectLiftable.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectEnemyLevel.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/System/Vibration.h"
#include "KingSystem/Sound/sndSound.h"
#include "KingSystem/Physics/System/physStaticCompoundMgr.h"
#include "KingSystem/Physics/System/physSystem.h"
#include "Game/Actor/actSoundProxy.h"
#include <xlink2/xlink2HandleSLink.h>
#include "KingSystem/ActorSystem/actAiActionBase.h"
#include "KingSystem/ActorSystem/actAiParam.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Physics/System/physContactPointInfo.h"
#include "KingSystem/Physics/System/physHavokAI.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include "KingSystem/Physics/Ragdoll/physRagdollInstance.h"
#include "KingSystem/ActorSystem/actTag.h"
#include "KingSystem/World/worldWeatherMgr.h"
#include "KingSystem/World/worldEnvMgr.h"
#include "KingSystem/World/worldManager.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include <gsys/gsysModelAccessKey.h>
#include <gsys/gsysModel.h>
#include <gsys/gsysModelUnit.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <prim/seadStringBuilder.h>
#include "KingSystem/Utils/MathUtil.h"
#include "Game/UI/uiUtils.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"
#include "KingSystem/ActorSystem/actInfoData.h"
#include "KingSystem/Terrain/teraSystem.h"
#include "Game/Actor/actOptionalWeapon.h"
#include <prim/seadBitUtil.h>
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/actHorseRideInfo.h"
#include "Game/Actor/actNPC.h"
#include "Game/Actor/actWeapon.h"
#include "Game/Actor/Damage/dmgDamageCallback.h"
#include "Game/Actor/Damage/dmgDamageManager.h"
#include "Game/Actor/Damage/dmgDamageManagerBase.h"
#include "Game/Actor/Player/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actBoneControl.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/ActorSystem/actDropData.h"
#include "KingSystem/ActorSystem/actUnk_7100e4e084.h"
#include "KingSystem/ActorSystem/actUnk_71006ecc78.h"
#include "Game/AutoPlacement/AutoPlacementMgr.h"
#include "KingSystem/ActorSystem/actLodState.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapObjectLink.h"

namespace uking::ui {
// 0x7100a9d0b4 (defined in uiMiscFacade.cpp): forwards a dungeon-rotate marker to the UI singleton.
void sub_7100A9D0B4(const void* a0);
}  // namespace uking::ui

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

// 0x71005d6e28: whether the actor may play the damage / death reaction. Excludes the damage
// types that other code handles (and dead actors).
// NON_MATCHING: the type-5 arm tests the enemy pointer after the damage type and narrows the flag
// load to a byte; the true / false return blocks are laid out the other way round.
bool sub_71005D6E28(ksys::act::Actor* actor) {
    if (actor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_40000))
        return false;

    auto* mgr = actor->getDamageMgr();
    if (!mgr)
        return false;
    const s32 type = mgr->getField54();
    auto* enemy = sead::DynamicCast<Enemy>(actor);

    if (!enemy || !enemy->_e84.isOnBit(0) || mgr->checkDamageFlags(8) ||
        sub_7100736BD8(type) || type == 0x17) {
        s32* life = actor->getLife();
        if (life && *life < 1)
            return true;
    }

    auto* player_or_enemy = sead::DynamicCast<ksys::act::PlayerOrEnemy>(actor);
    if (player_or_enemy && (player_or_enemy->m151(3) || player_or_enemy->m151(4)))
        return true;

    if (enemy && type == 5 && enemy->_e84.isOnBit(0))
        return true;

    switch (type) {
    case -1:
    case 0:
    case 1:
    case 2:
    case 5:
        return false;
    default:
        return true;
    }
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
    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::acquireActor(&link, &accessor);
    return accessor.getField44C_Vec3();
}

const sead::Vector3f& sub_71005D9548(ksys::act::Actor* actor) {
    if (!sead::IsDerivedFrom<Enemy>(actor))
        return sead::Vector3f::zero;
    auto* enemy = static_cast<Enemy*>(actor);
    ksys::act::ActorLinkConstDataAccess accessor;
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
                             uking::act::DamageCallback* callback) {
    auto* damage_mgr = actor->getDamageMgr();
    if (!damage_mgr)
        return false;
    if (damage_mgr == callback->mDamageManager)
        return true;
    auto* mgr = sead::DynamicCast<uking::act::DamageManager>(damage_mgr);
    if (!mgr)
        return false;
    mgr->addDamageCallback(timing, callback);
    return true;
}

// 0x71005e1fa8 / 0x71005e2068 / 0x71005e2128 (lane1 s43): the Enemy's `_f4c` reached the GlobalParameter's ForceTired /
// ForceTiredNoSight / ForceWarpReturn LOD count.
bool sub_71005E1FA8(ksys::act::Actor* actor) {
    auto* global = ksys::act::GlobalParameter::instance();
    if (!global)
        return false;
    auto* param = global->getGlobalParam();
    if (!param)
        return false;
    f32 value = 0.0f;
    if (auto* enemy = sead::DynamicCast<Enemy>(actor))
        value = enemy->_f4c;
    return value >= f32(param->mEnemyForceTiredLODCount.ref());
}

bool sub_71005E2068(ksys::act::Actor* actor) {
    auto* global = ksys::act::GlobalParameter::instance();
    if (!global)
        return false;
    auto* param = global->getGlobalParam();
    if (!param)
        return false;
    f32 value = 0.0f;
    if (auto* enemy = sead::DynamicCast<Enemy>(actor))
        value = enemy->_f4c;
    return value >= f32(param->mEnemyForceTiredNoSightLODCount.ref());
}

bool sub_71005E2128(ksys::act::Actor* actor) {
    auto* global = ksys::act::GlobalParameter::instance();
    if (!global)
        return false;
    auto* param = global->getGlobalParam();
    if (!param)
        return false;
    f32 value = 0.0f;
    if (auto* enemy = sead::DynamicCast<Enemy>(actor))
        value = enemy->_f4c;
    return value >= f32(param->mEnemyForceWarpReturnLODCount.ref());
}

bool sub_71005E1800(ksys::act::Actor* actor, Unk_710235aba0* sender, const char* tag) {
    sender->_18.y(actor);
    return sub_71005E1884(actor, sender, tag);
}

bool sub_71005E1884(ksys::act::Actor* actor, Unk_7102357d20* sender, const char* tag) {
    if (sead::SafeString(tag).isEmpty())
        return false;
    auto* object = actor->getMapObject();
    if (!object)
        return false;
    auto* links = object->getLinkData();
    if (!links)
        return false;
    auto objects = links->mObjects;
    u32 found = 0;
    for (s32 i = 0; i < objects.size(); ++i) {
        if (!objects[i])
            continue;
        ksys::act::ActorLinkConstDataAccess accessor;
        objects[i]->getActorWithAccessor(accessor);
        if (accessor.getProc() && accessor.hasTag(tag)) {
            found = 1;
            sender->sub_710070DD78(accessor, true);
        }
    }
    return found & 1;
}

// 0x71005e1630: sends `sender` every linked actor whose unit config name is `name` (all linked actors
// when `name` is null).
bool sub_71005E1630(ksys::act::Actor* actor, Unk_7102357d20* sender, const char* name) {
    if (name && sead::SafeString(name).isEmpty())
        return false;
    auto* object = actor->getMapObject();
    if (!object)
        return false;
    auto* links = object->getLinkData();
    if (!links)
        return false;
    auto objects = links->mObjects;
    u32 found = 0;
    for (s32 i = 0; i < objects.size(); ++i) {
        if (!objects[i])
            continue;
        const sead::SafeString unit_name(objects[i]->getUnitConfigName());
        if (!name || unit_name == name) {
            ksys::act::ActorLinkConstDataAccess accessor;
            objects[i]->getActorWithAccessor(accessor);
            if (accessor.getProc()) {
                found = 1;
                sender->sub_710070DD78(accessor, true);
            }
        }
    }
    return found & 1;
}

bool sub_71005E1974(ksys::act::Actor* actor, Unk_71023e7bc0* sender, const char* tag) {
    sender->_18.x(actor);
    return sub_71005E1884(actor, sender, tag);
}

bool sub_71005E19F8(ksys::act::Actor* actor, Unk_7102357d20* sender, const char* tag) {
    if (sead::SafeString(tag).isEmpty())
        return false;
    auto* object = actor->getMapObject();
    if (!object)
        return false;
    auto* links = object->getLinkData();
    if (!links)
        return false;
    auto objects = links->mObjects;
    u32 found = 0;
    for (s32 i = 0; i < objects.size(); ++i) {
        if (!objects[i])
            continue;
        ksys::act::ActorLinkConstDataAccess accessor;
        objects[i]->getActorWithAccessor(accessor);
        if (accessor.getProc() && accessor.hasTag(tag)) {
            found = 1;
            sender->sub_710070DFD8(accessor, true);
        }
    }
    return found & 1;
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

bool sub_71005DA114(ksys::act::Actor* actor, uking::act::DamageCallback* callback) {
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

// 0x71005da164: collects the position of every linked map object that has the EnemyHide
// (0x0ba4a61e) tag into `points`; without a list, just reports whether one exists.
bool sub_71005DA164(ksys::act::Actor* actor, sead::ObjList<sead::Vector3f>* points) {
    if (!actor)
        return false;
    auto* object = actor->getMapObject();
    if (!object)
        return false;
    auto* links = object->getLinkData();
    u32 found = 0;
    if (links && links->mObjects.size() != 0) {
        auto& objects = links->mObjects;
        auto* const objs = objects.getBufferPtr();
        if (points) {
            for (s32 i = 0; i != objects.size(); ++i) {
                if (!objs[i])
                    continue;
                ksys::act::ActorLinkConstDataAccess accessor;
                objs[i]->getActorWithAccessor(accessor);
                if (!accessor.hasTag(0x0ba4a61e))
                    continue;
                if (!points->isFull()) {
                    sead::Vector3f pos;
                    accessor.getActorMtx().getTranslation(pos);
                    points->emplaceBack(pos);
                    if (points->isFull()) {
                        found = 1;
                        break;
                    }
                }
                found = 1;
            }
        } else {
            for (s32 i = 0; i != objects.size(); ++i) {
                if (!objs[i])
                    continue;
                ksys::act::ActorLinkConstDataAccess accessor;
                objs[i]->getActorWithAccessor(accessor);
                if (accessor.hasTag(0x0ba4a61e))
                    found = 1;
            }
        }
    }
    return found & 1;
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
    ksys::act::ActorLinkConstDataAccess accessor;
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
    auto* mgr = uking::AutoPlacementMgr::instance();
    if (!mgr)
        return false;
    return mgr->isNonAutoPlacement(pos, true);
}

bool sub_71005D9FC0(ksys::act::BaseProcLink* link) {
    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::acquireActor(link, &accessor);
    sead::Vector3f pos;
    accessor.getActorMtx().getTranslation(pos);
    auto* mgr = uking::AutoPlacementMgr::instance();
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
    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::acquireActor(&static_cast<Enemy*>(actor)->_c48._8, &accessor);
    return accessor.sub_7100D12E64();
}

bool sub_71005D9F70(ksys::act::Actor* actor) {
    sead::Vector3f pos;
    actor->getMtx().getTranslation(pos);
    auto* mgr = uking::AutoPlacementMgr::instance();
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

// NON_MATCHING: clang keeps the filter address in a second callee-saved register where the original
// rematerialises it, and splits one request zero store.
// 0x71005e0f68: the link of the sight target that matches the actor's sight angle (kind 2).
ksys::act::BaseProcLink* sub_71005E0F68(ksys::act::Actor* actor) {
    auto* awareness = actor->getAwareness();
    if (!awareness)
        return &ksys::act::getDummyBaseProcLink();

    Unk_7102451678 filter;
    auto* sensor = awareness->_260[0];
    if (sensor) {
        if (auto* entry = ksys::act::sub_7100D7EEE8(&sensor->_8, &filter)) {
            if (entry->_a0 == 2) {
                Unk_71023e26d8 request;
                if (auto* sight = awareness->_260[0])
                    sight->m5(&request);
                if (entry->_a8 < request.params.sight.radius * 2.0f / 3.0f)
                    return &entry->_0.mLink;
            }
        }
    }
    return &ksys::act::getDummyBaseProcLink();
}

namespace {

// NON_MATCHING: one extra bool copy after the filter call and a different false-return block order.
// Face callback of sub_71005E11AC (vtable 0x710242dd40): keeps a usable face and checks its area.
class NavFaceAreaCallback : public ksys::phys::NavMeshFaceCallback {
public:
    bool m0(const ksys::phys::Unk_7100f7e9f0& face, const sead::Vector3f& ref_pos) override {
        const s32 material = face.sub_7100F7EEE4();
        if (material == 6 || material == 8)
            return false;
        if (auto* filter = mNav->_58) {
            if (!filter->m4(mNav, material, 0, ksys::phys::NavMeshCharacterType::Player))
                return false;
        } else {
            if (sead::Mathf::abs(ksys::phys::NavMeshCharacter::sub_7100F74FD8(
                    mNav->_1d8, material)) > std::numeric_limits<f32>::max())
                return false;
        }
        mFace = face;
        if (face.sub_7100F7ED6C(nullptr) >= mMinArea)
            return true;
        return false;
    }

    ksys::phys::NavMeshCharacter* mNav;
    ksys::phys::Unk_7100f7e9f0 mFace;
    f32 mMinArea;
};

}  // namespace

// NON_MATCHING: block order of the material / material-6 test paths.
// 0x71005e11ac: finds a navmesh position near `from` (or the actor's position) for the material of the
// actor's navmesh character.
bool sub_71005E11AC(sead::Vector3f* out, ksys::act::Actor* actor, const sead::Vector3f* from,
                    f32 radius, f32 min_area) {
    auto* nav = actor->m45();
    if (!nav)
        return false;

    auto* filter = nav->_58;
    const u32 material = nav->_2a4.load() & 0xffff;
    if (material != 6 && material != 8) {
        if (filter) {
            if (filter->m4(nav, material, 0, ksys::phys::NavMeshCharacterType::Player)) {
                *out = actor->getMtx().getTranslation();
                return true;
            }
        } else if (sead::Mathf::abs(ksys::phys::NavMeshCharacter::sub_7100F74FD8(
                       nav->_1d8, material)) <= std::numeric_limits<f32>::max()) {
            *out = actor->getMtx().getTranslation();
            return true;
        }
    }

    bool usable;
    if (filter)
        usable = filter->m4(nav, 6, 0, ksys::phys::NavMeshCharacterType::Player);
    else
        usable = sead::Mathf::abs(ksys::phys::NavMeshCharacter::sub_7100F74FD8(nav->_1d8, 6)) <=
                 std::numeric_limits<f32>::max();

    if (!usable) {
        if (from->isNan()) {
            const sead::Vector3f pos = actor->getMtx().getTranslation();
            const auto face = nav->sub_7100F76078(out, pos, radius);
            return face.sub_7100F7EB40();
        }
        const auto face = nav->sub_7100F76078(out, *from, radius);
        return face.sub_7100F7EB40();
    }

    NavFaceAreaCallback callback;
    callback.mNav = nav;
    callback.mMinArea = min_area;
    if (from->isNan())
        nav->sub_7100F76168(radius, false, &callback);
    else
        nav->sub_7100F761C8(*from, radius, false, &callback);
    if (!callback.mFace.sub_7100F7EB40())
        return false;
    callback.mFace.sub_7100F7EB60(out);
    return true;
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

void sub_71005DC02C(ksys::act::Actor* actor) {
    if (sead::IsDerivedFrom<ksys::act::PhysicsUserTag>(&actor->mPhysicsUserTag)) {
        if (auto* controller = actor->getCharacterController())
            controller->sub_7100F62D3C(false);

        if (auto* bodies = actor->getRigidBodyByName(ksys::act::getStr_Body().cstr())) {
            const s32 last = bodies->getRigidBodies().size() - 1;
            for (s32 i = 0; i <= last; ++i)
                bodies->getRigidBody(i)->setEntityMotionFlag8(false);
        }

        actor->mPhysicsUserTag.resetMaybe();
    }
}

void sub_71005DBE1C(ksys::phys::CharacterController* controller, s32 mode, u8 value, bool a3, bool a4,
                    bool a5, bool a6) {
    controller->sub_7100F62D3C(true);
    auto* tag = controller->sub_7100F5EDA8();
    if (sead::IsDerivedFrom<ksys::act::PhysicsUserTag>(tag))
        static_cast<ksys::act::PhysicsUserTag*>(tag)->setStateMaybe(mode, value, a3, a4, a5, a6);
}

void sub_71005DC158(ksys::phys::CharacterController* controller) {
    controller->sub_7100F62D3C(false);
    auto* tag = controller->sub_7100F5EDA8();
    if (sead::IsDerivedFrom<ksys::act::PhysicsUserTag>(tag))
        static_cast<ksys::act::PhysicsUserTag*>(tag)->resetMaybe();
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

// NON_MATCHING: identical instruction sequence; only the actor / proc callee-saved pair is swapped.
// 0x71005dc640: attaches the grabbed actor `handle` to its bone transform.
void sub_71005DC640(ksys::act::Actor* actor, ksys::act::BaseProcHandle* handle, int grab_idx) {
    auto* proc = sead::DynamicCast<ksys::act::Actor>(handle->getProc());
    if (!proc) {
        actor->getConnectedCalcChild();
    } else {
        actor->getConnectedCalcChild();
        if (!actor->getConnectedCalcChild())
            actor->setConnectedCalcChild(proc, false);
        proc->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_40000000);
        actor->sendMessage(*proc->getMesTransceiverId(), ksys::MessageType(0x8000001), actor, true);
        if (auto* obj = proc->m100())
            obj->sub_7100E4E304(sub_7100EDD258(actor, grab_idx), actor->getMtx());
        if (auto* obj = proc->m100())
            obj->sub_7100E50254();

        const sead::SafeString& bone_name = sub_7100EDD258(actor, grab_idx);
        const auto key = actor->getModel()->searchBone(bone_name);
        if (key.isValid()) {
            sead::Matrix34f mtx;
            actor->getModel()
                ->getUnits()
                .unsafeAt(key.model_unit_index)
                ->mModelUnit->getBoneWorldMatrix(&mtx, key.bone_index);
            proc->m100();
            const sead::Matrix34f* src = &sead::Matrix34f::ident;
            if (auto* obj = proc->m100())
                src = &obj->_80;
            mtx.setMul(mtx, *src);
            actor->setMatrix(mtx, nullptr);
        }
    }
    handle->releaseAndWakeProc();
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

// NON_MATCHING: the inlined Matrix34 multiply keeps the rotation rows in vector registers where the
// original broadcasts their scalars (21 extra movs; same operations).
// 0x71005ddae4: builds the transform that rotates by `rot` around the actor's home position.
void sub_71005DDAE4(sead::Matrix34f* out, const ksys::act::Actor* actor,
                    const sead::Vector3f& rot) {
    sead::Matrix34f rotation;
    rotation.makeR(rot);
    if (!out)
        return;

    const sead::Vector3f home_position = actor->getHomeMtxRaw().getTranslation();
    sead::Matrix34f inverse_home;
    inverse_home.makeT(-home_position);
    sead::Matrix34f transform;
    transform.setMul(rotation, inverse_home);
    sead::Matrix34f translation;
    translation.makeT(home_position);
    transform.setMul(translation, transform);
    *out = transform;
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

// 0x71005e2ad4: whether the actor the accessor points at is the kind of target
// sub_71006E3580 accepts (resolves the link first).
bool sub_71005E2AD4(const ksys::act::BaseProcAccessor& accessor) {
    ksys::act::ActorLinkConstDataAccess link;
    link.acquireActor(accessor);
    return sub_71006E3580(link);
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

void sub_71005E2318(sead::Vector3f* out, ksys::act::Actor* actor, uking::act::DamageManager* mgr) {
    sead::Vector3f dir = sead::Vector3f::zero;
    if (!(mgr && mgr->m30(&dir))) {
        actor->getMtx().getBase(dir, 2);
        dir.normalize();
        dir = -dir;
    }
    *out = dir;
}

void sub_71005E242C(sead::Vector3f* out, ksys::act::Actor* actor, uking::act::DamageManager* mgr) {
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

void sub_71005E1AE8(ksys::act::Actor* actor) {
    if (auto* dynamic_actor = sead::DynamicCast<ksys::act::DynamicActor>(actor)) {
        if (auto* handler = dynamic_actor->_868)
            handler->_d2.set(0x40);
    }
}

// 0x71005e1d00: pushes the actor out of the penetrating contact points that are above it. Only
// points more than 1 m away and above the actor with a negative separating distance count; their
// distances along the separating normals are averaged and fed to the character controller.
// NON_MATCHING: the empty-contact early exit duplicates the tail block where the original shares
// it, and the contact-point distance load stays after the two range compares.
void sub_71005E1D00(ksys::act::Actor* actor) {
    auto* body = actor->getMainBody();
    if (!body)
        return;
    auto* controller = actor->getCharacterController();
    if (!controller)
        return;

    sead::Vector3f push = sead::Vector3f::zero;
    const f32 speed = controller->sub_7100F5EF00();
    if (speed <= 0.1f && speed >= -0.1f) {
        if (auto* info = body->getContactPointInfo()) {
            const sead::Vector3f position = actor->getMtx().getTranslation();
            s32 count = 0;
            auto it = info->begin();
            auto end = info->end();
            for (; it != end; ++it) {
                const auto* point = *it;
                const sead::Vector3f point_position =
                    it.getPointPosition(ksys::phys::ContactPointInfo::Iterator::Point::BodyA);
                sead::Vector3f dir = point_position - position;
                dir.y = 0.0f;
                const f32 dist = dir.normalize();
                if (dist > 1.0f && point_position.y - position.y > 1.0f &&
                    point->separating_distance < 0.0f &&
                    dir.dot(point->separating_normal) >= 0.0f) {
                    push.x += point->separating_distance * point->separating_normal.x;
                    push.z += point->separating_distance * point->separating_normal.z;
                    ++count;
                }
                ++it;
            }
            push *= 0.1f;
            if (count > 0)
                push *= 1.0f / count;
        }
    }
    if (push.x == 0.0f && push.z == 0.0f) {
        controller->sub_7100F5F060(sead::Vector3f::zero);
    } else {
        controller->sub_7100F5F060(push * 30.0f);
    }
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
    auto& link = uking::act::PlayerInfo::getSomeProcLink();
    if (link.hasProc()) {
        ksys::act::ActorLinkConstDataAccess accessor;
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

bool sub_71005E2B48(ksys::act::Actor* actor) {
    if (sub_71007A2604(actor)) {
        if (auto* attack = sub_71007A255C(actor, 0)) {
            if (attack->sub_71007A1F68(0x1000) ||
                ksys::act::hasTag(&attack->_e8, 0x3d2fc55b))
                return true;
        }
    }
    if (auto* chemical = actor->getChemicalStuff()) {
        if (chemical->_b8 & 2)
            return true;
    }
    return false;
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
void sub_71005E0230(sead::Vector3f* out, const ksys::phys::RigidBody* actor, const sead::Vector3f& dir) {
    if (!actor)
        return;
    sead::Vector3f v;
    v.setCross(sead::Vector3f::ey, dir);
    v.y = 0.0f;
    v.normalize();
    out->set(v);
}

bool sub_71005E02E0(ksys::act::Actor* actor, Unk_7102357d20* sender, ksys::act::BaseProcLink* link) {
    ksys::act::ActorLinkConstDataAccess accessor;
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

// 0x71005dd1cc: fades the model material by `a3` (the material index comes from the ray cast in
// sub_71005DCD84 when the angle is outside [-epsilon, 10 degrees]).
bool sub_71005DD1CC(ksys::act::Actor* actor, bool a2, f32 a3, f32 a4) {
    if (!actor || !actor->getModel())
        return false;

    u32 material = 0;
    f32 value;
    if (a3 <= sead::Mathf::epsilon() && a3 >= -sead::Mathf::epsilon()) {
        value = 0.0f;
    } else {
        if (!sub_71005DCD84(&material, actor, a4, a2))
            return false;
        value = f32(material);
    }

    Unk_710260af28::instance()->sub_7100F1E794(actor->getModel(), value, a3);
    return true;
}

// 0x71005d70c8: the Enemy-only entry point of sub_71005D715C (the Enemy target link).
bool sub_71005D70C8(ksys::act::Actor* actor) {
    if (!sead::IsDerivedFrom<uking::act::Enemy>(actor))
        return false;
    return sub_71005D715C(actor);
}

// 0x71005dcba4: the same forward as sub_71005DCB3C but only for a non-zero speed (the launch
// velocity is relative to sead::Vector3f::zero).
bool sub_71005DCBA4(sead::Vector3f* out, ksys::act::Actor* actor, const sead::Vector3f* pos,
                    f32 a3) {
    if (!actor)
        return false;

    const f32 neg = 0.0f - a3;
    if (neg <= sead::Mathf::epsilon() && neg >= -sead::Mathf::epsilon())
        return false;

    sead::Vector3f gravity;
    sub_710072DC54(&gravity, actor);
    return sub_710072D344(out, sead::Vector3f::zero, *pos, a3, gravity.y);
}

// 0x71005df024: whether `actor` may attack `other` (hidden / fire / freeze rules): the actors must
// be closer than `range`, moving at least `min_speed`, and looking more than `angle_limit` away from
// the other's forward direction.
// NON_MATCHING: the two parameter saves swap order and the untagged state range test is encoded
// `cmp #3; b.hi` instead of `cmp #4; b.hs`; same instructions otherwise (147).
bool sub_71005DF024(f32 range, f32 min_speed, f32 angle_limit, ksys::act::Actor* actor,
                    ksys::act::Actor* other) {
    if (!actor)
        return false;

    const sead::Vector3f offset =
        actor->getMtx().getTranslation() - other->getMtx().getTranslation();
    if (offset.length() >= range)
        return true;

    sead::Vector3f velocity;
    velocity = actor->getVelocity();
    const f32 speed = velocity.normalize();
    const f32 dot = velocity.dot(other->getMtx().getBase(2));
    const f32 angle = sead::Mathf::acos(sead::Mathf::clamp(dot, -1.0f, 1.0f));

    if (!(speed >= min_speed) || angle <= angle_limit)
        return true;

    if (actor->getActorFlags2().isAnyOn({ksys::act::Actor::ActorFlag2::_40000000,
                                        ksys::act::Actor::ActorFlag2::_40}))
        return true;

    auto* chemical = actor->getChemicalStuff();
    if (!chemical)
        return false;

    const bool tagged = ksys::act::hasTag(actor, 0xff2ecb67);
    const u8 state = chemical->_c0;
    if (tagged) {
        switch (state) {
        case 1: {
            const auto* liftable = actor->getParam()->getRes().mGParamList->getLiftable();
            if (*liftable->mDisableFreezeLift)
                return true;
            break;
        }
        case 2: {
            const auto* liftable = actor->getParam()->getRes().mGParamList->getLiftable();
            if (*liftable->mDisableBurnLift)
                return true;
            break;
        }
        case 4:
            return true;
        }
        return false;
    }

    switch (state) {
    case 1:
    case 2:
    case 4:
        return true;
    case 3:
        return false;
    default:
        return false;
    }
}

// 0x71005df820: one step of the vertical buoyancy velocity for floating in water (called by the
// WaterFloat actions and the swim damage / jump actions).
// NON_MATCHING: same operations (172 vs 176 instructions); the original keeps the outer flag tests
// and the clamp tails in separate blocks and enters the clamp phase with an early exit, ours
// merges them and if-converts the clamps.
void sub_71005DF820(f32* out, f32 velY, f32 depth, f32 floatDepth, f32 inWaterDepth, f32 floatRadius,
                    f32 floatCycleTime, f32 changeDepthSpeed) {
    const f32 inv_cycle = 1.0f / std::max(floatCycleTime, 0.0001f);
    const f32 diff = depth - (floatDepth + inWaterDepth);
    const f32 delta = ksys::VFR::instance()->getDeltaFrame();
    const f32 omega = inv_cycle * sead::Mathf::pi2();
    f32 velocity = velY + diff * (inv_cycle * (inv_cycle * 39.47842f)) * delta;
    const f32 limit = omega * floatRadius;
    if (sead::Mathf::abs(velocity) < limit * 0.5f) {
        if (sead::Mathf::abs(diff) < floatRadius * 0.25f) {
            const f32 amplitude =
                omega * sead::Mathf::sqrt(floatRadius * floatRadius - diff * diff);
            if (velocity >= 0.0f)
                ksys::VFR::lerp(&velocity, amplitude, 0.5f);
            else
                ksys::VFR::lerp(&velocity, -amplitude, 0.5f);
        }
    }
    if (sead::Mathf::abs(diff) > floatRadius) {
        if (diff > 0.0f) {
            if (velocity >= 0.0f) {
                const f32 max_delta = sead::Mathf::clampMin(2.0f * limit, changeDepthSpeed);
                f32 max_velocity = max_delta * 5.0f;
                if (diff - floatRadius <= max_velocity) {
                    const f32 t = ((floatDepth + inWaterDepth) - floatRadius) / max_velocity;
                    max_velocity = max_delta * t + limit * (1.0f - t);
                }
                velocity = sead::Mathf::clamp(velocity, -max_velocity, max_velocity);
            }
        } else if (limit < changeDepthSpeed) {
            const f32 max_velocity = sead::Mathf::clampMax(-diff / delta, changeDepthSpeed);
            velocity = sead::Mathf::clamp(velocity, -max_velocity, max_velocity);
        } else {
            velocity = sead::Mathf::clamp(velocity, -limit, limit);
        }
    } else {
        velocity = sead::Mathf::clamp(velocity, -limit, limit);
    }
    *out = velocity;
}

// 0x71005df270: the position of the linked map object named `anchor_name`, moved `dist` towards the
// enemy's current target position (or towards the origin without one), along the ground plane.
void sub_71005DF270(sead::Vector3f* out, ksys::act::Actor* actor, const sead::SafeString& anchor_name,
                    f32 dist) {
    if (auto* object = actor->getMapObject()) {
        if (auto* links = object->getLinkData()) {
            auto objects = links->mObjects;
            for (s32 i = 0; i < objects.size(); ++i) {
                if (sead::SafeString(objects(i)->getUnitConfigName()) == anchor_name) {
                    const sead::Vector3f& anchor =
                        sead::IsDerivedFrom<Enemy>(actor) ? static_cast<Enemy*>(actor)->_c48._18
                                                          : sead::Vector3f::zero;
                    out->set(anchor);
                    *out -= objects(i)->getTranslate();
                    out->y = 0;
                    out->normalize();
                    *out *= dist;
                    *out += objects(i)->getTranslate();
                    return;
                }
            }
        }
    }
    actor->getHomePos(out);
}

// 0x71005d9a20: the horizontal front direction of the actor (or of the enemy's target matrix when
// the enemy's target is not the player, or the camera direction is zero).
// NON_MATCHING: same 210 instructions; ours sets the return value before the last out.z store and
// hoists the target matrix address in the camera-zero branch.
bool sub_71005D9A20(sead::Vector3f* out, ksys::act::Actor* actor) {
    if (!out)
        return false;

    sead::Vector3f dir;
    if (sead::IsDerivedFrom<Enemy>(actor) &&
        ksys::act::isPlayerProfile(&static_cast<Enemy*>(actor)->_c48._8)) {
        ksys::sub_7100D8C7FC(&dir);
        dir.y = 0.0f;
        dir.normalize();
        if (dir.x == 0.0f && dir.z == 0.0f) {
            const sead::Matrix34f& mtx = sead::IsDerivedFrom<Enemy>(actor)
                                             ? static_cast<Enemy*>(actor)->_c48._24
                                             : sead::Matrix34f::ident;
            mtx.getBase(dir, 2);
            dir.y = 0.0f;
            dir.normalize();
        }
    } else {
        const sead::Matrix34f& mtx = sead::IsDerivedFrom<Enemy>(actor)
                                         ? static_cast<Enemy*>(actor)->_c48._24
                                         : sead::Matrix34f::ident;
        mtx.getBase(dir, 2);
        dir.y = 0.0f;
        dir.normalize();
    }
    if (dir.x == 0.0f && dir.y == 0.0f && dir.z == 0.0f) {
        *out = sead::Vector3f(0.0f, 0.0f, 1.0f);
        return false;
    }
    *out = dir;
    return true;
}

// 0x71005dc8ac: writes the launch velocity for a throw at the carried object's target to `out`.
// NON_MATCHING: same 164 instructions, but the position copy's y / z registers are swapped and
// the local stack slots differ (the original keeps the angle and the speed limit in the
// saved-register holes).
bool sub_71005DC8AC(ksys::act::Actor* actor, sead::Vector3f* out) {
    auto* carried = actor->m100();
    if (!carried)
        return false;

    sead::Vector3f gravity;
    sead::Vector3f target;
    f32 angle;
    f32 max_speed;
    if (!carried->sub_7100E5019C(&target, &angle, &max_speed))
        return false;

    const sead::Matrix34f& mtx = actor->getMtx();
    sead::Vector3f delta;
    sead::Vector3f pos = mtx.getTranslation();
    if (auto* controller = actor->getCharacterController()) {
        pos = pos + mtx.getBase(1);
    } else if (auto* body = actor->getMainBody()) {
        body->getCenterOfMassInWorld(&pos);
    }

    delta = target - pos;
    sub_710072DC50(&gravity, actor);
    const f32 dist = sead::Mathf::sqrt(delta.x * delta.x + delta.z * delta.z);
    const f32 tan_angle = sead::Mathf::tan(angle);
    const f32 v2 = gravity.y * dist * dist /
                   (2.0f * ((delta.y - dist * tan_angle) / (tan_angle * tan_angle + 1.0f)));
    if (v2 >= 0.0f) {
        const f32 frame_speed = sead::Mathf::sqrt(v2) / 30.0f;
        const f32 speed = frame_speed > max_speed ? max_speed : frame_speed;
        sead::Vector3f dir(delta.x, 0.0f, delta.z);
        dir.normalize();
        *out = (dir * sead::Mathf::cos(angle) + sead::Vector3f::ey * sead::Mathf::sin(angle)) * speed;
    } else {
        const f32 neg_speed = 0.0f - max_speed;
        if (!(neg_speed <= sead::Mathf::epsilon() && neg_speed >= -sead::Mathf::epsilon())) {
            sead::Vector3f gravity2;
            sub_710072DC54(&gravity2, actor);
            sub_710072D344(out, sead::Vector3f::zero, delta, max_speed, gravity2.y);
        }
    }
    return true;
}

// 0x71005dcb3c: forwards the actor's gravity/position vector to the launch-point search.
bool sub_71005DCB3C(sead::Vector3f* out, ksys::act::Actor* actor, const sead::Vector3f* pos, f32 a,
                    f32 b) {
    if (!actor)
        return false;
    sead::Vector3f p;
    sub_710072DC50(&p, actor);
    return sub_71005DF4E4(out, pos, &p, a, b);
}

// 0x71005dc208: plays the SafeString/matrix pair returned for actor slot `idx` on the same
// effect object the child actor exposes (child->m100()).
void sub_71005DC208(ksys::act::Actor* actor, ksys::act::Actor* child, int idx) {
    if (auto* obj = child->m100())
        obj->sub_7100E4E304(sub_7100EDD258(actor, idx), actor->getMtx());
}

// 0x71005dd27c: switches the actor's model material to `material` and eases `a3` (the model
// effects manager, then the material fade itself).
void sub_71005DD27C(ksys::act::Actor* actor, u32 material, f32 a3) {
    if (!actor || !actor->getModel())
        return;

    Unk_710260af28::instance()->sub_7100F1E794(actor->getModel(), f32(material), a3);
    sub_71005DCC34(actor, material, a3);
}

// 0x71005dfae0
void sub_71005DFAE0(ksys::act::BaseProcHandle* handle, ksys::act::Actor* actor,
                    const sead::Vector3f* pos, const sead::Matrix33f* rot,
                    const sead::Vector3f* vel, const sead::Vector3f* ang_vel) {
    if (auto* target = sead::DynamicCast<ksys::act::Actor>(handle->getProc())) {
        target->sub_71011C7020(pos, rot, nullptr);
        target->setVelocity(vel, ang_vel);
        target->sub_71011C8BA4(2);
        if (auto* obj = target->m100())
            obj->sub_7100E502EC(actor);
    }
    handle->releaseAndWakeProc();
}

// NON_MATCHING: vector load scheduling and register allocation differ.
bool sub_71005DE53C(uking::act::Weapon* weapon, uking::act::Enemy* enemy, f32 distance,
                   f32 angle, bool check_awareness) {
    if (!weapon || !enemy)
        return false;
    auto* awareness = enemy->getAwareness();
    if (!awareness)
        return false;
    if (check_awareness) {
        Unk_7102451740 filter;
        filter._28.acquire(weapon, false);
        if (distance > 3.0f) {
            auto* sensor = awareness->_260[0];
            if (!sensor || !ksys::act::sub_7100D7EEE8(&sensor->_8, &filter))
                return false;
        }
    } else {
        sead::Vector3f direction = weapon->getMtx().getTranslation() -
                                  enemy->getMtx().getTranslation();
        direction.y = 0.0f;
        direction.normalize();
        if (distance > 3.0f &&
            !(direction.dot(enemy->getMtx().getBase(2)) >= std::cos(angle)))
            return false;
    }
    sead::Vector3f offset = weapon->getMtx().getTranslation() -
                            enemy->getMtx().getTranslation();
    offset.y = 0.0f;
    const f32 horizontal_distance = offset.length();
    if (horizontal_distance > 3.0f &&
        std::atan2(weapon->getMtx()(1, 3) - enemy->getMtx()(1, 3), horizontal_distance) >=
            sead::Mathf::deg2rad(70.0f))
        return false;
    if (weapon->_cf0 == 4 || weapon->hasParentActor())
        return false;
    if (weapon->_d90 && weapon->_d90->m2())
        return false;
    if (weapon->get68f().load())
        return false;
    return enemy->_f54.isOnBit(weapon->_cf0);
}

// NON_MATCHING: vector register allocation, stack slots and mass-condition scheduling differ.
void sub_71005DE398(sead::Vector3f* out, ksys::act::BaseProcLink* link,
                    const sead::Vector3f* target, f32 speed, f32 ratio, f32 mass_limit) {
    if (!out)
        return;
    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::acquireActor(link, &accessor);
    sead::Vector3f direction = *target - accessor.getActorMtx().getTranslation();
    const f32 length = direction.length();
    if (length > 0.0f)
        direction *= speed / length;
    direction -= accessor.getVelocity();
    const f32 mass = accessor.sub_7100D14114();
    f32 blend = ksys::VFR::instance()->getDeltaFrame() * ratio;
    if (mass_limit > 0.0f && mass > 0.0f)
        blend = blend * mass_limit / mass;
    *out = direction * sead::Mathf::min(blend, 1.0f);
}

// 0x71005dff24: clears the stump flag of the old unit and switches the tree trunk materials to
// the new one.
void sub_71005DFF24(ksys::act::Actor* actor, s32 new_index, s32 old_index) {
    auto* model = actor->getModel();
    if (!model)
        return;
    const s32 index = old_index > new_index ? old_index : new_index;
    if (index >= model->getUnits().size())
        return;
    if (actor->getMapObject())
        return;

    if (old_index >= 0) {
        auto* info = model->getUnits()(old_index);
        if (info->mModelUnit)
            info->_1e &= ~0x20;
    }

    if (new_index < 0)
        return;

    auto* info = model->getUnits()(new_index);
    if (info->mModelUnit) {
        auto key = model->searchMaterial("Mt_TreeSection_Trunk");
        if (key.isValid())
            model->getUnits()(key.model_unit_index)->mModelUnit->setMaterialVisible(
                key.material_index, true);
    }

    auto key = model->searchMaterial("Mt_Tree_Stump");
    if (key.isValid())
        model->getUnits()(key.model_unit_index)->mModelUnit->setMaterialVisible(
            key.material_index, false);

    key = model->searchMaterial("Mt_TreeSection_Stump");
    if (key.isValid())
        model->getUnits()(key.model_unit_index)->mModelUnit->setMaterialVisible(
            key.material_index, false);
}

void sub_71005E00C8(ksys::act::Actor* actor) {
    sub_71005DFF24(actor, 0, -1);
}

// NON_MATCHING: the link select is if-converted to csel; the original branches.
// 0x71005d715c: checks the actor's Enemy target link with acc::PlayerOrEnemy::sub_710000975C
// (the weapon check behind sub_71005D70C8).
bool sub_71005D715C(ksys::act::Actor* actor) {
    ksys::act::BaseProcLink* link = &ksys::act::sUnk_71026505e0;
    if (sead::IsDerivedFrom<Enemy>(actor))
        link = &static_cast<Enemy*>(actor)->_c48._8;
    if (!link->hasProc())
        return false;
    ksys::act::acc::PlayerOrEnemy accessor;
    ksys::act::acquireActor(link, &accessor);
    return accessor.sub_710000975C(actor);
}

// 0x71005d7c94: copies the first comma-separated token of `in` to `out`.
bool sub_71005D7C94(sead::BufferedSafeString* out, const sead::SafeString* in) {
    if (!out || in->isEmpty())
        return false;
    const sead::SafeString delimiter(",");
    auto it = in->tokenBegin(delimiter);
    const auto end = in->tokenEnd(delimiter);
    if (it == end)
        return false;
    it.get(out);
    return true;
}

// NON_MATCHING: the a6 / a7 copies to v8 / v9 are scheduled before the integer parameter copies;
// the original interleaves them (v8 after x21, v9 after x24). Same 108 instructions otherwise.
// 0x71005d7f4c: builds the request of type 2 (the caller passes the token, the two range values,
// the flags and the attack direction type hash) and hands it to the equipped weapon.
void sub_71005D7F4C(ksys::act::Actor* actor, int idx, u32 a2, const sead::SafeString* name,
                    const sead::BitFlag8* flags, int a5, f32 a6, f32 a7) {
    sead::FixedSafeString<9> token;
    if (name && !name->isEmpty()) {
        const sead::SafeString delimiter(",");
        auto it = name->tokenBegin(delimiter);
        const auto end = name->tokenEnd(delimiter);
        if (it != end)
            it.get(&token);
    }

    uking::act::Unk_71002edaec arg(2);
    arg._4 = a2;
    arg._8 = a6;
    arg._c = a7;
    arg._10 = sub_71007A3A8C(&token);
    arg._18 = a5;
    if (flags)
        arg._14 = flags->getDirect();
    sub_71005D79AC(actor, idx, arg);
}

// NON_MATCHING: the a9 / a10 copies to v8 / v9 are scheduled before the integer parameter copies;
// the original interleaves them (v8 after x21, v9 after x26). Same 110 instructions otherwise.
// 0x71005d7adc: the type 0 request (a name picked by a query) for the equipped weapon.
void sub_71005D7ADC(ksys::act::Actor* actor, int idx, u32 a2, const sead::SafeString* name,
                    const sead::BitFlag8* flags, int a5, int a6, int a7, int a8, f32 a9, f32 a10) {
    sead::FixedSafeString<9> token;
    if (name && !name->isEmpty()) {
        const sead::SafeString delimiter(",");
        auto it = name->tokenBegin(delimiter);
        const auto end = name->tokenEnd(delimiter);
        if (it != end)
            it.get(&token);
    }

    uking::act::Unk_71002edaec arg(0);
    arg._4 = a2;
    arg._8 = a9;
    arg._c = a10;
    arg._10 = sub_71007A3A8C(&token);
    arg._18 = a5;
    arg._1c = a6;
    arg._20 = a7;
    arg._24 = a8;
    if (flags)
        arg._14 = flags->getDirect();
    sub_71005D79AC(actor, idx, arg);
}

// NON_MATCHING: same float copy scheduling as sub_71005D7ADC. Same 111 instructions otherwise.
// 0x71005d7d90: the same type 0 request with the trailing "keep the token" flag set.
void sub_71005D7D90(ksys::act::Actor* actor, int idx, u32 a2, const sead::SafeString* name,
                    const sead::BitFlag8* flags, int a5, int a6, int a7, int a8, f32 a9, f32 a10) {
    sead::FixedSafeString<9> token;
    if (name && !name->isEmpty()) {
        const sead::SafeString delimiter(",");
        auto it = name->tokenBegin(delimiter);
        const auto end = name->tokenEnd(delimiter);
        if (it != end)
            it.get(&token);
    }

    uking::act::Unk_71002edaec arg(0);
    arg._4 = a2;
    arg._8 = a9;
    arg._c = a10;
    arg._10 = sub_71007A3A8C(&token);
    arg._18 = a5;
    arg._1c = a6;
    arg._20 = a7;
    arg._24 = a8;
    arg._28 = true;
    if (flags)
        arg._14 = flags->getDirect();
    sub_71005D79AC(actor, idx, arg);
}

// 0x71005d8a30: hands `weapon` to the PlayerOrEnemy or NPC (their m164 / m148).
bool sub_71005D8A30(ksys::act::Actor* actor, uking::act::Weapon* weapon, s32 a3) {
    if (sead::IsDerivedFrom<ksys::act::PlayerOrEnemy>(actor))
        return static_cast<ksys::act::PlayerOrEnemy*>(actor)->m164(a3, weapon, false, false);
    if (sead::IsDerivedFrom<NPC>(actor))
        return static_cast<NPC*>(actor)->m148(a3, weapon, false, false);
    return false;
}

// 0x71005db96c: index of the actor's first shield (weapon type 4), or -1; 0 without weapons.
s32 sub_71005DB96C(ksys::act::Actor* actor) {
    auto* weapons = actor->getWeapons();
    if (!weapons)
        return 0;
    for (s32 i = 0; i < 6; ++i) {
        ksys::act::ActorLinkConstDataAccess accessor;
        if (weapons->mWeapons[i].link.hasProc())
            ksys::act::acquireActor(&weapons->mWeapons[i].link, &accessor);
        if (sub_71002F0258(accessor) == 4)
            return i;
    }
    return -1;
}

// 0x71005dbf28: sets the entity motion flag 8 of `body` and stores the PhysicsUserTag state.
void sub_71005DBF28(ksys::phys::RigidBody* body, s32 a1, s32 a2, bool a3, bool a4, bool a5,
                    bool a6) {
    body->setEntityMotionFlag8(true);
    auto* tag = body->getUserTag();
    if (sead::IsDerivedFrom<ksys::act::PhysicsUserTag>(tag))
        static_cast<ksys::act::PhysicsUserTag*>(tag)->setStateMaybe(a1, a2, a3, a4, a5, a6);
}

// 0x71005dbc94: the PhysicsUserTag counterpart of sub_71005DC02C with entity motion flag 8 set.
void sub_71005DBC94(ksys::act::Actor* actor, s32 a1, s32 a2, bool a3, bool a4, bool a5,
                    bool a6) {
    if (!sead::IsDerivedFrom<ksys::act::PhysicsUserTag>(&actor->mPhysicsUserTag))
        return;

    if (auto* controller = actor->getCharacterController())
        controller->sub_7100F62D3C(true);

    if (auto* bodies = actor->getRigidBodyByName(ksys::act::getStr_Body().cstr())) {
        const s32 last = bodies->getRigidBodies().size() - 1;
        for (s32 i = 0; i <= last; ++i)
            bodies->getRigidBody(i)->setEntityMotionFlag8(true);
    }

    actor->mPhysicsUserTag.setStateMaybe(a1, a2, a3, a4, a5, a6);
}

struct DungeonRotateMarkerInfo {
    s32 part_type;
    f32 angle;
    sead::Vector3f pos;
};

// NON_MATCHING: the original has an extra (unused) x28 save and x29-relative frame addresses.
// 0x71005dde8c: passes the current remains rotation (home matrix relative to the field-body
// transform) and its position to the dungeon-rotate UI.
void sub_71005DDE8C(ksys::act::Actor* actor, const sead::Vector3f* axis, s32 part_type) {
    f32 angle = 0.0f;
    const sead::Vector3f pos = actor->getHomeMtxRaw().getTranslation();
    sead::Matrix34f home;
    actor->getHomeMtx(&home);
    sead::Matrix34f from;
    from = actor->getHomeMtxRaw();
    if (axis) {
        sead::Vector3f out_axis;
        ksys::util::sub_71011EF78C(&out_axis, &angle, from, home, *axis);
        if (axis->dot(out_axis) < 0.0f)
            angle = -angle;
    }
    DungeonRotateMarkerInfo info;
    info.part_type = part_type;
    info.angle = angle;
    info.pos = pos;
    uking::ui::sub_7100A9D0B4(&info);
}

// 0x71005dfbe4: whether an attack from behind is possible on the enemy's target: the target must
// face away (within `angle`) and be within `dist`.
bool sub_71005DFBE4(ksys::act::Actor* actor, f32 dist, f32 angle) {
    if (!actor)
        return false;

    const auto* level = actor->getParam()->getRes().mGParamList->getEnemyLevel();
    if (!level || !*level->mIsBackSwiftAttack)
        return false;

    sead::Vector3f to_target = sub_71005D9330(actor);
    to_target -= actor->getMtx().getTranslation();
    to_target.y = 0.0f;
    if (to_target.normalize() > dist)
        return false;

    const sead::Matrix34f& mtx = sub_71005D96A8(actor);
    sead::Vector3f forward;
    mtx.getBase(forward, 2);
    forward.y = 0.0f;
    forward.normalize();

    // NON_MATCHING: same operations; the original's flattened y is -0.0f, so its final dot has
    // `fmul` where ours has `fnmul`, and it keeps &_c48 in an extra register (0x10 larger frame)
    return forward.dot(-to_target) <= sead::Mathf::cos(angle);
}

// 0x71005dfe40: hides the tree trunk and stump section materials.
void sub_71005DFE40(ksys::act::Actor* actor) {
    auto* model = actor->getModel();
    if (!model)
        return;

    auto key = model->searchMaterial("Mt_TreeSection_Trunk");
    if (key.isValid())
        model->getUnits().unsafeAt(key.model_unit_index)->mModelUnit->setMaterialVisible(
            key.material_index, false);

    key = model->searchMaterial("Mt_TreeSection_Stump");
    if (key.isValid())
        model->getUnits().unsafeAt(key.model_unit_index)->mModelUnit->setMaterialVisible(
            key.material_index, false);
}

// 0x71005e00d4: hides every material and shows only the tree stump.
void sub_71005E00D4(ksys::act::Actor* actor) {
    auto* model = actor->getModel();
    if (!model)
        return;

    auto key = model->searchMaterial("Mt_Tree_Stump");
    if (key.isValid()) {
        model->setMaterialVisibleAll(false);
        model->getUnits().unsafeAt(key.model_unit_index)->mModelUnit->setMaterialVisible(
            key.material_index, true);
    }

    key = model->searchMaterial("Mt_TreeSection_Stump");
    if (key.isValid())
        model->getUnits().unsafeAt(key.model_unit_index)->mModelUnit->setMaterialVisible(
            key.material_index, true);
}

// 0x71005e0648: sweeps a ground ray from one unit along `direction` out to `max_distance`; returns
// true when nothing blocks the sweep, else writes the hit distance to `out_distance`.
// NON_MATCHING: the three fmul of the direction have their operands swapped (commutative).
bool sub_71005E0648(sead::Matrix34f mtx, f32* out_distance, f32 dx, f32 dy, f32 dz,
                    f32 max_distance) {
    ksys::phys::RayCastBodyQuery query(nullptr, ksys::phys::GroundHit::HitAll);
    ksys::act::sub_7100EEACE8(&query);
    if (!(max_distance > 1.0f))
        return true;

    f32 distance = 1.0f;
    do {
        sead::Vector3f start =
            mtx.getTranslation() + sead::Vector3f(dx, dy, dz) * distance;
        start.y += 5.0f;
        sead::Vector3f end = start;
        end.y += -50.0f;
        query.setStartAndEnd(start, end);
        if (query.worldRayCast(ksys::phys::ContactLayerType::Entity) &&
            !sub_71006F1E70(query.getMaterialMask())) {
            if (out_distance)
                *out_distance = distance;
            return false;
        }
        distance += 1.0f;
    } while (distance < max_distance);
    return true;
}

// 0x71005e0514: sweeps the matrix's z basis vector, rotated by `angle` around the Y axis, and
// reports the first blocked distance up to `max_distance`.
// NON_MATCHING: the rotation's sin/cos temporaries take the other s registers and the z term is
// scheduled after the subtract; same operations.
bool sub_71005E0514(const sead::Matrix34f* mtx, f32* out_distance, f32 angle, f32 max_distance) {
    const sead::Vector3f base = mtx->getBase(2);
    sead::Matrix33f rot;
    rot.makeR(sead::Vector3f(0.0f, angle, 0.0f));
    sead::Vector3f dir;
    dir.setRotated(rot, base);
    dir.normalize();
    return sub_71005E0648(*mtx, out_distance, dir.x, dir.y, dir.z, max_distance);
}

// NON_MATCHING: the clear flag lives in w20 (target w19) and the two false returns carry
// their own zero moves; same operations.
// 0x71005d91a0: whether the fall path below the Enemy is clear up to `value` (a ground ray cast
// from the actor's depth below its home position).
bool sub_71005D91A0(ksys::act::Actor* actor, f32 value) {
    if (!sead::IsDerivedFrom<Enemy>(actor))
        return false;
    auto* enemy = static_cast<Enemy*>(actor);
    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::acquireActor(&enemy->_c48._8, &accessor);
    const f32 depth = accessor.sub_7100D110E4();
    bool clear = false;
    if (depth <= 0.0f)
        return clear;
    sead::Vector3f start;
    accessor.getActorMtx().getTranslation(start);
    start.y += depth + 0.1f;
    sead::Vector3f end = start;
    end.y -= value + 0.1f;
    ksys::phys::RayCastBodyQuery query(nullptr, ksys::phys::GroundHit::HitAll);
    query.setStartAndEnd(start, end);
    query.enableLayer(ksys::phys::ContactLayer::EntityGround);
    query.enableLayer(ksys::phys::ContactLayer::EntityGroundObject);
    query.enableLayer(ksys::phys::ContactLayer::EntityGroundRough);
    query.enableLayer(ksys::phys::ContactLayer::EntityGroundSmooth);
    clear = !query.worldRayCast(ksys::phys::ContactLayerType::Entity);
    return clear;
}

// 0x71005dcf80: the terrain texture along `dir` from the actor (a short ray cast through the
// actor's position).
bool sub_71005DCF80(u32* material, ksys::act::Actor* actor, const sead::Vector3f& dir, bool unused) {
    if (!actor || !actor->getModel())
        return false;

    sead::Vector3f pos;
    actor->getMtx().getTranslation(pos);
    ksys::phys::RayCastBodyQuery query(nullptr, ksys::phys::GroundHit::HitAll);
    sead::Vector3f direction = dir;
    direction.normalize();
    const sead::Vector3f start = pos - direction;
    const sead::Vector3f end = pos + direction;
    query.setStartAndDisplacement(start, end);
    query.enableLayer(ksys::phys::ContactLayer::EntityGround);
    query.enableLayer(ksys::phys::ContactLayer::EntityGroundRough);
    query.enableLayer(ksys::phys::ContactLayer::EntityGroundObject);
    query.set99(true);
    if (!query.worldRayCast(ksys::phys::ContactLayerType::Entity))
        return false;

    sead::Vector3f hit_pos;
    query.getHitPosition(&hit_pos);
    if (sub_710072C388(material, &hit_pos, 1.0f))
        return true;

    const ksys::phys::MaterialMask mask = query.getMaterialMask();
    if (auto* object = query.getHitMapObject()) {
        ksys::act::InfoData::TerrainTextures textures;
        const s32 count = ksys::act::InfoData::instance()->getTerrainTextures(
            object->getUnitConfigName(), textures);
        for (s32 i = 0; i < count; ++i) {
            const u8 texture = textures.textures[i];
            s32 a, b;
            ksys::tera::sub_710110C134(&a, &b, texture);
            if ((mask.getRawData() & 0x3f) == static_cast<u32>(a)) {
                ksys::tera::sub_710110C1A4(material, texture);
                return true;
            }
        }
    }
    return false;
}

// NON_MATCHING: the u64 argument is built in a register (target stores its two fields separately).
// 0x71005dcc34: forwards a mimicry material request (material index and value) to every weapon.
void sub_71005DCC34(ksys::act::Actor* actor, u32 material, f32 a3) {
    auto* weapons = actor->getWeapons();
    if (!weapons)
        return;

    const u64 value = u64(material) | (u64(sead::BitUtil::bitCast<u32>(a3)) << 32);
    for (s32 i = 0; i < 6; ++i) {
        auto* proc = weapons->mWeapons[i].link.getProc(nullptr, nullptr);
        auto* weapon_base = sead::DynamicCast<ksys::act::WeaponBase>(proc);
        if (sead::IsDerivedFrom<uking::act::Weapon>(weapon_base))
            static_cast<uking::act::Weapon*>(weapon_base)->sub_71002EDB84(value);
    }
}

// 0x71005dd7e4: copies the second comma-separated token of `name` to `out`.
bool sub_71005DD7E4(sead::BufferedSafeString* out, const sead::SafeString& name) {
    if (!out || name.isEmpty())
        return false;
    const sead::SafeString delimiter(",");
    auto it = name.tokenBegin(delimiter);
    const auto end = name.tokenEnd(delimiter);
    if (end != it) {
        ++it;
        if (end != it) {
            it.get(out);
            return true;
        }
    }
    return false;
}

// 0x71005ddc98: stops the rotation sound and requests the matching camera rumble.
void sub_71005DDC98(ksys::act::Actor* actor, s32 pattern, f32 power, f32 range, bool start,
                    ksys::map::Object* object) {
    if (auto* proxy = ksys::snd::SoundMgr::instance()->_a0->sub_710105A830(object)) {
        xlink2::HandleSLink handle;
        if (start)
            proxy->sub_710105A10C("StopCW", &handle);
        else
            proxy->sub_710105A10C("StopCCW", &handle);
        if (!handle.isActive())
            proxy->sub_710105A10C("Stop", &handle);
    } else {
        xlink2::HandleSLink handle;
        if (start)
            ksys::eft::sub_710105DDB8(actor, "StopCW", &handle);
        else
            ksys::eft::sub_710105DDB8(actor, "StopCCW", &handle);
        if (!handle.isActive())
            ksys::eft::sub_710105DDB8(actor, "Stop", &handle);
    }

    ksys::Vibration::Unk2 request;
    request._20 = pattern;
    request._18 = power;
    request._1c = range;
    sead::Vector3f pos;
    actor->getHomePos(&pos);
    sead::Matrix34f mtx = sead::Matrix34f::ident;
    mtx.setTranslation(pos);
    if (auto* mgr = ksys::phys::System::instance()->getStaticCompoundMgr())
        mtx = mgr->getTransformedMatrix(actor->getFieldBodyGroup(), mtx);
    mtx.getTranslation(pos);
    request._0 = pos;
    ksys::Vibration::instance()->sub_71010BB428(request);
}

// 0x71005dd3a8: forwards a mimicry material request to every weapon and its optional weapon.
void sub_71005DD3A8(ksys::act::Actor* actor, f32 value, bool use_parent) {
    if (!actor)
        return;
    auto* weapons = actor->getWeapons();
    if (!weapons)
        return;

    uking::act::Unk_71002edc14 request;
    request._0 = sead::BitUtil::bitCast<u32>(value);
    request._4 = use_parent;
    for (s32 i = 0; i < 6; ++i) {
        auto* proc = weapons->mWeapons[i].link.getProc(nullptr, nullptr);
        auto* weapon_base = sead::DynamicCast<ksys::act::WeaponBase>(proc);
        if (!sead::IsDerivedFrom<uking::act::Weapon>(weapon_base))
            continue;
        auto* weapon = static_cast<uking::act::Weapon*>(weapon_base);
        weapon->sub_71002EDC14(request);
        auto* optional = weapon->m162();
        if (sead::IsDerivedFrom<uking::act::OptionalWeapon>(optional))
            static_cast<uking::act::OptionalWeapon*>(optional)->sub_7100EF2290(value, use_parent);
    }
}

// NON_MATCHING: one fmul is scheduled before the other (x*x / z*z); same operations.
// 0x71005df4e4: ballistic launch velocity for `angle` and `speed` from the horizontal
// distance in `pos`; false when the trajectory is not reachable.
bool sub_71005DF4E4(sead::Vector3f* out, const sead::Vector3f* pos, const sead::Vector3f* p,
                    f32 angle, f32 speed) {
    const f32 len = std::sqrt(pos->x * pos->x + pos->z * pos->z);
    const f32 height = pos->y;
    const f32 tan_angle = std::tan(angle);
    const f32 denom = (height - len * tan_angle) / (tan_angle * tan_angle + 1.0f);
    const f32 h = p->y * len * len / (denom + denom);
    if (h >= 0.0f) {
        const f32 velocity = std::sqrt(h);
        speed = sead::Mathf::clampMax(velocity / 30.0f, speed);
        sead::Vector3f dir(pos->x, 0.0f, pos->z);
        dir.normalize();
        *out = (dir * std::cos(angle) + sead::Vector3f::ey * std::sin(angle)) * speed;
        return true;
    }
    return false;
}

// 0x71005e1484: movement speed scale for the actor's horizontal velocity against the ground
// ahead (1.0 on a hit, 0.4 or a ratio depending on the reachable distance).
f32 sub_71005E1484(ksys::act::Actor* actor) {
    f32 speed = 1.0f;
    const sead::Vector3f velocity = actor->getVelocity();
    sead::Vector3f dir = velocity;
    dir.y = 0.0f;
    const f32 len = dir.normalize();
    if (len > 0.0f) {
        if (dir.x != 0.0f || dir.y != 0.0f || dir.z != 0.0f) {
            const f32 distance = len * ksys::VFR::instance()->getDeltaFrame();
            sead::Vector3f pos;
            actor->getMtx().getTranslation(pos);
            sead::Vector3f hit;
            if (!sub_710072FD0C(actor, pos, dir, &hit, -1, distance + distance, -1.0f, -1.0f,
                                -1.0f)) {
                sead::Vector3f delta = hit - pos;
                delta.y = 0.0f;
                f32 reach = delta.dot(dir);
                if (reach < 0.0f)
                    reach = 0.0f;
                if (!(reach < distance))
                    speed = 0.4f;
                else
                    speed = reach * 0.7f / distance;
            }
        }
    }
    return speed;
}

// 0x71005e0904: whether one of the sensed actors of the Enemy is above it by `value`.
bool sub_71005E0904(ksys::act::Actor* actor, f32 value) {
    if (!sub_71007A4178(actor, false))
        return false;
    if (!sead::IsDerivedFrom<Enemy>(actor))
        return false;
    auto* enemy = static_cast<Enemy*>(actor);
    const s32 count = sub_71007A425C(actor);
    if (count < 1)
        return false;

    f32 min = std::numeric_limits<f32>::infinity();
    bool found = false;
    for (s32 i = 0; i < count; ++i) {
        auto* entry = sub_71007A40D0(actor, i);
        if (!entry)
            continue;
        if (entry->_50 != enemy->_c48._8)
            continue;
        if (!(entry->_c.dot(sead::Vector3f::ey) < 0.0f))
            continue;
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&entry->_50, &accessor);
        min = sead::Mathf::min(accessor.getActorMtx().m[1][3], min);
        found = true;
    }
    if (found) {
        if (min - actor->getMtx().m[1][3] >= value)
            return true;
    }
    return false;
}

// 0x71005e2540: eases the controller's direction toward the target velocity and passes the
// resulting speed to the controller.
// NON_MATCHING: the original copies the velocity into callee-saved registers; ours round-trips the
// copy through the local's stack slot (two extra load/store pairs).
void sub_71005E2540(ksys::phys::CharacterController* controller, ksys::act::Actor* actor,
                    const sead::Vector3f& target_velocity, f32 acc_ratio) {
    sead::Vector3f dir = actor->getVelocity();
    ksys::VFR::lerp(&dir, target_velocity, acc_ratio);
    const f32 speed = dir.normalize();
    sub_710072C1B4(controller, dir);
    sub_7100737708(controller, speed);
}

// 0x71005e2684: resolves the named physics body (entity sensor first, then plain body) among the
// actor's bodies and passes it to the contact-event helper.
bool sub_71005E2684(ksys::act::Actor* actor, const sead::SafeString& body_name,
                    const sead::SafeString& event_name, sead::Vector3f* position,
                    sead::Vector3f* normal) {
    if (body_name.isEmpty())
        return false;

    ksys::phys::RigidBody* body =
        actor->findPhysicsBodyByName(sub_71007A250C()->cstr(), body_name.cstr());
    if (!body)
        body = actor->findPhysicsBodyByName(sub_71007A24E4()->cstr(), body_name.cstr());
    if (!body)
        return false;
    return sub_71005E2788(actor, body, event_name, position, normal);
}

bool Unk_71005e1be8::sub_71005E1BE8(ksys::act::ai::ActionBase* action, int idx) {
    sead::FixedStringBuilder<64> name;
    const int n = idx + 1;
    name.format("EntitySensorName%d", n);
    action->getStaticParam(&_20, name);
    name.format("PartsKey%d", n);
    action->getStaticParam(&_0, name);
    name.format("RigidBodyName%d", n);
    action->getStaticParam(&_10, name);
    name.format("ModelMatrialName%d", n);
    action->getStaticParam(&_30, name);
    return false;
}

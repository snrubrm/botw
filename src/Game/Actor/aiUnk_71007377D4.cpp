#include <limits>
#include "Game/Actor/aiUnk_710001A69C.h"
#include "KingSystem/ActorSystem/actTag.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "Game/Actor/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActorChemicals.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/Chemical/chmSystemConfig.h"
#include "Game/gameUnk_71024739d0.h"
#include "Game/gameSceneSubsys12.h"
#include "Game/Actor/actDragon.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/actWeapon.h"
#include "Game/Actor/actNPC.h"
#include "Game/Actor/actWolfLink.h"
#include "Game/gameSceneSubsys14.h"
#include "KingSystem/Map/mapPlacementActors.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/GameData/gdtManager.h"
#include "Game/AOC/aocHardModeManager.h"
#include "Game/Actor/actUnk_71025ae680.h"
#include "Game/Actor/actHorseRideInfo.h"
#include "KingSystem/ActorSystem/actDropData.h"
#include "KingSystem/ActorSystem/actDropMgr.h"
#include "KingSystem/ActorSystem/actActorWeapons.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/XLink/xlinkInfoData.h"
#include "KingSystem/ActorSystem/actInfoData.h"
#include "KingSystem/ActorSystem/actReaction.h"

#include "KingSystem/Map/mapPlacementMgr.h"
#include "KingSystem/Terrain/teraSystem.h"
#include "KingSystem/ActorSystem/actAttackSensor.h"
#include "KingSystem/ActorSystem/aiRootAi.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "Game/Actor/Player/actPlayerBase.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Physics/System/physContactPointInfo.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include "KingSystem/ActorSystem/actBoneControl.h"
#include "KingSystem/Physics/System/physHavokAI.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"
#include "KingSystem/Physics/System/physRayCastForRequest.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actInfoData.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include "KingSystem/Resource/Actor/resResourceDamageParam.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectGiantArmorSlot.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectNpcEquipment.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectItem.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectSmallSword.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectLargeSword.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectSpear.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectBow.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectShield.h"
#include <math/seadMathCalcCommon.h>

void sub_710072C1B4(ksys::phys::CharacterController* controller, const sead::Vector3f& up) {
    ksys::act::sub_7100EE60AC(controller, up);
}

f32 sub_710073768C(ksys::act::Actor* actor, ksys::act::BaseProcLink* link) {
    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::acquireActor(link, &accessor);
    const f32 ratio = actor->getParam()->getRes().mDamageParam->mSpAffectRatio.ref();
    return ratio * accessor.getAttackSpHitRatio();
}

s32 sub_71007376F8(ksys::act::Actor* actor, ksys::act::BaseProcLink*) {
    return actor->getParam()->getRes().mDamageParam->mSpAffectDamage.ref();
}

const s32& sub_7100730FD0(const ksys::act::ActorLinkConstDataAccess* accessor) {
    return accessor->getGParamList()->getItem()->mBuyingPrice.ref();
}

void sub_7100734228(ksys::act::Actor* actor) {
    if (auto* info = sub_71007A255C(actor, 0))
        sub_7100733E24(actor, info->_a0, info->_0, info);
}

const sead::SafeString& sub_710072D96C(ksys::act::Actor* actor) {
    if (auto* weapon = sead::DynamicCast<uking::act::Weapon>(actor)) {
        switch (weapon->_cf0) {
        case 0:
            return weapon->getParam()->getRes().mGParamList->getSmallSword()->mWeaponSubType.ref();
        case 1:
            return weapon->getParam()->getRes().mGParamList->getLargeSword()->mWeaponSubType.ref();
        case 2:
            return weapon->getParam()->getRes().mGParamList->getSpear()->mWeaponSubType.ref();
        case 3:
            return weapon->getParam()->getRes().mGParamList->getBow()->mWeaponSubType.ref();
        case 4:
            return weapon->getParam()->getRes().mGParamList->getShield()->mWeaponSubType.ref();
        default:
            break;
        }
    }
    return sead::SafeString::cEmptyString;
}

ksys::act::Unk_DynamicActorA58* sub_710073DC28(ksys::act::Actor* actor) {
    if (auto* dynamic_actor = sead::DynamicCast<ksys::act::DynamicActor>(actor))
        return dynamic_actor->_a58;
    return nullptr;
}

bool sub_710073DB94(const char* name, ksys::act::BaseProcHandle* handle,
                    ksys::act::InstParamPack* params, sead::Heap* heap) {
    if (handle->isAllocatedOrFailed()) {
        if (handle->isProcReady())
            return true;
        if (!handle->hasProcCreationFailed())
            return false;
        handle->deleteProcIfFailed();
    }
    ksys::act::ActorCreator::instance()->requestCreateActor(name, heap, handle, params, nullptr, 1);
    return false;
}

bool sub_710073CD5C(const char* name, sead::Heap* heap) {
    const char* profile;
    ksys::act::InfoData::instance()->getActorProfile(&profile, name);
    if (sead::SafeString(profile).findIndex("Weapon") != -1)
        return false;
    if (auto* subsystem = GameSceneSubsys12::instance()) {
        subsystem->sub_7100662B58(name, heap);
        return true;
    }
    return false;
}

bool sub_710072EC24(ksys::phys::RayCastForRequest* cast, const sead::Vector3f& start,
                    const sead::Vector3f& end, ksys::phys::RayCast::NormalCheckingMode mode, f32) {
    if (cast->isRequestQueued())
        return false;
    cast->setStartAndEnd(start, end);
    ksys::act::sub_7100EEACE8(cast);
    cast->setNormalCheckingMode(mode);
    cast->submitRequest(ksys::phys::ContactLayerType::Entity);
    return true;
}

void sub_7100737708(ksys::phys::CharacterController* controller, f32 value) {
    ksys::act::sub_7100EE60A0(controller, value);
}

void sub_710073770C(ksys::phys::CharacterController* controller, f32 value, const sead::Vector3f& up) {
    ksys::act::sub_7100EE61B4(controller, value, up);
}

void sub_7100737710(ksys::phys::CharacterController* controller, const sead::Vector3f& vel) {
    ksys::act::sub_7100EE61E8(controller, vel);
}

void sub_7100737714(ksys::phys::CharacterController* controller, const sead::Vector3f& ang_vel) {
    ksys::act::sub_7100EE6228(controller, ang_vel);
}

void sub_7100738DC8(ksys::act::Actor* actor) {
    if (auto* physics = actor->getPhysics())
        physics->sub_7100FBDFA4(physics->get178(0));
}

void sub_7100737718(ksys::phys::RigidBody* body, const sead::Vector3f& vel) {
    ksys::act::sub_7100EE6268(body, vel);
}

void sub_710073771C(ksys::phys::RigidBody* body, const sead::Vector3f& ang_vel) {
    ksys::act::sub_7100EE62B0(body, ang_vel);
}

bool sub_710072E0A0(ksys::act::Actor* actor, const sead::Vector3f& target,
                    const sead::Matrix34f& mtx, f32 max_dist, f32 min_dy, f32 max_dy, f32 angle,
                    f32 angle_check_dist, f32 y_offset) {
    if (!actor)
        return false;
    if (!inlineIsTargetInReach(target, max_dist, min_dy, max_dy, mtx, angle, angle_check_dist,
                               y_offset)) {
        return false;
    }
    return sub_710072E154(actor, target, nullptr, -1);
}

bool sub_710072DCFC(const sead::Vector3f& target, const sead::Vector3f& pos,
                    const sead::Vector3f& dir, f32 angle) {
    sead::Vector3f to_target = target;
    to_target -= pos;
    to_target.y = 0;
    to_target.normalize();
    return to_target.dot(dir) >= sead::Mathf::cos(angle);
}

bool sub_710072E154(ksys::act::Actor* actor, const sead::Vector3f& target, sead::Vector3f* out_pos,
                    s32 a4) {
    const sead::Vector3f from{std::numeric_limits<f32>::quiet_NaN(), std::numeric_limits<f32>::quiet_NaN(), std::numeric_limits<f32>::quiet_NaN()};
    return sub_710072F28C(actor, from, target, nullptr, out_pos, a4, true, -1.0f, -1.0f, -1.0f);
}

void sub_7100738428(ksys::act::Actor* actor, f32 ratio) {
    if (auto* controller = actor->getCharacterController())
        sub_71007377D4(controller, ratio);
    else if (auto* body = actor->getMainBody())
        sub_71007379FC(body, ratio);
}

// The `dir` parameter is not used (the original always passes the negated Y axis).
void sub_7100738488(ksys::act::Actor* actor, f32 ratio, const sead::Vector3f& dir) {
    if (auto* controller = actor->getCharacterController()) {
        const sead::Vector3f down = -sead::Vector3f::ey;
        sub_7100737C0C(controller, ratio, down);
    } else if (auto* body = actor->getMainBody()) {
        const sead::Vector3f down = -sead::Vector3f::ey;
        sub_7100738084(body, ratio, down);
    }
}

// NON_MATCHING: the original computes the zero-direction test into a bool before the distance compare,
// copies the result vectors as 8 + 4 bytes and tests NaN as `< 0x7f800001`; same logic.
bool sub_710072EDFC(ksys::act::Actor* actor, const sead::Vector3f& from, const sead::Vector3f& dir,
                    sead::Vector3f* out_normal, sead::Vector3f* out_pos, s32 a5, bool a6, f32 distance,
                    f32 radius, f32 a9, f32 tolerance) {
    if ((dir.x == 0.0f && dir.y == 0.0f && dir.z == 0.0f) || distance <= radius) {
        if (out_normal)
            *out_normal = {0.0f, 0.0f, 0.0f};
        if (out_pos) {
            if (!from.isNan())
                *out_pos = from;
            else
                actor->getMtx().getTranslation(*out_pos);
        }
        return true;
    }

    auto* nav = actor->m45();
    if (!nav) {
        if (out_normal)
            *out_normal = {0.0f, 0.0f, 0.0f};
        if (out_pos) {
            if (!from.isNan())
                *out_pos = from;
            else
                actor->getMtx().getTranslation(*out_pos);
        }
        return false;
    }

    ksys::phys::HavokAI::Unk1 result;
    ksys::phys::HavokAI::Unk2 query;
    query.from = from;
    query._30 = a5;
    if (radius > 0.0f)
        query.radius = radius;
    if (tolerance >= 0.0f)
        query.tolerance = tolerance;
    sead::Vector3f pos = from;
    if (pos.isNan())
        actor->getMtx().getTranslation(pos);
    query.dir = dir;
    query.distance = distance;

    auto* havok_ai = nav->_18 ? nav->_18 : ksys::phys::HavokAI::instance();
    const bool hit = havok_ai->sub_7100F86324(nav, query, &result);
    const sead::Vector3f point = !result._24.isNan() ? result._24 : pos;

    bool reached = hit;
    if (radius > 0.0f && !hit) {
        sead::Vector3f flat_dir{dir.x, 0.0f, dir.z};
        flat_dir.normalize();
        const sead::Vector3f end = flat_dir * distance + pos;
        const f32 dx = result._c.x - end.x;
        const f32 dz = result._c.z - end.z;
        reached = !(dx * dx + dz * dz > radius * radius);
    }

    if (out_normal)
        *out_normal = point;
    if (out_pos) {
        if (hit || !result._c.isNan())
            *out_pos = result._c;
        else
            *out_pos = pos;
    }
    return reached;
}

bool sub_710072F788(ksys::act::Actor* actor, const sead::Vector3f& from, const sead::Vector3f& to,
                    sead::Vector3f* out_pos) {
    return sub_710072F28C(actor, from, to, nullptr, out_pos, -1, true, -1.0f, -1.0f, -1.0f);
}

bool sub_710072CB78(ksys::act::Actor* actor, const sead::Vector3f& target, sead::Vector3f* out_pos,
                    f32 a3, s32 a4) {
    const sead::Vector3f from{std::numeric_limits<f32>::quiet_NaN(), std::numeric_limits<f32>::quiet_NaN(), std::numeric_limits<f32>::quiet_NaN()};
    return sub_710072F28C(actor, from, target, nullptr, out_pos, a4, true, a3, -1.0f, -1.0f);
}

bool sub_710072E304(const sead::Vector3f& to, f32 a3) {
    if (auto* ai = ksys::phys::HavokAI::instance()) {
        sead::Vector3f out;
        return ai->sub_7100F87ED0(&out, to, a3).sub_7100F7EB40();
    }
    return false;
}

bool sub_710072F854(ksys::act::Actor* actor, const sead::Vector3f& from, const sead::Vector3f& to,
                    sead::Vector3f* out_pos, f32 extra, s32 a5) {
    auto* nav = actor->m45();
    const f32 tolerance = nav ? nav->getRadiusMaybe() + extra : extra;
    return sub_710072F28C(actor, from, to, nullptr, out_pos, a5, true, tolerance, -1.0f, -1.0f);
}

bool sub_710072F944(ksys::act::Actor* actor, const sead::Vector3f& target, sead::Vector3f* out_pos,
                    f32 a3, f32 a4) {
    const sead::Vector3f from = actor->getMtx().getTranslation();
    return sub_710072F28C(actor, from, target, nullptr, out_pos, -1, true, a3, a4, -1.0f);
}

bool sub_710072F8E4(ksys::act::Actor* actor, const sead::Vector3f& target, sead::Vector3f* out_pos,
                    f32 a3) {
    const sead::Vector3f from = actor->getMtx().getTranslation();
    return sub_710072F28C(actor, from, target, nullptr, out_pos, -1, true, -1.0f, a3, -1.0f);
}

bool sub_710072F7AC(ksys::act::Actor* actor, const sead::Vector3f& from, const sead::Vector3f& to,
                    sead::Vector3f* out_pos, s32 a5, f32 a7) {
    return sub_710072F28C(actor, from, to, nullptr, out_pos, a5, true, a7, -1.0f, -1.0f);
}

bool sub_710072F7D0(ksys::act::Actor* actor, const sead::Vector3f& from, const sead::Vector3f& to,
                    sead::Vector3f* out_pos, s32 a5) {
    auto* nav = actor->m45();
    const f32 tolerance = nav ? nav->_2a8 * nav->_2ac : 0.0f;
    return sub_710072F28C(actor, from, to, nullptr, out_pos, a5, true, tolerance, -1.0f, -1.0f);
}

bool sub_710072F99C(ksys::act::Actor* actor, const sead::Vector3f& from, const sead::Vector3f& to,
                    sead::Vector3f* out_pos, s32 a5, f32 a6, f32 a7) {
    sead::Vector3f dir = to - from;
    const f32 distance = sead::Mathf::sqrt(dir.x * dir.x + dir.z * dir.z);
    dir.normalize();
    return sub_710072EDFC(actor, from, dir, nullptr, out_pos, a5, false, distance, a6, a7, -1.0f);
}

// NON_MATCHING: scheduling (the original moves the `a4` copy after the first fsqrt).
bool sub_710072FAB0(ksys::act::Actor* actor, const sead::Vector3f& target, sead::Vector3f* out_pos,
                    s32 a4, f32 a5, f32 a6) {
    sead::Vector3f dir = target - actor->getMtx().getTranslation();
    const f32 distance = sead::Mathf::sqrt(dir.x * dir.x + dir.z * dir.z);
    dir.normalize();
    const sead::Vector3f from{std::numeric_limits<f32>::quiet_NaN(),
                              std::numeric_limits<f32>::quiet_NaN(),
                              std::numeric_limits<f32>::quiet_NaN()};
    return sub_710072EDFC(actor, from, dir, nullptr, out_pos, a4, false, distance, a5, a6, -1.0f);
}

bool sub_710072FBD4(ksys::act::Actor* actor, const sead::Vector3f& from, const sead::Vector3f& to,
                    sead::Vector3f* out_pos, s32 a5, f32 extra, f32 a7) {
    sead::Vector3f dir = to - from;
    const f32 distance = sead::Mathf::sqrt(dir.x * dir.x + dir.z * dir.z);
    dir.normalize();
    auto* nav = actor->m45();
    const f32 radius = nav ? nav->getRadiusMaybe() + extra : extra;
    return sub_710072EDFC(actor, from, dir, nullptr, out_pos, a5, false, distance, radius, a7, -1.0f);
}

bool sub_710072FD0C(ksys::act::Actor* actor, const sead::Vector3f& from, const sead::Vector3f& to,
                    sead::Vector3f* out_pos, s32 a5, f32 a6, f32 a7, f32 a8, f32 a9) {
    return sub_710072EDFC(actor, from, to, nullptr, out_pos, a5, false, a6, a7, a8, a9);
}

f32 sub_710072FD7C(ksys::act::Actor* actor) {
    if (auto* nav = actor->m45())
        return nav->_2a8 * nav->_2ac;
    return 0.0f;
}

bool sub_710072FD28(ksys::act::Actor* actor, const sead::Vector3f& dir, sead::Vector3f* out_pos,
                    s32 a4, f32 a5, f32 a6, f32 a7, f32 a8) {
    const sead::Vector3f from{std::numeric_limits<f32>::quiet_NaN(),
                              std::numeric_limits<f32>::quiet_NaN(),
                              std::numeric_limits<f32>::quiet_NaN()};
    return sub_710072EDFC(actor, from, dir, nullptr, out_pos, a4, false, a5, a6, a7, a8);
}

bool sub_710072B8E8(ksys::act::Actor* actor) {
    bool result = false;
    if (auto* manager = sead::DynamicCast<uking::act::DamageManager>(actor->getDamageMgr()))
        result = manager->getField54() > 27;
    if (auto* chemicals = actor->getChemicalContainer()) {
        if (chemicals->_58.size() + chemicals->_80 >= 0)
            result |= chemicals->sub_7100E39458();
    }
    if (!(actor->getProfile() == "CapturedActor") || actor->getDropData()) {
        auto* life = actor->getLife();
        result |= life && *life < 1;
    }
    result |= actor->getFadeOutDeleteType() != 0;
    return result;
}

void sub_710072DC9C(ksys::act::Actor* actor, f32 factor) {
    if (auto* controller = actor->getCharacterController())
        controller->sub_7100F5EEB8(factor);
    else if (auto* body = actor->getMainBody())
        body->setGravityFactor(factor);
}

bool sub_710072E1B4(ksys::act::Actor* actor, bool include_3) {
    auto* enemy = sead::DynamicCast<uking::act::Enemy>(actor);
    if (!enemy)
        return false;
    const s32 state = sub_71005D9744(enemy);
    if (!ksys::act::isEnemyProfile(enemy))
        return false;
    return state == 2 || state == 5 || (state == 3 && include_3);
}

bool somePositionCalc(sead::Vector3f* hit_position, const sead::Vector3f& pos,
                      const sead::Vector3f& dir, f32 distance) {
    sead::Vector3f end = pos;
    end += dir * distance;
    return uking::sub_710090DB04(pos, end, hit_position, nullptr, nullptr);
}

bool sub_710072E500(const sead::Vector3f& from, const sead::Vector3f& to, sead::Vector3f* hit_pos,
                    sead::Vector3f* hit_normal, ksys::phys::MaterialMask* material_mask, f32 y_offset) {
    sead::Vector3f start = from;
    sead::Vector3f end = to;
    start.y += y_offset;
    end.y += y_offset;

    ksys::phys::RayCastBodyQuery query(nullptr, ksys::phys::GroundHit::HitAll);
    ksys::act::sub_7100EEACE8(&query);
    ksys::act::sub_7100EEAF28(&query);
    query.setStartAndEnd(start, end);
    if (!query.worldRayCast(ksys::phys::ContactLayerType::Entity))
        return false;

    if (hit_pos)
        query.getHitPosition(hit_pos);
    if (hit_normal)
        query.getHitNormal(hit_normal);
    if (material_mask)
        *material_mask = query.getMaterialMask();
    return true;
}

bool sub_710072E5F8(const sead::Vector3f& from, const sead::Vector3f& to, int normal_checking_mode,
                    sead::Vector3f* hit_pos, sead::Vector3f* hit_normal,
                    ksys::phys::MaterialMask* material_mask, f32 y_offset) {
    sead::Vector3f start = from;
    sead::Vector3f end = to;
    start.y += y_offset;
    end.y += y_offset;

    ksys::phys::RayCastBodyQuery query(nullptr, ksys::phys::GroundHit::HitAll);
    ksys::act::sub_7100EEAE58(&query);
    query.setStartAndEnd(start, end);
    query.setNormalCheckingMode(
        static_cast<ksys::phys::RayCast::NormalCheckingMode>(normal_checking_mode));
    if (!query.worldRayCast(ksys::phys::ContactLayerType::Entity))
        return false;

    if (hit_pos)
        query.getHitPosition(hit_pos);
    if (hit_normal)
        query.getHitNormal(hit_normal);
    if (material_mask)
        *material_mask = query.getMaterialMask();
    return true;
}

ksys::phys::SystemGroupHandler* sub_710072E804(ksys::act::Actor* actor, int idx) {
    if (!actor)
        return nullptr;
    auto* physics = actor->getPhysics();
    if (!physics)
        return nullptr;
    return physics->get188(idx);
}

ksys::phys::SystemGroupHandler* sub_7100738C18(ksys::act::BaseProcLink* link, int idx) {
    if (!link->hasProc())
        return nullptr;
    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::acquireActor(link, &accessor);
    return accessor.x(idx);
}

void sub_710073953C(ksys::act::Actor* actor) {
    const auto& name = *sub_71007A24F8();
    if (!actor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_200))
        ksys::act::sub_7100EE5330(actor, name);
}

bool sub_710072E830(const sead::Vector3f& from, const sead::Vector3f& to, int normal_checking_mode,
                    sead::Vector3f* hit_pos, sead::Vector3f* hit_normal,
                    ksys::phys::MaterialMask* material_mask, f32 y_offset) {
    sead::Vector3f start = from;
    sead::Vector3f end = to;
    start.y += y_offset;
    end.y += y_offset;

    ksys::phys::RayCastBodyQuery query(nullptr, ksys::phys::GroundHit::HitAll);
    ksys::act::sub_7100EEAECC(&query);
    query.setStartAndEnd(start, end);
    query.setNormalCheckingMode(
        static_cast<ksys::phys::RayCast::NormalCheckingMode>(normal_checking_mode));
    if (!query.worldRayCast(ksys::phys::ContactLayerType::Entity))
        return false;

    if (hit_pos)
        query.getHitPosition(hit_pos);
    if (hit_normal)
        query.getHitNormal(hit_normal);
    if (material_mask)
        *material_mask = query.getMaterialMask();
    return true;
}

// NON_MATCHING: the original keeps the dy / max_dist checks as separate branches (ours merges them
// with fccmp) and computes the result after the query destructor
bool sub_710072DEF0(const sead::Vector3f& target, f32 max_dist, f32 min_dy, f32 max_dy,
                    const sead::Vector3f& pos, const sead::Vector3f& dir, f32 angle,
                    f32 angle_check_dist, f32 y_offset) {
    sead::Vector3f diff = target - pos;
    const f32 dy = diff.y;
    diff.y = 0;
    const f32 dist = diff.normalize();
    const f32 dot = diff.dot(dir);
    const f32 cos = sead::Mathf::cos(angle);
    if (dist > angle_check_dist && dot < cos)
        return false;

    if (dy < min_dy)
        return false;
    if (dy > max_dy)
        return false;
    if (dist > max_dist)
        return false;

    sead::Vector3f start = pos;
    sead::Vector3f end = target;
    start.y += y_offset;
    end.y += y_offset;

    ksys::phys::RayCastBodyQuery query(nullptr, ksys::phys::GroundHit::HitAll);
    ksys::act::sub_7100EEACE8(&query);
    query.setStartAndEnd(start, end);
    query.setGroundHit(ksys::phys::GroundHit::LineOfSight);
    return !query.worldRayCast(ksys::phys::ContactLayerType::Entity);
}

bool sub_710072EB10(const sead::Vector3f& from, const sead::Vector3f& to,
                    ksys::phys::RayCast::NormalCheckingMode mode, ksys::act::Actor* actor,
                    sead::Vector3f* hit_pos, sead::Vector3f* hit_normal,
                    ksys::phys::MaterialMask* hit_info, f32 y_offset) {
    sead::Vector3f start = from;
    sead::Vector3f end = to;
    start.y += y_offset;
    end.y += y_offset;
    ksys::phys::RayCastBodyQuery query(nullptr, ksys::phys::GroundHit::HitAll);
    ksys::act::sub_7100EEACE8(&query);
    query.setStartAndEnd(start, end);
    query.setNormalCheckingMode(mode);
    if (actor) {
        if (auto* physics = actor->getPhysics())
            query.setGroupHandlerIfAny(physics->get188(0));
    }
    if (!query.worldRayCast(ksys::phys::ContactLayerType::Entity))
        return false;
    if (hit_pos)
        query.getHitPosition(hit_pos);
    if (hit_normal)
        query.getHitNormal(hit_normal);
    if (hit_info)
        *hit_info = query.getMaterialMask();
    return true;
}

bool sub_710072E928(const sead::Vector3f& from, const sead::Vector3f& to, sead::Vector3f* hit_pos,
                    sead::Vector3f* hit_normal, ksys::phys::MaterialMask* material_mask,
                    f32 y_offset) {
    sead::Vector3f start = from;
    sead::Vector3f end = to;
    start.y += y_offset;
    end.y += y_offset;

    ksys::phys::RayCastBodyQuery query(nullptr, ksys::phys::GroundHit::HitAll);
    ksys::act::sub_7100EEACE8(&query);
    query.setStartAndEnd(start, end);
    if (!query.worldRayCast(ksys::phys::ContactLayerType::Entity))
        return false;

    if (hit_pos)
        query.getHitPosition(hit_pos);
    if (hit_normal)
        query.getHitNormal(hit_normal);
    if (material_mask)
        *material_mask = query.getMaterialMask();
    return true;
}

bool sub_710072EA18(const sead::Vector3f& from, const sead::Vector3f& to, int normal_checking_mode,
                    sead::Vector3f* hit_pos, sead::Vector3f* hit_normal,
                    ksys::phys::MaterialMask* material_mask, f32 y_offset) {
    sead::Vector3f start = from;
    sead::Vector3f end = to;
    start.y += y_offset;
    end.y += y_offset;

    ksys::phys::RayCastBodyQuery query(nullptr, ksys::phys::GroundHit::HitAll);
    ksys::act::sub_7100EEACE8(&query);
    query.setStartAndEnd(start, end);
    query.setNormalCheckingMode(
        static_cast<ksys::phys::RayCast::NormalCheckingMode>(normal_checking_mode));
    if (!query.worldRayCast(ksys::phys::ContactLayerType::Entity))
        return false;

    if (hit_pos)
        query.getHitPosition(hit_pos);
    if (hit_normal)
        query.getHitNormal(hit_normal);
    if (material_mask)
        *material_mask = query.getMaterialMask();
    return true;
}

// NON_MATCHING: the original branches to two copies of the point selection (the valid path reuses the
// loaded x); ours selects the source pointer with csel
bool sub_710072EC90(const sead::Vector3f& pos, const sead::Vector3f& target, sead::Vector3f* out,
                    f32 max_dist, f32 max_height) {
    ksys::phys::HavokAI::Unk1 result;
    auto* havok_ai = ksys::phys::HavokAI::instance();
    if (!havok_ai)
        return false;
    const bool hit = havok_ai->sub_7100F86174(pos, target, &result, max_height);
    sead::Vector3f point;
    if (!sead::Mathf::isNan(result._24.x) && !sead::Mathf::isNan(result._24.y) &&
        !sead::Mathf::isNan(result._24.z))
        point = result._24;
    else
        point = pos;
    if (out)
        *out = point;
    if (hit)
        return true;
    const f32 dist = sead::Mathf::sqrt(sead::Mathf::square(target.x - result._24.x) +
                                       sead::Mathf::square(target.z - result._24.z));
    if (dist <= max_dist)
        return sead::Mathf::abs(target.y - point.y) < max_height;
    return false;
}

void sub_71000891C8(sead::Vector3f* out, ksys::act::Actor* actor) {
    sead::Vector3f dir;
    actor->getMtx().getBase(dir, 2);
    const sead::Vector3f up = getUpDir(actor);
    ksys::util::sub_71011EFA00(&dir, dir, up);
    dir.normalize();
    *out = dir;
}

void sub_7100010168(uking::act::Dragon* dragon, sead::Vector3f* out) {
    sead::Vector3f dir = dragon->getMtx().getTranslation() - dragon->_1e10;
    if (dir.x == 0 && dir.y == 0 && dir.z == 0)
        dir = dragon->_1e28.getBase(0);
    dir.normalize();
    *out = dir;
}

bool sub_710072DDB8(const sead::Vector3f& target, const sead::Matrix34f& mtx, f32 angle) {
    sead::Vector3f forward;
    mtx.getBase(forward, 2);
    sead::Vector3f pos;
    mtx.getTranslation(pos);
    forward.y = 0;
    forward.normalize();
    sead::Vector3f to_target = target;
    to_target -= pos;
    to_target.y = 0;
    to_target.normalize();
    return forward.dot(to_target) >= sead::Mathf::cos(angle);
}

ksys::act::Actor* sub_710073D318(ksys::act::Actor* actor) {
    auto* info = actor->getPlayerRideInfo();
    if (!info)
        return nullptr;
    return sead::DynamicCast<ksys::act::Actor>(info->_18.getProc(nullptr, info->mActor));
}

uking::act::Rideable* sub_710073D3C8(ksys::act::Actor* actor) {
    auto* info = actor->getPlayerRideInfo();
    if (!info)
        return nullptr;
    if (auto* rider = sead::DynamicCast<ksys::act::Actor>(info->_18.getProc(nullptr, info->mActor)))
        return rider->getHorseOptionsMaybe();
    return nullptr;
}

const sead::Matrix34f& getPlayerPositionViaPlayerInfo() {
    if (auto* info = uking::act::PlayerInfo::instance()) {
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&info->getPlayerLink(), &accessor);
        return accessor.getActorMtx();
    }
    return sead::Matrix34f::ident;
}

bool sub_7100738E70(ksys::act::Actor* actor) {
    if (auto* set = actor->getRigidBodyByName(sub_71007A24D0()->cstr())) {
        if (set->getRigidBodies().size() != 0) {
            if (auto* body = set->getRigidBodies()(0)) {
                if (auto* info = body->getContactPointInfo()) {
                    if (info->getNumContactPoints() != 0 && !info->begin().isEnd()) {
                        for (auto it = info->begin(), end = info->end(); it != end; ++it) {
                            if ((*it)->body_b->getContactLayer() ==
                                ksys::phys::ContactLayer::SensorPlayer) {
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}

bool sub_7100738DF0(ksys::act::Actor* actor) {
    if (!sub_71007A4178(actor, false))
        return false;
    const s32 num = sub_71007A425C(actor);
    for (s32 i = 0; i < num; ++i) {
        if (ksys::act::isPlayerProfile(&sub_71007A40D0(actor, i)->_50))
            return true;
    }
    return false;
}

bool sub_7100734270(ksys::act::Actor* actor, sead::Vector3f* out, const sead::Vector3f& pos) {
    *out = pos;
    if (auto* drop = sead::DynamicCast<ksys::act::DropData>(actor->getDropData())) {
        drop->_c |= 0x80;
        return true;
    }
    return false;
}

// NON_MATCHING: the grouped condition cases share the controller update instead of three native copies.
void sub_710073DCB4(ksys::act::Actor* actor, int condition) {
    if (auto* dynamic_actor = sead::DynamicCast<ksys::act::DynamicActor>(actor)) {
        if (auto* life = dynamic_actor->getLife())
            *life = 0;
        switch (condition) {
        case 2:
        case 3:
        case 4: {
            auto* controller = dynamic_actor->m159();
            if (!(controller->_a & 3)) {
                controller->m12(condition);
                controller->_a |= 4;
            }
            break;
        }
        default:
            break;
        }
    }
}

void sub_710073DE08(ksys::act::Actor* actor) {
    actor->sub_71011D0228(0x10);
    actor->sub_71011D0228(4);
    actor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_10000);
}

void sub_710073DE44(ksys::act::Actor* actor) {
    actor->sub_71011D0204(0x10);
    actor->sub_71011D0204(4);
    actor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_10000);
}

// NON_MATCHING: same instructions but the SafeString temporary is stored with two str instead of one stp (104 vs 100 bytes)
bool sub_7100731000(ksys::act::Actor* actor, bool value) {
    return actor->getRootAi()->getMapUnitParams().setAITreeVariable(
        "IsPlayerPut", ksys::AIDefParamType::Bool, value);
}

ksys::act::Unk_7100d860d8* sub_71007398C0(ksys::act::Actor* actor) {
    auto* bone_control = actor->getBoneControl();
    if (!bone_control)
        return nullptr;
    auto* unk = bone_control->_0;
    if (!unk)
        return nullptr;
    return &unk->_10;
}

// NON_MATCHING: everything matches except the address computation: the original has one `add x0, x8, #0x78` where we get
// `add x8, x8, #0x60; add x0, x8, #0x18` (the Parameter object, then its value; ref() and operator* tried)
const sead::SafeString& sub_710072D53C(ksys::act::Actor* actor, u32 slot) {
    switch (slot) {
    case 0:
        return *actor->getParam()->getRes().mGParamList->getGiantArmorSlot()->mSlot0RigidBody;
    case 1:
        return *actor->getParam()->getRes().mGParamList->getGiantArmorSlot()->mSlot1RigidBody;
    case 2:
        return *actor->getParam()->getRes().mGParamList->getGiantArmorSlot()->mSlot2RigidBody;
    case 3:
        return *actor->getParam()->getRes().mGParamList->getGiantArmorSlot()->mSlot3RigidBody;
    default:
        return sead::SafeString::cEmptyString;
    }
}

void sub_7100738C88(ksys::act::Actor* actor, ksys::act::Actor* other) {
    if (!other)
        return;
    auto* other_physics = other->getPhysics();
    if (!other_physics)
        return;
    auto* handler = other_physics->get188(0);
    auto* physics = actor->getPhysics();
    if (handler && physics)
        physics->sub_7100FBDFA4(handler);
}

void sub_7100738D28(ksys::act::Actor* actor, ksys::act::Actor* other) {
    if (!other)
        return;
    auto* other_physics = other->getPhysics();
    if (!other_physics)
        return;
    auto* handler = other_physics->get188(1);
    auto* physics = actor->getPhysics();
    if (handler && physics)
        physics->sub_7100FBDFA4(handler);
}


void sub_71007390B8(ksys::act::AttackSensor* sensor) {
    if (sensor)
        sensor->_20 = 0xfffd;
}

void sub_71007390C8(ksys::act::AttackSensor* sensor) {
    if (sensor)
        sensor->_20 = 0x15;
}

void sub_71007390D8(ksys::act::AttackSensor* sensor) {
    if (sensor)
        sensor->_20 = 0x8;
}

void sub_71007390E8(ksys::act::AttackSensor* sensor) {
    if (sensor)
        sensor->_20 = 0x5;
}

void sub_71007390F8(ksys::act::AttackSensor* sensor) {
    if (sensor)
        sensor->_20 = 0x1;
}

void sub_7100739118(ksys::act::AttackSensor2* sensor) {
    if (sensor)
        sensor->_1c = 1;
}

void sub_7100739128(ksys::act::AttackSensor2* sensor) {
    if (sensor)
        sensor->_1c = 8;
}

void sub_7100739138(ksys::act::AttackSensor2* sensor) {
    if (sensor)
        sensor->_1c = 2;
}

void sub_7100739148(ksys::act::AttackSensor2* sensor) {
    if (sensor)
        sensor->_1c = 16;
}

void sub_7100739158(ksys::act::AttackSensor2* sensor) {
    if (sensor)
        sensor->_1c = 16;
}

void sub_7100739168(ksys::act::AttackSensor2* sensor) {
    if (sensor)
        sensor->_1c = 4;
}

void sub_71007393EC(ksys::act::Actor* actor) {
    const auto* body_name = sub_71007A24E4();
    if (!actor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_200))
        ksys::act::sub_7100EE5330(actor, *body_name);
    if (auto* controller = actor->getCharacterController())
        controller->sub_7100F5EC30();
}

const ksys::act::ActorAtk::Unk_710079e64c::Unk1* sub_7100739578(ksys::act::Actor* actor) {
    auto* manager = sead::DynamicCast<uking::act::DamageManager>(actor->getDamageMgr());
    if (manager && manager->_6c >= 0)
        return sub_71007A255C(actor, manager->_6c);
    if (!sub_71007A2604(actor))
        return nullptr;
    return sub_71007A255C(actor, 0);
}

// NON_MATCHING: compare order of the switch (the original tests 2, 6, 4) and the _18 flag test (word load).
bool sub_7100739634(Unk_7100739634Result* out, const ksys::act::Chemical* chemical,
                    const ksys::act::ActorAtk::Unk_710079e64c::Unk1* atk, const bool* flags) {
    if (!atk)
        return false;

    bool skip = false;
    if (!flags || flags[1])
        skip = (atk->_18 & 1) ? true : (atk->_18 >> 1 & 1);

    if (chemical->sub_7100D91080())
        return false;
    if (!(chemical->_8 & 2))
        return false;

    const s32 id = atk->_f8;
    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::acquireActor(&atk->_e8, &accessor);
    if (accessor.sub_7100D12F08(-1) && !accessor.hasTag(0x19f6c13a))
        return false;

    s32 value;
    switch (accessor.sub_7100D131D0(id)) {
    case 2:
        if (skip)
            return false;
        out->kind = 2;
        out->_4 = accessor.sub_7100D134F8(id);
        value = ((chemical->mMaterial->attribute.ref() & 1) && !(chemical->_be & 1)) ||
                        (flags && flags[0]) ?
                    1 :
                    2;
        break;
    case 6:
        if (skip)
            return false;
        if (!accessor.sub_7100D1370C(id))
            return false;
        out->kind = 3;
        out->_4 = 1;
        value = (chemical->_be & 2) ? 2 : ((chemical->mMaterial->attribute.ref() >> 22) & 1) + 1;
        break;
    case 4:
        if (skip)
            return false;
        if (accessor.sub_7100D0FFDC(id)) {
            out->kind = 2;
            out->_4 = 3;
            value = ((chemical->mMaterial->attribute.ref() & 1) && !(chemical->_be & 1)) ||
                            (flags && flags[0]) ?
                        1 :
                        2;
            break;
        }
        // fallthrough
    default:
        if (accessor.sub_7100D13080() <= 0.0f)
            return false;
        if (atk->sub_71007A1F68(0x800)) {
            if ((flags != nullptr & skip) && !flags[2])
                return false;
            out->_18 = true;
        } else if (skip) {
            return false;
        }
        out->kind = 4;
        out->_4 = 1;
        out->_c = 1;
        return true;
    }

    out->_c = value;
    if (atk->sub_71007A1F68(0x800))
        out->_18 = true;
    return true;
}

void sub_7100739108(ksys::act::AttackSensor* sensor) {
    if (sensor)
        sensor->_20 = 0xffff;
}

// NON_MATCHING: the type 20 check is merged with the flag test (orr) instead of branching.
void sub_7100732864(sead::BitFlag8* flags, ksys::act::Actor* actor) {
    flags->makeAllZero();
    auto* base = sead::DynamicCast<uking::act::DamageManagerBase>(actor->getDamageMgr());
    if (!base)
        return;

    auto* mgr = sead::DynamicCast<uking::act::DamageManager>(base);
    s32 type;
    bool flag12;
    if (mgr && mgr->sub_71006D82D4()) {
        type = mgr->sub_71006D8340();
        flag12 = mgr->sub_71006D83B8(12);
    } else {
        type = base->getField54();
        flag12 = base->checkDamageFlags(12);
    }

    if (type == 0) {
        flags->set(2);
        return;
    }

    bool hit = false;
    if (sub_7100732AD0(type) || type == 1 || type == 2 || type == 5 || sub_7100732AFC(type) ||
        sub_7100732B0C(type)) {
        hit = true;
    } else if (mgr && type == 18) {
        if (mgr->getDamageType() == 4 || mgr->getDamageType() == 2)
            hit = true;
    } else if (type == 3 || type == 4) {
        flags->set(2);
        if (mgr && (mgr->_218 & 0xf)) {
            if (!base->isDamageItemFlagCheckDisabled())
                flags->set(1);
            return;
        }
    } else if (mgr && type == 20) {
        if (mgr->_218 & 0xf)
            hit = true;
    }

    if (!hit && !flag12)
        return;
    flags->set(2);
    if (!base->isDamageItemFlagCheckDisabled())
        flags->set(1);
}

bool sub_7100732AFC(s32 damage_type) {
    return u32(damage_type - 11) < 3;
}

bool sub_7100732B0C(s32 damage_type) {
    return u32(damage_type - 9) < 2 || damage_type == 14;
}

// 0x71006df0f8 (dmgActorAccessors.cpp): bit 3 of the accessor's DynamicActor::_a68.
bool sub_71006DF0F8(const ksys::act::ActorLinkConstDataAccess& accessor);

// NON_MATCHING: regalloc (damage / field50 swapped) and the order of the _1d / _1e stores.
void sub_7100732B28(DamageReactionInfo* info, ksys::act::Actor* actor) {
    auto* base = sead::DynamicCast<uking::act::DamageManagerBase>(actor->getDamageMgr());
    if (!base)
        return;

    auto* mgr = sead::DynamicCast<uking::act::DamageManager>(base);
    s32 type;
    bool from_mgr;
    if (mgr && mgr->sub_71006D82D4()) {
        type = mgr->sub_71006D8340();
        from_mgr = true;
    } else {
        type = base->getField54();
        from_mgr = false;
    }

    sead::BitFlag8 flags;
    sub_7100732864(&flags, actor);
    if (flags.isZero())
        return;

    s32 field50;
    s32 damage;
    const ksys::phys::MaterialMask* attack_mask;
    const ksys::phys::MaterialMask* sensor_mask;
    bool flag0, flag7, flag10, flag12, flag1, flag16, flag18;
    bool kind9;
    if (from_mgr) {
        damage = mgr->sub_71006D8304();
        field50 = mgr->sub_71006D837C();
        flag0 = mgr->sub_71006D83B8(0);
        flag7 = mgr->sub_71006D83B8(7);
        flag10 = mgr->sub_71006D83B8(10);
        flag12 = mgr->sub_71006D83B8(12);
        flag1 = mgr->sub_71006D83B8(1);
        flag16 = mgr->sub_71006D83B8(16);
        flag18 = mgr->sub_71006D83B8(18);
        attack_mask = nullptr;
        kind9 = false;
        sensor_mask = nullptr;
    } else {
        damage = base->getDamage();
        field50 = base->getField50();
        attack_mask = base->getAttackOtherMaterialMask();
        sensor_mask = base->tgSensorMaterialOnHitMaybe();
        flag0 = base->checkDamageFlags(0);
        flag7 = base->checkDamageFlags(7);
        flag10 = base->checkDamageFlags(10);
        flag12 = base->checkDamageFlags(12);
        flag1 = base->checkDamageFlags(1);
        flag16 = base->checkDamageFlags(16);
        flag18 = base->checkDamageFlags(18);
        kind9 = mgr && mgr->getDamageType() == 9;
    }

    ksys::act::ActorLinkConstDataAccess attacker;
    ksys::act::acquireActor(base->m37(), &attacker);
    info->_0 = field50;
    info->_4 = type;
    info->_8 = damage;
    info->_c = mgr ? mgr->getField40() : 0;
    info->_10 = base->m37();
    info->_19 = flag0;
    info->_1a = flag7;
    info->_18 = base->checkDamageFlags(9);
    info->_30 = sensor_mask;
    info->_38 = attack_mask;
    info->_1b = base->sub_71006E0D24();
    info->_1c = base->sub_71006E0E78();
    info->_1d = base->sub_71006E0FB4();
    info->_1f = flag10;
    info->_1e = actor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_40);
    info->_22 = flag1;
    info->_20 = flag12;
    info->_21 = (mgr && mgr->getDamageType() == 4) || field50 == 6;
    info->_25 = mgr && type == 20 && ((mgr->_218 & 8) || (mgr->_218 & 2));
    info->_26 = flag16;
    info->_27 = flag18;
    info->_28 = sub_71006DF0F8(attacker);
    info->_29 = kind9;
}

// NON_MATCHING: the original keeps the reaction kind in a stack slot (stored by each branch and reloaded for
// xlinkEventOn, like a SEAD_ENUM value); ours keeps it in a register.
void sub_7100734E68(ksys::act::ActorLinkConstDataAccess* out, ksys::act::Actor* actor) {
    auto* weapons = actor->getWeapons();
    if (!weapons)
        return;
    for (auto& weapon : weapons->mWeapons) {
        ksys::act::ActorLinkConstDataAccess accessor;
        if (weapon.link.hasProc())
            ksys::act::acquireActor(&weapon.link, &accessor);
        if (sub_71002F0258(accessor) == 4) {
            if (weapon.link.hasProc())
                ksys::act::acquireActor(&weapon.link, out);
            return;
        }
    }
}

// NON_MATCHING: the target kind branches and the profile string tests are laid out differently.
void sub_7100735044(DamageReactionRequest* request, ksys::act::Actor* actor,
                    const DamageReactionInfo* info, bool a3, bool a4, bool a5, bool a6) {
    const char* user = ksys::act::InfoData::instance()->getXLinkUser(actor->getName().cstr());
    const auto iter = ksys::xlink::InfoData::instance()->getIter(user);
    const bool tiny_enemy =
        ksys::xlink::InfoData::instance()->getXLinkSettingIsReactionTargetTinyEnemy(iter);
    const bool enemy = ksys::xlink::InfoData::instance()->getXLinkSettingIsReactionTargetEnemy(iter);
    const bool object = ksys::xlink::InfoData::instance()->getXLinkSettingIsReactionTargetObject(iter);
    const bool tag_fa5c683e = ksys::act::hasTag(actor, 0xfa5c683e);

    s32 target;
    if (tiny_enemy) {
        target = 4;
    } else if (object) {
        target = 5;
    } else {
        const bool tag_319c67f0 = ksys::act::hasTag(actor, 0x319c67f0);
        if (enemy || tag_319c67f0) {
            target = tag_319c67f0 ? 9 : 3;
        } else {
            bool other = true;
            if (ksys::act::isEnemyProfile(actor) || ksys::act::isPreyOrSwarm(actor) ||
                ksys::act::isHorseProfile(actor)) {
                other = tag_fa5c683e;
            } else if (actor->getProfile() == "CapturedActor") {
                other = (ksys::act::hasTag(actor, 0xe0194f30) && info->_24) || tag_fa5c683e;
            }
            if (!other)
                target = 3;
            else if (ksys::act::isPlayerProfile(actor))
                target = 1;
            else if (tag_fa5c683e || ksys::act::isNPCProfile(actor))
                target = 2;
            else if (actor->getName() == "RemainsWind_Barrier_A_01")
                target = 8;
            else
                target = 5;
        }
    }

    s32 kind;
    if (info->_0 == 0x12) {
        kind = 7;
    } else if (info->_1e) {
        kind = 6;
    } else {
        switch (info->_4) {
        case 9:
        case 10:
        case 11:
        case 12:
        case 14:
            kind = 4;
            break;
        case 13:
            kind = 5;
            break;
        default:
            if (info->_25)
                kind = 4;
            else if (info->_0 == 3)
                kind = 3;
            else
                kind = info->_21 ? 2 : 1;
            break;
        }
    }

    s32 reaction = 3;
    if (!(a3 && a4) && !ksys::act::hasTag(actor, 0xfa5c683e) && (info->_8 > 0 || info->_4 > 0x1c) &&
        !(info->_24 && actor->getProfile() == "CapturedActor")) {
        if (info->_4 == 0x17) {
            reaction = 7;
        } else if (info->_18) {
            reaction = 9;
        } else if (info->_1f) {
            reaction = 4;
        } else if (info->_1a) {
            reaction = 5;
        } else if (info->_19) {
            reaction = 6;
        } else if (info->_26) {
            reaction = 8;
        } else if (info->_0 == 0x10) {
            reaction = 11;
        } else if (info->_0 == 4) {
            reaction = 10;
        } else {
            switch (info->_4) {
            case 21:
            case 22:
            case 27:
            case 30:
            case 31:
            case 34:
                reaction = 2;
                break;
            default:
                reaction = 1;
                break;
            }
        }
    }

    s32 a4_kind = info->_22 || a6 ? 3 : 0;
    if (!a5 && (info->_22 || a6))
        a4_kind = ksys::act::hasTag(actor, 0x17044493) ? 2 : 1;

    if (info->_27)
        request->_c4 |= 0x10;
    if (auto* life = actor->getLife()) {
        if (*life <= 0 && !(actor->getProfile() == "CapturedActor"))
            request->_c4 |= 1;
    }

    request->_94 = reaction;
    request->_98 = target;
    request->_90 = kind;
    request->_a4 = a4_kind;
    request->mSource.mLink = info->_10;
    if (info->_28)
        request->_c4 |= 0x20;
    else
        request->_c4 &= ~0x20;
    if (info->_29)
        request->_c4 |= 0x40;
    else
        request->_c4 &= ~0x40;
}

bool sub_71007357A8(ksys::act::Actor* actor, const DamageReactionInfo* info) {
    if (sub_71007A2604(actor) && sub_71007A255C(actor, 0)->sub_71007A1F68(0x20))
        return true;

    auto* dynamic_actor = sead::DynamicCast<ksys::act::DynamicActor>(actor);
    auto* unk = dynamic_actor ? dynamic_actor->m159() : nullptr;

    s32 kind = 0;
    if (ksys::act::hasTag(actor, 0xfa5c683e)) {
        kind = 2;
    } else if (info->_4 == 4 || (unk && unk->_8.isOn(0x10))) {
        kind = 13;
    } else if (ksys::act::hasTag(info->_10, 0x5e27ef10) && ksys::act::hasTag(actor, 0x17044493)) {
        kind = info->_19 ? 9 : 8;
    } else if (info->_4 == 23) {
        kind = 6;
    } else if (info->_20) {
        kind = 7;
    } else if (info->_4 == 3 || info->_1f) {
        kind = 3;
    } else if (info->_1a) {
        kind = 4;
    } else if (info->_19) {
        kind = 5;
    } else {
        switch (info->_4) {
        case 0: {
            const s32* life = actor->getLife();
            if (!life || *life > 0)
                return true;
            if (info->_0 == 20)
                kind = 12;
            else if (info->_0 == 19)
                kind = 11;
            else
                return true;
            break;
        }
        case 18:
            kind = 10;
            break;
        case 21:
        case 22:
            if (!info->_23 || info->_c > 1)
                kind = 1;
            else
                kind = 0;
            break;
        case 27:
        case 30:
        case 31:
        case 34:
            kind = 1;
            break;
        default:
            kind = 0;
            break;
        }
    }

    xlinkEventOn(actor, 22, kind, true);
    const s32* life = actor->getLife();
    if (life && *life <= 0) {
        ksys::eft::searchAndEmitSLink(actor, "DamageDead", false);
    } else if (u32(info->_4) <= 34 && ((1ull << info->_4) & 0x4c862803eull)) {
        ksys::eft::searchAndEmitSLink(actor, "Damage", false);
    }
    return true;
}

namespace ksys::act {

// NON_MATCHING: the original masks the getFlags2() result as 32-bit (our getFlags2 returns u64).
void Actor::x_2() {
    auto* drop = sead::DynamicCast<DropData>(getDropData());
    if (drop && (drop->_8 == 1 || drop->_8 == 2))
        return;

    auto* mgr = sead::DynamicCast<uking::act::DamageManager>(getDamageMgr());
    if (!mgr)
        return;

    const s32 type = mgr->sub_71006D82D4() ? mgr->sub_71006D8340() : mgr->getField54();
    mgr->applyDamage(*getLife());
    const res::DamageParam* damage_param = mActorParam ? mActorParam->getRes().mDamageParam : nullptr;
    if (type != -1) {
        sead::BitFlag8 flags;
        sub_7100732864(&flags, this);
        if (!flags.isZero()) {
            DamageReactionInfo info;
            sub_7100732B28(&info, this);
            if (flags.isOnBit(0))
                sub_7100733418(this, &info, nullptr);
        }
    }

    drop = sead::DynamicCast<DropData>(getDropData());
    if (drop && drop->_8 == 1)
        return;
    if (sub_7100733C24(this))
        return;
    if (!damage_param || !*damage_param->mBreakable || *getLife() >= 1)
        return;

    *getLife() = 0;
    if (auto* data = sead::DynamicCast<DropData>(getDropData()))
        data->sub_71006DA914(mgr, false);
    if (auto* unk3 = m135(); unk3 && u16(mgr->getFlags2()) == 5)
        unk3->_4 = 4;
    callDeleteAndCreateDropAndEmit(this, 0);
}

}  // namespace ksys::act

bool sub_7100732AD0(s32 damage_type) {
    switch (damage_type) {
    case 15:
    case 17:
    case 21:
    case 22:
    case 23:
    case 27:
    case 30:
    case 31:
    case 34:
        return true;
    default:
        return false;
    }
}

void sub_7100738CB0(ksys::act::Actor* actor, ksys::act::BaseProcLink* link) {
    if (!link->hasProc())
        return;
    ksys::phys::SystemGroupHandler* handler;
    {
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(link, &accessor);
        handler = accessor.x(0);
    }
    if (handler && actor->getPhysics())
        actor->getPhysics()->sub_7100FBDFA4(handler);
}

void sub_7100738D50(ksys::act::Actor* actor, ksys::act::BaseProcLink* link) {
    if (!link->hasProc())
        return;
    ksys::phys::SystemGroupHandler* handler;
    {
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(link, &accessor);
        handler = accessor.x(1);
    }
    if (handler && actor->getPhysics())
        actor->getPhysics()->sub_7100FBDFA4(handler);
}

void sub_7100738DDC(ksys::act::Actor* actor) {
    if (auto* physics = actor->getPhysics())
        physics->sub_7100FBDFA4(physics->get178(1));
}

bool sub_7100738FA8(ksys::act::Actor* actor, ksys::act::BaseProc* proc) {
    if (!sub_71007A4178(actor, false))
        return false;
    const s32 num = sub_71007A425C(actor);
    for (s32 i = 0; i < num; ++i) {
        if (sub_71007A40D0(actor, i)->_50.hasProcById(proc))
            return true;
    }
    return false;
}



u32 sub_710072C494(f32* out_height, const sead::Vector3f* pos) {
    auto* placement = ksys::map::PlacementMgr::instance();
    if (!placement)
        return 0;
    auto* tera_system = placement->mTeraSystem;
    if (!tera_system)
        return 0;
    const sead::Vector2f xz(pos->x, pos->z);
    return ksys::tera::sub_710110B4A4(out_height, &xz, tera_system);
}

bool sub_710072C388(u32* out, const sead::Vector3f* pos, f32 max_height_diff) {
    sead::Vector2f xz;
    f32 height = 0;
    ksys::tera::MaterialRecordMaybe record;
    auto* placement = ksys::map::PlacementMgr::instance();
    if (!placement)
        return false;
    auto* tera_system = placement->mTeraSystem;
    if (!tera_system)
        return false;
    xz = sead::Vector2f(pos->x, pos->z);
    if (ksys::tera::sub_71011094A0(&height, &xz, tera_system, -1, 0) == 0)
        return false;
    if (sead::Mathf::abs(pos->y - height) > max_height_diff)
        return false;

    tera_system = ksys::map::PlacementMgr::instance()->mTeraSystem;
    record.raw = 0xff;
    if (!tera_system)
        return false;
    xz = sead::Vector2f(pos->x, pos->z);
    if (ksys::tera::sub_710110BD78(&record, &xz, tera_system, false) == 0)
        return false;
    const u32 index = record._1 >= 0 ? record._3 : record._2;
    *out = tera_system->_e8[index].value;
    return true;
}

// NON_MATCHING: the two float locals sit 8 bytes higher in the frame and the sampled height stays in s0
// instead of a callee-saved register; the instruction sequence is otherwise identical.
u32 sub_710072C278(f32* out, const sead::Vector3f* pos) {
    sead::Vector2f xz;
    f32 grass_amount = 0;
    f32 height = 0;

    auto* terrain = ksys::tera::Terrain::instance();
    if (!terrain || !terrain->isGrassEnabled()) {
        *out = 0;
        return 0;
    }
    auto* grass = terrain->sub_710114DE58();
    xz = sead::Vector2f(pos->x, pos->z);
    const u32 grass_result = grass->sub_71011516D0(&grass_amount, &xz);
    if (grass_result == 0) {
        *out = 0;
        return 0;
    }

    bool on_material = false;
    f32 material_height = 0;
    auto* placement = ksys::map::PlacementMgr::instance();
    if (placement && placement->mTeraSystem) {
        xz = sead::Vector2f(pos->x, pos->z);
        on_material =
            ksys::tera::sub_71011094A0(&height, &xz, placement->mTeraSystem, -1, 0) == 2;
        material_height = height;
    }

    if (grass_amount * 1.2f <= pos->y - material_height)
        grass_amount = 0;
    *out = grass_amount;
    return grass_result == 2 && on_material ? 2 : 1;
}

// NON_MATCHING: the original adds 0.0f to every ray y coordinate (source form unknown).
bool sub_710072C4E8(sead::Vector3f* out, const sead::Vector3f& pos) {    *out = pos;
    sead::Vector3f dir = sead::Vector3f::zero;
    sead::Vector3f player_pos = sead::Vector3f::zero;
    if (sub_710084D068()) {
        auto* info = uking::act::PlayerInfo::instance();
        player_pos = info ? info->getPlayerPos() : sead::Vector3f::zero;
        dir = pos - player_pos;
        dir.normalize();
    }

    sead::Vector3f target = pos;
    target.y -= 0.5f;
    {
        const sead::Vector3f start(pos.x, pos.y + 0.5f, pos.z);
        ksys::phys::RayCastBodyQuery ray_cast(nullptr, ksys::phys::GroundHit::HitAll);
        ksys::act::sub_7100EEAD7C(&ray_cast);
        ray_cast.setStartAndEnd(start, target);
        if (ray_cast.worldRayCast(ksys::phys::ContactLayerType::Entity)) {
            ray_cast.getHitPosition(&target);
            target.y += 0.005f;
            *out = target;
        }
    }

    const sead::Vector3f start(player_pos.x, player_pos.y + 0.5f, player_pos.z);
    ksys::phys::RayCastBodyQuery ray_cast(nullptr, ksys::phys::GroundHit::HitAll);
    ksys::act::sub_7100EEAD7C(&ray_cast);
    ray_cast.setStartAndEnd(start, target);
    if (!ray_cast.worldRayCast(ksys::phys::ContactLayerType::Entity))
        return false;
    sead::Vector3f hit;
    ray_cast.getHitPosition(&hit);
    *out = hit - dir * 0.25f;
    return true;
}

u32 sub_710072C1B8(f32* out, const sead::Vector3f* pos) {
    auto* terrain = ksys::tera::Terrain::instance();
    if (!terrain)
        return 0;
    if (!terrain->isGrassEnabled())
        return 0;
    auto* grass = terrain->sub_710114DE58();
    const sead::Vector2f xz(pos->x, pos->z);
    return grass->sub_71011516D0(out, &xz);
}

u32 sub_710072C21C(f32* out_height, const sead::Vector3f* pos) {
    auto* placement = ksys::map::PlacementMgr::instance();
    if (!placement)
        return 0;
    auto* tera_system = placement->mTeraSystem;
    if (!tera_system)
        return 0;
    const sead::Vector2f xz(pos->x, pos->z);
    return ksys::tera::sub_71011094A0(out_height, &xz, tera_system, -1, 0);
}

namespace {
// inline-only in the original; name is a guess: the same sequence (the name is evaluated before the flag test) is
// inlined twice into sub_71007394E8.
void setUpBodyUnlessFlag200(ksys::act::Actor* actor, const sead::SafeString& name) {
    if (!actor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_200))
        ksys::act::sub_7100EE5330(actor, name);
}
}  // namespace

void sub_71007394E8(ksys::act::Actor* actor) {
    setUpBodyUnlessFlag200(actor, *sub_71007A24D0());
    setUpBodyUnlessFlag200(actor, *sub_71007A24F8());
}

void sub_71007428DC(f32 distance, f32 radius, sead::Vector3f* out,
                   ksys::phys::NavMeshCharacter* character, const sead::Vector3f* axis, s32 count) {
    sub_71007428EC(distance, radius, out, character, axis, axis, count);
}

const sead::SafeString& sub_710072DAD0(const ksys::act::BaseProcLink* link) {
    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::acquireActor(link, &accessor);
    return sub_710072DB1C(accessor);
}

// NON_MATCHING: compiler shares the Parameter::ref offset across switch branches.
const sead::SafeString& sub_710072DB1C(const ksys::act::ActorLinkConstDataAccess& accessor) {
    ksys::act::ActorLinkConstDataAccess weapon;
    weapon.acquireActor(accessor);
    switch (sub_71002F0258(weapon)) {
    case 0:
        return accessor.getGParamList()->getSmallSword()->mWeaponSubType.ref();
    case 1:
        return accessor.getGParamList()->getLargeSword()->mWeaponSubType.ref();
    case 2:
        return accessor.getGParamList()->getSpear()->mWeaponSubType.ref();
    case 3:
        return accessor.getGParamList()->getBow()->mWeaponSubType.ref();
    case 4:
        return accessor.getGParamList()->getShield()->mWeaponSubType.ref();
    default:
        return sead::SafeString::cEmptyString;
    }
}

// NON_MATCHING: the unrolled search reuses its link pointer instead of recomputing it from the slot.
void sub_7100736114(ksys::act::BaseProcLink* link, ksys::act::Actor* actor) {
    auto* weapons = actor->getWeapons();
    if (!weapons)
        return;
    for (s32 i = 0; i < 6; ++i) {
        ksys::act::ActorLinkConstDataAccess accessor;
        if (weapons->mWeapons[i].link.hasProc())
            ksys::act::acquireActor(&weapons->mWeapons[i].link, &accessor);
        if (sub_71002F0258(accessor) == 4) {
            *link = weapons->mWeapons[i].link;
            return;
        }
    }
    link->reset();
}

bool sub_7100736384(ksys::act::Actor* actor) {
    if (auto* npc = sead::DynamicCast<uking::act::NPC>(actor))
        return (npc->_fe8 & 4) != 0;
    return false;
}

bool sub_71007356EC(const ksys::act::BaseProcLink* link) {
    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::acquireActor(link, &accessor);
    return accessor.getName() == "Weapon_Sword_070";
}

bool sub_7100733360(ksys::act::Actor* actor) {
    auto* data = sead::DynamicCast<ksys::act::DropData>(actor->getDropData());
    if (data) {
        if (data->_8 == 1)
            return true;
        if (data->_8 == 2)
            return true;
    }
    return false;
}

bool sub_7100733B84(ksys::act::Actor* actor) {
    auto* data = sead::DynamicCast<ksys::act::DropData>(actor->getDropData());
    if (!data)
        return false;
    return data->_8 == 1;
}

bool sub_7100733C24(ksys::act::Actor* actor) {
    auto* damage = sead::DynamicCast<uking::act::DamageManager>(actor->getDamageMgr());
    if (!damage || damage->getField54() != 28)
        return false;
    *actor->getLife() = 0;
    if (auto* state = actor->m135()) {
        switch (damage->getFlags2() & 0xffff) {
        case 1:
            state->_4 = 13;
            break;
        case 3:
            state->_4 = 6;
            break;
        case 5:
            state->_4 = 5;
            break;
        case 6:
            state->_4 = 7;
            break;
        default:
            break;
        }
    }
    actor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::Alive);
    if (auto* data = sead::DynamicCast<ksys::act::DropData>(actor->getDropData())) {
        data->sub_71006DA914(damage, false);
        data->_8 = 1;
        if (auto* mgr = ksys::act::DropMgr::instance()) {
            mgr->sub_7100D2C024(actor);
            return true;
        }
    }
    callDeleteAndCreateDropAndEmit(actor, 0);
    return true;
}

bool cannotUseWolfLinkAmiibo() {
    auto* placement = ksys::map::PlacementMgr::instance();
    if (!placement || !placement->mPlacementActors || !placement->mPlacementActors->mStruct1)
        return false;
    auto* location = GameSceneSubsys14::instance();
    if (!location || location->sub_7100904ED4())
        return true;
    return location->sub_7100904F4C();
}

void sub_7100731A30(ksys::act::Actor* actor, s32 index) {
    if (!actor)
        return;
    auto* gdt = ksys::gdt::Manager::instance();
    if (!gdt)
        return;
    auto* object = actor->getMapObject();
    if (!object)
        return;
    const auto& map = gdt->getMapName();
    const u32 hash = object->getHashId();
    sead::FormatFixedSafeString<128> name("%s_OreDrop%d_%s_%u", map.cstr(), index,
                                          actor->getName().cstr(), hash);
    auto* hard_mode = uking::aoc::HardModeManager::instance();
    if (hard_mode && hard_mode->checkFlag(uking::aoc::HardModeManager::Flag::EnableHardMode))
        name.format("%s_OreDrop%d_%s_%u", map.cstr(), index, object->getUnitConfigName(), hash);
    gdt->setBool(true, name);
}

// NON_MATCHING: initial false return is shared after the null checks.
bool sub_7100731B70(ksys::act::Actor* actor, s32 index) {
    if (!actor)
        return false;
    auto* gdt = ksys::gdt::Manager::instance();
    if (!gdt)
        return false;
    auto* object = actor->getMapObject();
    if (!object)
        return false;
    const auto& map = gdt->getMapName();
    const u32 hash = object->getHashId();
    sead::FormatFixedSafeString<128> name("%s_OreDrop%d_%s_%u", map.cstr(), index,
                                          actor->getName().cstr(), hash);
    auto* hard_mode = uking::aoc::HardModeManager::instance();
    if (hard_mode && hard_mode->checkFlag(uking::aoc::HardModeManager::Flag::EnableHardMode))
        name.format("%s_OreDrop%d_%s_%u", map.cstr(), index, object->getUnitConfigName(), hash);
    bool value = false;
    auto& param = gdt->getParam();
    param.get().getBuffer()->getBool(&value, name, param.shouldCheckPermissions(), false);
    return value;
}

// NON_MATCHING: the inline hash getter is evaluated after string termination.
void sub_7100731F30(ksys::act::Actor* actor, s32 index) {
    if (!actor)
        return;
    auto* gdt = ksys::gdt::Manager::instance();
    if (!gdt)
        return;
    auto* object = actor->getMapObject();
    if (!object)
        return;
    sead::FormatFixedSafeString<128> name("%s_PartsDrop_%u", gdt->getMapName().cstr(),
                                          object->getHashId());
    s32 bits = 0;
    auto& param = gdt->getParam();
    if (param.get().getBuffer()->getS32(&bits, name, param.shouldCheckPermissions(), false))
        gdt->setS32((bits | (1u << index)) & 0xff, name);
}

// NON_MATCHING: hash getter timing, initial false returns and register allocation differ.
bool sub_710073200C(ksys::act::Actor* actor, s32 index) {
    if (!actor)
        return false;
    auto* gdt = ksys::gdt::Manager::instance();
    if (!gdt)
        return false;
    auto* object = actor->getMapObject();
    if (!object)
        return false;
    sead::FormatFixedSafeString<128> name("%s_PartsDrop_%u", gdt->getMapName().cstr(),
                                          object->getHashId());
    s32 bits = 0;
    auto& param = gdt->getParam();
    param.get().getBuffer()->getS32(&bits, name, param.shouldCheckPermissions(), false);
    if (!bits)
        return false;
    return (bits & (1u << index) & 0xff) != 0;
}

void uking::act::Enemy::setDroppedWeaponFlag() {
    if (!this)
        return;
    auto* manager = ksys::gdt::Manager::instance();
    if (!manager)
        return;
    auto* object = mMapObject;
    if (!object)
        return;
    const auto& map = manager->getMapName();
    if (map.findIndex("AocField") != -1)
        return;
    const u32 hash = object->getHashId();
    sead::FormatFixedSafeString<128> name("%s_WeaponDrop_%u", map.cstr(), hash);
    manager->setBool(true, name);
}


bool uking::act::Enemy::isWeaponAlreadyDropped() {
    if (!mMapObject)
        return false;
    auto* gdt = ksys::gdt::Manager::instance();
    if (!gdt)
        return false;
    const u32 hash = mMapObject->getHashId();
    sead::FormatFixedSafeString<128> name("%s_WeaponDrop_%u", gdt->getMapName().cstr(), hash);
    bool dropped = false;
    auto& param = gdt->getParam();
    param.get().getBuffer()->getBool(&dropped, name, param.shouldCheckPermissions(), false);
    return dropped;
}

// NON_MATCHING: normal format arguments read the hash after map-name string termination.
bool sub_7100731E70(const ksys::map::Object* object) {
    if (!object)
        return false;
    auto* gdt = ksys::gdt::Manager::instance();
    if (!gdt)
        return false;
    sead::FormatFixedSafeString<128> name("%s_WeaponDrop_%u", gdt->getMapName().cstr(),
                                          object->getHashId());
    bool dropped = false;
    auto& param = gdt->getParam();
    param.get().getBuffer()->getBool(&dropped, name, param.shouldCheckPermissions(), false);
    return dropped;
}

f32 sub_710072D0D8(const sead::Vector3f& vector, f32 value) {
    const f32 length = vector.length();
    if (sead::Mathf::equalsEpsilon(length, 0.0f))
        return sead::Mathf::infinity();
    return sead::Mathf::sqrt(value * 8.0f / length);
}

// NON_MATCHING: the two accessor stack slots are reversed.
bool sub_7100735D2C(const ksys::act::BaseProcLink* link, ksys::act::Actor* actor) {
    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::acquireActor(link, &accessor);
    ksys::act::ActorLinkConstDataAccess target(actor);
    return sub_7100735BF8(accessor, target);
}

// NON_MATCHING: Parameter::ref emits separate object/value address additions.
const sead::SafeString& sub_710072D6D4(ksys::act::Actor* actor, s32 index) {
    switch (index) {
    case 0:
        return actor->getParam()->getRes().mGParamList->getGiantArmorSlot()->mSlot0DefaultActorName.ref();
    case 1:
        return actor->getParam()->getRes().mGParamList->getGiantArmorSlot()->mSlot1DefaultActorName.ref();
    case 2:
        return actor->getParam()->getRes().mGParamList->getGiantArmorSlot()->mSlot2DefaultActorName.ref();
    case 3:
        return actor->getParam()->getRes().mGParamList->getGiantArmorSlot()->mSlot3DefaultActorName.ref();
    default:
        return sead::SafeString::cEmptyString;
    }
}

// NON_MATCHING: Parameter::ref emits separate object/value address additions.
const sead::SafeString& sub_710072D7A0(ksys::act::Actor* actor, s32 index) {
    switch (index) {
    case 0:
        return actor->getParam()->getRes().mGParamList->getNpcEquipment()->mEquipName1.ref();
    case 1:
        return actor->getParam()->getRes().mGParamList->getNpcEquipment()->mEquipName2.ref();
    case 2:
        return actor->getParam()->getRes().mGParamList->getNpcEquipment()->mEquipName3.ref();
    case 3:
        return actor->getParam()->getRes().mGParamList->getNpcEquipment()->mEquipName4.ref();
    default:
        return sead::SafeString::cEmptyString;
    }
}

bool sub_710072CF4C(f32 vertical_speed, f32* speed, f32* time, const sead::Vector3f* start,
                    const sead::Vector3f* target, const sead::Vector3f* gravity) {
    const f32 acceleration = gravity->length();
    const sead::Vector2f displacement(target->x - start->x, target->z - start->z);
    const f32 distance = displacement.length();
    f32 height = start->y;
    *time = 0.0f;
    while (vertical_speed > 0.0f) {
        height += vertical_speed;
        vertical_speed -= acceleration;
        *time += 1.0f;
    }
    bool success = true;
    if (target->y >= height) {
        success = false;
    } else {
        while (height > target->y) {
            *time += 1.0f;
            height += vertical_speed;
            vertical_speed -= acceleration;
        }
    }
    *speed = distance / *time;
    return success;
}

// 0x7100735a6c
// NON_MATCHING: the two scoped accessors occupy opposite stack slots.
bool sub_7100735A6C(ksys::act::Actor* actor, const ksys::act::ActorLinkConstDataAccess& target) {
    ksys::act::ActorLinkConstDataAccess actor_access(actor);
    if (!target.hasTag(ksys::act::tags::AcceptSilentKill))
        return false;
    ksys::act::ActorLinkConstDataAccess target_access;
    target_access.acquireActor(target);
    return !target_access.sub_7100D10FB8() && sub_710001A69C(&target_access, 0x100);
}

void sub_710073278C(ksys::act::Actor* actor, ksys::act::BaseProcLink* link,
                   ksys::phys::RigidBody* body, int flags, int index) {
    ksys::act::Chemical* chemical = nullptr;
    if (body)
        chemical = actor->sub_71011D8A54(body->getHkBodyName());
    if (!chemical)
        chemical = actor->getChemicalStuff();
    if (!chemical || chemical->sub_7100D91080())
        return;
    ksys::act::ActorLinkConstDataAccess target;
    if (link->hasProc()) {
        ksys::act::acquireActor(link, &target);
        if (!target.sub_7100D12F08(-1))
            target.sub_7100D12758(chemical, flags, index);
    }
}

// NON_MATCHING: the original reads the accessor matrix (and its translation) through separate
// getActorMtx calls, one of them discarded; ours reads it once into a reference and the resulting
// frame / register allocation differs.
void sub_71006E3340(DamageReactionRequestResult* result, ksys::act::Actor* actor) {
    if (!result->_d9)
        return;

    if (result->_d8) {
        ksys::act::ActorLinkConstDataAccess accessor;
        sub_7100734E68(&accessor, actor);
        if (accessor.hasProc()) {
            const sead::Matrix34f& mtx = accessor.getActorMtx();
            const f32 scale = accessor.getField418().x;
            sead::Matrix34f transform;
            transform.makeRT(sead::Vector3f(-sead::Mathf::piHalf(), 0, 0),
                             sead::Vector3f(0.15f, -0.2f, 0) * scale);
            result->request.mtx = mtx * transform;
        }
    }

    result->request.mSource.mLink = &result->_c8;
    ksys::act::Reaction::instance()->sub_7100EC10B8(&result->request);
    result->_c8.reset();
    result->_d9 = false;
}

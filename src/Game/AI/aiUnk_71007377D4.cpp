#include <limits>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActorChemicals.h"
#include "Game/gameUnk_71024739d0.h"
#include "Game/Actor/actDragon.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/actHorseRideInfo.h"
#include "KingSystem/ActorSystem/actDropData.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Map/mapPlacementMgr.h"
#include "KingSystem/ActorSystem/actAttackSensor.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
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
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectGiantArmorSlot.h"
#include <math/seadMathCalcCommon.h>

void sub_710072C1B4(ksys::phys::CharacterController* controller, const sead::Vector3f& up) {
    ksys::act::sub_7100EE60AC(controller, up);
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

bool sub_710072FD0C(ksys::act::Actor* actor, const sead::Vector3f& from, const sead::Vector3f& to,
                    sead::Vector3f* out_pos, s32 a5, f32 a6, f32 a7, f32 a8, f32 a9) {
    return sub_710072F28C(actor, from, to, nullptr, out_pos, a5, false, a6, a7, a8);
}

bool sub_710072B8E8(ksys::act::Actor* actor) {
    bool result = false;
    if (auto* manager = sead::DynamicCast<uking::dmg::DamageManager>(actor->getDamageMgr()))
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
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(link, &accessor);
    return accessor.x(idx);
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
    if (auto* info = ksys::act::PlayerInfo::instance()) {
        ksys::act::ActorConstDataAccess accessor;
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

void sub_7100739168(ksys::act::AttackSensor2* sensor) {
    if (sensor)
        sensor->_1c = 4;
}

const ksys::act::ActorAtk::Unk_710079e64c::Unk1* sub_7100739578(ksys::act::Actor* actor) {
    auto* manager = sead::DynamicCast<uking::dmg::DamageManager>(actor->getDamageMgr());
    if (manager && manager->_6c >= 0)
        return sub_71007A255C(actor, manager->_6c);
    if (!sub_71007A2604(actor))
        return nullptr;
    return sub_71007A255C(actor, 0);
}

void sub_7100739108(ksys::act::AttackSensor* sensor) {
    if (sensor)
        sensor->_20 = 0xffff;
}

bool sub_7100732AFC(s32 damage_type) {
    return u32(damage_type - 11) < 3;
}

bool sub_7100732B0C(s32 damage_type) {
    return u32(damage_type - 9) < 2 || damage_type == 14;
}

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
        ksys::act::ActorConstDataAccess accessor;
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
        ksys::act::ActorConstDataAccess accessor;
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

namespace ksys::tera {
// 0x710110b4a4 (declared only; CSV unnamed): terrain height at (x, z), written to `out_height`.
u32 sub_710110B4A4(f32* out_height, const sead::Vector2f* xz, void* tera_system);
// 0x71011094a0 (declared only; CSV unnamed): the terrain height query with two more flags.
u32 sub_71011094A0(f32* out_height, const sead::Vector2f* xz, void* tera_system, s32 a3, s32 a4);
}  // namespace ksys::tera

u32 sub_710072C494(f32* out_height, const sead::Vector3f* pos) {
    auto* placement = ksys::map::PlacementMgr::instance();
    if (!placement)
        return 0;
    void* tera_system = placement->mTeraSystem;
    if (!tera_system)
        return 0;
    const sead::Vector2f xz(pos->x, pos->z);
    return ksys::tera::sub_710110B4A4(out_height, &xz, tera_system);
}

u32 sub_710072C21C(f32* out_height, const sead::Vector3f* pos) {
    auto* placement = ksys::map::PlacementMgr::instance();
    if (!placement)
        return 0;
    void* tera_system = placement->mTeraSystem;
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

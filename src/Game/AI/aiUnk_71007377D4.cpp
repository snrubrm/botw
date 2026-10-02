#include <limits>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/gameUnk_71024739d0.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Physics/System/physHavokAI.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"
#include <math/seadMathCalcCommon.h>

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

void sub_7100737718(ksys::phys::RigidBody* body, const sead::Vector3f& vel) {
    ksys::act::sub_7100EE6268(body, vel);
}

void sub_710073771C(ksys::phys::RigidBody* body, const sead::Vector3f& ang_vel) {
    ksys::act::sub_7100EE62B0(body, ang_vel);
}

// NON_MATCHING: the original copies the translation element-wise into a short-lived local (as an
// out-param getTranslation(pos) inside an inline helper would); ours pairs the stores
bool sub_710072E0A0(ksys::act::Actor* actor, const sead::Vector3f& target,
                    const sead::Matrix34f& mtx, f32 max_dist, f32 min_dy, f32 max_dy, f32 angle,
                    f32 angle_check_dist, f32 y_offset) {
    if (!actor)
        return false;
    if (!sub_710072DEF0(target, max_dist, min_dy, max_dy, mtx.getTranslation(), mtx.getBase(2),
                        angle, angle_check_dist, y_offset)) {
        return false;
    }
    return sub_710072E154(actor, target, nullptr, -1);
}

bool sub_710072E154(ksys::act::Actor* actor, const sead::Vector3f& target, sead::Vector3f* out_pos,
                    s32 a4) {
    const sead::Vector3f from{std::numeric_limits<f32>::quiet_NaN(), std::numeric_limits<f32>::quiet_NaN(), std::numeric_limits<f32>::quiet_NaN()};
    return sub_710072F28C(actor, from, target, nullptr, out_pos, a4, true, -1.0f, -1.0f, -1.0f);
}

bool sub_710072F944(ksys::act::Actor* actor, const sead::Vector3f& target, sead::Vector3f* out_pos,
                    f32 a3, f32 a4) {
    const sead::Vector3f from = actor->getMtx().getTranslation();
    return sub_710072F28C(actor, from, target, nullptr, out_pos, -1, true, a3, a4, -1.0f);
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

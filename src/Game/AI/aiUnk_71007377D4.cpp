#include <limits>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Physics/System/physHavokAI.h"
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

bool sub_710072E154(ksys::act::Actor* actor, const sead::Vector3f& target, sead::Vector3f* out_pos,
                    s32 a4) {
    const sead::Vector3f from{std::numeric_limits<f32>::quiet_NaN(), std::numeric_limits<f32>::quiet_NaN(), std::numeric_limits<f32>::quiet_NaN()};
    return sub_710072F28C(actor, from, target, nullptr, out_pos, a4, true, -1.0f, -1.0f, -1.0f);
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

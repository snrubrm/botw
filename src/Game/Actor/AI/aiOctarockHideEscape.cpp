#include "Game/Actor/AI/aiOctarockHideEscape.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/MathUtil.h"
#include <limits>

// 0x710072f99c (declaration only, as in LynelEscapeFromTarget / EnemyMoveBattle).
bool sub_710072F99C(ksys::act::Actor* actor, const sead::Vector3f& from, const sead::Vector3f& to,
                    sead::Vector3f* hit, s32 a5, f32 a6, f32 a7);

namespace uking::ai {

OctarockHideEscape::OctarockHideEscape(const InitArg& arg) : OctarockHideEscapeBase(arg) {}

OctarockHideEscape::~OctarockHideEscape() = default;

bool OctarockHideEscape::init_(sead::Heap* heap) {
    return OctarockHideEscapeBase::init_(heap);
}

void OctarockHideEscape::enter_(ksys::act::ai::InlineParamPack* params) {
    OctarockHideEscapeBase::enter_(params);
}

void OctarockHideEscape::calc_() {
    OctarockHideEscapeBase::calc_();
}

void OctarockHideEscape::leave_() {
    OctarockHideEscapeBase::leave_();
}

void OctarockHideEscape::loadParams_() {
    OctarockHideEscapeBase::loadParams_();
    getStaticParam(&mEscapeDist_s, "EscapeDist");
}

// NON_MATCHING: stack layout (the original keeps the component addresses of both candidates in stack slots) and
// regalloc
// Searches a point `escape_dist` away from `target_pos`, turning the direction from the target to the actor by
// alternating growing angles (pi / 4 steps, up to pi); keeps the farthest reachable point (the actor position if none).
void OctarockHideEscape::sub_71004EBE08(sead::Vector3f* pos, f32 escape_dist,
                                        const sead::Vector3f& target_pos) {
    const sead::Vector3f actor_pos = mActor->getMtx().getTranslation();
    sead::Vector3f dir{target_pos.x - actor_pos.x, 0.0f, target_pos.z - actor_pos.z};
    dir.normalize();
    if (dir.x == 0.0f && dir.y == 0.0f && dir.z == 0.0f)
        dir = sead::Vector3f::ez;

    f32 best_dist = 0.0f;
    sead::Vector3f best{std::numeric_limits<f32>::quiet_NaN(), std::numeric_limits<f32>::quiet_NaN(),
                        std::numeric_limits<f32>::quiet_NaN()};
    f32 angle = 0.0f;
    f32 step = sead::Mathf::pi() / 4;
    do {
        sead::Vector3f target = dir;
        ksys::util::sub_71011EF010(&target, angle);
        target *= escape_dist;
        target += target_pos;
        sead::Vector3f hit;
        const bool reached = sub_710072F99C(mActor, actor_pos, target, &hit, -1, -1.0f, -1.0f);
        const sead::Vector3f* candidate;
        f32 dist;
        if (reached) {
            candidate = &target;
            dist = escape_dist;
        } else {
            candidate = &hit;
            const f32 dx = hit.x - target_pos.x;
            const f32 dz = hit.z - target_pos.z;
            dist = sead::Mathf::sqrt(dx * dx + dz * dz);
        }
        if (best_dist < dist) {
            best = *candidate;
            best_dist = dist;
            if (reached)
                break;
        }
        angle += step;
        step = -((step >= 0.0f ? 1.0f : -1.0f) * (sead::Mathf::abs(step) + sead::Mathf::pi() / 4));
    } while (sead::Mathf::abs(angle) <= sead::Mathf::pi());

    if (best.isNan())
        *pos = actor_pos;
    else
        *pos = best;
}

void OctarockHideEscape::m35() {
    sub_71004ECB04();
    sead::Vector3f pos;
    sub_71004EBE08(&pos, *mEscapeDist_s, *mTargetPos_d);
    _68 = pos;
    ksys::act::ai::InlineParamPack params;
    params.addVec3(pos, "TargetPos", -1);
    changeChild("移動", &params);
}

}  // namespace uking::ai

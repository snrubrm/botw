#include "Game/AI/AI/aiCircleMove.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/System/VFR.h"
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>
#include "KingSystem/Utils/MathUtil.h"

namespace uking::ai {

CircleMove::CircleMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

CircleMove::~CircleMove() = default;

bool CircleMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void CircleMove::sub_710034E838() {
    sead::Vector3f target;
    sub_710034EEB0(&target);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(target, "TargetPos", -1);
    changeChild("遠ざかり", &pack);
}

// NON_MATCHING: same code, but the x / z of the horizontal front vector live in swapped float registers (s8 / s10)
// The point on the circle (radius m37()) around m34()'s center in the direction of the actor.
void CircleMove::sub_710034EEB0(sead::Vector3f* out) {
    if (!out)
        return;
    sead::Vector3f center;
    m34(&center);
    sead::Vector3f dir;
    sead::Vector3f diff(mActor->getMtx().getTranslation().x - center.x, 0.0f,
                        mActor->getMtx().getTranslation().z - center.z);
    if (diff.length() > 0.0f) {
        diff.normalize();
        dir = diff;
    } else {
        sead::Vector3f front;
        mActor->getMtx().getBase(front, 2);
        front.normalize();
        const sead::Vector2f xz(front.x, front.z);
        if (xz.length() > 0.0f) {
            dir.set(xz.x, 0.0f, xz.y);
            dir.normalize();
        } else {
            dir.set(0.0f, 0.0f, 1.0f);
        }
    }
    *out = center + dir * m37();
}

void CircleMove::enter_(ksys::act::ai::InlineParamPack* params) {
    _5c = 1.0f;
    sead::Vector3f offset;
    m34(&offset);
    offset = mActor->getMtx().getTranslation() - offset;
    const f32 distance = sead::Vector2f(offset.x, offset.z).length();
    const f32 difference = distance - m37();
    if (sead::Mathf::abs(difference) > *mRadiusMargin_s) {
        if (difference < 0.0f) {
            sub_710034E838();
        } else {
            sead::Vector3f target;
            m34(&target);
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(target, "TargetPos", -1);
            changeChild("近づき", &pack);
        }
    } else {
        sub_710034E90C(false);
    }
}

void CircleMove::sub_710034E90C(bool keep_direction) {
    sead::Vector3f center;
    m34(&center);
    sead::Vector3f direction(mActor->getMtx().getTranslation().x - center.x, 0.0f,
                             mActor->getMtx().getTranslation().z - center.z);
    direction.normalize();
    _58 = sead::Mathf::atan2(direction.x, direction.z);
    if (!keep_direction)
        sub_710034F16C(_58);
    const f32 speed = *mSpeed_s;
    const f32 radius = m37();
    _58 += _5c * (speed / radius) * ksys::VFR::instance()->getDeltaFrame();
    _58 -= sead::Mathf::floor(_58 * (1.0f / sead::Mathf::pi2())) * sead::Mathf::pi2();
    const f32 angle = _58 >= sead::Mathf::pi2() ? 0.0f : _58;
    _58 = angle;
    sead::Vector3f target;
    m38(&target, angle, m37());
    m35(target);
}

void CircleMove::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (child->isFinished())
            sub_710034E90C(false);
        else
            setFailed();
    } else if (child->isChangeable()) {
        if (isCurrentChild("近づき")) {
            sead::Vector3f offset;
            m34(&offset);
            offset = mActor->getMtx().getTranslation() - offset;
            const f32 distance = sead::Vector2f(offset.x, offset.z).length();
            const f32 difference = distance - m37();
            if (difference < 0.0f || !(sead::Mathf::abs(difference) > *mRadiusMargin_s)) {
                sub_710034E90C(false);
                return;
            }
        } else if (isCurrentChild("遠ざかり")) {
            sead::Vector3f offset;
            m34(&offset);
            offset = mActor->getMtx().getTranslation() - offset;
            const f32 distance = sead::Vector2f(offset.x, offset.z).length();
            const f32 difference = distance - m37();
            if (!(difference < 0.0f && sead::Mathf::abs(difference) > *mRadiusMargin_s)) {
                sub_710034E90C(false);
                return;
            }
        }
    }
    if (isCurrentChild("移動")) {
        const f32 speed = *mSpeed_s;
        const f32 radius = m37();
        _58 += _5c * (speed / radius) * ksys::VFR::instance()->getDeltaFrame();
        _58 -= sead::Mathf::floor(_58 * (1.0f / sead::Mathf::pi2())) * sead::Mathf::pi2();
        const f32 angle = _58 >= sead::Mathf::pi2() ? 0.0f : _58;
        _58 = angle;
        sead::Vector3f target;
        m38(&target, angle, m37());
        m36(target);
    } else if (isCurrentChild("近づき")) {
        sead::Vector3f target;
        m34(&target);
        child->setDynamicParam(target, "TargetPos");
    } else if (isCurrentChild("遠ざかり")) {
        sead::Vector3f target;
        sub_710034EEB0(&target);
        child->setDynamicParam(target, "TargetPos");
    }
}

void CircleMove::leave_() {
    ksys::act::ai::Ai::leave_();
}

void CircleMove::loadParams_() {
    getStaticParam(&mDirection_s, "Direction");
    getStaticParam(&mRadius_s, "Radius");
    getStaticParam(&mRadiusMargin_s, "RadiusMargin");
    getStaticParam(&mSpeed_s, "Speed");
}

void CircleMove::m35(const sead::Vector3f& target_pos) {
    ksys::act::ai::InlineParamPack params;
    params.addVec3(target_pos, "TargetPos", -1);
    changeChild("移動", &params);
}

void CircleMove::m36(const sead::Vector3f& target_pos) {
    getCurrentChild()->setDynamicParam(target_pos, "TargetPos");
}

void CircleMove::m38(sead::Vector3f* out, f32 angle, f32 radius) {
    if (!out)
        return;
    m34(out);
    out->x += sead::Mathf::sin(angle) * radius;
    out->z += sead::Mathf::cos(angle) * radius;
}

// NON_MATCHING: vector temporaries, direct actor access, and direction comparison scheduling differ.
void CircleMove::sub_710034F16C(f32 angle) {
    s32 direction = *mDirection_s;
    if (direction == 3) {
        const auto position = mActor->getMtx().getTranslation();
        const f32 radius = m37();
        direction = 2;
        if (radius > 0.0f) {
            const f32 speed = *mSpeed_s / radius;
            const f32 step = speed > 0.0f ? speed : -speed;
            f32 next = angle + step;
            next -= sead::Mathf::floor(next * (1.0f / sead::Mathf::pi2())) * sead::Mathf::pi2();
            if (next >= sead::Mathf::pi2())
                next = 0.0f;
            sead::Vector3f forward;
            m38(&forward, next, radius);
            f32 previous = angle - step;
            previous -= sead::Mathf::floor(previous * (1.0f / sead::Mathf::pi2())) * sead::Mathf::pi2();
            if (previous >= sead::Mathf::pi2())
                previous = 0.0f;
            sead::Vector3f reverse;
            m38(&reverse, previous, radius);
            forward -= position;
            reverse -= position;
            sead::Vector3f facing;
            facing.setRotated(mActor->getMtx(), sead::Vector3f(0.0f, 0.0f, 1.0f));
            sead::Vector3f axis;
            f32 forward_angle = 0.0f;
            f32 reverse_angle = 0.0f;
            ksys::util::sub_71011EEB08(&axis, &forward_angle, facing, forward, sead::Vector3f::ey);
            ksys::util::sub_71011EEB08(&axis, &reverse_angle, facing, reverse, sead::Vector3f::ey);
            direction = reverse_angle < forward_angle ? 1 : 2;
            if (!(reverse_angle <= forward_angle))
                direction = 0;
        }
    }
    if (direction == 2)
        direction = sead::GlobalRandom::instance()->getU32() & 1;
    _5c = direction == 1 ? -1.0f : 1.0f;
}

}  // namespace uking::ai

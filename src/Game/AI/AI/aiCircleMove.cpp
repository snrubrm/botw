#include "Game/AI/AI/aiCircleMove.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/System/VFR.h"
#include <math/seadMathCalcCommon.h>

namespace uking::ai {

CircleMove::CircleMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

CircleMove::~CircleMove() = default;

bool CircleMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: Direct margin branches and vector stack placement differ from the original.
void CircleMove::sub_710034E838() {
    sead::Vector3f target;
    sub_710034EEB0(&target);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(target, "TargetPos", -1);
    changeChild("遠ざかり", &pack);
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

// NON_MATCHING: Virtual-table loads and shared margin branches differ from the original.
void CircleMove::sub_710034E90C(bool keep_direction) {
    sead::Vector3f center;
    m34(&center);
    sead::Vector3f direction(mActor->getMtx().getTranslation().x - center.x, 0.0f,
                             mActor->getMtx().getTranslation().z - center.z);
    direction.normalize();
    _58 = sead::Mathf::atan2(direction.x, direction.z);
    if (!keep_direction)
        sub_710034F16C();
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

}  // namespace uking::ai

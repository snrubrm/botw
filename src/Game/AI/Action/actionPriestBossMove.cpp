#include "Game/AI/Action/actionPriestBossMove.h"
#include <algorithm>
#include "Game/AI/aiUnk_71007320F0.h"
#include "Game/AI/aiUnk_7100742478.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/System/physHavokAI.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

PriestBossMove::PriestBossMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

PriestBossMove::~PriestBossMove() = default;

void PriestBossMove::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* controller = mActor->getCharacterController();
    if (!controller)
        return;
    _d0 = sead::Vector2f(mActor->getVelocity().x, mActor->getVelocity().z).length();
    sub_7100741034(&_f0, mActor);
    _d4 = *mInitRotSpd_s;
    _12c = *mMaxRotSpd_s;
    mActor->getMtx().getTranslation(_114);
    _120.set(*mMoveTargetPos_d);
    _120 -= mActor->getMtx().getTranslation();
    _120.normalize();
    controller->sub_7100F60AE0();
    sub_7100737708(controller, _d0);
    _130 = true;
    bool b = true;
    if (mActor->m45())
        b = (mActor->m45()->_2a4 & 0xffff) != 5;
    _131 = b;
    _d8 = ksys::Timer(0.0f, 0.0f, 1.0f);
    _e4 = ksys::Timer(0.0f, 0.0f, 1.0f);
    if (!mASName_s.isEmpty())
        playAS(mASName_s.cstr(), true, 0, 0, -1.0f);
    mFlags.set(Flag::Changeable);
}

void PriestBossMove::leave_() {
    ksys::act::ai::Action::leave_();
}

void PriestBossMove::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mWallHitLimitTime_s, "WallHitLimitTime");
    getStaticParam(&mMoveAngCliffLimitTime_s, "MoveAngCliffLimitTime");
    getStaticParam(&mNotMoveLimitTime_s, "NotMoveLimitTime");
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mAccRatio_s, "AccRatio");
    getStaticParam(&mInitRotSpd_s, "InitRotSpd");
    getStaticParam(&mAccRotSpd_s, "AccRotSpd");
    getStaticParam(&mMaxRotSpd_s, "MaxRotSpd");
    getStaticParam(&mFinRadius_s, "FinRadius");
    getStaticParam(&mFinRotate_s, "FinRotate");
    getStaticParam(&mFrontCliffDistance_s, "FrontCliffDistance");
    getStaticParam(&mFrontCliffAngle_s, "FrontCliffAngle");
    getStaticParam(&mJumpUpSpeedReduceRatio_s, "JumpUpSpeedReduceRatio");
    getStaticParam(&mNotMoveDistanceThreshold_s, "NotMoveDistanceThreshold");
    getStaticParam(&mFollowGround_s, "FollowGround");
    getStaticParam(&mIgnoreLastCurve_s, "IgnoreLastCurve");
    getStaticParam(&mIgnoreDecelerationFrontCliff_s, "IgnoreDecelerationFrontCliff");
    getStaticParam(&mIgnoreMoveDirCoHit_s, "IgnoreMoveDirCoHit");
    getStaticParam(&mASName_s, "ASName");
    getDynamicParam(&mMoveTargetPos_d, "MoveTargetPos");
}

// NON_MATCHING: register allocation / load order (the original loads `*mAccRatio_s` after |cur - target| and
// `*speed` after the delta-time lookup of the final clamp).
void PriestBossMove::sub_71000679D0(f32* speed, f32 cur, f32 threshold, f32 dist, f32 angle,
                                    bool a, bool b) {
    if (a && !b && !*mIgnoreDecelerationFrontCliff_s) {
        ksys::VFR::multiply(speed, 0.4f);
    } else {
        f32 target;
        f32 rate;
        if (angle > 0 && !*mIgnoreLastCurve_s && _d4 > 0 && dist / angle < cur / _d4) {
            target = _d4 * dist * 0.5f;
            rate = sead::Mathf::abs(cur - target) * 0.5f;
        } else {
            target = cur + cur + threshold > dist ? *mSpeed_s * 0.5f : *mSpeed_s;
            rate = *mAccRatio_s * sead::Mathf::abs(cur - target);
        }
        ksys::VFR::chase(speed, target, rate);
    }
    *speed = sead::Mathf::clampMax(*speed, dist / ksys::VFR::instance()->getDeltaFrame());
}

void PriestBossMove::m32(sead::Vector3f* forward) {
    mActor->getMtx().getBase(*forward, 2);
    forward->normalize();
    forward->y = 0;
    forward->normalize();
}

void PriestBossMove::m33() {
    setFinished();
}

void PriestBossMove::m34(ksys::phys::CharacterController* controller, const sead::Vector3f& dir) {
    sub_7100741038(&_f0, mActor);
    _d4 += *mAccRotSpd_s * ksys::VFR::instance()->getDeltaFrame();
    _d4 = sead::Mathf::clampMax(_d4, *mMaxRotSpd_s);
    sead::Vector3f up;
    if (!*mFollowGround_s || !controller->sub_7100F5F234(&up))
        up = getReverseDirOrUp(controller->get70());
    sead::Matrix34f mtx;
    ksys::util::sub_71011F00EC(&mtx, dir, up, sead::Vector3f::zero, true);
    sub_710074149C(&_f0, mtx, 1.0f, _d4, 0.0f);
    sub_71007419F4(_f0, controller);
}

s32 PriestBossMove::m35(f32 distance, const sead::Vector3f& dir, const sead::Vector3f& pos) {
    auto* havok = ksys::phys::HavokAI::instance();
    if (!havok)
        return true;
    const f32 d = std::min(*mFrontCliffDistance_s, distance);
    sead::Vector3f point;
    sead::Vector3f end;
    end.setScaleAdd(d, dir, pos);
    if (sub_7100742588(&point, mActor->m45(), &end, 10.0f) || !_131)
        return true;
    point.setScaleAdd(0.5f, dir, point);
    sead::Vector3f from = point;
    sead::Vector3f to = point;
    from.y += 1.0f;
    to.y -= 1.0f;
    {
        ksys::phys::Unk_7100f7e9f0 result = havok->sub_7100F87A80(&point, from, to);
        if (result.sub_7100F7EB40() && result.sub_7100F7EEE4() == 5)
            return false;
    }
    return true;
}

bool PriestBossMove::m36(const sead::Vector3f& dir) {
    if (!isLandedMaybe(mActor, false))
        return false;
    const auto* contact = sub_71007A471C(mActor, 0);
    return dir.dot(contact->_c) < 0;
}

// NON_MATCHING: the original loads the actor and `_114` x / z in a different order for the distance.
bool PriestBossMove::m37() {
    if (!_130 && sub_71007A4178(mActor, false) && !(*mNotMoveDistanceThreshold_s < 0)) {
        const f32 dist = sead::Vector2f(mActor->getMtx().m[0][3] - _114.x,
                                        mActor->getMtx().m[2][3] - _114.z)
                             .length();
        if (dist < ksys::VFR::instance()->getDeltaFrame() * *mNotMoveDistanceThreshold_s) {
            _e4.update();
            if (_e4.value > f32(*mNotMoveLimitTime_s))
                return true;
        } else {
            _e4 = ksys::Timer(0.0f, 0.0f, 1.0f);
        }
    }
    return false;
}

// NON_MATCHING: the original loads `angle` (the sub_71011EEB08 result) into a callee-saved register before
// the sub_71007320F0 call and sets up the sub_71000679D0 arguments in a different order.
void PriestBossMove::calc_() {
    auto* controller = mActor->getCharacterController();
    if (!controller)
        return;
    sead::Vector3f axis;
    f32 angle;
    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    const sead::Vector3f up = getReverseDirOrUp(controller->get70());
    sead::Vector3f to_target = *mMoveTargetPos_d;
    to_target -= pos;
    ksys::util::sub_71011EFA00(&to_target, to_target, up);
    const f32 dist = to_target.normalize();
    sead::Vector3f forward;
    m32(&forward);
    _120 = to_target;
    sead::Vector3f steer = to_target;
    if (!*mIgnoreMoveDirCoHit_s && sub_71007A4178(mActor, false)) {
        axis.set(sub_71007A40D0(mActor, 0)->_c);
        ksys::util::sub_71011EFA00(&axis, axis, up);
        axis.normalize();
        if ((-axis).dot(to_target) >= sead::Mathf::cos(sead::Mathf::deg2rad(85))) {
            axis.set(-axis.z, axis.y, axis.x);
            if (!m35(1.0f, axis, pos))
                steer = axis;
        }
    }
    const s32 state = m35(dist, forward, pos);
    s32 cliff = state;
    if (*mFrontCliffAngle_s < 0 || !(to_target.dot(forward) >= sead::Mathf::cos(*mFrontCliffAngle_s)))
        cliff = 1;
    const bool landed = m36(to_target);
    if (cliff == 0 || landed)
        _d8.update();
    else if (cliff != 2)
        _d8 = ksys::Timer(0.0f, 0.0f, 1.0f);
    if (_d8.value > f32(*mWallHitLimitTime_s) ||
        (cliff != 1 && _d8.value > f32(*mMoveAngCliffLimitTime_s)) || m37()) {
        setFailed();
        return;
    }
    ksys::util::sub_71011EEB08(&axis, &angle, forward, to_target, sead::Vector3f::ey);
    const f32 threshold = *mFinRadius_s + sub_71007320F0(mActor, *mWeaponIdx_s);
    m34(controller, steer);
    if (*mJumpUpSpeedReduceRatio_s < 1.0f)
        sub_710073852C(controller, *mJumpUpSpeedReduceRatio_s);
    sub_71000679D0(&_d0, _d0, threshold, dist, angle, state == 0, landed);
    sub_710073770C(controller, _d0, forward);
    if (dist <= 0.00001f) {
        m33();
    } else if (dist < threshold &&
               (_120.dot(to_target) >= -0.8660254f || angle <= *mFinRotate_s)) {
        m33();
    }
    _114 = pos;
    _130 = false;
}

}  // namespace uking::action

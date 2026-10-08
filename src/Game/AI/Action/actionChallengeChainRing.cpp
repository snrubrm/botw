#include "Game/AI/Action/actionChallengeChainRing.h"
#include <cfloat>
#include <cmath>
#include <math/seadMathCalcCommon.h>
#include <math/seadMatrix.h>
#include "Game/AI/aiUnk_71024f15c0.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Map/mapRail.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/System/VFR.h"

namespace uking::action {

ChallengeChainRing::ChallengeChainRing(const InitArg& arg) : FollowChallenge(arg) {}

ChallengeChainRing::~ChallengeChainRing() = default;

bool ChallengeChainRing::init_(sead::Heap* heap) {
    if (!FollowChallenge::init_(heap))
        return false;

    _b70 = *mIsFirstNode_m;
    _b78 = new (heap) Unk_71024f15c0;
    ksys::gdt::resetFlag_BalladOfHeroes_ChainRing_Running(false);
    return true;
}

void ChallengeChainRing::enter_(ksys::act::ai::InlineParamPack* params) {
    FollowChallenge::enter_(params);
}

void ChallengeChainRing::leave_() {
    FollowChallenge::leave_();
}

void ChallengeChainRing::loadParams_() {
    FollowChallenge::loadParams_();
    getMapUnitParam(&mChainRingOrbitSpeed_m, "ChainRingOrbitSpeed");
    getMapUnitParam(&mIsFirstNode_m, "IsFirstNode");
}

void ChallengeChainRing::calc_() {
    FollowChallenge::calc_();
}

void ChallengeChainRing::m34(const sead::Vector3f& pos, const sead::Vector3f& dir) {
    const sead::Vector3f up_axis = sead::Vector3f::ey;
    sead::Vector3f front = dir;
    front.normalize();
    sead::Vector3f side;
    side.setCross(up_axis, front);
    side.normalize();
    sead::Vector3f up;
    up.setCross(front, side);
    up.normalize();

    sead::Matrix34f mtx;
    mtx.setBase(0, side);
    mtx.setBase(1, up);
    mtx.setBase(2, front);
    mtx.setBase(3, pos);
    if (auto* body = mActor->getMainBody())
        body->setTransform(mtx, ksys::phys::PropagateToLinkedMotions{true});
    mActor->actorPhysicsSetFlag2();
}

void ChallengeChainRing::m35(sead::Vector3f* pos) {
    if (pos)
        pos->set(_b78->_30.sub_7100EEB370());
}

// NON_MATCHING: head/VFR/loop/timer-check/rail-clamp/normalize tail all match; differs only
// in backend choices: prev is reloaded at loop top from x0 instead of kept in s12-s14
// (pre-loop copy folded, refresh folded into top reload), and the rail progress fadd targets
// s9 instead of s8 (cascades into a skipped zeroing mov and fcsel branches in the open leg)
void ChallengeChainRing::m33() {
    if (_b78->_8.rail == nullptr)
        return;

    const f32 curSpeed = _b50;
    if (_b4c > _b58)
        _b50 = curSpeed + (_b5c - curSpeed) * 0.5f * *mChainRingOrbitSpeed_m;

    const f32 speed = _b50 * ksys::VFR::instance()->getDeltaFrame();
    const sead::Vector3f* pos = &_b78->_30.sub_7100EEB370();
    _b4c += speed;
    sead::Vector3f prev;
    prev = *pos;
    if (speed > 0.0f) {
        f32 total = 0.0f;
        do {
            const f32 step = fminf(speed - total, 0.01f);
            if (step < sub_7100EEBE90())
                break;
            _b78->x(step);
            if (_b78->m3())
                break;
            pos = &_b78->_30.sub_7100EEB370();
            total += (*pos - prev).length();
            pos = &_b78->_30.sub_7100EEB370();
            prev = *pos;
        } while (total < speed);
    }

    if (!(_b8c.value <= FLT_EPSILON)) {
        _b8c.update();
        return;
    }

    ksys::map::Rail* rail = _b78->_8.rail;
    f32 progress = 0.0f;
    if (rail) {
        const f32 base = _b78->_8.progress;
        if (rail->getNumPoints() >= 1) {
            progress = base + 0.01f;
            const bool closed = rail->isClosed();
            const f32 count = rail->getNumPoints();
            if (closed) {
                const f32 max = sead::Mathf::clampMin(count - FLT_EPSILON, 0.0f);
                if (progress < 0.0f) {
                    do {
                        progress += max;
                    } while (progress < 0.0f);
                } else {
                    while (progress > max)
                        progress -= max;
                }
            } else {
                if (progress < 0.0f) {
                    progress = 0.0f;
                } else {
                    const f32 max = sead::Mathf::clampMin(count - 1.0f, 0.0f);
                    if (max < progress)
                        progress = max;
                }
            }
        }
    }

    sead::Vector3f dir;
    _b78->_8.rail->calcTranslate(&dir, progress);
    dir -= _b78->_8.sub_7100EEB370();
    dir.normalize();
    _b80 = dir;
    _b8c = ksys::Timer(3.0f, 3.0f);
}

}  // namespace uking::action

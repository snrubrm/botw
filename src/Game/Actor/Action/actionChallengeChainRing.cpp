#include "Game/Actor/Action/actionChallengeChainRing.h"
#include <cfloat>
#include <cmath>
#include <math/seadMathCalcCommon.h>
#include <math/seadMatrix.h>
#include "Game/Actor/aiUnk_71024f15c0.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Map/mapRail.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/System/VFR.h"

namespace uking::action {

ChallengeChainRing::ChallengeChainRing(const InitArg& arg) : AppearFollowChallenge(arg) {}

ChallengeChainRing::~ChallengeChainRing() = default;

bool ChallengeChainRing::init_(sead::Heap* heap) {
    if (!AppearFollowChallenge::init_(heap))
        return false;

    _b70 = *mIsFirstNode_m;
    _b78 = new (heap) Unk_71024f15c0;
    ksys::gdt::resetFlag_BalladOfHeroes_ChainRing_Running(false);
    return true;
}

void ChallengeChainRing::enter_(ksys::act::ai::InlineParamPack* params) {
    AppearFollowChallenge::enter_(params);
}

void ChallengeChainRing::leave_() {
    AppearFollowChallenge::leave_();
}

void ChallengeChainRing::loadParams_() {
    AppearFollowChallenge::loadParams_();
    getMapUnitParam(&mChainRingOrbitSpeed_m, "ChainRingOrbitSpeed");
    getMapUnitParam(&mIsFirstNode_m, "IsFirstNode");
}

void ChallengeChainRing::calc_() {
    AppearFollowChallenge::calc_();
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

// NON_MATCHING: register allocation, clamp scheduling and shared branch layout differ.
bool ChallengeChainRing::sub_7100051DF4(ksys::map::Rail* rail, sead::Vector3f* pos,
                                       sead::Vector3f* direction, f32 progress) {
    if (!rail || rail->getNumPoints() < 2)
        return false;

    if (rail->getNumPoints() < 1) {
        progress = 0.0f;
    } else {
        const bool closed = rail->isClosed();
        const f32 count = rail->getNumPoints();
        if (closed) {
            const f32 max = sead::Mathf::clampMin(count - FLT_EPSILON, 0.0f);
            if (progress < 0.0f) {
                do {
                    progress += max;
                } while (progress < 0.0f);
            } else {
                while (max < progress)
                    progress -= max;
            }
        } else if (progress < 0.0f) {
            progress = 0.0f;
        } else {
            const f32 max = sead::Mathf::clampMin(count - 1.0f, 0.0f);
            if (max < progress)
                progress = max;
        }
    }
    rail->calcTranslate(pos, progress);
    f32 next_progress = progress + 0.1f;
    bool forward = rail->isClosed();
    if (!forward) {
        const bool closed = rail->isClosed();
        const s32 count = rail->getNumPoints();
        const f32 max = sead::Mathf::clampMin(
            closed ? f32(count) - FLT_EPSILON : f32(count - 1), 0.0f);
        forward = !(next_progress < 0.0f || max < next_progress);
    }
    sead::Vector3f dir;
    if (forward) {
        if (rail->getNumPoints() < 1) {
            next_progress = 0.0f;
        } else {
            const bool closed = rail->isClosed();
            const f32 count = rail->getNumPoints();
            if (closed) {
                const f32 max = sead::Mathf::clampMin(count - FLT_EPSILON, 0.0f);
                if (next_progress < 0.0f) {
                    do {
                        next_progress += max;
                    } while (next_progress < 0.0f);
                } else {
                    while (max < next_progress)
                        next_progress -= max;
                }
            } else if (next_progress < 0.0f) {
                next_progress = 0.0f;
            } else {
                const f32 max = sead::Mathf::clampMin(count - 1.0f, 0.0f);
                if (max < next_progress)
                    next_progress = max;
            }
        }
        dir = rail->calcTranslate(next_progress) - *pos;
        dir.normalize();
    } else {
        progress -= 0.1f;
        const bool closed = rail->isClosed();
        const s32 count = rail->getNumPoints();
        const f32 max = sead::Mathf::clampMin(
            closed ? f32(count) - FLT_EPSILON : f32(count - 1), 0.0f);
        if (progress < 0.0f || max < progress) {
            const sead::Vector3f first = rail->calcTranslate(0.0f);
            dir = rail->calcTranslate(rail->getNumPoints() - 1) - first;
            dir.normalize();
        } else {
            dir = *pos - rail->calcTranslate(progress);
            dir.normalize();
        }
    }
    *direction = dir;
    if (std::isnan(dir.x) || std::isnan(dir.y) || std::isnan(dir.z) ||
        (dir.x == 0.0f && dir.y == 0.0f && dir.z == 0.0f)) {
        *direction = mActor->getMtx().getBase(2);
        return false;
    }
    return true;
}

}  // namespace uking::action

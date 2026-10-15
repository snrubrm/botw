#include "Game/Actor/AI/aiAnimalRndMove.h"
#include "Game/Actor/aiUnk_71006F1DF0.h"
#include <math/seadMathCalcCommon.h>
#include <math/seadQuat.h>
#include <cmath>
#include "Game/Actor/actRideable.h"
#include <thread/seadMutex.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::ai {

// NON_MATCHING: scheduling / registers of the territory distance test
bool AnimalRndMove::sub_710030AE5C() {
    f32 radius = *mSearchNextPathRadius_s;
    auto* nav = mActor->m45();
    if (radius < sead::Mathf::epsilon() || !nav)
        return false;

    const f32 territory = *mTerritoryArea_m;
    if (territory > 0.0f && _a4) {
        sead::Vector3f home;
        mActor->getHomePos(&home);
        bool in_territory;
        {
            auto lock = sead::makeScopedLock(nav->_1e0);
            if (nav->_194.isNan())
                return true;
            in_territory = (nav->_194 - home).squaredLength() < sead::Mathf::square(territory * 1.1f);
        }
        if (!in_territory)
            return true;
        radius = sead::Mathf::min(radius, territory * 0.4f);
    }

    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    auto lock = sead::makeScopedLock(nav->_1e0);
    if (nav->_194.isNan())
        return false;
    return (nav->_194 - pos).squaredLength() < radius * radius;
}

bool AnimalRndMove::sub_710030B070(const sead::Vector3f& pos) {
    if (*mEnableNoEntryAreaCheck_m)
        return sub_71006F1DF0(mActor, pos);
    return false;
}

AnimalRndMove::AnimalRndMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

AnimalRndMove::~AnimalRndMove() = default;

bool AnimalRndMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void AnimalRndMove::enter_(ksys::act::ai::InlineParamPack* params) {
    _a0 = 0;
    _a4 = true;
    if (auto* nav = mActor->m45())
        nav->sub_7100F7604C(0.5f);
}

void AnimalRndMove::calc_() {}

void AnimalRndMove::leave_() {
    ksys::act::ai::Ai::leave_();
}

void AnimalRndMove::loadParams_() {
    getStaticParam(&mSearchNextPathRadius_s, "SearchNextPathRadius");
    getStaticParam(&mRadiusLimit_s, "RadiusLimit");
    getStaticParam(&mForwardDirDistCoefficient_s, "ForwardDirDistCoefficient");
    getStaticParam(&mDirRandomMinRatio_s, "DirRandomMinRatio");
    getStaticParam(&mDirRangeAngle_s, "DirRangeAngle");
    getStaticParam(&mRejectDistRatio_s, "RejectDistRatio");
    getStaticParam(&mContinueAddSearchAngle_s, "ContinueAddSearchAngle");
    getStaticParam(&mContinueReduceDistRatio_s, "ContinueReduceDistRatio");
    getStaticParam(&mContinueReduceRejectDistRatio_s, "ContinueReduceRejectDistRatio");
    getMapUnitParam(&mTerritoryArea_m, "TerritoryArea");
    getMapUnitParam(&mEnableNoEntryAreaCheck_m, "EnableNoEntryAreaCheck");
    getAITreeVariable(&mFramesStuckOnTerrain_a, "FramesStuckOnTerrain");
    getAITreeVariable(&mIsStuckOnTerrain_a, "IsStuckOnTerrain");
}

// NON_MATCHING: quaternion cap, normalization and navigation-state temporary scheduling differ.
bool AnimalRndMove::m34(const sead::Vector3f* pos) {
    auto* nav = mActor->m45();
    if (!nav)
        return false;
    f32 radius = *mRadiusLimit_s;
    f32 angle = *mDirRangeAngle_s;
    f32 reject_ratio = *mRejectDistRatio_s;
    if (_a0 >= 1) {
        u8 state;
        {
            auto lock = sead::makeScopedLock(nav->_1e0);
            state = nav->_294;
        }
        if (state == 2)
            _a0 = 0;
        angle += *mContinueAddSearchAngle_s * f32(_a0);
        // Retain an unordered angle rather than replacing it with the finite upper bound.
        if (angle > 6.2831855f)
            angle = 6.2831855f;
        radius *= std::pow(*mContinueReduceDistRatio_s, f32(_a0));
        reject_ratio *= std::pow(*mContinueReduceRejectDistRatio_s, f32(_a0));
    }
    ++_a0;
    sead::Vector3f direction;
    mActor->getMtx().getBase(direction, 2);
    if (pos)
        direction = *pos;
    u8 state;
    {
        auto lock = sead::makeScopedLock(nav->_1e0);
        state = nav->_294;
    }
    if ((state | 1) == 5)
        nav->sub_7100F76790();
    if (*mTerritoryArea_m > 0.0f && _a4) {
        sead::Vector3f home;
        mActor->getHomePos(&home);
        const auto position = mActor->getMtx().getTranslation();
        const sead::Vector2f delta(home.x - position.x, home.z - position.z);
        if (delta.length() > *mTerritoryArea_m * 0.7f) {
            direction.set(home.x - position.x, 0.0f, home.z - position.z);
            if (direction.normalize() == 0.0f) {
                mActor->getMtx().getBase(direction, 2);
                direction.y = 0.0f;
                if (direction.normalize() == 0.0f)
                    direction = sead::Vector3f::ez;
            }
            sead::Vector3f forward;
            mActor->getMtx().getBase(forward, 2);
            const f32 dot = direction.dot(forward);
            // An unordered dot follows the native quaternion path as well.
            if (!(dot + 1.0f <= sead::Mathf::epsilon())) {
                sead::Quatf rotation;
                if (dot < 0.4999999701976776f) {
                    const auto cross = direction.cross(forward);
                    const f32 scale = 0.866025447845459f / sead::Mathf::sqrt(1.0f - dot * dot) *
                                      0.5773502588272095f;
                    rotation.set(0.8660253882408142f, cross.x * scale, cross.y * scale,
                                 cross.z * scale);
                } else {
                    rotation.makeVectorRotation(direction, forward);
                }
                auto rotated = direction;
                rotated.rotate(rotation);
                rotated.y = 0.0f;
                if (rotated.normalize() != 0.0f)
                    direction = rotated;
            }
            reject_ratio = 0.6f;
            angle = 2.6179938316345215f;
        }
        radius = radius < *mTerritoryArea_m ? radius : *mTerritoryArea_m;
    }
    return act::sub_7100E816E4(angle, radius, *mDirRandomMinRatio_s,
                              *mForwardDirDistCoefficient_s, reject_ratio, mActor, direction);
}

bool AnimalRndMove::m35() {
    if (auto* nav = mActor->m45()) {
        nav->_1e0.lock();
        const u8 state = nav->_294;
        nav->_1e0.unlock();
        if (state == 1)
            return true;
    }
    return false;
}

}  // namespace uking::ai

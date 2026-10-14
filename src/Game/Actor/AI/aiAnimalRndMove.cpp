#include "Game/Actor/AI/aiAnimalRndMove.h"
#include "Game/Actor/aiUnk_71006F1DF0.h"
#include <math/seadMathCalcCommon.h>
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

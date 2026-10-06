#include "Game/AI/AI/aiAnimalRoamBase.h"
#include "Game/AI/aiUnk_71006F1DF0.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::ai {

bool AnimalRoamBase::sub_710030B070(const sead::Vector3f& pos) {
    if (*mEnableNoEntryAreaCheck_m)
        return sub_71006F1DF0(mActor, pos);
    return false;
}

AnimalRoamBase::AnimalRoamBase(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

AnimalRoamBase::~AnimalRoamBase() = default;

bool AnimalRoamBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void AnimalRoamBase::enter_(ksys::act::ai::InlineParamPack* params) {
    _a0 = 0;
    _a4 = true;
    if (auto* nav = mActor->m45())
        nav->sub_7100F7604C(0.5f);
}

void AnimalRoamBase::calc_() {}

void AnimalRoamBase::leave_() {
    ksys::act::ai::Ai::leave_();
}

void AnimalRoamBase::loadParams_() {
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

bool AnimalRoamBase::m35() {
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

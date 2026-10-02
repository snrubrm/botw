#include "Game/AI/AI/aiAnimalRoam.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

// NON_MATCHING: zero stores of the params are paired/scheduled differently
AnimalRoam::AnimalRoam(const InitArg& arg) : AnimalRoamBase(arg) {}

AnimalRoam::~AnimalRoam() = default;

bool AnimalRoam::init_(sead::Heap* heap) {
    return AnimalRoamBase::init_(heap);
}

void AnimalRoam::enter_(ksys::act::ai::InlineParamPack* params) {
    AnimalRoamBase::enter_(params);
}

void AnimalRoam::leave_() {
    AnimalRoamBase::leave_();
}

void AnimalRoam::loadParams_() {
    AnimalRoamBase::loadParams_();
    getStaticParam(&mFinishChangeCount_s, "FinishChangeCount");
    getStaticParam(&mLimitRadius_s, "LimitRadius");
    getStaticParam(&mChangeWaitRate_s, "ChangeWaitRate");
    getStaticParam(&mFramesStuckOnTerrainAction_s, "FramesStuckOnTerrainAction");
    getStaticParam(&mIsSendGoalPos_s, "IsSendGoalPos");
    getStaticParam(&mCheckValidStartPos_s, "CheckValidStartPos");
    getStaticParam(&mCheckLOS_s, "CheckLOS");
}

bool AnimalRoam::m40(sead::Vector3f* pos) {
    if (!pos)
        return false;
    auto* nav = mActor->m45();
    if (!nav)
        return false;
    nav->_1e0.lock();
    pos->set(nav->_194);
    nav->_1e0.unlock();
    return true;
}

}  // namespace uking::ai

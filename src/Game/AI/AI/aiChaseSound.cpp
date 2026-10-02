#include "Game/AI/AI/aiChaseSound.h"
#include "KingSystem/Physics/System/physRayCastForRequest.h"

namespace uking::ai {

ChaseSound::ChaseSound(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ChaseSound::~ChaseSound() = default;

void ChaseSound::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void ChaseSound::leave_() {
    if (_78) {
        _78->release();
        _78 = nullptr;
    }
}

void ChaseSound::loadParams_() {
    getStaticParam(&mTargetUpdateIntervalMin_s, "TargetUpdateIntervalMin");
    getStaticParam(&mTargetUpdateIntervalMax_s, "TargetUpdateIntervalMax");
    getStaticParam(&mNearDist_s, "NearDist");
    getStaticParam(&mTurnDir_s, "TurnDir");
    getStaticParam(&mUseViewPointSimpleOffset_s, "UseViewPointSimpleOffset");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai

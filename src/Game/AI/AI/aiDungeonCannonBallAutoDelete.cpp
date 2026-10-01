#include "Game/AI/AI/aiDungeonCannonBallAutoDelete.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

DungeonCannonBallAutoDelete::DungeonCannonBallAutoDelete(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

DungeonCannonBallAutoDelete::~DungeonCannonBallAutoDelete() = default;

bool DungeonCannonBallAutoDelete::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void DungeonCannonBallAutoDelete::enter_(ksys::act::ai::InlineParamPack* params) {
    _48 = ksys::Timer(*mTriggerVelocityKeepTime_s, *mTriggerVelocityKeepTime_s);
    changeChild("通常");
}

// NON_MATCHING: load scheduling of the velocity components (matches if the velocity is copied to a local first)
void DungeonCannonBallAutoDelete::calc_() {
    if (!isCurrentChild("通常"))
        return;

    if (mActor->getVelocity().length() >= *mTriggerVelocity_s)
        _48.update();

    if (_48.value <= sead::Mathf::epsilon())
        changeChild("消滅");
}

void DungeonCannonBallAutoDelete::leave_() {
    ksys::act::ai::Ai::leave_();
}

void DungeonCannonBallAutoDelete::loadParams_() {
    getStaticParam(&mTriggerVelocityKeepTime_s, "TriggerVelocityKeepTime");
    getStaticParam(&mTriggerVelocity_s, "TriggerVelocity");
}

}  // namespace uking::ai

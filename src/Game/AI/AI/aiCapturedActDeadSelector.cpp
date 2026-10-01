#include "Game/AI/AI/aiCapturedActDeadSelector.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiRoot.h"

namespace uking::ai {

CapturedActDeadSelector::CapturedActDeadSelector(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

CapturedActDeadSelector::~CapturedActDeadSelector() = default;

bool CapturedActDeadSelector::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void CapturedActDeadSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    const s32* life = mActor->getLife();
    if (life && *life <= 0)
        changeChild("通常");
    else if (*mIsDrop_a)
        changeChild("ドロップ");
    else if (*mIsPlayerPut_m)
        changeChild("手置き");
    else
        changeChild("通常");
}

void CapturedActDeadSelector::calc_() {}

void CapturedActDeadSelector::leave_() {
    ksys::act::ai::Ai::leave_();
}

void CapturedActDeadSelector::loadParams_() {
    getMapUnitParam(&mIsPlayerPut_m, "IsPlayerPut");
    mActor->getRootAi()->getAITreeVariable2(&mIsDrop_a, "IsDrop");
}

}  // namespace uking::ai

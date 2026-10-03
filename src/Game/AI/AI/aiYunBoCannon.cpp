#include "Game/AI/AI/aiYunBoCannon.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiRoot.h"

namespace uking::ai {

YunBoCannon::YunBoCannon(const InitArg& arg) : GoronCannonBase(arg) {}

YunBoCannon::~YunBoCannon() = default;

bool YunBoCannon::init_(sead::Heap* heap) {
    return GoronCannonBase::init_(heap);
}

void YunBoCannon::enter_(ksys::act::ai::InlineParamPack* params) {
    GoronCannonBase::enter_(params);
}

void YunBoCannon::leave_() {
    GoronCannonBase::leave_();
}

// NON_MATCHING: same instructions; the SafeString key temporary (adrp/stp) and the actor loads are scheduled
// differently
void YunBoCannon::m36(ksys::act::Actor* ball) {
    const int cannon_spot = *mCannonSpot_m;
    ball->getRootAi()->getMapUnitParams().setAITreeVariable("CannonSpot", ksys::AIDefParamType::Int,
                                                            cannon_spot);
}

void YunBoCannon::loadParams_() {
    GoronCannonBase::loadParams_();
    getStaticParam(&mReturnAnchorName_s, "ReturnAnchorName");
    getMapUnitParam(&mCannonSpot_m, "CannonSpot");
    getMapUnitParam(&mActorName_m, "ActorName");
}

}  // namespace uking::ai

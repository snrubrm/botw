#include "Game/AI/AI/aiNPCRoot.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

NPCRoot::NPCRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NPCRoot::~NPCRoot() = default;

bool NPCRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void NPCRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void NPCRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void NPCRoot::loadParams_() {
    getStaticParam(&mReleaseInterest2Time_s, "ReleaseInterest2Time");
    getStaticParam(&mPlayerHitVelocity_s, "PlayerHitVelocity");
    getStaticParam(&mStaggerUpperASName_s, "StaggerUpperASName");
    getStaticParam(&mStaggerUpperRunASName_s, "StaggerUpperRunASName");
}

// NON_MATCHING: scheduling (the original loads the name's first character and cNullChar before mActor)
void NPCRoot::m34() {
    const sead::SafeString name = mActor->getASList()->sub_710115ECF4(59, 1);
    mActor->getASList()->x_2(66, 35, name.isEmpty() && _201, false);
    changeChild("Timeline");
    _201 = false;
    mActor->getASList()->x_2(66, 35, false, false);
}

}  // namespace uking::ai

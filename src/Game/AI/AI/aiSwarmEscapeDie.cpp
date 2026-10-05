#include "Game/AI/AI/aiSwarmEscapeDie.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/System/CameraMgr.h"

namespace uking::ai {

SwarmEscapeDie::SwarmEscapeDie(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SwarmEscapeDie::~SwarmEscapeDie() = default;

bool SwarmEscapeDie::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: the position copy combines stores and schedules its component loads differently.
void SwarmEscapeDie::enter_(ksys::act::ai::InlineParamPack* params) {
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    if (ksys::sub_7100D8C4F8(pos))
        sub_71005B1464();
    else
        sub_71005B15F8();
}

void SwarmEscapeDie::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SwarmEscapeDie::loadParams_() {
    getStaticParam(&mTime_s, "Time");
    getStaticParam(&mRiseHeight_s, "RiseHeight");
    getStaticParam(&mRiseDist_s, "RiseDist");
    getStaticParam(&mEndDist_s, "EndDist");
}

}  // namespace uking::ai

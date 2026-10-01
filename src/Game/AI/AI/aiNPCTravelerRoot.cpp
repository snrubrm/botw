#include "Game/AI/AI/aiNPCTravelerRoot.h"
#include "Game/Actor/actNPC.h"

namespace uking::ai {

NPCTravelerRoot::NPCTravelerRoot(const InitArg& arg) : NPCRoot(arg) {}

NPCTravelerRoot::~NPCTravelerRoot() = default;

bool NPCTravelerRoot::init_(sead::Heap* heap) {
    if (!NPCRoot::init_(heap))
        return false;
    _248 = sead::DynamicCast<act::NPC>(mActor);
    return true;
}

void NPCTravelerRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    NPCRoot::enter_(params);
}

void NPCTravelerRoot::leave_() {
    NPCRoot::leave_();
}

void NPCTravelerRoot::loadParams_() {
    NPCRoot::loadParams_();
    getStaticParam(&mIsRiderChangableAction_s, "IsRiderChangableAction");
}

}  // namespace uking::ai

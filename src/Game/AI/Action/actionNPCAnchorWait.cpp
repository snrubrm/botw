#include "Game/AI/Action/actionNPCAnchorWait.h"
#include "Game/Actor/actNPC.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::action {

NPCAnchorWait::NPCAnchorWait(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCAnchorWait::~NPCAnchorWait() = default;

bool NPCAnchorWait::init_(sead::Heap* heap) {
    _40 = sead::DynamicCast<uking::act::NPC>(mActor);
    return true;
}

void NPCAnchorWait::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NPCAnchorWait::leave_() {
    _48 = false;
    if (auto* navmesh = mActor->m45())
        navmesh->sub_7100F76790();
}

void NPCAnchorWait::loadParams_() {
    getDynamicParam(&mIsRainAnchor_d, "IsRainAnchor");
    getDynamicParam(&mIsStartSameAS_d, "IsStartSameAS");
    getDynamicParam(&mASName_d, "ASName");
}

void NPCAnchorWait::calc_() {
    ksys::act::ai::Action::calc_();
}

bool NPCAnchorWait::handleMessage_(const ksys::Message* message) {
    return false;
}


}  // namespace uking::action

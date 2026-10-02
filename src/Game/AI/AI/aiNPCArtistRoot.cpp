#include "Game/AI/AI/aiNPCArtistRoot.h"
#include "Game/Actor/actNPC.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

static const sead::SafeString sUnk_710240AAB8 = "Hair_Root";

NPCArtistRoot::NPCArtistRoot(const InitArg& arg) : NPCRoot(arg) {}

NPCArtistRoot::~NPCArtistRoot() = default;

// NON_MATCHING: the original loads sead::Vector3f::zero once, before the sin/cos calls; ours
// reloads it after each call
bool NPCArtistRoot::init_(sead::Heap* heap) {
    if (!NPCRoot::init_(heap))
        return false;
    _308 = sead::DynamicCast<act::NPC>(mActor);
    _248.setName(sUnk_710240AAB8);
    mActor->boneHandleStuff(&_248, false);
    _248._68.makeRT(sead::Vector3f::zero, sead::Vector3f::zero);
    return true;
}

void NPCArtistRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    NPCRoot::enter_(params);
}

void NPCArtistRoot::leave_() {
    NPCRoot::leave_();
}

void NPCArtistRoot::loadParams_() {
    NPCRoot::loadParams_();
    getMapUnitParam(&mActorName_m, "ActorName");
}

}  // namespace uking::ai

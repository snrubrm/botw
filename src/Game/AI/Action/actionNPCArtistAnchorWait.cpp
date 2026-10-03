#include "Game/AI/Action/actionNPCArtistAnchorWait.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

NPCArtistAnchorWait::NPCArtistAnchorWait(const InitArg& arg) : NPCAnchorWait(arg) {}

NPCArtistAnchorWait::~NPCArtistAnchorWait() = default;

bool NPCArtistAnchorWait::init_(sead::Heap* heap) {
    return NPCAnchorWait::init_(heap);
}

void NPCArtistAnchorWait::enter_(ksys::act::ai::InlineParamPack* params) {
    NPCAnchorWait::enter_(params);
}

void NPCArtistAnchorWait::leave_() {
    NPCAnchorWait::leave_();
}

void NPCArtistAnchorWait::loadParams_() {
    NPCAnchorWait::loadParams_();
}

void NPCArtistAnchorWait::calc_() {
    NPCAnchorWait::calc_();
}

const char* NPCArtistAnchorWait::m32() {
    if (sead::SafeString(NPCAnchorWait::m32()) == "Act_Sketch" && !mActor->getConnectedCalcChild())
        return "SetEasel";
    return NPCAnchorWait::m32();
}

}  // namespace uking::action

#include "Game/AI/AI/aiSleepBedRoot.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/Event/evtMetadata.h"

namespace uking::ai {

SleepBedRoot::SleepBedRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SleepBedRoot::~SleepBedRoot() = default;

bool SleepBedRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SleepBedRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    changeChild("Wait");
}

void SleepBedRoot::leave_() {
    _38.x();
}

void SleepBedRoot::loadParams_() {}

// NON_MATCHING: the original computes &_38 before the Metadata ctor (kept in x22 across the calls) and
// stores the message type to a stack slot first, then copies it into the temporary it passes
// (sp+4 -> sp); ours keeps both in place.
void SleepBedRoot::calc_() {
    auto* actor = mActor;
    auto* child = getCurrentChild();
    if (_38._30) {
        ksys::evt::Metadata metadata("Demo007_0");
        _78.initWithEvent(actor, &metadata);
        actor->sendMessage(*ksys::evt::Manager::instance()->mTransceiver.getId(), ksys::MessageType(0x800002), &_78,
                           true);
        _38.x();
    }
    if (!child->isFinished() && !child->isFailed())
        child->isChangeable();
}

bool SleepBedRoot::handleMessage_(const ksys::Message* message) {
    if (!_38._30 && isCurrentChild("Wait"))
        return _38.m2(*message);
    return false;
}

}  // namespace uking::ai

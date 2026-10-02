#include "Game/AI/AI/aiAddDemoCall.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Event/evtBaseProcLinkForEvent.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/Event/evtMetadata.h"

namespace uking::ai {

AddDemoCall::AddDemoCall(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

AddDemoCall::~AddDemoCall() = default;

bool AddDemoCall::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void AddDemoCall::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

// NON_MATCHING: CallArg store order, and the original stores _98 after the Metadata destructor (as
// if the call were in an inline helper)
void AddDemoCall::calc_() {
    if (_98)
        return;

    ksys::evt::Metadata metadata(mDemoName_s.cstr(), mEntryPoint_s.cstr(), "");
    ksys::evt::CallArg arg;
    arg.metadata = &metadata;
    arg.proc = mActor;
    _98 = ksys::evt::Manager::instance()->callEvent(arg);
}

bool AddDemoCall::isFailed() const {
    return getCurrentChild()->isFailed();
}

bool AddDemoCall::isFinished() const {
    return getCurrentChild()->isFinished();
}

void AddDemoCall::leave_() {
    ksys::act::ai::Ai::leave_();
}

void AddDemoCall::loadParams_() {
    getStaticParam(&mOnlyOne_s, "OnlyOne");
    getStaticParam(&mIsBroadCastOnlyOne_s, "IsBroadCastOnlyOne");
    getStaticParam(&mEntryPoint_s, "EntryPoint");
    getStaticParam(&mDemoName_s, "DemoName");
}

}  // namespace uking::ai

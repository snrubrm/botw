#include "Game/AI/AI/aiInDemoSelect.h"

namespace uking::ai {

InDemoSelect::InDemoSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
InDemoSelect::~InDemoSelect() {
    ;
}

bool InDemoSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void InDemoSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void InDemoSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void InDemoSelect::loadParams_() {
    getStaticParam(&mDemoRetDelayMax_s, "DemoRetDelayMax");
    getStaticParam(&mOtherDemoNoRun_s, "OtherDemoNoRun");
    getStaticParam(&mForceChangeDemo_s, "ForceChangeDemo");
    getStaticParam(&mDemoFile_s, "DemoFile");
    getStaticParam(&mDemoEntryPoint_s, "DemoEntryPoint");
}

}  // namespace uking::ai

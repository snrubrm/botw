#include "Game/AI/Behavior/behaviorSubAS.h"

namespace uking::behavior {

SubAS::SubAS(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops (SafeString member).
SubAS::~SubAS() {
    ;
}

bool SubAS::m6(sead::Heap* heap) {
    return true;
}

void SubAS::m7() {}

void SubAS::loadParams() {
    getStaticParam(&mSeqBankIdx_s, "SeqBankIdx");
    getStaticParam(&mTargetIdx_s, "TargetIdx");
    getStaticParam(&mIsIgnoreSame_s, "IsIgnoreSame");
    getStaticParam(&mEnterASName_s, "EnterASName");
    getStaticParam(&mLeaveASName_s, "LeaveASName");
}

void SubAS::m8() {
    sub_7100643440(mEnterASName_s);
}

void SubAS::m9() {
    sub_7100643440(mLeaveASName_s);
}

}  // namespace uking::behavior

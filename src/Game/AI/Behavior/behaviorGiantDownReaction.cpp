#include "Game/AI/Behavior/behaviorGiantDownReaction.h"
#include <prim/seadFormatPrint.h>

namespace uking::behavior {

GiantDownReaction::GiantDownReaction(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops (SafeString member).
GiantDownReaction::~GiantDownReaction() {
    ;
}

bool GiantDownReaction::m6(sead::Heap* heap) {
    return true;
}

void GiantDownReaction::m8() {
    _70 = false;
    _74 = -1.0f;
}

void GiantDownReaction::m9() {}

void GiantDownReaction::loadParams() {
    getStaticParam(&mIntervalTime_s, "IntervalTime");
    getStaticParam(&mDownCheckRagdollRbName_s, "DownCheckRagdollRbName");
    sead::FixedSafeString<32> key;
    for (u32 i = 0; i < 3; i++) {
        (sead::StringCutOffPrintFormatter(&key) << "GroundCheckRagdollRbName%d", i) << sead::flush;
        getStaticParam(&mGroundCheckRagdollRbName_s[i], key);
    }
}

}  // namespace uking::behavior

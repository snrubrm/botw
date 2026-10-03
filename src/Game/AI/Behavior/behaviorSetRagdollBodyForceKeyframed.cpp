#include "Game/AI/Behavior/behaviorSetRagdollBodyForceKeyframed.h"
#include <prim/seadFormatPrint.h>
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::behavior {

SetRagdollBodyForceKeyframed::SetRagdollBodyForceKeyframed(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops (SafeString member).
SetRagdollBodyForceKeyframed::~SetRagdollBodyForceKeyframed() {
    ;
}

bool SetRagdollBodyForceKeyframed::m6(sead::Heap* heap) {
    return true;
}

void SetRagdollBodyForceKeyframed::m7() {}

void SetRagdollBodyForceKeyframed::m8() {
    for (const auto& name : mRagdollBodyName_s) {
        if (!name.isEmpty())
            sub_71005E226C(mActor, name, true);
    }
}

void SetRagdollBodyForceKeyframed::m9() {
    for (const auto& name : mRagdollBodyName_s) {
        if (!name.isEmpty())
            sub_71005E226C(mActor, name, false);
    }
}

void SetRagdollBodyForceKeyframed::loadParams() {
    sead::FixedSafeString<64> key;
    for (u32 i = 0; i < 2; i++) {
        (sead::StringCutOffPrintFormatter(&key) << "RagdollBodyName%d", i) << sead::flush;
        getStaticParam(&mRagdollBodyName_s[i], key);
    }
}

}  // namespace uking::behavior

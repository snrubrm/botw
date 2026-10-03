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

// NON_MATCHING: the original loads the null char (isEmpty()'s comparison constant) once at the start, before the
// first string pointer; we load it after it
void SetRagdollBodyForceKeyframed::m8() {
    if (!mRagdollBodyName0_s.isEmpty())
        sub_71005E226C(mActor, mRagdollBodyName0_s, true);
    if (!mRagdollBodyName1_s.isEmpty())
        sub_71005E226C(mActor, mRagdollBodyName1_s, true);
}

// NON_MATCHING: same load order difference as m8
void SetRagdollBodyForceKeyframed::m9() {
    if (!mRagdollBodyName0_s.isEmpty())
        sub_71005E226C(mActor, mRagdollBodyName0_s, false);
    if (!mRagdollBodyName1_s.isEmpty())
        sub_71005E226C(mActor, mRagdollBodyName1_s, false);
}

// NON_MATCHING: the original builds the names with `sead::StringCutOffPrintFormatter(&key) << "RagdollBodyName%d", n` +
// `flush` and calls the out-of-line trivial ~StringCutOffPrintOutput (0x7100b0c528), which lib/sead declares inline
// (needs a lib/sead edit, see REVIEW.md)
void SetRagdollBodyForceKeyframed::loadParams() {
    getStaticParam(&mRagdollBodyName0_s, sead::FormatFixedSafeString<64>("RagdollBodyName%d", 0));
    getStaticParam(&mRagdollBodyName1_s, sead::FormatFixedSafeString<64>("RagdollBodyName%d", 1));
}

}  // namespace uking::behavior

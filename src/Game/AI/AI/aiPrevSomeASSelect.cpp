#include "Game/AI/AI/aiPrevSomeASSelect.h"
#include <prim/seadFormatPrint.h>
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

PrevSomeASSelect::PrevSomeASSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
PrevSomeASSelect::~PrevSomeASSelect() {
    ;
}

bool PrevSomeASSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PrevSomeASSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    const auto& name = mActor->getASList()->x_1(*mTargetBone_s, *mSeqBank_s);
    for (int i = 0; i < 6; ++i) {
        if (mASName_s[i] == name) {
            changeChild("該当", params);
            return;
        }
    }
    changeChild("非該当", params);
}

void PrevSomeASSelect::calc_() {}

void PrevSomeASSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PrevSomeASSelect::loadParams_() {
    getStaticParam(&mSeqBank_s, "SeqBank");
    getStaticParam(&mTargetBone_s, "TargetBone");
    sead::FixedSafeString<64> key;
    for (u32 i = 0; i < 6; i++) {
        (sead::StringCutOffPrintFormatter(&key) << "ASName%d", i) << sead::flush;
        getStaticParam(&mASName_s[i], key);
    }
}

}  // namespace uking::ai

#include "Game/AI/Behavior/behaviorBeastGanonWPPrincessShout.h"

namespace uking::behavior {

BeastGanonWPPrincessShout::BeastGanonWPPrincessShout(const InitArg& arg)
    : SimpleAtvUnitOpenSimpleDialog(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops (SafeString member).
BeastGanonWPPrincessShout::~BeastGanonWPPrincessShout() {
    ;
}

bool BeastGanonWPPrincessShout::m6(sead::Heap* heap) {
    return SimpleAtvUnitOpenSimpleDialog::m6(heap);
}

void BeastGanonWPPrincessShout::m7() {
    SimpleAtvUnitOpenSimpleDialog::m7();
}

void BeastGanonWPPrincessShout::m8() {
    SimpleAtvUnitOpenSimpleDialog::m8();
}

void BeastGanonWPPrincessShout::m9() {
    SimpleAtvUnitOpenSimpleDialog::m9();
}

void BeastGanonWPPrincessShout::loadParams() {
    SimpleAtvUnitOpenSimpleDialog::loadParams();
    getStaticParam(&mSingleIdx_s, "SingleIdx");
    getStaticParam(&mlabelName2_s, "labelName2");
    getStaticParam(&mlabelName3_s, "labelName3");
    getStaticParam(&mlabelName4_s, "labelName4");
    getStaticParam(&mlabelName5_s, "labelName5");
    getStaticParam(&mlabelName6_s, "labelName6");
    getStaticParam(&mlabelName7_s, "labelName7");
    getStaticParam(&mlabelName8_s, "labelName8");
    getStaticParam(&mlabelName9_s, "labelName9");
    getStaticParam(&mlabelName10_s, "labelName10");
    getAITreeVariable(&mWeakPointActiveFlag_a, "WeakPointActiveFlag");
}

}  // namespace uking::behavior

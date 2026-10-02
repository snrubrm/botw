#include "Game/AI/Behavior/behaviorSimpleAtvUnitOpenDlgRnd3.h"

namespace uking::behavior {

SimpleAtvUnitOpenDlgRnd3::SimpleAtvUnitOpenDlgRnd3(const InitArg& arg)
    : SimpleAtvUnitOpenDlg(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops (SafeString member).
SimpleAtvUnitOpenDlgRnd3::~SimpleAtvUnitOpenDlgRnd3() {
    ;
}

bool SimpleAtvUnitOpenDlgRnd3::m6(sead::Heap* heap) {
    return SimpleAtvUnitOpenDlg::m6(heap);
}

void SimpleAtvUnitOpenDlgRnd3::m7() {
    SimpleAtvUnitOpenDlg::m7();
}

void SimpleAtvUnitOpenDlgRnd3::m8() {
    SimpleAtvUnitOpenDlg::m8();
}

void SimpleAtvUnitOpenDlgRnd3::m9() {
    SimpleAtvUnitOpenDlg::m9();
}

void SimpleAtvUnitOpenDlgRnd3::loadParams() {
    SimpleAtvUnitOpenDlg::loadParams();
    getStaticParam(&mlabelName2_s, "labelName2");
    getStaticParam(&mlabelName3_s, "labelName3");
}

// NON_MATCHING: csel operand order (the first select uses `ne`)
const sead::SafeString* SimpleAtvUnitOpenDlgRnd3::m14() {
    if (_88 == 1)
        return &mlabelName2_s;
    if (_88 == 2)
        return &mlabelName3_s;
    return &mlabelName_s;
}

}  // namespace uking::behavior

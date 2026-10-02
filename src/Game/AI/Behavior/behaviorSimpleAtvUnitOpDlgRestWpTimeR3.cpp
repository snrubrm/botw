#include "Game/AI/Behavior/behaviorSimpleAtvUnitOpDlgRestWpTimeR3.h"

namespace uking::behavior {

SimpleAtvUnitOpDlgRestWpTimeR3::SimpleAtvUnitOpDlgRestWpTimeR3(const InitArg& arg)
    : SimpleAtvUnitOpDlgRestWpTimeR3Base(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops (SafeString member).
SimpleAtvUnitOpDlgRestWpTimeR3::~SimpleAtvUnitOpDlgRestWpTimeR3() {
    ;
}

bool SimpleAtvUnitOpDlgRestWpTimeR3::m6(sead::Heap* heap) {
    return SimpleAtvUnitOpDlgRestWpTimeR3Base::m6(heap);
}

void SimpleAtvUnitOpDlgRestWpTimeR3::m7() {
    SimpleAtvUnitOpDlgRestWpTimeR3Base::m7();
}

void SimpleAtvUnitOpDlgRestWpTimeR3::m8() {
    SimpleAtvUnitOpDlgRestWpTimeR3Base::m8();
}

void SimpleAtvUnitOpDlgRestWpTimeR3::m9() {
    SimpleAtvUnitOpDlgRestWpTimeR3Base::m9();
}

void SimpleAtvUnitOpDlgRestWpTimeR3::loadParams() {
    SimpleAtvUnitOpDlgRestWpTimeR3Base::loadParams();
    getStaticParam(&mlabelName3_s, "labelName3");
    getStaticParam(&mlabelName2_s, "labelName2");
}

// NON_MATCHING: csel operand order (the first select uses `ne`)
const sead::SafeString* SimpleAtvUnitOpDlgRestWpTimeR3::m14() {
    if (_bc == 1)
        return &mlabelName2_s;
    if (_bc == 2)
        return &mlabelName3_s;
    return &mlabelName_s;
}

}  // namespace uking::behavior

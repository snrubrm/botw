#include "Game/Actor/Behavior/behaviorSimpleAtvUnitOpenDlgRnd3.h"

namespace uking::behavior {

SimpleAtvUnitOpenDlgRnd3::SimpleAtvUnitOpenDlgRnd3(const InitArg& arg)
    : SimpleAtvUnitOpenDlg(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops (SafeString member).
SimpleAtvUnitOpenDlgRnd3::~SimpleAtvUnitOpenDlgRnd3() {
    ;
}

bool SimpleAtvUnitOpenDlgRnd3::init_(sead::Heap* heap) {
    return SimpleAtvUnitOpenDlg::init_(heap);
}

void SimpleAtvUnitOpenDlgRnd3::calc() {
    SimpleAtvUnitOpenDlg::calc();
}

void SimpleAtvUnitOpenDlgRnd3::enter() {
    SimpleAtvUnitOpenDlg::enter();
}

void SimpleAtvUnitOpenDlgRnd3::leave() {
    SimpleAtvUnitOpenDlg::leave();
}

void SimpleAtvUnitOpenDlgRnd3::loadParams() {
    SimpleAtvUnitOpenDlg::loadParams();
    getStaticParam(&mlabelName2_s, "labelName2");
    getStaticParam(&mlabelName3_s, "labelName3");
}

const sead::SafeString* SimpleAtvUnitOpenDlgRnd3::m14() {
    if (_88 == 2)
        return &mlabelName3_s;
    if (_88 == 1)
        return &mlabelName2_s;
    return &mlabelName_s;
}

}  // namespace uking::behavior

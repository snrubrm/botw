#include "Game/AI/Behavior/behaviorSimpleAtvUnitOpenDlg.h"

namespace uking::behavior {

SimpleAtvUnitOpenDlg::SimpleAtvUnitOpenDlg(const InitArg& arg)
    : SimpleAtvUnitOpenSimpleDialog(arg) {}

SimpleAtvUnitOpenDlg::~SimpleAtvUnitOpenDlg() = default;

bool SimpleAtvUnitOpenDlg::m6(sead::Heap* heap) {
    if (!SimpleAtvUnitOpenSimpleDialog::m6(heap))
        return false;
    _86 = 0;
    return true;
}

void SimpleAtvUnitOpenDlg::m7() {
    SimpleAtvUnitOpenSimpleDialog::m7();
}

void SimpleAtvUnitOpenDlg::m8() {
    SimpleAtvUnitOpenSimpleDialog::m8();
}

void SimpleAtvUnitOpenDlg::m9() {
    SimpleAtvUnitOpenSimpleDialog::m9();
}

void SimpleAtvUnitOpenDlg::loadParams() {
    SimpleAtvUnitOpenSimpleDialog::loadParams();
}

}  // namespace uking::behavior

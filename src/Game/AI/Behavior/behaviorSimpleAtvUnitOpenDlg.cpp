#include "Game/AI/Behavior/behaviorSimpleAtvUnitOpenDlg.h"
#include <random/seadGlobalRandom.h>

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

void SimpleAtvUnitOpenDlg::m16() {
    _88 = 0;
    if ((m18() & ~_86.getDirect() & 0xff) == 0)
        _86.makeAllZero();
    const s32 count = m17();
    u32 candidates = 1;
    for (s32 i = 0; i < count; ++i) {
        if (_86.isOffBit(i)) {
            if (sead::GlobalRandom::instance()->getU32(candidates) == 0)
                _88 = i;
            ++candidates;
        }
    }
    _86.setBit(_88);
    SimpleAtvUnitOpenSimpleDialog::m16();
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

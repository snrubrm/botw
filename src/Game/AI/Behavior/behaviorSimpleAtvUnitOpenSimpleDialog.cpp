#include "Game/AI/Behavior/behaviorSimpleAtvUnitOpenSimpleDialog.h"
#include "Game/AI/aiUnk_71025b2aa8.h"

namespace uking::behavior {

SimpleAtvUnitOpenSimpleDialog::SimpleAtvUnitOpenSimpleDialog(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

void SimpleAtvUnitOpenSimpleDialog::m8() {
    if (_85)
        return;
    m16();
}

void SimpleAtvUnitOpenSimpleDialog::m9() {}

void SimpleAtvUnitOpenSimpleDialog::loadParams() {
    getStaticParam(&mCloseOption_s, "CloseOption");
    getStaticParam(&mTimer_s, "Timer");
    getStaticParam(&mDelayTimer_s, "DelayTimer");
    getStaticParam(&mType_s, "Type");
    getStaticParam(&mOnce_s, "Once");
    getStaticParam(&mmstxtName_s, "mstxtName");
    getStaticParam(&mlabelName_s, "labelName");
    getAITreeVariable(&mSimpleDialogUnit_a, "SimpleDialogUnit");
}

const sead::SafeString* SimpleAtvUnitOpenSimpleDialog::m14() {
    return &mlabelName_s;
}

SimpleAtvUnitOpenSimpleDialog::~SimpleAtvUnitOpenSimpleDialog() = default;

bool SimpleAtvUnitOpenSimpleDialog::m6(sead::Heap* heap) {
    if (!_78.acquire(heap, static_cast<Unk_71025afb58**>(mSimpleDialogUnit_a)))
        return false;
    _85 = false;
    return true;
SimpleAtvUnitOpenSimpleDialog::~SimpleAtvUnitOpenSimpleDialog() {
    if (_78) {
        auto* unit = sead::DynamicCast<Unk_71025b2aa8>(*_78);
        if (unit && unit->_20 > 0 && unit->_20-- == 1) {
            *_78 = nullptr;
            delete unit;
        }
        _78 = nullptr;
    }
}

}  // namespace uking::behavior

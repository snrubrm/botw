#include "Game/AI/Behavior/behaviorSimpleAtvUnitDlgStop.h"
#include "Game/AI/aiUnk_71025b2aa8.h"

namespace uking::behavior {

SimpleAtvUnitDlgStop::SimpleAtvUnitDlgStop(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

void SimpleAtvUnitDlgStop::m7() {}

void SimpleAtvUnitDlgStop::m9() {}

void SimpleAtvUnitDlgStop::loadParams() {
    getAITreeVariable(&mSimpleDialogUnit_a, "SimpleDialogUnit");
}

SimpleAtvUnitDlgStop::~SimpleAtvUnitDlgStop() = default;

// NON_MATCHING: the original keeps the second cast's `unit ? unit + 8 : nullptr` as branches (ours
// speculates the add and uses a csel); same as SimpleAtvUnitOpenSimpleDialog::sub_7100641EB8.
void SimpleAtvUnitDlgStop::m8() {
    if (!_30._0)
        return;
    auto* unit = sead::DynamicCast<Unk_71025b2aa8>(*_30._0);
    if (!unit || unit->mRefCount < 1)
        return;
    _30.getData()->sub_7100721F54();
}

bool SimpleAtvUnitDlgStop::m6(sead::Heap* heap) {
    return _30.acquire(heap, static_cast<Unk_71025afb58**>(mSimpleDialogUnit_a));
}

}  // namespace uking::behavior

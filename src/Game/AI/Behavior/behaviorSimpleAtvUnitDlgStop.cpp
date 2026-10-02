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

bool SimpleAtvUnitDlgStop::m6(sead::Heap* heap) {
    return _30.acquire(heap, static_cast<Unk_71025afb58**>(mSimpleDialogUnit_a));
SimpleAtvUnitDlgStop::~SimpleAtvUnitDlgStop() {
    if (_30) {
        auto* unit = sead::DynamicCast<Unk_71025b2aa8>(*_30);
        if (unit && unit->_20 > 0 && unit->_20-- == 1) {
            *_30 = nullptr;
            delete unit;
        }
        _30 = nullptr;
    }
}

}  // namespace uking::behavior

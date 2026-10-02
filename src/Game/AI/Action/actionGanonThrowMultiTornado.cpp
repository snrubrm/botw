#include "Game/AI/Action/actionGanonThrowMultiTornado.h"

namespace uking::action {

GanonThrowMultiTornado::GanonThrowMultiTornado(const InitArg& arg) : GanonThrowTornado(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
GanonThrowMultiTornado::~GanonThrowMultiTornado() {
    ;
}

bool GanonThrowMultiTornado::init_(sead::Heap* heap) {
    return GanonThrowTornado::init_(heap);
}

void GanonThrowMultiTornado::enter_(ksys::act::ai::InlineParamPack* params) {
    GanonThrowTornado::enter_(params);
}

void GanonThrowMultiTornado::leave_() {
    GanonThrowTornado::leave_();
}

void GanonThrowMultiTornado::loadParams_() {
    GanonThrowTornado::loadParams_();
    getStaticParam(&mAppearOffset1_s, "AppearOffset1");
    getDynamicParam(&mThrowPartsName1_d, "ThrowPartsName1");
}

void GanonThrowMultiTornado::calc_() {
    GanonThrowTornado::calc_();
}

}  // namespace uking::action

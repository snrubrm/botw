#include "Game/AI/Action/actionOctarockReloadWig.h"

namespace uking::action {

OctarockReloadWig::OctarockReloadWig(const InitArg& arg) : OctarockReloadWigBase(arg) {}

OctarockReloadWig::~OctarockReloadWig() = default;

bool OctarockReloadWig::init_(sead::Heap* heap) {
    return OctarockReloadWigBase::init_(heap);
}

void OctarockReloadWig::enter_(ksys::act::ai::InlineParamPack* params) {
    _90 = false;
    OctarockReloadWigBase::enter_(params);
}

// TODO: calls 0x7100714c9c on the OctarockFormChangeUnit AI tree variable (class not declared yet)
void OctarockReloadWig::leave_() {
    OctarockReloadWigBase::leave_();
}

void OctarockReloadWig::loadParams_() {
    OctarockReloadWigBase::loadParams_();
    _48._30 = "Wig";
    getAITreeVariable(&mOctarockFormChangeUnit_a, "OctarockFormChangeUnit");
}

// TODO: calls 0x7100714c9c on the OctarockFormChangeUnit AI tree variable (class not declared yet)
void OctarockReloadWig::calc_() {
    OctarockReloadWigBase::calc_();
}

}  // namespace uking::action

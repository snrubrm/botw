#include "Game/AI/Action/actionForkOctarockEnterReloadWig.h"

namespace uking::action {

ForkOctarockEnterReloadWig::ForkOctarockEnterReloadWig(const InitArg& arg) : Fork(arg) {}

ForkOctarockEnterReloadWig::~ForkOctarockEnterReloadWig() = default;

bool ForkOctarockEnterReloadWig::init_(sead::Heap* heap) {
    if (!Fork::init_(heap))
        return false;
    return _40.init(heap);
}

void ForkOctarockEnterReloadWig::enter_(ksys::act::ai::InlineParamPack* params) {
    Fork::enter_(params);
    _38 = false;
    _40.enter(params);
}

// TODO: calls 0x7100714c9c on the OctarockFormChangeUnit AI tree variable (class not declared yet)
void ForkOctarockEnterReloadWig::leave_() {
    Fork::leave_();
}

void ForkOctarockEnterReloadWig::loadParams_() {
    Fork::loadParams_();
    _40.loadParams();
    _40._30 = "Wig";
    getAITreeVariable(&mOctarockFormChangeUnit_a, "OctarockFormChangeUnit");
}

// TODO: calls 0x7100714c9c on the OctarockFormChangeUnit AI tree variable (class not declared yet)
void ForkOctarockEnterReloadWig::calc_() {
    Fork::calc_();
}

}  // namespace uking::action

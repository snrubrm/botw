#include "Game/AI/Action/actionForkOctarockEnterReloadWig.h"
#include "Game/AI/aiUnk_7102450d10.h"

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

void ForkOctarockEnterReloadWig::leave_() {
    if (!_38 && _40.isFinished()) {
        auto* unit = sead::DynamicCast<Unk_7102450d10>(
            *static_cast<Unk_71025afb58**>(mOctarockFormChangeUnit_a));
        if (unit)
            unit->sub_7100714C9C();
        _38 = true;
    }
    _40.leave();
    Fork::leave_();
}

void ForkOctarockEnterReloadWig::loadParams_() {
    Fork::loadParams_();
    _40.loadParams();
    _40._30 = "Wig";
    getAITreeVariable(&mOctarockFormChangeUnit_a, "OctarockFormChangeUnit");
}

void ForkOctarockEnterReloadWig::calc_() {
    Fork::calc_();
    if (isFinished() || isFailed())
        return;

    _40.calc();
    _40.sub_71002A7A38();
    if (!_38 && _40.isFinished()) {
        auto* unit = sead::DynamicCast<Unk_7102450d10>(
            *static_cast<Unk_71025afb58**>(mOctarockFormChangeUnit_a));
        if (unit)
            unit->sub_7100714C9C();
        _38 = true;
        setEndState();
    } else if (_40.isFailed()) {
        setFailed();
    }
}

}  // namespace uking::action

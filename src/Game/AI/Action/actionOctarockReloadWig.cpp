#include "Game/AI/Action/actionOctarockReloadWig.h"
#include "Game/AI/aiUnk_7102450d10.h"
#include "KingSystem/ActorSystem/actActor.h"

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

void OctarockReloadWig::leave_() {
    if (!_90 && _48.mOwner->getActor()->getConnectedCalcChild()) {
        auto* unit = sead::DynamicCast<Unk_7102450d10>(
            *static_cast<Unk_71025afb58**>(mOctarockFormChangeUnit_a));
        if (unit)
            unit->sub_7100714C9C();
        _90 = true;
    }
    OctarockReloadWigBase::leave_();
}

void OctarockReloadWig::loadParams_() {
    OctarockReloadWigBase::loadParams_();
    _48._30 = "Wig";
    getAITreeVariable(&mOctarockFormChangeUnit_a, "OctarockFormChangeUnit");
}

void OctarockReloadWig::calc_() {
    OctarockReloadWigBase::calc_();
    if (!_90 && _48.mOwner->getActor()->getConnectedCalcChild()) {
        auto* unit = sead::DynamicCast<Unk_7102450d10>(
            *static_cast<Unk_71025afb58**>(mOctarockFormChangeUnit_a));
        if (unit)
            unit->sub_7100714C9C();
        _90 = true;
    }
}

}  // namespace uking::action

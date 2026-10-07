#include "Game/AI/Action/actionForkDropGiantNecklace.h"
#include "Game/AI/aiUnk_7102450390.h"

namespace uking::action {

ForkDropGiantNecklace::ForkDropGiantNecklace(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkDropGiantNecklace::~ForkDropGiantNecklace() = default;

bool ForkDropGiantNecklace::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkDropGiantNecklace::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
    if (auto* unit = sead::DynamicCast<Unk_7102450390>(*mGiantNecklaceUnit_a)) {
        unit->sub_7100707544(0);
        unit->sub_7100707544(1);
        unit->sub_7100707544(2);
    }
}

void ForkDropGiantNecklace::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkDropGiantNecklace::loadParams_() {
    getAITreeVariable(&mGiantNecklaceUnit_a, "GiantNecklaceUnit");
}

void ForkDropGiantNecklace::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

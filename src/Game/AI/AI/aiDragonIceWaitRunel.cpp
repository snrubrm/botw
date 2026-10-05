#include "Game/AI/AI/aiDragonIceWaitRunel.h"
#include "Game/Actor/actDragon.h"

namespace uking::ai {

DragonIceWaitRunel::DragonIceWaitRunel(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

DragonIceWaitRunel::~DragonIceWaitRunel() = default;

bool DragonIceWaitRunel::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: the compiler selects the child name directly instead of branching.
void DragonIceWaitRunel::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* dragon = sead::DynamicCast<act::Dragon>(mActor))
        changeChild(dragon->sub_710000FE10() ? "怨念待機" : "正常待機", nullptr);
    mFlags.set(Flag::Changeable);
}

void DragonIceWaitRunel::calc_() {}

void DragonIceWaitRunel::leave_() {
    ksys::act::ai::Ai::leave_();
}

void DragonIceWaitRunel::loadParams_() {}

}  // namespace uking::ai

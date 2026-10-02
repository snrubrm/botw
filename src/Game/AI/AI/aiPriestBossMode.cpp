#include "Game/AI/AI/aiPriestBossMode.h"
#include "Game/AI/aiUnk_7102450fa8.h"

namespace uking::ai {

PriestBossMode::PriestBossMode(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PriestBossMode::~PriestBossMode() = default;

bool PriestBossMode::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PriestBossMode::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PriestBossMode::calc_() {}

void PriestBossMode::leave_() {
    ksys::act::ai::Ai::leave_();
}

Unk_7102450fa8* PriestBossMode::sub_7100505BE4() {
    return sead::DynamicCast<Unk_7102450fa8>(
        *static_cast<Unk_71025afb58**>(mPriestBossMetaAIUnit_a));
}

bool PriestBossMode::m34() {
    if (!sub_7100505BE4())
        return true;
    return sub_7100505BE4()->_78.isOnBit(Unk_7102450fa8::Flag(Unk_7102450fa8::Flag::_11));
}

void PriestBossMode::loadParams_() {
    getAITreeVariable(&mPriestBossMetaAIUnit_a, "PriestBossMetaAIUnit");
}

}  // namespace uking::ai

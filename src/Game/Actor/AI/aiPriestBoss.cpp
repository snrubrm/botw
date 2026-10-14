#include "Game/Actor/AI/aiPriestBoss.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/aiUnk_7102450fa8.h"

namespace uking::ai {

PriestBoss::PriestBoss(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PriestBoss::~PriestBoss() = default;

bool PriestBoss::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PriestBoss::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PriestBoss::calc_() {}

void PriestBoss::leave_() {
    ksys::act::ai::Ai::leave_();
}

Unk_7102450fa8* PriestBoss::sub_7100505BE4() {
    return sead::DynamicCast<Unk_7102450fa8>(
        *static_cast<Unk_71025afb58**>(mPriestBossMetaAIUnit_a));
}

// 0x7100505bd8
void PriestBoss::sub_7100505BD8(Unk_71025afb58* unit) {
    *static_cast<Unk_71025afb58**>(mPriestBossMetaAIUnit_a) = unit;
}

// 0x7100505c74
bool PriestBoss::sub_7100505C74() {
    return sead::DynamicCast<act::Enemy>(mActor)->getActorPartsActor(sUnk_7102450f98).hasProc();
}

bool PriestBoss::m34() {
    if (!sub_7100505BE4())
        return true;
    return sub_7100505BE4()->_78.isOnBit(Unk_7102450fa8::Flag(Unk_7102450fa8::Flag::_11));
}

void PriestBoss::loadParams_() {
    getAITreeVariable(&mPriestBossMetaAIUnit_a, "PriestBossMetaAIUnit");
}

}  // namespace uking::ai

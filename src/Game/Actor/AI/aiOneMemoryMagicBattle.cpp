#include "Game/Actor/AI/aiOneMemoryMagicBattle.h"
#include "Game/Actor/actEnemy.h"

namespace uking::ai {

OneMemoryMagicBattle::OneMemoryMagicBattle(const InitArg& arg) : MagicBattle(arg) {}

OneMemoryMagicBattle::~OneMemoryMagicBattle() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->sub_7100D3CFEC(mMemoryPartsName_s);
}

bool OneMemoryMagicBattle::init_(sead::Heap* heap) {
    if (!MagicBattle::init_(heap))
        return false;
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->sub_7100D3CED8(mMemoryPartsName_s, heap);
    return true;
}

void OneMemoryMagicBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    MagicBattle::enter_(params);
}

void OneMemoryMagicBattle::calc_() {
    MagicBattle::calc_();
    getCurrentChild()->isChangeable();
}

void OneMemoryMagicBattle::leave_() {
    MagicBattle::leave_();
}

void OneMemoryMagicBattle::loadParams_() {
    MagicBattle::loadParams_();
    getStaticParam(&mMemoryPartsName_s, "MemoryPartsName");
}

bool OneMemoryMagicBattle::m45() {
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (enemy && enemy->getActorPartsActor(mMemoryPartsName_s).hasProcInCalcState())
        return false;
    return MagicBattle::m45();
}

}  // namespace uking::ai

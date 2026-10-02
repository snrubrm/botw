#include "Game/AI/AI/aiOneMemoryMagicBattle.h"
#include "Game/Actor/actEnemy.h"

namespace uking::ai {

OneMemoryMagicBattle::OneMemoryMagicBattle(const InitArg& arg) : OneMemoryMagicBattleBase(arg) {}

OneMemoryMagicBattle::~OneMemoryMagicBattle() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->sub_7100D3CFEC(mMemoryPartsName_s);
}

bool OneMemoryMagicBattle::init_(sead::Heap* heap) {
    if (!OneMemoryMagicBattleBase::init_(heap))
        return false;
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->sub_7100D3CED8(mMemoryPartsName_s, heap);
    return true;
}

void OneMemoryMagicBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    OneMemoryMagicBattleBase::enter_(params);
}

void OneMemoryMagicBattle::calc_() {
    OneMemoryMagicBattleBase::calc_();
    getCurrentChild()->isChangeable();
}

void OneMemoryMagicBattle::leave_() {
    OneMemoryMagicBattleBase::leave_();
}

void OneMemoryMagicBattle::loadParams_() {
    OneMemoryMagicBattleBase::loadParams_();
    getStaticParam(&mMemoryPartsName_s, "MemoryPartsName");
}

bool OneMemoryMagicBattle::m45() {
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (enemy && enemy->getActorPartsActor(mMemoryPartsName_s).hasProcInCalcState())
        return false;
    return OneMemoryMagicBattleBase::m45();
}

}  // namespace uking::ai

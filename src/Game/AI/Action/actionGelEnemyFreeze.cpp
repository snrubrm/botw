#include "Game/AI/Action/actionGelEnemyFreeze.h"
#include "Game/Actor/actGelEnemy.h"

namespace uking::action {

GelEnemyFreeze::GelEnemyFreeze(const InitArg& arg) : Freeze(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
GelEnemyFreeze::~GelEnemyFreeze() {
    ;
}

bool GelEnemyFreeze::init_(sead::Heap* heap) {
    return Freeze::init_(heap);
}

void GelEnemyFreeze::enter_(ksys::act::ai::InlineParamPack* params) {
    playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
    Freeze::enter_(params);
    if (auto* gel = sead::DynamicCast<act::GelEnemy>(mActor)) {
        gel->_1678 |= 3;
        gel->_1620.z = 1.0f;
    }
}

void GelEnemyFreeze::leave_() {
    if (auto* gel = sead::DynamicCast<uking::act::GelEnemy>(mActor))
        gel->_1678 &= ~3;
    Freeze::leave_();
}

void GelEnemyFreeze::loadParams_() {
    Freeze::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void GelEnemyFreeze::calc_() {
    Freeze::calc_();
}

}  // namespace uking::action

#include "Game/Actor/Action/actionBattleCloseSlippedMoveBase.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

BattleCloseSlippedMoveBase::BattleCloseSlippedMoveBase(const InitArg& arg)
    : AvoidingCloseMoveActionWithAcc(arg) {}

BattleCloseSlippedMoveBase::~BattleCloseSlippedMoveBase() = default;

bool BattleCloseSlippedMoveBase::init_(sead::Heap* heap) {
    return AvoidingCloseMoveActionWithAcc::init_(heap);
}

void BattleCloseSlippedMoveBase::enter_(ksys::act::ai::InlineParamPack* params) {
    AvoidingCloseMoveActionWithAcc::enter_(params);
}

void BattleCloseSlippedMoveBase::leave_() {
    AvoidingCloseMoveActionWithAcc::leave_();
}

void BattleCloseSlippedMoveBase::loadParams_() {
    AvoidingCloseMoveActionWithAcc::loadParams_();
}

void BattleCloseSlippedMoveBase::calc_() {
    AvoidingCloseMoveActionWithAcc::calc_();
}

ksys::act::Unk_7100d78e50* BattleCloseSlippedMoveBase::m33(int idx) {
    auto* awareness = mActor->getAwareness();
    if (awareness && awareness->_8.size() > idx)
        return ksys::act::sub_7100D78E30(&awareness->_8, idx);
    return nullptr;
}

bool BattleCloseSlippedMoveBase::m34(ksys::act::Unk_7100d78e50* entry) {
    return ksys::act::isPlayerProfile(&entry->_0.mLink) || ksys::act::isWeaponProfile(&entry->_0.mLink);
}

}  // namespace uking::action

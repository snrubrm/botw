#include "Game/AI/Action/actionEnemyFortressChatTurn.h"
#include "KingSystem/Utils/Thread/MessageAck.h"

namespace uking::action {

EnemyFortressChatTurn::EnemyFortressChatTurn(const InitArg& arg)
    : EnemyFortressChatTurnBase(arg), _d0(mActor, 0x800009d) {}

EnemyFortressChatTurn::~EnemyFortressChatTurn() = default;

bool EnemyFortressChatTurn::init_(sead::Heap* heap) {
    if (!EnemyFortressChatTurnBase::init_(heap))
        return false;
    _d0.x(mActor);
    return true;
}

void EnemyFortressChatTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyFortressChatTurnBase::enter_(params);
}

void EnemyFortressChatTurn::leave_() {
    EnemyFortressChatTurnBase::leave_();
}

void EnemyFortressChatTurn::loadParams_() {
    EnemyFortressChatTurnBase::loadParams_();
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

void EnemyFortressChatTurn::calc_() {
    auto& target = *mTargetActor_d;
    {
        sead::ScopedLock<sead::JobQueueLock> lock(&_d0._28);
        _d0._18 = target;
    }
    EnemyFortressChatTurnBase::calc_();
}

void EnemyFortressChatTurn::m32(ksys::act::BaseProcLink* link) {
    _d0.sub_710070DCC0(link, true);
}

bool EnemyFortressChatTurn::m33(const ksys::MessageAck* ack) {
    return ack->getType() == 0x800009d;
}

}  // namespace uking::action

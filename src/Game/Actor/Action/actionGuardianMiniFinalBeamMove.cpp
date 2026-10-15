#include "Game/Actor/Action/actionGuardianMiniFinalBeamMove.h"
#include "Game/Actor/Player/actPlayerBase.h"
#include "Game/Actor/actBeamBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::action {

void GuardianMiniFinalBeamMove::m36(const AttackInfo* info) {
    BeamMove::m36(info);

    auto* beam = sead::DynamicCast<act::BeamBase>(mActor);
    if (!beam)
        return;
    if (!hasAttackInfo(beam) || !info)
        return;

    auto* actor = beam->m48();
    if (!actor)
        return;
    // The existing isPlayerProfile helper takes a non-const BaseProcLink pointer.
    if (!isPlayerProfile(&const_cast<AttackInfo*>(info)->_50))
        return;

    auto* proc = info->_50.getProc(nullptr, nullptr);
    if (!sead::DynamicCast<ksys::act::Actor>(proc))
        return;

    auto* player = sead::DynamicCast<uking::act::PlayerBase>(proc);
    if (!player)
        return;
    if (!player->_cf0.isOnBit(0))
        return;

    sendMessage(*actor->getMesTransceiverId(), ksys::MessageType(0x8000043), beam);
    _80 = true;
}

GuardianMiniFinalBeamMove::GuardianMiniFinalBeamMove(const InitArg& arg) : GuardianBeamFire(arg) {}

GuardianMiniFinalBeamMove::~GuardianMiniFinalBeamMove() = default;

void GuardianMiniFinalBeamMove::enter_(ksys::act::ai::InlineParamPack* params) {
    GuardianBeamFire::enter_(params);
    _80 = false;
}

void GuardianMiniFinalBeamMove::leave_() {
    sub_7100194A58();
    GuardianBeamFire::leave_();
}

void GuardianMiniFinalBeamMove::loadParams_() {
    GuardianBeamFire::loadParams_();
}

void GuardianMiniFinalBeamMove::calc_() {
    GuardianBeamFire::calc_();
    sub_7100194A58();
}

bool GuardianMiniFinalBeamMove::isFinished() const {
    return ActionBase::isFinished();
}

}  // namespace uking::action

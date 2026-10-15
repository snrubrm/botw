#include "Game/Actor/Action/actionGuardianMiniFinalBeamMove.h"
#include "Game/Actor/Player/actPlayerBase.h"
#include "Game/Actor/actBeamBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::action {

void GuardianMiniFinalBeamMove::sub_7100194A58() {
    if (_80)
        return;

    auto* beam = sead::DynamicCast<act::BeamBase>(mActor);
    if (!beam)
        return;
    auto* actor = beam->m48();
    if (!actor)
        return;

    if (hasAttackInfo(beam)) {
        auto* info = getAttackInfo(beam, 0);
        if (info && isPlayerProfile(&const_cast<AttackInfo*>(info)->_50)) {
            auto* proc = info->_50.getProc(nullptr, nullptr);
            if (sead::DynamicCast<ksys::act::Actor>(proc) &&
                sead::DynamicCast<uking::act::PlayerBase>(proc) &&
                static_cast<uking::act::PlayerBase*>(proc)->_cf0.isOnBit(0)) {
                sendMessage(*actor->getMesTransceiverId(), ksys::MessageType(0x8000043), beam);
                _80 = true;
                return;
            }
        }
    }

    auto* body = beam->findPhysicsBodyByName("Atk", "AtkBody");
    if (!body)
        return;
    auto* contacts = body->getContactPointInfo();
    if (!contacts || contacts->getNumContactPoints() == 0 || contacts->begin().isEnd())
        return;

    auto it = contacts->begin();
    const auto end = contacts->end();
    for (; it != end; ++it) {
        auto* user_tag = (*it)->body_b->getUserTag();
        if (!user_tag)
            continue;
        if (auto* tag = sead::DynamicCast<ksys::act::PhysicsUserTag>(user_tag)) {
            if (auto* target = tag->getActor(nullptr, nullptr)) {
                if (auto* player = sead::DynamicCast<uking::act::PlayerBase>(target)) {
                    if (!player->isGuard()) {
                        sendMessage(*actor->getMesTransceiverId(), ksys::MessageType(0x8000043),
                                    beam);
                        _80 = true;
                        return;
                    }
                }
            }
        }
    }
}

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

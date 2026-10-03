#include "Game/AI/Action/actionEnemyFortressChatSpeak.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "KingSystem/Utils/Thread/MessageAck.h"

namespace uking::action {

EnemyFortressChatSpeak::EnemyFortressChatSpeak(const InitArg& arg)
    : EnemyFortressChatTalk(arg), _f0(mActor, 0x800009e), _170(mActor, 0x80000a2) {}

EnemyFortressChatSpeak::~EnemyFortressChatSpeak() = default;

bool EnemyFortressChatSpeak::init_(sead::Heap* heap) {
    if (!EnemyFortressChatTalk::init_(heap))
        return false;
    _f0.x(mActor);
    return true;
}

void EnemyFortressChatSpeak::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyFortressChatTalk::enter_(params);
}

void EnemyFortressChatSpeak::leave_() {
    EnemyFortressChatTalk::leave_();
}

void EnemyFortressChatSpeak::loadParams_() {
    EnemyFortressChatTalk::loadParams_();
}

void EnemyFortressChatSpeak::calc_() {
    EnemyFortressChatTalk::calc_();
}

void EnemyFortressChatSpeak::m32() {
    _f0.sub_710070DCC0(mTargetActor_d, true);
}

bool EnemyFortressChatSpeak::m33(const ksys::MessageAck* ack) {
    return ack->getType() == 0x800009e;
}

bool EnemyFortressChatSpeak::handleMessage_(const ksys::Message* message) {
    if (EnemyFortressChatTalk::handleMessage_(message))
        return true;

    if (_120.m2(*message)) {
        auto& link = sub_7100108EC8();
        {
            sead::ScopedLock<sead::JobQueueLock> lock(&_170._28);
            _170._18 = link;
        }
        _170.sub_710070DE10(_120._18, true);
        _120.x();
        return true;
    }
    return false;
}

}  // namespace uking::action

bool Unk_71023799b0::m2(const ksys::Message& message) {
    if (message.getType() != 0x80000a3)
        return false;

    auto* payload = static_cast<Unk_71023799b0_Payload*>(message.getUserData());
    if (!payload)
        return false;

    payload->x(&_38.mLink);
    _30 = true;
    _18 = message.getSource();
    return true;
}

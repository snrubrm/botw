#include "Game/AI/Action/actionEnemyAreaInOutSendMessage.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::action {

EnemyAreaInOutSendMessage::EnemyAreaInOutSendMessage(const InitArg& arg)
    : ActorAreaInOutSendMessage(arg) {}

EnemyAreaInOutSendMessage::~EnemyAreaInOutSendMessage() {
    _70.freeBuffer();
}

bool EnemyAreaInOutSendMessage::init_(sead::Heap* heap) {
    if (!ActorAreaInOutSendMessage::init_(heap))
        return false;
    _70.tryAllocBuffer(1, heap);
    _70[0]._0 = ksys::phys::ContactLayer::SensorEnemy;
    return true;
}

void EnemyAreaInOutSendMessage::enter_(ksys::act::ai::InlineParamPack* params) {
    ActorAreaInOutSendMessage::enter_(params);
}

void EnemyAreaInOutSendMessage::leave_() {
    ActorAreaInOutSendMessage::leave_();
}

void EnemyAreaInOutSendMessage::loadParams_() {
    ActorAreaInOutSendMessage::loadParams_();
    getStaticParam(&mMessageID_s, "MessageID");
}

void EnemyAreaInOutSendMessage::calc_() {
    ActorAreaInOutSendMessage::calc_();
}

// NON_MATCHING: stack slot of the MessageType temporary (as AreaBottomTag::m15)
void EnemyAreaInOutSendMessage::m32(const ksys::act::ActorConstDataAccess& accessor) {
    if (*mMessageID_s == 0)
        sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x3000015), nullptr);
}

// NON_MATCHING: stack slot of the MessageType temporary (as AreaBottomTag::m15)
void EnemyAreaInOutSendMessage::m33(const ksys::act::ActorConstDataAccess& accessor) {
    if (*mMessageID_s == 0)
        sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x3000016), nullptr);
}

}  // namespace uking::action

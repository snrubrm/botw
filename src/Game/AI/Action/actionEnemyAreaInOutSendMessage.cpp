#include "Game/AI/Action/actionEnemyAreaInOutSendMessage.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::action {

EnemyAreaInOutSendMessage::EnemyAreaInOutSendMessage(const InitArg& arg)
    : AreaInOutSendMessage(arg) {}

EnemyAreaInOutSendMessage::~EnemyAreaInOutSendMessage() {
    _70.freeBuffer();
}

bool EnemyAreaInOutSendMessage::init_(sead::Heap* heap) {
    if (!AreaInOutSendMessage::init_(heap))
        return false;
    _70.tryAllocBuffer(1, heap);
    _70[0]._0 = ksys::phys::ContactLayer::SensorEnemy;
    return true;
}

void EnemyAreaInOutSendMessage::enter_(ksys::act::ai::InlineParamPack* params) {
    AreaInOutSendMessage::enter_(params);
}

void EnemyAreaInOutSendMessage::leave_() {
    AreaInOutSendMessage::leave_();
}

void EnemyAreaInOutSendMessage::loadParams_() {
    AreaInOutSendMessage::loadParams_();
    getStaticParam(&mMessageID_s, "MessageID");
}

void EnemyAreaInOutSendMessage::calc_() {
    AreaInOutSendMessage::calc_();
}

void EnemyAreaInOutSendMessage::m32(const ksys::act::ActorLinkConstDataAccess& accessor) {
    if (*mMessageID_s == 0)
        sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x3000015), nullptr);
}

void EnemyAreaInOutSendMessage::m33(const ksys::act::ActorLinkConstDataAccess& accessor) {
    if (*mMessageID_s == 0)
        sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x3000016), nullptr);
}

}  // namespace uking::action

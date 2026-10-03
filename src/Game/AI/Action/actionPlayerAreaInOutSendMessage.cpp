#include "Game/AI/Action/actionPlayerAreaInOutSendMessage.h"
#include <mc/seadJobQueue.h>
#include "Game/gameSceneSubsys14.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::action {

PlayerAreaInOutSendMessage::PlayerAreaInOutSendMessage(const InitArg& arg)
    : ActorAreaInOutSendMessage(arg) {}

PlayerAreaInOutSendMessage::~PlayerAreaInOutSendMessage() = default;

bool PlayerAreaInOutSendMessage::init_(sead::Heap* heap) {
    if (!ActorAreaInOutSendMessage::init_(heap))
        return false;

    Unk_71023b0898_Payload::Data data;
    data._8.acquire(mActor, false);
    switch (*mMessageSet_s) {
    case 0:
        data._0 = 0;
        break;
    case 1:
        data._0 = 1;
        break;
    case 2:
        data._0 = 2;
        break;
    case 3:
        data._0 = 3;
        break;
    case 4:
        data._0 = 5;
        break;
    case 5:
        data._0 = 6;
        break;
    case 6:
        data._0 = 7;
        break;
    case 7:
        data._0 = 8;
        break;
    }
    _70._18.x(data);
    return true;
}

void PlayerAreaInOutSendMessage::enter_(ksys::act::ai::InlineParamPack* params) {
    ActorAreaInOutSendMessage::enter_(params);
}

void PlayerAreaInOutSendMessage::leave_() {
    ActorAreaInOutSendMessage::leave_();
}

void PlayerAreaInOutSendMessage::loadParams_() {
    ActorAreaInOutSendMessage::loadParams_();
    getStaticParam(&mMessageSet_s, "MessageSet");
}

void PlayerAreaInOutSendMessage::calc_() {
    ActorAreaInOutSendMessage::calc_();
}

bool PlayerAreaInOutSendMessage::m34(const ksys::act::ActorConstDataAccess& accessor) {
    return !ksys::act::isPlayerProfile(accessor);
}

void PlayerAreaInOutSendMessage::m32(const ksys::act::ActorConstDataAccess& accessor) {
    {
        sead::ScopedLock<sead::JobQueueLock> lock(&_70._18.mLock);
        _70._18._0 = true;
    }
    _70.sub_710070DBB0(*GameSceneSubsys14::instance()->_180, true);
}

// NON_MATCHING: the original keeps &_70 (not `this`) in a callee-saved register across
// isActorDeletedOrDeleting()
void PlayerAreaInOutSendMessage::m33(const ksys::act::ActorConstDataAccess& accessor) {
    {
        sead::ScopedLock<sead::JobQueueLock> lock(&_70._18.mLock);
        _70._18._0 = false;
    }
    if (isActorDeletedOrDeleting())
        return;
    _70.sub_710070DBB0(*GameSceneSubsys14::instance()->_180, true);
}

}  // namespace uking::action

#include "Game/AI/AI/aiNPCTravel.h"
#include "Game/Actor/actNPC.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

NPCTravel::NPCTravel(const InitArg& arg) : NPCTravelBase(arg) {}

NPCTravel::~NPCTravel() = default;

void NPCTravel::onPreDelete() {
    if (_88 && _88->_840 == &_1f8)
        _88->_840 = nullptr;
    if (_f8.isRegistered()) {
        mActor->sendMessage(_f8, ksys::MessageType(0x8000076), nullptr, true);
        if (_88)
            _88->_fe8 &= ~0x40000;
    }
}

bool NPCTravel::init_(sead::Heap* heap) {
    return NPCTravelBase::init_(heap);
}

void NPCTravel::enter_(ksys::act::ai::InlineParamPack* params) {
    NPCTravelBase::enter_(params);
}

void NPCTravel::leave_() {}

void NPCTravel::loadParams_() {
    NPCTravelBase::loadParams_();
    getStaticParam(&mWaitHorseReturnDist_s, "WaitHorseReturnDist");
    getStaticParam(&mGiveUpWaitHorseTime_s, "GiveUpWaitHorseTime");
}

}  // namespace uking::ai

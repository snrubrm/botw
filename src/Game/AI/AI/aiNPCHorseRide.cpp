#include "Game/AI/AI/aiNPCHorseRide.h"
#include "Game/Actor/actNPC.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

NPCHorseRide::NPCHorseRide(const InitArg& arg) : NonPlayerHorseRide(arg) {}

NPCHorseRide::~NPCHorseRide() = default;

void NPCHorseRide::onPreDelete() {
    m34();
    if (_158.isRegistered()) {
        mActor->sendMessage(_158, ksys::MessageType(0x8000076), nullptr, true);
        if (_110)
            _110->_fe8 &= ~0x40000;
    }
}

bool NPCHorseRide::init_(sead::Heap* heap) {
    return NonPlayerHorseRide::init_(heap);
}

void NPCHorseRide::enter_(ksys::act::ai::InlineParamPack* params) {
    NonPlayerHorseRide::enter_(params);
}

void NPCHorseRide::leave_() {
    NonPlayerHorseRide::leave_();
}

void NPCHorseRide::loadParams_() {
    getStaticParam(&mGearLevel_s, "GearLevel");
    getStaticParam(&mGearResetPathNum_s, "GearResetPathNum");
    getStaticParam(&mPlayerNearDistance_s, "PlayerNearDistance");
    getAITreeVariable(&mEventBindUnit_a, "EventBindUnit");
}

}  // namespace uking::ai

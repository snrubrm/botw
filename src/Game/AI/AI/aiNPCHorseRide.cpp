#include "Game/AI/AI/aiNPCHorseRide.h"
#include "Game/Actor/actNPC.h"
#include "Game/Actor/actHorseRideInfo.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Utils/Thread/Message.h"

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
    if (!NonPlayerHorseRide::init_(heap))
        return false;
    _110 = sead::DynamicCast<act::NPC>(mActor);
    *static_cast<Unk_71025afb58**>(mEventBindUnit_a) = &_270;
    _270._8 = &_38;
    return true;
}

void NPCHorseRide::enter_(ksys::act::ai::InlineParamPack* params) {
    NonPlayerHorseRide::enter_(params);
}

void NPCHorseRide::leave_() {
    if (!mActor->get1a0()) {
        auto* object = mActor->getMapObject();
        if (!(object && object->getFlags0().isOn(ksys::map::Object::Flag0::_20000)) &&
            !testRootAiFlag(ksys::act::ai::RootAiFlag::_5)) {
            return;
        }
    }

    if (mActor->getPlayerRideInfo()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&mActor->getPlayerRideInfo()->_18, &accessor);
        mActor->sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x3800007),
                            mActor, true);
    }
    NonPlayerHorseRide::leave_();
}

void NPCHorseRide::loadParams_() {
    getStaticParam(&mGearLevel_s, "GearLevel");
    getStaticParam(&mGearResetPathNum_s, "GearResetPathNum");
    getStaticParam(&mPlayerNearDistance_s, "PlayerNearDistance");
    getAITreeVariable(&mEventBindUnit_a, "EventBindUnit");
}

void NPCHorseRide::m36() {
    ksys::act::ai::InlineParamPack pack;
    pack.addFloat(_100, "GearSpeed", -1);
    changeChild("乗る", &pack);
}

}  // namespace uking::ai

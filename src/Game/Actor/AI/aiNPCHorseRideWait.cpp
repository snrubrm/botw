#include "Game/Actor/AI/aiNPCHorseRideWait.h"
#include "Game/Actor/actHorseRideInfo.h"
#include "Game/Actor/actNPC.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/aiRootAi.h"
#include "KingSystem/ActorSystem/actSchedule.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"

namespace uking::ai {

NPCHorseRideWait::NPCHorseRideWait(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NPCHorseRideWait::~NPCHorseRideWait() = default;

bool NPCHorseRideWait::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: rotation arithmetic, accessor cleanup and stack slots differ.
void NPCHorseRideWait::enter_(ksys::act::ai::InlineParamPack* params) {
    _d8 = false;
    if (auto* npc = sead::DynamicCast<act::NPC>(mActor)) {
        if (auto* point = npc->_f80) {
            _38._40.set(point->_0);
            sead::Matrix33f rotation;
            rotation.makeR({0.0f, point->_c.y, 0.0f});
            _88._40.setRotated(rotation, sead::Vector3f::ez);
        } else {
            setFailed();
        }
    }
    const auto& position = mActor->getMtx().getTranslation();
    const f32 distance = (sead::Vector2f(position.x, position.z) -
                          sead::Vector2f(_38._40.x, _38._40.z)).length();
    if (!(distance < 4.0f)) {
        sub_71004CC76C();
        return;
    }
    {
        ksys::act::ActorLinkConstDataAccess accessor;
        if (ksys::act::acquireActor(&mActor->getPlayerRideInfo()->_18, &accessor)) {
            mActor->sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x3800005),
                                &_88, true);
        }
    }
    sub_71004CC680();
}

// NON_MATCHING: same control flow; stack layout / register allocation only (the original keeps the
// MessageType temporary at sp+4 below the accessor and rematerialises &accessor for the destructor)
void NPCHorseRideWait::leave_() {
    if (!mActor->get1a0()) {
        auto* object = mActor->getMapObject();
        if (!(object && object->getFlags0().isOn(ksys::map::Object::Flag0::_20000)) &&
            !testRootAiFlag(ksys::act::ai::RootAiFlag::_5)) {
            if (auto* schedule = mActor->getSchedule())
                schedule->_88 = "";
            return;
        }
    }

    ksys::act::ActorLinkConstDataAccess accessor;
    if (ksys::act::acquireActor(&mActor->getPlayerRideInfo()->_18, &accessor)) {
        mActor->sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x3800007),
                            mActor, true);
    }
}

bool NPCHorseRideWait::handleMessage_(const ksys::Message* message) {
    if (message && isCurrentChild("移動")) {
        if (message->getType() == 0x3800023) {
            _d8 = true;
            return true;
        }
        if (message->getType() == 0x3800027) {
            _d9 = true;
            return false;
        }
        if (message->getType() == 0x3800028) {
            _d9 = false;
            sub_71004CC76C();
            return true;
        }
    }
    return false;
}

// NON_MATCHING: same as leave_ (the original rematerialises &accessor for each accessor destructor
// instead of keeping it in a callee-saved register; regalloc only)
void NPCHorseRideWait::sub_71004CC76C() {
    if (auto* schedule = mActor->getSchedule())
        schedule->_88 = "";
    _dc = 1;

    {
        ksys::act::ActorLinkConstDataAccess accessor;
        if (ksys::act::acquireActor(&mActor->getPlayerRideInfo()->_18, &accessor)) {
            mActor->sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x380000b),
                                reinterpret_cast<void*>(_dc), true);
        }
    }
    {
        ksys::act::ActorLinkConstDataAccess accessor;
        if (ksys::act::acquireActor(&mActor->getPlayerRideInfo()->_18, &accessor)) {
            mActor->sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x3800004),
                                &_38, true);
        }
    }

    ksys::act::ai::InlineParamPack params;
    params.addFloat(f32(_dc), "GearSpeed", -1);
    changeChild("移動", &params);
}

// NON_MATCHING: sensor iteration saved registers and null-output branch layout.
bool NPCHorseRideWait::sub_71004CCCB8(s32 level, sead::Vector3f* position) {
    auto* awareness = mActor->getAwareness();
    if (!awareness)
        return false;
    auto* sensor = awareness->_260[2];
    if (!sensor)
        return false;
    const s32 count = sensor->_8.size();
    for (s32 i = 0; i < count; ++i) {
        sensor = awareness->_260[2];
        if (!sensor || i >= sensor->_8.size())
            continue;
        auto* entry = ksys::act::sub_7100D78E30(&sensor->_8, i);
        if (!entry || !(static_cast<f32>(level) <= entry->_a4))
            continue;
        ksys::act::ActorLinkConstDataAccess accessor;
        if (position && ksys::act::acquireActor(&entry->_0.mLink, &accessor)) {
            accessor.getActorMtx().getTranslation(*position);
            return true;
        }
    }
    return false;
}

void NPCHorseRideWait::loadParams_() {}

// 0x71004cc680
void NPCHorseRideWait::sub_71004CC680() {
    if (auto* schedule = mActor->getSchedule())
        schedule->_88 = schedule->_68;
    _dc = 0;
    ksys::act::ai::InlineParamPack pack;
    pack.addFloat(f32(_dc), "GearSpeed", -1);
    changeChild("到着", &pack);
}

}  // namespace uking::ai

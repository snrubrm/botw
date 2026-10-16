#include "Game/gameStasisMgr.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/Player/actPlayerBase.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorSystem.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actReaction.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking {

SEAD_SINGLETON_DISPOSER_IMPL(StasisMgr)

// NON_MATCHING: the original zero-fills mEffects with one memset (a trivially constructible handle);
// our xlink2::Handle has a user-provided constructor, so each handle is stored separately.
StasisMgr::StasisMgr() {
    ksys::act::ActorSystem::instance()->setStasisMessageSender(this);
}

StasisMgr::~StasisMgr() {
    ksys::act::ActorSystem::instance()->setStasisMessageSender(nullptr);
}

// TODO: not decompiled yet (W). Handles the stasis messages 0x3000003 - 0x3000006 for `actor`.
s32 StasisMgr::m0(ksys::act::Actor* actor, void* request) {
    return 0;
}

void StasisMgr::sub_710067F9A8() {
    _40 = 0;
    _41 = false;
    _42 = false;
    _43 = 0;
    _44 = 0;
    _48 = 0;
    _4c = 0;
    _54 = 1.0f;
    _58 = 1.0f;
    for (auto& entry : mEntries) {
        entry.link.reset();
        entry._2a8.kill();
        entry.damage.sub_71006D99F4();
    }
    for (auto& effect : mEffects)
        effect.kill();
    _32e0.reset();
}

void StasisMgr::sub_7100680368(bool on_processing_thread) {
    for (auto& entry : mEntries) {
        if (entry.link.hasProc()) {
            ksys::act::ActorLinkConstDataAccess accessor;
            ksys::act::acquireActor(&entry.link, &accessor);
            if (on_processing_thread) {
                mTransceiver.sendMessageOnProcessingThread(*accessor.getMessageTransceiverId(),
                                                           ksys::MessageType(0x3000004),
                                                           nullptr, true);
            } else {
                mTransceiver.sendMessage(*accessor.getMessageTransceiverId(),
                                         ksys::MessageType(0x3000004), nullptr, true);
            }
        }
        entry._2a8.kill();
    }

    if (auto* info = act::PlayerInfo::instance()) {
        ksys::act::acc::PlayerBase player;
        ksys::act::acquireActor(&info->getPlayerLink(), &player);
        f32 time = player.getStopTimerReloadTime();
        if (time <= 1.0f)
            time = 1.0f;
        _58 = 1.0f / time;
        const f32 progress = _42 ? std::max(_48 * _54, 0.0f) : 0.0f;
        time *= 1.0f - progress;
        if (time <= 1.0f)
            time = 1.0f;
        _44 = time;
    }
    _41 = false;
    _42 = false;
    _48 = 0;
}

void StasisMgr::sub_7100680920(ksys::act::Actor* actor) {
    if (actor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_40)) {
        if (_42) {
            ksys::act::ActorLinkConstDataAccess accessor;
            ksys::act::acquireActor(&mEntries[0].link, &accessor);
            mTransceiver.sendMessage(*accessor.getMessageTransceiverId(),
                                     ksys::MessageType(0x3000004), nullptr, true);
        }
    } else if (!_42 && ksys::act::canBeStasised(actor, false)) {
        mTransceiver.sendMessage(*actor->getMesTransceiverId(), ksys::MessageType(0x3000003),
                                 nullptr, true);
    }
}

void* StasisMgr::m4(ksys::act::Actor* actor) {
    for (auto it = mEntries.begin(); it != mEntries.end(); ++it) {
        if (it->link.hasProcById(actor))
            return &it->_2c8;
    }
    return nullptr;
}

void StasisMgr::sub_7100680AC8(Entry* entry, ksys::act::BaseProc* proc) {
    entry->link.acquire(proc, false);
    entry->damage.sub_71006D99F4();
    entry->_2a8.kill();
}

s32 StasisMgr::m2(const sead::Matrix34f& mtx) {
    s32 index = 0;
    for (auto& effect : mEffects) {
        if (!effect.isActive()) {
            effect = ksys::eft::searchAndEmitELink(ksys::act::Reaction::instance()->_30,
                                                   "BitaLocked_Trace");
            return m3(mtx, index);
        }
        ++index;
    }
    return -1;
}

s32 StasisMgr::m3(const sead::Matrix34f& mtx, s32 index) {
    auto& handle = mEffects[index];
    if (!handle.isActive())
        return -1;
    handle.setMatrix(mtx);
    return index;
}

void StasisMgr::sendMessage(ksys::act::Actor* actor, ksys::MessageType type,
                            bool on_processing_thread) {
    if (on_processing_thread)
        mTransceiver.sendMessageOnProcessingThread(*actor->getMesTransceiverId(), type, nullptr,
                                                   true);
    else
        mTransceiver.sendMessage(*actor->getMesTransceiverId(), type, nullptr, true);
}

f32 StasisMgr::sub_7100681570() const {
    return std::max(_44 * _58, 0.0f);
}

act::DamageManagerUnk220* StasisMgr::sub_7100681588(ksys::act::Actor* actor) {
    for (auto it = mEntries.begin(); it != mEntries.end(); ++it) {
        if (it->link.hasProcById(actor))
            return &it->damage;
    }
    return nullptr;
}

}  // namespace uking

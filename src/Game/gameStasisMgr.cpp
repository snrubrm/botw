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

// NON_MATCHING: the original recomputes each entry address from the index (as m2 / m4).
void StasisMgr::sub_7100680368(bool on_processing_thread) {
    for (s32 i = 0; i < mEntries.size(); ++i) {
        auto& entry = mEntries[i];
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
        f32 progress = 0.0f;
        if (_42) {
            progress = _48 * _54;
            if (progress <= 0.0f)
                progress = 0.0f;
        }
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

// NON_MATCHING: our build unrolls the 16-entry loop.
void* StasisMgr::m4(ksys::act::Actor* actor) {
    for (s32 i = 0; i < mEntries.size(); ++i) {
        if (mEntries[i].link.hasProcById(actor))
            return &mEntries[i]._2c8;
    }
    return nullptr;
}

// NON_MATCHING: the original recomputes the handle address from the index each iteration; ours
// keeps a pointer.
void StasisMgr::sub_7100680AC8(Entry* entry, ksys::act::BaseProc* proc) {
    entry->link.acquire(proc, false);
    entry->damage.sub_71006D99F4();
    entry->_2a8.kill();
}

s32 StasisMgr::m2(const sead::Matrix34f& mtx) {
    s32 index = 0;
    for (s32 i = 0; i < mEffects.size(); ++i) {
        if (!mEffects[i].isActive()) {
            mEffects[i] = ksys::eft::searchAndEmitELink(ksys::act::Reaction::instance()->_30,
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

// NON_MATCHING: our build unrolls the 16-entry loop (as m4).
act::DamageManagerUnk220* StasisMgr::sub_7100681588(ksys::act::Actor* actor) {
    for (s32 i = 0; i < mEntries.size(); ++i) {
        if (mEntries[i].link.hasProcById(actor))
            return &mEntries[i].damage;
    }
    return nullptr;
}

}  // namespace uking

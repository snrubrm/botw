#include "Game/gameStasisMgr.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSystem.h"
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

}  // namespace uking

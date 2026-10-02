#include "Game/AI/Action/actionActorAreaInOutSendMessage.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::action {

ActorAreaInOutSendMessage::ActorAreaInOutSendMessage(const InitArg& arg) : AreaTagAction(arg) {}

ActorAreaInOutSendMessage::~ActorAreaInOutSendMessage() {
    _40[0].freeBuffer();
    _40[1].freeBuffer();
}

bool ActorAreaInOutSendMessage::init_(sead::Heap* heap) {
    _40[0].tryAllocBuffer(*mBufferNum_s, heap);
    _40[1].tryAllocBuffer(*mBufferNum_s, heap);
    return true;
}

// NON_MATCHING: the original's sead::Buffer iterator compares only the index (ours also compares the
// buffer pointer, which is reloaded after each call)
void ActorAreaInOutSendMessage::enter_(ksys::act::ai::InlineParamPack* params) {
    AreaTagAction::enter_(params);
    _64 = 0;
    for (auto it = _40[0].begin(); it != _40[0].end(); ++it)
        it->reset();
    for (auto it = _40[1].begin(); it != _40[1].end(); ++it)
        it->reset();
}

// NON_MATCHING: the original's sead::Buffer iterator compares only the index (ours also compares the
// buffer pointer, which is reloaded after each call)
void ActorAreaInOutSendMessage::leave_() {
    auto& buffer = _40[_64];
    for (auto it = buffer.begin(); it != buffer.end(); ++it) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&*it, &accessor);
        m33(accessor);
    }
}

void ActorAreaInOutSendMessage::loadParams_() {
    getStaticParam(&mBufferNum_s, "BufferNum");
}

void ActorAreaInOutSendMessage::calc_() {
    AreaTagAction::calc_();
}

// NON_MATCHING: the original's sead::Buffer iterator compares only the index (ours also compares the
// buffer pointer, which is reloaded after each call)
void ActorAreaInOutSendMessage::m2() {
    s32 next = _64 + 1;
    if (u32(next) > 1)
        next = 0;
    _64 = next;
    for (auto it = _40[_64].begin(); it != _40[_64].end(); ++it)
        it->reset();
}

bool ActorAreaInOutSendMessage::m15(const ksys::act::ActorConstDataAccess& accessor) {
    if (m34(accessor))
        return false;

    auto& buffer = _40[_64];
    const s32 size = buffer.size();
    if (size < 1)
        return true;

    s32 i = 0;
    while (buffer[i].hasProcInCalcState()) {
        if (++i >= size)
            return true;
    }
    accessor.linkAcquire(&buffer[i]);
    return false;
}

// NON_MATCHING: regalloc and address computation order of the two buffers
void ActorAreaInOutSendMessage::m5() {
    const s32 prev_idx = _64 < 1 ? 1 : _64 - 1;
    auto& cur = _40[_64];
    auto& prev = _40[prev_idx];
    const s32 cur_size = cur.size();
    const s32 prev_size = prev.size();
    _60 = 0;

    for (s32 i = 0; i < cur_size; ++i) {
        bool entered = true;
        for (s32 j = 0; j < prev_size; ++j) {
            if (cur[i].hasProcInCalcState() && cur[i] == prev[j]) {
                _60 |= 1 << j;
                entered = false;
                break;
            }
        }
        if (entered && cur[i].hasProcInCalcState()) {
            ksys::act::ActorConstDataAccess accessor;
            ksys::act::acquireActor(&cur[i], &accessor);
            m32(accessor);
        }
    }

    for (s32 j = 0; j < prev_size; ++j) {
        if (!(_60 & (1 << j)) && prev[j].hasProcInCalcState()) {
            ksys::act::ActorConstDataAccess accessor;
            ksys::act::acquireActor(&prev[j], &accessor);
            m33(accessor);
        }
    }
}

}  // namespace uking::action

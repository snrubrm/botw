#include "KingSystem/Event/evtActionContext.h"
#include <cstring>
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "evfl/Action.h"
#include "evfl/ResTimeline.h"

namespace ksys::evt {

// 0x7100da5360
void ActionContext::x_3(act::BaseProcLink* link) {
    if (!link->hasProc())
        return;
    act::ActorConstDataAccess accessor;
    act::acquireActor(link, &accessor);
    mStatus2 = 0;
    Manager::instance()->sub_7100DB0FB0(*accessor.getMessageTransceiverId(), MessageType(0x800006), this);
}

// 0x7100da53e4
void ActionContext::sub_7100DA53E4(act::BaseProcLink* link) {
    if (!link->hasProc())
        return;
    act::ActorConstDataAccess accessor;
    act::acquireActor(link, &accessor);
    mStatus2 = 1;
    Manager::instance()->sub_7100DB0FB0(*accessor.getMessageTransceiverId(), MessageType(0x800008), this);
}

// 0x7100da546c
void ActionContext::setStatus2(const evfl::ActionArg&) {
    mStatus = 2;
}

// 0x7100da5478
void ActionContext::setStatus1(const evfl::ActionArg&) {
    mStatus = 1;
}

// 0x7100da5484
void ActionContext::setStatus1_0(const evfl::ActionArg&) {
    mStatus = 1;
}

// 0x7100da56b8
void ActionContext::reset() {
    mStatus = 0;
    _af4 = 0;
}

// 0x7100da5678
void ActionContext::x_0() {
    _a50 = 0;
}

// 0x7100da5708
void ActionContext::statusStuff_2() {
    const s32 status = mStatus;
    mStatus = status == 3 ? 7 : (status == 4 ? 8 : 0);
}

// 0x7100da572c
void ActionContext::x_2() {
    switch (mStatus) {
    case 1:
        mStatus = 7;
        break;
    case 2:
        mStatus = 8;
        break;
    default:
        mStatus = 0;
        _af4 = 0;
        break;
    }
}

// 0x7100da5680
void ActionContext::x_1() {
    switch (mStatus) {
    case 1:
        mStatus = 3;
        break;
    case 2:
        mStatus = 4;
        break;
    default:
        mStatus = 0;
        _af4 = 0;
        break;
    }
}

// 0x7100da5490
bool ActionContext::statusStuff(bool) {
    switch (mStatus) {
    case 2:
        mStatus = 1;
        return true;
    case 4:
        mStatus = 3;
        return true;
    case 6:
    case 8:
        return true;
    default:
        return false;
    }
}

// 0x7100da54e0
bool ActionContext::statusStuff_0() {
    switch (mStatus) {
    case 2:
        mStatus = 1;
        return true;
    case 4:
        mStatus = 3;
        return true;
    case 6:
    case 8:
        mStatus = 0;
        return true;
    default:
        return false;
    }
}

// 0x7100da56c4
void ActionContext::statusStuff_1(act::Actor* actor) {
    (void)actor;
    switch (mStatus) {
    case 0:
    case 5:
        break;
    case 3:
        mStatus = 5;
        break;
    case 4:
        mStatus = 6;
        break;
    default:
        mStatus = 0;
        _af4 = 0;
        break;
    }
}

// 0x7100da7b1c (CSV unnamed): construct the strings and the request nodes.
// NON_MATCHING: the 32 request-node constructions fully unroll in ours (32 out-of-line
// link calls plus an unrolled-by-2 field loop) while the original keeps a single rolled
// loop holding one link call plus the field stores. Two source shapes tried (NSDMI element
// init, explicit field loop); neither reproduces the rolled fusion, and placement-new to
// force it is not honest source. All member offsets/stores/calls match.
ActionContext::ActionContext() {
    for (s32 i = 0; i < 32; ++i) {
        _50[i]._20 = -1;
        _50[i]._28 = 0;
        _50[i]._30 = 0;
    }
    reset();
    _48 = 0;
    mStatus2 = 2;
    _a58 = nullptr;
    _40 = 0;
    _44 = 0.0f;
    _af0 = -1;
}

// 0x7100da5528 (CSV unnamed): fill the context from a name, an action argument and a value.
void ActionContext::init(const sead::SafeString& name, const evfl::ActionArg& arg, s32 a3) {
    // Discarded call that really is in the target asm (ensures `name` is terminated before
    // its top is read below; the top itself comes from the reload, as in sub_7100AA2FA0).
    char* dst = const_cast<char*>(_8.getStringTop());
    name.cstr();
    const char* top = name.getStringTop();
    if (dst != top) {
        s32 len = name.calcLength();
        const s32 cap = _8.getBufferSize();
        if (len >= cap)
            len = cap - 1;
        memcpy(dst, top, len);
        dst[len] = sead::SafeString::cNullChar;
    }
    _af4 = 0;
    _a58 = nullptr;
    _af0 = a3;
    const u32 trigger = u32(arg.trigger_type) - 1;
    if (trigger <= 1) {
        _48 = arg.res.clip->_c - 1;
        _44 = arg.res.clip->duration;
    } else {
        _48 = -1;
        _44 = -1.0f;
    }
    _a50 = 0;
    _40 = -1;
}

}  // namespace ksys::evt

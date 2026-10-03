#include "Game/AI/Action/actionEnemyFortressChatTalk.h"
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiUnk_710001A69C.h"
#include "Game/AI/aiUnk_71025b1808.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "KingSystem/Utils/Thread/MessageAck.h"

namespace uking::action {

EnemyFortressChatTalk::EnemyFortressChatTalk(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EnemyFortressChatTalk::~EnemyFortressChatTalk() = default;

bool EnemyFortressChatTalk::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EnemyFortressChatTalk::enter_(ksys::act::ai::InlineParamPack* params) {
    _e0 = *mTryNum_s;
    _e8 = false;
    _e9 = true;
    _40.x();
    _90.x();
    _e4 = f32(*mTimeOut_s);
}

void EnemyFortressChatTalk::leave_() {
    ksys::act::ai::Action::leave_();
}

void EnemyFortressChatTalk::loadParams_() {
    getStaticParam(&mTryNum_s, "TryNum");
    getDynamicParam(&mTargetActor_d, "TargetActor");
    getStaticParam(&mTimeOut_s, "TimeOut");
    getAITreeVariable(&mRegistedActorUnit_a, "RegistedActorUnit");
}

// NON_MATCHING: the original decrements `_e0` with `subs w8, w8, #1; b.lt`; any source form of the
// `_e0 - 1 < 0` test is folded to `cmp w8, #0; b.le` here.
void EnemyFortressChatTalk::calc_() {
    if (!mTargetActor_d->hasProcInCalcState() || _90._30) {
        setFailed();
        return;
    }

    if (!_e9)
        return;

    if (_e8) {
        if (_40._30) {
            setFinished();
            return;
        }
        ksys::Timer::update(&_e4, -1.0f);
        if (_e4 <= 0.0f)
            setFailed();
        return;
    }

    const s32 remaining = _e0 - 1;
    if (remaining < 0) {
        setFailed();
        return;
    }
    _e0 = remaining;
    m32();
    _e9 = false;
}

// NON_MATCHING: register allocation only (the original rematerialises `this + 0x78` / `this + 0xc8` for
// the BaseProcLink comparison, ours keeps it in a callee-saved register across the lock).
bool EnemyFortressChatTalk::handleMessage_(const ksys::Message* message) {
    if (_90._30)
        return false;

    if (!_40._30 && _40.m2(*message)) {
        if (_40._38.mLink == *mTargetActor_d)
            return true;
        _40.x();
        return false;
    }

    if (!_90._30 && _90.m2(*message)) {
        if (_90._38.mLink == *mTargetActor_d) {
            _40.x();
            return true;
        }
        _90.x();
    }
    return false;
}

bool EnemyFortressChatTalk::handleAck_(const ksys::MessageAck* ack) {
    if (!m33(ack))
        return false;
    _e9 = true;
    _e8 = ack->isSuccess() && ack->isDestinationValid();
    return true;
}

void EnemyFortressChatTalk::m32() {}

bool EnemyFortressChatTalk::m33(const ksys::MessageAck* ack) {
    return false;
}

ksys::act::BaseProcLink& EnemyFortressChatTalk::sub_7100108DA4() {
    auto* unit =
        sead::DynamicCast<Unk_71025b1808>(*static_cast<Unk_71025afb58**>(mRegistedActorUnit_a));
    if (unit) {
        ksys::act::BaseProcLink* result = nullptr;
        u32 n = 1;
        for (auto& entry : unit->_8.mEntries) {
            if (entry.link == *mTargetActor_d)
                continue;
            if (!entry.link.hasProcInCalcState())
                continue;
            if (sead::GlobalRandom::instance()->getU32(n) == 0)
                result = &entry.link;
            ++n;
        }
        if (result)
            return *result;
    }
    return ksys::act::getDummyBaseProcLink();
}

ksys::act::BaseProcLink& EnemyFortressChatTalk::sub_7100108EC8() {
    auto* unit =
        sead::DynamicCast<Unk_71025b1808>(*static_cast<Unk_71025afb58**>(mRegistedActorUnit_a));
    if (unit) {
        ksys::act::BaseProcLink* result = nullptr;
        u32 n = 1;
        for (auto& entry : unit->_8.mEntries) {
            if (entry.link == *mTargetActor_d)
                continue;
            ksys::act::ActorConstDataAccess accessor;
            ksys::act::acquireActor(&entry.link, &accessor);
            if (entry.link.hasProcInCalcState() && sub_710001A69C(&accessor, 0x1000)) {
                if (sead::GlobalRandom::instance()->getU32(n) == 0)
                    result = &entry.link;
                ++n;
            }
        }
        if (result)
            return *result;
    }
    return ksys::act::getDummyBaseProcLink();
}

}  // namespace uking::action

bool Unk_7102379b00::m2(const ksys::Message& message) {
    if (message.getType() != 0x800009f)
        return false;

    auto* payload = static_cast<Unk_7102379b00_Payload*>(message.getUserData());
    if (!payload)
        return false;

    payload->x(&_38.mLink);
    _30 = true;
    _18 = message.getSource();
    return true;
}

bool Unk_7102379b30::m2(const ksys::Message& message) {
    if (message.getType() != 0x80000a0)
        return false;

    auto* payload = static_cast<Unk_7102379b30_Payload*>(message.getUserData());
    if (!payload)
        return false;

    payload->x(&_38.mLink);
    _30 = true;
    _18 = message.getSource();
    return true;
}

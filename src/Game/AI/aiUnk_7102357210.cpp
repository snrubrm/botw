#include "Game/AI/aiUnk_7102357210.h"
#include <prim/seadScopedLock.h>
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actActor.h"

Unk_7102450498::~Unk_7102450498() = default;

bool Unk_7102450498::m2(const ksys::Message& message) {
    if (message.getType().value != 0x8000021)
        return false;

    auto* payload = static_cast<Unk_71023f83e8_Payload*>(message.getUserData());
    if (!payload)
        return false;

    {
        sead::ScopedLock<sead::JobQueueLock> lock(&payload->mLock);
        _34._0 = payload->_0;
        _34._c = payload->_c;
        _34._10 = payload->_10;
    }
    _30 = true;
    _18 = message.getSource();
    return true;
}

void Unk_7102450498::m3() {
    sead::ScopedLock<sead::JobQueueLock> lock(&_34.mLock);
    _34._0 = sead::Vector3f::zero;
    _34._c = 0;
    _34._10 = false;
}

Unk_71024505b8::Unk_71024505b8() = default;

bool Unk_71024505b8::m2(const ksys::Message& message) {
    if (message.getType().value != 0x800001e)
        return false;

    auto* payload = static_cast<Unk_710237ecc0_Payload*>(message.getUserData());
    if (!payload)
        return false;

    payload->sub_710070E194(&_38.mLink);
    _30 = true;
    _18 = message.getSource();
    return true;
}

Unk_7102450a08::Unk_7102450a08() = default;

bool Unk_7102450a08::m2(const ksys::Message& message) {
    if (message.getType().value != 0x800001b)
        return false;

    auto* payload = static_cast<Unk_71023b1608_Payload*>(message.getUserData());
    if (!payload)
        return false;

    payload->sub_710070E374(&_38.mLink);
    auto* actor = sead::DynamicCast<ksys::act::Actor>(payload->mLink.getProc(nullptr, nullptr));
    _8.acquire(actor, false);
    _30 = true;
    _18 = message.getSource();
    return true;
}

// NON_MATCHING: the original computes &_38 before taking the lock (see lane2 log, borderline)
bool Unk_71024504c8::m2(const ksys::Message& message) {
    if (message.getType().value != 0x8000010)
        return false;

    auto* payload = static_cast<Unk_71024504c8_Payload*>(message.getUserData());
    if (!payload)
        return false;

    {
        sead::ScopedLock<sead::JobQueueLock> lock(&payload->mLock);
        _38[0] = payload->_0;
        _38[1] = payload->_10;
        _58 = payload->_20;
        _5c = payload->_24;
        _60 = payload->_28;
        _6c = payload->_34;
    }
    auto* actor = sead::DynamicCast<ksys::act::Actor>(payload->_10.getProc(nullptr, nullptr));
    _8.acquire(actor, false);
    _30 = true;
    _18 = message.getSource();
    return true;
}

bool Unk_71024504f8::m2(const ksys::Message& message) {
    if (message.getType().value != 0x80000a4)
        return false;

    auto* payload = static_cast<Unk_7102410070_Payload*>(message.getUserData());
    if (!payload)
        return false;

    auto& link = _38;
    {
        sead::ScopedLock<sead::JobQueueLock> lock(&payload->mLock);
        link = payload->mLink;
        _48.set(payload->_10);
        _54.set(payload->_1c);
    }
    _8 = link;
    _30 = true;
    _18 = message.getSource();
    return true;
}

// NON_MATCHING: the original computes &_38 before taking the lock (see lane2 log, borderline)
bool Unk_7102450528::m2(const ksys::Message& message) {
    if (message.getType().value != 0x8000006)
        return false;

    auto* payload = static_cast<Unk_710235abc8_Payload*>(message.getUserData());
    if (!payload)
        return false;

    {
        sead::ScopedLock<sead::JobQueueLock> lock(&payload->mLock);
        _38._0 = payload->mData._0;
        _38._10 = payload->mData._10;
        _38._24 = payload->mData._24;
        _38._20 = payload->mData._20;
        _38._28 = payload->mData._28;
        _38._34 = payload->mData._34;
    }
    auto* actor =
        sead::DynamicCast<ksys::act::Actor>(payload->mData._10.getProc(nullptr, nullptr));
    _8.acquire(actor, false);
    _30 = true;
    _18 = message.getSource();
    return true;
}

void Unk_7102450528::m3() {
    _38._20 = 0x7fffffff;
    _38._24 = 0;
    _38._28.set(sead::Vector3f::zero);
    _38._10.reset();
    _38._0.reset();
    _38._34 = false;
}

bool Unk_7102450558::m2(const ksys::Message& message) {
    if (message.getType().value != 0x8000007)
        return false;

    auto* payload = static_cast<Unk_710236f520_Payload*>(message.getUserData());
    if (!payload)
        return false;

    payload->x(&_38.mLink);
    _30 = true;
    _18 = message.getSource();
    return true;
}

bool Unk_7102450588::m2(const ksys::Message& message) {
    if (message.getType().value != 0x8000008)
        return false;

    auto* payload = static_cast<Unk_7102372510_Payload*>(message.getUserData());
    if (!payload)
        return false;

    payload->x(&_38);
    _30 = true;
    _18 = message.getSource();
    return true;
}

Unk_71024505e8::~Unk_71024505e8() = default;

bool Unk_71024505e8::m2(const ksys::Message& message) {
    if (message.getType().value != 0x80000b1)
        return false;

    auto* data = static_cast<const u32*>(message.getUserData());
    if (!data)
        return false;

    _34 = *data;
    _30 = true;
    _18 = message.getSource();
    return true;
}

Unk_7102450618::~Unk_7102450618() = default;

bool Unk_7102450618::m2(const ksys::Message& message) {
    if (message.getType().value != 0x8000022)
        return false;

    _30 = true;
    _18 = message.getSource();
    return true;
}

Unk_71024506d8::~Unk_71024506d8() = default;

bool Unk_71024506d8::m2(const ksys::Message& message) {
    if (message.getType().value != 0x800000a)
        return false;

    _30 = true;
    _18 = message.getSource();
    return true;
}

Unk_7102450768::~Unk_7102450768() = default;

bool Unk_7102450768::m2(const ksys::Message& message) {
    if (message.getType().value != 0x8000084)
        return false;

    auto* data = static_cast<const u32*>(message.getUserData());
    if (!data)
        return false;

    _34 = *data;
    _30 = true;
    _18 = message.getSource();
    return true;
}

Unk_7102450798::~Unk_7102450798() = default;

bool Unk_7102450798::m2(const ksys::Message& message) {
    if (message.getType().value != 0x8000004)
        return false;

    _30 = true;
    _18 = message.getSource();
    return true;
}

Unk_7102450b28::~Unk_7102450b28() = default;

bool Unk_7102450b28::m2(const ksys::Message& message) {
    if (message.getType().value != 0x800003f)
        return false;

    _30 = true;
    _18 = message.getSource();
    return true;
}

Unk_7102450b58::~Unk_7102450b58() = default;

bool Unk_7102450b58::m2(const ksys::Message& message) {
    if (message.getType().value != 0x800003c)
        return false;

    auto* data = static_cast<const u64*>(message.getUserData());
    if (!data)
        return false;

    _38 = *data;
    _30 = true;
    _18 = message.getSource();
    return true;
}

bool Unk_7102450888::m2(const ksys::Message& message) {
    if (message.getType().value != 0x80000d3)
        return false;

    auto* payload = static_cast<Unk_7102413398_Payload*>(message.getUserData());
    if (!payload)
        return false;

    {
        sead::ScopedLock<sead::JobQueueLock> lock(&payload->mLock);
        _38._0 = payload->_0;
        _38.mLink = payload->mLink;
    }
    _8 = payload->mLink;
    _30 = true;
    _18 = message.getSource();
    return true;
}

// NON_MATCHING: the original evaluates the destination of BaseProcLink::operator= before the source
// (lane2 log: overloaded operator= evaluation order)
bool Unk_71024508b8::m2(const ksys::Message& message) {
    if (message.getType().value != 0x80000da)
        return false;

    auto* payload = static_cast<Unk_7102409958_Payload*>(message.getUserData());
    if (!payload)
        return false;

    {
        sead::ScopedLock<sead::JobQueueLock> lock(&payload->mLock);
        _38._0 = payload->_0;
        _38._4 = payload->_4;
        _38._8 = payload->_8;
        _38._c = payload->_c;
        _38._14 = payload->_14;
        _38.mLink = payload->mLink;
    }
    _8 = payload->mLink;
    _30 = true;
    _18 = message.getSource();
    return true;
}

bool Unk_71024508e8::m2(const ksys::Message& message) {
    if (message.getType().value != 0x80000db)
        return false;

    auto* payload = static_cast<Unk_71024508e8_Payload*>(message.getUserData());
    if (!payload)
        return false;

    {
        sead::ScopedLock<sead::JobQueueLock> lock(&payload->mLock);
        _38._0 = payload->_0;
        _38.mLink = payload->mLink;
    }
    _8 = payload->mLink;
    _30 = true;
    _18 = message.getSource();
    return true;
}

// NON_MATCHING: the original evaluates the destination of BaseProcLink::operator= before the source
// (lane2 log: overloaded operator= evaluation order)
bool Unk_7102450918::m2(const ksys::Message& message) {
    if (message.getType().value != 0x80000dc)
        return false;

    auto* payload = static_cast<Unk_7102411178_Payload*>(message.getUserData());
    if (!payload)
        return false;

    {
        sead::ScopedLock<sead::JobQueueLock> lock(&payload->mLock);
        _38._0 = payload->_0;
        _38._4 = payload->_4;
        _38.mLink = payload->mLink;
    }
    _8 = payload->mLink;
    _30 = true;
    _18 = message.getSource();
    return true;
}

// NON_MATCHING: the original evaluates the destination of BaseProcLink::operator= before the source
// (lane2 log: overloaded operator= evaluation order)
bool Unk_7102450948::m2(const ksys::Message& message) {
    if (message.getType().value != 0x80000d5)
        return false;

    auto* payload = static_cast<Unk_71023b1860_Payload*>(message.getUserData());
    if (!payload)
        return false;

    {
        sead::ScopedLock<sead::JobQueueLock> lock(&payload->mLock);
        _38._0 = payload->_0;
        _38._18 = payload->_18;
        _38.mLink = payload->mLink;
    }
    _8 = payload->mLink;
    _30 = true;
    _18 = message.getSource();
    return true;
}

Unk_7102450678::~Unk_7102450678() = default;

bool Unk_7102450678::m2(const ksys::Message& message) {
    if (message.getType().value != 0x8000044)
        return false;

    auto* link = static_cast<ksys::act::BaseProcLink*>(message.getUserData());
    if (!link)
        return false;

    auto* actor = sead::DynamicCast<ksys::act::Actor>(link->getProc(nullptr, nullptr));
    _8.acquire(actor, false);
    _30 = true;
    _18 = message.getSource();
    return true;
}

// NON_MATCHING: the original computes &_38 before taking the lock (see lane2 log, borderline)
bool Unk_7102450708::m2(const ksys::Message& message) {
    if (message.getType().value != 0x80000a5)
        return false;

    auto* payload = static_cast<Unk_7102379de0_Payload*>(message.getUserData());
    if (!payload)
        return false;

    {
        sead::ScopedLock<sead::JobQueueLock> lock(&payload->mLock);
        _38.mLink = payload->mLink;
        _38._10 = payload->_10;
    }
    auto* actor = sead::DynamicCast<ksys::act::Actor>(payload->mLink.getProc(nullptr, nullptr));
    _8.acquire(actor, false);
    _30 = true;
    _18 = message.getSource();
    return true;
}

Unk_7102450738::~Unk_7102450738() = default;

bool Unk_7102450738::m2(const ksys::Message& message) {
    if (message.getType().value != 0x8000047)
        return false;

    auto* payload = static_cast<Unk_7102450738_Payload*>(message.getUserData());
    if (!payload)
        return false;

    {
        sead::ScopedLock<sead::JobQueueLock> lock(&payload->mLock);
        _34._0 = payload->_0;
    }
    _30 = true;
    _18 = message.getSource();
    return true;
}

void Unk_7102450738::m3() {
    sead::ScopedLock<sead::JobQueueLock> lock(&_34.mLock);
    _34._0 = 0;
}

// NON_MATCHING: the original computes &_38 before taking the lock and evaluates the destination of
// BaseProcLink::operator= first (see lane2 log, borderline)
bool Unk_71024507f8::m2(const ksys::Message& message) {
    if (message.getType().value != 0x8000017)
        return false;

    auto* payload = static_cast<Unk_71023eaec8_Payload*>(message.getUserData());
    if (!payload)
        return false;

    {
        sead::ScopedLock<sead::JobQueueLock> lock(&payload->mLock);
        _38._0 = payload->_0;
        _38._10 = payload->_10;
        _38._20 = payload->_20;
    }
    auto* actor = sead::DynamicCast<ksys::act::Actor>(payload->_0.getProc(nullptr, nullptr));
    _8.acquire(actor, false);
    _30 = true;
    _18 = message.getSource();
    return true;
}

bool Unk_7102450858::m2(const ksys::Message& message) {
    if (message.getType().value != 0x80000d8)
        return false;

    auto* payload = static_cast<Unk_7102411f48_Payload*>(message.getUserData());
    {
        sead::ScopedLock<sead::JobQueueLock> lock(&payload->mLock);
        _34._0 = payload->_0;
        _34._4 = payload->_4;
    }
    _30 = true;
    _18 = message.getSource();
    return true;
}

// NON_MATCHING: the original evaluates the destination of BaseProcLink::operator= before the source
// (lane2 log: overloaded operator= evaluation order)
bool Unk_7102450978::m2(const ksys::Message& message) {
    if (message.getType().value != 0x80000d4)
        return false;

    auto* payload = static_cast<Unk_7102450978_Payload*>(message.getUserData());
    if (!payload)
        return false;

    {
        sead::ScopedLock<sead::JobQueueLock> lock(&payload->mLock);
        _38._0 = payload->_0;
        _38._8 = payload->_8;
        _38._18 = payload->_18;
        _38._28 = payload->_28;
        _38._2c = payload->_2c;
        _38._30 = payload->_30;
        _38._38 = payload->_38;
    }
    _8 = payload->_8;
    _30 = true;
    _18 = message.getSource();
    return true;
}

// NON_MATCHING: the original copies _0.._8 as one 12-byte block (ldr x + ldr w)
bool Unk_71024509a8::m2(const ksys::Message& message) {
    if (message.getType().value != 0x80000d7)
        return false;

    auto* payload = static_cast<Unk_71023dbd40_Payload*>(message.getUserData());
    {
        sead::ScopedLock<sead::JobQueueLock> lock(&payload->mLock);
        _34._0 = payload->_0;
        _34._4 = payload->_4;
        _34._8 = payload->_8;
        _34._c = payload->_c;
    }
    _30 = true;
    _18 = message.getSource();
    return true;
}

Unk_7102450a38::~Unk_7102450a38() = default;

bool Unk_7102450a38::m2(const ksys::Message& message) {
    if (message.getType().value != 0x800005d)
        return false;

    auto* payload = static_cast<Unk_7102450a38_Payload*>(message.getUserData());
    if (!payload)
        return false;

    {
        sead::ScopedLock<sead::JobQueueLock> lock(&payload->mLock);
        _34._30 = payload->_30;
        _34._0 = payload->_0;
    }
    _30 = true;
    _18 = message.getSource();
    return true;
}

// NON_MATCHING: the original computes &_38 before taking the lock and evaluates the destination of
// BaseProcLink::operator= first (see lane2 log, borderline)
bool Unk_7102450a98::m2(const ksys::Message& message) {
    if (message.getType().value != 0x8000029)
        return false;

    auto* payload = static_cast<Unk_7102450a98_Payload*>(message.getUserData());
    if (!payload)
        return false;

    {
        sead::ScopedLock<sead::JobQueueLock> lock(&payload->mLock);
        _38._0 = payload->_0;
        _38._10 = payload->_10;
    }
    _30 = true;
    _18 = message.getSource();
    return true;
}

bool Unk_7102450b88::m2(const ksys::Message& message) {
    if (message.getType().value != 0x800001f)
        return false;

    auto* payload = static_cast<Unk_7102396ae0_Payload*>(message.getUserData());
    if (!payload)
        return false;

    payload->x(&_38);
    _30 = true;
    _18 = message.getSource();
    return true;
}

// NON_MATCHING: the original computes &_38 before taking the lock (see lane2 log, borderline)
bool Unk_7102450a68::m2(const ksys::Message& message) {
    if (message.getType().value != 0x80000a9)
        return false;

    auto* payload = static_cast<Unk_7102450a68_Payload*>(message.getUserData());
    if (!payload)
        return false;

    {
        sead::ScopedLock<sead::JobQueueLock> lock(&payload->mLock);
        _38._0 = payload->_0;
        _38._10 = payload->_10;
    }
    auto* actor = sead::DynamicCast<ksys::act::Actor>(payload->_0.getProc(nullptr, nullptr));
    _8.acquire(actor, false);
    _30 = true;
    _18 = message.getSource();
    return true;
}

// NON_MATCHING: the original computes &_38 before taking the lock and evaluates the destination of
// BaseProcLink::operator= first (see lane2 log, borderline)
bool Unk_7102450be8::m2(const ksys::Message& message) {
    if (message.getType().value != 0x8000037)
        return false;

    auto* payload = static_cast<Unk_7102450be8_Payload*>(message.getUserData());
    if (!payload)
        return false;

    {
        sead::ScopedLock<sead::JobQueueLock> lock(&payload->mLock);
        _38._0 = payload->_0;
        _38._10 = payload->_10;
        _38._20 = payload->_20;
        _38._44 = payload->_44;
        _38._48 = payload->_48;
        _38._2c = payload->_2c;
        _38._38 = payload->_38;
        _38._4c = payload->_4c;
    }
    auto* actor = sead::DynamicCast<ksys::act::Actor>(payload->_0.getProc(nullptr, nullptr));
    _8.acquire(actor, false);
    _30 = true;
    _18 = message.getSource();
    return true;
}

bool Unk_7102450ac8::m2(const ksys::Message& message) {
    if (message.getType().value != 0x8000040)
        return false;

    auto* payload = static_cast<Unk_710235aba0_Payload*>(message.getUserData());
    if (!payload)
        return false;

    payload->x(&_38);
    _30 = true;
    _18 = message.getSource();
    return true;
}

bool Unk_71024509d8::m2(const ksys::Message& message) {
    if (message.getType().value != 0x80000de)
        return false;

    static_cast<Unk_71024509d8_Payload*>(message.getUserData())->sub_710070E270(&_34);
    _30 = true;
    _18 = message.getSource();
    return true;
}

// ---- Listeners embedded in AI classes (functions in their owners' TUs in the original) ----

bool Unk_71023e7c38::m2(const ksys::Message& message) {
    if (message.getType().value != 0x800009c)
        return false;

    auto* payload = static_cast<Unk_71023e7c38_Payload*>(message.getUserData());
    if (!payload)
        return false;

    payload->x(&_38);
    _30 = true;
    _18 = message.getSource();
    return true;
}

bool Unk_71023e7c68::m2(const ksys::Message& message) {
    if (message.getType().value != 0x800009d)
        return false;

    auto* payload = static_cast<Unk_71023e7c68_Payload*>(message.getUserData());
    if (!payload)
        return false;

    payload->x(&_38);
    _30 = true;
    _18 = message.getSource();
    return true;
}

bool Unk_71023e7c98::m2(const ksys::Message& message) {
    if (message.getType().value != 0x800009e)
        return false;

    auto* payload = static_cast<Unk_7102379988_Payload*>(message.getUserData());
    if (!payload)
        return false;

    payload->x(&_38);
    _30 = true;
    _18 = message.getSource();
    return true;
}

bool Unk_71023e7cc8::m2(const ksys::Message& message) {
    if (message.getType().value != 0x80000a1)
        return false;

    auto* payload = static_cast<Unk_71023e78b0_Payload*>(message.getUserData());
    if (!payload)
        return false;

    payload->x(&_38);
    _30 = true;
    _18 = message.getSource();
    return true;
}

bool Unk_71023e7cf8::m2(const ksys::Message& message) {
    if (message.getType().value != 0x80000a2)
        return false;

    auto* payload = static_cast<Unk_71023e7cf8_Payload*>(message.getUserData());
    if (!payload)
        return false;

    payload->x(&_38);
    _30 = true;
    _18 = message.getSource();
    return true;
}

bool Unk_71023e8ff8::m2(const ksys::Message& message) {
    if (message.getType().value != 0x80000b3)
        return false;

    auto* payload = static_cast<Unk_71023e8ff8_Payload*>(message.getUserData());
    if (!payload)
        return false;

    payload->x(&_38);
    _30 = true;
    _18 = message.getSource();
    return true;
}

bool Unk_71023e9028::m2(const ksys::Message& message) {
    if (message.getType().value != 0x80000bf)
        return false;

    auto* payload = static_cast<Unk_71023e9028_Payload*>(message.getUserData());
    if (!payload)
        return false;

    payload->x(&_38);
    _30 = true;
    _18 = message.getSource();
    return true;
}

Unk_71023e7d28::~Unk_71023e7d28() = default;

bool Unk_71023e7d28::m2(const ksys::Message& message) {
    if (message.getType().value != 0x80000c0)
        return false;

    auto* payload = static_cast<Unk_71023e7d28_Payload*>(message.getUserData());
    if (!payload)
        return false;

    {
        sead::ScopedLock<sead::JobQueueLock> lock(&payload->mLock);
        _34._0 = payload->_0;
        _34._4 = payload->_4;
        _34._8 = payload->_8;
    }
    _30 = true;
    _18 = message.getSource();
    return true;
}

bool Unk_7102358dc0::m2(const ksys::Message& message) {
    if (message.getType().value != 0x800006e)
        return false;

    auto* payload = static_cast<Unk_7102358dc0_Payload*>(message.getUserData());
    if (!payload)
        return false;

    payload->x(&_38);
    _30 = true;
    _18 = message.getSource();
    return true;
}

bool Unk_710235cec8::m2(const ksys::Message& message) {
    if (message.getType().value != 0x8000041)
        return false;

    auto* payload = static_cast<Unk_71023e7bc0_Payload*>(message.getUserData());
    if (!payload)
        return false;

    payload->x(&_38);
    _30 = true;
    _18 = message.getSource();
    return true;
}

bool Unk_71023799b0::m2(const ksys::Message& message) {
    if (message.getType().value != 0x80000a3)
        return false;

    auto* payload = static_cast<Unk_71023799b0_Payload*>(message.getUserData());
    if (!payload)
        return false;

    payload->x(&_38);
    _30 = true;
    _18 = message.getSource();
    return true;
}

bool Unk_7102379b00::m2(const ksys::Message& message) {
    if (message.getType().value != 0x800009f)
        return false;

    auto* payload = static_cast<Unk_7102379b00_Payload*>(message.getUserData());
    if (!payload)
        return false;

    payload->x(&_38);
    _30 = true;
    _18 = message.getSource();
    return true;
}

bool Unk_7102379b30::m2(const ksys::Message& message) {
    if (message.getType().value != 0x80000a0)
        return false;

    auto* payload = static_cast<Unk_7102379b30_Payload*>(message.getUserData());
    if (!payload)
        return false;

    payload->x(&_38);
    _30 = true;
    _18 = message.getSource();
    return true;
}

bool Unk_71023d4c08::m2(const ksys::Message& message) {
    if (message.getType().value != 0x80000ab)
        return false;

    auto* payload = static_cast<Unk_71023d4bb0_Payload*>(message.getUserData());
    if (!payload)
        return false;

    payload->x(&_38);
    _30 = true;
    _18 = message.getSource();
    return true;
}

bool Unk_7102404060::m2(const ksys::Message& message) {
    if (message.getType().value != 0x8000018)
        return false;

    auto* payload = static_cast<Unk_7102404060_Payload*>(message.getUserData());
    if (!payload)
        return false;

    payload->x(&_38);
    _30 = true;
    _18 = message.getSource();
    return true;
}

bool Unk_710240dd68::m2(const ksys::Message& message) {
    if (message.getType().value != 0x8000042)
        return false;

    auto* payload = static_cast<Unk_710240dd68_Payload*>(message.getUserData());
    if (!payload)
        return false;

    payload->x(&_38);
    _30 = true;
    _18 = message.getSource();
    return true;
}

bool Unk_7102424730::m2(const ksys::Message& message) {
    if (message.getType().value != 0x80000b8)
        return false;

    auto* payload = static_cast<Unk_71023c5480_Payload*>(message.getUserData());
    if (!payload)
        return false;

    payload->x(&_38);
    _30 = true;
    _18 = message.getSource();
    return true;
}

bool Unk_710244e760::m2(const ksys::Message& message) {
    if (message.getType().value != 0x80000cc)
        return false;

    auto* payload = static_cast<Unk_710244e760_Payload*>(message.getUserData());
    if (!payload)
        return false;

    payload->x(&_38);
    _30 = true;
    _18 = message.getSource();
    return true;
}

Unk_71024056a8::~Unk_71024056a8() = default;

bool Unk_71024056a8::m2(const ksys::Message& message) {
    if (message.getType().value != 0x80000ac)
        return false;

    auto* payload = static_cast<Unk_71024056a8_Payload*>(message.getUserData());
    if (!payload)
        return false;

    {
        sead::ScopedLock<sead::JobQueueLock> lock(&payload->mLock);
        _34._0 = payload->_0;
    }
    _30 = true;
    _18 = message.getSource();
    return true;
}

Unk_710244e7f0::~Unk_710244e7f0() = default;

bool Unk_710244e7f0::m2(const ksys::Message& message) {
    if (message.getType().value != 0x80000cf)
        return false;

    auto* payload = static_cast<Unk_710244e7f0_Payload*>(message.getUserData());
    if (!payload)
        return false;

    {
        sead::ScopedLock<sead::JobQueueLock> lock(&payload->mLock);
        _34._0 = payload->_0;
    }
    _30 = true;
    _18 = message.getSource();
    return true;
}

bool Unk_71023da100::m2(const ksys::Message& message) {
    if (message.getType().value != 0x5800000)
        return false;

    auto* payload = static_cast<Unk_71024512c0_Payload*>(message.getUserData());
    if (!payload)
        return false;

    payload->x(&_38);
    _30 = true;
    _18 = message.getSource();
    return true;
}

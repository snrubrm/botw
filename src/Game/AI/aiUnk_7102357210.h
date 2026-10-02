#pragma once

#include <basis/seadTypes.h>
#include <math/seadVector.h>
#include "Game/AI/aiUnkMessagePayloads.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "KingSystem/Utils/Thread/MessageTransceiverId.h"

namespace ksys::act {
class Actor;
}

// Unnamed message listener classes embedded in many AI classes. Placeholder names are the vtable
// addresses (Unk_<vtable>); slot functions are named by slot index (mN) and unnamed non-virtual
// functions by address (sub_<addr>).

// vtable 0x7102357210 (abstract)
class Unk_7102357210 {
public:
    Unk_7102357210() = default;
    virtual ~Unk_7102357210() = default;
    virtual bool m2(const ksys::Message& message) = 0;
    virtual void m3() {}

    // Inline only (no out-of-line copy in the executable); placeholder name.
    void x() {
        _30 = false;
        _8.reset();
        m3();
    }

    ksys::act::BaseProcLink _8;
    ksys::MesTransceiverId _18;
    bool _30 = false;
};

// vtable 0x7102450648
class Unk_7102450648 : public Unk_7102357210 {
public:
    explicit Unk_7102450648(u32 type) {
        _34 = type;
        _38 = false;
    }
    bool m2(const ksys::Message& message) override;
    void m3() override { _38 = false; }

    bool sub_710070A674(const ksys::Message& message);
    void sub_710070AE18(ksys::act::Actor* actor);

    u32 _34;
    bool _38;
};

// vtable 0x7102450828
class Unk_7102450828 : public Unk_7102450648 {
public:
    explicit Unk_7102450828(u32 type) : Unk_7102450648(type) {}
    bool m2(const ksys::Message& message) override;
};

// vtable 0x71023fa018 (GyroActivateTerminal)
class Unk_71023fa018 : public Unk_7102450648 {
public:
    explicit Unk_71023fa018(u32 type) : Unk_7102450648(type) {}
};

// vtable 0x71023e0020 (CommonPickedItem)
class Unk_71023e0020 : public Unk_7102450648 {
public:
    explicit Unk_71023e0020(u32 type) : Unk_7102450648(type) {}
    void m3() override {
        _38 = false;
        _39 = false;
        _3a = false;
    }

    bool _39 = false;
    bool _3a = false;
};

// vtable 0x71023f5f90 (GoronHeroDescendentRoot, MessageReceiveCheck)
class Unk_71023f5f90 : public Unk_7102357210 {
public:
    bool m2(const ksys::Message& message) override {
        if (message.getType().value != 0x8000045)
            return false;
        _30 = true;
        _18 = message.getSource();
        return true;
    }
    void m3() override {}
};

// vtable 0x71023fbec8 (HorseRideChaseBattleMoveBase; m2 handles message type 0x3800021)
class Unk_71023fbec8 : public Unk_7102357210 {
public:
    bool m2(const ksys::Message& message) override {
        if (message.getType().value != 0x3800021)
            return false;
        _30 = true;
        _18 = message.getSource();
        return true;
    }
    void m3() override {}
};

// vtable 0x71023f9b08 (GuardianRoot; m2 always returns false)
class Unk_71023f9b08 : public Unk_7102357210 {
public:
    bool m2(const ksys::Message& message) override { return false; }
};

// vtable 0x71023fbad8 (HorseRideChargeAttack; m2 handles message type 0x3800022)
class Unk_71023fbad8 : public Unk_7102357210 {
public:
    bool m2(const ksys::Message& message) override {
        if (message.getType().value != 0x3800022)
            return false;
        _30 = true;
        _18 = message.getSource();
        return true;
    }
    void m3() override {}
};

// vtable 0x71023fc720 (HorseRideMoveTo; m2 handles message type 0x3800023)
class Unk_71023fc720 : public Unk_7102357210 {
public:
    bool m2(const ksys::Message& message) override {
        if (message.getType().value != 0x3800023)
            return false;
        _30 = true;
        _18 = message.getSource();
        return true;
    }
    void m3() override {}
};

// vtable 0x71023fc750 (HorseRideMoveTo; m2 handles message type 0x3800024)
class Unk_71023fc750 : public Unk_7102357210 {
public:
    bool m2(const ksys::Message& message) override {
        if (message.getType().value != 0x3800024)
            return false;
        _30 = true;
        _18 = message.getSource();
        return true;
    }
    void m3() override {}
};

// vtable 0x71023fc5a0 (HorseRideTurn; m2 handles message type 0x3800025)
class Unk_71023fc5a0 : public Unk_7102357210 {
public:
    bool m2(const ksys::Message& message) override {
        if (message.getType().value != 0x3800025)
            return false;
        _30 = true;
        _18 = message.getSource();
        return true;
    }
    void m3() override {}
};

// vtable 0x71023fc5d0 (HorseRideTurn; m2 handles message type 0x3800026)
class Unk_71023fc5d0 : public Unk_7102357210 {
public:
    bool m2(const ksys::Message& message) override {
        if (message.getType().value != 0x3800026)
            return false;
        _30 = true;
        _18 = message.getSource();
        return true;
    }
    void m3() override {}
};

// vtable 0x7102450af8 (ReflectableThrown)
class Unk_7102450af8 : public Unk_7102357210 {
public:
    bool m2(const ksys::Message& message) override;
    void m3() override {}
};

// vtable 0x710241d7c8 (SeqNextMessage; m2 is defined in aiSeqNextMessage.cpp)
class Unk_710241d7c8 : public Unk_7102357210 {
public:
    bool m2(const ksys::Message& message) override;
    void m3() override {}
};

// vtable 0x71024507c8 (EnemyRoot, PreyRoot, SimpleLiftable, StalEnemyRoot, CarryBox, RemoteBomb, ...)
class Unk_71024507c8 : public Unk_7102450648 {
public:
    explicit Unk_71024507c8(u32 type) : Unk_7102450648(type) {}
    bool m2(const ksys::Message& message) override;

    bool sub_71007094F4(ksys::act::Actor* actor);
    void sub_710070B5A0(ksys::act::Actor* actor);
};

// vtable 0x71023da100 (SimpleLiftable family; functions in the BarrelBomb/SimpleLiftable TU)
class Unk_71023da100 : public Unk_7102357210 {
public:
    bool m2(const ksys::Message& message) override;
    void m3() override {}

    Unk_71024512c0_Payload _38;
};

// vtable 0x7102450528 (m2 handles message type 0x8000006 (payload Unk_710235abc8_Payload); embedded
// in uking::act::Enemy at 0xcf0)
class Unk_7102450528 : public Unk_7102357210 {
public:
    bool m2(const ksys::Message& message) override;
    void m3() override;

    Unk_710235abc8_Payload::Data _38;
};

// vtable 0x7102450bb8 (WolfLinkNormalRoot; m2 handles message type 0x80000a8 with a u32 payload)
class Unk_7102450bb8 : public Unk_7102357210 {
public:
    Unk_7102450bb8() { _34 = 0; }
    bool m2(const ksys::Message& message) override;

    u32 _34;
};

// ---- Listeners copying JobQueueLock-guarded payloads (see aiUnkMessagePayloads.h); functions in
// aiUnk_7102357210.cpp ----

// vtable 0x7102450498 (message 0x8000021)
class Unk_7102450498 : public Unk_7102357210 {
public:
    ~Unk_7102450498() override;
    bool m2(const ksys::Message& message) override;
    void m3() override;

    Unk_71023f83e8_Payload _34;
};

// vtable 0x71024505b8 (message 0x800001e)
class Unk_71024505b8 : public Unk_7102357210 {
public:
    Unk_71024505b8();
    bool m2(const ksys::Message& message) override;

    Unk_710237ecc0_Payload _38;
};

// vtable 0x7102450a08 (LumberjackTree; message 0x800001b)
class Unk_7102450a08 : public Unk_7102357210 {
public:
    Unk_7102450a08();
    bool m2(const ksys::Message& message) override;

    Unk_71023b1608_Payload _38;
};

// vtable 0x71024504c8 (message 0x8000010)
class Unk_71024504c8 : public Unk_7102357210 {
public:
    bool m2(const ksys::Message& message) override;
    void m3() override {}

    Unk_71024504c8_Payload _38;
};

// vtable 0x71024504f8 (message 0x80000a4)
class Unk_71024504f8 : public Unk_7102357210 {
public:
    bool m2(const ksys::Message& message) override;
    void m3() override {}

    ksys::act::BaseProcLink _38;
    sead::Vector3f _48;
    sead::Vector3f _54;
};

// vtable 0x7102450558 (message 0x8000007)
class Unk_7102450558 : public Unk_7102357210 {
public:
    bool m2(const ksys::Message& message) override;
    void m3() override {}

    Unk_710236f520_Payload _38;
};

// vtable 0x7102450588 (message 0x8000008)
class Unk_7102450588 : public Unk_7102357210 {
public:
    bool m2(const ksys::Message& message) override;
    void m3() override {}

    Unk_7102372510_Payload _38;
};

// vtable 0x71024505e8 (message 0x80000b1)
class Unk_71024505e8 : public Unk_7102357210 {
public:
    ~Unk_71024505e8() override;
    bool m2(const ksys::Message& message) override;
    void m3() override {}

    u32 _34;
};

// vtable 0x7102450618 (message 0x8000022)
class Unk_7102450618 : public Unk_7102357210 {
public:
    ~Unk_7102450618() override;
    bool m2(const ksys::Message& message) override;
    void m3() override {}
};

// vtable 0x71024506d8 (message 0x800000a)
class Unk_71024506d8 : public Unk_7102357210 {
public:
    ~Unk_71024506d8() override;
    bool m2(const ksys::Message& message) override;
    void m3() override {}
};

// vtable 0x7102450768 (message 0x8000084)
class Unk_7102450768 : public Unk_7102357210 {
public:
    ~Unk_7102450768() override;
    bool m2(const ksys::Message& message) override;
    void m3() override {}

    u32 _34;
};

// vtable 0x7102450798 (message 0x8000004)
class Unk_7102450798 : public Unk_7102357210 {
public:
    ~Unk_7102450798() override;
    bool m2(const ksys::Message& message) override;
    void m3() override {}
};

// vtable 0x7102450b28 (message 0x800003f)
class Unk_7102450b28 : public Unk_7102357210 {
public:
    ~Unk_7102450b28() override;
    bool m2(const ksys::Message& message) override;
    void m3() override {}
};

// vtable 0x7102450b58 (message 0x800003c)
class Unk_7102450b58 : public Unk_7102357210 {
public:
    ~Unk_7102450b58() override;
    bool m2(const ksys::Message& message) override;
    void m3() override {}

    u64 _38;
};

// vtable 0x7102450888 (message 0x80000d3)
class Unk_7102450888 : public Unk_7102357210 {
public:
    bool m2(const ksys::Message& message) override;

    Unk_7102413398_Payload _38;
};

// vtable 0x71024508b8 (message 0x80000da)
class Unk_71024508b8 : public Unk_7102357210 {
public:
    bool m2(const ksys::Message& message) override;

    Unk_7102409958_Payload _38;
};

// vtable 0x71024508e8 (message 0x80000db)
class Unk_71024508e8 : public Unk_7102357210 {
public:
    bool m2(const ksys::Message& message) override;

    Unk_71024508e8_Payload _38;
};

// vtable 0x7102450918 (message 0x80000dc)
class Unk_7102450918 : public Unk_7102357210 {
public:
    bool m2(const ksys::Message& message) override;

    Unk_7102411178_Payload _38;
};

// vtable 0x7102450948 (message 0x80000d5)
class Unk_7102450948 : public Unk_7102357210 {
public:
    bool m2(const ksys::Message& message) override;

    Unk_71023b1860_Payload _38;
};

// vtable 0x7102450678 (message 0x8000044; the user data is a BaseProcLink)
class Unk_7102450678 : public Unk_7102357210 {
public:
    ~Unk_7102450678() override;
    bool m2(const ksys::Message& message) override;
    void m3() override {}
};

// vtable 0x7102450708 (message 0x80000a5)
class Unk_7102450708 : public Unk_7102357210 {
public:
    bool m2(const ksys::Message& message) override;
    void m3() override {}

    Unk_7102379de0_Payload _38;
};

// vtable 0x7102450738 (message 0x8000047)
class Unk_7102450738 : public Unk_7102357210 {
public:
    ~Unk_7102450738() override;
    bool m2(const ksys::Message& message) override;
    void m3() override;

    Unk_7102450738_Payload _34;
};

// vtable 0x71024507f8 (message 0x8000017)
class Unk_71024507f8 : public Unk_7102357210 {
public:
    bool m2(const ksys::Message& message) override;
    void m3() override {}

    Unk_71023eaec8_Payload _38;
};

// vtable 0x7102450858 (message 0x80000d8)
class Unk_7102450858 : public Unk_7102357210 {
public:
    bool m2(const ksys::Message& message) override;

    Unk_7102411f48_Payload _34;
};

// vtable 0x7102450978 (message 0x80000d4)
class Unk_7102450978 : public Unk_7102357210 {
public:
    bool m2(const ksys::Message& message) override;

    Unk_7102450978_Payload _38;
};

// vtable 0x71024509a8 (message 0x80000d7)
class Unk_71024509a8 : public Unk_7102357210 {
public:
    bool m2(const ksys::Message& message) override;

    Unk_71023dbd40_Payload _34;
};

// vtable 0x7102450a38 (message 0x800005d)
class Unk_7102450a38 : public Unk_7102357210 {
public:
    ~Unk_7102450a38() override;
    bool m2(const ksys::Message& message) override;
    void m3() override {}

    Unk_7102450a38_Payload _34;
};

// vtable 0x7102450a98 (message 0x8000029)
class Unk_7102450a98 : public Unk_7102357210 {
public:
    bool m2(const ksys::Message& message) override;
    void m3() override {}

    Unk_7102450a98_Payload _38;
};

// vtable 0x7102450b88 (message 0x800001f)
class Unk_7102450b88 : public Unk_7102357210 {
public:
    bool m2(const ksys::Message& message) override;
    void m3() override {}

    Unk_7102396ae0_Payload _38;
};

// vtable 0x7102450a68 (message 0x80000a9)
class Unk_7102450a68 : public Unk_7102357210 {
public:
    bool m2(const ksys::Message& message) override;
    void m3() override {}

    Unk_7102450a68_Payload _38;
};

// vtable 0x7102450be8 (message 0x8000037)
class Unk_7102450be8 : public Unk_7102357210 {
public:
    bool m2(const ksys::Message& message) override;
    void m3() override {}

    Unk_7102450be8_Payload _38;
};

// vtable 0x7102450ac8 (message 0x8000040)
class Unk_7102450ac8 : public Unk_7102357210 {
public:
    bool m2(const ksys::Message& message) override;
    void m3() override {}

    Unk_710235aba0_Payload _38;
};

// vtable 0x71024509d8 (message 0x80000de)
class Unk_71024509d8 : public Unk_7102357210 {
public:
    bool m2(const ksys::Message& message) override;

    Unk_7102413c08_Payload _34;
};

// ---- Listeners embedded in AI classes (functions in their owners' TUs in the original) ----

// vtable 0x71023e7c38 (message 0x800009c)
class Unk_71023e7c38 : public Unk_7102357210 {
public:
    bool m2(const ksys::Message& message) override;
    void m3() override {}

    Unk_71023e7c38_Payload _38;
};

// vtable 0x71023e7c68 (message 0x800009d)
class Unk_71023e7c68 : public Unk_7102357210 {
public:
    bool m2(const ksys::Message& message) override;
    void m3() override {}

    Unk_71023e7c68_Payload _38;
};

// vtable 0x71023e7c98 (message 0x800009e)
class Unk_71023e7c98 : public Unk_7102357210 {
public:
    bool m2(const ksys::Message& message) override;
    void m3() override {}

    Unk_7102379988_Payload _38;
};

// vtable 0x71023e7cc8 (message 0x80000a1)
class Unk_71023e7cc8 : public Unk_7102357210 {
public:
    bool m2(const ksys::Message& message) override;
    void m3() override {}

    Unk_71023e78b0_Payload _38;
};

// vtable 0x71023e7cf8 (message 0x80000a2)
class Unk_71023e7cf8 : public Unk_7102357210 {
public:
    bool m2(const ksys::Message& message) override;
    void m3() override {}

    Unk_71023e7cf8_Payload _38;
};

// vtable 0x71023e8ff8 (message 0x80000b3)
class Unk_71023e8ff8 : public Unk_7102357210 {
public:
    bool m2(const ksys::Message& message) override;
    void m3() override {}

    Unk_71023e8ff8_Payload _38;
};

// vtable 0x71023e9028 (message 0x80000bf)
class Unk_71023e9028 : public Unk_7102357210 {
public:
    bool m2(const ksys::Message& message) override;
    void m3() override {}

    Unk_71023e9028_Payload _38;
};

// vtable 0x71023e7d28 (message 0x80000c0)
class Unk_71023e7d28 : public Unk_7102357210 {
public:
    ~Unk_71023e7d28() override;
    bool m2(const ksys::Message& message) override;
    void m3() override {}

    Unk_71023e7d28_Payload _34;
};

// vtable 0x7102358dc0 (message 0x800006e)
class Unk_7102358dc0 : public Unk_7102357210 {
public:
    bool m2(const ksys::Message& message) override;
    void m3() override {}

    Unk_7102358dc0_Payload _38;
};

// vtable 0x710235cec8 (message 0x8000041)
class Unk_710235cec8 : public Unk_7102357210 {
public:
    bool m2(const ksys::Message& message) override;
    void m3() override {}

    Unk_71023e7bc0_Payload _38;
};

// vtable 0x71023799b0 (message 0x80000a3)
class Unk_71023799b0 : public Unk_7102357210 {
public:
    bool m2(const ksys::Message& message) override;
    void m3() override {}

    Unk_71023799b0_Payload _38;
};

// vtable 0x7102379b00 (message 0x800009f)
class Unk_7102379b00 : public Unk_7102357210 {
public:
    bool m2(const ksys::Message& message) override;
    void m3() override {}

    Unk_7102379b00_Payload _38;
};

// vtable 0x7102379b30 (message 0x80000a0)
class Unk_7102379b30 : public Unk_7102357210 {
public:
    bool m2(const ksys::Message& message) override;
    void m3() override {}

    Unk_7102379b30_Payload _38;
};

// vtable 0x71023d4c08 (message 0x80000ab)
class Unk_71023d4c08 : public Unk_7102357210 {
public:
    bool m2(const ksys::Message& message) override;
    void m3() override {}

    Unk_71023d4bb0_Payload _38;
};

// vtable 0x7102404060 (message 0x8000018)
class Unk_7102404060 : public Unk_7102357210 {
public:
    bool m2(const ksys::Message& message) override;
    void m3() override {}

    Unk_7102404060_Payload _38;
};

// vtable 0x710240dd68 (message 0x8000042)
class Unk_710240dd68 : public Unk_7102357210 {
public:
    bool m2(const ksys::Message& message) override;
    void m3() override {}

    Unk_710240dd68_Payload _38;
};

// vtable 0x7102424730 (message 0x80000b8)
class Unk_7102424730 : public Unk_7102357210 {
public:
    bool m2(const ksys::Message& message) override;
    void m3() override {}

    Unk_71023c5480_Payload _38;
};

// vtable 0x710244e760 (message 0x80000cc)
class Unk_710244e760 : public Unk_7102357210 {
public:
    bool m2(const ksys::Message& message) override;
    void m3() override {}

    Unk_710244e760_Payload _38;
};

// vtable 0x71024056a8 (message 0x80000ac)
class Unk_71024056a8 : public Unk_7102357210 {
public:
    ~Unk_71024056a8() override;
    bool m2(const ksys::Message& message) override;
    void m3() override {}

    Unk_71024056a8_Payload _34;
};

// vtable 0x710244e7f0 (message 0x80000cf)
class Unk_710244e7f0 : public Unk_7102357210 {
public:
    ~Unk_710244e7f0() override;
    bool m2(const ksys::Message& message) override;
    void m3() override {}

    Unk_710244e7f0_Payload _34;
};

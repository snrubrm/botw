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
};

// vtable 0x71023da100 (SimpleLiftable family; functions in the BarrelBomb/SimpleLiftable TU)
class Unk_71023da100 : public Unk_7102357210 {
public:
    bool m2(const ksys::Message& message) override;
    void m3() override {}

    ksys::act::BaseProcLink _38;
};

// vtable 0x7102450528 (m2 handles message type 0x8000006 (payload Unk_710235abc8_Payload); embedded
// in uking::act::Enemy at 0xcf0)
class Unk_7102450528 : public Unk_7102357210 {
public:
    ~Unk_7102450528() override;
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
    ~Unk_71024505b8() override;
    bool m2(const ksys::Message& message) override;

    Unk_710237ecc0_Payload _38;
};

// vtable 0x7102450a08 (LumberjackTree; message 0x800001b)
class Unk_7102450a08 : public Unk_7102357210 {
public:
    Unk_7102450a08();
    ~Unk_7102450a08() override;
    bool m2(const ksys::Message& message) override;

    Unk_71023b1608_Payload _38;
};

// vtable 0x71024504c8 (message 0x8000010)
class Unk_71024504c8 : public Unk_7102357210 {
public:
    ~Unk_71024504c8() override;
    bool m2(const ksys::Message& message) override;
    void m3() override {}

    ksys::act::BaseProcLink _38[2];
    u32 _58;
    u32 _5c;
    sead::Vector3f _60;
    u32 _6c;
};

// vtable 0x71024504f8 (message 0x80000a4)
class Unk_71024504f8 : public Unk_7102357210 {
public:
    ~Unk_71024504f8() override;
    bool m2(const ksys::Message& message) override;
    void m3() override {}

    ksys::act::BaseProcLink _38;
    sead::Vector3f _48;
    sead::Vector3f _54;
};

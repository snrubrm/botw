#pragma once

#include <basis/seadTypes.h>
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "KingSystem/Utils/Thread/MessageTransceiverId.h"

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
    u32 _34;
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

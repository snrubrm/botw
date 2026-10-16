#pragma once

#include <basis/seadTypes.h>
#include "KingSystem/Utils/Thread/MessageBroker.h"
#include "KingSystem/Utils/Thread/MessageTransceiverId.h"
#include "KingSystem/Utils/Types.h"

namespace ksys {
class MessageTransceiverBase;
}

// Placeholders for the debug board (CSV DebugBoardMgr; instance pointer 0x71025d04f0, GOT 0x2590e98): the manager owns
// three message brokers and the board components (ScreenEx +0x300 / +0x310 / +0x320, Player, EventSystem + 0x58, the
// OpenWorldStage family, ...) register a transceiver with one of them. Names are placeholders; the namespace is a
// guess.

// The broker's register at +8 has 200 IDs: manager construction at 899FE0 initializes
// every ID, and the complete register methods at 89C060..89C254 use this same array.
class Unk_DebugBoardRegister final : public ksys::IMessageBrokerRegister {
public:
    ~Unk_DebugBoardRegister() override;
    bool registerTransceiver(const ksys::MesTransceiverId& id) override;
    void deregisterTransceiver(const ksys::MesTransceiverId& id) override;
    void forEachRegistered(IForEachContext& context) override;
    void setId(const u32& id) override;
    const u32& getId() const override;
    int countTransceivers() const override;

    u32 mId = 0xffffffff;
    ksys::MesTransceiverId mIds[200];
};
static_assert(sizeof(Unk_DebugBoardRegister) == 0x12d0);

// A debug message broker embedded in the manager (placeholder: only what the vtable needs; 0x12d8 bytes each).
class Unk_DebugBoardBroker final : public ksys::IMessageBroker {
public:
    ~Unk_DebugBoardBroker() override;
    bool setId(const SetIdArg* arg) override;
    ksys::IMessageBrokerRegister* getRegister() override;

    Unk_DebugBoardRegister mRegister;
};
static_assert(sizeof(Unk_DebugBoardBroker) == 0x12d8);

class DebugBoardMgr {
public:
    static DebugBoardMgr* instance() { return sInstance; }
    static DebugBoardMgr* sInstance;

    // 0x710089baf4 (CSV x_0) / 0x710089bafc (CSV __auto0) / 0x710089bb08 (CSV __auto1): out of line.
    ksys::IMessageBroker* getBroker0();
    ksys::IMessageBroker* getBroker1();
    ksys::IMessageBroker* getBroker2();

    u8 _0[0x60];
    /* 0x60 */ Unk_DebugBoardBroker mBroker0;
    /* 0x1338 */ Unk_DebugBoardBroker mBroker1;
    /* 0x2610 */ Unk_DebugBoardBroker mBroker2;
    u8 _38e8[0x39bc - 0x38e8];
    /* 0x39bc */ s32 _39bc;  // 1 / 0: ScreenGamePadBG::m83 stops its animator at max / min
};

// The three board components (no RTTI; vtables 0x710246c458 / 0x710246c498 / 0x710246c4d8 with the destructor pair
// only). Each holds the transceiver it registered (+8) and deregisters it from its broker in the destructor. The base
// classes (vtables 0x710246c478 / c4b8 / c4f8) only have an empty virtual destructor.
// Placeholder (name unknown): the argument ScreenEx::m113 passes to the board components' register functions, a
// polymorphic temporary holding the transceiver (three derived types with empty destructors, vtables 0x710245b458 /
// 0x710246bdc8 / 0x710246bde8).
class DebugBoardTransceiverArgMaybe {
public:
    virtual ~DebugBoardTransceiverArgMaybe() = default;
    ksys::MessageTransceiverBase* mTransceiver;
};

class Unk_710246c478 {
public:
    virtual ~Unk_710246c478() = default;
};

class Unk_710246c458 : public Unk_710246c478 {
public:
    Unk_710246c458();
    ~Unk_710246c458() override;
    // 0x710089c664: keeps the transceiver and registers it with the board's broker (false without one).
    bool sub_710089C664(const DebugBoardTransceiverArgMaybe& arg);
    ksys::MessageTransceiverBase* mTransceiver;
};

class Unk_710246c4b8 {
public:
    virtual ~Unk_710246c4b8() = default;
};

class Unk_710246c498 : public Unk_710246c4b8 {
public:
    Unk_710246c498();
    ~Unk_710246c498() override;
    // 0x710089c88c: keeps the transceiver and registers it with the board's broker (false without one).
    bool sub_710089C88C(const DebugBoardTransceiverArgMaybe& arg);
    ksys::MessageTransceiverBase* mTransceiver;
};

class Unk_710246c4f8 {
public:
    virtual ~Unk_710246c4f8() = default;
};

class Unk_710246c4d8 : public Unk_710246c4f8 {
public:
    Unk_710246c4d8();
    ~Unk_710246c4d8() override;
    // 0x710089ca04: keeps the transceiver and registers it with the board's broker (false without one).
    bool sub_710089CA04(const DebugBoardTransceiverArgMaybe& arg);
    ksys::MessageTransceiverBase* mTransceiver;
};

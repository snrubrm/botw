#pragma once

#include <basis/seadTypes.h>
#include "KingSystem/Utils/Thread/MessageBroker.h"
#include "KingSystem/Utils/Types.h"

namespace ksys {
class MessageTransceiverBase;
}

// Placeholders for the debug board (CSV DebugBoardMgr; instance pointer 0x71025d04f0, GOT 0x2590e98): the manager owns
// three message brokers and the board components (ScreenEx +0x300 / +0x310 / +0x320, Player, EventSystem + 0x58, the
// OpenWorldStage family, ...) register a transceiver with one of them. Names are placeholders; the namespace is a
// guess.

// A debug message broker embedded in the manager (placeholder: only what the vtable needs; 0x12d8 bytes each).
class Unk_DebugBoardBroker final : public ksys::IMessageBroker {
public:
    void setId(const SetIdArg& arg) override;
    ksys::IMessageBrokerRegister* getRegister() override;

    u8 _[0x12d8 - sizeof(ksys::IMessageBroker)];
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
class Unk_710246c478 {
public:
    virtual ~Unk_710246c478() = default;
};

class Unk_710246c458 : public Unk_710246c478 {
public:
    Unk_710246c458();
    ~Unk_710246c458() override;
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
    ksys::MessageTransceiverBase* mTransceiver;
};

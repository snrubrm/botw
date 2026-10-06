#pragma once

#include <basis/seadTypes.h>
#include <heap/seadDisposer.h>
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Utils/Thread/MessageTransceiverId.h"

// Name from the CSV (GameSceneSubsys14::createInstance 0x7100903598, ctor 0x7100903620, init,
// initCurrentLocation, postCalc, x_N, ...; instance pointer at 0x71025d1760). A polymorphic sead
// singleton; only the member that the AI code reads is declared so far (the transceiver that the
// area-location senders of CookPotRoot, DragonRoot, IceMakerBlock and PlayerAreaInOutSendMessage
// address their messages to).
// TODO: incomplete (layout and namespace unknown; the CSV name has no namespace).
class GameSceneSubsys14 {
    SEAD_SINGLETON_DISPOSER(GameSceneSubsys14)
    GameSceneSubsys14();
    virtual ~GameSceneSubsys14();

public:
    // 0x7100903fbc (CSV GameSceneSubsys14::postCalc; declared only).
    void postCalc();
    // 0x7100904ed4-0x7100904f68: out-of-line flag getters (`__auto*` in the CSV; bit meanings unknown).
    bool sub_7100904ED4() const;
    bool sub_7100904EE0() const;
    bool sub_7100904EF8() const;
    bool sub_7100904F04() const;
    bool sub_7100904F10() const;
    bool sub_7100904F1C() const;
    bool sub_7100904F28() const;
    bool sub_7100904F34() const;
    bool sub_7100904F40() const;
    bool sub_7100904F4C() const;
    bool sub_7100904F68() const;

    u8 _28[0x168 - 0x28];
    u32 _168;
    u32 _16c;
    u8 _170[0x180 - 0x170];
    const ksys::MesTransceiverId* _180;
};

// Placeholder name (out-of-line ctor 0x7100903948 / dtor 0x7100903b38; embedded at GameSceneSubsys14 + 0x1040): 16
// actor links with an id each (-1 = none).
class Unk_7100903948 {
public:
    Unk_7100903948();
    ~Unk_7100903948();

    struct Slot {
        s32 id = -1;
        ksys::act::BaseProcLink link;
    };

    Slot slots[16];
};
KSYS_CHECK_SIZE_NX150(Unk_7100903948, 0x180);

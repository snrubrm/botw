#pragma once

#include <basis/seadTypes.h>
#include <heap/seadDisposer.h>
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
    u8 _28[0x180 - 0x28];
    const ksys::MesTransceiverId* _180;
};

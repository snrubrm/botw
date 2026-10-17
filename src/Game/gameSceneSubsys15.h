#pragma once

#include <heap/seadDisposer.h>
#include "KingSystem/Sound/sndSound.h"
#include "KingSystem/Utils/Types.h"

// Name from the CSV (GameSceneSubsys15::createInstance 0x710089469c). A sead singleton that answers the sound
// system's BGM condition queries from game data flags; it registers itself as SoundMgr::_c8.
class GameSceneSubsys15 : public ksys::snd::Unk_710246be38 {
    SEAD_SINGLETON_DISPOSER(GameSceneSubsys15)
    GameSceneSubsys15() { ksys::snd::SoundMgr::instance()->_c8 = this; }
    ~GameSceneSubsys15() override;

public:
    // 0x7100894aac: clears the flags.
    void m2() override;
    void m3() override;
    // Terminal / Ganon state queries, selected by the battle dungeon BGM controller's dungeon index.
    s32 m4() override;
    bool m5() override;
    bool m6() override;
    // 0x7100894d2c: inside the Eventide Island challenge.
    bool m7() override;
    // 0x7100894d64: Tarrey Town progress 0 - 5.
    s32 m8() override;
    bool m9() override;

private:
    /* 0x28 */ u8 _28 = 0;
};
KSYS_CHECK_SIZE_NX150(GameSceneSubsys15, 0x30);

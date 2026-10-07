#pragma once

#include <basis/seadTypes.h>
#include <heap/seadDisposer.h>
#include <container/seadSafeArray.h>
#include <prim/seadSafeString.h>
#include "Game/gameAlbumInfo.h"
#include "KingSystem/Utils/Types.h"

namespace uking {

// Placeholder name (lane2 s46): the 0x308-byte save slot data of SaveSystem (only two flag bytes are read).
struct SaveSlotData {
    u8 _0[0x300];
    /* 0x300 */ u8 _300;
    u8 _301;
    /* 0x302 */ u8 _302;
    u8 _303[0x308 - 0x303];
};

// Placeholder declaration (name from the CSV: SaveSystem::createInstance 0x710090ee60, ctor
// 0x710090eee8, calc 0x7100910e5c, init, invokedAutoSave, isFinishedSavingMaybe, ...; instance
// pointer at 0x71025d2028; namespace is a guess). The game-level save controller that drives
// ksys::SaveMgr. A polymorphic sead singleton; only what the AI actions use is declared.
// TODO: incomplete.
class SaveSystem {
    SEAD_SINGLETON_DISPOSER(SaveSystem)
    SaveSystem();
    virtual ~SaveSystem();

public:
    // 0x7100915764 (CSV SaveSystem::isFinishedSavingMaybe): ksys::SaveMgr is idle (+0x38 == 0) and
    // this->_3c == 0.
    bool isFinishedSavingMaybe() const;
    // 0x710091579c (CSV SaveSystem::loadDone): the same test as isFinishedSavingMaybe (a separate copy).
    bool loadDone() const;
    // 0x71009147f4 (CSV SaveSystem::startLoad2; declaration only)
    void startLoad2(s32 slot);
    // 0x71009167f8 (CSV SaveSystem::requestAutoSaveForGameClear; declaration only)
    void requestAutoSaveForGameClear(const sead::SafeString& game_clear_flag);
    // 0x71009146f8 (CSV SaveSystem::setRetryData; declaration only)
    bool setRetryData();
    // 0x71009145f8 (CSV SaveSystem::loadOptionsStart; declaration only; 256 bytes)
    void sub_71009145F8();

    // 0x7100914ce4 (CSV __auto3), 0x71009154a8, 0x7100914dc8 (declared only; lane2 s46): the SaveMgr is idle and no save
    // is pending / the number of slots / the slot `index`.
    bool sub_7100914CE4() const;
    s32 sub_71009154A8(s32 a);
    SaveSlotData* sub_7100914DC8(s32 index, bool a);

    u8 _28[0x30 - 0x28];
    s32 _30;
    u32 _34;
    // bit 2 (4): see isFirstLaunch
    u8 _38;
    u8 _39[0x3c - 0x39];
    // The save state (read by GameScene::sub_71007B1C64, isFinishedSavingMaybe).
    u32 _3c;
    sead::SafeArray<SaveSlot, 8> _40;
    AlbumInfo _1880;
    u8 _1a00[0x1a28 - 0x1a00];
    f32 _1a28;
    u8 _1a2c[0x1a34 - 0x1a2c];
    // bool / s32 flag indices (with the flag handle prefix in the top byte) set by requestAutoSaveForGameClear
    u32 _1a34;
    u32 _1a38;
    u8 _1a3c[0x1a42 - 0x1a3c];
    bool _1a42;
    u8 _1a43[0x1a50 - 0x1a43];
    // bit 2 (4): auto saving paused (cleared by DisableAutoSavePausing); bit 11 (0x800) is tested by calc
    u16 _1a50;
};

}  // namespace uking

#pragma once

#include <basis/seadTypes.h>
#include <heap/seadDisposer.h>
#include <container/seadSafeArray.h>
#include <prim/seadSafeString.h>
#include "Game/gameAlbumInfo.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {
class Actor;
}

namespace uking {

// The per-slot save data (0x308 bytes; only the flag at +0x300 is known: tested by AlbumInfo's copy helpers).
struct SaveSlot {
    s32 mAlbumIndices[0x30];  // the picture indices of the slot's album (copied by AlbumInfo)
    u8 _c0[0x2f8 - 0xc0];
    /* 0x2f8 */ s32 _2f8;  // set from the UI manager when saving (initA / init1)
    u8 _2fc[4];
    bool _300;
    u8 _301;
    /* 0x302 */ u8 _302;  // read by the UI save-slot scan (lane2 s46)
    u8 _303;
    /* 0x304 */ bool _304;
    u8 _305[3];
};
KSYS_CHECK_SIZE_NX150(SaveSlot, 0x308);

// Placeholders (unknown classes: the objects at SaveSystem + 0x1a00 / + 0x1a08).
class SaveFlagCache {
public:
    // 0x710090cdf4 (CSV AlbumInfo::x; declared only)
    void sub_710090CDF4();
};

class SaveFlagCacheOwner {
public:
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual void m3();
    virtual void m4();
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
    // 0x71009145f8 (CSV SaveSystem::loadOptionsStart): starts loading the options save file (state 24 first when the
    // save manager asks for the track block file number); false when the save system is busy.
    bool sub_71009145F8();
    // 0x7100913cc8 (CSV loadOptions; declared only)
    void sub_7100913CC8(bool a);

    // 0x7100914ce4 / 0x7100914504 (CSV SaveSystem::__auto3 / __auto4; the same test as isFinishedSavingMaybe,
    // separate copies called by the UI).
    bool sub_7100914CE4() const;
    bool sub_7100914504() const;
    // 0x71009154a8 / 0x7100914dc8 (declared only; lane2 s46): the number of slots / the slot `index`.
    s32 sub_71009154A8(s32 a);
    // The slot `index` after sub_7100914E20 (the default slot when there is no such slot).
    SaveSlot* sub_7100914DC8(s32 index, bool a);
    // 0x7100914e20 (1672 bytes, declared only): maps the slot number to the index into _40 (sorting the used
    // slots by the 64-bit time stamp at +0x2f0); negative when there is no such slot.
    s32 sub_7100914E20(s32 index, bool a);
    // 0x7100915a00: when bit 4 of _38 is set, the flag at +0x304 of the first slot (the default slot when
    // there is none) if its +0x300 flag is set.
    bool sub_7100915A00();
    // 0x7100915f58 (CSV SaveSystem::__auto5): the album picture index flag `idx` (AlbumInfo at +0x1880).
    s32 sub_7100915F58(s32 idx);
    // 0x71009157d4 (CSV SaveSystem::isFirstLaunch): true while bit 2 of _38 is clear.
    bool isFirstLaunch() const;
    // 0x71009167f4 (CSV SaveSystem::noop)
    void noop();
    // 0x710090fd08 / 0x7100914d1c / 0x71009167c8: request a reset of the game data flags (the first sets
    // BitFlag 8 and ResetFlag 8, the others BitFlag 8 and ResetFlag 2 / 4).
    void newDayCallback();
    void setGameDataMgrResetFlag2();
    void setGdmFlagsBeforeStageGen();
    // 0x7100910cd0 / 0x7100910c94 (CSV SaveSystem::invoked3 / invoked8): whether the save state is one of
    // the "busy" states; invoked8 additionally records `value` (and _1a50 bit 3) when it is not.
    bool sub_7100910CD0() const;
    void sub_7100910C94(f32 value);
    // 0x7100915914 (CSV SaveSystem::x_3): requests a manual save of `slot` (state 30) when saving is possible.
    bool x_3(s32 slot);
    // 0x7100912b18: hashes the track block file number flag name (hard mode variant) into the game data
    // manager and goes to state 38.
    void calculateTrackBlockSaveNumberFlagHash();
    // 0x7100914d48 (CSV SaveSystem::__auto1): starts the state 6 (when the save and game data managers exist).
    bool sub_7100914D48();
    // 0x7100914da0 (CSV SaveSystem::__auto2): the per-slot data (slot 0 unless bit 0 of _38 is set).
    SaveSlot* sub_7100914DA0(s32 slot);
    // 0x710091410c: true when the E3 demo mode is off and the state _30 is 8.
    bool sub_710091410C() const;
    // 0x7100913160: like sub_7100914D48 but goes to state 22.
    bool sub_7100913160();
    // 0x71009157e4: finishes the album processing of the current slot and sets _30 to 8.
    void sub_71009157E4();
    // 0x7100910d04 (CSV SaveSystem::invoked6): 2 while the scene is paused (Root38 flag 6), 1 while it is not
    // frozen, else 0.
    s32 sub_7100910D04() const;

    // 0x7100915838 (CSV __auto0): when the save state is idle: clears the flag at +0x300 of every slot whose flag at
    // +0x301 is set; true when it ran.
    bool sub_7100915838();
    // 0x7100911bb8 (CSV initA) / 0x710091171c (CSV init1): the save state start steps that record the UI manager field
    // in the slot and start the save (state 11 / 2).
    void sub_7100911BB8();
    // 0x7100912464 (CSV init27): when the tracker block save file exists, writes it (state 40), else resets the
    // callbacks and flags.
    void sub_7100912464();
    // 0x710090fa84 (CSV callback): the save finished / was cancelled callback: resets the state unless it is 2 or 11.
    void callback();
    // 0x710090fb5c (CSV finishLoadCb): the load finished: starts state 35 and applies the loaded game data fixes.
    void finishLoadCb();
    // 0x7100912c94 (CSV x; declared only)
    void sub_7100912C94(s32 slot);
    // 0x710091453c (CSV triggerAutoSaveFromArea): an auto save requested by the area actor `actor` (not again for
    // the same map object while the cool down _1a24 runs).
    bool triggerAutoSaveFromArea(ksys::act::Actor* actor);
    // 0x71009109ec (CSV invokedAutoSave; declared only)
    bool sub_71009109EC(bool a, bool b);
    // 0x7100911524 (CSV init2) / 0x7100911620 (CSV initC): the steps that save the slot caption image (state 4 / 13).
    void sub_7100911524();
    void sub_7100911620();
    // 0x7100912a50 (CSV init20): flushes the flag cache, records the auto save flags and goes to state 37.
    void sub_7100912A50();
    // 0x7100912ea4 (CSV clearAllCbsAndResetFlagsToInitial; declared only)
    void sub_7100912EA4(bool a);
    void sub_710091171C();
    // 0x7100912be0 (CSV x_1): true when saving is not possible right now (the demo was not played, saving is
    // prohibited, auto saving is paused, ...) or the map type is empty.
    bool sub_7100912BE0(bool check_ui);

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
    // 0x1a00 / 0x1a08: objects of unknown type (0x1a00 is passed to the album cache flush 0x90cdf4; 0x1a08 has a virtual
    // function called by init20)
    SaveFlagCache* _1a00;
    SaveFlagCacheOwner* _1a08;
    // The track block save file number
    s32 _1a10;
    u8 _1a14[4];
    // The buffer written by SaveMgr::x for the tracker file
    void* _1a18;
    f32 _1a20;
    f32 _1a24;
    f32 _1a28;
    s32 _1a2c;
    // The HashId of the map object of the last auto save area
    u32 _1a30;
    // bool / s32 flag indices (with the flag handle prefix in the top byte) set by requestAutoSaveForGameClear
    u32 _1a34;
    u32 _1a38;
    u8 _1a3c[0x1a42 - 0x1a3c];
    bool _1a42;
    bool _1a43;
    bool _1a44;
    u8 _1a45[0x1a50 - 0x1a45];
    // bit 2 (4): auto saving paused (cleared by DisableAutoSavePausing); bit 11 (0x800) is tested by calc
    u16 _1a50;
    u8 _1a52[0x1ef8 - 0x1a52];
};
KSYS_CHECK_SIZE_NX150(SaveSystem, 0x1ef8);

}  // namespace uking

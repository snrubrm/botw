#pragma once

#include <basis/seadTypes.h>
#include <container/seadPtrArray.h>
#include <heap/seadDisposer.h>
#include "KingSystem/System/StringBoard.h"
#include "KingSystem/Utils/Types.h"

class DebugStatus;

// Name from the CSV (GameSceneStatusMgr::createInstance 0x71010bd158, registerStatus 0x71010bd280, ...;
// the CSV name has no namespace). A sead singleton without vtable that keeps the sorted list of
// DebugStatus lines and draws them (debug builds only, mostly stubbed in the release binary).
// TODO: incomplete (registerStatus and the draw function are not decompiled).
class GameSceneStatusMgr {
    SEAD_SINGLETON_DISPOSER(GameSceneStatusMgr)
    GameSceneStatusMgr() = default;

public:
    // 0x71010bd280 (declared only): adds `status` and sorts the list by id, then by title.
    void registerStatus(DebugStatus* status);
    // 0x71010bd50c
    void unregisterStatus(DebugStatus* status);
    // 0x71010bd55c (declared only): draws the list.
    void draw();
    // 0x71010bdc48: clears every status.
    void clearStatuses();
    // 0x71010bdce4 / 0x71010bdcf0 / 0x71010bdcfc: bool setters
    void sub_71010BDCE4(bool value);
    void sub_71010BDCF0(bool value);
    void sub_71010BDCFC(bool value);

private:
    bool _20 = true;
    bool _21 = false;
    bool _22 = false;
    bool _23 = true;
    ksys::StringBoard _28;
    sead::FixedPtrArray<DebugStatus, 16> mStatuses;
    ksys::StringBoard _c0[48];
};
KSYS_CHECK_SIZE_NX150(GameSceneStatusMgr, 0x240);

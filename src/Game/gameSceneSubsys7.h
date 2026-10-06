#pragma once

#include <basis/seadTypes.h>
#include <heap/seadDisposer.h>
#include <heap/seadHeap.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Utils/Types.h"

// Name from the CSV (GameSceneSubsys7::createInstance 0x71007d32e8, init 0x71007d33fc,
// createTeraSystem 0x71007d3460, loadTscbMaybe 0x71007d3520, getTeraSystem; the CSV name has no
// namespace). A sead singleton without vtable that owns the terrain system and its heap.
// TODO: incomplete (createTeraSystem and loadTscbMaybe are not decompiled).
class GameSceneSubsys7 {
    SEAD_SINGLETON_DISPOSER(GameSceneSubsys7)
    GameSceneSubsys7() = default;

public:
    // 0x71007d33fc: creates the "Terrain Scene" heap.
    void init(sead::Heap* parent);
    // 0x71007d3d38
    void* getTeraSystem() const;

private:
    ksys::res::Handle _20;
    void* mTeraSystem = nullptr;
    sead::Heap* mHeap = nullptr;
    s32 _80 = 3;
    sead::FixedSafeString<0x20> _88;
    sead::FixedSafeString<0x20> _c0;
};
KSYS_CHECK_SIZE_NX150(GameSceneSubsys7, 0xf8);

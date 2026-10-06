#pragma once

#include <basis/seadTypes.h>
#include <heap/seadDisposer.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Utils/Types.h"

// Name from the CSV (SceneMgr::createInstance 0x7100896254, setStageName 0x7100896384, getMapPosition
// 0x710089646c, setWarpDLCDestPosAndDegree 0x7100897644, getStartPosForDungeon; the CSV name has no
// namespace). A polymorphic sead singleton.
// TODO: incomplete (getMapPosition and the other functions are not decompiled).
class SceneMgr {
    SEAD_SINGLETON_DISPOSER(SceneMgr)
    SceneMgr() = default;
    virtual ~SceneMgr();

public:
    // 0x7100896384: copies the name into the stage name buffer.
    void setStageName(const sead::SafeString& name);
    // 0x7100897644
    void setWarpDLCDestPosAndDegree(const sead::Vector3f& pos, const f32& degree);

private:
    sead::FixedSafeString<0x100> _28;
    sead::FixedSafeString<0x40> mStageName;
};
KSYS_CHECK_SIZE_NX150(SceneMgr, 0x198);

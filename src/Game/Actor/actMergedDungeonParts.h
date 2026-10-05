#pragma once

#include <math/seadMatrix.h>
#include "Game/Actor/actMapConst.h"

namespace uking::act {

// Name from the CSV (MergedDungeonParts::*; the namespace is a guess). Factory 0x7100ddcb4: new(0xbc8) + inlined
// ctor. RTTI static 0x71025b7238.
// TODO: incomplete (m63 = 984 B not written).
class MergedDungeonParts : public MapConstActiveOrMergedDungeonParts {
    SEAD_RTTI_OVERRIDE(MergedDungeonParts, MapConstActiveOrMergedDungeonParts)
public:
    explicit MergedDungeonParts(const CreateArg& arg);

    static ksys::act::BaseProc* construct(const CreateArg& arg, sead::Heap* heap);
    void m63() override;
    void updatePositionMaybe() override;

    /* 0x850 */ sead::Matrix34f _850[17];
    /* 0xb80 */ s32 _b80[17];
};
KSYS_CHECK_SIZE_NX150(MergedDungeonParts, 0xbc8);

}  // namespace uking::act

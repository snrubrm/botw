#pragma once

#include "KingSystem/ActorSystem/actActor.h"

namespace uking::act {

// Name from the CSV (AreaManagement::*; the namespace is a guess). Factory 0x7100e27418: new(0x848) + inlined
// ctor (clears the first two job handlers). RTTI static 0x7102602288.
// TODO: incomplete (m29 = onJobPush2_ and m64 = initMaybe not written yet).
class AreaManagement : public ksys::act::Actor {
    SEAD_RTTI_OVERRIDE(AreaManagement, ksys::act::Actor)
public:
    explicit AreaManagement(const CreateArg& arg);

    static ksys::act::BaseProc* construct(const CreateArg& arg, sead::Heap* heap);

    void m73() override;
    int getCalcTiming() override;

    /* 0x83c */ u32 _83c = 0;
    /* 0x840 */ u8 _840 = 0;
    /* 0x841 */ u8 _841 = 0;
    /* 0x842 */ u8 _842 = 0;
    /* 0x843 */ u8 _843 = 0;
};
KSYS_CHECK_SIZE_NX150(AreaManagement, 0x848);

}  // namespace uking::act

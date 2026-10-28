#pragma once

#include <heap/seadHeap.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Utils/Types.h"

namespace uking {

// Base of the "arg" classes (RTTI base only; its typeinfo is checked by OpenWorldStageArg's checkDerived...;
// the name is a guess after OpenWorldStageArg). The virtuals are the binder interface of the arg: slots 4 / 5
// return 0 in OpenWorldStageArg.
class StageArg {
    SEAD_RTTI_BASE(StageArg)
public:
    virtual ~StageArg() = default;

    virtual s32 m4() = 0;
    virtual s32 m5() = 0;
    virtual void setHeap(sead::Heap* heap) = 0;
    virtual s32 m7() = 0;
    virtual const sead::SafeString& m8() = 0;
    virtual const sead::SafeString& m9() = 0;
    virtual const sead::SafeString& m10() = 0;
    virtual s32 m11() = 0;
    virtual bool m12() = 0;
};

}  // namespace uking

// The arg of the StartupSaveCheckStageBinder and of StartupSaveCheckStage::init (0x20 bytes; vtable
// 0x710245c368, 13 slots). Its (non-inlined) virtuals are in the StartupSaveCheckStage TU
// (0x71007d17d8-0x71007d182c). Global scope: the CSV/data symbols are unqualified.
class Unk_710245c368 : public uking::StageArg {
    SEAD_RTTI_OVERRIDE(Unk_710245c368, uking::StageArg)
public:
    // 0x71007d17d8 (out of line; empty)
    ~Unk_710245c368() override;

    s32 m4() override;
    // 0x71007d17e8: the next slot after m4, also 4 (like TitleStageArg's m4 / m5).
    s32 m5() override;
    void setHeap(sead::Heap* heap) override;
    s32 m7() override;
    const sead::SafeString& m8() override;
    const sead::SafeString& m9() override;
    const sead::SafeString& m10() override;
    s32 m11() override;
    bool m12() override;

    /* 0x08 */ u32 _0;
    /* 0x0c */ u32 _4;
    /* 0x10 */ sead::Heap* mHeap;
    /* 0x18 */ s32 _18;
    /* 0x1c */ bool _1c;
};
KSYS_CHECK_SIZE_NX150(Unk_710245c368, 0x20);

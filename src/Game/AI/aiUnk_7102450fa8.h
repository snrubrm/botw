#pragma once

#include <basis/seadTypes.h>
#include <prim/seadBitFlag.h>
#include <prim/seadEnum.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <prim/seadSafeString.h>
#include "Game/AI/aiUnk_71025afb58.h"
#include "Game/AI/aiUnk_7102357210.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Utils/Types.h"

// Unnamed class of the object shared by the PriestBoss* AI trees through the
// "PriestBossMetaAIUnit" AI tree variable. Created by PriestBossMetaAIRoot::init_ (create 0x7100718360,
// ctor 0x7100717eec, init 0x71007183a4); its functions live at 0x7100717000-0x710071c000.
// Placeholder name = vtable address. Only the members used by its users are declared.
class Unk_7102450fa8 : public Unk_71025afb58 {
    SEAD_RTTI_OVERRIDE(Unk_7102450fa8, Unk_71025afb58)
public:
    SEAD_ENUM(Phase, _0, _1, _2, _3, _4)
    SEAD_ENUM(Flag, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15)

    ~Unk_7102450fa8() override;

    /* 0x008 */ s32 _8;
    /* 0x010 */ void* _10;  // new[]'d array of 0xf0-byte objects (BaseProcLink at +0xe0)
    /* 0x018 */ ksys::act::BaseProcLink _18;
    /* 0x028 */ ksys::act::BaseProcLink _28;
    /* 0x038 */ u32 _38;
    /* 0x03c */ Phase _3c;
    /* 0x040 */ f32 _40;  // compared with PriestBossActorNormalMode's SecondHalfLifePercent
    /* 0x044 */ u8 _44[0x78 - 0x44];
    /* 0x078 */ sead::BitFlag32 _78;
    /* 0x07c */ u8 _7c[0xa0 - 0x7c];
    /* 0x0a0 */ u8 _a0[0x1b8 - 0xa0];  // sead::FixedObjArray<?, 9> (0x10-byte nodes) at 0xa0
    /* 0x1b8 */ Unk_71024509a8 _1b8;
    /* 0x200 */ u8 _200[0x208 - 0x200];
    /* 0x208 */ Unk_7102450858 _208;
    /* 0x248 */ u8 _248[0x258 - 0x248];
    /* 0x258 */ Unk_7102450918 _258;
    /* 0x2b0 */ sead::FixedSafeString<128> _2b0;
    /* 0x348 */ u8 _348[0x368 - 0x348];
    /* 0x368 */ Unk_71024508b8 _368;
    /* 0x3c8 */ u8 _3c8[0x448 - 0x3c8];  // BaseProcLink at 0x3d0; sead::FixedRingBuffer<?, 6> at 0x3f0
};
KSYS_CHECK_SIZE_NX150(Unk_7102450fa8, 0x448);

#pragma once

#include <container/seadObjArray.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiClassDef.h"
#include "Game/AI/aiUnk_71025afb58.h"

namespace uking {
class AirOctaDataMgr : public Unk_71025afb58 {
    SEAD_RTTI_OVERRIDE(AirOctaDataMgr, Unk_71025afb58)
public:
    ksys::act::BaseProcLink& getProc() { return mBaseProcLink; }
    void changeOctasYheightMaybe();
    // 0x71002faf84 (not decompiled; placeholder name): finds the linked reference objects of `actor`
    // and acquires them into mBaseProcLink / mBaseProcLink2 (unless mFlags bit 0 is set).
    void sub_71002FAF84(ksys::act::Actor* actor);
    // 0x71002fb1a8 (placeholder name; message 0x80000c8 type 1): passes `a1` to the helper 0x71002fb1d8 on
    // unk_28 and sets mFlags bit 2.
    void sub_71002FB1A8(u64 a1);
    void sub_71002FB340(f32 x, f32 z);

    // Placeholder (lane3 s36): the object at +0x28 as returned by sub_71002FB32C (only two flag bytes are
    // read: +0xb1 / +0xb2 = mgr +0xd9 / +0xda).
    struct SubData {
        u8 _0[0xb1];
        bool _b1;
        bool _b2;
    };
    // 0x71002fb32c (declared only): `this + 0x28` if mFlags bit 2 is set, else null.
    SubData* sub_71002FB32C();

    struct MessageData {
        u32 unk_00;
        u64 unk_08;
    };

    /* 0x08 */ ksys::act::BaseProcLink mBaseProcLink;
    /* 0x18 */ ksys::act::BaseProcLink mBaseProcLink2;
    /* 0x28 */ void* unk_28{};
    /* 0x30 */ u32 unk_30{};
    /* 0x34 */ sead::Vector3f unk_34{sead::Vector3f::zero};
    /* 0x40 */ void* unk_40{};
    /* 0x48 */ u32 unk_48{};
    /* 0x4C */ sead::Vector3f unk_4C{sead::Vector3f::zero};
    /* 0x58 */ sead::FixedObjArray<MessageData, 4> obj_arr;
    /* 0xD8 */ u16 unk_D8{};
    /* 0xDA */ bool unk_DA{};
    /* 0xDC */ u32 unk_DC;
    /* 0xE0 */ sead::Vector3f vec_E0{sead::Vector3f::zero};
    /* 0xEC */ sead::Vector3f vec_EC{sead::Vector3f::zero};
    /* 0xF8 */ sead::Vector3f vec_F8{sead::Vector3f::zero};
    /*0x104 */ sead::Vector3f vec_104{sead::Vector3f::zero};
    /*0x110 */ float unk_110 = 0;
    /*0x114 */ float unk_114 = 0;
    /*0x118 */ float unk_118 = 0;
    /*0x11c */ float unk_11c = 0;
    /*0x120 */ u32 mFlags = 0;
};
}  // namespace uking

#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <thread/seadAtomic.h>
#include "KingSystem/Utils/Types.h"

namespace sead {
template <typename T>
class SafeStringBase;
using SafeString = SafeStringBase<char>;
}  // namespace sead

namespace ksys::map {

class Object;

// TODO: incomplete (CSV PlacementGenGroup; only the members read by ObjectLinkData's forwarders are declared and the
// size is unknown).
class GenGroup {
public:
    // 0x0000007100d50778
    void sub_7100D50778(Object* obj);
    // 0x0000007100d5119c
    void sub_7100D5119C(Object* obj);

    // Placeholder names (declared only; lane4 s30), called by ObjectLinkData's forwarders.
    void sub_7100D507F8();
    void deleteEachActorIfDeleteType2();
    void sub_7100D50E00();
    bool sub_7100D50E44(bool a1);
    void sub_7100D50E90(bool a1);
    bool sub_7100D50EF4(bool a1);
    bool sub_7100D51064();
    void sub_7100D510D0();
    u8 sub_7100D510FC();
    void sub_7100D51250(bool a1, u32 a2);
    bool sub_7100D51330(const u32* a1);
    bool checkContainsObjWithName(const sead::SafeString& name, const u32* mode);

    /* 0x00 */ u8 _0[4];
    /* 0x04 */ sead::Atomic<s32> _4;
    /* 0x08 */ sead::Atomic<s32> mNumPrepareDelete;
    /* 0x0c */ u8 _c[0x10 - 0xc];
    /* 0x10 */ sead::Atomic<s32> _10;
    /* 0x14 */ sead::Atomic<s32> _14;
    /* 0x18 */ u16 _18;
    /* 0x1a */ u8 mInitState;  // 2: complete, 3: state 3
    /* 0x1b */ u8 mNumExecLinkTag;
    /* 0x1c */ u8 _1c[2];
    /* 0x1e */ u8 mHasCreateOrDeleteLinks;
    /* 0x1f */ u8 _1f[0x38 - 0x1f];
    /* 0x38 */ sead::Buffer<Object*> mObjects;
};

}  // namespace ksys::map

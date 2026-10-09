#pragma once

#include <basis/seadTypes.h>

namespace sead {
class Heap;
}

namespace uking::action {
class SoundOcclusionTagAction;
}

namespace ksys::snd {

// Placeholder: the type of the owned objects of OcclusionMgr (deleted through the virtual destructor in slot 1).
class Unk_OcclusionMgrMember {
public:
    virtual ~Unk_OcclusionMgrMember();
};

// Name from the CSV (snd::OcclusionMgr::ctor 0x7101055f70, init 0x71010560d4 (an empty function in the original)): created in
// SoundMgr's init. TODO: incomplete.
class OcclusionMgr {
    friend class uking::action::SoundOcclusionTagAction;
public:
    // 0x7101055f70
    OcclusionMgr();
    void sub_71010560D4(sead::Heap* heap);
    void sub_7101056868();
    // 0x7101055ffc (D1) / 0x7101056068 (D0)
    virtual ~OcclusionMgr();

private:
    /* 0x08 */ u16 _8 = 0;
    /* 0x0a */ u8 _a = 0;
    /* 0x0c */ u32 _c = 0;
    /* 0x10 */ u32 _10 = 0;
    /* 0x14 */ f32 _14 = 0.6f;
    /* 0x18 */ f32 _18 = 0.4f;
    /* 0x1c */ f32 _1c = 0.1f;
    /* 0x20 */ f32 _20 = 0.6f;
    /* 0x24 */ s32 _24 = 1;
    /* 0x28 */ Unk_OcclusionMgrMember* _28 = nullptr;
    /* 0x30 */ u8* _30 = nullptr;
    /* 0x38 */ u8 _38[0x70 - 0x38] = {};
    /* 0x70 */ f32 _70{};
    /* 0x74 */ bool _74{};
    u8 _75[3];
    /* 0x78 */ u32 _78{};
    /* 0x7c */ u32 _7c{};
    /* 0x80 */ Unk_OcclusionMgrMember* _80 = nullptr;
    /* 0x88 */ u16 _88 = 0;
    u8 _8a[2];
    /* 0x8c */ f32 _8c = 100.0f;
    /* 0x90 */ f32 _90 = 500.0f;
};

}  // namespace ksys::snd

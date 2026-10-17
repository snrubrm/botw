#pragma once

#include "KingSystem/Utils/Types.h"
#include <basis/seadTypes.h>
#include <aal/aalFxDelayParamSetter.h>
#include <container/seadObjList.h>
#include <prim/seadEnum.h>
#include <prim/seadSafeString.h>

namespace sead {
class Heap;
class DrawContext;
class Camera;
class Projection;
class Viewport;
class DirectResource;
}
class Unk_710251b5c0;
// The reverb setting _18 points at (it is the +0x10 data of the preset entry init picks).
struct FxReverbSetting {
    u8 _0[0xc];
    /* 0x0c */ s32 mRoom;
    /* 0x10 */ s32 _10;
    /* 0x14 */ f32 _14;
    u8 _18[0xc];
    /* 0x24 */ s32 _24;
    u8 _28[0x18];
    /* 0x40 */ f32 _40;
};

namespace ksys::snd {

// The reverb preset row index of FxMgr::sub_7101050104 (0 = no preset). Enumerator names are unknown.
SEAD_ENUM(FxPreset, _0, _1, _2, _3, _4, _5)

class Unk_7101059888;

// The preset entries of the pool at +0x40 (0x58 bytes each; ObjList appends its list node, so a
// full pooled node is 0x68 bytes).
struct FxMgrEntry {
    FxMgrEntry* mNextFree;
    u8 _8[0x50];
};
KSYS_CHECK_SIZE_NX150(FxMgrEntry, 0x58);

// Whole SoundMgr::init 11fab7c allocates d8 bytes, calls 104fe98 and stores +50.
// Own constructor installs the whole two-slot table 2502520 (D1 104ff34, D0 105004c).
// Whole FxMgr::init 10504fc creates the 98-byte manager at +50; own D1 deletes it.
class FxMgr {
public:
    FxMgr();
    virtual ~FxMgr();
    void init(sead::Heap* heap);
    // Whole SoundMgr::calc 11FB8A4 calls 1050348 with its FxMgr pointer.
    void sub_7101050348();
    // Whole 105034C updates effect state using only this.
    void sub_710105034C();
    // 0x7101050ccc: applies the I3DL2 room of _18 to the two effects at +0x8 / +0x10.
    void sub_7101050CCC();
    void sub_7101051078();
    void sub_71010511D4();
    // 0x7101050104: the per-frame reverb preset (the five _50->_60 values plus the preset table row and
    // the debug overrides), the environment FX send and the I3DL2 parameters.
    void sub_7101050104();
    // 0x71010511dc: applies the debug room offset of _18 (mRoom) plus the reverb gain to both reverb
    // effects at +0x8 / +0x10.
    void sub_71010511DC(f32 gain);
    // 0x7101051410: loads a direct resource with the given path; `this` is not read.
    sead::DirectResource* sub_7101051410(const sead::SafeString& path, sead::Heap* heap);
    // 0x7101051154: sets the out gain of the two delay effects at +0x68 / +0x70 from `gain`.
    void sub_7101051154(f32 gain);
    // 0x710105126c: sets the out gain of the two delay effects at +0x68 / +0x70 (1.0, 0.1).
    void sub_710105126C();
    void sub_71010514F4(sead::DrawContext* context, const sead::Camera& camera,
                      const sead::Projection& projection, const sead::Viewport& viewport);

    // The two reverb effects and their setting (read by sub_7101050CCC / sub_7101051078).
    /* 0x8 */ Unk_710251b5c0* _8 = nullptr;
    /* 0x10 */ Unk_710251b5c0* _10 = nullptr;
    /* 0x18 */ FxReverbSetting* _18 = nullptr;
    // The used preset entries; init 0x71010504fc gives it an external buffer of four (0x40 / 0x48
    // are its FreeList work pointer and capacity).
    sead::ObjList<FxMgrEntry> mUsed;
    Unk_7101059888* _50 = nullptr;
    // Reverb sends (aal::AuxBusMgr::setEnvFxSend in init).
    /* 0x58 */ f32 _58 = 0.5f;
    /* 0x5c */ f32 _5c = 1.0f;
    /* 0x60 */ f32 _60 = 0.32f;
    /* 0x64 */ bool _64 = false;
    u8 _65[3];
    // The two aal::FxDelay effects (vtable 0x710251b5c0) created by init 0x71010504fc.
    Unk_710251b5c0* _68 = nullptr;
    Unk_710251b5c0* _70 = nullptr;
    /* 0x78 */ aal::FxDelayParamSetter mDelayParams;
    /* 0x98 */ u32 _98 = 0;
    /* 0x9c */ u32 _9c = 0;
    /* 0xa0 */ u32 _a0 = 0;
    /* 0xa4 */ f32 _a4 = 0.0f;
    // Whole calculation 1050104 uses this signed index for the five-float preset table.
    /* 0xa8 */ s32 _a8 = 0;
    /* 0xac */ bool _ac = false;
    u8 _ad[3];
    /* 0xb0 */ f32 _b0 = 0.0f;
    /* 0xb4 */ bool _b4 = false;
    /* 0xb5 */ bool _b5 = false;
    /* 0xb6 */ bool _b6 = false;
    u8 _b7;
    /* 0xb8 */ u32 _b8 = 0;
    /* 0xbc */ f32 _bc = 1.0f;
    /* 0xc0 */ f32 _c0 = 1.0f;
    /* 0xc4 */ u32 _c4 = 0;
    /* 0xc8 */ f32 _c8 = 50.0f;
    /* 0xcc */ f32 _cc = 500.0f;
    /* 0xd0 */ bool _d0 = false;
    u8 _d1[7];
};
KSYS_CHECK_SIZE_NX150(FxMgr, 0xd8);

}  // namespace ksys::snd

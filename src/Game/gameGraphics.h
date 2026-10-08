#pragma once

#include <basis/seadTypes.h>
#include <container/seadPtrArray.h>
#include <gfx/seadCamera.h>
#include <prim/seadBitFlag.h>
#include <thread/seadCriticalSection.h>
#include <gsys/gsysModelScene.h>

// Partial declaration: name from the CSV Graphics::createInstance (0x7100f2a1d0).
// Source namespace remains unknown; global spelling follows the existing scene placeholders.
// No instance layout or construction is modeled here.
class Graphics {
public:
    // Placeholder name: the block at Graphics + 0xa98 (shadow settings; lane3 s35, only the fields
    // EventChangeShadowNearAndFar::calc_ writes are modeled).
    struct Unk_a98 {
        u8 _0[0x12];
        /* 0x12 */ u16 mFlags;  // bit 8: near distance set manually, bit 9: far distance set manually
        u8 _14[0x540 - 0x14];
        /* 0x540 */ f32 mShadowNear;
        /* 0x544 */ f32 mShadowFar;
    };

    // Placeholder names (lane4 s64): the object at Graphics + 0x378 points (+0x18) to a block that holds two floats
    // at 0x1520 / 0x1524 (read by Camera::updateMatrix and sub_710079AE60 as clip distances).
    struct Unk_378_18 {
        u8 _0[0x1520];
        /* 0x1520 */ f32 _1520;
        /* 0x1524 */ f32 _1524;
    };
    struct Unk_378 {
        u8 _0[0x18];
        /* 0x18 */ Unk_378_18* _18;
    };

    // Original instance pointer 0x710260b060 (GOT 0x7102579d58).
    static Graphics* instance() { return sInstance; }
    static Graphics* sInstance;

    // 0x7100f2ddf0: declaration only; selects a lens-flare preset, negative disables it.
    void sub_7100F2DDF0(s32 preset);


    // 0x7100f2af70 (placeholder name; CSV Graphics::__auto0): stores the map kind (byte at +0xf59) under
    // the lock at +0xf18.
    void sub_7100F2AF70(u8 map);

    // 0x7100f2afac / 0x7100f2afe8 / 0x7100f2b024 (lane4 s64; placeholder names; CSV Graphics::__auto9 / __auto14 / x):
    // store a byte at +0xf5b / +0xf5d / +0xf5f under the lock at +0xf18 (values 0 .. 2 seen).
    void sub_7100F2AFAC(u8 value);
    void sub_7100F2AFE8(u8 value);
    void sub_7100F2B024(u8 value);
    // 0x7100f35f28 / 0x7100f35f38 (lane4 s64): `_378->_18->_1520` / `_1524`.
    f32 sub_7100F35F28() const;
    f32 sub_7100F35F38() const;

    // 0x7100f2e06c (placeholder name): sets bit 22 of `_284`.
    void sub_7100F2E06C();

    // 0x7100f35de8 (declaration only; placeholder name; lane2 s47): called by ui::Manager::sub_7100A7F81C
    void sub_7100F35DE8();

    // 0x7100f35fa4 (lane2 request, s49; placeholder name): sets bit 12 (`second`) or 11 (not `second`) of
    // `_284` to `value`, then marks the settings dirty (`_280 |= 1`).
    void sub_7100F35FA4(bool value, bool second);

    // Placeholder name: the block that Graphics + 0xab0 points to (lane2 s47: only the flag word at 0xe48 that
    // NPCMamonoShopRoot::onPreDelete sets is modeled).
    struct Unk_ab0 {
        u8 _0[0xe48];
        /* 0xe48 */ u32 _e48;
    };

    // Only a pointer to the (separately allocated) shadow settings is modeled.
    Unk_a98* getUnk_a98() const { return _a98; }
    Unk_ab0* getUnk_ab0() const { return _ab0; }

private:
    u8 _0[0x150];

public:
    // 0x150: the model scenes (lane5 s3: SystemApplyEnvSetAction::enter_).
    sead::PtrArray<gsys::ModelScene> mModelScenes;

private:
    u8 _160[0x280 - 0x160];
    u32 _280;
    sead::BitFlag32 _284;
    u8 _288[0x378 - 0x288];
    Unk_378* _378;
    u8 _380[0xa98 - 0x380];
    Unk_a98* _a98;
    u8 _aa0[0xab0 - 0xaa0];
    Unk_ab0* _ab0;
    u8 _ab8[0xe08 - 0xab8];

public:
    // 0xe08 (lane1 s44): the camera of the graphics system (read by SkyMgr::sub_71010E4EE0).
    sead::Camera* _e08;

private:
    u8 _e10[0xf18 - 0xe10];
    // Lock for the map kind below (placeholder name).
    sead::CriticalSection _f18;
    u8 _f58;
    u8 _f59;  // map kind (Graphics::sub_7100F2AF70)
    u8 _f5a;
    u8 _f5b;  // sub_7100F2AFAC
    u8 _f5c;
    u8 _f5d;  // sub_7100F2AFE8
    u8 _f5e;
    u8 _f5f;  // sub_7100F2B024
};

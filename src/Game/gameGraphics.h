#pragma once

#include <basis/seadTypes.h>
#include <container/seadPtrArray.h>
#include <container/seadBuffer.h>
#include <math/seadVector.h>
#include <math/seadBoundBox.h>
#include "KingSystem/Utils/Types.h"
#include <gfx/seadCamera.h>
#include <hostio/seadHostIONode.h>
#include <prim/seadBitFlag.h>
#include <thread/seadCriticalSection.h>
#include <gsys/gsysModelScene.h>
#include <gsys/gsysModelUnit.h>
#include <prim/seadSafeString.h>
#include <prim/seadScopedLock.h>

namespace nn::gfx {
class ResTexture;
}
namespace gsys {
class ModelNW;
}
namespace agl::lyr {
class Layer;
}

namespace ksys::act {
class PlayerLink;
}
namespace ksys::world {
class EnvMgr;
}

// Settings registered at Graphics + 0xae0, embedded in RuneMgr + 0x250 and GameSceneSubsys5 + 0x58.
// Constructor 0x7100f35df8; the bounds and result fields are copied by Graphics::sub_7100F2E2A4.
class Unk_7100f35df8 {
public:
    // Copied as one 16-byte block by Graphics::sub_7100F2E2A4 (placeholder name).
    struct Unk_20 {
        sead::Vector3f _0 = sead::Vector3f::zero;
        f32 _c = 0;
    };

    Unk_7100f35df8();

    bool _0 = false;
    u64 _8 = 0;
    sead::BoundBox2f _10;
    Unk_20 _20;
    f32 _30 = 0;
    f32 _34 = 0;
    f32 _38 = 0;
    f32 _3c = 0.36f;
    f32 _40 = 0.48f;
    s32 _44 = 0;
    s32 _48 = 0;
    f32 _4c = 0;
};
KSYS_CHECK_SIZE_NX150(Unk_7100f35df8, 0x50);

// Declaration only: Graphics initializer F2C140 allocates 0x4a8 bytes, constructs this
// object at 12A20E0 and stores it at Graphics + 0xab8. Its source name is unknown.
class Unk_71012a20e0 : public sead::hostio::Node {
public:
    // 12A2268 stores the low byte of mode at 0x1b0; the full word is tested for mode 2.
    // EnvMgr reset 10D326C, doCalc 10D62C0 and wrapper 10DB0B0 call this same receiver.
    void sub_71012A2268(u32 mode);

private:
    // Complete constructor 12A20E0 and cleanup 12A22B0 establish the Node prefix.
    // 12A2768 consumes these two floats and the low mode byte independently.
    // Texture objects and the rest of the lifetime remain undeclared; do not allocate this prefix.
    u8 _8[0x190 - 0x8];
    f32 _190;
    f32 _194;
    u8 _198[0x1b0 - 0x198];
    u8 _1b0;
};

// Declaration only: F2C140 constructs a 0x268-byte object at 129175C and stores it at B38.
// 12920C4 selects a signed buffer index and sets byte 1FF4 in its record.
class Unk_710129175c {
public:
    // Placeholder: the 0x2088-byte records of the buffer at 0x10 (only the fields read through
    // sub_710129276C and Graphics::sub_7100F2E2A4 are modelled).
    struct Record {
        u8 _0[0x1f91];
        u8 _1f91;  // Graphics::sub_7100F2E2A4 tests bit 1 of record 0
        u8 _1f92[0x2088 - 0x1f92];
    };
    static_assert(sizeof(Record) == 0x2088);

    // The result that 0x710129276c fills from a record (layout from Graphics::sub_7100F2E2A4, which copies
    // it to the registered Unk_7100f35df8 settings).
    struct Result {
        u64 _0;
        sead::BoundBox2f bounds;
        f32 _18;
        Unk_7100f35df8::Unk_20 _1c;
        f32 _2c;
    };

    void sub_71012920C4(s32 index);
    // 0x710129276c (declaration only; placeholder name): copies record `index` (the first if out of range)
    // into `result`.
    void sub_710129276C(s32 index, Result* result);

    u8 _0[0x10];
    sead::Buffer<Record> mRecords;
};

// Declaration only: F2C140 constructs these (0x1010 bytes at 0x7100f185a4, stored at Graphics + 0x388;
// 0x178 bytes at 0x7100efd9b8, stored at + 0x3a8) and the GrudgeRenderer at + 0x3a0 (0x2fb0 bytes; name from
// the CSV, namespace unknown). Graphics::sub_7100F2E2A4 calls one method of each.
class Unk_7100f185a4 {
public:
    void sub_7100F1AC58();
};
class Unk_7100efd9b8 {
public:
    void sub_7100EFE030();
};
class GrudgeRenderer {
public:
    void sub_710128F2A4();
};

// Declaration only: F2C140 allocates 0x6c0 bytes, constructs this object at 129421C and stores it at
// Graphics + 0x370. Its source name is unknown.
class Unk_710129421c {
public:
    // 0x71012955ac (placeholder name): stores value at +0x7e4 of entry index of the 0x7e8-byte entry
    // buffer at 0x1e0.
    void sub_71012955AC(f32 value, s32 index);
};

// Partial declaration only: F2C140 constructs this 0x258-byte item filter at
// 1293BAC and stores it at 398. Table 25192A8 inherits Node's class-type method;
// 1293BAC initializes the word at C to 2, and 1293D68 / 1293FC0 consume its flags.
// The DebugTexturePage at 10 and its lifetime remain unmodeled.
class Unk_7101293bac : public sead::hostio::Node {
public:
    virtual ~Unk_7101293bac();
    s32 _8;
    sead::BitFlag32 mFlags;
    u8 _10[0x254 - 0x10];
    // Graphics::setRainRatio 0x7100f2fcdc scales the rain ratio by 1 - this value.
    f32 _254;
};

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
        struct Cell {
            u8 _0[0x18];
            f32 _18;
            u8 _1c[4];
        };
        static_assert(sizeof(Cell) == 0x20);
        u8 _0[0x12a8];
        // 10D103C indexes 0x20-byte cells with Buffer's bounds fallback and reads f32 +0x18.
        /* 0x12a8 */ sead::Buffer<Cell> _12a8;
        u8 _12b8[0x1520 - 0x12b8];
        /* 0x1520 */ f32 _1520;
        /* 0x1524 */ f32 _1524;
    };
    struct Unk_378 {
        u8 _0[0x18];
        /* 0x18 */ Unk_378_18* _18;
        u8 _20[0x268 - 0x20];
        /* 0x268 */ s32 _268;  // grid row width used by 10D103C
    };

    // Original instance pointer 0x710260b060 (GOT 0x7102579d58).
    static Graphics* instance() { return sInstance; }
    static Graphics* sInstance;

    // Native F2E0F4 compares MaterialObj texture resources, or dirties all when texture is null.
    // Texture identity is also proved by initializer 128F724 and native finalizer FE0FE4.
    void sub_7100F2E0F4(gsys::ModelNW* model, const nn::gfx::ResTexture* texture);

    // 0x7100f2ddf0: declaration only; selects a lens-flare preset, negative disables it.
    void sub_7100F2DDF0(s32 preset);

    void sub_7100F2F1C8(Unk_7100f35df8* settings);
    void sub_7100F2F1E8(Unk_7100f35df8* settings);


    // 0x7100f2af70 (placeholder name; CSV Graphics::__auto0): stores the map kind (byte at +0xf59) under
    // the lock at +0xf18.
    void sub_7100F2AF70(u8 map);

    // 0x7100f2e2a4 (placeholder name; CSV Graphics::__auto1): refreshes the registered settings from the
    // object at 0xb38 (if its flag is set), then updates the objects at 0x388 / 0x3a0 / 0x3a8.
    void sub_7100F2E2A4();

    // 0x7100f2afac / 0x7100f2afe8 / 0x7100f2b024 (lane4 s64; placeholder names; CSV Graphics::__auto9 / __auto14 / x):
    // store a byte at +0xf5b / +0xf5d / +0xf5f under the lock at +0xf18 (values 0 .. 2 seen).
    void sub_7100F2AFAC(u8 value);
    void sub_7100F2AFE8(u8 value);
    void sub_7100F2B024(u8 value);
    // 0x7100f35f28 / 0x7100f35f38 (lane4 s64): `_378->_18->_1520` / `_1524`.
    f32 sub_7100F35F28() const;
    f32 sub_7100F35F38() const;
    void sub_7100F35F50(agl::lyr::Layer* layer, bool value);
    void sub_7100F35F68(bool value);

    // 0x7100f2e06c (placeholder name): sets bit 22 of `_284`.
    void sub_7100F2E06C();

    // 0x7100f35de8 (declaration only; placeholder name; lane2 s47): called by ui::Manager::sub_7100A7F81C
    void sub_7100F35DE8();

    // 0x7100f2fb6c (placeholder name; CSV Graphics::__auto6): stores the ratio at 0xe84 and sets
    // uking_dynamic_proj_shadow_off to 1 - ratio.
    void sub_7100F2FB6C(f32 ratio);
    // 0x7100f2fc24 (placeholder name): stores the ratio at 0xe80 and sets
    // uking_dynamic_base_light_change_ratio to 1 - ratio.
    void sub_7100F2FC24(f32 ratio);
    // 0x7100f2fcdc (CSV name): sets uking_dynamic_rain_ratio and uking_dynamic_rainfall and picks the
    // environment unit's shader variation (2 when the first scene's _52e0 flag is set, else rain > 0).
    void setRainRatio(f32 ratio, f32 rainfall);
    // 0x7100f2fe38 (CSV Graphics::getDynamicCloudRatio; it sets the value): sets uking_dynamic_cloud_ratio to
    // 1 - ratio clamped to [0, 1].
    void setDynamicCloudRatio(f32 ratio);
    // 0x7100f2ff08 (placeholder name; CSV Graphics::__auto7): stores ratio at 0xe88, passes 1 - scale to the
    // object at 0x370 and sets the depth / world shadow uking_dynamic parameters.
    void sub_7100F2FF08(f32 ratio, f32 scale);
    // Placeholder name: the camera values 0x7100f30178 passes to sub_7100F309FC (camera +0x6c, the projection's
    // fovy from its virtual getter at +0x30, Graphics +0x358).
    struct DofCameraArg {
        f32 focus_distance;
        f32 fovy;
        f32 f_number;
    };
    // 0x7100f309fc (placeholder name; CSV Graphics::__auto8): computes the near / far blur ranges of the depth of
    // field from the camera and writes them to the first scene's agl::pfx::DepthOfField. False if the fovy is ~0.
    bool sub_7100F309FC(const DofCameraArg& arg);
    // 0x7100f2faac (placeholder name): sets uking_dynamic_exposure unless the byte at 0xf5a is 4 (force skips the test).
    void sub_7100F2FAAC(f32 exposure, bool force);

    // inline-only in the original; name is a guess: the same lock / searchMaterialParamIndex /
    // setMaterialParamF32 sequence is inlined in 0x7100f2fb6c, 0x7100f2fc24, 0x7100f2fcdc, 0x7100f2fe38,
    // 0x7100f2ff08, 0x7100f2faac and 0x7100f2e5cc.
    // inline-only in the original; name is a guess (searches a material parameter by name and sets it; part of
    // setEnvMaterialParamF32 below, same functions).
    static void setMaterialParamF32(gsys::ModelUnit* unit, s32 material, const sead::SafeString& name,
                                    f32 value) {
        const s32 index = unit->searchMaterialParamIndex(material, name);
        if (index != -1)
            unit->setMaterialParamF32(material, index, value);
    }
    void setEnvMaterialParamF32(const char* name, f32 value) {
        auto lock = sead::makeScopedLock(_ed8);
        setMaterialParamF32(_ea8, _f58, name, value);
    }

    // 0x7100f35e54: settings currently registered by the rune / magnesis managers.
    Unk_7100f35df8* sub_7100F35E54() const;

    // 0x7100f35fa4 (lane2 request, s49; placeholder name): sets bit 12 (`second`) or 11 (not `second`) of
    // `_284` to `value`, then marks the settings dirty (`_280 |= 1`).
    void sub_7100F35FA4(bool value, bool second);

    // Placeholder name: the block that Graphics + 0xab0 points to (lane2 s47: only the flag word at 0xe48 that
    // NPCMamonoShopRoot::onPreDelete sets is modeled).
    struct Unk_ab0 {
        u8 _0[0xe48];
        /* 0xe48 */ u32 _e48;
    };

    // Placeholder name: the block that Graphics + 0xaa8 points to; ksys::act::sub_7100EEAFDC casts along the vector at
    // 0x7f8 (a down direction).
    struct Unk_aa8 {
        u8 _0[0x7f8];
        /* 0x7f8 */ sead::Vector3f _7f8;
    };
    Unk_aa8* getUnk_aa8() const { return _aa8; }

    // Only a pointer to the (separately allocated) shadow settings is modeled.
    Unk_a98* getUnk_a98() const { return _a98; }
    Unk_ab0* getUnk_ab0() const { return _ab0; }

public:
    // Placeholder: the object at 0x118 (SkyMgr::sub_71010E37C8 copies the sky light direction to _1c0).
    struct Unk_118 {
        u8 _0[0x1c0];
        sead::Vector3f _1c0;
    };

private:
    u8 _0[0x118];

public:
    /* 0x118 */ Unk_118* _118;

private:
    u8 _120[0x150 - 0x120];

public:
    // 0x150: the model scenes (lane5 s3: SystemApplyEnvSetAction::enter_).
    sead::PtrArray<gsys::ModelScene> mModelScenes;

private:
    u8 _160[0x280 - 0x160];
    u32 _280;
    sead::BitFlag32 _284;
    u8 _288[0x360 - 0x288];

public:
    // The player link (set by ksys::setPlayerLink).
    /* 0x360 */ ksys::act::PlayerLink* _360;

private:
    u8 _368[0x370 - 0x368];
    Unk_710129421c* _370;

public:
    // Read by the shooting-star grid predicate at 10D103C.
    Unk_378* _378;

private:
    u8 _380[0x388 - 0x380];
    Unk_7100f185a4* _388;
    u8 _390[0x398 - 0x390];
    Unk_7101293bac* _398;
    GrudgeRenderer* _3a0;
    Unk_7100efd9b8* _3a8;
    u8 _3b0[0xa98 - 0x3b0];
    Unk_a98* _a98;
    u8 _aa0[0xaa8 - 0xaa0];
    Unk_aa8* _aa8;
    Unk_ab0* _ab0;
    // EnvMgr reset/update and mode dispatch access this native field directly.
    friend class ksys::world::EnvMgr;
    Unk_71012a20e0* _ab8;
    u8 _ac0[0xae0 - 0xac0];
    Unk_7100f35df8* _ae0;
    u8 _ae8[0xb38 - 0xae8];
    Unk_710129175c* _b38;
    u8 _b40[0xe08 - 0xb40];

public:
    // 0xe08 (lane1 s44): the camera of the graphics system (read by SkyMgr::sub_71010E4EE0).
    sead::Camera* _e08;
    // 0xf32ac8 (CSV Graphics::__auto12; placeholder name): stores the camera at 0xe08 and an unknown object at 0xe10
    // (MainFieldDungeonStage::initForStageGen passes its members at 0x150 / 0x158).
    void sub_7100F32AC8(sead::Camera* camera, void* unk);

private:
    void* _e10;
    u8 _e18[0xe80 - 0xe18];
    f32 _e80;
    f32 _e84;
    f32 _e88;
    f32 _e8c;
    u8 _e90[0xe98 - 0xe90];
    // A model unit whose shader variation setRainRatio (0x7100f2fcdc) picks.
    gsys::ModelUnit* _e98;
    u8 _ea0[0xea8 - 0xea0];
    // The environment model unit whose material parameters the uking_dynamic_* setters change.
    gsys::ModelUnit* _ea8;
    u8 _eb0[0xed8 - 0xeb0];
    sead::CriticalSection _ed8;
    // Lock for the map kind below (placeholder name).
    sead::CriticalSection _f18;
    // Material index used by setEnvMaterialParamF32.
    s8 _f58;
    u8 _f59;  // map kind (Graphics::sub_7100F2AF70)
    u8 _f5a;
    u8 _f5b;  // sub_7100F2AFAC
    u8 _f5c;
    u8 _f5d;  // sub_7100F2AFE8
    u8 _f5e;
    u8 _f5f;  // sub_7100F2B024
};

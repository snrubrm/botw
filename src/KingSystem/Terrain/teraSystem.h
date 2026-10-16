#pragma once

#include <prim/seadSafeString.h>

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <container/seadSafeArray.h>
#include <math/seadVector.h>
#include <math/seadMatrix.h>
#include <thread/seadAtomic.h>
#include <heap/seadHeap.h>
#include "KingSystem/Utils/Types.h"

namespace gsys {
class Model;
}

namespace sead {
class Heap;
class ExpHeap;
}

namespace ksys::phys {
class Material;
}

namespace ksys::tera {

// ResourceHolder 1138A2C supplies a size, name, parent and heap direction.
sead::ExpHeap* sub_7101120314(u32 size, const sead::SafeString& name, sead::Heap* parent,
                            sead::Heap::HeapDirection direction);

// TODO:
class ApertureMaps {
    void updateMap();
};
class ApertureMapsCollector {
    void allocateImage();
    void releaseImage();
};
class System;

class Core {
public:
    class Grass {
    public:
        struct Unk_7101150c24 {
            u32 _0;
            const sead::Vector3f* mPosition;
            f32 _10;
            f32 _14;
            bool _18;
            bool _19;
            bool _1a;
            bool _1b;
            bool _1c;
        };
        static_assert(sizeof(Unk_7101150c24) == 0x20);
        u32 sub_7101150C24(const Unk_7101150c24* arg);
        bool sub_7101150F08(const sead::Vector3f* pos, f32 a, f32 b);
        bool sub_7101150F48(const sead::Vector3f* pos, f32 a, f32 b);
        bool sub_7101150F88(const sead::Vector3f* pos, f32 a, f32 b, bool flag);
        bool sub_7101150FD4(const sead::Vector3f* pos, f32 a, f32 b);
        bool sub_710115101C(const sead::Vector3f* pos, f32 radius);
        // Position and radius from ActorUtil and the independent terrain-cull caller.
        // Declaration only; the implementation remains with the Grass owner.
        bool sub_7101150BA4(const sead::Vector3f* pos, f32 radius);
        // CutGrass and independent Motorcycle/Sandworm callers establish the position and flags.
        // Declaration only; the implementation remains with the Grass owner.
        bool sub_7101151064(const sead::Vector3f* pos, f32 radius, f32 intensity, bool call_effect,
                           bool flag, bool check_ground);
        // 0x71011516d0 (declared only): grass amount at `xz` written to `out`; returns the terrain query result
        // (2 when the grass is disabled, 0 without terrain data).
        u32 sub_71011516D0(f32* out, const sead::Vector2f* xz);

        void sub_7101150990(bool enabled);
        void sub_7101150A7C(const sead::Vector3f* pos, f32 radius, f32 value);
        // 0x7101150be0 (placeholder name; ExpandChemicalField::calc_ with cut grass type 3).
        bool sub_7101150BE0(const sead::Vector3f* pos, f32 radius, f32 value);

        // Shared flags read and written by 0x7101150990 and 0x710114dd4c.
        u8 _0[8];
        u32 mFlags;
    };
    struct Unk_71013010d4 {
        s8 mIndex;
        u8 mFlags;
    };
    static_assert(sizeof(Unk_71013010d4) == 2);
    void sub_71013010D4(const Unk_71013010d4& state, s32 index);

    // Setter 0x7101300b4c and cleanup 0x710130063c prove the position and record stride.
    // The remainder includes an unrecovered uniform block; no record lifetime is implemented.
    struct Unk_7101300b4c {
        u8 _0[8];
        sead::Vector3f mPosition;
        u8 _14[0x1a0 - 0x14];
    };
    static_assert(sizeof(Unk_7101300b4c) == 0x1a0);
    void sub_7101300B4C(u32 index, const sead::Vector3f* position, bool update);
    void sub_7101300F1C(u32 index, const sead::Vector3f* position, bool update);
    void sub_7101300BF0();
    void sub_710130085C();
    void sub_710130089C();
    // 0x7101300aac (declared only; 160 B): sets the visibility mask of the units of the model _f8 (all bits
    // for true).
    void sub_7101300AAC(bool visible);
    void sub_71013008E4(sead::Heap* heap, System* system);
    void sub_71013009C4(sead::Heap* heap);
    bool sub_7101300D50(u32 index, bool a, bool b);

    class Model;
    class Tree;

    u8 _0[0xf0];
    void* _f0;
    gsys::Model* _f8;
    u8 _100[0x38];
    Grass* _138;
    void* _140;
    // Getter 0x710114dd84 and setter 0x71013010d4 share this two-byte record buffer.
    sead::Buffer<Unk_71013010d4> mStates;
    sead::Buffer<Unk_7101300b4c> mPositions;
    u8 _168[0x360 - 0x168];
    // Original 0x710130085c and 0x710130089c reset this word with exclusive-loop exchanges.
    sead::Atomic<u32> _360;
    u8 _364[0x18];
    u8 _37c;
};

// 0x71011501c8 (declaration only): Grass cleanup thunk called by world::ChemicalMgr::unload2;
// the body stays with the Grass owner.
void sub_71011501C8(Core::Grass* grass);

// Terrain is the CSV name of the singleton at 0x7102620698.
// The bases and the remaining members are not modeled yet.
class Terrain {
public:
    static Terrain* sInstance;
    static Terrain* instance() { return sInstance; }

    void setPauseState(bool paused);
    // 0x710114d73c (CSV Terrain::__auto21; placeholder name): Core::sub_710130085C while bits 1 and 2 of _a58 are
    // set.
    void sub_710114D73C();
    // 0x710114deac (CSV Terrain::__auto0; placeholder name): forwards to Core::sub_7101300AAC.
    void sub_710114DEAC(bool visible);
    void sub_710114D8C0(sead::Heap* heap, System* system);
    void sub_710114D8C8(sead::Heap* heap);
    void sub_710114D804(bool enabled, const sead::Matrix44f* projection,
                      const sead::Matrix34f* view);
    s32 sub_710114DD84(s32 index);
    void sub_710114DDF8(u32 index, const sead::Vector3f* position, bool update);
    void sub_710114DE04(u32 index, const sead::Vector3f* position, bool update);
    void sub_710114DDA4(const Core::Unk_71013010d4* states, u32 count);
    bool isGrassEnabled() const { return (_a58 & 2) != 0; }
    Core::Grass* sub_710114DE4C();
    Core::Grass* sub_710114DE58();
    void* sub_710114DE64();
    void* sub_710114DE70();
    void sub_710114DE7C(bool value);
    bool sub_710114DE9C();
    gsys::Model* sub_710114DEE0();
    bool sub_710114DD40();
    f64 sub_710114D9E8();
    void* sub_710114DED4();
    void* sub_710114D8D0();
    struct Unk_710114D8E4 {
        u8 _0[0x10];
        sead::Vector2f _10;
        f32 _18;
    };
    sead::Vector2f sub_710114D8E4(const Unk_710114D8E4* params);
    f32 sub_710114D8F8(const Unk_710114D8E4* params);

    // Placeholders for the chain Terrain::_370->_4ae0 (0x710114de10 / 0x710114de20 / 0x710114de3c).
    struct MaterialName {
        u16 _0;
        char name[1];
    };
    struct MaterialNameTable {
        u8 _0[8];
        MaterialName** mNames;
    };
    struct Unk4ae0 {
        void* _0;
        u8 _8[0x710 - 0x8];
        s32 _710;
        MaterialNameTable* mMaterialNames;
    };
    struct Unk370 {
        u8 _0[0x4ae0];
        Unk4ae0* _4ae0;
    };
    // 0x710114de10 (CSV Terrain::__auto9) / 0x710114de3c (CSV Terrain::__auto6) / 0x710114de20 (placeholder names).
    void* sub_710114DE10() const;
    s32 sub_710114DE3C() const;
    // The name of terrain material `index` (DragonMoveTo searches it for "雪").
    const char* sub_710114DE20(s32 index) const;

    u8 _0[0x360];
    Core* _360;
    u8 _368[0x370 - 0x368];
    Unk370* _370;
    u8 _378[0x3c8 - 0x378];
    f32 _3c8;
    // Passed by sub_710110B4A4 to sub_710110AA5C.
    f32 _3cc;
    u8 _3d0[0x3dc - 0x3d0];
    // Scene::sub_7101101964 gives the first _3dc of 19 entries level 1, the first _3dd level 2 and the
    // first _3de level 3.
    u8 _3dc;
    u8 _3dd;
    u8 _3de;
    u8 _3df[0x400 - 0x3df];
    f32 _400;
    u8 _404[0x680 - 0x404];
    sead::Matrix44f mProjectionMatrix;
    sead::Matrix34f mViewMatrix;
    u8 _6f0[0xa48 - 0x6f0];
    f64 _a48;
    void* _a50;
    u32 _a58;
};
KSYS_CHECK_SIZE_NX150(Terrain, 0xa60);
class ImageResourceMgr {
    void procUnloadResidualRequest();
};
class ResourceHolder;
// Placeholder: the object System::sub_710111F504 returns (`*_e0 + 0x2300`); sub_710110AA5C reads it and its +0x20.
// The nine 0x460-byte objects at the start of a Scene (Scene::sub_7101100260 writes _1c of eight of them).
struct Unk_710111F504 {
    u8 _0[0x1c];
    u16 _1c;
    u8 _1e[0x20 - 0x1e];
    u8 _20;
    u8 _21[0x28 - 0x21];
    u8 _28;
    u8 _29;
    u8 _2a[0x460 - 0x2a];
};
KSYS_CHECK_SIZE_NX150(Unk_710111F504, 0x460);

// The objects System keeps in its 0x90-byte scene slots (name from the CSV row at 0x7101111650).
class Scene {
    void exportFileBinary();

public:
    // 0x71011001d4 (declaration only; placeholder name): stores the two levels at 0x2940 / 0x2941
    // (clamped) and sets flag 4.
    void sub_71011001D4(int level, int type);
    // 0x7101100234 (placeholder name): sets flag 8 from `a` and flag 0x10 from `b`.
    void sub_7101100234(bool a, bool b);
    // 0x7101101914 (placeholder name): copies the levels that are not -1 into _278c; flag 4 if one changed.
    void sub_7101101914(const sead::SafeArray<s32, 19>& levels);
    // 0x7101101a10 / 0x7101101a7c / 0x7101101aa0 (placeholder names): store pointers into the buffers at
    // 0x2910 / 0x2920 / 0x2930.
    void sub_7101101A10(void* a, void* b, void* c, void* d, void* e);
    void sub_7101101A7C(void* a, void* b);
    void sub_7101101AA0(void* a, void* b, void* c);
    // 0x7101101964 (declaration only; placeholder name): refreshes the 19 words at 0x278c from the Terrain
    // and sets flag 4 if one changed.
    void sub_7101101964();
    // 0x71010ffe70 (declaration only; placeholder name): when (a, b) differ from _2780 / _2784, stores them,
    // rebuilds through _2948 and sets flags 0xff00.
    void sub_71010FFE70(s32 a, s32 b);
    // 0x7101100260 (placeholder name): stores the four values as u16 into the sub-objects of
    // stride 0x460 (+0x1c).
    void sub_7101100260(s32 a, s32 b, s32 c, s32 d);

    // [5] is returned by System::sub_710111F4F0, [8] by System::sub_710111F504.
    Unk_710111F504 _0[9];
    // Set on every scene by System::sub_7101112C30.
    sead::Vector3f _2760;
    u8 _276c[0x2780 - 0x276c];
    s32 _2780;
    u8 _2784[0x278c - 0x2784];
    s32 _278c[19];
    u8 _27d8[0x2910 - 0x27d8];
    sead::Buffer<void*> _2910;
    // Element types unknown (pointer-sized).
    sead::Buffer<void*> _2920;
    sead::Buffer<void*> _2930;
    u8 _2940;
    u8 _2941;
    u8 _2942[0x2946 - 0x2942];
    s8 _2946;
    u8 _2947[0x2948 - 0x2947];
    // Placeholder type: System::sub_710111F644 writes its _afc0.
    struct Unk_2948 {
        u8 _0[0xafc0];
        void* _afc0;
    };
    Unk_2948* _2948;
    u8 _2950[0x2998 - 0x2950];
    // Flags: 4 set when the levels change, 8 read by System::sub_710111F618.
    u32 _2998;
};

class System {
public:
    static System* instance();
    // 0x710111f504: `*_e0 + 0x2300`.
    Unk_710111F504* sub_710111F504();
    // 0x710111f4f0 (placeholder name): `*_e0 + 0x15e0`.
    void* sub_710111F4F0();
    // 0x710111f644 (placeholder name): stores `value` in _2948->_afc0 of every scene.
    void sub_710111F644(void* value);
    // 0x710111f518 (placeholder name): sub_71011001D4(level, type) on every scene.
    void sub_710111F518(int level, int type);
    // 0x7101112a74 (placeholder name): sub_7101101964 on every scene, then clears bit 3 of _1338.
    void sub_7101112A74();
    // 0x7101112af0 / 0x7101112b80 (placeholder names): Scene::sub_71010FFE70 / sub_7101100260 on every scene.
    void sub_7101112AF0(s32 a, s32 b);
    void sub_7101112B80(s32 a, s32 b, s32 c, s32 d);
    // 0x7101112c30 (placeholder name): stores `vec` in every scene (_2760) and sets its flag 4.
    void sub_7101112C30(const sead::Vector3f& vec);
    // 0x71011188e4 (placeholder name): `_2946 - 1 - _2780` of the first scene, at least 0.
    s32 sub_71011188E4() const;
    void allocateApertureMapsCollectorImage(sead::Heap* heap);
    void loadScene();
    // 0x710111f618 (CSV TeraSystem::x_0): bit 3 of the flags of the `index`th scene (the first if out of range)
    bool sub_710111F618(s32 index);

    // 0x90-byte entries; only the scene pointer at +0 is known.
    struct SceneSlot {
        Scene* scene;
        u8 _8[0x90 - 0x8];
    };

    u8 _0[0x8];
    // Checked by sub_710110B4A4 (no query without it).
    void* _8;
    u8 _10[0xd8 - 0x10];
    sead::Buffer<SceneSlot> mScenes;
    u8 _e8[0x1338 - 0xe8];
    // sub_7101112A74 clears bit 3 (8).
    u32 _1338;
};
class Water {
    void setUpAttributeTable();
};

// 0x710110aa5c (declaration only, 536 bytes): height query used by sub_710110B4A4.
u32 sub_710110AA5C(f32 a, f32 b, f32* out_height, const sead::Vector2f* xz, const u8* info_20,
                   const Unk_710111F504* info);
// CreateTeraSystem passes the System created at 0x71011113d4 to PlacementMgr.
// 0x710110b4a4: 0 without a scene (System+0x8) or unless Terrain flags 2 and 4 are both set.
u32 sub_710110B4A4(f32* out_height, const sead::Vector2f* xz, System* system);
// Full 110C02C writes material and submaterial; independent 1224C1C consumes both.
u32 sub_710110C02C(phys::Material* material, s32* submaterial, const sead::Vector2f* xz,
                    System* system, bool flag);
// Returns query status 0/1/2; the final argument preserves a full integer flag.
u32 sub_71011094A0(f32* out_height, const sead::Vector2f* xz, System* system, s32 index,
                    s32 flag);

// Full 110C1E4 looks up the texture name and writes its indexed 32-bit value.
// GolemRootBase 402194 consumes the unsigned output for model and XLink state.
bool sub_710110C1E4(u32* out, const sead::SafeString& name);

bool checkTeraSystemStatus();

// 0x71011190c8 (declaration only; placeholder name and signature): called by map::PlacementMapMgr::postPlaceActorsRouteStuff with
// the tera system and every route of every map.
void sub_71011190C8(void* tera_system, void* route);

}  // namespace ksys::tera

// Full native 0x7100F3F84C (28 bytes) records terrain bit indices 0..9 from
// callback 0x7101200AC0. Declaration only; terrain storage ownership stays unresolved.
void sub_7100F3F84C(u32 index);

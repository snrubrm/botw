#pragma once

#include <cstddef>
#include <cstring>
#include <prim/seadSafeString.h>

#include <basis/seadTypes.h>
#include <container/seadObjArray.h>
#include <container/seadBuffer.h>
#include <container/seadFreeList.h>
#include <container/seadSafeArray.h>
#include <math/seadBoundBox.h>
#include <math/seadVector.h>
#include <math/seadMatrix.h>
#include <thread/seadAtomic.h>
#include <heap/seadDisposer.h>
#include <thread/seadThread.h>
#include <heap/seadHeap.h>
#include <hostio/seadHostIONode.h>
#include <container/seadTreeMap.h>
#include <prim/seadBitFlag.h>
#include <filedevice/seadFileDevice.h>
#include <prim/seadXmlDocument.h>
#include <thread/seadCriticalSection.h>
#include <thread/seadReadWriteLock.h>
#include <thread/seadThread.h>
#include <common/aglGPUMemAddr.h>
#include <common/aglGPUMemBlock.h>
#include <common/aglTextureSampler.h>
#include <cull/aglViewFrustumCulling.h>
#include "KingSystem/System/DebugMessage.h"
#include "KingSystem/Terrain/teraResourceNode.h"
#include "KingSystem/Utils/Types.h"
#include <common/aglRenderBuffer.h>
#include <common/aglRenderTarget.h>
#include <common/aglTextureSampler.h>

class Unk_7102503a50;

namespace agl {
class ShaderProgram;
}

namespace gsys {
class Model;
class ModelResource;
}

namespace nn::g3d {
class ResModel;
}

namespace sead {
class FileDevice;
class Heap;
class Thread;
class ExpHeap;
}

namespace ksys::phys {
class Material;
}

namespace ksys {
class OverlayArena;
}

namespace ksys::res {
class Handle;
}

namespace ksys::tera {

// Existing terrain draw-state setter called by GearMgr teardown.
void sub_7100F418B8(void* value);

// 0x7101086ee0 maps world x/z coordinates into the 10-by-8 terrain cells.
s32 sub_710107F9C4(f32 x);
s32 sub_710107FA0C(f32 z);

// ResourceHolder 1138A2C supplies a size, name, parent and heap direction.
sead::ExpHeap* sub_7101120314(u32 size, const sead::SafeString& name, sead::Heap* parent,
                            sead::Heap::HeapDirection direction);

// TODO:
class ApertureMaps {
    void updateMap();
};
class ApertureMapsCollector;
class System;
class Unk_7101106F44;

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
        void sub_7101150A7C(const sead::Vector3f* pos, f32 radius, f32 value);
        // 0x7101150be0 (placeholder name; ExpandChemicalField::calc_ with cut grass type 3).
        bool sub_7101150BE0(const sead::Vector3f* pos, f32 radius, f32 value);
        // 0x7101150990 (placeholder name): sets or clears flag 0x4000 and releases every entry.
        void sub_7101150990(bool enabled);
        // 0x7101151a1c (placeholder name): sets bit 0 of _c.
        void sub_7101151A1C();
        // 0x7101152da0 (placeholder name): _274 of entry `index` (with the buffer's bounds fallback).
        sead::Vector3f* sub_7101152DA0(s32 index);
        void sub_7101152B3C(f32 fovy, const sead::Vector3f* position,
                               const sead::Vector3f* target);
        // 0x710114ee5c (placeholder name): sets or clears bit 5 of both objects of every entry.
        void sub_710114EE5C(bool on);

        // Shared flags read and written by 0x7101150990 and 0x710114dd4c.
        u8 _0[8];
        u32 mFlags;
        // 0x7101151a1c sets bit 0.
        u8 _c;
        u8 _d[3];
        // The two objects of a grass entry (0x710114ee5c sets bit 5 of a word at +0x50 / +0x280).
        struct EntryPart {
            u8 _0[0x50];
            u32 mFlags;
        };
        struct EntryPart2 {
            u8 _0[0x280];
            u32 mFlags;
        };
        // One 0x2c0-byte grass entry.
        struct Entry {
            EntryPart* _0;
            EntryPart2* _8;
            u8 _10[0x28 - 0x10];
            // 0x710114f978 stores the System passed by Core 0x71013019bc.
            System* mSystem;
            u8 _30[0x3c - 0x30];
            // Camera setters 0x710114f978 and 0x7101152b3c update this frustum.
            agl::cull::ViewFrustumCulling mFrustum;
            sead::Vector3f mPosition;
            u8 _280[0x28c - 0x280];
            sead::Matrix34f mCamera;
            u8 _2bc[4];
        };
        static_assert(sizeof(Entry) == 0x2c0);
        static_assert(offsetof(Entry, mFrustum) == 0x3c);
        static_assert(offsetof(Entry, mPosition) == 0x274);
        static_assert(offsetof(Entry, mCamera) == 0x28c);
        // At 0x10: size (0x10) and pointer (0x18), like sead::Buffer.
        sead::Buffer<Entry> mEntries;
        u8 _20[0x28 - 0x20];
        // 0x7101150ba4 / 0x7101150f08 query this object (0x7101069db8).
        Unk_7102503a50* _28;
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

    // Placeholder (the object at 0x140; ForestRenderer x_2 / x_3 / x_5 reach it through
    // Terrain::sub_710114DE70): flags at +0x8 (bit 2 checked by all three methods), two objects at
    // +0x14cd0 / +0x14cd8.
    class Unk_140 {
    public:
        // One 0x1a0-byte entry of the ten 8-entry tables at +0x30: 0x7101083060 stores its
        // table / entry indices and 0x710108330c hands it the heap. The per-entry bodies stay U.
        struct TableEntry {
            void init(s32 table, s32 index);
            void setup(sead::Heap* heap);
            u8 _0[0x1a0];
        };
        static_assert(sizeof(TableEntry) == 0x1a0);

        // 0x71010827dc (declared only): clears flag bit 2 and resets both sub-objects (0x7101084d04).
        void sub_71010827DC();
        // 0x7101082824 (declared only): unless flag bit 2 is set, handles a tree placed at `pos` by name.
        void sub_7101082824(const sead::SafeString& name, const sead::Vector3f& pos);
        // 0x7101083028 (declared only): calls 0x7101084e78 on both sub-objects.
        void sub_7101083028();
        // 0x7101083060 (declared only; 400 B): sets flag bit 1 unless bit 2 is set and builds the tables.
        void sub_7101083060();
        // 0x710108330c (declared only; 328 B; unnamed in the CSV): the setup ForestRenderer::x runs first.
        void sub_710108330C();
        // 0x71010832b0 (unnamed; 92 B, declared only): resolves a tree placed at `pos` (returns -1 unless
        // (_8 & 6) == 2).
        s32 sub_71010832B0(const sead::SafeString& name, const sead::Vector3f& pos,
                           const sead::Vector3f& rotate, const sead::Vector3f& scale, f32 unk);
        // 0x7101083b78 (unnamed; declaration only): updates the table entry for a changed tree record.
        void sub_7101083B78(u16 index, const sead::Vector3f& pos, bool b);

        u8 _0[8];
        u32 _8;
        // +0x28: heap passed to every table entry setup and to the two sub-objects.
        u8 _c[0x28 - 0xc];
        sead::Heap* _28;
        // Ten tables of eight entries: table 0 / 1 at +0x30 / +0xd30 (0x7101083060 / 0x710108330c).
        TableEntry mTables[10][8];
        u8 _8230[0x14cd0 - 0x8230];
        // Both are passed to 0x7101084d04 / 0x7101084e78.
        void* _14cd0;
        void* _14cd8;
    };

    u8 _0[0xf0];
    void* _f0;
    gsys::Model* _f8;
    u8 _100[0x38];
    Grass* _138;
    Unk_140* _140;
    // Getter 0x710114dd84 and setter 0x71013010d4 share this two-byte record buffer.
    sead::Buffer<Unk_71013010d4> mStates;
    sead::Buffer<Unk_7101300b4c> mPositions;
    u8 _168[0x180 - 0x168];
    // Four 0x78-byte records (0x710114deb8 indexes them as 3 * b + a).
    struct Record {
        u8 _0[0x78];
    };
    Record mRecords[4];
    static_assert(sizeof(Record) == 0x78);
    // Original 0x710130085c and 0x710130089c reset this word with exclusive-loop exchanges.
    sead::Atomic<u32> _360;
    u8 _364[0x18];
    u8 _37c;
};

// 0x71011501c8 (declaration only): Grass cleanup thunk called by world::ChemicalMgr::unload2;
// the body stays with the Grass owner.
void sub_71011501C8(Core::Grass* grass);

// 0x7101128ac0 (unnamed): maps the two 2D points `a` and `b` by the scale / offset in `transform`
// (transform[0], transform[2], transform[3]) into `out`.
void sub_7101128AC0(f32* out, const f32* a, const f32* b, const f32* transform);

// 0x7100f40780 (CSV name): points the terrain camera at `pos` (or at the patched position when the
// terrain debug flag is set). Called by GameScene::loadTera.
void terrainSetCameraLookAtPos(const sead::Vector3f* pos);

// Terrain is the CSV name of the singleton at 0x7102620698 (a sead singleton: createInstance 0x710114961c
// builds the disposer at 0x300). Its ctor 0x71011496a4 also constructs bases at 0x20 (ctor 0x710107e724) and
// The 0x28-byte layer entries of an extra info definition (0x71012ff698 creates them): a name pool
// id, the name copied from the pool and the slope parameters the terrain XML gives.
struct ExtraInfoLayerMaybe {
    s32 name_id;
    sead::SafeString name;
    f32 ratio;
    f32 scale_min;
    f32 range;
    f32 _24;
};
KSYS_CHECK_SIZE_NX150(ExtraInfoLayerMaybe, 0x28);

// One record of the name pool at Terrain::_370->_4ae8: eight unmodelled bytes (the System cleanup at
// 0x710113ecf4 reads the next record's first byte as this record's "name buffer allocated" flag) and
// the name.
struct ExtraInfoNameMaybe {
    u8 _0[8];
    sead::SafeString name;
};
KSYS_CHECK_SIZE_NX150(ExtraInfoNameMaybe, 0x18);

// The name pool itself: 512 names, the 8-byte tail that holds the last record's flag and the count.
struct ExtraInfoNamePoolMaybe {
    ExtraInfoNameMaybe names[0x200];
    u8 _3000[8];
    u32 count;

    // 0x7101140414 (placeholder name): appends `name`, returns the allocated buffer.
    char* addName(sead::Heap* heap, const sead::SafeString& name);
};

// The definition 0x7101138390 creates per extra info name and 0x710111a4dc fills; only the fields
// those functions use are modelled.
struct ExtraInfoMaybe {
    u16 id;
    u8 _2[6];
    sead::BufferedSafeString name;
    u8 _20[0x80];
    f32 width;
    f32 density;
    sead::ObjArray<ExtraInfoLayerMaybe> layers;
    u8 _c8[0x300];
    u32 flags;

    // 0x71012ff4f0 (placeholder name): adds a layer for the pool entry called `name` (id -1 when the
    // name is not in the pool).
    ExtraInfoLayerMaybe* addLayer(f32 ratio, f32 scale_min, f32 scale_max, const sead::SafeString& name);
    // 0x71012ff698 (placeholder name): creates a layer entry with pool id `name_id`.
    ExtraInfoLayerMaybe* createLayer(s32 name_id, f32 ratio, f32 scale_min, f32 scale_max);
    // 0x71012ff810 (placeholder name): the index of `layer` in `layers`, -1 if absent.
    s32 findLayerIndex(const ExtraInfoLayerMaybe* layer) const;
};

class ImageResourceMgr;

// 0x58 (vtable group 0x710250faa8); those and the remaining members are not modeled yet.
class Terrain : public sead::IDisposer {
public:
    Terrain();
    ~Terrain() override;

    void setPauseState(bool paused);
    // 0x710114d73c (CSV Terrain::__auto21; placeholder name): Core::sub_710130085C while bits 1 and 2 of _a58 are
    // set.
    void sub_710114D73C();
    // 0x7101149af0 (CSV Terrain::__auto11; placeholder name): under the image manager's lock, sets
    // (clears) bit 18 of _a58 when it differs from `on`.
    void sub_7101149AF0(bool on);
    // 0x710114deac (CSV Terrain::__auto0; placeholder name): forwards to Core::sub_7101300AAC.
    void sub_710114DEAC(bool visible);
    // 0x710114d7c8 (placeholder name): whether the calling thread is the one stored in _a40.
    bool sub_710114D7C8() const;
    // 0x710114e0cc (CSV Terrain::__auto1; placeholder name): under mImageResourceMgr's 0x28 lock,
    // clears bit 2 of its _6473.
    void clearImageResourceMgrFlagMaybe();
    // 0x710114e074 (CSV Terrain::__auto2; placeholder name): under the image manager's lock, sets bit 2
    // of its _6473 and refreshes it through sub_71011315BC.
    void startImageResourceMgrMaybe();
    // 0x710114dfac (placeholder name): clears bit 2 of the image manager's _6473 and sets / clears
    // bit 17 of _a58 while bit 16 guards re-entry; `resume` also restarts the image manager.
    void sub_710114DFAC(bool resume);
    // 0x710114d858 (CSV name): 1, or 2 when the image manager's busy counter is above `threshold`.
    s32 resourceIsLoading(u32 threshold, bool update);
    // 0x710114d7b8 (placeholder name): refreshes the image resource manager.
    bool sub_710114D7B8();
    // 0x710114deb8 (placeholder name): record 3 * b + a of Core _360.
    void* sub_710114DEB8(s32 a, s32 b);
    // 0x710114c35c (CSV Terrain::__auto3; placeholder name): stores `value` in _388[offset][index],
    // where type 0 / 1 map to offset 0 / 1 and type 3 to offset 2 / 3 (index 0 / 1).
    bool setPackModeMaybe(const ImageTypeMaybe& type, s32 index, u8 value);
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
    Core::Unk_140* sub_710114DE70();
    void sub_710114DE7C(bool value);
    bool sub_710114DE9C();
    gsys::Model* sub_710114DEE0();
    bool sub_710114DD40();
    f64 sub_710114D9E8();
    void* sub_710114DED4();
    void* sub_710114D8D0();
    // The callers (System::x_3, parseSceneXmlMaybe, sub_710111DD0C, 0x71013019bc) pass a System.
    sead::Vector2f sub_710114D8E4(const System* system);
    f32 sub_710114D8F8(const System* system);
    // 0x710114d928 (CSV Terrain::a; placeholder name): whether the image file of `area` for `type` exists
    // on _428.
    bool sub_710114D928(System* system, Unk_7101106F44* area, const ImageTypeMaybe& type);

    // Placeholders for the chain Terrain::_370->_4ae0 (0x710114de10 / 0x710114de20 / 0x710114de3c).
    struct MaterialName {
        u16 _0;
        char name[1];
    };
    struct MaterialNameTable {
        u8 _0[8];
        MaterialName** mNames;
        // Read by Water::setUpAttributeTable 0x7101144834.
        u32 mCount;
    };
    // Placeholder: pairs read by sub_710110C134 / sub_710110B7A4 (-1 when out of range); the main / sub
    // attribute of a material (setUpAttributeTable 0x7101140aa8 / 0x7101141e5c / 0x7101144834).
    struct IndexPair {
        s32 a;
        s32 b;
    };
    using AttributeMap = sead::TreeMap<sead::SafeString, s32>;
    // Placeholder: one u32 per material (read by sub_710110C1A4).
    struct MaterialValueTable {
        u8 _0[8];
        u32* mValues;
    };
    struct Unk4ae0 {
        // Placeholder: the object at 0x10 (0x710113e9fc sets it up, with the objects at 0xf98 and 0x1e80
        // (Water)). Slot 0x60 returns the material texture of an index (System::x_2 0x71011178e4 calls
        // it with 0 when _8 is set).
        class Unk_10 {
        public:
            // Declared only (never constructed here).
            virtual void m0();
            virtual void m1();
            virtual void m2();
            virtual void m3();
            virtual void m4();
            virtual void m5();
            virtual void m6();
            virtual void m7();
            virtual void m8();
            virtual void m9();
            virtual void m10();
            virtual void m11();
            virtual const MaterialTextureMaybe* m12(s32 index);

            // 0x71011406cc (declaration only; placeholder name): stores `count` in _700.
            void sub_71011406CC(u32 count);
            // 0x7101140aa8 (placeholder name): the same as Water::setUpAttributeTable for this object's
            // tables (file names _718, main _728, sub _730; result in _738).
            void setUpAttributeTableMaybe(sead::Heap* heap, const AttributeMap* main_map,
                                          const AttributeMap* sub_map);
            // 0x710114161c (placeholder name): looks up the four terrain materials of _8 and the shader
            // parameter indices _6d0 - _6e8; stores the material table _6ec - _6fc.
            void sub_710114161C();
            // 0x7101147360 / 0x7101147370 / 0x710114737c / 0x7101147388 / 0x7101147394: per-index
            // accessors (sampler, material index, shader parameter index, constant table, texture entry).
            agl::TextureSampler* getSamplerMaybe(s32 index);
            s32 getMaterialIndexMaybe(s32 index) const;
            s32 getShaderParamIndexMaybe(s32 index) const;
            s32 getConstantIndexMaybe(s32 index) const;
            struct TextureEntry {
                agl::TextureData* mTexture;
                s32 mIndex;
                u8 _c[4];
            };
            static_assert(sizeof(TextureEntry) == 0x10);
            TextureEntry* getTextureEntryMaybe(s32 index);

            nn::g3d::ResModel* _8;
            // Filled by 0x7101140d84 (texture, index of the material).
            TextureEntry _10[3];
            agl::TextureSampler _40[3];
            // Material indices of _8 (0x710114161c): OpaqueNear / OpaqueMiddle / OpaqueFar / Translucent.
            s32 _490[4];
            u8 _4a0[0x6d0 - 0x4a0];
            // Shader parameter indices (0x710114161c).
            s32 _6d0[7];
            // Constants 11 / 12 / 13 / 5 / 3 (0x710114161c).
            s32 _6ec[5];
            s32 _700;
            MaterialNameTable* mMaterialNames;
            u8 _710[0x718 - 0x710];
            // Names searched by sub_710110C1E4 (indexes _720); the file names in the attribute table log.
            MaterialNameTable* _718;
            MaterialValueTable* _720;
            MaterialNameTable* _728;
            MaterialNameTable* _730;
            sead::Buffer<IndexPair> _738;
            u8 _748[0x878 - 0x748];
            // Read by index by 0x7101123224.
            sead::Buffer<sead::Vector4f> _878;
            // Read by Unk370::sub_710113F34C.
            bool _888;
            u8 _889[0xf88 - 0x889];
        };
        // Placeholder: the object at 0xf98 (see Unk_10).
        class Unk_f98 {
        public:
            // 0x7101141e5c (placeholder name): the same as Water::setUpAttributeTable for this object's
            // tables (file names _6f8, main _708, sub _710; result in _718).
            void setUpAttributeTableMaybe(sead::Heap* heap, const AttributeMap* main_map,
                                          const AttributeMap* sub_map);
            // 0x71011474d8 / 0x71011474e8 / 0x71011474f4 / 0x7101147500 / 0x710114750c: the same
            // per-index accessors as Unk_10, with this object's offsets.
            agl::TextureSampler* getSamplerMaybe(s32 index);
            s32 getMaterialIndexMaybe(s32 index) const;
            s32 getShaderParamIndexMaybe(s32 index) const;
            s32 getConstantIndexMaybe(s32 index) const;
            struct TextureEntry {
                agl::TextureData* mTexture;
                s32 mIndex;
                u8 _c[4];
            };
            static_assert(sizeof(TextureEntry) == 0x10);
            TextureEntry* getTextureEntryMaybe(s32 index);

            u8 _0[0x10];
            TextureEntry _10[3];
            agl::TextureSampler _40[2];
            u8 _320[0x480 - 0x320];
            s32 _480[4];
            u8 _490[0x6c8 - 0x490];
            s32 _6c8[7];
            s32 _6e4[5];
            MaterialNameTable* _6f8;
            u8 _700[0x708 - 0x700];
            MaterialNameTable* _708;
            MaterialNameTable* _710;
            sead::Buffer<IndexPair> _718;
        };

        void* _0;
        u8 _8[0x10 - 0x8];
        Unk_10 _10;
        u8 _f98[0x3910 - 0xf98];
        u32 _3910;
        IndexPair* _3918;
        u8 _3920[0x3ad8 - 0x3920];
        // Read by Unk370::sub_710113F34C.
        bool _3ad8;
    };
    struct Unk370 {
        // 0x710113f34c (placeholder name): _4ae0->_10._888 and _4ae0->_3ad8.
        bool sub_710113F34C() const;

        u8 _0[0x478];
        // 0x710114cbf4 and 0x710113fdf4 select variants through ShaderProgram data.
        agl::ShaderProgram* _478;
        u8 _480[0x4ae0 - 0x480];
        Unk4ae0* _4ae0;
        // The terrain XML's name pool (read by ExtraInfoMaybe::addLayer / createLayer).
        ExtraInfoNamePoolMaybe* _4ae8;
    };
    // 0x710114de10 (CSV Terrain::__auto9) / 0x710114de3c (CSV Terrain::__auto6) / 0x710114de20 (placeholder names).
    void* sub_710114DE10() const;
    s32 sub_710114DE3C() const;
    // 0x710114d920 (placeholder name): _370->sub_710113F34C().
    bool sub_710114D920() const;
    // The name of terrain material `index` (DragonMoveTo searches it for "雪").
    const char* sub_710114DE20(s32 index) const;

    u8 _20[0x2e0 - 0x20];
    // Arenas of the image load requests of ImageResourceMgr::sub_710113400C (_2e8 for the ".stera" pack).
    OverlayArena* _2e0;
    OverlayArena* _2e8;
    u8 _2f0[0x300 - 0x2f0];
    // The disposer buffer (mSingletonDisposerBuf_) is at 0x300.
    SEAD_SINGLETON_DISPOSER(Terrain)
public:
    u8 _320[0x360 - 0x320];
    Core* _360;
    u8 _368[0x370 - 0x368];
    Unk370* _370;
    ImageResourceMgr* mImageResourceMgr;
    // Placeholder type: System::loadScene 0x710111e04c calls sub_71011382EC on it.
    struct Unk_380 {
        // Placeholder: the pooled items (only linked through the list).
        struct Item;
        // 0x71011382ec (placeholder name): returns every item of mList to mFreeList.
        void sub_71011382EC();
        // 0x7101138494 (declaration only; placeholder name): the item of mList whose name (SafeString at +0x8)
        // is `name`, or null. System::sub_71011194C4 passes the result to sub_7101118C40 as the key.
        Unk_710110d278::Key* sub_7101138494(const sead::SafeString& name);

        sead::FreeList mFreeList;
        sead::OffsetList<Item> mList;
    };
    Unk_380* _380;
    // Pack load modes by area depth (ImageResourceMgr::sub_710113400C, with bit 18 of _a58): image types 0
    // and 1, then type 3 with index 0 and 1. 1: one pack per four names, 2: per sixteen.
    u8 _388[4][0x10];
    f32 _3c8;
    // Passed by sub_710110B4A4 to sub_710110AA5C.
    f32 _3cc;
    // Image size index of the Unk_710250dc50 resources (their m9 0x710110d9b4).
    u32 _3d0;
    u8 _3d4[0x3dc - 0x3d4];
    // ApertureMapsCollector::sub_7101101964 gives the first _3dc of 19 entries level 1, the first _3dd level 2 and the
    // first _3de level 3.
    u8 _3dc;
    u8 _3dd;
    u8 _3de;
    u8 _3df[0x400 - 0x3df];
    f32 _400;
    u8 _404[0x418 - 0x404];
    // Placeholder: one render target set per core (0x710114c3c4 .. 0x710114ce48 index this buffer with
    // sead::CoreInfo::getCurrentCoreId()). Color targets 0 / 1 at 0x68 / 0x1e0, depth at 0x358, eight samplers
    // at 0x4d0; bits 0 / 1 of mColorFlags mark bound color targets (0x710114c9d0 invalidates them).
    struct RenderSet {
        agl::RenderBuffer mRenderBuffer;
        agl::RenderTargetColor mColorTargets[2];
        agl::RenderTargetDepth mDepthTarget;
        agl::TextureSampler mSamplers[8];
        u32 mColorFlags;
    };
    // 0x710114c9d0 (placeholder name): invalidates the GPU cache of the bound color targets of this core's set
    // and clears their flags.
    void sub_710114C9D0(agl::DrawContext* context);
    // 0x710114c648 (placeholder name): binds this core's render set and fast-clears its depth to 1.
    void sub_710114C648(agl::DrawContext* context);
    // 0x710114c3c4 (placeholder name): binds `texture` (mip, layer) as color target `index`
    // of this core's set. Flag bit 0 first unbinds all targets, bit 1 sets the buffer size from the texture and
    // binds it (or clears it through 0x710114c648 when bit 31 of mColorFlags is set).
    void sub_710114C3C4(agl::DrawContext* context, const agl::TextureData& texture, u32 mip, u32 layer,
                        u32 index, u32 flags);
    // 0x710114c72c (declaration only; placeholder name): the same for the depth target, with its storage.
    void sub_710114C72C(agl::DrawContext* context, const agl::TextureData& texture,
                        const agl::GPUMemVoidAddr& storage, u32 mip, u32 flags);
    // 0x710114ca64 (placeholder name): returns sampler `index` of this core's set; when bit 0 of `flags`
    // is set, first resets it (filters, wraps, LOD, selectors, border colour sead::Color4f::cBlack).
    agl::TextureSampler* sub_710114CA64(s32 index, u32 flags);
    // 0x710114ce48 (declaration only; placeholder name; x0 is not read): sets three uniforms of `program`,
    // activates `sampler` and the shared vertex attribute, then draws.
    void sub_710114CE48(agl::DrawContext* context, const agl::ShaderProgram* program,
                               const agl::TextureSampler* sampler, const sead::Vector4f* a,
                               const sead::Vector4f* b, const sead::Vector4f* c);
    struct DrawArg {
        const agl::TextureData* texture; // 00
        u32 mip;                       // 08
        u32 layer;                     // 0c
        u32 _10;
        f32 _14;
        sead::Vector4f a;               // 18
        bool bind_target;              // 28
        bool invalidate;               // 29
        u8 _2a[6];
        const agl::TextureSampler* sampler; // 30
        f32 _38;
        f32 _3c;
        sead::Vector4f c;               // 40
        sead::Vector4f b;               // 50
        u32 _60;
        u32 program_id;                // 64
    };
    static_assert(sizeof(DrawArg) == 0x68);
    u32 sub_710114CBF4(agl::DrawContext* context, const DrawArg* arg);
    sead::Buffer<RenderSet> mRenderSets;
    // Checked for image files by sub_710114D928.
    sead::FileDevice* _428;
    u8 _430[0x680 - 0x430];
    sead::Matrix44f mProjectionMatrix;
    sead::Matrix34f mViewMatrix;
    u8 _6f0[0xa40 - 0x6f0];
    // Placeholder type (zeroed by the ctor): sub_710114D7C8 compares its thread at 0x750 with the current thread.
    struct Unk_a40 {
        u8 _0[0x750];
        sead::Thread* mThread;
    };
    Unk_a40* _a40;
    f64 _a48;
    // Placeholder type: ForestRenderer::requestDraw 0x7100f03964 draws nothing when bit 5 of its byte at
    // 0x18 is set.
    struct Unk_a50 {
        u8 _0[0x18];
        // Bit 7: sub_7101115584 skips sub_7101115338.
        u8 _18;
        u8 _19[0x1d - 0x19];
        // Bit 4: passed to ApertureMapsCollector::sub_7101100F08 by sub_7101115584 (unless System::_1338 bit 1).
        u8 _1d;
        u8 _1e[0x70 - 0x1e];
        // Debug log targets. 0x71011320b4 logs to _110 when its enabled flag (_88, at 0x198) is set.
        DebugMessage _70;
        u8 _100[0x110 - 0x100];
        DebugMessage _110;
    };
    Unk_a50* _a50;
    u32 _a58;
};
KSYS_CHECK_SIZE_NX150(Terrain, 0xa60);
class Unk_7101106F44;

// Placeholder: a 2D scale and offset (0x7101128b24).
struct Unk_7101128B24Transform {
    f32 scale;
    f32 _4;
    sead::Vector2f offset;
};

// 0x7101128b24 (placeholder name): the box from `min` to `max` (x / z, scaled and offset by `transform`)
// with heights interpolated between `low` and `high` at `t_min` / `t_max`.
void sub_7101128B24(f32 low, f32 high, f32 t_min, f32 t_max, sead::BoundBox3f* box,
                    const sead::Vector2f& min, const sead::Vector2f& max,
                    const Unk_7101128B24Transform& transform);

// 0x7101123224 (placeholder name): entry `index` of Terrain::_370->_4ae0->_888 (the first one when out of
// range).
sead::Vector4f sub_7101123224(s32 index);

class ImageResourceMgr {
    // 0x7101136d7c (declaration only; 2664 B). Returns a status (2: busy, 5: idle; see sub_7101130C80).
    s32 procUnloadResidualRequest();

public:
    // Placeholder: a load / unload request for one image of an area node (defined after System).
    struct Request;
    // Placeholder: a queued load task for one image of an area node (defined after System). Filled by
    // sub_7101132FE0, queued in mList3200 / mKindLists by sub_7101133274; free tasks wait in mList31e8.
    struct LoadTask;

    // 0x7101132270 (declared only; placeholder name).
    bool sub_7101132270(Request* request);
    // 0x7101133724 (placeholder name): sets up the image of `request` from its data (unless already set
    // up), marks it in use and counts it.
    void sub_7101133724(Request* request);

    // 0x7101133af8 (placeholder name): unless the image for `type` is already requested (flag 2), takes a free
    // request from mList31e8, fills it (sub_7101132FE0), marks the image and runs sub_7101133274; returns
    // false when no request is free.
    bool sub_7101133AF8(System* system, Unk_7101106F44* area, const ImageTypeMaybe& type);
    // 0x7101132fe0 (declaration only; placeholder name).
    void sub_7101132FE0(LoadTask* task, System* system, Unk_7101106F44* area,
                        const ImageTypeMaybe& type);
    // 0x710113625c (placeholder name): under the manager lock (0x68), runs sub_7101135F34 and, with flag 2
    // of _6473, finishes the matching request of mLists19c0 (sub_7101136328 first if `a4`).
    bool sub_710113625C(System* owner, Unk_7101106F44* area, const ImageTypeMaybe& type,
                        bool a4, const sead::SafeString* a5);
    // 0x7101130c80 (CSV tera::ImageResourceMgr::a; placeholder name): one step of the loader thread with
    // flag 4 of _6473: unloads residual requests, publishes the queue size (waking the thread), and
    // sleeps 33 ms or yields; after 16 busy steps, lowers _3c of the queued kind-1 tasks by 2.
    void sub_7101130C80();
    // 0x7101130df0
    ~ImageResourceMgr();
    // 0x71011339d0 (placeholder name): releases the image of `request` if its flag 8 is set.
    void sub_71011339D0(Request* request);
    // 0x71011311bc (placeholder name): under both locks, runs sub_7101131290 and sub_71011320B4 on every
    // request of _31c0, then publishes the queue size and wakes the loader thread if it is not zero.
    void sub_71011311BC();
    // 0x7101131290 (placeholder name): under both locks, drops the queued load tasks (Unk_7101132878) and
    // unloads every request of mLists1c0 (releasing its image first while its handle is valid).
    void sub_7101131290();
    // 0x71011320b4 (declared only; placeholder name; 444 B).
    void sub_71011320B4(Request* request);
    // 0x710113333c (declared only; placeholder name): looks for a matching queued request.
    s32 sub_710113333C(LoadTask* task, bool a3);
    // 0x7101133274 (placeholder name): queues `request` unless sub_710113333C finds a match (returns its
    // result) and wakes the loader thread if the queue was empty.
    s32 sub_7101133274(LoadTask* task);
    // 0x71011315bc (placeholder name): publishes the queue size and wakes the loader thread if it is not
    // zero.
    void sub_71011315BC();
    // 0x7101131cdc (placeholder name): registers `system` in the slot given by the low three bits of its
    // _1334 (false if taken).
    bool sub_7101131CDC(System* system);
    // 0x71011334b4 (placeholder name): moves the kind-1 requests to the front of the queue.
    void sub_71011334B4();
    // 0x71011355e8 (declared only; placeholder name).
    void sub_71011355E8(LoadTask* task);
    // 0x7101131d68 (placeholder name): moves every request of mList4a18 to mList31e8 (running
    // sub_71011355E8 on kind 0); false if there was none.
    bool sub_7101131D68();
    // 0x7101131fd0 (placeholder name): takes `request` out of mList31c0 / mLists19c0 if it is linked and
    // queues it in mLists1c0.
    void sub_7101131FD0(Request* request);
    // 0x7101131e7c (placeholder name; `this` unused): the request in `lists` for (`a2`, `area`, `type`), or null (also when
    // the area does not have that image).
    Request* sub_7101131E7C(sead::OffsetList<Request>* lists, void* a2, Unk_7101106F44* area,
                            const ImageTypeMaybe& type);
    // 0x7101136328 (placeholder name): with flag 1 of _6473, dumps the data of a valid request whose image
    // has flag 0x20 to "<dir>/<name>" (`name`, or the image's own file name under the system's
    // directory), then moves the image from flag 0x20 to 0x40; logs the save.
    void sub_7101136328(Request* request, const sead::SafeString* name);
    // 0x7101132548 (placeholder name; 816 bytes): the copy half of the load.
    bool sub_7101132548(Request* request);
    // 0x71011369d0 (placeholder name): allocates from mHeap, unloading the requests of mList31c0 until it
    // succeeds; on failure (or once _626c is set) logs the size, counts the failure in _626c and returns
    // null.
    void* sub_71011369D0(u32 size, s32 alignment);
    // 0x7101135aa0 (placeholder name): if the image for `type` is requested (flag 2), marks it unused and
    // queues a kind-1 (unload) task for it; 0 if no task is free or the image is still referenced.
    s32 sub_7101135AA0(System* system, Unk_7101106F44* area, const ImageTypeMaybe& type);
    // 0x7101135f34 (placeholder name): under the manager lock, clears the image's pending state for `type`
    // (sub_710110DD20(false), flag 2), queues a kind-1 load task for it (sub_710113333C) and hands it to
    // sub_7101136188.
    void sub_7101135F34(System* owner, Unk_7101106F44* area, const ImageTypeMaybe& type);
    // Placeholder: holds only the manager (x0 of 0x7101132878 is loaded as a pointer to it); probably a
    // lambda closure in teraImageResourceMgrStuff 0x710113400c.
    struct Unk_7101132878 {
        // 0x7101132878 (placeholder name): with `load`, drops the queued kind-0 tasks (kind 2 and stale
        // ones directly) after clearing their image's flag 2 and updating their system; with `unload`, the
        // same for kind 1 / 3, setting flag 2 and waiting for the image (sub_71011077C8) instead. Dropped
        // tasks leave `queue` and `kind_lists` and go back to mList31e8.
        void sub_7101132878(sead::OffsetList<LoadTask>* queue, sead::OffsetList<LoadTask>* kind_lists,
                            bool load, bool unload);

        ImageResourceMgr* mgr;
    };

    // Placeholder: like Unk_7101132878, a closure over the manager in 0x710113400c.
    struct Unk_7101136B40 {
        // 0x7101136b40 (placeholder name): if the request's handle is stale, unloads it (sub_7101133588,
        // then sub_71011320B4 with flag 2 of _6473) and returns 8; otherwise gives it a GPU address in
        // mMemBlock6328 (if it has none), sets up its image (sub_7101133724) and returns `result`.
        s32 sub_7101136B40(s32 result, Request* request);

        ImageResourceMgr* mgr;
    };

    // Placeholder: a closure over the manager in 0x710113400c (with a flag it clears).
    struct Unk_7101136C10 {
        // 0x7101136c10 (placeholder name): waits for `handle` in 30 ms steps (sleeping 3.3 ms between
        // tries) while flag 4 of _6473 is set and `task` (if any) is still valid. Clears _8 when the flag
        // goes away; false if it stopped waiting.
        bool sub_7101136C10(res::Handle* handle, LoadTask* task);

        ImageResourceMgr* mgr;
        bool _8;
    };

    // 0x7101136188 (placeholder name): under the manager lock, finds the request in mLists1c0 matching
    // `task`, releases its image when its handle is still valid and runs sub_7101133588 on it. Returns 8
    // if the task's handle is stale, 3 if no request matches, 1 otherwise.
    s32 sub_7101136188(LoadTask* task);
    // 0x710113400c (CSV teraImageResourceMgrStuff; declaration only; placeholder name; 5596 bytes): runs a
    // kind-0 (load) task; procUnloadResidualRequest switches on its result (1 - 17).
    s32 sub_710113400C(LoadTask* task);
    // 0x7101133588 (declared only; placeholder name).
    void sub_7101133588(Request* request);
    // 0x7101136950 (placeholder name): sub_7101136328 and sub_71011320B4 on every request of mList31c0.
    void sub_7101136950();
    // 0x7101131d64 (placeholder name): branch to sub_7101131D68.
    bool sub_7101131D64();
    // 0x7101130fbc (placeholder name): writes "<dir>/<file name>" for the image of `area` for `type` to
    // `out`; dir is system->_1050, or mBaseDir when the image has flag 0x40 and flag 1 of _6473 is set
    // (then returns true).
    bool sub_7101130FBC(sead::BufferedSafeString* out, System* system, Unk_7101106F44* area,
                        const ImageTypeMaybe& type);
    // 0x7101130e44 (placeholder name): writes "<dir>/<name>" to `out` (with mBaseDir as the directory if
    // `use_base_dir` and flag 1 of _6473); true if mBaseDir was used.
    bool sub_7101130E44(sead::BufferedSafeString* out, const sead::SafeString& dir,
                        const sead::SafeString& name, bool use_base_dir);

    u8 _0[0x8];
    // Compared with mHeap before freeing a request's data (0x710113400c).
    sead::Heap* _8;
    u8 _10[0x18 - 0x10];
    // Requests are allocated from it with tryAlloc (slot 0x30, 0x71011369d0) and freed with free
    // (slot 0x38, 0x71011320b4): sead::Heap's slots.
    sead::Heap* mHeap;
    // 0x710113400c keeps a loaded request only while this is still the mHeap it saw before loading.
    sead::Heap* _20;
    sead::CriticalSection mCS28;
    sead::CriticalSection mCS68;
    // Directory used instead of the given one when flag 1 of _6473 is set (0x7101130e44); the real
    // string type (a FixedSafeString?) is not known.
    sead::SafeString mBaseDir;
    u8 _b8[0x1c0 - 0xb8];
    // Indexed by Request::_50.
    sead::OffsetList<Request> mLists1c0[0x100];
    sead::OffsetList<Request> mLists19c0[0x100];
    sead::OffsetList<Request> mList31c0;
    u8 _31d8[0x31e8 - 0x31d8];
    sead::OffsetList<LoadTask> mList31e8;
    // Pending requests (insertion order depends on the request kind); its size is published in _62a0.
    sead::OffsetList<LoadTask> mList3200;
    // Indexed by the low byte of LoadTask::_24.
    sead::OffsetList<LoadTask> mKindLists[0x100];
    sead::OffsetList<LoadTask> mList4a18;
    // Indexed like mKindLists (0x7101131d68).
    sead::OffsetList<LoadTask> mKindLists2[0x100];
    // Destroyed by 0x7101130df0.
    agl::GPUMemBlock<u8> mMemBlock6230;
    u8 _6268[0x626c - 0x6268];
    // Cleared by 0x7101133588.
    u32 _626c;
    s32 _6270;
    u8 _6274[0x6298 - 0x6274];
    sead::Thread* mThread;
    sead::Atomic<s32> _62a0;
    u8 _62a4[0x62a8 - 0x62a4];
    // Storage for the requests' resource handles (0x710113400c allocates, 0x7101133588 frees).
    sead::FreeList mHandleFreeList;
    u8 _62b8[0x62d8 - 0x62b8];
    System* mSystems[8];
    // CPU address of mMemBlock6328's buffer (0x7101136b40 turns request addresses into block offsets).
    u64 _6318;
    u64 _6320;
    agl::GPUMemBlock<u8> mMemBlock6328;
    u8 _6360[0x6470 - 0x6360];
    // Key passed to Unk_71012eb6e8::set / isValid for the tasks and requests (0x7101132fe0, 0x7101136188).
    u16 _6470;
    // Busy step counter of sub_7101130C80.
    u8 _6472;
    // Bit 0: use mBaseDir; bit 3: mMemBlock6328 has a buffer.
    u8 _6473;
};
class ResourceHolder;

// The objects System keeps in its 0x90-byte scene slots (name from the CSV row at 0x7101111650).
// Placeholder (0x7101102b58; callers 0x71011027a8, 0x71011041a4 and four more): a layered texture whose
// frames are slices of one GPU buffer; keeps a sampler bound to the current layer / frame.
// The type is Unk_7101108AE8Flags (teraResourceNode.h): the record at 0x20 has the same layout.
using Unk_7101102B58 = Unk_7101108AE8Flags;
static_assert(offsetof(Unk_7101102B58, _2c0) == 0x2c0);
static_assert(offsetof(Unk_7101102B58, _430) == 0x430);
static_assert(offsetof(Unk_7101102B58, table) == 0x438);

// Placeholder: a self-relative offset in the "TSCB" scene file (null when 0; 0x710111dd0c).
template <typename T>
struct SceneOffsetMaybe {
    T* get() const {
        return offset != 0 ? static_cast<T*>(sead::PtrUtil::addOffset(this, offset)) : nullptr;
    }
    s32 offset;
};

// Placeholder: the "TSCB" binary scene read by System::sub_710111DD0C (version 10.0). From _10 on, the
// words are byte-swapped in place unless `swapped` is 1.
struct SceneBinaryMaybe {
    // Copied into System::_e8.
    struct Material {
        u32 value;
        f32 _4;
        f32 _8;
        f32 _c;
        f32 _10;
    };
    struct Area {
        sead::Vector2f pos;
        f32 size;
    };

    char magic[4];
    u8 version_major;
    u8 version_minor;
    u8 _6[2];
    u32 swapped;
    // Bytes from _10 to swap.
    u32 swap_size;
    // Terrain::_3c8 / _3cc.
    f32 _10;
    f32 _14;
    u32 num_materials;
    u32 num_areas;
    // System::_10 / _18.
    sead::Vector2f _20;
    f32 _28;
    SceneOffsetMaybe<SceneOffsetMaybe<Material>> materials;
    SceneOffsetMaybe<SceneOffsetMaybe<Area>> areas;
};

// Placeholder: 0x1a0-byte elements of a buffer at 0x158 of 0x71013019bc's third argument, passed to
// System::sub_7101115584 (the object at _0 and the flag at 0x198 are read there).
struct Unk_7101115584Arg {
    // Passed to sub_7101115338, which tests area boxes with ViewFrustumCulling::isInside 0x7100c7dcd0.
    const agl::cull::ViewFrustumCulling* _0;
    u8 _8[0x14 - 0x8];
    // Its x / z select the area node marked by System::sub_7101115674.
    sead::Vector3f _14;
    u8 _20[0x198 - 0x20];
    bool _198;
    u8 _199[0x1a0 - 0x199];
};

// Only the name is known ("[tera::Scene::exportFileBinary]"; no code in the tera range uses the string).
class Scene {
    void exportFileBinary();
};

// The objects in System's 0x90-byte slots (SceneSlot). Named from the asserts of 0x71010ffee0 /
// 0x71011000b0 ("[ksys::tera::ApertureMapsCollector::allocateImage]" / "releaseImage"), whose `this` has
// this layout (nine records at 0, flags _2998), and from System::allocateApertureMapsCollectorImage
// 0x71011128c4 (upstream name of the call in OverlayArenaSystem), which calls 0x71010ffee0 on each slot's
// object. Called Scene in this repo until session 104.
class ApertureMapsCollector {
public:
    // 0x71010ffee0: unless already allocated (flag 2; logs a double allocation), allocates the image
    // memory of the nine records from `heap` and sets flags 2 and 0xff00. The heap's getFreeSize() is called
    // before and after each record and the result dropped (discarded calls in the original).
    bool allocateImage(sead::Heap* heap);
    // 0x71011000b0: unless not allocated (logs a double release), clears flag 2 and releases the nine
    // records' memory (freeing the GPU blocks if `free_memory`).
    bool releaseImage(bool free_memory);
    // 0x710110028c (declaration only; placeholder name): range checks under Terrain::_a50 debug flags.
    void sub_710110028C();
    // 0x7101100f08 (declaration only; placeholder name and signature; 1648 bytes).
    void sub_7101100F08(System* system, Unk_7101115584Arg* arg, bool flag);
    // Placeholder type: passed by sub_710110234C to sub_71011021E4 (0x7101100330 reads _0 and _8).
    struct Unk_276c {
        u32 _0;
        u32 _4;
        u32 _8;
        u8 _c[0x14 - 0xc];
    };

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
    // 0x710110234c (placeholder name): sub_71011021E4 with _276c and true.
    void sub_710110234C(System* system);
    // 0x71011021e4 (placeholder name): with `request_all`, sub_7101101578 for all four image types (inlined),
    // then sub_7101100330.
    void sub_71011021E4(System* system, const Unk_276c* arg, bool request_all);
    // 0x7101100330 (declaration only; placeholder name and signature).
    void sub_7101100330(System* system, const Unk_276c* arg, bool a, bool b);
    // Placeholder: an image type with its two request flags (sub_7101101578 builds four).
    struct Unk_7101101DFC {
        ImageTypeMaybe type;
        u32 flag_a;
        u32 flag_b;
    };
    // 0x7101101578 (placeholder name): under _2950, calls sub_7101101DFC for each of the four image types
    // (0, 1, grass, water) whose flags are in `flags` (System::x passes 0xff0000).
    void sub_7101101578(System* system, u32 flags);
    // 0x7101101dfc (declaration only; placeholder name and signature): picks the per-type data
    // (0x15e0 / 0x8c0 / 0xd20 / 0x1180) by entry.type.
    void sub_7101101DFC(System* system, const Unk_7101101DFC& entry, s32 a3, bool a, bool b);
    // 0x71010ffe70 (placeholder name): when (a, b) differ from _2780 / _2784, stores them,
    // rebuilds through _2948 and sets flags 0xff00.
    void sub_71010FFE70(s32 a, s32 b);
    // 0x71011016f4 (placeholder name): forwards the level _2942 to _2948.
    void sub_71011016F4();
    // 0x7101100260 (placeholder name): stores the four values as u16 into the sub-objects of
    // stride 0x460 (+0x1c).
    void sub_7101100260(s32 a, s32 b, s32 c, s32 d);
    // 0x71011020c0 (placeholder name): whether records 5 - 8 have no area below `level` that is not
    // loaded yet (Unk_71010FEDBC::areAreasReadyMaybe).
    bool sub_71011020C0(u32 level) const;

    // [5] is returned by System::sub_710111F4F0, [8] by System::sub_710111F504.
    Unk_71010FEDBC _0[9];
    // Set on every scene by System::sub_7101112C30.
    sead::Vector3f _2760;
    Unk_276c _276c;
    s32 _2780;
    s32 _2784;
    u8 _2788[0x278c - 0x2788];
    s32 _278c[19];
    u8 _27d8[0x2910 - 0x27d8];
    sead::Buffer<void*> _2910;
    // Element types unknown (pointer-sized).
    sead::Buffer<void*> _2920;
    sead::Buffer<void*> _2930;
    u8 _2940;
    u8 _2941;
    s8 _2942;
    // Set (at least 0) by System::sub_71011126C4.
    u8 _2943;
    u8 _2944[0x2946 - 0x2944];
    s8 _2946;
    u8 _2947[0x2948 - 0x2947];
    // Placeholder type: System::sub_710111F644 writes its _afc0.
    struct Unk_2948 {
        // 0x710112727c (placeholder name): called by sub_71010FFE70 with the first four records and two
        // level offsets; sizes _1310 / _6070 from the texel counts (_20._e) shifted by the levels.
        void sub_710112727C(Unk_71010FEDBC* a, Unk_71010FEDBC* b, Unk_71010FEDBC* c, Unk_71010FEDBC* d, s32 x,
                            s32 y);

        // 0x7101128ba0 (declaration only; placeholder name)
        void sub_7101128BA0(s32 level);

        // Placeholder: two of these at 0x1310 / 0x6070, sized by 0x710112727c.
        struct Unk_1310 {
            // 0x7101127304 (declaration only; placeholder name).
            void sub_7101127304(u32 size);

            u8 _0[0x6070 - 0x1310];
        };

        u8 _0[0x8];
        // Set by sub_710112727C: four records and the record after the fourth.
        Unk_71010FEDBC* _8;
        Unk_71010FEDBC* _10;
        Unk_71010FEDBC* _18;
        Unk_71010FEDBC* _20;
        Unk_71010FEDBC* _28;
        u8 _30[0x38 - 0x30];
        u32 _38;
        u32 _3c;
        u32 _40;
        u8 _44[0x1310 - 0x44];
        Unk_1310 _1310;
        Unk_1310 _6070;
        u8 _add0[0xafc0 - 0xadd0];
        void* _afc0;
    };
    Unk_2948* _2948;
    // Locked by sub_7101101578.
    sead::CriticalSection _2950;
    u8 _2950_end[0x2998 - 0x2950 - sizeof(sead::CriticalSection)];
    // Flags: 4 set when the levels change, 8 read by System::sub_710111F618.
    u32 _2998;
};

// Placeholder: the listener System::sub_7101112C94 notifies (slot 0, event 5) before an area node is
// destroyed (passed through from System::x 0x7101112714).
class Unk_7101112C94Listener {
public:
    virtual void m0(Unk_7101106F44* area, s32 event) = 0;
};

class System {
public:
    static System* instance();
    // 0x710111f504: `*_e0 + 0x2300`.
    Unk_71010FEDBC* sub_710111F504();
    // 0x710111f4f0 (placeholder name): `*_e0 + 0x15e0`.
    Unk_71010FEDBC* sub_710111F4F0();
    // 0x710111f644 (placeholder name): stores `value` in _2948->_afc0 of every scene.
    void sub_710111F644(void* value);
    // 0x710111f518 (placeholder name): sub_71011001D4(level, type) on every scene.
    void sub_710111F518(int level, int type);
    // 0x710111f598 (placeholder name): ApertureMapsCollector::sub_7101100234(a, b) on every scene.
    void sub_710111F598(bool a, bool b);
    // 0x71011126c4 (placeholder name): stores `value` (at least 0) in _2943 of every scene.
    void sub_71011126C4(s32 value);
    // 0x71011129cc (placeholder name): unless bit 3 of _1338 is set (and not `force`), passes `levels` to
    // every scene; `force` then sets bit 3.
    void sub_71011129CC(const sead::SafeArray<s32, 19>& levels, bool force);
    // 0x7101112a74 (placeholder name): sub_7101101964 on every scene, then clears bit 3 of _1338.
    void sub_7101112A74();
    // 0x7101112af0 / 0x7101112b80 (placeholder names): ApertureMapsCollector::sub_71010FFE70 / sub_7101100260 on every scene.
    void sub_7101112AF0(s32 a, s32 b);
    void sub_7101112B80(s32 a, s32 b, s32 c, s32 d);
    // 0x7101112c30 (placeholder name): stores `vec` in every scene (_2760) and sets its flag 4.
    void sub_7101112C30(const sead::Vector3f& vec);
    // 0x7101112c94 (placeholder name): destroys `area` and its subtree (children first): waits until its
    // images are unused, tells `listener`, releases its images from the image resource manager and deletes it.
    void sub_7101112C94(Unk_7101106F44* area, Unk_7101112C94Listener* listener);
    // 0x7101115158 (placeholder name): with a current area node: if `update`, runs ApertureMapsCollector::sub_710110234C
    // on every scene under the write lock, sets flag 0x10000 and runs sub_7101115BAC; otherwise only sets
    // flags 0x10002.
    void sub_7101115158(bool update);
    // 0x7101115bac (declaration only; placeholder name).
    void sub_7101115BAC();
    // 0x7101119278 (CSV ksys::tera::System::x_0; placeholder name): sets the image directory _1050 from
    // `path` (copied, or through sub_7101123258 with '/' when `split`), _1168 to its last component, and
    // bit 31 of _1338 if it contains ':'.
    void sub_7101119278(const sead::SafeString& path, bool split);
    // 0x7101117048 (placeholder name): under the write lock, runs ApertureMapsCollector::sub_71011021E4 on scene `index`
    // and then sub_7101115BAC (only with Terrain flags 2 and 4).
    void sub_7101117048(s32 index, const ApertureMapsCollector::Unk_276c* arg, bool request_all);
    // 0x71011170f4 (CSV TeraSystem::x; placeholder name): ApertureMapsCollector::sub_71011020C0 of scene `index` (true
    // unless Terrain flags 2 and 4 are set).
    bool sub_71011170F4(s32 index, u32 level);
    // 0x710111713c (CSV TeraSystem::x_1; placeholder name): ApertureMapsCollector::_276c of scene `index`.
    ApertureMapsCollector::Unk_276c* sub_710111713C(s32 index);
    // 0x7101117874 (CSV eui::BoxCursorNode::clearRouteAll is a wrong owner): clears the terrain images
    // of every scene through ApertureMapsCollector::sub_7101101578(this, 0xff0000).
    void sub_7101117874();
    // 0x71011178e4 (CSV name; the debug message calls it Scene::setMaterialUVWInfo): sets each material's
    // value and scale (the first material texture's width times the larger of _4 / _8).
    void x_2();
    // 0x7101112714 (CSV System::x; placeholder name): under the write lock, resets every scene, removes
    // the image users of the flagged _fa8 nodes, destroys the area tree (telling `listener`) and clears
    // the image change ring.
    void sub_7101112714(Unk_7101112C94Listener* listener);
    // 0x71011188e4 (placeholder name): `_2946 - 1 - _2780` of the first scene, at least 0.
    s32 sub_71011188E4() const;
    // 0x71011171ac (placeholder name): bit 1 of the collector flags of scene `index`.
    bool sub_71011171AC(s32 index);
    // 0x71011188cc (placeholder name): orders area nodes by mId (x_3 0x7101114cc8 sorts _1018 with it
    // through 0x71011200e8).
    static s32 sub_71011188CC(const Unk_7101106F44* a, const Unk_7101106F44* b);
    // 0x71011128c4: ApertureMapsCollector::allocateImage on every slot (OverlayArenaSystem calls it with
    // the TeraWork heap).
    void allocateApertureMapsCollectorImage(sead::Heap* heap);
    // 0x7101112948 (name by analogy with allocateApertureMapsCollectorImage): releaseImage on every slot
    // (called by OverlayArenaSystem 0x7100fdf1e0).
    void releaseApertureMapsCollectorImage(bool free_memory);
    // 0x710111e04c: under the write lock, resets the scenes, sets the image directory from `dir` and
    // parses the scene XML; unless `keep_flags`, flags the images no node can provide (pre-order walk
    // 4). Then x_2 (unless Terrain flag 1) and x_3. Signature from the callees: `heap` is passed to
    // parseSceneXmlMaybe and on to 0x7101140414 (operator new[]), `doc`'s root (+0x8) is the XML element.
    bool loadScene(sead::Heap* heap, const sead::XmlDocument* doc, const sead::SafeString& dir,
                   bool keep_flags);
    // 0x710111ab00 (declaration only; CSV name): reads the scene element (named "scene").
    bool parseSceneXmlMaybe(sead::Heap* heap, sead::XmlElement* element);
    // 0x7101114cc8 (declaration only; CSV name).
    void x_3();
    // 0x7101114ba8 (placeholder name): under the read lock, refreshes the scaled bounds (_1c / _24), clears
    // every slot's _88, runs x_3 once if bit 0 of _1338 is set (clearing it), then sub_710110028C on every
    // scene, and clears the node flags _1008.
    void sub_7101114BA8();
    // 0x710111a2b8 (placeholder name): creates the root area node from the "scale" / "x" / "y" attributes of
    // `element` (setting _10 / _18 / _1c / _24), then a node for each child element (read by
    // sub_71011194C4). True if one of the children failed.
    bool sub_710111A2B8(sead::Heap* heap, const sead::XmlElement* element);
    // 0x71011194c4 (declaration only; placeholder name; 3572 bytes): reads area `node` from `element`.
    bool sub_71011194C4(sead::Heap* heap, Unk_7101106F44* node, const sead::XmlElement* element);
    // 0x710111b16c (placeholder name): whether the scene version "<major>.<minor>" is 10.0 or 9.1; logs
    // a major / minor version mismatch otherwise. Called by parseSceneXmlMaybe (`this` is not used).
    bool sub_710111B16C(const sead::SafeString& version);
    // 0x7101115584 (placeholder name): under the read lock, marks scene `index` (_88) and runs its
    // sub_7101100F08 with `arg`, then sub_7101115338 (if arg->_198 and the debug bit allows) and
    // sub_7101115674.
    void sub_7101115584(s32 index, Unk_7101115584Arg* arg);
    // 0x7101115338 (placeholder name): sets bit 0 of _1008 for `area` and, recursively, its children
    // whose boxes are inside `culling`.
    void sub_7101115338(const agl::cull::ViewFrustumCulling* culling, Unk_7101106F44* area,
                        const sead::Vector2f& center, f32 size);
    // 0x7101115674 (placeholder name): sets bit 1 of _1008 for the deepest node at the x / z of
    // arg->_14 and all its parents (sub_7101115218 inlined with 0xffff levels).
    void sub_7101115674(Unk_7101115584Arg* arg);
    // 0x710111e960 (placeholder name): loadScene for a binary scene ("TSCB", parsed by sub_710111DD0C).
    // `size` (x3) is not used.
    bool sub_710111E960(sead::Heap* heap, SceneBinaryMaybe* data, size_t size, const sead::SafeString& dir,
                        bool keep_flags);
    // 0x710111dd0c (placeholder name): reads a "TSCB" binary scene (version 10.0; byte-swapped in place
    // unless already done): terrain scales, the material table (into _e8) and the area nodes.
    bool sub_710111DD0C(sead::Heap* heap, SceneBinaryMaybe* data);
    // 0x7101117a08 (declaration only; placeholder name and signature; 3336 bytes): the area node of
    // `size` at `pos` (created on `heap`).
    Unk_7101106F44* sub_7101117A08(f32 size, sead::Heap* heap, const sead::Vector2f* pos, u32 a4,
                                   void* a5);
    // 0x710111dab8 (declaration only; placeholder name and signature): sets up `node` from `area`.
    void sub_710111DAB8(sead::Heap* heap, Unk_7101106F44* node, const SceneBinaryMaybe::Area* area);
    // 0x710111f618 (CSV TeraSystem::x_0): bit 3 of the flags of the `index`th scene (the first if out of range)
    bool sub_710111F618(s32 index);

    // Renamed from the placeholder System (lane1 s101): the owner of the image change ring at
    // 0x1038; ImageResourceMgr::sub_710113625C and the System method 0x7101112c94 take it as the System,
    // and its slot bits (_1334) index ImageResourceMgr::mSystems.
    // Placeholder: an image change queued by sub_71011171D8 / sub_710111731C.
    struct Entry {
        // The first word is the free-list link while the entry sits in Unk_7101088B24's pool
        // (0x71010887cc chains the entries through it).
        union {
            Unk_7101106F44* area;
            Entry* nextFree;
        };
        ImageTypeMaybe type;
    };

    // inline-only in the original; name is a guess. The same ring buffer push is inlined into
    // 0x71011171d8 and 0x710111731c.
    void pushEntryMaybe(Unk_7101106F44* area, const ImageTypeMaybe& type) {
        const u32 index = mWriteIndex.increment();
        mEntries[s32(index % mNumEntries)] = {area, type};
    }

    // 0x7101118b34 (placeholder name): makes sure `area` and its parents have a type-2 node for `key`
    // (creating missing ones); with `check`, an existing node only counts if Terrain flag 0x400 is
    // clear or its image has flag 1, and new nodes get flag 1.
    bool sub_7101118B34(sead::Heap* heap, Unk_7101106F44* area, Unk_710110d278::Key* key, bool check);
    // 0x71011176bc (placeholder name): runs sub_71011171D8 (or sub_710111731C if `flag` is false) on
    // every image of `area`.
    void sub_71011176BC(Unk_7101106F44* area, bool flag);
    // 0x7101118908 (placeholder name): when the node with key `id` here and in all four children has a B
    // value above epsilon, hands the type-2 image to the image resource manager and rebuilds the node.
    void sub_7101118908(Unk_7101106F44* area, u16 id);
    // 0x7101118c40 (placeholder name): makes sure `area` has a type-2 node for `key` with image size
    // `size`, creating parents' nodes first and splitting the image to the children when they cannot all
    // provide it. True if the node is ready.
    bool sub_7101118C40(sead::Heap* heap, Unk_7101106F44* area, Unk_710110d278::Key* key, u32 size,
                        bool check, f32 value);
    // 0x7101118fc0 (placeholder name): makes sure `area` (and its parents first) has the type-3 image
    // `index`; a new image gets flag 1 with `check`, and `listener` is told (event 3). With `check` and
    // Terrain flag 0x400, an existing image counts only with flag 1.
    bool sub_7101118FC0(sead::Heap* heap, Unk_7101106F44* area, u32 index, bool check,
                        Unk_7101112C94Listener* listener);
    // 0x71011171d8 / 0x710111731c (placeholder names): add / remove a user of the image for `type`; the
    // first user / the last one queues the image.
    void sub_71011171D8(Unk_7101106F44* area, const ImageTypeMaybe& type);
    void sub_710111731C(Unk_7101106F44* area, const ImageTypeMaybe& type);

    // Placeholder: the context loadScene 0x710111e04c and 0x710111e960 pass (as a member-function
    // delegate) to the area tree walk 0x7101107db0.
    struct Unk_710111E168 {
        // 0x710111e168 (placeholder name): flags (0x40) every image of `area` that the node or its
        // children cannot provide or whose file is missing. Always returns 0 (keep walking).
        s32 sub_710111E168(Unk_7101106F44* area);

        System* system;
        bool no_child;
    };

    // 0x90-byte entries; only the scene pointer at +0 is known.
    struct SceneSlot {
        ApertureMapsCollector* collector;
        u8 _8[0x88 - 0x8];
        // Set by sub_7101115584.
        bool _88;
        u8 _89[0x90 - 0x89];
    };

    u8 _0[0x8];
    // 0x7101115218 (placeholder name): from the current area node, climbs to the one containing `pos` and
    // descends at most `levels` (plus the levels climbed) towards it; returns that node and writes its
    // centre and size.
    Unk_7101106F44* sub_7101115218(sead::Vector2f* out_center, f32* out_size, const sead::Vector2f& pos,
                                   u32 levels);

    // Current area node (quadtree, see teraAreaNode.h). Checked by sub_710110B4A4 (no query without it).
    Unk_7101106F44* _8;
    // Scaled by Terrain::_3c8 into _1c / _24 (Terrain::sub_710114D8E4 / sub_710114D8F8); set from the
    // scene file (sub_710111DD0C).
    sead::Vector2f _10;
    f32 _18;
    // Centre and size of _8.
    sead::Vector2f _1c;
    f32 _24;
    u8 _28[0xd8 - 0x28];
    sead::Buffer<SceneSlot> mScenes;
    // 0x7101115080 (placeholder name): the area node with id `id`: a binary search of the sorted _1018
    // when it is not empty, else a linear search of _fa8.
    Unk_7101106F44* sub_7101115080(u32 id) const;

    // Placeholder: per-material UV scale, set by x_2 0x71011178e4 (one entry per material of
    // Terrain::_370->_4ae0; the count is not known, at most 149 fit before 0xee9).
    struct MaterialUVWMaybe {
        u32 value;
        f32 _4;
        f32 _8;
        f32 _c;
        f32 _10;
        f32 scale;
    };
    MaterialUVWMaybe _e8[149];
    u8 _ee0[0xee9 - 0xee0];
    u8 _ee9;
    // Number of entries of _fa8 / _ff8 in use (sub_7101112714).
    u16 _eea;
    u8 _eec[0xef0 - 0xeec];
    // Write-locked by System::x 0x7101112714 and sub_7101115158 around scene updates.
    sead::ReadWriteLock mLock;
    u8 _ef0_end[0xfa8 - 0xef0 - sizeof(sead::ReadWriteLock)];
    // Area nodes and their flags (bit 0: sub_7101112714 removes their image users). 0x7101112714 passes
    // the elements to sub_71011176BC; 0x7101115080 and 0x71012eb70c read their mIndex / mId.
    sead::Buffer<Unk_7101106F44*> _fa8;
    u8 _fb8[0xff8 - 0xfb8];
    sead::Buffer<u8> _ff8;
    // Per-node flags by Unk_7101106F44::mIndex (bit 1 set by sub_7101115674).
    sead::Buffer<u8> _1008;
    // The area nodes sorted by mId.
    sead::Buffer<Unk_7101106F44*> _1018;
    u8 _1028[0x1038 - 0x1028];
    // Image change ring (see pushEntryMaybe).
    s32 mNumEntries;
    Entry* mEntries;
    sead::Atomic<u32> mWriteIndex;
    u32 _104c;
    // The system's image directory (ImageResourceMgr::sub_7101130FBC copies it through a virtual cstr
    // call, so it is a buffered string; its buffer is not known).
    sead::BufferedSafeString _1050;
    u8 _1068[0x1168 - 0x1068];
    // The last component of _1050 (set by sub_7101119278).
    sead::SafeString _1168;
    u8 _1178[0x1330 - 0x1178];
    // Copied into ImageResourceMgr load tasks (0x7101132fe0, 0x7101135f34).
    u32 _1330;
    // Two bytes copied together into handles (0x71012eb6e8 ldrh/strh; 0x71012eb70c compares with ldrh).
    // The init function 0x71011113d4 clears both with one strh. 0x7101112714 increments 0x1335 alone
    // with ldrb/strb, and 0x7101131cdc reads 0x1334 alone with ldrb, so these are two byte fields.
    struct Id {
        // Low three bits: slot in ImageResourceMgr::mSystems.
        u8 slot;
        u8 generation;
    };
    Id _1334;
    u8 _1336[0x1338 - 0x1336];
    // sub_7101112A74 clears bit 3 (8).
    u32 _1338;

};

// Placeholder: a handle to an area node in System::_fa8 (set by 0x71012eb6e8, checked by 0x71012eb70c; ImageResourceMgr
// keeps them at +0x40 of its requests and +0x20 of other objects).
struct Unk_71012eb6e8 {
    void set(System* system, const Unk_7101106F44* entry, u16 key);
    // Whether the handle still refers to `entry`: same key, its system is systems[slot & 7] with the same
    // id, and the entry at mIndex (or with id mId) is `entry`.
    bool isValid(System* const* systems, const Unk_7101106F44* entry, u16 key) const;

    System* mSystem;
    System::Id mSystemId;
    u16 mKey;
    u32 mId;
    s32 mIndex;
};

// Placeholder: a file written on Terrain::_428 (ImageResourceMgr::sub_7101136328 dumps image data with it).
// 0x71012ebdbc constructs it, 0x71012ebdf4 closes and destroys it.
struct Unk_71012EBDBC {
    Unk_71012EBDBC();
    ~Unk_71012EBDBC();
    // 0x71012ebe70 (placeholder name): opens `path` (mode clamped to 2); sets flag 1 on success.
    bool open(const char* path, u32 mode);
    // 0x71012ebef0 (placeholder name). sub_7101136328 passes 0 for the last two arguments (unused).
    void write(const u8* data, u32 size, u32 a3, u32 a4);

    const char* mPath = "";
    sead::FileHandle mHandle;
    // Set by ImageResourceMgr::sub_7101136328 before writing (the size, then 1, 1, 1).
    s32 _48 = 0;
    u32 _4c = 0;
    u32 _50 = 0;
    u32 _54 = 0;
    u32 mMode = 2;
    // Bit 0: open; bit 1 set by ImageResourceMgr::sub_7101136328.
    sead::BitFlag32 mFlags;
};

struct ImageResourceMgr::Request {
    // inline-only in the original; name is a guess. Clears a request placed in new memory: inlined three
    // times into 0x710113400c (loaded resource, read file, zeroed buffer).
    void initMaybe() {
        std::memset(this, 0, offsetof(Request, type));
        _54 = 0;
        _58 = 0;
        _5c = 0;
        _60 = 0;
        _64 = 0;
        _68 = 0;
        _6c = 0;
        _70 = 0;
        _74 = 0;
        _78 = 0;
        _7c = 0;
        _80 = 0;
        addr = nullptr;
        _90 = nullptr;
        type.raw = 0xff;
        _4c &= ~0x1f;
        _50 = -1;
    }

    u8 _0[0x10];
    // Link in mList31c0.
    sead::ListNode mNode10;
    // Checked with isValid against mSystems / _6470 (0x7101131290, 0x7101136188).
    Unk_71012eb6e8 _20;
    // The owning System (0x7101136328 reads its directory _1050).
    System* _38;
    Unk_7101106F44* area;
    ImageTypeMaybe type;
    // Bit 0: queued in mLists1c0; bit 1: in mList31c0; bit 2: the data is ready (passed to the image
    // set-up); bit 3: set up.
    u8 _4c;
    u8 _4d[0x50 - 0x4d];
    // Name hash of the area; the low byte indexes mLists1c0 / mLists19c0.
    u32 _50;
    // From the load task (0x710113400c): _54 = alignment (task _58), _58 / _70 = task _70, _5c = task _64,
    // _68 / _6c = task _68 / _6c, _7c / _80 = task _74 / _78.
    u32 _54;
    u32 _58;
    u32 _5c;
    // Offset of the image data from the request, inside mMemBlock6328 (0x7101136b40).
    u32 _60;
    u32 _64;
    u32 _68;
    u32 _6c;
    u32 _70;
    // Data offset from the request and the bytes dumped by sub_7101136328 (_78 - _74 + _80).
    u32 _74;
    u32 _78;
    u32 _7c;
    u32 _80;
    u8 _84[0x88 - 0x84];
    // Address of _98 once the request has one (0x7101136b40 / 0x7101132548 create it in place).
    agl::GPUMemAddrBase* addr;
    // Resource handle taken from ImageResourceMgr::mHandleFreeList (0x710113400c); destroyed and returned
    // there by 0x7101133588.
    res::Handle* _90;
    // GPU address of the image data; `addr` points here once set (0x7101136b40). The original
    // constructs a GPUMemAddrBase here (the ctor at 0x7101132548 writes the three words in place).
    agl::GPUMemAddrBase _98;
    agl::TextureSampler sampler;
};

// Layout from 0x7101132fe0 (fills it), 0x710113333c (compares _24 / _28 / _30 / _38 and checks _40) and
// 0x7101135f34 (builds one on the stack: 0x88 bytes).
struct ImageResourceMgr::LoadTask {
    // Two list links (only these are cleared in the stack task of 0x7101135f34).
    sead::ListNode mNode0;
    sead::ListNode mNode10;
    // 1: queued at the front of mList3200.
    s32 _20;
    // Name hash of the area; the low byte indexes mKindLists.
    u32 _24;
    System* system;
    Unk_7101106F44* area;
    ImageTypeMaybe type;
    // System::_1330.
    u32 _3c;
    Unk_71012eb6e8 handle;
    u16 _58;
    u8 _5a;
    u32 _5c;
    u32 _60;
    u32 _64;
    u32 _68;
    u32 _6c;
    u32 _70;
    u32 _74;
    u32 _78;
    u32 _7c;
    // The request this task feeds (0x71011355e8).
    Request* _80;
};
class Water {
public:
    // Placeholder: the main / sub attribute of a material (-1 if not found).
    struct AttributeMaybe {
        s32 main;
        s32 sub;
    };
    using AttributeMap = sead::TreeMap<sead::SafeString, s32>;

    // 0x7101144834: looks up the main / sub attribute of every material by name in the two maps;
    // logs the materials with a missing one.
    void setUpAttributeTable(sead::Heap* heap, const AttributeMap* main_map, const AttributeMap* sub_map);

    u8 _0[0x700];
    // File names (for the debug message), main and sub attribute names of each material.
    Terrain::MaterialNameTable* _700;
    u8 _708[0x710 - 0x708];
    Terrain::MaterialNameTable* _710;
    Terrain::MaterialNameTable* _718;
    sead::Buffer<AttributeMaybe> mAttributes;
};

// 0x710110aa5c (declaration only, 536 bytes): height query used by sub_710110B4A4.
u32 sub_710110AA5C(f32 a, f32 b, f32* out_height, const sead::Vector2f* xz, const Unk_7101108AE8Flags* info_20,
                   const Unk_71010FEDBC* info);
// 0x710110adf8 (declaration only, 752 bytes; placeholder name): sub_710110AA5C that also writes the normal.
u32 sub_710110ADF8(f32 a, f32 b, f32* out_height, sead::Vector3f* out_normal, const sead::Vector2f* xz,
                   const Unk_7101108AE8Flags* info_20, const Unk_71010FEDBC* info);
// 0x710110b0e8 / 0x710110b38c (declaration only; placeholder names): queries like sub_710110AA5C that
// write a 2D value / a u32.
u32 sub_710110B0E8(f32 a, sead::Vector2f* out, const sead::Vector2f* xz, const Unk_7101108AE8Flags* info_20,
                   const Unk_71010FEDBC* info);
u32 sub_710110B38C(u32* out, const sead::Vector2f* xz, const Unk_7101108AE8Flags* info_20, const Unk_71010FEDBC* info);
// 0x710110b5bc / 0x710110b634 (placeholder names): sub_710110B0E8 (with 50) / sub_710110B38C for
// `system`, under the same conditions as sub_710110B4A4.
u32 sub_710110B5BC(sead::Vector2f* out, const sead::Vector2f* xz, System* system);
u32 sub_710110B634(u32* out, const sead::Vector2f* xz, System* system);
// CreateTeraSystem passes the System created at 0x71011113d4 to PlacementMgr.
// 0x710110b4a4: 0 without a scene (System+0x8) or unless Terrain flags 2 and 4 are both set.
u32 sub_710110B4A4(f32* out_height, const sead::Vector2f* xz, System* system);
// Placeholder: the four-byte terrain material record written by 0x710110bd78 (0x710110c02c starts it as
// {0xff, 0, 0, 0}; when _1 has its top bit set, _2 is the material index, otherwise _3).
// 0x710110bd78 stores it as one word.
union MaterialRecordMaybe {
    u32 raw;
    struct {
        u8 _0;
        s8 _1;
        u8 _2;
        u8 _3;
    };
};
// 0x710110bd78 (declaration only, 692 bytes; placeholder name): looks up the material record at `xz`.
u32 sub_710110BD78(MaterialRecordMaybe* out, const sead::Vector2f* xz, System* system, bool flag);
// Full 110C02C writes material and submaterial; independent 1224C1C consumes both.
u32 sub_710110C02C(phys::Material* material, s32* submaterial, const sead::Vector2f* xz,
                    System* system, bool flag);
// Placeholder: the argument of 0x7101108c44 (0x71011094a0 fills it from the area record's table (_20.table) and the
// area index).
struct Unk_7101108C44Arg {
    const Unk_710110AC74Table* table;
    u32 index;
    bool _c;
};
// Placeholder: the texel position 0x710110ac74 writes (indices, then the fractions).
struct TexelPosMaybe {
    u32 x;
    u32 y;
    f32 fx;
    f32 fy;
};
// 0x710110ac74 (placeholder name): the texel position of `x` / `y` (wrapped into [0, 1) after the level's
// offset) at mip `level`; with arg->_c set, sub_710110C3E8 instead.
void sub_710110AC74(f32 x, f32 y, const Unk_7101108C44Arg* arg, TexelPosMaybe* out, u32 level);
// 0x710110ba6c (placeholder name): four-byte texel of the area texel data of `arg` at mip `level`;
// like sub_710110B814 over Unk_710110AC74Table.
u32 sub_710110BA6C(f32 u, f32 v, const Unk_7101108C44Arg* arg, u32 level);
// 0x710110a130 (placeholder name): filtered bytes 1 - 3 of the area texel data of `arg` at mip
// `level`, as (x, y, z, 1).
sead::Vector4f sub_710110A130(f32 u, f32 v, const Unk_7101108C44Arg* arg, u32 level);
// 0x710110c930 (placeholder name): the bilinear 16-bit value (0 - 1, bytes 0 / 1 of each texel) at `texel`
// on mip `level`, with its x / z differences (x, y) and the value (z). Called by 0x71011091dc.
sead::Vector3f sub_710110C930(const Unk_7101108C44Arg* arg, const TexelPosMaybe* texel, u32 level);
// 0x710110c3e8 (declaration only, 1352 bytes; placeholder name).
void sub_710110C3E8(const Unk_710110AC74Table* table, TexelPosMaybe* out, s32 index, u32 level);
// 0x7101108c44 (placeholder name): the height (0 - 1, bilinear over 16-bit texels) at `pos` in the area of
// `arg` at mip `level`.
f32 sub_7101108C44(sead::Vector2f pos, const Unk_7101108C44Arg* arg, u32 level);
// 0x7101108f0c (declaration only; placeholder name; 720 bytes): the height (0 - 1) at `x` / `y` in
// the area of `arg`; the sampler of sub_71011095B8 (levels up to `height_flag`).
f32 sub_7101108F0C(f32 x, f32 y, const Unk_7101108C44Arg* arg, u32 level);
// Returns query status 0/1/2; the final argument preserves a full integer flag.
u32 sub_71011094A0(f32* out_height, const sead::Vector2f* xz, System* system, s32 index,
                    s32 flag);

// 0x71011091dc (placeholder name): height and normal query used by sub_71011096D0 (like sub_710110ADF8, at
// mip `level`).
u32 sub_71011091DC(f32 a, f32 b, f32* out_height, sead::Vector3f* out_normal, const sead::Vector2f* xz,
                   const Unk_7101108AE8Flags* info_20, const Unk_71010FEDBC* info, s32 index,
                   s32 level);
// 0x71011096d0: like sub_71011094A0, also writes the terrain normal.
u32 sub_71011096D0(f32* out_height, sead::Vector3f* out_normal, const sead::Vector2f* xz,
                   System* system, s32 index, s32 flag);
// Existing normalized terrain-image query used by Grass::sub_71011516D0.
u32 sub_7101109BD8(f32* out, const sead::Vector2f* xz, System* system, bool flag);
// 0x710110b52c: like sub_710110B4A4, also writes the terrain normal (sub_710110ADF8).
u32 sub_710110B52C(f32* out_height, sead::Vector3f* out_normal, const sead::Vector2f* xz,
                   System* system);
// 0x710110b6a4 (declaration only): like sub_710110C02C without the flag.
u32 sub_710110B6A4(phys::Material* material, s32* submaterial, const sead::Vector2f* xz,
                   System* system);

// 0x7101123258 (declaration only; placeholder name): forwards to 0x7101372840 (a path helper outside
// tera) with the flag masked to one bit.
void sub_7101123258(sead::BufferedSafeString* out, const sead::SafeString& path, char separator,
                    bool flag);
// Full 110C1E4 looks up the texture name and writes its indexed 32-bit value.
// GolemRootBase 402194 consumes the unsigned output for model and XLink state.
bool sub_710110C1E4(u32* out, const sead::SafeString& name);
// 0x710110c134 / 0x710110b7a4 (placeholder names): the pair `index` of Unk4ae0::_750 / _3918, or -1.
void sub_710110C134(s32* out_a, s32* out_b, s32 index);
void sub_710110B7A4(s32* out_a, s32* out_b, s32 index);
// 0x710110c1a4 (placeholder name): the u32 value of terrain material `index`; false if out of range.
bool sub_710110C1A4(u32* out, u32 index);

bool checkTeraSystemStatus();

// 0x7101084d04 / 0x7101084e78 / 0x7101084f6c / 0x710108515c (declaration only; placeholder
// signatures): reset / update / allocate the two sub-objects of Core::Unk_140.
void sub_7101084D04(void* object);
void sub_7101084E78(void* object);
void sub_7101084F6C(void* object);
void sub_710108515C(void* object, sead::Heap* heap);
// 0x710106bc54 / 0x71012e258c (declaration only): release the two parts of one grass entry.
void sub_710106BC54(void* entry);
void sub_71012E258C(void* object);
// 0x71012dc42c (declaration only): the object Core::Grass::_30 forwards to.
void sub_71012DC42C(void* object);

// 0x71011190c8 (declaration only; placeholder name and signature): called by map::PlacementMapMgr::postPlaceActorsRouteStuff with
// the tera system and every route of every map.
void sub_71011190C8(void* tera_system, void* route);

// Placeholder: vtable 0x710250fc48 (hostio::Node::getNodeClassType, D1 0x710114e904, D0 0x710114ea4c),
// ctor 0x710114e714 (sets _8 = 0x1e000481). Held by the renderer that calls sub_710114EA70 (0x71012dafb8).
class Unk_710250fc48 : public sead::hostio::Node {
public:
    virtual ~Unk_710250fc48();
    // 0x710114ea70: bit 0 of _8 is set and Terrain's _a50 does not have bit 3 of its byte at 0x18 set.
    bool sub_710114EA70() const;

    u32 _8;
};

// Placeholder: a terrain cell quad record; 0x71012eb7dc / 0x71012eb840 fill its corner fields.
struct CellQuadMaybe {
    u8 _0[0x18];
    f32 _18;
    f32 _1c;
    f32 _20;
    f32 _24;
    u32 _28;
    u32 _2c;
};
// 0x71012eb7dc / 0x71012eb840 (placeholder names): write the two corners of a cell quad.
void sub_71012EB7DC(CellQuadMaybe* out, const sead::Vector2f* a, const sead::Vector2f* b);
void sub_71012EB840(CellQuadMaybe* out, const sead::Vector2f* a, const sead::Vector2f* b);

// Placeholder: the objects 0x7101154fc0 and six other unnamed callers pass to sub_7101152DC0.
struct Unk_7101152DC0 {
    u8 _0[0x130];
    f32 _130;
};
// 0x7101152dc0: the larger of obj->_130 and tan(half of an angle in degrees, a TU static).
f32 sub_7101152DC0(const Unk_7101152DC0* obj);

// Placeholder: a terrain material object type whose per-index accessors sit in the block at
// 0x7101147678. Each type has the same shape: an entry array, texture samplers, a material index
// array, a shader parameter index array and a constant index array. The entries are opaque here.
struct TextureAccessorEntryMaybe {
    u8 _0[0x10];
};

// 0x7101147678
struct Unk_7101147678 {
    // Return type u8*: the 0x170-byte stride record overlaps the index array at 0x47c.
    u8* getSamplerMaybe(s32 index);
    s32 getMaterialIndexMaybe(s32 index) const;
    s32 getShaderParamIndexMaybe(s32 index) const;
    s32 getConstantIndexMaybe(s32 index) const;
    TextureAccessorEntryMaybe* getTextureEntryMaybe(s32 index);

    u8 _0[0x20];
    TextureAccessorEntryMaybe _20[1];
    u8 _30[0x410 - 0x30];
    u8 _410[0x47c - 0x410];
    s32 _47c[1];
    u8 _480[0x6ac - 0x480];
    s32 _6ac[1];
    u8 _6b0[0x6c0 - 0x6b0];
    s32 _6c0[1];
};

// 0x71011477f4
struct Unk_71011477F4 {
    agl::TextureSampler* getSamplerMaybe(s32 index);
    s32 getMaterialIndexMaybe(s32 index) const;
    s32 getShaderParamIndexMaybe(s32 index) const;
    s32 getConstantIndexMaybe(s32 index) const;
    TextureAccessorEntryMaybe* getTextureEntryMaybe(s32 index);

    u8 _0[0x50];
    TextureAccessorEntryMaybe _50[1];
    u8 _60[0x474 - 0x60];
    s32 _474[1];
    u8 _478[0x6b8 - 0x478];
    s32 _6b8[1];
    u8 _6bc[0x74c - 0x6bc];
    s32 _74c[1];
    u8 _750[0x860 - 0x750];
    agl::TextureSampler _860[1];
};

// 0x7101147970
struct Unk_7101147970 {
    agl::TextureSampler* getSamplerMaybe(s32 index);
    s32 getMaterialIndexMaybe(s32 index) const;
    s32 getShaderParamIndexMaybe(s32 index) const;
    s32 getConstantIndexMaybe(s32 index) const;
    TextureAccessorEntryMaybe* getTextureEntryMaybe(s32 index);

    u8 _0[0x80];
    TextureAccessorEntryMaybe _80[1];
    u8 _90[0xbd8 - 0x90];
    s32 _bd8[1];
    u8 _bdc[0xc60 - 0xbdc];
    agl::TextureSampler _c60[1];
    u8 _dd0[0x1118 - 0xdd0];
    s32 _1118[1];
    u8 _111c[0x126c - 0x111c];
    s32 _126c[1];
};

// 0x7101147b38 (no sampler accessor)
struct Unk_7101147B38 {
    s32 getMaterialIndexMaybe(s32 index) const;
    s32 getShaderParamIndexMaybe(s32 index) const;
    s32 getConstantIndexMaybe(s32 index) const;
    TextureAccessorEntryMaybe* getTextureEntryMaybe(s32 index);

    u8 _0[0x160];
    TextureAccessorEntryMaybe _160[1];
    u8 _170[0x430 - 0x170];
    s32 _430[1];
    u8 _434[0x500 - 0x434];
    s32 _500[1];
    u8 _504[0x624 - 0x504];
    s32 _624[1];
};

// 0x7101147c48 (no sampler accessor)
struct Unk_7101147C48 {
    s32 getMaterialIndexMaybe(s32 index) const;
    s32 getShaderParamIndexMaybe(s32 index) const;
    s32 getConstantIndexMaybe(s32 index) const;
    TextureAccessorEntryMaybe* getTextureEntryMaybe(s32 index);

    u8 _0[0x100];
    TextureAccessorEntryMaybe _100[1];
    u8 _110[0x8ac - 0x110];
    s32 _8ac[1];
    u8 _8b0[0xbb0 - 0x8b0];
    s32 _bb0[1];
    u8 _bb4[0xcb4 - 0xbb4];
    s32 _cb4[1];
};

}  // namespace ksys::tera

// Full native 0x7100F3F84C (28 bytes) records terrain bit indices 0..9 from
// callback 0x7101200AC0. Declaration only; terrain storage ownership stays unresolved.
void sub_7100F3F84C(u32 index);

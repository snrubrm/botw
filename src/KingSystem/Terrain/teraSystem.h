#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <math/seadVector.h>
#include <math/seadMatrix.h>
#include <thread/seadAtomic.h>
#include "KingSystem/Utils/Types.h"

namespace gsys {
class Model;
}

namespace sead {
class Heap;
}

namespace ksys::tera {

// TODO:
class ApertureMaps {
    void updateMap();
};
class ApertureMapsCollector {
    void allocateImage();
    void releaseImage();
};
class Core {
public:
    class Grass {
    public:
        void sub_7101150990(bool enabled);
        void sub_7101150A7C(const sead::Vector3f* pos, f32 radius, f32 value);

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
    void sub_7101300BF0();
    void sub_710130085C();
    void sub_710130089C();
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

// Terrain is the CSV name of the singleton at 0x7102620698.
// The bases and the remaining members are not modeled yet.
class Terrain {
public:
    static Terrain* sInstance;
    static Terrain* instance() { return sInstance; }

    void setPauseState(bool paused);
    void sub_710114D804(bool enabled, const sead::Matrix44f* projection,
                      const sead::Matrix34f* view);
    s32 sub_710114DD84(s32 index);
    void sub_710114DDF8(u32 index, const sead::Vector3f* position, bool update);
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

    u8 _0[0x360];
    Core* _360;
    u8 _368[0x60];
    f32 _3c8;
    u8 _3cc[0x680 - 0x3cc];
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
class Scene {
    void exportFileBinary();
};
class System {
public:
    static System* instance();
    void sub_710111F518(int level, int type);
    void sub_7101112A74();
    void allocateApertureMapsCollectorImage(sead::Heap* heap);
    void loadScene();
    // 0x710111f618 (CSV TeraSystem::x_0): bit 3 of the flags of the `index`th scene (the first if out of range)
    bool sub_710111F618(s32 index);
};
class Water {
    void setUpAttributeTable();
};

// CreateTeraSystem passes the System created at 0x71011113d4 to PlacementMgr.
u32 sub_710110B4A4(f32* out_height, const sead::Vector2f* xz, System* system);
// Returns query status 0/1/2; the final argument preserves a full integer flag.
u32 sub_71011094A0(f32* out_height, const sead::Vector2f* xz, System* system, s32 index,
                    s32 flag);

bool checkTeraSystemStatus();

// 0x71011190c8 (declaration only; placeholder name and signature): called by map::PlacementMapMgr::postPlaceActorsRouteStuff with
// the tera system and every route of every map.
void sub_71011190C8(void* tera_system, void* route);

}  // namespace ksys::tera

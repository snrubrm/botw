#pragma once

#include <container/seadObjArray.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Utils/Types.h"
#include "KingSystem/World/worldShootingStarMgr.h"

namespace ksys::act {
class InstParamPack;
}

namespace ksys::world {

// One "FldObj_DLC_ShootingStarCollaborationAnchor" entry of the map static mubin (0x90 bytes, constructed inline
// in ShootingStarMgrEx::sub_71010CFE18; the name is a guess after the byml key). Both destructors are emitted
// in ShootingStarMgr's translation unit.
class ShootingStarAnchor {
public:
    virtual ~ShootingStarAnchor();

    // 0x71010cf868 (CSV wm::calcShootingStarDLC; declaration only)
    void calcShootingStarDLC();
    void sub_71010D00B0();

    void sub_71010D0814(act::InstParamPack* pack, const sead::Vector3f* position);

    u8 _8[0x48 - 0x8];
    sead::Vector3f _48;
    u8 _54[0x60 - 0x54];
    f32 _60;
    u8 _64[4];
    const char* _68;
    const char* _70;
    const char* _78;
    u8 _80[8];
    bool _88;
    bool _89;
    u8 _8a[6];
};
KSYS_CHECK_SIZE_NX150(ShootingStarAnchor, 0x90);

class ShootingStarMgrEx : public ShootingStarMgr {
public:
    ShootingStarMgrEx();
    ~ShootingStarMgrEx() override;

    void init_(sead::Heap* heap) override;
    void calc_() override;
    void m11() override {}
    void spawnStar() override;

private:
    // 0x71010cfe18 (declaration only): loads the anchors from the map static mubin
    bool sub_71010CFE18();

    /* 0x30 */ sead::ObjArray<ShootingStarAnchor> mAnchors;
    /* 0x50 */ sead::FixedSafeString<0x20> mMapName;
};
KSYS_CHECK_SIZE_NX150(ShootingStarMgrEx, 0x88);

}  // namespace ksys::world

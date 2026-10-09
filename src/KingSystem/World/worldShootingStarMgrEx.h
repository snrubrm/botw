#pragma once

#include <container/seadObjArray.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Utils/Types.h"
#include "KingSystem/World/worldShootingStarMgr.h"

namespace ksys::act {
class InstParamPack;
}

namespace ksys::world {

bool sub_71010D103C();

// One "FldObj_DLC_ShootingStarCollaborationAnchor" entry of the map static mubin (0x90 bytes, constructed inline
// in ShootingStarMgrEx::sub_71010CFE18; the name is a guess after the byml key). Both destructors are emitted
// in ShootingStarMgr's translation unit.
class ShootingStarAnchor {
public:
    virtual ~ShootingStarAnchor();

    // 0x71010cf868 (CSV wm::calcShootingStarDLC; declaration only)
    void calcShootingStarDLC();
    void sub_71010D00B0();

    bool sub_71010D0734() const;
    bool sub_71010D07A4() const;
    void sub_71010D1394();
    bool sub_71010D0F64(s32 hour_offset) const;
    // 0x71010d0d78 (placeholder name): the anchor can show its star: flag _68 set, flag _70 clear, the
    // hour window (end + 2), not `_89`, and the camera between 25 and 2000 units away (horizontally).
    bool sub_71010D0D78() const;
    void sub_71010D1348(bool value) const;

    struct Identifier {
        u32 hash{};
        sead::SafeString name;
    };

    void sub_71010D0814(act::InstParamPack* pack, sead::Vector3f* out_position);

    u8 _8[0x2c - 0x8];
    s32 _2c;
    Identifier mIdentifier;
    sead::Vector3f _48;
    s32 mStartHour;
    s32 mEndHour;
    u8 _5c[4];
    f32 _60;
    u8 _64[4];
    const char* _68;
    const char* _70;
    const char* _78;
    u8 _80[4];
    s32 _84;
    bool _88;
    bool _89;
    u8 _8a[6];
};
KSYS_CHECK_SIZE_NX150(ShootingStarAnchor, 0x90);

class ShootingStarMgrEx : public ShootingStarMgr {
public:
    ShootingStarMgrEx();
    static ShootingStarAnchor* sub_71010D0464(const ShootingStarAnchor::Identifier& id);
    // 0x71010d05f0 (placeholder name): returns 20.0f.
    static f32 sub_71010D05F0();
    // 0x71010d05f8 (placeholder name): the map name of the world manager's ShootingStarMgrEx, or
    // "MainField" without one.
    static const sead::SafeString& sub_71010D05F8();
    // 0x71010d06c4 (CSV WorldMgrStruct0_2::x; placeholder name): clears _84 of the anchors with this name.
    void sub_71010D06C4(const sead::SafeString& name);
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

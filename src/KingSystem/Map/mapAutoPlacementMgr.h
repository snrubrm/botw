#pragma once

#include <heap/seadDisposer.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <prim/seadDelegate.h>
#include <prim/seadSafeString.h>
#include <container/seadSafeArray.h>
#include <thread/seadAtomic.h>
#include <thread/seadCriticalSection.h>

#include "KingSystem/Utils/Types.h"

namespace sead {
class DelegateThread;
}

namespace ksys::act {
class Actor;
}  // namespace ksys::act

namespace ksys::map {

// Placeholder (CSV AutoPlacementInfo::ctor 0x7100e8c60c, x 0x7100e8ce54 (pos -> grid cell lookup), x_0): embedded in the
// AutoPlacementMgr at 0x171ef0 (size is a guess: up to the next member at 0x189df8; not decompiled).
class AutoPlacementInfo {
public:
    // 0x7100e8ce54 (declared only; 720 bytes): `a4` is the optional extra buffer (the mgr passes its member at
    // 0x189df8 for placement type 0).
    bool x(const sead::Vector3f& pos, bool a2, u32 type_mask, const void* a4);
    // 0x7100e8d124 (CSV x_0; declaration only; placeholder parameter names): looks at one grid cell; -1 if there is
    // no match.
    int x_0(f32 scale, int cell_x, int cell_z, const sead::Vector3f& pos, bool a2, u32 type_mask, const void* a7,
            const void* a4);

    u8 _0[0x189db0 - 0x171ef0];
};

class AutoPlacementMgr {
    SEAD_SINGLETON_DISPOSER(AutoPlacementMgr)
public:
    AutoPlacementMgr();
    virtual ~AutoPlacementMgr();

    bool sub_7100659E40(act::Actor* actor, const sead::SafeString& actor_name, int count,
                        u32 is_box);
    void sub_7100659F94(act::Actor* actor);
    // 0x7100655568 (CSV stopThread)
    void stopThread();
    // 0x7100659158 (CSV __auto10; placeholder name): placement type of the flow `idx` (near flows with `near_flow`).
    int sub_7100659158(int idx, bool near_flow);
    // 0x71006591bc (CSV __auto4; placeholder name): whether the placement type of the flow `idx` is active.
    bool sub_71006591BC(int idx, bool near_flow);
    // 0x7100659230 / 0x71006592e8 (CSV __auto7 / __auto6; placeholder names): 50 / 200 times the statistics value at
    // `pos` (0 if there is none).
    f32 sub_7100659230(const sead::Vector3f& pos);
    f32 sub_71006592E8(const sead::Vector3f& pos);
    // 0x7100659de0 (CSV AutoPlacementMgr::__auto3, declaration only): increments (`enable`) or decrements the
    // atomic counter of kind `type` (0-6) at 0x171e4c; incrementing also stores 5 at 0x171e68 + type.
    void sub_7100659DE0(int type, bool enable);

    // 0x0000007100654e44
    bool threadFn();
    // 0x0000007100656030
    bool auto9();
    // 0x0000007100656d24
    bool auto2(const sead::SafeString& name, const sead::Vector3f& pos);
    // 0x0000007100659188
    bool auto0(const sead::Vector3f& pos, u32 placement_type);
    // 0x0000007100659350
    bool auto11(const sead::Vector3f& pos);
    // 0x000000710065946c (CSV name). With `a2`, true while the s8 at 0x171e6e is positive
    // (after a discarded dlc::isPlayingOneHitObliteratorQuest() call); otherwise asks the
    // AutoPlacementInfo at 0x171ef0 (AutoPlacementInfo::x(pos, true, 0x40, nullptr)). Not decompiled
    // yet: AutoPlacementInfo is not declared.
    bool isNonAutoPlacement(const sead::Vector3f& pos, bool a2);

    // TODO: rename
    struct Unk1 {
        act::Actor* actor;
        sead::SafeString name;
        // The actor's matrix / scale when it was registered (sub_7100659E40).
        sead::Matrix34f mtx;
        sead::Vector3f scale;
        u32 is_box;
        u8 _58[0x8b60 - 0x58];
        u16 count;
        bool _8b62;
        u8 _8b63[0x8b68 - 0x8b63];
    };
    KSYS_CHECK_SIZE_NX150(Unk1, 0x8b68);

    /* 0x28 */ sead::DelegateThread* mThread;
    /* 0x30 */ sead::DelegateR<AutoPlacementMgr, bool> mDelegate;
    /* 0x50 */ sead::Atomic<s32> _50;
    // TODO
    u8 _54[0x5b0d8 - 0x54];
    sead::CriticalSection mCS;
    sead::SafeArray<Unk1, 32> _5b118;
    u8 _171e18[0x171e46 - 0x171e18];
    bool _171e46;
    u8 _171e47;
    s32 _171e48;
    sead::SafeArray<sead::Atomic<s32>, 7> _171e4c;
    sead::SafeArray<s8, 7> _171e68;
    u8 _171e6f[0x171ef0 - 0x171e6f];
    AutoPlacementInfo _171ef0;
    // Statistics pointers (StatisticsMgr::getStatsPointer results) used by sub_7100659230 / sub_71006592E8.
    void* _189db0;
    u8 _189db8[0x189dd0 - 0x189db8];
    void* _189dd0;
    u8 _189dd8[0x189df8 - 0x189dd8];
    u8 _189df8[0x189e38 - 0x189df8];
};
KSYS_CHECK_SIZE_NX150(AutoPlacementMgr, 0x189E38);

// 0x7100659298 (placeholder name and signature; called by the AutoPlacement queries apQueryTreeRate / apQueryRouteDistance): the
// StatisticsMgr value of the statistics pointer `*stats` at `pos`, 0 if the query fails.
f32 sub_7100659298(const sead::Vector3f& pos, void* const* stats);

// 0x710065622c (placeholder name and signature; called by AutoPlacementMgr 0x71006 4de34): the cell (50 x 40 cells of 200 units, the
// origin at (-5000, -4000)) of `pos`, clamped to the grid.
void sub_710065622C(s32* col, s32* row, const sead::Vector3f* pos);

}  // namespace ksys::map

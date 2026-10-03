#pragma once

#include <heap/seadDisposer.h>
#include <math/seadVector.h>
#include <prim/seadDelegate.h>
#include <prim/seadSafeString.h>
#include <container/seadSafeArray.h>
#include <thread/seadCriticalSection.h>

#include "KingSystem/Utils/Types.h"

namespace ksys::act {
class Actor;
}  // namespace ksys::act

namespace ksys::map {

class AutoPlacementMgr {
    SEAD_SINGLETON_DISPOSER(AutoPlacementMgr)
public:
    AutoPlacementMgr();
    virtual ~AutoPlacementMgr();

    bool sub_7100659E40(act::Actor* actor, const sead::SafeString& actor_name, int count,
                        bool is_box);
    void sub_7100659F94(act::Actor* actor);
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
        u8 _8[0x8b68 - 0x8];
    };
    KSYS_CHECK_SIZE_NX150(Unk1, 0x8b68);

    sead::DelegateR<AutoPlacementMgr, bool> mDelegate;
    // TODO
    u8 _48[0x5b0d8 - 0x48];
    sead::CriticalSection mCS;
    sead::SafeArray<Unk1, 32> _5b118;
    u8 _171e18[0x171e46 - 0x171e18];
    bool _171e46;
    u8 _171e47;
    s32 _171e48;
    u8 _171e4c[0x189e38 - 0x171e4c];
};
KSYS_CHECK_SIZE_NX150(AutoPlacementMgr, 0x189E38);

}  // namespace ksys::map

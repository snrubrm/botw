#pragma once

#include <basis/seadTypes.h>
#include <heap/seadDisposer.h>
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace ksys::act {
class ActorConstDataAccess;
}

namespace uking {

namespace act {
// 0x7100e6eaac (declaration only; CreateObjectsOfOwnedHorse::calc_): a check of the horse actor.
bool sub_7100E6EAAC(const ksys::act::ActorConstDataAccess& accessor);
}  // namespace act

// Placeholder declaration (name from the CSV: HorseMgr::createInstance 0x7100e81fb0, ctor
// 0x7100e821e4, postCalc 0x7100e8789c, createHorse, ...; instance pointer at 0x7102603c90; namespace
// is a guess). The manager of the owned horse; only what the AI actions use is declared.
// TODO: incomplete.
class HorseMgr {
    SEAD_SINGLETON_DISPOSER(HorseMgr)
    HorseMgr();
    ~HorseMgr();

public:
    // 0x7100e85334 (CSV HorseMgr::__auto0): whether `link` is the owned horse's link.
    bool sub_7100E85334(const ksys::act::BaseProcLink& link) const;
    // 0x7100e8527c (declaration only; NPCRegisterHorse / NPCRegisterAndReceiveHorse): registers
    // the horse `link` under `name`.
    bool sub_7100E8527C(ksys::act::BaseProcLink* link, const sead::SafeString& name, bool a3);

    // 0x7100e857cc (declaration only, placeholder signature): used by NPCReleaseHorse with
    // (Horse_SelectedIndex, true, false, -1).
    void sub_7100E857CC(s32 index, bool a2, bool a3, s32 a4);
    // 0x7100e86cf4 / 0x7100e86d44 (declaration only; WaitWhileCreatingOwnedHorse): whether the horse
    // is still being created / marks it done.
    bool sub_7100E86CF4();
    void sub_7100E86D44();
    // 0x7100e87340 / 0x7100e87424 / 0x7100e87508 (declarations only; CreateObjectsOfOwnedHorse::enter_):
    // create the mane / reins / saddle actor with the given name.
    void sub_7100E87340(const sead::SafeString& name, sead::Heap* heap);
    void sub_7100E87424(const sead::SafeString& name, sead::Heap* heap);
    void sub_7100E87508(const sead::SafeString& name, sead::Heap* heap);
    // 0x7100e875ec (declaration only; CreateObjectsOfOwnedHorse::leave_).
    void sub_7100E875EC();
    // 0x7100e85bc0 (declaration only; NPCReceiveHorse).
    void sub_7100E85BC0();

    /* 0x20 */ ksys::act::BaseProcLink mOwnedHorse;
    /* 0x30 */ ksys::act::BaseProcLink _30;  // the horse being registered / received (NPCRegisterHorse)
};

}  // namespace uking

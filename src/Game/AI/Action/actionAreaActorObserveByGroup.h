#pragma once

#include <container/seadSafeArray.h>
#include <prim/seadDelegate.h>
#include "Game/AI/Action/actionAreaActorObserve.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AreaActorObserveByGroup;

// vtable 0x7102366fd8: the filter delegates' type. Its vtable is a separate copy of the
// Delegate1R one (0x7102367000, which Delegate1R::clone() uses), so the members are of a class
// derived from Delegate1R that overrides nothing.
class Unk_7102366fd8
    : public sead::Delegate1R<AreaActorObserveByGroup, const ksys::act::ActorConstDataAccess&, bool> {
public:
    using Delegate1R::Delegate1R;
};

class AreaActorObserveByGroup : public AreaActorObserve {
    SEAD_RTTI_OVERRIDE(AreaActorObserveByGroup, AreaActorObserve)
public:
    using Filter = Unk_7102366fd8;

    explicit AreaActorObserveByGroup(const InitArg& arg);
    ~AreaActorObserveByGroup() override;

    bool init_(sead::Heap* heap) override;
    void m9() override;

protected:
    void m32() override;
    bool m37(const ksys::act::ActorConstDataAccess& accessor) override;
    bool m16(ksys::phys::RigidBody* body) override;

    // Group filters (indexed by the ActorGroupForObserveTag map unit parameter).
    bool sub_710009E7AC(const ksys::act::ActorConstDataAccess& accessor);
    bool sub_710009E7C0(const ksys::act::ActorConstDataAccess& accessor);
    bool sub_710009E7C8(const ksys::act::ActorConstDataAccess& accessor);
    bool sub_710009E7D0(const ksys::act::ActorConstDataAccess& accessor);
    // 0x710009e848 (declared only): needs the act::acc::Bullet accessor (not decompiled).
    bool sub_710009E848(const ksys::act::ActorConstDataAccess& accessor);

    sead::SafeArray<Filter, 5> mFilters;
    int mGroup = 0;
    // map_unit_param (loaded by m32)
    const int* mActorGroupForObserveTag_m{};
};
KSYS_CHECK_SIZE_NX150(AreaActorObserveByGroup, 0x110);

}  // namespace uking::action

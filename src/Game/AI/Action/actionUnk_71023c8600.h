#pragma once

#include <prim/seadSafeString.h>
#include "Game/AI/Action/actionUnk_71025afc58.h"

namespace ksys::act {
class BaseProcHandle;
}

// Ignite/grab helper (vtable 0x71023c8600, ctor 0x71002a7924) embedded in ForkIgniteCarriedActor,
// ForkForceIgniteCarriedActor, ForkOctarockEnterReloadWig, OctarockReloadWig and IgniteGrabAndShoot:
// connects the actor given by the dynamic param IgniteHandle as a calc child (once the AS allows it)
// and grabs it with GrabIdx. The optional actor parts name _30 is registered with the owner's
// Unk_7100d3cd74.
class Unk_71023c8600 : public Unk_71025afc58 {
    SEAD_RTTI_OVERRIDE(Unk_71023c8600, Unk_71025afc58)
public:
    explicit Unk_71023c8600(ksys::act::ai::ActionBase* owner);
    ~Unk_71023c8600() override;

    bool isFailed() const override { return _28 == 4; }
    bool isFinished() const override { return _28 == 3; }
    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override {}
    void loadParams_() override;

    void sub_71002A7A38();

    const int* mGrabIdx_s{};
    ksys::act::BaseProcHandle** mIgniteHandle_d{};
    /// 0: wait for the AS, 1: connected, 2: grabbed, 3: finished, 4: failed.
    int _28 = 0;
    sead::SafeString _30;
};
KSYS_CHECK_SIZE_NX150(Unk_71023c8600, 0x40);

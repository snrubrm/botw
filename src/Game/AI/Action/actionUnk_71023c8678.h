#pragma once

#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include "Game/AI/Action/actionUnk_71025afc58.h"

namespace ksys::act {
class Actor;
class BaseProcHandle;
}  // namespace ksys::act

// Follow/ignite helper (vtable 0x71023c8678, ctor 0x71002a7ed0) embedded in FollowIgniteToSelfPos
// (and, through a subclass with vtable 0x7102360d20, in FollowIgniteToBonePos): once the AS allows
// it, places the actor given by IgniteHandle at m13()'s position with a random yaw, releases it
// and links it to the owner's physics. The optional memory parts name is registered with the
// owner's enemy parts list (Enemy::_1128).
class Unk_71023c8678 : public Unk_71025afc58 {
    SEAD_RTTI_OVERRIDE(Unk_71023c8678, Unk_71025afc58)
public:
    explicit Unk_71023c8678(ksys::act::ai::ActionBase* owner);
    ~Unk_71023c8678() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override {}
    void loadParams_() override;
    bool handleMessage_(const ksys::Message& message) override;
    virtual void m13(sead::Vector3f* pos);
    virtual void m14(ksys::act::Actor* actor) {}

    void sub_71002A81D4(ksys::act::BaseProcHandle* handle);

    sead::SafeString mMemoryPartsName_s;
    ksys::act::BaseProcHandle** mIgniteHandle_d{};
    bool _30 = false;
};
KSYS_CHECK_SIZE_NX150(Unk_71023c8678, 0x38);

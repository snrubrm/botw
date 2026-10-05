#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/System/Timer.h"

namespace uking::action {

class ForkDisableContact : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkDisableContact, ksys::act::ai::Action)
public:
    explicit ForkDisableContact(const InitArg& arg);
    ~ForkDisableContact() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // 0x710014b0f0 (declared only): the body of leave_ is out of line in the original.
    void sub_710014B0F0();
    void sub_710014AED0();
    void sub_710014B018();
    void calc_() override;
    virtual bool m32() = 0;
    virtual bool m33() = 0;

    // static_params at offset 0x20 (RigidBodyName0-4)
    sead::SafeString mRigidBodyName_s[5];
    struct Params {
        // static_param at offset 0x70
        const int* mRecoverDelayTimeMin_s{};
    };
    Params mParams;

    // Rigid bodies looked up by name in init_ (RigidBodyName0-4)
    struct Body {
        ksys::phys::RigidBody* mBody{};
        bool mIsEnabled = true;
    };
    Body mBodies[5];
    ksys::Timer mRecoverTimer;
};

}  // namespace uking::action

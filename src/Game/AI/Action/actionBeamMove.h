#pragma once
#include "KingSystem/ActorSystem/actActorAtk.h"

#include "KingSystem/ActorSystem/actAiAction.h"
#include <math/seadVector.h>

namespace ksys::phys {
class RigidBody;
}

namespace uking::action {

class BeamMove : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(BeamMove, ksys::act::ai::Action)
public:
    explicit BeamMove(const InitArg& arg);
    ~BeamMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    using AttackInfo = ksys::act::ActorAtk::Struct7::AttackInfo;
    virtual bool m32(const AttackInfo* info);
    virtual void m33(const AttackInfo* info);
    virtual bool m34(const AttackInfo* info);
    virtual void m35(sead::Vector3f* dir);
    virtual void m36(const AttackInfo* info);
    virtual f32 m37();
    virtual bool m38();
    virtual bool m39(sead::Vector3f* pos);
    virtual void m40();
    virtual int m41();
    virtual int m42();
    virtual int m43();

    // static_param at offset 0x20
    const int* mAtMinDamage_s{};
    // static_param at offset 0x28
    const int* mShieldDamage_s{};
    // static_param at offset 0x30
    const float* mForceExplodeFrame_s{};
    // aitree_variable at offset 0x38
    bool* mIsReflectThrownBullet_a{};
    sead::Vector3f _40 = sead::Vector3f::ez;
    f32 _4c = 0;
    ksys::phys::RigidBody* _50 = nullptr;
    ksys::phys::RigidBody* _58 = nullptr;
    ksys::phys::RigidBody* _60 = nullptr;
    u8 _68 = 0;
    u8 _69 = 0;
    bool _6a = false;
    bool _6b = false;
    u32 _6c = 0;
};

KSYS_CHECK_SIZE_NX150(BeamMove, 0x70);

}  // namespace uking::action

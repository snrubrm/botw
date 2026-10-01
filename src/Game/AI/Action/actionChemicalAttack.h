#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ChemicalAttack : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ChemicalAttack, ksys::act::ai::Action)
public:
    explicit ChemicalAttack(const InitArg& arg);
    ~ChemicalAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    virtual void m32();
    virtual int m33();
    virtual float m34();
    virtual int m35();
    virtual int m36();
    virtual int m37();
    virtual int m38();
    virtual int m39();

    // static_param at offset 0x20
    const int* mAttackIntensity_s{};
    // static_param at offset 0x28
    const int* mAttackMinPower_s{};
    // map_unit_param at offset 0x30
    const int* mAttackPower_m{};
    // map_unit_param at offset 0x38
    const int* mAttackPowerForPlayer_m{};
    // map_unit_param at offset 0x40
    const float* mScaleTime_m{};
    // map_unit_param at offset 0x48
    const float* mRange_m{};
    // map_unit_param at offset 0x50
    sead::SafeString mRigidBodyName_m{};
    sead::Vector3f _60;
    sead::Vector3f _6c;
    f32 _78 = 0;
    f32 _7c = 1.0f;
};

}  // namespace uking::action

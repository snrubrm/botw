#pragma once

#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace ksys::phys {
class CollisionInfo;
}

namespace uking::action {

class DamageField : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(DamageField, ksys::act::ai::Action)
public:
    explicit DamageField(const InitArg& arg);
    ~DamageField() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mFieldType_s{};
    // static_param at offset 0x28
    const int* mRigidSetName_s{};
    // static_param at offset 0x30
    const bool* mIsChangeRigidWorldMode_s{};
    // static_param at offset 0x38
    const bool* mIsUseCollisionInfo_s{};
    // static_param at offset 0x40
    sead::SafeString mRigidBodyName_s{};
    // static_param at offset 0x50
    sead::SafeString mCollisionInfoName_s{};
    /* 0x60 */ Unk_7102372d68 _60{mActor, 0x8000084};
    const sead::SafeString& getRigidSetName() const;
    // 0x71000e5dac (no CSV name): messages the actors of the bodies colliding with `info`.
    void sub_7100E5DAC(ksys::phys::CollisionInfo* info);
};

}  // namespace uking::action

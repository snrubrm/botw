#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::action {

class ExpandChemicalField : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ExpandChemicalField, ksys::act::ai::Action)
public:
    explicit ExpandChemicalField(const InitArg& arg);
    ~ExpandChemicalField() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // 0x7100129760: ends the field: puts the actor to sleep if its creator (a Bullet's `_bd0` link or the create
    // arg link) is alive, else deletes it.
    void sub_7100129760();

    // map_unit_param at offset 0x20
    const int* mAttackPower_m{};
    // map_unit_param at offset 0x28
    const int* mAttackAttr_m{};
    // map_unit_param at offset 0x30
    const int* mAttackType_m{};
    // map_unit_param at offset 0x38
    const int* mCutGrassType_m{};
    // map_unit_param at offset 0x40
    const int* mAttackTarget_m{};
    // map_unit_param at offset 0x48
    const int* mAttackDirType_m{};
    // map_unit_param at offset 0x50
    const float* mScaleTime_m{};
    // map_unit_param at offset 0x58
    const bool* mIsReuseActor_m{};
    // map_unit_param at offset 0x60
    const bool* mIsUseAtCollision_m{};
    // map_unit_param at offset 0x68
    sead::SafeString mXLinkKey_m{};
    f32 _78 = 0.0f;
    f32 _7c = 1.0f;
    Unk_71012419b4 _80;
};
KSYS_CHECK_SIZE_NX150(ExpandChemicalField, 0xa0);

}  // namespace uking::action

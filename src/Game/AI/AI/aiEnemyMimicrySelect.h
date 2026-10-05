#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyMimicrySelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyMimicrySelect, ksys::act::ai::Ai)
public:
    explicit EnemyMimicrySelect(const InitArg& arg);
    ~EnemyMimicrySelect() override;
    bool isChangeable() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void calc_() override;
    void loadParams_() override;

    void sub_71003988E0(ksys::act::ai::InlineParamPack* params);

    void sub_7100398A34(ksys::act::ai::InlineParamPack* params);

protected:
    // map_unit_param at offset 0x38
    const bool* mIsMimicry_m{};
    // aitree_variable at offset 0x40
    int* mMimicryMaterial_a{};
    // aitree_variable at offset 0x48
    bool* mIsStartResetMimicry_a{};
    u8 _50 = 0xff;
};

}  // namespace uking::ai

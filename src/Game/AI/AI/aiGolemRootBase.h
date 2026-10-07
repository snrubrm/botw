#pragma once

#include "Game/AI/AI/aiEnemyRoot.h"
#include "Game/AI/aiUnk_7102450410.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GolemRootBase : public EnemyRoot {
    SEAD_RTTI_OVERRIDE(GolemRootBase, EnemyRoot)
public:
    explicit GolemRootBase(const InitArg& arg);
    ~GolemRootBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    void m37() override;
    void m38() override;

    bool m35() override;

    void sub_71004012F8();
    void sub_71004014A4();
    void sub_7100402194();

protected:
    // static_param at offset 0x1d8
    const int* mShaderASTargetBone_s{};
    // static_param at offset 0x1e0
    const int* mBodyShaderSeqBank_s{};
    // static_param at offset 0x1e8
    const int* mArmRShaderSeqBank_s{};
    // static_param at offset 0x1f0
    const int* mArmLShaderSeqBank_s{};
    // static_param at offset 0x1f8
    sead::SafeString mUpperArmL_PartsKey_s{};
    // static_param at offset 0x208
    sead::SafeString mLowerArmL_PartsKey_s{};
    // static_param at offset 0x218
    sead::SafeString mUpperArmR_PartsKey_s{};
    // static_param at offset 0x228
    sead::SafeString mLowerArmR_PartsKey_s{};
    // static_param at offset 0x238
    sead::SafeString mChemicalFieldKey_s{};
    // static_param at offset 0x248
    sead::SafeString mBodyDeactiveAS_s{};
    // static_param at offset 0x258
    sead::SafeString mArmRDeactiveAS_s{};
    // static_param at offset 0x268
    sead::SafeString mArmLDeactiveAS_s{};
    // static_param at offset 0x278
    sead::SafeString mBodyActiveAS_s{};
    // static_param at offset 0x288
    sead::SafeString mArmRActiveAS_s{};
    // static_param at offset 0x298
    sead::SafeString mArmLActiveAS_s{};
    // static_param at offset 0x2a8
    sead::SafeString mBodyMimicAS_s{};
    // static_param at offset 0x2b8
    sead::SafeString mArmRMimicAS_s{};
    // static_param at offset 0x2c8
    sead::SafeString mArmLMimicAS_s{};
    // map_unit_param at offset 0x2d8
    sead::SafeString mGolemTextureName_m{};
    // aitree_variable at offset 0x2e8
    void* mGolemChemicalController_a{};
    Unk_7102450410 _2f0;
};
KSYS_CHECK_SIZE_NX150(GolemRootBase, 0x310);

}  // namespace uking::ai

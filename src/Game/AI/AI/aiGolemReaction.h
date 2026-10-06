#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/ActorSystem/actUnk_7100d3bc4c.h"

namespace uking::ai {

class GolemReaction : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GolemReaction, ksys::act::ai::Ai)
public:
    explicit GolemReaction(const InitArg& arg);
    ~GolemReaction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    void sub_71003FE9C4();
    // 0x71003ff3f8 (declaration only, 352 B; placeholder name): reports which arms (a: right, b: left) were broken.
    void sub_71003FF3F8(bool* right, bool* left);
    // 0x71003ff79c (declaration only, 708 B; placeholder name): breaks an arm: its body names, the effect key and
    // the arm target/material names.
    void sub_71003FF79C(const sead::SafeString& body1, const sead::SafeString& body2,
                        const sead::SafeString& str, const sead::SafeString& target,
                        const sead::SafeString& chm, const sead::SafeString& material,
                        const sead::SafeString& xlink_key);
    bool sub_71003FEAB0();
    bool sub_71003FEC7C();

protected:
    // static_param at offset 0x38
    const int* mClimbLimitTime_s{};
    // static_param at offset 0x40
    const int* mClampRestClimbTime_s{};
    // static_param at offset 0x48
    const int* mIgnoreBombTime_s{};
    // static_param at offset 0x50
    sead::SafeString mRightArmTgtBodyName_s{};
    // static_param at offset 0x60
    sead::SafeString mLeftArmTgtBodyName_s{};
    // static_param at offset 0x70
    sead::SafeString mBreakArmLXLinkKey_s{};
    // static_param at offset 0x80
    sead::SafeString mBodyArmLName1_s{};
    // static_param at offset 0x90
    sead::SafeString mBodyArmLName2_s{};
    // static_param at offset 0xa0
    sead::SafeString mChmArmLName_s{};
    // static_param at offset 0xb0
    sead::SafeString mArmLMaterialName_s{};
    // static_param at offset 0xc0
    sead::SafeString mBreakArmRXLinkKey_s{};
    // static_param at offset 0xd0
    sead::SafeString mBodyArmRName1_s{};
    // static_param at offset 0xe0
    sead::SafeString mBodyArmRName2_s{};
    // static_param at offset 0xf0
    sead::SafeString mChmArmRName_s{};
    // static_param at offset 0x100
    sead::SafeString mArmRMaterialName_s{};
    // aitree_variable at offset 0x110
    float* mGolemClimbedTime_a{};
    // aitree_variable at offset 0x118
    void* mGolemChemicalController_a{};
    bool _120 = true;
    ksys::act::Unk_7100d3bce4 _128{mActor};
    ksys::act::BaseProcLink _140;
};
KSYS_CHECK_SIZE_NX150(GolemReaction, 0x150);

}  // namespace uking::ai

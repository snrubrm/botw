#pragma once

#include <container/seadSafeArray.h>
#include <gsys/gsysModelAccessKey.h>
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DemoCookPotCook : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(DemoCookPotCook, ksys::act::ai::Action)
public:
    explicit DemoCookPotCook(const InitArg& arg);
    ~DemoCookPotCook() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    // Updates the carried ingredients' bone transforms.
    void sub_71000E8D94();

    // static_param at offset 0x20
    const int* mMaterialTargetBone_s{};
    // static_param at offset 0x28
    const int* mFairyTargetBone_s{};
    // dynamic_param at offset 0x30
    bool* mIsSuccess_d{};
    // aitree_variable at offset 0x38
    void* mCurrentCookResultHolder_a{};
    s32 _40 = 0;
    gsys::BoneAccessKeyEx _48;
    gsys::BoneAccessKeyEx _80;
    gsys::BoneAccessKeyEx _b8;
    sead::SafeArray<gsys::BoneAccessKeyEx, 5> _f0;
    s32 _208 = 0;
    s32 _20c = 0;
    bool _210 = false;
};
KSYS_CHECK_SIZE_NX150(DemoCookPotCook, 0x218);

}  // namespace uking::action

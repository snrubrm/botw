#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkASTrgWeaponDrop : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkASTrgWeaponDrop, ksys::act::ai::Action)
public:
    explicit ForkASTrgWeaponDrop(const InitArg& arg);
    ~ForkASTrgWeaponDrop() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // 0x7100146880 (declared only): out of line in the original.
    void sub_7100146880();
    void calc_() override;

    const int* mWeaponIdx_s[4]{};
    // static_param at offset 0x40
    const bool* mIsKeepRemind_s{};
};

}  // namespace uking::action

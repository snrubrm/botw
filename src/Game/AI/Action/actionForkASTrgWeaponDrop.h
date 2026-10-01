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
    void calc_() override;

    // static_param at offset 0x40
    const bool* mIsKeepRemind_s{};
    void* _28{};
    void* _30{};
    void* _38{};
    void* _40{};
};

}  // namespace uking::action

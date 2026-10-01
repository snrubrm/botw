#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EquipHaveSelector : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EquipHaveSelector, ksys::act::ai::Ai)
public:
    explicit EquipHaveSelector(const InitArg& arg);
    ~EquipHaveSelector() override;
    bool isChangeable() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    void calc_() override;

    virtual bool m34();

protected:
    // static_param at offset 0x38
    const int* mWeaponIdx_s{};
    void* _40{};
};

}  // namespace uking::ai

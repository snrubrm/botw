#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class DrawnWeaponSelector : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(DrawnWeaponSelector, ksys::act::ai::Ai)
public:
    explicit DrawnWeaponSelector(const InitArg& arg);
    ~DrawnWeaponSelector() override;
    void calc_() override;
    bool isFinished() const override;
    bool isFailed() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    // 0x7100373988 (placeholder name): starts the child for the weapon type the actor has drawn (bits of the mask from
    // sub_7100373C14: 1 sword, 2 two-handed sword, 4 spear, 8 bow, 0x10 shield).
    void sub_7100373988(ksys::act::ai::InlineParamPack* params);
    // 0x7100373c14 (placeholder name): sets bit `weapon type` of `mask` for each of the six weapon links the actor holds.
    void sub_7100373C14(u32* mask);

protected:
};

}  // namespace uking::ai

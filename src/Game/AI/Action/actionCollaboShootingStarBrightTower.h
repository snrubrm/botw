#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::action {

class CollaboShootingStarBrightTower : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(CollaboShootingStarBrightTower, ksys::act::ai::Action)
public:
    explicit CollaboShootingStarBrightTower(const InitArg& arg);
    ~CollaboShootingStarBrightTower() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // aitree_variable at offset 0x20
    sead::SafeString* mCollaboShootingStarId_a{};
    Unk_71012419b4 _28;
    u32 _48 = 0;
    sead::SafeString _50;
};

}  // namespace uking::action

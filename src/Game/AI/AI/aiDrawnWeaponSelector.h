#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class DrawnWeaponSelector : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(DrawnWeaponSelector, ksys::act::ai::Ai)
public:
    explicit DrawnWeaponSelector(const InitArg& arg);
    ~DrawnWeaponSelector() override;
    bool isFinished() const override;
    bool isFailed() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    void sub_7100373988(ksys::act::ai::InlineParamPack* params);

protected:
};

}  // namespace uking::ai

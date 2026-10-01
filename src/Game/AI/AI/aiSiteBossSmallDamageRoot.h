#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SiteBossSmallDamageRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SiteBossSmallDamageRoot, ksys::act::ai::Ai)
public:
    explicit SiteBossSmallDamageRoot(const InitArg& arg);
    ~SiteBossSmallDamageRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    bool isFinished() const override;

protected:
};

}  // namespace uking::ai

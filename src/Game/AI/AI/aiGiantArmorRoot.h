#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GiantArmorRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GiantArmorRoot, ksys::act::ai::Ai)
public:
    explicit GiantArmorRoot(const InitArg& arg);
    ~GiantArmorRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    // 0x71003f5f6c (declared only)
    void sub_71003F5F6C();
};

}  // namespace uking::ai

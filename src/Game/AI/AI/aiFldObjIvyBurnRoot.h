#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class FldObjIvyBurnRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(FldObjIvyBurnRoot, ksys::act::ai::Ai)
public:
    explicit FldObjIvyBurnRoot(const InitArg& arg);
    ~FldObjIvyBurnRoot() override;
    void calc_() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void* _38{};
    u32 _40{};
    void* _48{};
    u32 _50{};
};

}  // namespace uking::ai

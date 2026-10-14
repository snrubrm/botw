#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class NPCReturnAnchor : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(NPCReturnAnchor, ksys::act::ai::Ai)
public:
    explicit NPCReturnAnchor(const InitArg& arg);
    ~NPCReturnAnchor() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    void sub_71004D6E7C();
    void sub_71004D70D8();

protected:
};

}  // namespace uking::ai

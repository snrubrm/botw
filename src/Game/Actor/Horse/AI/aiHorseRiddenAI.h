#pragma once

#include <prim/seadEnum.h>
#include "Game/Actor/aiFlagByte.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class HorseRiddenAI : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(HorseRiddenAI, ksys::act::ai::Ai)
public:
    explicit HorseRiddenAI(const InitArg& arg);

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    SEAD_ENUM(Flag, _0, _1)
    FlagByte<Flag> _38;
};

}  // namespace uking::ai

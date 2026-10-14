#pragma once

#include <prim/seadEnum.h>
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actModelBindInfo.h"

namespace uking::ai {

class RideHorseNonPlayer : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(RideHorseNonPlayer, ksys::act::ai::Ai)
public:
    explicit RideHorseNonPlayer(const InitArg& arg);
    ~RideHorseNonPlayer() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    void calc_() override;

    virtual void m34();
    virtual bool m35();
    virtual void m36();

protected:
    // Placeholder SEAD_ENUM: the bit index passed to `Unk_7100e8b2b8::_10` (stack round trip in the original).
    SEAD_ENUM(Bit, _0, _1, _2, _3)

    ksys::act::ModelBindInfo _38;
    s32 _d8 = 0;
};
KSYS_CHECK_SIZE_NX150(RideHorseNonPlayer, 0xe0);

}  // namespace uking::ai

#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actModelBindInfo.h"

namespace uking::ai {

class Magnetglove : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(Magnetglove, ksys::act::ai::Ai)
public:
    explicit Magnetglove(const InitArg& arg);
    ~Magnetglove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    ksys::act::ModelBindInfo _38;
};
KSYS_CHECK_SIZE_NX150(Magnetglove, 0xd8);

}  // namespace uking::ai

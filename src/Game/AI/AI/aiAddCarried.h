#pragma once

#include "Game/AI/AI/aiAddCarriedBase.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actModelBindInfo.h"

namespace uking::ai {

class AddCarried : public AddCarriedBase {
    SEAD_RTTI_OVERRIDE(AddCarried, AddCarriedBase)
public:
    explicit AddCarried(const InitArg& arg);
    ~AddCarried() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    ksys::act::ModelBindInfo _c0;
};
KSYS_CHECK_SIZE_NX150(AddCarried, 0x160);

}  // namespace uking::ai

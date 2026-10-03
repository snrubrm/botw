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

    ksys::act::ModelBindInfo* m35() override { return &_c0; }
    void m36() override;
    void m37(const sead::Matrix34f& mtx) override { _c0._68 = mtx; }

protected:
    ksys::act::ModelBindInfo _c0;
};
KSYS_CHECK_SIZE_NX150(AddCarried, 0x160);

}  // namespace uking::ai

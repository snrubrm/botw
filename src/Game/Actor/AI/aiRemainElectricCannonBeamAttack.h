#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Utils/Thread/MessageTransceiverTxOnly.h"

namespace uking::ai {

class RemainElectricCannonBeamAttack : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(RemainElectricCannonBeamAttack, ksys::act::ai::Ai)
public:
    explicit RemainElectricCannonBeamAttack(const InitArg& arg);
    ~RemainElectricCannonBeamAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    void sub_710053E864();

protected:
    ksys::act::BaseProcLink _38;
    ksys::act::BaseProcLink _48;
    ksys::MessageTransceiverTxOnly _58{mActor};
};
KSYS_CHECK_SIZE_NX150(RemainElectricCannonBeamAttack, 0xa8);

}  // namespace uking::ai

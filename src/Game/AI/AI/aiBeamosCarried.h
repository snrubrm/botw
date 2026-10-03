#pragma once

#include "Game/AI/AI/aiAddCarried.h"
#include "Game/AI/aiUnk_71023da520.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class BeamosCarried : public AddCarried {
    SEAD_RTTI_OVERRIDE(BeamosCarried, AddCarried)
public:
    explicit BeamosCarried(const InitArg& arg);
    ~BeamosCarried() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    // aitree_variable at offset 0x160
    void* mBeamActorLink_a{};
    Unk_71000b0800<Unk_71023da520> _168;
};
KSYS_CHECK_SIZE_NX150(BeamosCarried, 0x170);

}  // namespace uking::ai

#pragma once

#include "Game/AI/Action/actionAirOctaFloatBase.h"
#include "Game/AI/aiUnk_7100D3D3A8.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AirOctaFloat : public AirOctaFloatBase {
    SEAD_RTTI_OVERRIDE(AirOctaFloat, AirOctaFloatBase)
public:
    explicit AirOctaFloat(const InitArg& arg);
    ~AirOctaFloat() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message* message) override;

protected:
    void calc_() override;

    Unk_7100d3d3a8 _1d0;
    void* _1f0 = nullptr;
    f32 _1f8 = 0.0f;
};
KSYS_CHECK_SIZE_NX150(AirOctaFloat, 0x200);

}  // namespace uking::action

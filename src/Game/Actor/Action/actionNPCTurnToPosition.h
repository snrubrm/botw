#pragma once

#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/System/VFRValue.h"
#include "KingSystem/Utils/Types.h"

namespace uking::action {

class NPCTurnToPosition : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(NPCTurnToPosition, ksys::act::ai::Action)
public:
    explicit NPCTurnToPosition(const InitArg& arg);
    ~NPCTurnToPosition() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    float* mPosX_d{};
    // dynamic_param at offset 0x28
    float* mPosY_d{};
    // dynamic_param at offset 0x30
    float* mPosZ_d{};
    sead::Vector3f _38;
    bool _44 = false;
    bool _45 = false;
    sead::Vector3f _48;
    bool _54 = false;
    sead::Vector3f _58;
    ksys::Timer _64{};
    ksys::VFRVec3f _70;
};
KSYS_CHECK_SIZE_NX150(NPCTurnToPosition, 0x98);

}  // namespace uking::action

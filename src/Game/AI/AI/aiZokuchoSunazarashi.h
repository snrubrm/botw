#pragma once

#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Utils/Thread/MessageTransceiverTxOnly.h"

namespace uking::ai {

class ZokuchoSunazarashi : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(ZokuchoSunazarashi, ksys::act::ai::Ai)
public:
    explicit ZokuchoSunazarashi(const InitArg& arg);
    ~ZokuchoSunazarashi() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mPlayerLostDis_s{};
    // static_param at offset 0x40
    const float* mLeadPlayerAngle_s{};
    // static_param at offset 0x48
    const float* mMoveTargetDist_s{};
    // static_param at offset 0x50
    const float* mStopMoveDist_s{};
    // static_param at offset 0x58
    const float* mStayAwayDist_s{};
    ksys::act::BaseProcHandle _60;
    ksys::act::BaseProcLink _70;
    ksys::act::BaseProcLink _80;
    bool _90 = false;
    bool _91 = false;
    bool _92 = false;
    sead::Vector3f _94 = sead::Vector3f::zero;
    u32 _a0 = 0;
    u32 _a4 = 0;
    u32 _a8 = 0;
    ksys::MessageTransceiverTxOnly _b0{mActor};
};
KSYS_CHECK_SIZE_NX150(ZokuchoSunazarashi, 0x100);

}  // namespace uking::ai

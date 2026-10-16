#pragma once

#include <math/seadMatrix.h>
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class SiteBossThrowIceRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SiteBossThrowIceRoot, ksys::act::ai::Ai)
public:
    explicit SiteBossThrowIceRoot(const InitArg& arg);
    ~SiteBossThrowIceRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    // 0x7100599ef4: changes to the "弾発射" child
    void sub_7100599EF4(const sead::Vector3f& pos);
    // static_param at offset 0x38
    const int* mIgnitionNum_s{};
    // static_param at offset 0x40
    sead::SafeString mThrowActorName_s{};
    // dynamic_param at offset 0x50
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x58
    ksys::act::BaseProcLink* mTargetActor_d{};
    bool _60 = false;
    /* 0x64 */ sead::Matrix33f _64;  // the turning rotation (calc_; not initialised by the ctor)
    /* 0x88 */ ksys::Timer _88{0, 0, 0};
};
KSYS_CHECK_SIZE_NX150(SiteBossThrowIceRoot, 0x98);

}  // namespace uking::ai

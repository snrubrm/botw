#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class SiteBossLswordTornadoRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SiteBossLswordTornadoRoot, ksys::act::ai::Ai)
public:
    explicit SiteBossLswordTornadoRoot(const InitArg& arg);
    ~SiteBossLswordTornadoRoot() override;
    bool isChangeable() const override { return true; }

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    void sub_710057DD54();

protected:
    // 0x710057e398: throws the big flame ball
    void sub_710057E398();
    // 0x710057e4f0: changes to the "待機" child
    void sub_710057E4F0();
    // dynamic_param at offset 0x38
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x40
    sead::Vector3f* mDestPos_d{};
    // dynamic_param at offset 0x48
    ksys::act::BaseProcLink* mTargetActor_d{};
    /* 0x50 */ sead::Matrix33f _50;  // the turning rotation (calc_)
    u8 _74[0x78 - 0x74];
    ksys::act::BaseProcHandle _78;
    ksys::Timer _88{0, 0, 0};
};
KSYS_CHECK_SIZE_NX150(SiteBossLswordTornadoRoot, 0x98);

}  // namespace uking::ai

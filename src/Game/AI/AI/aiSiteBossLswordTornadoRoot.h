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
    void leave_() override;
    void loadParams_() override;

    void sub_710057DD54();

protected:
    // 0x710057e4f0: changes to the "待機" child
    void sub_710057E4F0();
    // dynamic_param at offset 0x38
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x40
    sead::Vector3f* mDestPos_d{};
    // dynamic_param at offset 0x48
    ksys::act::BaseProcLink* mTargetActor_d{};
    u8 _50[0x78 - 0x50];  // not used by this class
    ksys::act::BaseProcHandle _78;
    ksys::Timer _88{0, 0, 0};
};
KSYS_CHECK_SIZE_NX150(SiteBossLswordTornadoRoot, 0x98);

}  // namespace uking::ai

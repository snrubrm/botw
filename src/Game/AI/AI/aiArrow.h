#pragma once

#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::ai {

class Arrow : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(Arrow, ksys::act::ai::Ai)
public:
    explicit Arrow(const InitArg& arg);
    ~Arrow() override;
    bool isChangeable() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    virtual void m34();
    virtual void m35();
    virtual void m36();
    virtual void m37();
    virtual bool m38();
    virtual void m39();
    virtual void m40(ksys::act::BaseProc* proc);

    void sub_7100463940();
    // 0x71004682cc: kills the ELink event of _170 (if it is still the one that was emitted).
    void sub_71004682CC();
    void spawnElectricWaterBall();  // CSV name (aiArrowSpawnElectricWaterBall)

protected:
    sead::Vector3f _38{0, 0, 0};
    u32 _44 = 0;
    u64 _48 = 0;
    sead::SafeString _50 = sead::SafeString::cEmptyString;
    ksys::Timer _60{0, 0};
    ksys::Timer _6c{0, 0};
    ksys::Timer _78{0, 0};
    ksys::Timer _84{0.1f, 0.1f};
    ksys::Timer _90{0, 0};
    s32 _9c = 19;
    const f32* mStickTime_s = nullptr;
    const f32* mGroundHitTime_s = nullptr;
    const s32* mKillFireTime_s = nullptr;
    bool _b8 = false;
    bool _b9 = false;
    bool _ba = false;
    bool _bb = false;
    bool _bc = false;
    bool _bd = false;
    bool _be = false;
    f32 _c0 = 1.0f;
    ksys::act::BaseProcLink _c8;
    bool _d8 = false;
    u32 _dc = 0;
    u32 _e0 = 0;
    u32 _e4 = 0;
    u32 _e8 = 0;
    bool _ec = false;
    Unk_71012419b4 _f0;
    Unk_71012419b4 _110;
    Unk_71012419b4 _130;
    Unk_71012419b4 _150;
    Unk_71012419b4 _170;
    void* _190;
    ksys::act::BaseProcLink _198;
    ksys::act::BaseProcHandle _1a8;
    Unk_71024013b8 _1b8{mActor, 0x80000bb};
    u32 _1d0 = 0;
    u32 _1d4 = 0;
};
KSYS_CHECK_SIZE_NX150(Arrow, 0x1d8);

}  // namespace uking::ai

#pragma once

#include "Game/AI/AI/aiCameraEvent.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include <prim/seadBitFlag.h>
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace uking::ai {

class CameraEventTalk : public CameraEvent {
    SEAD_RTTI_OVERRIDE(CameraEventTalk, CameraEvent)
public:
    explicit CameraEventTalk(const InitArg& arg);
    ~CameraEventTalk() override = default;

    bool isFinished() const override;
    void m40(ksys::act::ai::InlineParamPack* params) override;
    void m41() override;

    void sub_710078E964();

    virtual u32 m44() { return 1; }
    virtual f32 m45();
    virtual bool m46();
    virtual f32 m47() { return -1.0f; }
    virtual bool m48();
    virtual void m49() {}
    virtual void m50();
    virtual void m51(ksys::act::ai::InlineParamPack* params) {}
    virtual void m52(ksys::act::ai::InlineParamPack* params) {}

protected:
    ksys::act::BaseProcLink _48;
    u8 _58 = true;
    s32 _5c = 2;
    sead::BitFlag8 _60;
    sead::BitFlag8 _61;
    u8 _62 = 0;  // saturating counters
    u8 _63 = 0;
};

}  // namespace uking::ai

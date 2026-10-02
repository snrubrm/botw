#pragma once

#include "Game/AI/AI/aiCameraEvent.h"
#include "KingSystem/ActorSystem/actAiAi.h"
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

    virtual bool m44() { return true; }
    virtual f32 m45();
    virtual bool m46();
    virtual f32 m47() { return -1.0f; }
    virtual bool m48();
    virtual void m49() {}
    virtual void m50();
    virtual void m51() {}
    virtual void m52(ksys::act::ai::InlineParamPack* params) {}

protected:
    ksys::act::BaseProcLink _48;
    bool _58 = true;
    s32 _5c = 2;
    bool _60 = false;
    bool _61 = false;
    u8 _62 = 0;
    bool _63 = false;
};

}  // namespace uking::ai

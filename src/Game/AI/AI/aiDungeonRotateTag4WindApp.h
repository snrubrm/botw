#pragma once

#include "Game/AI/AI/aiWholeDungeonRotateTag.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class DungeonRotateTag4WindApp : public WholeDungeonRotateTag {
    SEAD_RTTI_OVERRIDE(DungeonRotateTag4WindApp, WholeDungeonRotateTag)
public:
    explicit DungeonRotateTag4WindApp(const InitArg& arg);
    ~DungeonRotateTag4WindApp() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    void m39() override;
    void m40() override;
    void m41() override;
    void m43(int state) override;
    void m44() override;
    void m45() override;

protected:
};

}  // namespace uking::ai

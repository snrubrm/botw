#pragma once

#include "Game/AI/AI/aiDragonRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class DragonFireRoot : public DragonRoot {
    SEAD_RTTI_OVERRIDE(DragonFireRoot, DragonRoot)
public:
    explicit DragonFireRoot(const InitArg& arg);
    ~DragonFireRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    void calc_() override;
    void m42() override;
    void m44(const sead::Vector3f& pos) override;

    void sub_7100367FE4();

protected:
};

}  // namespace uking::ai

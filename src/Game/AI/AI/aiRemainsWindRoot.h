#pragma once

#include "Game/AI/AI/aiRemainsRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace uking::ai {

class RemainsWindRoot : public RemainsRoot {
    SEAD_RTTI_OVERRIDE(RemainsWindRoot, RemainsRoot)
public:
    explicit RemainsWindRoot(const InitArg& arg);
    ~RemainsWindRoot() override;

    bool reenter_(ksys::act::ai::ActionBase* other, bool x) override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    void m34() override;
    void m35(bool x) override;
    void m36() override;
    virtual void m37();

protected:
    ksys::act::BaseProcLink _50;
    void* _60{};
    void* _68{};
    bool _70 = false;
};
KSYS_CHECK_SIZE_NX150(RemainsWindRoot, 0x78);

}  // namespace uking::ai

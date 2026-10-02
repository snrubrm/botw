#pragma once

#include "Game/AI/AI/aiSimpleWildlifeRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class InsectRoot : public SimpleWildlifeRoot {
    SEAD_RTTI_OVERRIDE(InsectRoot, SimpleWildlifeRoot)
public:
    explicit InsectRoot(const InitArg& arg);
    ~InsectRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    void calc_() override;
    bool handleMessage_(const ksys::Message& message) override;

    bool m34() override;
    bool m35() override;
    void m40() override;

protected:
    // static_param at offset 0xf8
    const bool* mIsEscapeInWater_s{};
    ksys::Timer _100{};
    bool _10c = false;
};
KSYS_CHECK_SIZE_NX150(InsectRoot, 0x110);

}  // namespace uking::ai

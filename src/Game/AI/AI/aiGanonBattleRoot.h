#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GanonBattleRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GanonBattleRoot, ksys::act::ai::Ai)
public:
    explicit GanonBattleRoot(const InitArg& arg);
    ~GanonBattleRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    void sub_71003E3644();
    void sub_71003E3A3C(const sead::Vector3f& position);
    void sub_71003E3BA0(const sead::Vector3f& position);
    // 0x71003e3cfc (placeholder name)
    void changeToStateChange(const sead::Vector3f& position);

    bool _38{};
};

}  // namespace uking::ai

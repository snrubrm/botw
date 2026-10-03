#pragma once

#include "Game/gameNpcShopData.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NPCPurchase : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(NPCPurchase, ksys::act::ai::Action)
public:
    explicit NPCPurchase(const InitArg& arg);
    ~NPCPurchase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;

protected:
    void calc_() override;

    NpcShopData _20;
    bool _40 = false;
    bool _41 = false;
    u64 _48 = 0;
};

}  // namespace uking::action

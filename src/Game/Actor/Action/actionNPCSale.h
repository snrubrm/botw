#pragma once

#include "Game/gameNpcShopData.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NPCSale : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(NPCSale, ksys::act::ai::Action)
public:
    explicit NPCSale(const InitArg& arg);
    ~NPCSale() override;

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

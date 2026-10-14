#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class DungeonRotateTagInOrder : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(DungeonRotateTagInOrder, ksys::act::ai::Ai)
public:
    explicit DungeonRotateTagInOrder(const InitArg& arg);

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    bool _38 = false;
    // static_param at offset 0x40
    const bool* mRotateTurnOn_s{};
};

}  // namespace uking::ai

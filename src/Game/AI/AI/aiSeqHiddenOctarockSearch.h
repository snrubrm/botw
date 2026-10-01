#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SeqHiddenOctarockSearch : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SeqHiddenOctarockSearch, ksys::act::ai::Ai)
public:
    explicit SeqHiddenOctarockSearch(const InitArg& arg);
    ~SeqHiddenOctarockSearch() override;

    bool isChangeable() const override { return false; }

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    bool _38 = false;
    bool _39 = false;
};
KSYS_CHECK_SIZE_NX150(SeqHiddenOctarockSearch, 0x40);

}  // namespace uking::ai

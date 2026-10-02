#pragma once

#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "Game/AI/Action/actionNoticeTurn.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HoverNoticeTurn : public NoticeTurn {
    SEAD_RTTI_OVERRIDE(HoverNoticeTurn, NoticeTurn)
public:
    explicit HoverNoticeTurn(const InitArg& arg);
    ~HoverNoticeTurn() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    void m32() override;

    ksys::act::Unk_710072AFD0 _80;
};

}  // namespace uking::action

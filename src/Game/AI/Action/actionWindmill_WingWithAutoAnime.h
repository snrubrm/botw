#pragma once

#include "Game/AI/Action/actionWindmill_Wing.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class Windmill_WingWithAutoAnime : public Windmill_Wing {
    SEAD_RTTI_OVERRIDE(Windmill_WingWithAutoAnime, Windmill_Wing)
public:
    explicit Windmill_WingWithAutoAnime(const InitArg& arg);
    ~Windmill_WingWithAutoAnime() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    void m32(bool a1) override;
    void m33() override;
};

}  // namespace uking::action

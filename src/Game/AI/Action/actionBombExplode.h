#pragma once

#include "Game/AI/Action/actionActionEx.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace ksys::phys {
class RigidBody;
}

namespace uking::action {

class BombExplode : public ActionEx {
    SEAD_RTTI_OVERRIDE(BombExplode, ActionEx)
public:
    explicit BombExplode(const InitArg& arg);
    ~BombExplode() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    float _1c = 0.0f;
    float _20 = 0.0f;
    float _24 = -1.0f;
    void* _28{};
    void* _30{};
    void* _38{};
    void* _40{};
    ksys::phys::RigidBody* _48{};
    float _50 = 0.0f;
    float _54 = 0.0f;
    float _58 = 0.0f;
};

}  // namespace uking::action

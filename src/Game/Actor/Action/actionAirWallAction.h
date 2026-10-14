#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace ksys::phys {
class RigidBody;
}

namespace uking::action {

class AirWallAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(AirWallAction, ksys::act::ai::Action)
public:
    explicit AirWallAction(const InitArg& arg);

protected:
    void calc_() override;

    // 0x710008a8c8 (placeholder name; does not use `this`).
    bool sub_710008A8C8(ksys::phys::RigidBody* body);
};

}  // namespace uking::action

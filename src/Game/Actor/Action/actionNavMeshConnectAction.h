#pragma once

#include <math/seadMatrix.h>
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NavMeshConnectAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(NavMeshConnectAction, ksys::act::ai::Action)
public:
    explicit NavMeshConnectAction(const InitArg& arg);
    ~NavMeshConnectAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    sead::Matrix34f _1c = sead::Matrix34f::ident;
    f32 _4c = 0;
    bool _50 = false;
    bool _51 = false;
};
KSYS_CHECK_SIZE_NX150(NavMeshConnectAction, 0x58);

}  // namespace uking::action

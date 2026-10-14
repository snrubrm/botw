#pragma once

#include "Game/Actor/Area/Action/actionAreaActionBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AreaBottomTag : public AreaActionBase {
    SEAD_RTTI_OVERRIDE(AreaBottomTag, AreaActionBase)
public:
    explicit AreaBottomTag(const InitArg& arg);
    ~AreaBottomTag() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    bool m15(const ksys::act::ActorLinkConstDataAccess& accessor) override;
    sead::Buffer<Payload>* m6() override { return &_38; }
    bool m16(ksys::phys::RigidBody* body) override;

    sead::Buffer<Payload> _38;
};
KSYS_CHECK_SIZE_NX150(AreaBottomTag, 0x48);

}  // namespace uking::action

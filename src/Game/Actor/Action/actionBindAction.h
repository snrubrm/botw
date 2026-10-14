#pragma once

#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actModelBindInfo.h"

namespace ksys::act {
class Actor;
class BaseProc;
}

namespace uking::action {

class BindAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(BindAction, ksys::act::ai::Action)
public:
    explicit BindAction(const InitArg& arg);
    ~BindAction() override = default;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    virtual void m32() = 0;
    // The actor to bind to.
    virtual ksys::act::Actor* m33() = 0;
    // Binds the actor to m33()'s NodeName bone (with RotOffset / TransOffset).
    virtual void m34();
    // Unbinds the actor.
    virtual void m35();

    // dynamic_param at offset 0x20
    sead::SafeString* mNodeName_d{};
    // dynamic_param at offset 0x28
    sead::Vector3f* mRotOffset_d{};
    // dynamic_param at offset 0x30
    sead::Vector3f* mTransOffset_d{};
    ksys::act::ModelBindInfo _38;
};
KSYS_CHECK_SIZE_NX150(BindAction, 0xd8);

}  // namespace uking::action

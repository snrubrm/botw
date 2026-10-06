#pragma once

#include <math/seadMatrix.h>
#include "KingSystem/ActorSystem/actAiAction.h"

namespace ksys::as {
class ASList;
}

namespace uking::action {

class TurnToActorBase : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(TurnToActorBase, ksys::act::ai::Action)
public:
    explicit TurnToActorBase(const InitArg& arg);
    ~TurnToActorBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    // inline in the original (emitted out of line in this TU); the arguments are what calc_ passes
    virtual void m32(ksys::as::ASList* as_list, ksys::act::Actor* actor) {}
    // slots 33-38 are pure virtual in the base vtable (the class is abstract)
    virtual sead::Matrix34f m33() = 0;
    virtual f32 m34() = 0;
    virtual int m35() = 0;
    virtual int m36() = 0;
    virtual bool m37() = 0;
    virtual const sead::SafeString& m38() = 0;

    /* 0x1c */ bool _1c = false;
};

}  // namespace uking::action

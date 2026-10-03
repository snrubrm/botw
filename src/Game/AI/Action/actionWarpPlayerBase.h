#pragma once

#include <math/seadMatrix.h>
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class WarpPlayerBase : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(WarpPlayerBase, ksys::act::ai::Action)
public:
    explicit WarpPlayerBase(const InitArg& arg);
    ~WarpPlayerBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    virtual void m32();
    virtual bool m33();
    virtual int m34();

    sead::Matrix34f _1c = sead::Matrix34f::ident;
    sead::Vector3f _4c = sead::Vector3f::ones;
    bool _58 = false;
    bool _59 = false;
    f32 _5c = 0.0f;
};

}  // namespace uking::action

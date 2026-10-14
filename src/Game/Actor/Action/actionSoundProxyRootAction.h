#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"
#include <xlink2/xlink2HandleSLink.h>

namespace uking::act { class SoundProxy; }
namespace ksys::map { class Object; }

namespace uking::action {

class SoundProxyRootAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SoundProxyRootAction, ksys::act::ai::Action)
public:
    explicit SoundProxyRootAction(const InitArg& arg);
    ~SoundProxyRootAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    void sub_7100FF1DB4();
    bool sub_7100FF1E5C(ksys::map::Object* object, sead::Heap* heap);
    bool _1c = false;
    uking::act::SoundProxy* _20{};
    sead::Heap* _28{};
    int _30 = 0;
    xlink2::HandleSLink* _38{};
};

}  // namespace uking::action

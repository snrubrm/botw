#pragma once

#include <random/seadGlobalRandom.h>
#include "KingSystem/System/Timer.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class InDemoSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(InDemoSelect, ksys::act::ai::Ai)
public:
    explicit InDemoSelect(const InitArg& arg);
    ~InDemoSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    // Inline-only in the original (enter_ and calc_ inline the same sequence); the name is a guess.
    void resetDelay() {
        _70 = _74 == _78 ? _74 : sead::GlobalRandom::instance()->getS32Range(_74, _78);
        _7c = false;
    }
    // Inline-only in the original; the name is a guess. Returns true when the delay ran out.
    bool updateDelay() {
        f32* delay = &_70;
        if (_7c)
            ksys::Timer::update(delay, -1.0f);
        else
            _7c = true;
        return *delay < 0;
    }

    // static_param at offset 0x38
    const int* mDemoRetDelayMax_s{};
    // static_param at offset 0x40
    const bool* mOtherDemoNoRun_s{};
    // static_param at offset 0x48
    const bool* mForceChangeDemo_s{};
    // static_param at offset 0x50
    sead::SafeString mDemoFile_s{};
    // static_param at offset 0x60
    sead::SafeString mDemoEntryPoint_s{};
    f32 _70{};
    int _74{};
    int _78{};
    bool _7c{};
};

}  // namespace uking::ai

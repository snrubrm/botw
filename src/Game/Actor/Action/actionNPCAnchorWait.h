#pragma once

#include <thread/seadCriticalSection.h>
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::act {
class NPC;
}

namespace uking::action {

class NPCAnchorWait : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(NPCAnchorWait, ksys::act::ai::Action)
public:
    explicit NPCAnchorWait(const InitArg& arg);
    ~NPCAnchorWait() override;
    bool handleMessage_(const ksys::Message* message) override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    virtual const char* m32() { return mASName_d.cstr(); }
    // 0x71001f3ae8 (placeholder name): once the NPC's horse has the flag, tells it where the NPC stands.
    void sub_71001F3AE8();

    // dynamic_param at offset 0x20
    bool* mIsRainAnchor_d{};
    // dynamic_param at offset 0x28
    bool* mIsStartSameAS_d{};
    // dynamic_param at offset 0x30
    sead::SafeString mASName_d{};
    uking::act::NPC* _40 = nullptr;
    bool _48 = false;
    // The user data of the message 0x3800005 NPCAnchorWait::calc_ sends (the actor's position, copied
    // under the lock); placeholder name.
    struct Unk_50 {
        sead::CriticalSection mCS;
        sead::Vector3f mPos;
    } _50;
};
KSYS_CHECK_SIZE_NX150(NPCAnchorWait, 0xa0);

}  // namespace uking::action

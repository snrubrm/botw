#pragma once

#include "Game/AI/aiUnk_7102357210.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace uking::action {

class Bolt : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(Bolt, ksys::act::ai::Action)
public:
    explicit Bolt(const InitArg& arg);
    ~Bolt() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message* message) override;

protected:
    void calc_() override;

    // map_unit_param at offset 0x20
    const bool* mIsNoBindAlive_m{};
    ksys::act::BaseProcLink _28;

    // Local listener subclass (own vtable in this TU); message 0x800002a.
    class Listener : public Unk_7102357210 {
    public:
        bool m2(const ksys::Message& message) override {
            if (message.getType() != 0x800002a)
                return false;
            _30 = true;
            _18 = message.getSource();
            return true;
        }
        void m3() override {}
    };

    Listener _38;
};
KSYS_CHECK_SIZE_NX150(Bolt, 0x70);

}  // namespace uking::action

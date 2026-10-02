#pragma once

#include <prim/seadBitFlag.h>
#include "Game/AI/aiUnk_7102357210.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::ai {

// vtable 0x710241ff70 (SimpleLineBeam::_38; D0 0x710056f738, m2 0x710056f52c): message 0x8000038.
class Unk_710241ff70 : public Unk_7102357210 {
public:
    bool m2(const ksys::Message& message) override {
        if (message.getType().value != 0x8000038)
            return false;
        _30 = true;
        _18 = message.getSource();
        return true;
    }
    void m3() override {}
};

// vtable 0x710241ffa0 (SimpleLineBeam::_70; D0 0x710056f780, m2 0x710056f49c): message 0x8000039.
class Unk_710241ffa0 : public Unk_7102357210 {
public:
    bool m2(const ksys::Message& message) override {
        if (message.getType().value != 0x8000039)
            return false;
        _30 = true;
        _18 = message.getSource();
        return true;
    }
    void m3() override {}
};

class SimpleLineBeam : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SimpleLineBeam, ksys::act::ai::Ai)
public:
    explicit SimpleLineBeam(const InitArg& arg);
    ~SimpleLineBeam() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message& message) override;

protected:
    Unk_710241ff70 _38;
    Unk_710241ffa0 _70;
    sead::BitFlag16 _a8;
};
KSYS_CHECK_SIZE_NX150(SimpleLineBeam, 0xb0);

}  // namespace uking::ai

#pragma once

#include "Game/Actor/actGuardian.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GuardianAI : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GuardianAI, ksys::act::ai::Ai)
public:
    explicit GuardianAI(const InitArg& arg);
    ~GuardianAI() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    // 0x710040da6c (lane1 s21): the actor as a Guardian (DynamicCast), or nullptr.
    act::Guardian* sub_710040DA6C();

    // The Guardian helpers below act on the actor as a Guardian (DynamicCast) or, failing that, on its connected
    // calc parent (0x710040daf8 / 0x710040dc54 return the Guardian's _15a8 / _15b0, nullptr if there is none).
    act::Guardian::Unk15a8* sub_710040DAF8();
    act::Guardian::Unk1* sub_710040DC54();
    // 0x710040dc50 / 0x710040ddac: out-of-line tail calls to sub_710040DAF8 / sub_710040DC54 (callers in GuardianRoot / GuardianTargetLost).
    act::Guardian::Unk15a8* sub_710040DC50();
    act::Guardian::Unk1* sub_710040DDAC();
    // 0x710040ddb0: Guardian::sub_7100035A90(state); 0x710040de48: Guardian::sub_7100034514(on).
    void sub_710040DDB0(s32 state);
    void sub_710040DE48(bool on);
    // 0x710040dee0 / 0x710040df74: Guardian::sub_710003B43C / sub_710003B4C8 (false for other actors).
    bool sub_710040DEE0();
    bool sub_710040DF74();
    // 0x710040e008 / 0x710040e048: copy the vector at _15a8 + 0x3c / + 0x30 (false without the structure).
    bool sub_710040E008(sead::Vector3f* out);
    bool sub_710040E048(sead::Vector3f* out);
    // 0x710040e088: Guardian::sub_710003B090(value).
    void sub_710040E088(u32 value);

protected:
};

}  // namespace uking::ai

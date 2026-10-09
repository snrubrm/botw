#pragma once

#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include <container/seadSafeArray.h>
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class BowShoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(BowShoot, ksys::act::ai::Ai)
public:
    explicit BowShoot(const InitArg& arg);
    ~BowShoot() override;
    bool isChangeable() const override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    bool handleMessage_(const ksys::Message* message) override;

    void sub_710033BB98();

protected:
    void calc_() override;

    // 0x7100338f38 (declaration only): `a1` = the equipped arrow differs from the remembered one.
    void sub_7100338F38(bool a1);
    // 0x7100339d04 / 0x7100339f94 / 0x710033a1f0 / 0x710033a350 / 0x710033a690 (declaration only).
    void sub_7100339D04();
    void sub_7100339F94();
    void sub_710033A1F0();
    bool sub_710033A350();
    void sub_710033A690();
    // 0x710033aa88 / 0x710033b16c (declaration only): `value` is the timer value of the shot.
    void sub_710033AA88(f32 value);
    void sub_710033B16C(f32 value);
    // 0x710033bdb4 (declaration only): changes the child to `name` (resets the shot state).
    void sub_710033BDB4(const sead::SafeString& name);
    // Native mode dispatcher at 0x710033BF8C consumes the low byte (modes 0 to 3).
    void sub_710033BF8C(u8 mode);
    void sub_710033C2C0(const sead::SafeString& arrow_name, s32 count);
    // 0x710033c888 (declaration only).
    s32 sub_710033C684();
    bool sub_710033C888();

    /* 0x38 */ bool _38 = false;
    /* 0x39 */ bool _39 = false;
    // The arrow-holding actors of the shots
    /* 0x40 */ sead::SafeArray<ksys::act::BaseProcHandle, 20> mHandles;
    /* 0x180 */ ksys::Timer _180{0, 0};
    // Number of shots fired (mode) and the number to fire
    /* 0x18c */ s32 _18c{};
    /* 0x190 */ s32 _190{};
    /* 0x194 */ sead::Vector3f _194{0, 0, 0};
    /* 0x1a0 */ sead::Vector3f _1a0{0, 0, 0};
    /* 0x1ac */ sead::Vector3f _1ac{0, 0, 0};
    /* 0x1b8 */ u16 _1b8{};
    /* 0x1ba */ u8 _1ba = 0xff;
    /* 0x1c0 */ sead::FixedSafeString<32> mArrowName{sead::SafeString::cEmptyString};
};
KSYS_CHECK_SIZE_NX150(BowShoot, 0x1f8);

}  // namespace uking::ai

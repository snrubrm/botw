#pragma once

#include "Game/gameUnkRttiClasses.h"
#include "KingSystem/Utils/Types.h"

KSYS_CHECK_SIZE_NX150(Unk_7102457a80, 0x48);
KSYS_CHECK_SIZE_NX150(Unk_7102457ac0, 0x50);

// Native callback checker vtables 0x7102457b00 / 0x7102457b28 / 0x7102457b50.
// Constructor calls and the state copy at 0x7100786e14 prove the common 0x50-byte layout.
class Unk_7102457b00 {
public:
    explicit Unk_7102457b00(uking::action::CameraLockOnBase* owner) : _8(owner) {}
    virtual ~Unk_7102457b00() = default;
    virtual u32 m2(uking::act::Unk_71009214b8* state) { return 0; }
    u32 sub_7100786E14(const uking::act::Unk_71009214b8& state);

    uking::action::CameraLockOnBase* _8;
    uking::act::Unk_71009214b8 _10;
    // Native checker results are 0, 1 and 2; copied to this full 32-bit result field.
    u32 _48 = 0;
};
KSYS_CHECK_SIZE_NX150(Unk_7102457b00, 0x50);

class Unk_7102457b28 : public Unk_7102457b00 {
public:
    explicit Unk_7102457b28(uking::action::CameraLockOnBase* owner);
    ~Unk_7102457b28() override = default;
    u32 m2(uking::act::Unk_71009214b8* state) override { return 0; }
};

class Unk_7102457b50 : public Unk_7102457b00 {
public:
    explicit Unk_7102457b50(uking::action::CameraLockOnBase* owner);
    ~Unk_7102457b50() override = default;
    // 0x7100786f38; blocked on the still-unproved camera collision utility signature.
    u32 m2(uking::act::Unk_71009214b8* state) override;
};

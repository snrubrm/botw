#include "KingSystem/XLink/xlinkXLink.h"

#include "KingSystem/ActorSystem/Profiles/actPlayerLink.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actReaction.h"

namespace ksys::xlink {

// The footstep reaction speed thresholds, directly before the bone-name array in .rodata
// (0x7102516320). Defined in xlinkXLink.cpp with hidden visibility so the two uses load it.
extern const f32 sUnk_7102516320[2] __attribute__((visibility("hidden")));

namespace {
const char* const sUnk_71025162F8[] = {"Toe_L", "Toe_R", "Wrist_L", "Wrist_R"};
const char* const sUnk_7102516328[] = {"Ankle_L", "Ankle_R", "Wrist_L", "Wrist_R"};
}  // namespace

void Unk_710123830c::sub_71012372EC() {
    _1c.reset(1);
}

void Unk_710123830c::sub_710123827C(bool value) {
    if (_16.isOn(0x100))
        _1c.change(0x100, value);
}

void Unk_710123830c::sub_71012381A8(const char* key, s32 duration) {
    if (!key)
        return;
    _1c.set(1);
    mOverrideKey.copy(key);
    mOverrideDuration = u16(duration);
}

// NON_MATCHING: scale stays in a register and the reaction switch uses a different test order.
void Unk_710123830c::sub_7101236520(s32 reaction, s32 scale, s32 duration) {
    mReaction = reaction;
    _1c.set(4);
    switch (scale) {
    case 1:
        mReactionScale = 1.1f;
        break;
    case 2:
        mReactionScale = 10.1f;
        break;
    case 3:
        mReactionScale = 100.1f;
        break;
    default:
        mReactionScale = 0.0f;
        break;
    }
    mOverrideDuration = u16(duration);
    switch (reaction) {
    case 19:
        _16.reset(0x40);
        break;
    case 20:
        _16.reset(1);
        break;
    case 24:
        _16.reset(1);
        mBoneNames = sUnk_71025162F8;
        break;
    }
    _1c.set(0x40);
}

// NON_MATCHING: reaction switch order and the bone-name array address calculation differ.
void Unk_710123830c::sub_71012370A8() {
    switch (mReaction) {
    case 19:
        _16.set(0x40);
        break;
    case 24:
        mBoneNames = sUnk_7102516328;
        [[fallthrough]];
    case 20:
        _16.set(1);
        break;
    }
    _1c.reset(4);
    mReaction = mDefaultReaction;
    mReactionScale = 10.0f;
    mOverrideDuration = 0;
}

Unk_710123830c::~Unk_710123830c() = default;

void Unk_710123830c::sub_7101237DD0() {
    bool riding = false;
    if (auto* link = mActor->m129())
        riding = link->isRidingHorse();

    if (!riding && mActor->getVelocity().length() > 0.001f) {
        if (_cc > sUnk_7102516320[0]) {
            _18 = (_18 & ~u16(3)) | 1;
            return;
        }
        if (_c8 > sUnk_7102516320[1]) {
            act::Reaction::instance()->sub_7100EC2980(mActor);
            _18 = (_18 & ~u16(3)) | 2;
            return;
        }
    }

    const u16 flags = _18;
    if ((flags & 1) == 0)
        _18 = flags | 1;
    else
        _18 = flags & ~u16(2);
}

}  // namespace ksys::xlink

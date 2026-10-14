#include "KingSystem/XLink/xlinkXLink.h"

namespace ksys::xlink {

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

}  // namespace ksys::xlink

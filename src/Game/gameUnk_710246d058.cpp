#include "Game/gameUnk_710246d058.h"
#include "Game/gameUnk_71024739f8.h"
#include <container/seadBuffer.h>
#include <cmath>
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"

namespace uking {

Unk_710246d448::~Unk_710246d448() = default;

sead::SafeString Unk_710246d448::sub_7100D9DF34() const {
    return sead::SafeString::cEmptyString;
}

void Unk_710246d448::sub_7100D9DF54() {
    auto* input = _1f0;
    if (input) {
        input->update();
        mPadHold.set(input->getHold());
        if (input->sub_710090DD88()) {
            mPointer = input->getPointerState().position;
            setPointerWithBound_(input->getPointerState()._0, input->getPointerState()._1,
                                 input->getPointerState().position);
        }
        if (input->sub_710090DD9C()) {
            if (input->getSticks()[0].length() > mLeftStick.length())
                mLeftStick = input->getSticks()[0];
            if (input->getSticks()[1].length() > mLeftStick.length())
                mRightStick = input->getSticks()[1];
        }
        mLeftAnalogTrigger = 0.0f;
        mRightAnalogTrigger = 0.0f;
    }
    sub_71008BF838();
}

bool Unk_710246d448::sub_7100D9DF58() {
    if (Root4::instance())
        return Root4::instance()->checkFlag(_1f8);
    return false;
}

void Unk_710246d448::sub_71008BF838() {}

namespace {

// Button mask for each key index (0x710246cfb0).
u32 sUnk_710246cfb0[] = {
    0x1,     0x2,    0x8,    0x10,   0x8,     0x1,     0x8,     0x2,    0x8,    0x2,   0x8,
    0x8,     0x2,    0x4,    0x2,    0x40,    0x1,     0x80,    0x20,   0x8,    0x2,   0x10000,
    0x20000, 0x10000, 0x20000, 0x2,  0x1,     0x2000,  0x4000,  0x4,    0x2,    0x4000, 0x4000,
    0x2000,  0x1,    0x20000, 0x10,  0x20000, 0x1,     0x2,     0x2000,
};

sead::Buffer<u32> sUnk_710246cfa0(41, sUnk_710246cfb0);

}  // namespace

bool Unk_710246d058::playerCheckController(int key) const {
    u32 mask = sUnk_710246cfa0[key];
    if ((mask == 1 << sead::Controller::cPadIdx_X || mask == 1 << sead::Controller::cPadIdx_B) &&
        ksys::gdt::getFlag_JumpButtonChange()) {
        mask = mask == 1 << sead::Controller::cPadIdx_B ? 1 << sead::Controller::cPadIdx_X :
                                                          1 << sead::Controller::cPadIdx_B;
    }
    return isHold(mask);
}

bool Unk_710246d058::controllerCheckPressedMaybe(int key) const {
    u32 mask = sUnk_710246cfa0[key];
    if ((mask == 1 << sead::Controller::cPadIdx_X || mask == 1 << sead::Controller::cPadIdx_B) &&
        ksys::gdt::getFlag_JumpButtonChange()) {
        mask = mask == 1 << sead::Controller::cPadIdx_B ? 1 << sead::Controller::cPadIdx_X :
                                                          1 << sead::Controller::cPadIdx_B;
    }
    return isTrig(mask);
}

f32 Unk_710246d058::sub_71008BD344() const {
    return std::atan2(-getLeftStick().x, getLeftStick().y);
}

f32 Unk_710246d058::sub_71008BD354() const {
    return std::atan2(-getRightStick().x, getRightStick().y);
}

f32 Unk_710246d058::sub_71008BD364() const {
    return getLeftStick().length();
}

f32 Unk_710246d058::sub_71008BD390() const {
    return getRightStick().length();
}

}  // namespace uking

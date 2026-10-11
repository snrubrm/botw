#include "KingSystem/System/SeadController.h"
#include "KingSystem/System/Controller.h"
#include "KingSystem/System/ControllerSnapshot.h"

namespace ksys {

static SeadController* sInstance;

// 0x71011f931c
SeadController* SeadController::getInstance() {
    return sInstance;
}

// 0x71011f9328
void SeadController::setInstance(SeadController* controller) {
    sInstance = controller;
}

u32 SeadController::sub_7100D9D874() const {
    return _1a4;
}

void SeadController::sub_7100D9D8C0(bool on) {
    _188 = on ? (_188 | 0x80) : (_188 & ~0x80);
}

void SeadController::sub_7100D9D8DC(u32 value) {
    _190 = value;
}

void SeadController::sub_7100D9DAC8(u32 value) {
    _194 = value;
}

void SeadController::sub_7100D9DAD8() {
    _188 &= ~0x1;
}

void SeadController::sub_7100D9DAE8() {
    _188 &= ~0x2;
}

void SeadController::sub_7100D9DB04(bool on) {
    _188 = on ? (_188 | 0x10) : (_188 & ~0x10);
}

void SeadController::sub_7100D9DF60() {
    _188 &= ~0x20;
}

void SeadController::sub_7100D9DAF8(SeadController* child) {
    mTreeNode.pushBackChild(&child->mTreeNode);
}

sead::SafeString SeadController::sub_7100D9DF34() const {
    return sead::SafeString::cEmptyString;
}

void SeadController::sub_7100D9DF54() {}

bool SeadController::sub_7100D9DF58() {
    return true;
}

}  // namespace ksys

Unk_71024dd5c8::Unk_71024dd5c8()
    : _8(false), _c(0), _10(0), _14(0.0f), _18(0.0f), _1c(0), _20(0), _24(0),
      _28(sead::Vector2f::zero), _30(sead::Vector2f::zero),
      _38(sead::ControllerBase::cInvalidPointer), _40(sead::ControllerBase::cInvalidPointer),
      _48(sead::ControllerBase::cInvalidPointer), _50(sead::ControllerBase::cInvalidPointer) {}

Unk_71024dd5c8::~Unk_71024dd5c8() = default;

bool Unk_71024dd5c8::sub_7100D9E148() {
    return true;
}

bool Unk_71024dd5c8::sub_7100D9E48C() const {
    return _c & 0x80;
}

const sead::Vector2f& Unk_71024dd5c8::sub_7100D9E498() const {
    if (_24 == 1)
        return _38;
    if (_24 == 2)
        return _40;
    return sead::ControllerBase::cInvalidPointer;
}

Unk_71024dd5a8::~Unk_71024dd5a8() = default;

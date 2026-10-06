#include "KingSystem/System/SeadController.h"

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

}  // namespace ksys

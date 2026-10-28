#include "Game/Framework/gameSystemStruct1.h"
#include <cstring>

namespace uking::frm {

// NON_MATCHING: the target initialises both matrices through an out-of-line memcpy and zeroes the
// tail with an unaligned 8-byte store at +0x8e (a wider store than our four separate tail members
// produce); the order of the first vector copy also differs.
SystemStruct1::SystemStruct1()
    : _8(sead::Vector3f::zero), _14(sead::Vector3f::ex), _20(sead::Vector3f::ey),
      _2c(sead::Vector3f::ez) {
    memcpy(&_38, &sead::Matrix33f::ident, sizeof(sead::Matrix33f));
    memcpy(&_5c, &sead::Matrix33f::ident, sizeof(sead::Matrix33f));
    _80 = false;
    _84 = 2;
    _88 = 0.0f;
    _8c = 0.0f;
    _90 = 0;
    _94 = 0;
}

SystemStruct1* SystemStruct1::sInstance = nullptr;

SystemStruct1* SystemStruct1::getInstance() {
    return sInstance;
}

void SystemStruct1::setInstance(SystemStruct1* instance) {
    sInstance = instance;
}

}  // namespace uking::frm

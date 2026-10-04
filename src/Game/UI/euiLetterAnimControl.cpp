#include "Game/UI/euiLetterAnimControl.h"

namespace eui {

// 0x7100bd92cc
const char* LetterAnimControl::getClassName() const {
    return "LetterAnimControl";
}

// 0x7100bd92d8
LetterAnimControl::LetterAnimControl() = default;

// 0x7100bd9b80
void LetterAnimControl::flushAllowWait() {
    if (_60 != 2)
        _60 = 1;
}

// 0x7100bd94c4
void LetterAnimControl::sub_7100BD94C4(void* a1) {
    _70 = a1;
}

// 0x7100bd94cc
void LetterAnimControl::sub_7100BD94CC(void* a1) {
    _78 = a1;
}

// 0x7100bd9b5c
void LetterAnimControl::sub_7100BD9B5C() {
    _5e = 1;
}

// 0x7100bd9b68
void LetterAnimControl::sub_7100BD9B68(f32 value) {
    _40 = value;
    _44 = value;
}

// 0x7100bd9b74
void LetterAnimControl::sub_7100BD9B74() {
    _60 = 2;
}

}  // namespace eui

#include "Game/UI/euiLetterAnimControl.h"
#include "Game/UI/euiTextBoxEx.h"
#include "Game/UI/euiTagProcessor.h"
#include <heap/seadHeap.h>
#include <cstring>

namespace eui {

// 0x7100bd92cc
const char* LetterAnimControl::getClassName() const {
    return "LetterAnimControl";
}

// 0x7100bd92d8
LetterAnimControl::LetterAnimControl() = default;

// 0x7100bd9330
void LetterAnimControl::reset() {
    _5e = 0;
    _48 = 0;
    _58 = 0;
    _50 = 0;
    _5f &= ~3;
    _61 = 0;
    char16* text = TagProcessor::setAlphaTag(_38, false, 0);
    std::memcpy(text, _30, _5c * sizeof(char16));
    mTextBox->setStringNoPreproces(_38, _5c + 5);
}

// NON_MATCHING: adjacent object-pointer assignments are paired differently.
// 0x7100bd93a4
void LetterAnimControl::initialize(sead::Heap* heap, TextBoxEx* text_box, LayoutEx* layout) {
    if (text_box->GetStringBufferLength() < text_box->mTextLength + 10)
        return;
    mTextBox = text_box;
    mName = text_box->GetName();
    mLayout = layout;
    _5a = text_box->GetStringBufferLength();
    _5c = text_box->mTextLength;
    _30 = static_cast<char16*>(heap->alloc(_5a * sizeof(char16), 8));
    std::memcpy(_30, text_box->mTextBuf, _5c * sizeof(char16));
    _38 = static_cast<char16*>(heap->alloc(_5a * sizeof(char16), 8));
    _5e = 0;
    _48 = 0;
    _58 = 0;
    _50 = 0;
    _5f &= ~3;
    _61 = 0;
    char16* text = TagProcessor::setAlphaTag(_38, false, 0);
    std::memcpy(text, _30, _5c * sizeof(char16));
    mTextBox->setStringNoPreproces(_38, _5c + 5);
}

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

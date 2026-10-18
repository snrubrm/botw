#include "Game/UI/euiLetterAnimControl.h"
#include "Game/UI/euiTextBoxEx.h"
#include "Game/UI/euiTagProcessor.h"
#include "Game/UI/euiMessageString.h"
#include <heap/seadHeap.h>
#include <nn/font/font_Font.h>
#include <algorithm>
#include <cstring>

namespace eui {

// 0x7100bd92cc
const char* LetterAnimControl::getClassName() const {
    return "LetterAnimControl";
}

// 0x7100bd92d8
LetterAnimControl::LetterAnimControl() = default;

// NON_MATCHING: tag dispatch, choice loops and reveal-buffer copies are lowered differently.
// 0x7100bd94d4
void LetterAnimControl::Update(f32 dt) {
    if ((_5f & 1) && _50 > 0.0f)
        _50 = std::max(_50 - dt, 0.0f);
    if (!mTextBox || !_5e)
        return;
    if (_4c > 0.0f) {
        if (_60 != 2) {
            _4c = std::max(_4c - dt, 0.0f);
            return;
        }
        _4c = 0.0f;
    }

    if (_58 < _5c) {
        _54 += _40 * dt;
        f32 width = _48;
        u32 index = _58;
        do {
            const u32 previous_index = index;
            const char16* cursor = _30 + index;
            const char16 character = *cursor;
            f32 next_width = width;
            if ((character | 1) != 0xf) {
                if (character >= 0x20)
                    next_width = width + (f32(mTextBox->GetFont()->GetCharWidth(character)) +
                                          mTextBox->mCharSpace);
                ++index;
            } else {
                const auto* tag =
                    reinterpret_cast<const sead::MessageSet<char16>::TagInfo*>(cursor);
                cursor = character == 0xf ? cursor + 3 :
                    reinterpret_cast<const char16*>(tag->getParam() + tag->paramSize);
                const u8* parameters = tag->getParam();
                if (tag->group == 1 && tag->type <= 10) {
                    switch (tag->type) {
                    case 0: {
                        s32 wait;
                        std::memcpy(&wait, parameters, sizeof(wait));
                        _5f |= 2;
                        if (_60 != 2) {
                            _4c = f32(wait);
                            _54 = width;
                        }
                        break;
                    }
                    case 1: {
                        f32 speed;
                        std::memcpy(&speed, parameters, sizeof(speed));
                        _40 = std::max(speed * _44, 1.0f);
                        break;
                    }
                    case 2:
                        if (_60 != 2)
                            _60 = 1;
                        _4c = 0.0f;
                        break;
                    case 3: {
                        s32 wait;
                        std::memcpy(&wait, parameters, sizeof(wait));
                        _5f |= 1;
                        _50 = f32(wait);
                        break;
                    }
                    case 4:
                    case 5:
                    case 6:
                    case 10: {
                        _61 = tag->type == 4 ? 2 : tag->type == 5 ? 3 : tag->type == 6 ? 4 : 1;
                        s32 offset = 0;
                        for (s32 i = 0; i < _61; ++i) {
                            u16 choice;
                            std::memcpy(&choice, parameters + offset, sizeof(choice));
                            _68[i] = choice;
                            _64[i] = i;
                            offset += sizeof(choice);
                        }
                        if (_61 > 1)
                            _62 = parameters[offset++];
                        const u8 cancel = parameters[offset];
                        _63 = cancel < _61 ? cancel : 0xff;
                        break;
                    }
                    case 8:
                    case 9: {
                        const s32 count = tag->type == 8 ? 4 : 8;
                        _61 = 0;
                        s32 offset = 0;
                        for (s32 i = 0; i < count; ++i) {
                            s16 choice;
                            u16 text_bytes;
                            std::memcpy(&choice, parameters + offset, sizeof(choice));
                            std::memcpy(&text_bytes, parameters + offset + 2, sizeof(text_bytes));
                            offset += 4;
                            if (choice >= 0 && _61 < 4) {
                                if (!(text_bytes && _78 && _78->invoke(
                                          reinterpret_cast<const char16*>(parameters + offset),
                                          text_bytes >> 1))) {
                                    _68[_61] = choice;
                                    _64[_61] = i;
                                    ++_61;
                                }
                            }
                            offset += text_bytes;
                        }
                        const u8 selected = parameters[offset];
                        _62 = 0;
                        for (s32 i = 0; i < _61; ++i) {
                            if (_64[i] == selected)
                                _62 = i;
                        }
                        _63 = 0xff;
                        if (_61) {
                            const u8 cancel = parameters[offset + 1];
                            for (s32 i = 0; i < _61; ++i) {
                                if (_64[i] == cancel)
                                    _63 = i;
                            }
                        }
                        break;
                    }
                    default:
                        break;
                    }
                } else if (_70) {
                    _70->invoke(tag);
                }
                index = (reinterpret_cast<const u8*>(cursor) -
                         reinterpret_cast<const u8*>(_30)) / 2;
            }

            if (_4c > 0.0f) {
                std::memcpy(_38, _30, index * sizeof(char16));
                char16* remaining = TagProcessor::setAlphaTag(_38 + index, false, 0);
                std::memcpy(remaining, _30 + index, (_5c - index) * sizeof(char16));
                mTextBox->setStringNoPreproces(_38, _5c + 5);
                _48 = width;
                _58 = index;
                return;
            }
            if (_54 <= next_width && character >= 0x20 && _60 == 0) {
                f32 alpha = 1.0f - (next_width - _54) / (next_width - width);
                if (alpha < 0.0f)
                    alpha = 0.0f;
                else if (alpha > 1.0f)
                    alpha = 1.0f;
                std::memcpy(_38, _30, previous_index * sizeof(char16));
                char16* remaining = TagProcessor::setAlphaTag(
                    _38 + previous_index, false, u8(s32(alpha * 255.0f)));
                *remaining++ = character;
                remaining = TagProcessor::setAlphaTag(remaining, false, 0);
                std::memcpy(remaining, _30 + previous_index + 1,
                            (_5c - previous_index - 1) * sizeof(char16));
                mTextBox->setStringNoPreproces(_38, _5c + 10);
                if (previous_index > _58) {
                    _48 = width;
                    _58 = previous_index;
                }
                return;
            }
            width = next_width;
        } while (index < _5c);
    }
    mTextBox->setStringNoPreproces(_30, _5c);
    _58 = _5c;
    _5e = 0;
    _60 = 0;
    _40 = _44;
}

// 0x7100bd9330
void LetterAnimControl::reset() {
    _5e = 0;
    _48 = 0;
    _58 = 0;
    _50 = 0;
    _54 = 0;
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
    _54 = 0;
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
void LetterAnimControl::sub_7100BD94C4(
    sead::IDelegate1<const sead::MessageSet<char16>::TagInfo*>* callback) {
    _70 = callback;
}

// 0x7100bd94cc
void LetterAnimControl::sub_7100BD94CC(sead::IDelegate2R<const char16*, s32, bool>* callback) {
    _78 = callback;
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

// NON_MATCHING: reset flag stores in the successful paging path are scheduled differently.
bool LetterAnimControl::sub_7100BD9B98(const char16* string, u16 length, u32 page) {
    bool has_next_page = false;
    _5c = mTextBox->setStringWithPage(string, length, &has_next_page, page, true, nullptr);
    if (mTextBox->GetStringBufferLength() < mTextBox->mTextLength + 10) {
        _30[0] = 0;
        _5c = 0;
        reset();
        return false;
    }
    std::memcpy(_30, mTextBox->mTextBuf, _5c * sizeof(char16));
    reset();
    return has_next_page;
}

bool LetterAnimControl::sub_7100BD9CDC(const MessageString& message, u32 page) {
    return sub_7100BD9B98(message.getString(), message.getLength(), page);
}

}  // namespace eui

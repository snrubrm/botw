#pragma once

#include "Game/UI/euiControlBase.h"

namespace sead {
class Heap;
}

namespace eui {

class TextBoxEx;

// The letter-by-letter text reveal control of a TextBoxEx (CSV eui::LetterAnimControl; 0x80 bytes, vtable 0x24c75f8).
// Field names / types are guesses from the constructor and the small accessors.
class LetterAnimControl : public ControlBase {
public:
    NN_RUNTIME_TYPEINFO(ControlBase)
    const char* getClassName() const override;
    // 0x7100bd94d4 (not decompiled)
    void Update(f32 dt) override;

    LetterAnimControl();
    void reset();
    void initialize(sead::Heap*, TextBoxEx*, LayoutEx*);

    // 0x7100bd9b80
    void flushAllowWait();
    // 0x7100bd94c4 / 0x7100bd94cc / 0x7100bd9b5c / 0x7100bd9b68 / 0x7100bd9b74 (placeholder names; trivial setters)
    void sub_7100BD94C4(void* a1);
    void sub_7100BD94CC(void* a1);
    void sub_7100BD9B5C();
    void sub_7100BD9B68(f32 value);
    void sub_7100BD9B74();

    /* 0x28 */ TextBoxEx* mTextBox = nullptr;
    /* 0x30 */ char16_t* _30 = nullptr;
    /* 0x38 */ char16_t* _38 = nullptr;
    /* 0x40 */ f32 _40 = 0;
    /* 0x44 */ f32 _44 = 0;
    /* 0x48 */ s32 _48 = 0;
    /* 0x4c */ s32 _4c = 0;
    /* 0x50 */ u64 _50 = 0;
    /* 0x58 */ u16 _58 = 0;
    /* 0x5a */ u16 _5a = 0;
    /* 0x5c */ u16 _5c = 0;
    /* 0x5e */ u8 _5e = 0;
    /* 0x5f */ u8 _5f = 0;
    /* 0x60 */ u8 _60 = 0;
    /* 0x61 */ u8 _61 = 0;
    /* 0x62 */ u8 _62 = 0;
    /* 0x63 */ u8 _63 = 0xff;
    u8 _64[0x70 - 0x64]{};
    /* 0x70 */ void* _70 = nullptr;
    /* 0x78 */ void* _78 = nullptr;
};
static_assert(sizeof(LetterAnimControl) == 0x80);

}  // namespace eui

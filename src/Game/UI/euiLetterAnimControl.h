#pragma once

#include <container/seadSafeArray.h>
#include <message/seadMessageSet.h>
#include <prim/seadDelegate.h>
#include "Game/UI/euiControlBase.h"

namespace sead {
class Heap;
}

namespace eui {

class TextBoxEx;
class MessageString;

// The letter-by-letter text reveal control of a TextBoxEx (CSV eui::LetterAnimControl; 0x80 bytes, vtable 0x24c75f8).
// Field names / types are guesses from the constructor and the small accessors.
class LetterAnimControl : public ControlBase {
public:
    NN_RUNTIME_TYPEINFO(ControlBase)
    const char* getClassName() const override;
    void Update(f32 dt) override;

    LetterAnimControl();
    void reset();
    void initialize(sead::Heap*, TextBoxEx*, LayoutEx*);

    // 0x7100bd9b80
    void flushAllowWait();
    bool sub_7100BD9B98(const char16* string, u16 length, u32 page);
    bool sub_7100BD9CDC(const MessageString& message, u32 page);
    // 0x7100bd94c4 / 0x7100bd94cc / 0x7100bd9b5c / 0x7100bd9b68 / 0x7100bd9b74 (placeholder names; trivial setters)
    void sub_7100BD94C4(sead::IDelegate1<const sead::MessageSet<char16>::TagInfo*>* callback);
    void sub_7100BD94CC(sead::IDelegate2R<const char16*, s32, bool>* callback);
    void sub_7100BD9B5C();
    void sub_7100BD9B68(f32 value);
    void sub_7100BD9B74();

    /* 0x28 */ TextBoxEx* mTextBox = nullptr;
    /* 0x30 */ char16_t* _30 = nullptr;
    /* 0x38 */ char16_t* _38 = nullptr;
    /* 0x40 */ f32 _40 = 0;
    /* 0x44 */ f32 _44 = 0;
    /* 0x48 */ f32 _48 = 0;
    /* 0x4c */ f32 _4c = 0;
    /* 0x50 */ f32 _50 = 0;
    /* 0x54 */ f32 _54 = 0;
    /* 0x58 */ u16 _58 = 0;
    /* 0x5a */ u16 _5a = 0;
    /* 0x5c */ u16 _5c = 0;
    /* 0x5e */ u8 _5e = 0;
    /* 0x5f */ u8 _5f = 0;
    /* 0x60 */ u8 _60 = 0;
    /* 0x61 */ u8 _61 = 0;
    /* 0x62 */ u8 _62 = 0;
    /* 0x63 */ u8 _63 = 0xff;
    /* 0x64 */ sead::SafeArray<u8, 4> _64{};
    // Read per choice by ScreenMessageDialog::sub_71010B2F68.
    /* 0x68 */ sead::SafeArray<u16, 4> _68{};
    /* 0x70 */ sead::IDelegate1<const sead::MessageSet<char16>::TagInfo*>* _70 = nullptr;
    /* 0x78 */ sead::IDelegate2R<const char16*, s32, bool>* _78 = nullptr;
};
static_assert(sizeof(LetterAnimControl) == 0x80);

}  // namespace eui

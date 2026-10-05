#pragma once

#include <nn/ui2d/TextBox.h>
#include <message/seadMessageSet.h>
#include <prim/seadDelegate.h>
#include <prim/seadSafeString.h>
#include "Game/UI/euiMessageString.h"

namespace eui {

class LayoutEx;

// The UI text pane. Its own virtual functions follow TextBox's 40 slots; it has no additional data.
class TextBoxEx : public nn::ui2d::TextBox {
public:
    NN_RUNTIME_TYPEINFO(nn::ui2d::TextBox)

    TextBoxEx(const nn::ui2d::ResTextBox*, const nn::ui2d::ResTextBox*,
              const nn::ui2d::BuildArgSet&, nn::ui2d::TextBox::InitializeStringParam*);
    TextBoxEx(const TextBoxEx&, LayoutEx*);

    void InitializeString(nn::ui2d::BuildResultInformation*, nn::gfx::Device*,
                          const nn::ui2d::BuildArgSet&,
                          const nn::ui2d::TextBox::InitializeStringParam&) override;
    bool InitializeStringWithTextSearcherInfo(nn::gfx::Device*, const nn::ui2d::BuildArgSet&,
                                              const nn::ui2d::TextSearcher::TextInfo&) override;
    u16 SetString(const u16* string, u16 dst_index) override;
    u16 SetString(const u16* string, u16 dst_index, u16 length) override;

    // Slots 40-47 (the two unnamed processing functions are not decompiled).
    virtual u16 setStringNoPreproces(const char16* string, u16 length);
    virtual u16 m41(const char16* string, u16 length, bool* has_next_page, u32 page, bool flag,
                    void* user_data);
    virtual s32 m42(sead::WBufferedSafeString* out, u32* text_length, u32* character_count,
                    const char16* string, u32 length, u32 page, bool flag, void* user_data);
    virtual void adjustText_(LayoutEx* layout);
    virtual bool getTextAdjustMinScale_(f32* scale);
    virtual bool isWordwrapOn_();
    virtual bool isTextChangeOn_() const;
    virtual bool getLetterAnimSpeed_(f32* speed);

    void processAppTag(sead::IDelegate1<const sead::MessageSet<char16>::TagInfo*>* callback);

    // Convenience forms of the page-processing virtual.
    u16 setMessageString(const MessageString& string, void* user_data);
    u16 setMessageStringWithPage(const MessageString& string, bool* has_next_page, u32 page,
                                 bool flag, void* user_data);
    u16 setStringWithPage(const char16* string, u16 length, bool* has_next_page, u32 page,
                         bool flag, void* user_data);
};
static_assert(sizeof(TextBoxEx) == 0x160);

// 0x7100933580
TextBoxEx* sub_7100933580(nn::ui2d::Pane* pane);

}  // namespace eui

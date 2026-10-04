#include "Game/UI/euiTextSearcher.h"
#include <nn/ui2d/Pane.h>
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/euiMessageSet.h"

namespace eui {

// 0x7100be729c
TextSearcher::TextSearcher(MessageSet* messages, TagProcessor* tag_processor)
    : mMessages(messages), mTagProcessor(tag_processor) {}

// 0x7100be72b4
void TextSearcher::SearchText(TextInfo* out, const char* text_id,
                              const nn::ui2d::Layout* parent_layout, const nn::ui2d::Pane* pane,
                              const nn::ui2d::Layout*) {
    if (mMessages) {
        sead::FixedStringBuilder<256> label;
        // Screen::doCreateLayout_ constructs LayoutEx; the message-label helpers use that type.
        const auto* layout = static_cast<const LayoutEx*>(parent_layout);
        if (text_id == nullptr) {
            CreateLayoutItemUniqueName(&label, pane->GetName(), layout);
        } else if (text_id[0] != '-' && text_id[0] != '@') {
            if (text_id[0] == '=')
                sub_7100BEF498(&label, text_id + 1, layout);
            else
                label.copy(text_id);
        }
        if (!label.isEmpty()) {
            const auto message = mMessages->tryFindMessage(label.cstr());
            if (message.getString()) {
                out->mText = reinterpret_cast<const u16*>(message.getString());
                out->mTextLength = message.getLength();
            }
        }
        if (out->_10 != -1)
            out->mBufferLength = out->_10;
    }
}

// 0x7100be73c4
void TextSearcher::SearchTextUtf8(TextInfoUtf8*, const char*, const nn::ui2d::Layout*,
                                  const nn::ui2d::Pane*, const nn::ui2d::Layout*) {}

}  // namespace eui

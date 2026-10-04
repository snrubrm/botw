#pragma once

#include <nn/ui2d/TextSearcher.h>
#include <prim/seadStringBuilder.h>

namespace eui {

class LayoutEx;
class MessageSet;
class TagProcessor;

void CreateLayoutItemUniqueName(sead::StringBuilder* out, const char* name, const LayoutEx* layout);
// 0x7100bef498: resolves a layout-relative message label (placeholder name).
void sub_7100BEF498(sead::StringBuilder* out, const char* name, const LayoutEx* layout);

// The message searcher built on the stack by Screen::doBuildLayout_ (0x7100bead1c).
class TextSearcher : public nn::ui2d::TextSearcher {
public:
    TextSearcher(MessageSet* messages, TagProcessor* tag_processor);
    ~TextSearcher() override = default;
    void SearchText(TextInfo* out, const char* text_id, const nn::ui2d::Layout* parent_layout,
                    const nn::ui2d::Pane* pane, const nn::ui2d::Layout* root_layout) override;
    void SearchTextUtf8(TextInfoUtf8*, const char*, const nn::ui2d::Layout*, const nn::ui2d::Pane*,
                        const nn::ui2d::Layout*) override;

    // Inline-only in the original; name is a guess. TextBoxEx's resource
    // constructor and LayoutEx::isScalableFontTextBox_ read this pointer.
    TagProcessor* getTagProcessor() const { return mTagProcessor; }

private:
    /* 0x08 */ MessageSet* mMessages;
    /* 0x10 */ TagProcessor* mTagProcessor;
};
static_assert(sizeof(TextSearcher) == 0x18);

}  // namespace eui

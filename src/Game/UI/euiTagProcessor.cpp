#include "Game/UI/euiTagProcessor.h"

namespace eui {

// 0x7100be5be4
TagProcessor::TagProcessor(MessageMgr* message_mgr, FontMgr* font_mgr)
    : mMessageMgr(message_mgr), mFontMgr(font_mgr) {}

// 0x7100be5cf0
void TagProcessor::EndPrint(nn::font::PrintContext<u16>*) {
    --mNestingDepth;
}

// 0x7100be5d30
void TagProcessor::EndCalculateRect(nn::font::PrintContext<u16>*) {
    --mNestingDepth;
}

// 0x7100be6254
char16* TagProcessor::setAlphaTag(char16* out, bool flag, u8 alpha) {
    out[0] = 0xe;
    out[1] = 0;
    out[2] = 0x80;
    out[3] = 2;
    u8* params = reinterpret_cast<u8*>(out + 4);
    params[0] = !flag;
    params[1] = alpha;
    return out + 5;
}

// 0x7100be628c
char16* TagProcessor::setSkipTag(char16* out, u16 count) {
    out[0] = 0xe;
    out[1] = 0;
    out[2] = 0x82;
    out[3] = 2;
    out[4] = count;
    return out + 5;
}

// 0x7100be6308
char16* TagProcessor::setSizeTag(char16* out, u16 size) {
    out[0] = 0xe;
    out[1] = 0;
    out[2] = 2;
    out[3] = 2;
    out[4] = size;
    return out + 5;
}

}  // namespace eui

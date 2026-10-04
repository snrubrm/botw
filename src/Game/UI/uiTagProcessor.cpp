#include "Game/UI/uiTagProcessor.h"

namespace uking::ui {

// 0x71010afb74
TagProcessor::TagProcessor(eui::MessageMgr* message_mgr, eui::FontMgr* font_mgr)
    : eui::TagProcessor(message_mgr, font_mgr) {
    mRubyEnabled = false;
}

// 0x71010b20a8
f32 TagProcessor::m31() const {
    return _58;
}

// 0x71010afc44
f32 TagProcessor::m28() const {
    return 0.67f;
}

}  // namespace uking::ui

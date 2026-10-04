#pragma once

#include "Game/UI/euiTagProcessor.h"

namespace uking::ui {

// Game tag processor (descriptive name), identified by ctor 0x10afb74 and vtable 0x250acb0.
class TagProcessor : public eui::TagProcessor {
public:
    TagProcessor(eui::MessageMgr* message_mgr, eui::FontMgr* font_mgr);
    ~TagProcessor() override = default;
    const nn::font::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override;
    f32 m27() const override;
    f32 m28() const override;
    f32 m29() const override;
    f32 m31() const override;

private:
    /* 0x50 */ void* _50 = nullptr;
    /* 0x58 */ f32 _58 = 1.4f;
    /* 0x5c */ bool _5c = false;
    /* 0x5d */ bool _5d = false;
};
KSYS_CHECK_SIZE_NX150(TagProcessor, 0x60);

}  // namespace uking::ui

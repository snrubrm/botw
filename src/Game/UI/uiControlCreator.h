#pragma once

#include <container/seadBuffer.h>
#include "Game/UI/euiControlCreator.h"
#include "Game/UI/uiScreens.h"

namespace uking::ui {
// Constructor 0x7100931d6c calls ScreenChildEx and clears +0x130.
// 0x71009322e4 owns its four-level ControlBase/ScreenChild/ScreenChildEx RTTI chain.
class Unk_71024746d0 : public ScreenChildEx {
public:
    NN_RUNTIME_TYPEINFO(ScreenChildEx)
    explicit Unk_71024746d0(eui::LayoutEx* layout);
    /* 0x130 */ eui::AnimButton* mButton = nullptr;
};
static_assert(sizeof(Unk_71024746d0) == 0x138);

// 0x7100a01130 reads a count/pointer Buffer of 0x18-byte entries, matching the
// layout's root pane name exactly (mode 0) or by prefix (mode 1).
struct ChildControlCreatorEntry {
    const char* name;
    ScreenChild* (*create)(const nn::ui2d::ControlSrc&, eui::LayoutEx*);
    s32 matchMode;
};
static_assert(sizeof(ChildControlCreatorEntry) == 0x18);

// Real shared game creator, vtable 0x7102485000. Slot 5 defaults to nullptr.
class Unk_7102485000 : public eui::ControlCreator {
public:
    using eui::ControlCreator::ControlCreator;
    ~Unk_7102485000() override;
    // 0x7100a01074 / 0x7100a01130
    eui::ControlBase* createControl(const nn::ui2d::ControlSrc&, eui::LayoutEx*) override;
    ScreenChild* createChildControl(const nn::ui2d::ControlSrc&, eui::LayoutEx*);
    virtual const sead::Buffer<const ChildControlCreatorEntry>* getEntries() const;
};
}  // namespace uking::ui

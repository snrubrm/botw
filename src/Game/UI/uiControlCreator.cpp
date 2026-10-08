#include "Game/UI/uiControlCreator.h"
#include <nn/ui2d/Pane.h>
#include "Game/UI/euiButton.h"
#include "Game/UI/euiLayoutEx.h"

namespace eui {
// Genuine out-of-line AnimButton cast, defined in uiPaneCasts.cpp (0x7100a013e4).
AnimButton* sub_7100A013E4(ControlBase* control);
}

namespace uking::ui {
// 0x7100a0106c / 0x7100a01070
// NON_MATCHING: the out-of-line eui base destructor is called.
Unk_7102485000::~Unk_7102485000() = default;

// 0x7100a01074
eui::ControlBase* Unk_7102485000::createControl(const nn::ui2d::ControlSrc& src,
                                               eui::LayoutEx* layout) {
    auto* child = createChildControl(src, layout);
    if (child)
        mControls->linkPrev(&child->_8);
    auto* control = eui::ControlCreator::createControl(src, layout);
    if (auto* button = eui::sub_7100A013E4(control)) {
        if (auto* button_child = nn::font::DynamicCast<Unk_71024746d0>(child))
            button_child->mButton = button;
    }
    return child ? child : control;
}

// 0x7100a01130
// NON_MATCHING: SafeString comparison traversal and Buffer index/load scheduling differ.
ScreenChild* Unk_7102485000::createChildControl(const nn::ui2d::ControlSrc& src,
                                              eui::LayoutEx* layout) {
    const sead::SafeString name(layout->mPane->GetName());
    const auto* entries = getEntries();
    if (!entries)
        return nullptr;
    for (s32 i = 0; i < entries->size(); ++i) {
        const auto& entry = (*entries)(i);
        const sead::SafeString entry_name(entry.name);
        if ((entry.matchMode == 0 && name == entry_name) ||
            (entry.matchMode == 1 && name.startsWith(entry_name)))
            return entry.create(src, layout);
    }
    return nullptr;
}

// 0x7100a014f0
const sead::Buffer<const ChildControlCreatorEntry>* Unk_7102485000::getEntries() const {
    return nullptr;
}
}  // namespace uking::ui

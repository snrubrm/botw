#include "Game/UI/uiScreens.h"
#include "Game/UI/euiLayoutEx.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ui {

// 0x71010ae9e8
bool ScreenMessage3D::sub_71010AE9E8(ksys::act::Actor* actor) {
    if (!isOpened())
        return false;
    for (u32 i = 0; i < 4; ++i) {
        auto* entry = i < _300.size() ? _300.at(i) : nullptr;
        if (entry->m38.hasProcById(actor))
            return true;
    }
    return false;
}

// 0x71010ae7c0
// NON_MATCHING: regalloc/scheduling only (original keeps loop inits in-branch with i in x21 and no
// spill; ours hoists i=0/five above the flag check, shifting i/entry to x23/x25 with an x25 spill).
// All loads/stores/calls/branches match.
void ScreenMessage3D::sub_71010AE7C0(bool flag) {
    _698.lock();
    u32 v = 0x47c35000;
    if (flag) {
        for (u64 i = 0; i != 4; ++i) {
            if (!(((u64)(u32)_300.size() <= i) ? nullptr : _300.data()[i])->m38.hasProc())
                continue;
            Entry* entry = ((u64)(u32)_300.size() <= i) ? nullptr : _300.data()[i];
            if ((u32)(entry->_48 - 5) >= 2) {
                eui::LayoutEx* layout = entry->_8;
                eui::Animator* animator = layout->mOpenAnimator;
                if (animator) {
                    if (animator->mRate != 0.0f) {
                        layout->sub_7100BDDE7C(false, 1, true);
                        layout->startAnimCloseImpl_(false, true);
                        if (EntryState* state = entry->_10) {
                            state->_30 = v;
                            state->_34 = 0;
                            state->_38 = 0;
                            state->_58 |= 0x10;
                        }
                        entry->_48 = 6;
                    } else {
                        layout->startAnimCloseImpl_(false, false);
                        entry->_48 = 5;
                    }
                }
            }
            (((u64)(u32)_300.size() <= i) ? nullptr : _300.data()[i])->m38.reset();
        }
    } else {
        for (u64 i = 0; i != 4; ++i) {
            if (!(((u64)(u32)_300.size() <= i) ? nullptr : _300.data()[i])->m38.hasProc())
                continue;
            Entry* entry = ((u64)(u32)_300.size() <= i) ? nullptr : _300.data()[i];
            if ((u32)(entry->_48 - 5) >= 2) {
                eui::LayoutEx* layout = entry->_8;
                eui::Animator* animator = layout->mOpenAnimator;
                if (animator) {
                    if (animator->mRate != 0.0f) {
                        layout->sub_7100BDDE7C(false, 1, true);
                        layout->startAnimCloseImpl_(false, true);
                        if (EntryState* state = entry->_10) {
                            state->_30 = v;
                            state->_34 = 0;
                            state->_38 = 0;
                            state->_58 |= 0x10;
                        }
                        entry->_48 = 6;
                    } else {
                        layout->startAnimCloseImpl_(false, false);
                        entry->_48 = 5;
                    }
                }
            }
        }
    }
    _698.unlock();
}

}  // namespace uking::ui

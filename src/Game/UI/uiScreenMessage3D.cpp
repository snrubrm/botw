#include "Game/UI/uiScreens.h"
#include "Game/UI/euiLayoutEx.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ui {

// 0x71010aefb0 (CSV unnamed): Entry D1 (restores the vtable, releases the proc link)
ScreenMessage3D::Entry::~Entry() = default;

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

// 0x71010ae548
// NON_MATCHING: regalloc/encoding only (original reuses actor's x22 for the match index and varies
// select predicate encodings per site; ours keeps a separate index reg with an extra spill and uniform
// encodings). All loads/stores/calls/branches match.
void ScreenMessage3D::sub_71010AE548(ksys::act::Actor* actor, bool flag) {
    _698.lock();
    if (actor) {
        s32 idx;
        if (((u64)(u32)_300.size() <= 0 ? nullptr : _300.data()[0])->m38.hasProc() &&
            (((u64)(u32)_300.size() <= 0) ? nullptr : _300.data()[0])->m38.hasProcById(actor))
            idx = 0;
        else if ((((u64)(u32)_300.size() <= 1) ? nullptr : _300.data()[1])->m38.hasProc() &&
                 (((u64)(u32)_300.size() <= 1) ? nullptr : _300.data()[1])->m38.hasProcById(actor))
            idx = 1;
        else if ((((u64)(u32)_300.size() <= 2) ? nullptr : _300.data()[2])->m38.hasProc() &&
                 (((u64)(u32)_300.size() <= 2) ? nullptr : _300.data()[2])->m38.hasProcById(actor))
            idx = 2;
        else if ((((u64)(u32)_300.size() <= 3) ? nullptr : _300.data()[3])->m38.hasProc() &&
                 (((u64)(u32)_300.size() <= 3) ? nullptr : _300.data()[3])->m38.hasProcById(actor))
            idx = 3;
        else {
            _698.unlock();
            return;
        }
        Entry* entry = ((u64)(u32)_300.size() <= (u64)idx) ? nullptr : _300.data()[idx];
        if ((u32)(entry->_48 - 5) >= 2) {
            eui::LayoutEx* layout = entry->_8;
            eui::Animator* animator = layout->mOpenAnimator;
            if (animator) {
                if (animator->mRate != 0.0f) {
                    layout->sub_7100BDDE7C(false, 1, true);
                    layout->startAnimCloseImpl_(false, true);
                    if (EntryState* state = entry->_10) {
                        state->_30 = 0x47c35000;
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
        if (flag) {
            Entry* target =
                ((u64)(u32)_300.size() <= (u64)idx) ? nullptr : _300.data()[idx];
            target->m38.reset();
        }
    }
    _698.unlock();
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

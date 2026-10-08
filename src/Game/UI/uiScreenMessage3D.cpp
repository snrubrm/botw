#include "Game/UI/uiScreens.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/euiMessageMgr.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ui {

// 0x71010ae104 (CSV unnamed): message lookup into _680 (0 = found, 1 = no set, 2 = no message)
s32 ScreenMessage3D::sub_71010AE104(const sead::SafeString& set, const sead::SafeString& label) {
    eui::MessageSet* message_set = eui::MessageMgr::instance()->getMessageSet(set);
    if (!message_set)
        return 1;
    eui::MessageString message = message_set->tryFindMessage(label.cstr());
    _680.assign(message);
    return _680.getString() ? 0 : 2;
}

// 0x71010aefb0 (CSV unnamed): Entry D1 (restores the vtable, releases the proc link)
ScreenMessage3D::Entry::~Entry() = default;

// 0x71010aeb60
void ScreenMessage3D::Entry::sub_71010AEB60() {
    if (m38.hasProc())
        m38.reset();
    _54 = 0;
    _4c = -1;
    _a8 = false;
    _18->setStringNoPreproces(sead::WSafeString::cEmptyString.cstr(), 0);
    if (_20)
        _20->StopAtMin();
    if (_8) {
        _8->sub_7100BDDE7C(false, 1, true);
        _8->startAnimCloseImpl_(false, true);
    }
    _48 = 6;
}

// 0x71010ae190
// NON_MATCHING: encoding/scheduling only (original tests the hasProcById result directly with
// tbnz while ours materialises !by_id with eor+tbz (4 sites; snippet-proven that clang 4 emits
// eor for `if (bool)` here); scan-2 block0 uses the eq-null-first csel operand order; the init
// tail keeps the entry/index in registers with merged stores while the original reloads the buffer
// per store and computes flags&1 plus &_680 before the assign-entry check). All loads/stores/calls
// (lock, 8 hasProc/hasProcById, isClosed/open(1), MessageString::assign, acquire, unlock tail)
// and branches match; rodata -200.0f/220.0f verified.
void ScreenMessage3D::sub_71010AE190(ksys::act::Actor* actor, f32 x, u32 flags) {
    _698.lock();
    Entry* raw0 = _300.data()[0];
    u32 state0 = raw0->_48;
    if (((u32)_300.size() == 0 ? nullptr : raw0)->m38.hasProc()) {
        state0 -= 5;
        Entry* entry0;
        if ((u32)_300.size() == 0)
            entry0 = nullptr;
        else
            entry0 = _300.data()[0];
        bool by_id0 = entry0->m38.hasProcById(actor);
        if (state0 >= 2) {
            if (by_id0) {
                _698.unlock();
                return;
            }
        }
    }
    Entry* raw1 = _300.data()[1];
    u32 state1 = raw1->_48;
    if (((u32)_300.size() > 1 ? raw1 : nullptr)->m38.hasProc()) {
        state1 -= 5;
        Entry* entry1 = (u32)_300.size() >= 2 ? _300.data()[1] : nullptr;
        bool by_id1 = entry1->m38.hasProcById(actor);
        if (state1 >= 2) {
            if (by_id1) {
                _698.unlock();
                return;
            }
        }
    }
    Entry* raw2 = _300.data()[2];
    u32 state2 = raw2->_48;
    if (((u32)_300.size() > 2 ? raw2 : nullptr)->m38.hasProc()) {
        state2 -= 5;
        Entry* entry2 = (u32)_300.size() >= 3 ? _300.data()[2] : nullptr;
        bool by_id2 = entry2->m38.hasProcById(actor);
        if (state2 >= 2) {
            if (by_id2) {
                _698.unlock();
                return;
            }
        }
    }
    Entry* raw3 = _300.data()[3];
    u32 state3 = raw3->_48;
    if (((u32)_300.size() > 3 ? raw3 : nullptr)->m38.hasProc()) {
        state3 -= 5;
        Entry* entry3 = (u32)_300.size() >= 4 ? _300.data()[3] : nullptr;
        bool by_id3 = entry3->m38.hasProcById(actor);
        if (state3 >= 2) {
            if (by_id3) {
                _698.unlock();
                return;
            }
        }
    }
    if (isClosed())
        open(1);
    u32 idx;
    Entry* check0 = _300.data()[0];
    if (check0->_48 == 6 && !(0u < (u32)_300.size() ? check0 : nullptr)->m38.hasProc())
        idx = 0;
    else if (_300.data()[1]->_48 == 6 &&
             !(1u < (u32)_300.size() ? _300.data()[1] : nullptr)->m38.hasProc())
        idx = 1;
    else if (_300.data()[2]->_48 == 6 &&
             !(2u < (u32)_300.size() ? _300.data()[2] : nullptr)->m38.hasProc())
        idx = 2;
    else if (_300.data()[3]->_48 != 6 ||
             (3u < (u32)_300.size() ? _300.data()[3] : nullptr)->m38.hasProc()) {
        _698.unlock();
        return;
    } else {
        idx = 3;
    }
    Entry* entry = (u32)_300.size() <= idx ? nullptr : _300.data()[idx];
    entry->_60.assign(_680);
    _300.data()[idx]->_50 = _690;
    _300.data()[idx]->_54 = 0;
    _300.data()[idx]->_58 = false;
    _300.data()[idx]->_59 = false;
    _300.data()[idx]->_5a = flags & 1;
    _300.data()[idx]->_5b = false;
    _300.data()[idx]->_70 = 0;
    _300.data()[idx]->_74 = idx * -200.0f + 220.0f;
    _300.data()[idx]->_7c = 0;
    _300.data()[idx]->_80 = 0;
    _300.data()[idx]->_84 = 0;
    _300.data()[idx]->m38.acquire(actor, false);
    _300.data()[idx]->_b0 = x;
    _300.data()[idx]->_48 = 0;
    _698.unlock();
}

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

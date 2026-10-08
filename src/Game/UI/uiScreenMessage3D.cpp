#include "Game/UI/uiScreens.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/euiMessageMgr.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::ui {

// File-static message block for the Entry tag processing (0x710261ef20 in the original; the two
// SafeStrings carry the "T_Message_00" IDs, with the assure-termination virtual calls and string
// accesses below reproducing).
struct Message3DMsgStatics {
    u32 _20 = 0;
    u32 _24 = 0x8004ef;
    sead::SafeString _28 = "T_Message_00";
    sead::SafeString _38 = "T_Message_00";
    sead::SafeString _48 = "Pa_Message_00";
    sead::SafeString _58 = "Pa_Message_01";
    sead::SafeString _68 = "Pa_Message_02";
    sead::SafeString _78 = "Pa_Message_03";
};
static Message3DMsgStatics sUnk_710261EF20;

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

// 0x71010aeacc (slot 103): reset all four entries
void ScreenMessage3D::m101() {
    Entry* e0;
    if (_300.size() == 0)
        e0 = nullptr;
    else
        e0 = _300.data()[0];
    e0->sub_71010AEB60();
    Entry* e1 = (u32)_300.size() >= 2 ? _300.data()[1] : nullptr;
    e1->sub_71010AEB60();
    Entry* e2 = (u32)_300.size() >= 3 ? _300.data()[2] : nullptr;
    e2->sub_71010AEB60();
    Entry* e3 = (u32)_300.size() >= 4 ? _300.data()[3] : nullptr;
    e3->sub_71010AEB60();
}

// 0x71010aec24 (slot 85): reset all four entries
void ScreenMessage3D::m83() {
    Entry* e0;
    if (_300.size() == 0)
        e0 = nullptr;
    else
        e0 = _300.data()[0];
    e0->sub_71010AEB60();
    Entry* e1 = (u32)_300.size() >= 2 ? _300.data()[1] : nullptr;
    e1->sub_71010AEB60();
    Entry* e2 = (u32)_300.size() >= 3 ? _300.data()[2] : nullptr;
    e2->sub_71010AEB60();
    Entry* e3 = (u32)_300.size() >= 4 ? _300.data()[3] : nullptr;
    e3->sub_71010AEB60();
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

// 0x71010adbc8 (slot 96, m94 override)
// NON_MATCHING: guard layout only (per-entry bodies, _59 accumulation, close/x_2 tails match).
// The size-guard branches lay out null-away in the original but entry-away in ours (if/else form
// keeps the e0 cbz guard; a ternary gets UB-folded away entirely).
void ScreenMessage3D::m94() {
    if (isOpened()) {
        Entry* e0;
        if ((u32)_300.size() == 0)
            e0 = nullptr;
        else
            e0 = _300.data()[0];
        if (e0->_48 == 6 && !e0->m38.hasProc()) {
            Entry* e1;
            if ((u32)_300.size() <= 1)
                e1 = nullptr;
            else
                e1 = _300.data()[1];
            if (e1->_48 == 6 && !e1->m38.hasProc()) {
                Entry* e2;
                if ((u32)_300.size() < 3)
                    e2 = nullptr;
                else
                    e2 = _300.data()[2];
                if (e2->_48 == 6 && !e2->m38.hasProc()) {
                    Entry* e3;
                    if ((u32)_300.size() < 4)
                        e3 = nullptr;
                    else
                        e3 = _300.data()[3];
                    if (e3->_48 == 6 && !e3->m38.hasProc()) {
                        close(-1);
                        return;
                    }
                }
            }
        }
    }
    Entry* e0;
    if ((u32)_300.size() == 0)
        e0 = nullptr;
    else
        e0 = _300.data()[0];
    e0->_b4 = getAnimationStep_();
    Entry* a0;
    if ((u32)_300.size() == 0)
        a0 = nullptr;
    else
        a0 = _300.data()[0];
    a0->sub_71010ADE64();
    u32 mask = _300.data()[0]->_59;
    Entry* e1;
    if ((u32)_300.size() <= 1)
        e1 = nullptr;
    else
        e1 = _300.data()[1];
    e1->_b4 = getAnimationStep_();
    Entry* a1;
    if ((u32)_300.size() < 2)
        a1 = nullptr;
    else
        a1 = _300.data()[1];
    a1->sub_71010ADE64();
    mask |= _300.data()[1]->_59;
    Entry* e2;
    if ((u32)_300.size() < 3)
        e2 = nullptr;
    else
        e2 = _300.data()[2];
    e2->_b4 = getAnimationStep_();
    Entry* a2;
    if ((u32)_300.size() < 3)
        a2 = nullptr;
    else
        a2 = _300.data()[2];
    a2->sub_71010ADE64();
    mask |= _300.data()[2]->_59;
    Entry* e3;
    if ((u32)_300.size() < 4)
        e3 = nullptr;
    else
        e3 = _300.data()[3];
    e3->_b4 = getAnimationStep_();
    Entry* a3;
    if ((u32)_300.size() < 4)
        a3 = nullptr;
    else
        a3 = _300.data()[3];
    a3->sub_71010ADE64();
    mask |= _300.data()[3]->_59;
    if ((mask & 0xff) == 0)
        return;
    x_2();
}

// 0x71010ade64 (CSV unnamed)
// NON_MATCHING: scheduling/allocation only (switch structure, all calls/stores/branches match).
// Remaining diffs: smaller frame (fewer callee-saved regs), case-1 _a8=1 kept inline instead of
// shared with case 4, TextBox vslot load hoisted differently, float <= uses b.ls not b.le.
void ScreenMessage3D::Entry::sub_71010ADE64() {
    _59 = false;
    switch (_48) {
    case 0:
        sub_71010AEFF8();
        _8->sub_7100BDDE7C(false, 0, true);
        _a8 = true;
        _48 = 1;
        break;
    case 1:
        if (_8->isAnimOpenEnd(false)) {
            _ac = 0.0f;
            _a8 = true;
            _20->StopAtMin();
            _48 = 2;
        }
        break;
    case 2:
        if (_b0 < 0.0f)
            break;
        if (_ac <= _b0)
            break;
        _54 = 0.0f;
        _48 = 3;
        break;
    case 3:
        if (_50 <= _54) {
            if (_4c == -1) {
                if (!_58) {
                    _8->startAnimCloseImpl_(false, false);
                    _48 = 5;
                } else {
                    _48 = _8->isAnimCloseEnd(false) ? 6 : 5;
                }
            } else {
                _20->PlayAuto(1.0f);
                _48 = 4;
            }
        } else {
            _54 += _b4;
        }
        break;
    case 4:
        if ((_20->mFlags & 1) != 0) {
            u32 page = _4c;
            bool has_next = false;
            _8->setMessageStringForEachIdWithPage("T_Message_00", _60, &has_next, page, true,
                                                 nullptr);
            _59 = true;
            u16 len = _18->GetStringBufferLength();
            u16 textlen = _18->mTextLength;
            _a8 = false;
            // Discarded call that really is in the target asm.
            sead::WSafeString::cEmptyString.cstr();
            _18->setStringNoPreproces(sead::WSafeString::cEmptyString.getStringTop(), 0);
            if ((len & 0xffff) < textlen + 10) {
                _4c = -1;
            } else {
                _18->processAppTag(&_88);
                if (!has_next)
                    _4c = -1;
                else
                    ++_4c;
            }
            _a8 = true;
            _20->StopAtMin();
            _48 = 2;
        }
        break;
    case 5:
        if (_8->isAnimCloseEnd(false)) {
            _48 = 6;
            sub_71010AEFF8();
        }
        break;
    case 6:
        if (m38.hasProc())
            m38.reset();
        break;
    default:
        break;
    }
    if (_a8)
        _ac += _b4;
    sub_71010AF290();
}

// 0x71010aeff8 (CSV unnamed)
void ScreenMessage3D::Entry::sub_71010AEFF8() {
    if (_5b)
        return;
    if (_5a)
        _28->PlayAuto(1.0f);
    else
        _28->StopAtMin();
    if (_60.getString() != nullptr &&
        sUnk_710261EF20._38.getStringTop()[0] != sead::SafeString::cNullChar) {
        bool has_next = false;
        eui::LayoutEx* layout = _8;
        // Discarded call that really is in the target asm (explicit termination before use).
        sUnk_710261EF20._38.cstr();
        layout->setMessageStringForEachIdWithPage(sUnk_710261EF20._38.getStringTop(), _60, &has_next,
                                                 _4c, true, nullptr);
        _4c = has_next ? 1 : -1;
        _18->processAppTag(&_88);
        _59 = true;
    }
    {
        ksys::act::ActorConstDataAccess access;
        eui::MessageSet* set = nullptr;
        bool have_actor = ksys::act::acquireActor(&m38, &access);
        if (have_actor)
            set = eui::MessageMgr::instance()->getMessageSet("ActorType/NPC");
        if (!have_actor || !set) {
            eui::MessageString empty;
            if (empty.getString() != nullptr)
                _8->setMessageStringForEachId("T_Name_00", empty, true, nullptr);
        } else {
            sead::FixedSafeString<256> label;
            const sead::SafeString& actor_name = access.getName();
            actor_name.cstr();
            label.format("%s_Name", actor_name.getStringTop());
            label.cstr();
            eui::MessageString msg = set->tryFindMessage(label.getStringTop());
            if (msg.getString() == nullptr) {
                eui::MessageSet* clerk_set =
                    eui::MessageMgr::instance()->getMessageSet("ActorType/ClerkNPC");
                if (clerk_set) {
                    label.cstr();
                    eui::MessageString msg2 = clerk_set->tryFindMessage(label.getStringTop());
                    msg.assign(msg2);
                }
            }
            if (msg.getString() != nullptr)
                _8->setMessageStringForEachId("T_Name_00", msg, true, nullptr);
        }
    }
    _5b = true;
}

// 0x71010aecb8 (CSV unnamed): tag invoke (the method bound to the _88 delegate).
void ScreenMessage3D::Entry::sub_71010AECB8(const sead::MessageSet<char16>::TagInfo* tag) {
    if (tag->group == 4 && tag->type == 0) {
        if (m38.hasProc()) {
            auto* proc = m38.getProc(nullptr, nullptr);
            auto* actor = sead::DynamicCast<ksys::act::Actor>(proc);
            if (actor)
                sub_71010B3468(tag, actor, true);
        }
    }
    if (tag->group == 4 && tag->type == 1) {
        if (m38.hasProc()) {
            auto* proc = m38.getProc(nullptr, nullptr);
            auto* actor = sead::DynamicCast<ksys::act::Actor>(proc);
            if (actor)
                sub_71010B3484(tag, actor, true);
        }
    }
    if (tag->group == 4 && tag->type == 2) {
        if (m38.hasProc()) {
            auto* proc = m38.getProc(nullptr, nullptr);
            auto* actor = sead::DynamicCast<ksys::act::Actor>(proc);
            if (actor)
                sub_71010B3468(tag, actor, true);
        }
    }
    if (tag->group == 3 && tag->type == 1) {
        if (m38.hasProc()) {
            auto* proc = m38.getProc(nullptr, nullptr);
            auto* actor = sead::DynamicCast<ksys::act::Actor>(proc);
            if (actor)
                sub_71010B3188(tag, actor, true, nullptr, true);
        }
    }
}

}  // namespace uking::ui

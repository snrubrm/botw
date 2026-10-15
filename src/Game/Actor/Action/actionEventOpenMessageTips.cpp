#include "Game/Actor/Action/actionEventOpenMessageTips.h"
#include <container/seadBuffer.h>
#include "Game/UI/uiUI.h"

namespace uking::action {

namespace {

// Placeholder: tips type -> message tips id entry (16 bytes: vtable 0x710237dc60, id).
struct TipsTypeEntry {
    explicit TipsTypeEntry(s32 id_) : id(id_) {}
    virtual ~TipsTypeEntry() = default;

    s32 id;
};

// Placeholder: the object at 0x71025b1f10 that the static initializer 0x710011d528 builds. Only the tips table
// at +0x148 is read here; the colour/float values at +0x8..+0x140 are not modelled.
struct Unk_71025b1f10 {
    Unk_71025b1f10(sead::Buffer<TipsTypeEntry> tips_) : tips(tips_) {}

    u32 _0 = 0x8004ef;
    u32 _4 = 0;
    u8 _8[0x140]{};
    sead::Buffer<TipsTypeEntry> tips;
};

// 0x71025b1c80
TipsTypeEntry sTipsTypeEntries[] = {
    TipsTypeEntry(0),  TipsTypeEntry(1),  TipsTypeEntry(2),  TipsTypeEntry(3),  TipsTypeEntry(4),
    TipsTypeEntry(5),  TipsTypeEntry(6),  TipsTypeEntry(7),  TipsTypeEntry(8),  TipsTypeEntry(-1),
    TipsTypeEntry(28), TipsTypeEntry(-1), TipsTypeEntry(9),  TipsTypeEntry(10), TipsTypeEntry(-1),
    TipsTypeEntry(11), TipsTypeEntry(12), TipsTypeEntry(13), TipsTypeEntry(14), TipsTypeEntry(15),
    TipsTypeEntry(-1), TipsTypeEntry(-1), TipsTypeEntry(-1), TipsTypeEntry(-1), TipsTypeEntry(16),
    TipsTypeEntry(17), TipsTypeEntry(-1), TipsTypeEntry(-1), TipsTypeEntry(-1), TipsTypeEntry(-1),
    TipsTypeEntry(18), TipsTypeEntry(20), TipsTypeEntry(21), TipsTypeEntry(22), TipsTypeEntry(23),
    TipsTypeEntry(24), TipsTypeEntry(25), TipsTypeEntry(26), TipsTypeEntry(27), TipsTypeEntry(19),
};

Unk_71025b1f10 sUnk_71025b1f10(sTipsTypeEntries);

}  // namespace

EventOpenMessageTips::EventOpenMessageTips(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventOpenMessageTips::~EventOpenMessageTips() = default;

bool EventOpenMessageTips::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventOpenMessageTips::enter_(ksys::act::ai::InlineParamPack* params) {
    mRequested = false;
    mOpened = false;
    if (auto* ui = ui::UI::instance())
        ui->sub_71010A6B98(nullptr);
}

void EventOpenMessageTips::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventOpenMessageTips::loadParams_() {
    getDynamicParam(&mTipsType_d, "TipsType");
    getDynamicParam(&mMessageId_d, "MessageId");
}

// NON_MATCHING: scheduling of the FixedSafeString vtable load and of `index + 1` (same shape as
// NPCTalkASyncAction::oneShot_)
void EventOpenMessageTips::calc_() {
    if (isFailed() || isFinished())
        return;

    auto* ui = ui::UI::instance();
    if (!ui) {
        setFailed();
        mFlags.set(Flag::Changeable);
        return;
    }

    if (mOpened) {
        if (ui->sub_71010A5C18())
            return;
        setFinished();
        mFlags.set(Flag::Changeable);
        return;
    }

    if (mRequested) {
        if (ui->sub_71010A5C18())
            mOpened = true;
        return;
    }

    if (ui->sub_71010A5C18()) {
        ui->closeMessageTipsScreen();
        return;
    }

    const s32 index = mMessageId_d.rfindIndex(":");
    if (index < 1 || *mTipsType_d < 0 || sUnk_71025b1f10.tips.size() <= *mTipsType_d ||
        sUnk_71025b1f10.tips[*mTipsType_d].id == -1) {
        setFailed();
        mFlags.set(Flag::Changeable);
        return;
    }

    sead::FixedSafeString<64> message_set;
    message_set.copy(mMessageId_d, index);
    ui->sub_71010A6584(message_set, mMessageId_d.cstr() + (index + 1),
                       sUnk_71025b1f10.tips[*mTipsType_d].id);
    mRequested = true;
}

}  // namespace uking::action

#include "Game/Actor/Action/actionOpenMessageDialogTrig.h"
#include <prim/seadSafeString.h>
#include "Game/UI/uiUI.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Event/evtEventSystem.h"
#include "KingSystem/Sound/sndSound.h"

namespace uking::action {

OpenMessageDialogTrig::OpenMessageDialogTrig(const InitArg& arg) : ksys::act::ai::Action(arg) {}

OpenMessageDialogTrig::~OpenMessageDialogTrig() = default;

bool OpenMessageDialogTrig::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: return block placement and when `separator + 1` is computed.
bool OpenMessageDialogTrig::oneShot_() {
    auto* ui = ui::UI::instance();
    if (!ui)
        return false;
    if (*mIsBecomingSpeaker_d)
        ksys::evt::EventSystem::instance()->setSpeaker(mActor);
    if (ui->sub_71010A5A54())
        ui->x_0(false);

    const s32 separator = mMessageId_d.rfindIndex(":");
    if (separator < 1)
        return true;

    sead::FixedSafeString<64> mstxt;
    mstxt.copy(mMessageId_d, separator);
    if (*mIsOverWriteLabelActorName_d) {
        const s32 slash = mstxt.findIndex("/");
        mstxt.chop(mstxt.calcLength() - slash - 1);
        mstxt.copyAt(-1, mActor->getName());
    }

    s32 option;
    switch (*mCloseDialogOption_d) {
    case 0:
        option = 2;
        break;
    case 1:
        option = 1;
        break;
    case 2:
        option = 3;
        break;
    case 3:
        option = 0;
        break;
    default:
        option = 2;
        break;
    }

    if (ui->messageDialogViewStyleStuff(mstxt, sead::SafeString(mMessageId_d.cstr() + (separator + 1)),
                                        mActor, 0.0f, option, false, false)) {
        if (auto* sound_mgr = ksys::snd::SoundMgr::instance()) {
            if (sound_mgr->_90)
                sound_mgr->_90->sub_710104F86C();
        }
        return true;
    }
    return false;
}

void OpenMessageDialogTrig::loadParams_() {
    getDynamicParam(&mCloseDialogOption_d, "CloseDialogOption");
    getDynamicParam(&mIsBecomingSpeaker_d, "IsBecomingSpeaker");
    getDynamicParam(&mIsOverWriteLabelActorName_d, "IsOverWriteLabelActorName");
    getDynamicParam(&mMessageId_d, "MessageId");
}

}  // namespace uking::action

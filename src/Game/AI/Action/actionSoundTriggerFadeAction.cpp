#include "Game/AI/Action/actionSoundTriggerFadeAction.h"
#include <xlink2/xlink2HandleSLink.h>
#include <xlink2/xlink2UserInstance.h>
#include "KingSystem/Sound/sndMgr.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Event/evtEventResource.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/XLink/xlinkXLink.h"

namespace uking::action {

SoundTriggerFadeAction::SoundTriggerFadeAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SoundTriggerFadeAction::~SoundTriggerFadeAction() = default;

bool SoundTriggerFadeAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool SoundTriggerFadeAction::oneShot_() {
    if (auto* info = ksys::evt::Manager::instance()->sub_7100DB137C()) {
        if (auto* xlink = info->sub_7100DC9628()) {
            if (xlink->_50 && sub_7100E16B70(xlink->_50))
                return true;
        }
    }
    if (auto* actor = mActor) {
        if (auto* xlink = actor->getXLink()) {
            if (xlink->_50 && sub_7100E16B70(xlink->_50))
                return true;
        }
    }
    if (auto* user = ksys::snd::Unk_710104e5b4::instance()->_28)
        return sub_7100E16B70(user);
    return false;
}

bool SoundTriggerFadeAction::sub_7100E16B70(xlink2::UserInstance* user) {
    xlink2::HandleSLink handle;
    if (!user->searchEmittingEvent(&handle, mSound_d.cstr()))
        return false;
    handle.fade();
    return true;
}

void SoundTriggerFadeAction::loadParams_() {
    getDynamicParam(&mSound_d, "Sound");
}

}  // namespace uking::action

#include "Game/Actor/Action/actionXLinkEventKillAction.h"
#include "Game/Actor/aiXlinkHandle.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Event/evtEventResource.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/XLink/xlinkXLink.h"

namespace uking::action {

XLinkEventKillAction::XLinkEventKillAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

XLinkEventKillAction::~XLinkEventKillAction() = default;

bool XLinkEventKillAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool XLinkEventKillAction::oneShot_() {
    auto* xlink = mActor->getXLink();
    if (!xlink)
        return false;

    if (!mELinkKey_d.isEmpty()) {
        if (auto* user = xlink->_48) {
            xlink2::HandleELink handle;
            if (user->searchEmittingEvent(&handle, mELinkKey_d.cstr()))
                xlink::kill(handle);
        }
    }

    if (!mSLinkKey_d.isEmpty()) {
        if (auto* user = xlink->_50) {
            xlink2::HandleSLink handle;
            if (user->searchEmittingEvent(&handle, mSLinkKey_d.cstr()))
                xlink::fade(handle, 0);
        }

        if (ksys::evt::Manager::instance()->getActiveEvent()) {
            if (auto* info = ksys::evt::Manager::instance()->sub_7100DB137C()) {
                if (auto* event_xlink = info->sub_7100DC9628()) {
                    if (auto* user = event_xlink->_50) {
                        xlink2::HandleSLink handle;
                        if (user->searchEmittingEvent(&handle, mSLinkKey_d.cstr()))
                            xlink::fade(handle, 0);
                    }
                }
            }
        }
    }

    return true;
}

void XLinkEventKillAction::loadParams_() {
    getDynamicParam(&mELinkKey_d, "ELinkKey");
    getDynamicParam(&mSLinkKey_d, "SLinkKey");
}

}  // namespace uking::action

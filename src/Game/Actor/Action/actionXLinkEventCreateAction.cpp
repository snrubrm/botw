#include "Game/Actor/Action/actionXLinkEventCreateAction.h"

#include <xlink2/xlink2HandleELink.h>
#include <xlink2/xlink2HandleSLink.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Event/evtEventFlow.h"
#include "KingSystem/Event/evtEventResource.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/XLink/xlinkXLink.h"

namespace uking::action {

XLinkEventCreateAction::XLinkEventCreateAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

XLinkEventCreateAction::~XLinkEventCreateAction() = default;

bool XLinkEventCreateAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void XLinkEventCreateAction::loadParams_() {
    getDynamicParam(&mIsTargetDemoSLinkUser_d, "IsTargetDemoSLinkUser");
    getDynamicParam(&mELinkKey_d, "ELinkKey");
    getDynamicParam(&mSLinkKey_d, "SLinkKey");
}

// NON_MATCHING: branch layout and handle/position update scheduling differ.
bool XLinkEventCreateAction::oneShot_() {
    if (auto* event = ksys::evt::Manager::instance()->getActiveEvent())
        event->getFrameCount();  // The native virtual call's result is discarded.

    bool elink_success = mELinkKey_d.isEmpty();
    if (!elink_success) {
        if (auto* xlink = mActor->getXLink()) {
            if (auto* user = xlink->_48) {
                xlink2::Locator locator;
                if (user->searchAsset(&locator, mELinkKey_d.cstr())) {
                    xlink2::HandleELink handle;
                    user->emit(locator, &handle);
                    if (handle.isActive()) {
                        handle.setDelayEmitParamF8Flags(0x10);
                        elink_success = true;
                    }
                }
            }
        }
    }

    bool slink_success = mSLinkKey_d.isEmpty();
    if (!slink_success) {
        if (*mIsTargetDemoSLinkUser_d) {
            if (ksys::evt::Manager::instance()->getActiveEvent()) {
                if (auto* info = ksys::evt::Manager::instance()->sub_7100DB137C()) {
                    if (auto* xlink = info->sub_7100DC9628()) {
                        if (auto* user = xlink->_50) {
                            xlink2::Locator locator;
                            if (user->searchAsset(&locator, mSLinkKey_d.cstr())) {
                                auto handle = user->emit(locator);
                                if (handle.isActive()) {
                                    auto* event = static_cast<xlink2::EventSLink*>(handle.getEvent());
                                    const auto position = mActor->getMtx().getTranslation();
                                    event->mBitFlag2.setBit(8);
                                    event->mPosition = position;
                                    event->mBitFlag3.setBit(8);
                                }
                                slink_success = true;
                            }
                        }
                    }
                }
            }
        } else {
            if (auto* xlink = mActor->getXLink()) {
                if (auto* user = xlink->_50) {
                    xlink2::Locator locator;
                    if (user->searchAsset(&locator, mSLinkKey_d.cstr())) {
                        xlink2::HandleSLink handle;
                        user->emit(locator, &handle);
                        slink_success = handle.isActive();
                    }
                }
            }
        }
    }
    return elink_success & slink_success;
}

}  // namespace uking::action

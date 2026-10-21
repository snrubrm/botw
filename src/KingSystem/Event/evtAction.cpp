#include "KingSystem/Event/evtAction.h"
#include <ore/StringView.h>
#include "Game/Actor/Player/actPlayerBase.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "Game/UI/uiUtils.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/Event/evtActionContext.h"
#include "KingSystem/Event/evtActorBase.h"
#include "KingSystem/Event/evtEventFlow.h"
#include "KingSystem/Event/evtEventResource.h"

namespace ksys::evt {

// 0x7100da39d4 (declared only; placeholder name): whether `name` is a camera animation action.
bool isCameraAnimAction(const sead::SafeString& name);
// 0x7100da38d4 (declared only; placeholder name): whether `name` is a camera actor.
bool isCameraActor(const sead::SafeString& name);

// 0x71008a71fc (CSV evt::Action::ctor)
Action::Action(const evfl::ResAction* res, ActorBase* actor) : ActionBase(res, actor) {}

// 0x71008a7230 (CSV evt::Action::dtor), 0x71008a7244 (dtorDelete)
// (user-provided empty body: the original keeps the vtable pointer store, see uiScreenDtors2.cpp)
Action::~Action() { ; }

// 0x7100da7c44
bool Action::x() {
    for (s64 i = 0; i < 32; ++i) {
        ActionContext* context = mSlots[i].context;
        if (context && !(context->_af4 & 0x20) && context->mStatus != 0 && context->mStatus < 5)
            return false;
    }
    return true;
}

// 0x7100da7c8c
void Action::sub_7100DA7C8C() {
    for (s64 i = 0; i < 32; ++i) {
        ActionContext* context = mSlots[i].context;
        if (context && !(context->_af4 & 0x20) && context->statusStuff_0())
            mSlots[i].handler.Reset();
    }
}

// 0x7100da7d1c
void Action::x_0(Slot* slot) {
    if (slot->context->statusStuff(true))
        slot->handler.Invoke();
    ActionContext* context = slot->context;
    if (context && !(context->_af4 & 0x20)) {
        context->reset();
        slot->context = nullptr;
    }
}

// 0x7100da7dc4
void Action::sub_7100DA7DC4() {
    for (s64 i = 0; i < 32; ++i) {
        ActionContext* context = mSlots[i].context;
        if (context && !(context->_af4 & 0x20)) {
            context->reset();
            mSlots[i].context = nullptr;
        }
    }
}

// 0x71008a7278
void Action::m4(Slot* slot, const evfl::ActionArg& arg, evfl::ActionDoneHandler* handler) {
    ActionBase::m4(slot, arg, handler);
    sub_71008A72A4(nullptr, arg);
}

// 0x71008a72a4
// NON_MATCHING: the original stores the Talk flag through the immediate offset [x25,#0x1cc]; ours
// materialises the address (add x20, x25, #0x1cc) once per branch and stores through it (2 insns).
void Action::sub_71008A72A4(void* unused, const evfl::ActionArg& arg) {
    ActorBase* base = mActor;
    auto* event_actor = sead::DynamicCast<Actor>(base);
    auto* actor = sead::DynamicCast<act::Actor>(base->mLink.getProc(nullptr));

    EventFlowBase* flow = base->mActorSet->mFlow;
    EventResource* resource = flow->_108;

    if (isCameraAnimAction(sead::SafeString(mRes->name.Get()->data()))) {
        auto* camera = resource->_148;
        if (camera) {
            // The original constructs and destroys this accessor around the block.
            act::ActorLinkConstDataAccess accessor;
            if (isCameraActor(actor->getName())) {
                ore::StringView scene_name;
                if (arg.param_accessor.FindString(&scene_name, "SceneName") &&
                    !scene_name.empty()) {
                    sead::FixedSafeString<64> name;
                    name.copy(scene_name.data());
                    if (sead::SafeString(mRes->name.Get()->data()) ==
                        "Demo_AnimFlowForMapTower") {
                        if (auto* info = uking::act::PlayerInfo::instance()) {
                            if (auto* player = info->getPlayer()) {
                                sead::FixedSafeString<16> player_name;
                                sead::Vector3f position;
                                player->getMtx().getTranslation(position);
                                uking::ui::sub_7100A9F55C(&player_name, &position, 10.0f);
                                name.appendWithFormat("-%s", player_name.cstr());
                            }
                        }
                    }
                    camera->sub_7100DA44EC(name, flow->mStartTransform);
                }
                return;
            }
        }
    }

    if (sead::SafeString(mRes->name.Get()->data()) == "Demo_ForbidSettingInstEventFlag")
        event_actor->_1cc |= 4;

    if (sead::SafeString(mRes->name.Get()->data()) == "Demo_Talk") {
        if (!(event_actor->_1cc & 2)) {
            actor->getASList()->x_2(0x42, 9, false, false);
            actor->getASList()->x_2(0x42, 0xb, false, false);
        }
        event_actor->_1cc |= 2;
    } else {
        event_actor->_1cc &= ~2;
    }
}

// 0x71008a7758
void Action::m5(ActionContext* context, const evfl::ActionArg& arg) {
    ActionBase::m5(context, arg);
    sub_71008A72A4(nullptr, arg);
}

// 0x71008a7784
void Action::m6(ActionContext* context, const evfl::ActionArg& arg) {
    ActionBase::m6(context, arg);
}

}  // namespace ksys::evt

#include "Game/Actor/Action/actionEventSetAttentionForbidSale.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/ActorSystem/actTag.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"

namespace uking::action {

EventSetAttentionForbidSale::EventSetAttentionForbidSale(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventSetAttentionForbidSale::~EventSetAttentionForbidSale() = default;

bool EventSetAttentionForbidSale::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventSetAttentionForbidSale::loadParams_() {}

// NON_MATCHING: the state update is branchy here (csel in the original); loop bound test and stack layout.
bool EventSetAttentionForbidSale::oneShot_() {
    auto* link = ksys::evt::Manager::instance()->sub_7100DB22A8();
    if (!link || !link->hasProc())
        return false;

    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::acquireActor(link, &accessor);
    if (accessor.hasProc() && accessor.hasTag(ksys::act::tags::Mannequin)) {
        ksys::gdt::setFlag_PlacedItemCountState(
            ksys::act::sub_7100EE2F2C(mActor, &accessor, nullptr));
        ksys::act::sub_7100EE2850(mActor, &accessor, false, nullptr, nullptr);
    } else {
        const s32 num = ksys::gdt::getFlag_Shop_TradeItemNum();
        s32 state = 4;
        sead::LongBitFlag<256> flags;
        for (s32 i = 0; i < num; ++i) {
            const s32 result = ksys::act::sub_7100EE2F2C(mActor, &accessor, &flags);
            if (state == 4 || ((state == 0 || state == 2) && result == 1))
                state = result;
            ksys::act::ActorLinkConstDataAccess other;
            const bool grouping_item =
                ksys::act::hasTag(mActor, ksys::act::tags::GroupingDisplayItem);
            ksys::act::sub_7100EE2850(mActor, &accessor, grouping_item, &other, &flags);
            sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x300000e),
                        nullptr);
            accessor.acquireActor(other);
        }
        ksys::gdt::setFlag_PlacedItemCountState(state);
    }
    return false;
}

}  // namespace uking::action

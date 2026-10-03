#include "Game/AI/Action/actionPlayerSetVisibleWeapon.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorWeapons.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::action {

PlayerSetVisibleWeapon::PlayerSetVisibleWeapon(const InitArg& arg) : PlayerAction(arg) {}

PlayerSetVisibleWeapon::~PlayerSetVisibleWeapon() = default;

bool PlayerSetVisibleWeapon::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

// NON_MATCHING: the original keeps a branch for `visible ? 0x3000002 : 0x3000001` (we emit cinc) and
// shares the two null-return paths differently
bool PlayerSetVisibleWeapon::oneShot_() {
    if (!mActor)
        return false;
    auto* weapons = mActor->getWeapons();
    if (!weapons)
        return false;

    ksys::act::ActorConstDataAccess accessor;
    for (int i = 0; i < 3; ++i) {
        auto& link = weapons->mWeapons[i].link;
        if (link.hasProc())
            ksys::act::acquireActor(&link, &accessor);
        if (accessor.hasProc()) {
            const bool visible = *mSetVisible_d;
            const ksys::MesTransceiverId& id = *accessor.getMessageTransceiverId();
            ksys::MessageType type;
            if (visible)
                type = ksys::MessageType(0x3000002);
            else
                type = ksys::MessageType(0x3000001);
            _28.sendMessage(id, type, nullptr, false);
        }
    }
    return true;
}

void PlayerSetVisibleWeapon::loadParams_() {
    getDynamicParam(&mSetVisible_d, "SetVisible");
}

}  // namespace uking::action

#include "Game/AI/Behavior/behaviorBalloonBehavior.h"
#include "Game/UI/uiUI.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Event/evtManager.h"

namespace uking::behavior {

BalloonBehavior::BalloonBehavior(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

BalloonBehavior::~BalloonBehavior() = default;

void BalloonBehavior::m7() {
    // NON_MATCHING: register allocation and the suffix pointer arithmetic differ.
    if (!(mActor->getActorFlags2().getDirect() & 4))
        return;
    auto* ui = uking::ui::UI::instance();
    void* text = nullptr;
    if (!ksys::evt::Manager::instance()->sub_7100DB10B0("Demo_TalkASync", mActor, &text, nullptr))
        return;
    const sead::SafeString message(static_cast<const char*>(text));
    const s32 index = message.rfindIndex(":");
    if (index < 1)
        return;
    sead::FixedSafeString<64> message_set;
    message_set.copy(message, index);
    ui->sub_71010A6454(message_set, sead::SafeString(message.cstr() + index + 1), mActor, 30.0f,
                      false);
}

void BalloonBehavior::m8() {}

void BalloonBehavior::m9() {}

void BalloonBehavior::loadParams() {

}

}  // namespace uking::behavior

#include "Game/AI/aiMessage3DText.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking {

Message3DText::Message3DText() = default;

Message3DText::~Message3DText() {}

void Message3DText::sub_7100721830(ksys::act::Actor* actor, bool shout) {
    mActor = actor;
    if (actor) {
        sead::SafeString name;
        if (actor->getName() == "Npc_HiddenKorokGround" ||
            actor->getName() == "Npc_HiddenKorokFly") {
            name = "Npc_HiddenKorok";
        } else {
            ksys::act::getSameGroupActorName(&name, actor);
        }
        if (shout)
            _8.format("ShoutMsg/Shout_%s", name.cstr());
        else
            _8.format("EventFlowMsg/%s", name.cstr());
    } else if (shout) {
        _8.format("ShoutMsg/Shout_");
    } else {
        _8.format("EventFlowMsg/");
    }
    _c9 = true;
}

}  // namespace uking

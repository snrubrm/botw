#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

// Own TU: the original calls these out of line from sub_71000891C8 and the actors' AI code.
void sub_710072DC50(sead::Vector3f* gravity, ksys::act::Actor* actor) {
    ksys::act::sub_7100EE5B84(gravity, actor);
}

void sub_710072DC54(sead::Vector3f* gravity, ksys::act::Actor* actor) {
    ksys::act::sub_7100EE5C44(gravity, actor);
}

f32 sub_710072DC58(ksys::act::Actor* actor) {
    if (auto* controller = actor->getCharacterController())
        return controller->get110();
    if (auto* body = actor->getMainBody())
        return body->getGravityFactor();
    return 1.0f;
}

ksys::act::Actor* sub_710072BB4C() {
    if (auto* info = ksys::act::PlayerInfo::instance())
        return info->getPlayer_();
    return nullptr;
}

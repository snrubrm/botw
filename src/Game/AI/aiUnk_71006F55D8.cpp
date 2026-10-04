#include "Game/AI/aiUnk_71006F5B14.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

void sub_71006F55D8(ksys::act::Actor* actor) {
    if (!actor)
        return;
    if (auto* controller = actor->getCharacterController()) {
        const ksys::act::MotionType type = ksys::act::MotionType::_1;
        const ksys::act::MotionType current = controller->sub_7100F5F0E4();
        if (int(current) != int(type))
            controller->sub_7100F5F458(type);
    }
}

bool sub_71006F566C(ksys::act::Actor* actor) {
    if (!actor)
        return false;
    if (auto* controller = actor->getCharacterController())
        return controller->sub_7100F5F0E4() == ksys::act::MotionType::Hover;
    return false;
}

void sub_71006F5940(ksys::act::Chemical* chemical) {
    if (chemical)
        chemical->sub_7100D8F194();
}

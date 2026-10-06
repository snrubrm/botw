#include "Game/AI/aiUnk_71006F5B14.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

// 0x71006f54ec: the controller variants (cc != nullptr) of the actor helpers below.
void sub_71006F54EC(ksys::phys::CharacterController* controller) {
    if (controller) {
        const ksys::act::MotionType type = ksys::act::MotionType::Hover;
        const ksys::act::MotionType current = controller->sub_7100F5F0E4();
        if (int(current) != int(type))
            controller->sub_7100F5F458(type);
    }
}

void sub_71006F5538(ksys::phys::CharacterController* controller) {
    if (controller) {
        const ksys::act::MotionType type = ksys::act::MotionType::_1;
        const ksys::act::MotionType current = controller->sub_7100F5F0E4();
        if (int(current) != int(type))
            controller->sub_7100F5F458(type);
    }
}

void sub_71006F5584(ksys::act::Actor* actor) {
    if (!actor)
        return;
    if (auto* controller = actor->getCharacterController()) {
        const ksys::act::MotionType type = ksys::act::MotionType::Hover;
        const ksys::act::MotionType current = controller->sub_7100F5F0E4();
        if (int(current) != int(type))
            controller->sub_7100F5F458(type);
    }
}

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

bool sub_71006F562C(ksys::phys::CharacterController* controller) {
    return controller && controller->sub_7100F5F0E4() == ksys::act::MotionType::Hover;
}

bool sub_71006F564C(ksys::phys::CharacterController* controller) {
    return controller && controller->sub_7100F5F0E4() == ksys::act::MotionType::_0;
}

void sub_71006F5940(ksys::act::Chemical* chemical) {
    if (chemical)
        chemical->sub_7100D8F194();
}

#pragma once

namespace ksys::act {
class Actor;
}

namespace uking::dmg {
class DamageManager;
}

// Unnamed free function (0x710072BA90, CSV placeholder "Actor::getDamageMgrDerived"; its neighbours
// are getPlayerPosition / PlayerInfo::getSomeProcLink): the actor's damage manager if it is a
// uking::dmg::DamageManager.
uking::dmg::DamageManager* sub_710072BA90(ksys::act::Actor* actor);

// 0x710072bb28: disableAllAttClients(actor), then sub_71007A397C(actor) (its "Tgt" bodies become
// SensorQueryOnly).
void sub_710072BB28(ksys::act::Actor* actor);

// 0x7100728b38 (declaration only; unnamed in the CSV): reads an AI tree variable of the actor's root AI and acts on
// it (StalEnemyDie::enter_ calls it before sub_710072BB28).
void sub_7100728B38(ksys::act::Actor* actor);

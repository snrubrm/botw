#pragma once

namespace ksys::act {
class Actor;

// 0x7100ee53c4 (PickShootItemRoot; defined in actActorUtil.cpp): `if (auto* cc = actor->getCharacterController())
// cc->sub_7100F5EC30(); else if (actor->mMainBody) actor->mMainBody->addToWorld();`. Placeholder name.
void sub_7100EE53C4(Actor* actor);
// 0x7100ee5408 (PickShootItemRoot; defined in actActorUtil.cpp): the same with sub_7100F5EC44() / removeFromWorld().
void sub_7100EE5408(Actor* actor);
}  // namespace ksys::act

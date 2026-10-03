#pragma once

namespace ksys::act {
class BaseProcLink;
}  // namespace ksys::act

// Tag checks of an unnamed AI utility translation unit (0x7100736460 / 0x710073646c; neighbours
// PlayerOrEnemy::getEnemyAtkPower and the dlc::isOneHitObliterator* helpers). Names are
// placeholders.

/// Whether the linked actor has the ExplosivesEnemyAI tag.
bool sub_7100736460(ksys::act::BaseProcLink* link);
/// Whether the linked actor has the Explosive tag.
bool sub_710073646C(ksys::act::BaseProcLink* link);

/// 0x7100736414: whether the linked actor is an NPC of the "warrior" kind (ActorConstDataAccess::sub_7100022ED8;
/// TargetNPCTypeSelector). Placeholder name.
bool sub_7100736414(ksys::act::BaseProcLink* link);

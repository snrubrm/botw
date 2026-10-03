#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/AS/ASList.h"

// The bow AS checks live in their own translation unit in the original (0x7100882178, away from
// Player's virtual functions): keeping them out of actPlayer.cpp stops clang from inlining them into
// the Player slots that tail-call them.
namespace ksys::act {

bool playerIsReloadingBow(Player* player) {
    return player->getASList()->x_1(1, 1) == "BowReload" ||
           player->getASList()->x_1(1, 1) == "SquatBowReload" ||
           player->getASList()->x_1(0, 0) == "WallBowReloadL" ||
           player->getASList()->x_1(0, 0) == "WallBowReloadR";
}

bool playerIsChargingBow(Player* player) {
    return player->getASList()->x_1(1, 1) == "BowCharge" ||
           player->getASList()->x_1(1, 1) == "SquatBowCharge" ||
           player->getASList()->x_1(0, 0) == "WallBowChargeL" ||
           player->getASList()->x_1(0, 0) == "WallBowChargeR";
}

bool playerIsReloadingOrChargingOrShootingBow(Player* player) {
    return playerIsReloadingBow(player) || playerIsChargingBow(player) || player->isShootingBow();
}

}  // namespace ksys::act

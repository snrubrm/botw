#include "Game/AI/Action/actionPlayerStoleOpenEx.h"

namespace uking::action {

PlayerStoleOpenEx::PlayerStoleOpenEx(const InitArg& arg) : PlayerStoleOpenBase(arg) {}

void PlayerStoleOpenEx::m32() {
    playAS("Open", false, 0, 0, -1.0f);
}

}  // namespace uking::action

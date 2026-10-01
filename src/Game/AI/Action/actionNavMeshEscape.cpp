#include "Game/AI/Action/actionNavMeshEscape.h"

namespace uking::action {

NavMeshEscape::NavMeshEscape(const InitArg& arg) : NavMeshAction(arg) {}

void NavMeshEscape::m34() {
    playAS("Escape", true, 0, 0, -1.0f);
}

}  // namespace uking::action

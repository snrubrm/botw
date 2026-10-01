#include "Game/AI/Action/actionUnarmedLargeAttack.h"

namespace uking::action {

UnarmedLargeAttack::UnarmedLargeAttack(const InitArg& arg) : UnarmedAttack(arg) {}

UnarmedLargeAttack::~UnarmedLargeAttack() = default;

int UnarmedLargeAttack::m32() {
    return 16386;
}

}  // namespace uking::action

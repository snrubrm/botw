#include "Game/Actor/actUnk_7102366570.h"
#include "Game/Actor/actEnemy.h"

// 2026-10-07: original D1 calls the separate list erase function; preserve its own symbol.
Unk_7102366570::~Unk_7102366570() {
    if (mOwner)
        mOwner->erase(this);
}

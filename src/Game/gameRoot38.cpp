#include "Game/gameRoot38.h"
#include <thread/seadAtomic.h>
#include "Game/Scene/gameScene.h"
#include "Game/gameRoot4.h"

namespace uking {

SEAD_SINGLETON_DISPOSER_IMPL(Root38)

// 0x71025d1a10: the two flag words setFlag updates and the word hasAnyFlag / testFlag /
// doNotFreezeScene read.
struct Root38Flags {
    sead::Atomic<u32> _0;
    sead::Atomic<u32> _4;
    sead::Atomic<u32> mFlags;
};
Root38Flags sUnk_71025D1A10;

// NON_MATCHING: the original also spills `flag` to the stack (extra 0x30 frame and reloads); the
// branches and flag updates match.
bool Root38::setFlag(int flag, bool on) {
    if (_2f)
        return false;
    if (flag != 6 && isStageSelectState())
        return false;
    if (on) {
        if (!isGameSceneInitialized())
            return false;
        if (GameScene::hasLoadingScreenStarted())
            return false;
    }
    if (flag == 7)
        Root4::instance()->sub_71008BCE5C(Root4::FlagIdx::_2, !on, 2);

    const u32 bit = 1u << flag;
    if (on) {
        sUnk_71025D1A10._0.fetchOr(bit);
        sUnk_71025D1A10._4.fetchAnd(~bit);
    } else {
        sUnk_71025D1A10._0.fetchAnd(~bit);
        sUnk_71025D1A10._4.fetchOr(bit);
    }
    return true;
}

// NON_MATCHING: the original spills `flag` to the stack and reloads it; the word and shift match.
bool Root38::testFlag(int flag) const {
    return (sUnk_71025D1A10.mFlags.load() & (1u << flag)) != 0;
}

bool Root38::hasAnyFlag() const {
    return sUnk_71025D1A10.mFlags.load() != 0;
}

bool Root38::doNotFreezeScene() const {
    return sUnk_71025D1A10.mFlags.load() != 0;
}

void Root38::setField2F(bool value) {
    _2f = value;
}

}  // namespace uking

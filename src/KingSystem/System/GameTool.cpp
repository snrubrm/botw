#include "KingSystem/System/GameTool.h"

void Unk_71024f13f0::m6() {}

namespace ksys {

SEAD_SINGLETON_DISPOSER_IMPL(GameTool)

GameTool::GameTool() : Unk_71024f13f0(&mController) {
    _54.makeAllZero();
    mController.sub_7100D9DAD8();
}

GameTool::~GameTool() = default;

}  // namespace ksys

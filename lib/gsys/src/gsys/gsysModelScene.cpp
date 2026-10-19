#include <gsys/gsysModelScene.h>

namespace gsys {

void ModelScene::skipDraw() {
    mJobQueue.changeRequestFlag(true, true, false);
}

void ModelScene::calcModelUnit_(sead::WorkerMgr* wm) {
    mJobQueue.updateModelUnit(wm);
}

}  // namespace gsys

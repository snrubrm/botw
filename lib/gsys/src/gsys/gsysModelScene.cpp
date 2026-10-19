#include <gsys/gsysModelScene.h>

namespace gsys {

ModelScene::CreateArg::CreateArg()
    : _0(1), mName(sead::SafeString::cEmptyString), _18(0) {}


void ModelScene::skipDraw() {
    mJobQueue.changeRequestFlag(true, true, false);
}

void ModelScene::calcModelUnit_(sead::WorkerMgr* wm) {
    mJobQueue.updateModelUnit(wm);
}

}  // namespace gsys

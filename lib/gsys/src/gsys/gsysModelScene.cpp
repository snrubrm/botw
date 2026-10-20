#include <gsys/gsysModelScene.h>

namespace gsys {

ModelScene::CreateArg::CreateArg()
    : _0(1), mName(sead::SafeString::cEmptyString), _18(0) {}


void ModelScene::skipDraw() {
    mJobQueue.changeRequestFlag(true, true, false);
}

void ModelScene::calcWorld_(sead::WorkerMgr* wm) {
    calc(wm, 3, 7, 0);
}

void ModelScene::calcRenderView_(sead::WorkerMgr* wm) {
    calc(wm, 0, 0xc, 0);
}

void ModelScene::calcModelUnit_(sead::WorkerMgr* wm) {
    mJobQueue.updateModelUnit(wm);
}

}  // namespace gsys

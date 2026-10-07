#include "KingSystem/Resource/resTextureHandleMgr.h"
#include "Game/gameUnkRttiClasses.h"
#include "KingSystem/Utils/Thread/TaskMgr.h"
#include "KingSystem/Resource/resSystem.h"
#include "KingSystem/Utils/Thread/Task.h"
#include "KingSystem/Utils/Thread/TaskThread.h"

Unk_71024f9bb8::~Unk_71024f9bb8() = default;

namespace ksys::res {

TextureHandleMgr* TextureHandleMgr::sInstance;

void TextureHandleMgr::setInstance(TextureHandleMgr* mgr) {
    sInstance = mgr;
}

void TextureHandleMgr::calc() {
    if (!_30->canSubmitRequest())
        return;

    util::TaskRequest req;
    req.mHasHandle = false;
    req.mSynchronous = false;
    req.mLaneId = 8;
    req.mThread = _50;
    req.mName = "TextureHandleMgr::calc";
    _30->submitRequest(req);
}

void TextureHandleMgr::preCalc() {}

// 0x7100fe53bc (unnamed in the CSV): cancel everything queued on the loading thread and mark the
// manager as stopped.
void TextureHandleMgr::sub_7100FE53BC() {
    _50->cancelTasks(0);
    _50->cancelTasks(1);
    mFlags2.reset(1);
    if (!mFlags.isOn(4)) {
        mFlags.set(4);
        stubbedLogFunction();
    }
}

void TextureHandleMgr::sub_7100FE60B0(bool on) {
    if (mFlags.isOn(2) != on) {
        mFlags.change(2, on);
        stubbedLogFunction();
    }
}

void TextureHandleMgr::sub_7100FE60DC(bool on) {
    if (mFlags.isOn(1) != on) {
        mFlags.change(1, on);
        mFlags.change(4, on);
        stubbedLogFunction();
    }
}

bool TextureHandleMgr::isTooSlow(s32 seconds) {
    if (!mFlags2.isOn(4))
        return false;

    if (mTickTime.diffToNow().toSeconds() < seconds)
        return false;

    mTickTime.setNow();
    mFlags2.reset(4);
    stubbedLogFunction();
    return true;
}

bool TextureHandleMgr::sub_7100FE6120() const {
    return mFlags2.isOn(2);
}

ArchiveWork* TextureHandleMgr::getArchiveWork() const {
    return mArchiveWork;
}

void TextureHandleMgr::clearAllCache() {
    Unk_71024f9bb8 request;
    request.mHasHandle = false;
    request.mSynchronous = false;
    request.mLaneId = 7;
    request.mThread = _50;
    request.mDelegate = &_158;
    request.mName = "Texture::ClearAllCache";
    util::TaskMgrRequest manager_request;
    manager_request.request = &request;
    _48->submitRequest(manager_request);
}

}  // namespace ksys::res

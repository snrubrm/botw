#include "KingSystem/System/PlayReportMgr.h"
#include <nn/account.h>
#include <nn/prepo.h>
#include "KingSystem/System/Account.h"
#include "KingSystem/System/ProductReporter.h"

namespace ksys {

SEAD_SINGLETON_DISPOSER_IMPL(PlayReportMgr)

PlayReportMgr::~PlayReportMgr() {
    if (mReporter)
        delete mReporter;
}

void PlayReportMgr::init(sead::Heap* heap) {
    auto* reporter = new (heap) ProductReporter;
    reporter->init(heap);
    mReporter = reporter;
    if (mReporter)
        mReporter->setEnabled(true);
}

void PlayReportMgr::calc() {
    if (!_30 && mReporter)
        mReporter->updateTimers();
}

void PlayReportMgr::reportDebug(const sead::SafeString& message, const sead::SafeString& data) {
    // Stubbed in release builds
}

bool PlayReportMgr::auto0() const {
    return true;
}

PlayerTrackReporter* PlayReportMgr::getPlayerTrackReporter() const {
    if (!mReporter)
        return nullptr;
    return mReporter->getPlayerTrackReporter();
}

void PlayReportMgr::setPlayerTrackReporter28() {
    if (auto* reporter = getPlayerTrackReporter())
        reporter->_28 = true;
}

void PlayReportMgr::setPlayerTrackReporter29() {
    if (auto* reporter = getPlayerTrackReporter())
        reporter->_29 = true;
}

void PlayReportMgr::setPlayerTrackReporter30() {
    if (auto* reporter = getPlayerTrackReporter())
        reporter->_30 = true;
}

}  // namespace ksys

void ksys::PlayReportMgr::sub_7100FD3A50() {}

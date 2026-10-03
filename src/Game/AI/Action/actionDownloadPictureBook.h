#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DownloadPictureBook : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(DownloadPictureBook, ksys::act::ai::Action)
public:
    explicit DownloadPictureBook(const InitArg& arg);
    ~DownloadPictureBook() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    s32 _1c = 0;

};
KSYS_CHECK_SIZE_NX150(DownloadPictureBook, 0x20);

}  // namespace uking::action

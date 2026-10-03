#include "Game/AI/Behavior/behaviorShowConstStringBoard.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::behavior {

ShowConstStringBoard::ShowConstStringBoard(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

ShowConstStringBoard::~ShowConstStringBoard() = default;

void ShowConstStringBoard::m7() {
    _11c = sead::Color4f(mLineColor_s->x, mLineColor_s->y, mLineColor_s->z, *mLineAlpha_s);
    _f8.set(*mBGCenterOffset_s);
    _e8 = sead::Color4f(mBGColor_s->x, mBGColor_s->y, mBGColor_s->z, *mBGAlpha_s);
    _10c = *mBGRotateRadian_s;
    _e0 = {mBGScale_s->x, mBGScale_s->y};
    _98 = 0;
    _b8 = sead::Color4f(mTextColor_s->x, mTextColor_s->y, mTextColor_s->z, 1.0f);
    _b0 = *mTextScale_s;
    _c8 = sead::Color4f(mTextShadowColor_s->x, mTextShadowColor_s->y, mTextShadowColor_s->z, 1.0f);
    _d8 = {mTextShadowOffset_s->x, mTextShadowOffset_s->y};
    getStaticParam(&mText_s, "Text");
    _a0 = mText_s;
    mActor->getMtx().getTranslation(_110);
}

void ShowConstStringBoard::m8() {}

void ShowConstStringBoard::m9() {}

// NON_MATCHING: the trailing `SafeString = mText_s` copy (the stubbed string board's call argument) is
// built in a 24-byte stack object in the original (an extra zero qword after the SafeString), which
// moves every parameter-name temporary up by 8 bytes.
void ShowConstStringBoard::loadParams() {
    getStaticParam(&mTextScale_s, "TextScale");
    getStaticParam(&mBGRotateRadian_s, "BGRotateRadian");
    getStaticParam(&mBGAlpha_s, "BGAlpha");
    getStaticParam(&mLineAlpha_s, "LineAlpha");
    getStaticParam(&mText_s, "Text");
    getStaticParam(&mTextColor_s, "TextColor");
    getStaticParam(&mTextShadowOffset_s, "TextShadowOffset");
    getStaticParam(&mTextShadowColor_s, "TextShadowColor");
    getStaticParam(&mBGScale_s, "BGScale");
    getStaticParam(&mBGCenterOffset_s, "BGCenterOffset");
    getStaticParam(&mBGColor_s, "BGColor");
    getStaticParam(&mLineColor_s, "LineColor");
    sead::SafeString text;
    text = mText_s;
}

}  // namespace uking::behavior

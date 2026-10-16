#include "KingSystem/Sound/sndEnvBgmNode.h"

// The environment BGM TU (0x7101003df4..0x71010073b0): the node constructors; the nodes' inline virtuals are
// emitted at its end (0x7101006940..).

namespace ksys::snd {

// NON_MATCHING: the flag argument is masked with `and #1` before it is stored (the original stores w3 as is).
Unk_71024fdb98::Unk_71024fdb98(Unk_71024fdb00* owner, const sead::SafeString& name, bool flag,
                               const agl::utl::Parameter<u32>* wait_count,
                               const MusicInfo::MinMax<f32>* volume, const MusicInfo::MinMax<f32>* pan)
    : Unk_EnvBgmNode(owner), mFlag(flag), mWaitCount(wait_count), mVolume(volume),
      mPan(pan) {
    mName.append(name);
}

Unk_71024fdbe8::Unk_71024fdbe8(Unk_71024fdb00* owner, const sead::SafeString& name,
                               const MusicInfo::MinMax<f32>* volume, const MusicInfo::MinMax<f32>* pan)
    : Unk_EnvBgmNode(owner), mVolume(volume), mPan(pan) {
    mName.append(name);
}

// NON_MATCHING: the flag argument is masked with `and #1` before it is stored (the original stores w3 as is).
Unk_71024fdc38::Unk_71024fdc38(Unk_71024fdb00* owner, const sead::SafeString& name, bool flag,
                               const agl::utl::Parameter<u32>* wait_count,
                               const MusicInfo::MinMax<f32>* volume, const MusicInfo::MinMax<f32>* pan)
    : Unk_EnvBgmNode(owner), mFlag(flag), mWaitCount(wait_count), mVolume(volume),
      mPan(pan) {
    mName.append(name);
}

// NON_MATCHING: the flag argument is masked with `and #1` before it is stored (the original stores w3 as is).
Unk_71024fdc88::Unk_71024fdc88(Unk_71024fdb00* owner, const sead::SafeString& name, bool flag,
                               const agl::utl::Parameter<u32>* wait_count_base,
                               const MusicInfo::MinMax<u32>* wait_count_rate,
                               const MusicInfo::MinMax<f32>* volume, const MusicInfo::MinMax<f32>* pan)
    : Unk_EnvBgmNode(owner), mFlag(flag), mWaitCountBase(wait_count_base),
      mWaitCountRate(wait_count_rate), mVolume(volume), mPan(pan) {
    mName.append(name);
}

}  // namespace ksys::snd

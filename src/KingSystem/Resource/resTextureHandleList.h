#pragma once

namespace ksys::res {

// TODO: very incomplete
class TextureHandleList {
public:
    virtual ~TextureHandleList();

    // 0x71012bd6bc (declared only): clears the list under its lock.
    void sub_71012BD6BC();
};

}  // namespace ksys::res

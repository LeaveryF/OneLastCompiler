#include <type_traits>

// 基本的类型定义和isa实现
template <typename T, typename F>
struct CastInfo {
    static bool isPossible(const F *f) {
        return T::classof(f);
    }

    static T *doCast(F *f) {
        return static_cast<T *>(f);
    }

    static T *castFailed() {
        return nullptr;
    }

    static T *doCastIfPossible(F *f) {
        if (!isPossible(f))
            return castFailed();
        return doCast(f);
    }
};

template <typename T, typename F>
bool isa(const F *f) {
    if constexpr (std::is_base_of_v<T, F>) {
        return true;
    } else {
        return CastInfo<T, F>::isPossible(f);
    }
}

template <typename T, typename F>
T *cast(F *f) {
    return CastInfo<T, F>::doCast(f);
}

template <typename T, typename F>
const T *cast(const F *f) {
    return CastInfo<T, F>::doCast(f);
}

template <typename T, typename F>
T *dyn_cast(F *f) {
    return isa<T>(f) ? cast<T>(f) : nullptr;
}

template <typename T, typename F>
const T *dyn_cast(const F *f) {
    return isa<T>(f) ? cast<T>(f) : nullptr;
}

template <typename T, typename F>
T *dyn_cast_nullable(F *f) {
    return f && isa<T>(f) ? cast<T>(f) : nullptr;
}

template <typename T, typename F>
const T *dyn_cast_nullable(const F *f) {
    return f && isa<T>(f) ? cast<T>(f) : nullptr;
}
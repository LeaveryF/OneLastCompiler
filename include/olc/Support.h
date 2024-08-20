#pragma once

#include <cassert>
#include <functional>
#include <iostream>
#include <type_traits>

namespace olc {

[[noreturn]] inline void
unreachable(const char *file, int line, const char *msg) {
#ifndef NDEBUG
  std::fprintf(stderr, "%s:%d: unreachable: %s\n", file, line, msg);
#endif
  __builtin_unreachable();
}

#define olc_unreachable(msg) olc::unreachable(__FILE__, __LINE__, msg)

/// RTTI infrastructure from LLVM
/// llvm-project/llvm/include/llvm/Support/Casting.h

//===----------------------------------------------------------------------===//
// type traits
//===----------------------------------------------------------------------===//

/// If T is a pointer, just return it. If it is not, return T&.
template <typename T, typename Enable = void>
struct add_lvalue_reference_if_not_pointer {
  using type = T &;
};

template <typename T>
struct add_lvalue_reference_if_not_pointer<
    T, std::enable_if_t<std::is_pointer_v<T>>> {
  using type = T;
};

/// If T is a pointer to X, return a pointer to const X. If it is not,
/// return const T.
template <typename T, typename Enable = void> struct add_const_past_pointer {
  using type = const T;
};

template <typename T>
struct add_const_past_pointer<T, std::enable_if_t<std::is_pointer_v<T>>> {
  using type = const std::remove_pointer_t<T> *;
};

//===----------------------------------------------------------------------===//
// simplify_type
//===----------------------------------------------------------------------===//

/// Define a template that can be specialized by smart pointers to reflect the
/// fact that they are automatically dereferenced, and are not involved with the
/// template selection process...  the default implementation is a noop.
// TODO: rename this and/or replace it with other cast traits.
template <typename From> struct simplify_type {
  using SimpleType = From; // The real type this represents...

  // An accessor to get the real value...
  static SimpleType &getSimplifiedValue(From &Val) { return Val; }
};

template <typename From> struct simplify_type<const From> {
  using NonConstSimpleType = typename simplify_type<From>::SimpleType;
  using SimpleType = typename add_const_past_pointer<NonConstSimpleType>::type;
  using RetType =
      typename add_lvalue_reference_if_not_pointer<SimpleType>::type;

  static RetType getSimplifiedValue(const From &Val) {
    return simplify_type<From>::getSimplifiedValue(const_cast<From &>(Val));
  }
};

//===----------------------------------------------------------------------===//
// isa_impl
//===----------------------------------------------------------------------===//

// The core of the implementation of isa<X> is here; To and From should be
// the names of classes.  This template can be specialized to customize the
// implementation of isa<> without rewriting it from scratch.
template <typename To, typename From, typename Enabler = void> struct isa_impl {
  static inline bool doit(const From &Val) { return To::classof(&Val); }
};

// Always allow upcasts, and perform no dynamic check for them.
template <typename To, typename From>
struct isa_impl<To, From, std::enable_if_t<std::is_base_of_v<To, From>>> {
  static inline bool doit(const From &) { return true; }
};

template <typename To, typename From> struct isa_impl_cl {
  static inline bool doit(const From &Val) {
    return isa_impl<To, From>::doit(Val);
  }
};

template <typename To, typename From> struct isa_impl_cl<To, const From> {
  static inline bool doit(const From &Val) {
    return isa_impl<To, From>::doit(Val);
  }
};

template <typename To, typename From> struct isa_impl_cl<To, From *> {
  static inline bool doit(const From *Val) {
    assert(Val && "isa<> used on a null pointer");
    return isa_impl<To, From>::doit(*Val);
  }
};

template <typename To, typename From> struct isa_impl_cl<To, From *const> {
  static inline bool doit(const From *Val) {
    assert(Val && "isa<> used on a null pointer");
    return isa_impl<To, From>::doit(*Val);
  }
};

template <typename To, typename From> struct isa_impl_cl<To, const From *> {
  static inline bool doit(const From *Val) {
    assert(Val && "isa<> used on a null pointer");
    return isa_impl<To, From>::doit(*Val);
  }
};

template <typename To, typename From>
struct isa_impl_cl<To, const From *const> {
  static inline bool doit(const From *Val) {
    assert(Val && "isa<> used on a null pointer");
    return isa_impl<To, From>::doit(*Val);
  }
};

template <typename To, typename From, typename SimpleFrom>
struct isa_impl_wrap {
  // When From != SimplifiedType, we can simplify the type some more by using
  // the simplify_type template.
  static bool doit(const From &Val) {
    return isa_impl_wrap<
        To, SimpleFrom, typename simplify_type<SimpleFrom>::SimpleType>::
        doit(simplify_type<const From>::getSimplifiedValue(Val));
  }
};

template <typename To, typename FromTy>
struct isa_impl_wrap<To, FromTy, FromTy> {
  // When From == SimpleType, we are as simple as we are going to get.
  static bool doit(const FromTy &Val) {
    return isa_impl_cl<To, FromTy>::doit(Val);
  }
};

//===----------------------------------------------------------------------===//
// cast_retty + cast_retty_impl
//===----------------------------------------------------------------------===//

template <class To, class From> struct cast_retty;

// Calculate what type the 'cast' function should return, based on a requested
// type of To and a source type of From.
template <class To, class From> struct cast_retty_impl {
  using ret_type = To &; // Normal case, return Ty&
};
template <class To, class From> struct cast_retty_impl<To, const From> {
  using ret_type = const To &; // Normal case, return Ty&
};

template <class To, class From> struct cast_retty_impl<To, From *> {
  using ret_type = To *; // Pointer arg case, return Ty*
};

template <class To, class From> struct cast_retty_impl<To, const From *> {
  using ret_type = const To *; // Constant pointer arg case, return const Ty*
};

template <class To, class From> struct cast_retty_impl<To, const From *const> {
  using ret_type = const To *; // Constant pointer arg case, return const Ty*
};

template <class To, class From, class SimpleFrom> struct cast_retty_wrap {
  // When the simplified type and the from type are not the same, use the type
  // simplifier to reduce the type, then reuse cast_retty_impl to get the
  // resultant type.
  using ret_type = typename cast_retty<To, SimpleFrom>::ret_type;
};

template <class To, class FromTy> struct cast_retty_wrap<To, FromTy, FromTy> {
  // When the simplified type is equal to the from type, use it directly.
  using ret_type = typename cast_retty_impl<To, FromTy>::ret_type;
};

template <class To, class From> struct cast_retty {
  using ret_type = typename cast_retty_wrap<
      To, From, typename simplify_type<From>::SimpleType>::ret_type;
};

//===----------------------------------------------------------------------===//
// cast_convert_val
//===----------------------------------------------------------------------===//

// Ensure the non-simple values are converted using the simplify_type template
// that may be specialized by smart pointers...
//
template <class To, class From, class SimpleFrom> struct cast_convert_val {
  // This is not a simple type, use the template to simplify it...
  static typename cast_retty<To, From>::ret_type doit(const From &Val) {
    return cast_convert_val<
        To, SimpleFrom, typename simplify_type<SimpleFrom>::SimpleType>::
        doit(simplify_type<From>::getSimplifiedValue(const_cast<From &>(Val)));
  }
};

template <class To, class FromTy> struct cast_convert_val<To, FromTy, FromTy> {
  // If it's a reference, switch to a pointer to do the cast and then deref it.
  static typename cast_retty<To, FromTy>::ret_type doit(const FromTy &Val) {
    return *(std::remove_reference_t<typename cast_retty<To, FromTy>::ret_type>
                 *)&const_cast<FromTy &>(Val);
  }
};

template <class To, class FromTy>
struct cast_convert_val<To, FromTy *, FromTy *> {
  // If it's a pointer, we can use c-style casting directly.
  static typename cast_retty<To, FromTy *>::ret_type doit(const FromTy *Val) {
    return (typename cast_retty<To, FromTy *>::ret_type) const_cast<FromTy *>(
        Val);
  }
};

//===----------------------------------------------------------------------===//
// is_simple_type
//===----------------------------------------------------------------------===//

template <class X> struct is_simple_type {
  static const bool value =
      std::is_same_v<X, typename simplify_type<X>::SimpleType>;
};

// } // namespace detail

//===----------------------------------------------------------------------===//
// CastIsPossible
//===----------------------------------------------------------------------===//

/// This struct provides a way to check if a given cast is possible. It provides
/// a static function called isPossible that is used to check if a cast can be
/// performed. It should be overridden like this:
///
/// template<> struct CastIsPossible<foo, bar> {
///   static inline bool isPossible(const bar &b) {
///     return bar.isFoo();
///   }
/// };
template <typename To, typename From, typename Enable = void>
struct CastIsPossible {
  static inline bool isPossible(const From &f) {
    return isa_impl_wrap<
        To, const From,
        typename simplify_type<const From>::SimpleType>::doit(f);
  }
};

/// Upcasting (from derived to base) and casting from a type to itself should
/// always be possible.
template <typename To, typename From>
struct CastIsPossible<To, From, std::enable_if_t<std::is_base_of_v<To, From>>> {
  static inline bool isPossible(const From &f) { return true; }
};

//===----------------------------------------------------------------------===//
// Cast traits
//===----------------------------------------------------------------------===//

/// All of these cast traits are meant to be implementations for useful casts
/// that users may want to use that are outside the standard behavior. An
/// example of how to use a special cast called `CastTrait` is:
///
/// template<> struct CastInfo<foo, bar> : public CastTrait<foo, bar> {};
///
/// Essentially, if your use case falls directly into one of the use cases
/// supported by a given cast trait, simply inherit your special CastInfo
/// directly from one of these to avoid having to reimplement the boilerplate
/// `isPossible/castFailed/doCast/doCastIfPossible`. A cast trait can also
/// provide a subset of those functions.

/// This cast trait just provides castFailed for the specified `To` type to make
/// CastInfo specializations more declarative. In order to use this, the target
/// result type must be `To` and `To` must be constructible from `nullptr`.
template <typename To> struct NullableValueCastFailed {
  static To castFailed() { return To(nullptr); }
};

/// This cast trait just provides the default implementation of doCastIfPossible
/// to make CastInfo specializations more declarative. The `Derived` template
/// parameter *must* be provided for forwarding castFailed and doCast.
template <typename To, typename From, typename Derived>
struct DefaultDoCastIfPossible {
  static To doCastIfPossible(From f) {
    if (!Derived::isPossible(f))
      return Derived::castFailed();
    return Derived::doCast(f);
  }
};

namespace detail {
/// A helper to derive the type to use with `Self` for cast traits, when the
/// provided CRTP derived type is allowed to be void.
template <typename OptionalDerived, typename Default>
using SelfType = std::conditional_t<
    std::is_same_v<OptionalDerived, void>, Default, OptionalDerived>;
} // namespace detail

/// This cast trait provides casting for the specific case of casting to a
/// value-typed object from a pointer-typed object. Note that `To` must be
/// nullable/constructible from a pointer to `From` to use this cast.
template <typename To, typename From, typename Derived = void>
struct ValueFromPointerCast
    : public CastIsPossible<To, From *>,
      public NullableValueCastFailed<To>,
      public DefaultDoCastIfPossible<
          To, From *,
          detail::SelfType<Derived, ValueFromPointerCast<To, From>>> {
  static inline To doCast(From *f) { return To(f); }
};

/// Provides a cast trait that strips `const` from types to make it easier to
/// implement a const-version of a non-const cast. It just removes boilerplate
/// and reduces the amount of code you as the user need to implement. You can
/// use it like this:
///
/// template<> struct CastInfo<foo, bar> {
///   ...verbose implementation...
/// };
///
/// template<> struct CastInfo<foo, const bar> : public
///        ConstStrippingForwardingCast<foo, const bar, CastInfo<foo, bar>> {};
///
template <typename To, typename From, typename ForwardTo>
struct ConstStrippingForwardingCast {
  // Remove the pointer if it exists, then we can get rid of consts/volatiles.
  using DecayedFrom = std::remove_cv_t<std::remove_pointer_t<From>>;
  // Now if it's a pointer, add it back. Otherwise, we want a ref.
  using NonConstFrom =
      std::conditional_t<std::is_pointer_v<From>, DecayedFrom *, DecayedFrom &>;

  static inline bool isPossible(const From &f) {
    return ForwardTo::isPossible(const_cast<NonConstFrom>(f));
  }

  static inline decltype(auto) castFailed() { return ForwardTo::castFailed(); }

  static inline decltype(auto) doCast(const From &f) {
    return ForwardTo::doCast(const_cast<NonConstFrom>(f));
  }

  static inline decltype(auto) doCastIfPossible(const From &f) {
    return ForwardTo::doCastIfPossible(const_cast<NonConstFrom>(f));
  }
};

/// Provides a cast trait that uses a defined pointer to pointer cast as a base
/// for reference-to-reference casts. Note that it does not provide castFailed
/// and doCastIfPossible because a pointer-to-pointer cast would likely just
/// return `nullptr` which could cause nullptr dereference. You can use it like
/// this:
///
///   template <> struct CastInfo<foo, bar *> { ... verbose implementation... };
///
///   template <>
///   struct CastInfo<foo, bar>
///       : public ForwardToPointerCast<foo, bar, CastInfo<foo, bar *>> {};
///
template <typename To, typename From, typename ForwardTo>
struct ForwardToPointerCast {
  static inline bool isPossible(const From &f) {
    return ForwardTo::isPossible(&f);
  }

  static inline decltype(auto) doCast(const From &f) {
    return *ForwardTo::doCast(&f);
  }
};

//===----------------------------------------------------------------------===//
// CastInfo
//===----------------------------------------------------------------------===//

/// This struct provides a method for customizing the way a cast is performed.
/// It inherits from CastIsPossible, to support the case of declaring many
/// CastIsPossible specializations without having to specialize the full
/// CastInfo.
///
/// In order to specialize different behaviors, specify different functions in
/// your CastInfo specialization.
/// For isa<> customization, provide:
///
///   `static bool isPossible(const From &f)`
///
/// For cast<> customization, provide:
///
///  `static To doCast(const From &f)`
///
/// For dyn_cast<> and the *_if_present<> variants' customization, provide:
///
///  `static To castFailed()` and `static To doCastIfPossible(const From &f)`
///
/// Your specialization might look something like this:
///
///  template<> struct CastInfo<foo, bar> : public CastIsPossible<foo, bar> {
///    static inline foo doCast(const bar &b) {
///      return foo(const_cast<bar &>(b));
///    }
///    static inline foo castFailed() { return foo(); }
///    static inline foo doCastIfPossible(const bar &b) {
///      if (!CastInfo<foo, bar>::isPossible(b))
///        return castFailed();
///      return doCast(b);
///    }
///  };

// The default implementations of CastInfo don't use cast traits for now because
// we need to specify types all over the place due to the current expected
// casting behavior and the way cast_retty works. New use cases can and should
// take advantage of the cast traits whenever possible!

template <typename To, typename From, typename Enable = void>
struct CastInfo : public CastIsPossible<To, From> {
  using Self = CastInfo<To, From, Enable>;

  using CastReturnType = typename cast_retty<To, From>::ret_type;

  static inline CastReturnType doCast(const From &f) {
    return cast_convert_val<
        To, From,
        typename simplify_type<From>::SimpleType>::doit(const_cast<From &>(f));
  }

  // This assumes that you can construct the cast return type from `nullptr`.
  // This is largely to support legacy use cases - if you don't want this
  // behavior you should specialize CastInfo for your use case.
  static inline CastReturnType castFailed() { return CastReturnType(nullptr); }

  static inline CastReturnType doCastIfPossible(const From &f) {
    if (!Self::isPossible(f))
      return castFailed();
    return doCast(f);
  }
};

/// This struct provides an overload for CastInfo where From has simplify_type
/// defined. This simply forwards to the appropriate CastInfo with the
/// simplified type/value, so you don't have to implement both.
template <typename To, typename From>
struct CastInfo<To, From, std::enable_if_t<!is_simple_type<From>::value>> {
  using Self = CastInfo<To, From>;
  using SimpleFrom = typename simplify_type<From>::SimpleType;
  using SimplifiedSelf = CastInfo<To, SimpleFrom>;

  static inline bool isPossible(From &f) {
    return SimplifiedSelf::isPossible(
        simplify_type<From>::getSimplifiedValue(f));
  }

  static inline decltype(auto) doCast(From &f) {
    return SimplifiedSelf::doCast(simplify_type<From>::getSimplifiedValue(f));
  }

  static inline decltype(auto) castFailed() {
    return SimplifiedSelf::castFailed();
  }

  static inline decltype(auto) doCastIfPossible(From &f) {
    return SimplifiedSelf::doCastIfPossible(
        simplify_type<From>::getSimplifiedValue(f));
  }
};

/// isa<X> - Return true if the parameter to the template is an instance of one
/// of the template type arguments.  Used like this:
///
///  if (isa<Type>(myVal)) { ... }
///  if (isa<Type0, Type1, Type2>(myVal)) { ... }
template <typename To, typename From>
[[nodiscard]] inline bool isa(const From &Val) {
  return CastInfo<To, const From>::isPossible(Val);
}

template <typename First, typename Second, typename... Rest, typename From>
[[nodiscard]] inline bool isa(const From &Val) {
  return isa<First>(Val) || isa<Second, Rest...>(Val);
}

/// cast<X> - Return the argument parameter cast to the specified type.  This
/// casting operator asserts that the type is correct, so it does not return
/// null on failure.  It does not allow a null argument (use cast_if_present for
/// that). It is typically used like this:
///
///  cast<Instruction>(myVal)->getParent()

template <typename To, typename From>
[[nodiscard]] inline decltype(auto) cast(const From &Val) {
  assert(isa<To>(Val) && "cast<Ty>() argument of incompatible type!");
  return CastInfo<To, const From>::doCast(Val);
}

template <typename To, typename From>
[[nodiscard]] inline decltype(auto) cast(From &Val) {
  assert(isa<To>(Val) && "cast<Ty>() argument of incompatible type!");
  return CastInfo<To, From>::doCast(Val);
}

template <typename To, typename From>
[[nodiscard]] inline decltype(auto) cast(From *Val) {
  assert(isa<To>(Val) && "cast<Ty>() argument of incompatible type!");
  return CastInfo<To, From *>::doCast(Val);
}

//===----------------------------------------------------------------------===//
// ValueIsPresent
//===----------------------------------------------------------------------===//

template <typename T>
constexpr bool IsNullable =
    std::is_pointer_v<T> || std::is_constructible_v<T, std::nullptr_t>;

/// ValueIsPresent provides a way to check if a value is, well, present. For
/// pointers, this is the equivalent of checking against nullptr, for Optionals
/// this is the equivalent of checking hasValue(). It also provides a method for
/// unwrapping a value (think calling .value() on an optional).

// Generic values can't *not* be present.
template <typename T, typename Enable = void> struct ValueIsPresent {
  using UnwrappedType = T;
  static inline bool isPresent(const T &t) { return true; }
  static inline decltype(auto) unwrapValue(T &t) { return t; }
};

// If something is "nullable" then we just compare it to nullptr to see if it
// exists.
template <typename T>
struct ValueIsPresent<T, std::enable_if_t<IsNullable<T>>> {
  using UnwrappedType = T;
  static inline bool isPresent(const T &t) { return t != T(nullptr); }
  static inline decltype(auto) unwrapValue(T &t) { return t; }
};

namespace detail {
// Convenience function we can use to check if a value is present. Because of
// simplify_type, we have to call it on the simplified type for now.
template <typename T> inline bool isPresent(const T &t) {
  return ValueIsPresent<typename simplify_type<T>::SimpleType>::isPresent(
      simplify_type<T>::getSimplifiedValue(const_cast<T &>(t)));
}

// Convenience function we can use to unwrap a value.
template <typename T> inline decltype(auto) unwrapValue(T &t) {
  return ValueIsPresent<T>::unwrapValue(t);
}
} // namespace detail

/// dyn_cast<X> - Return the argument parameter cast to the specified type. This
/// casting operator returns null if the argument is of the wrong type, so it
/// can be used to test for a type as well as cast if successful. The value
/// passed in must be present, if not, use dyn_cast_if_present. This should be
/// used in the context of an if statement like this:
///
///  if (const Instruction *I = dyn_cast<Instruction>(myVal)) { ... }

template <typename To, typename From>
[[nodiscard]] inline decltype(auto) dyn_cast(const From &Val) {
  assert(detail::isPresent(Val) && "dyn_cast on a non-existent value");
  return CastInfo<To, const From>::doCastIfPossible(Val);
}

template <typename To, typename From>
[[nodiscard]] inline decltype(auto) dyn_cast(From &Val) {
  assert(detail::isPresent(Val) && "dyn_cast on a non-existent value");
  return CastInfo<To, From>::doCastIfPossible(Val);
}

template <typename To, typename From>
[[nodiscard]] inline decltype(auto) dyn_cast(From *Val) {
  assert(detail::isPresent(Val) && "dyn_cast on a non-existent value");
  return CastInfo<To, From *>::doCastIfPossible(Val);
}

/// isa_and_present<X> - Functionally identical to isa, except that a null value
/// is accepted.
template <typename... X, class Y>
[[nodiscard]] inline bool isa_and_present(const Y &Val) {
  if (!detail::isPresent(Val))
    return false;
  return isa<X...>(Val);
}

template <typename... X, class Y>
[[nodiscard]] inline bool isa_and_nonnull(const Y &Val) {
  return isa_and_present<X...>(Val);
}

/// cast_if_present<X> - Functionally identical to cast, except that a null
/// value is accepted.
template <class X, class Y>
[[nodiscard]] inline auto cast_if_present(const Y &Val) {
  if (!detail::isPresent(Val))
    return CastInfo<X, const Y>::castFailed();
  assert(isa<X>(Val) && "cast_if_present<Ty>() argument of incompatible type!");
  return cast<X>(detail::unwrapValue(Val));
}

template <class X, class Y> [[nodiscard]] inline auto cast_if_present(Y &Val) {
  if (!detail::isPresent(Val))
    return CastInfo<X, Y>::castFailed();
  assert(isa<X>(Val) && "cast_if_present<Ty>() argument of incompatible type!");
  return cast<X>(detail::unwrapValue(Val));
}

template <class X, class Y> [[nodiscard]] inline auto cast_if_present(Y *Val) {
  if (!detail::isPresent(Val))
    return CastInfo<X, Y *>::castFailed();
  assert(isa<X>(Val) && "cast_if_present<Ty>() argument of incompatible type!");
  return cast<X>(detail::unwrapValue(Val));
}

// Provide a forwarding from cast_or_null to cast_if_present for current
// users. This is deprecated and will be removed in a future patch, use
// cast_if_present instead.
template <class X, class Y> auto cast_or_null(const Y &Val) {
  return cast_if_present<X>(Val);
}

template <class X, class Y> auto cast_or_null(Y &Val) {
  return cast_if_present<X>(Val);
}

template <class X, class Y> auto cast_or_null(Y *Val) {
  return cast_if_present<X>(Val);
}

/// dyn_cast_if_present<X> - Functionally identical to dyn_cast, except that a
/// null (or none in the case of optionals) value is accepted.
template <class X, class Y> auto dyn_cast_if_present(const Y &Val) {
  if (!detail::isPresent(Val))
    return CastInfo<X, const Y>::castFailed();
  return CastInfo<X, const Y>::doCastIfPossible(detail::unwrapValue(Val));
}

template <class X, class Y> auto dyn_cast_if_present(Y &Val) {
  if (!detail::isPresent(Val))
    return CastInfo<X, Y>::castFailed();
  return CastInfo<X, Y>::doCastIfPossible(detail::unwrapValue(Val));
}

template <class X, class Y> auto dyn_cast_if_present(Y *Val) {
  if (!detail::isPresent(Val))
    return CastInfo<X, Y *>::castFailed();
  return CastInfo<X, Y *>::doCastIfPossible(detail::unwrapValue(Val));
}

// Forwards to dyn_cast_if_present to avoid breaking current users. This is
// deprecated and will be removed in a future patch, use
// cast_if_present instead.
template <class X, class Y> auto dyn_cast_or_null(const Y &Val) {
  return dyn_cast_if_present<X>(Val);
}

template <class X, class Y> auto dyn_cast_or_null(Y &Val) {
  return dyn_cast_if_present<X>(Val);
}

template <class X, class Y> auto dyn_cast_or_null(Y *Val) {
  return dyn_cast_if_present<X>(Val);
}

//===----------------------------------------------------------------------===//
// Isa Predicates
//===----------------------------------------------------------------------===//

/// These are wrappers over isa* function that allow them to be used in generic
/// algorithms such as `llvm:all_of`, `llvm::none_of`, etc. This is accomplished
/// by exposing the isa* functions through function objects with a generic
/// function call operator.

namespace detail {
template <typename... Types> struct IsaCheckPredicate {
  template <typename T> [[nodiscard]] bool operator()(const T &Val) const {
    return isa<Types...>(Val);
  }
};

template <typename... Types> struct IsaAndPresentCheckPredicate {
  template <typename T> [[nodiscard]] bool operator()(const T &Val) const {
    return isa_and_present<Types...>(Val);
  }
};
} // namespace detail

/// Function object wrapper for the `llvm::isa` type check. The function call
/// operator returns true when the value can be cast to any type in `Types`.
/// Example:
/// ```
/// SmallVector<Type> myTypes = ...;
/// if (llvm::all_of(myTypes, llvm::IsaPred<VectorType>))
///   ...
/// ```
template <typename... Types>
inline constexpr detail::IsaCheckPredicate<Types...> IsaPred{};

/// Function object wrapper for the `llvm::isa_and_present` type check. The
/// function call operator returns true when the value can be cast to any type
/// in `Types`, or if the value is not present (e.g., nullptr). Example:
/// ```
/// SmallVector<Type> myTypes = ...;
/// if (llvm::all_of(myTypes, llvm::IsaAndPresentPred<VectorType>))
///   ...
/// ```
template <typename... Types>
inline constexpr detail::IsaAndPresentCheckPredicate<Types...>
    IsaAndPresentPred{};

template <typename T> void hash_combine(std::size_t &seed, T const &v) {
  std::hash<T> hasher;
  seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

/// set_union(A, B) - Compute A := A u B, return whether A changed.
///
template <class S1Ty, class S2Ty> bool set_union(S1Ty &S1, const S2Ty &S2) {
  bool Changed = false;

  for (typename S2Ty::const_iterator SI = S2.begin(), SE = S2.end(); SI != SE;
       ++SI)
    if (S1.insert(*SI).second)
      Changed = true;

  return Changed;
}

/// set_intersect(A, B) - Compute A := A ^ B
/// Identical to set_intersection, except that it works on set<>'s and
/// is nicer to use.  Functionally, this iterates through S1, removing
/// elements that are not contained in S2.
///
template <class S1Ty, class S2Ty> void set_intersect(S1Ty &S1, const S2Ty &S2) {
  for (typename S1Ty::iterator I = S1.begin(); I != S1.end();) {
    const auto &E = *I;
    ++I;
    if (!S2.count(E))
      S1.erase(E); // Erase element if not in S2
  }
}

template <class S1Ty, class S2Ty>
S1Ty set_intersection_impl(const S1Ty &S1, const S2Ty &S2) {
  S1Ty Result;
  for (typename S1Ty::const_iterator SI = S1.begin(), SE = S1.end(); SI != SE;
       ++SI)
    if (S2.count(*SI))
      Result.insert(*SI);
  return Result;
}

/// set_intersection(A, B) - Return A ^ B
template <class S1Ty, class S2Ty>
S1Ty set_intersection(const S1Ty &S1, const S2Ty &S2) {
  if (S1.size() < S2.size())
    return set_intersection_impl(S1, S2);
  else
    return set_intersection_impl(S2, S1);
}

/// set_difference(A, B) - Return A - B
///
template <class S1Ty, class S2Ty>
S1Ty set_difference(const S1Ty &S1, const S2Ty &S2) {
  S1Ty Result;
  for (typename S1Ty::const_iterator SI = S1.begin(), SE = S1.end(); SI != SE;
       ++SI)
    if (!S2.count(*SI)) // if the element is not in set2
      Result.insert(*SI);
  return Result;
}

/// set_subtract(A, B) - Compute A := A - B
///
template <class S1Ty, class S2Ty> void set_subtract(S1Ty &S1, const S2Ty &S2) {
  for (typename S2Ty::const_iterator SI = S2.begin(), SE = S2.end(); SI != SE;
       ++SI)
    S1.erase(*SI);
}

/// set_subtract(A, B, C, D) - Compute A := A - B, set C to the elements of B
/// removed from A (A ^ B), and D to the elements of B not found in and removed
/// from A (B - A).
template <class S1Ty, class S2Ty>
void set_subtract(S1Ty &S1, const S2Ty &S2, S1Ty &Removed, S1Ty &Remaining) {
  for (typename S2Ty::const_iterator SI = S2.begin(), SE = S2.end(); SI != SE;
       ++SI)
    if (S1.erase(*SI))
      Removed.insert(*SI);
    else
      Remaining.insert(*SI);
}

/// set_is_subset(A, B) - Return true iff A in B
///
template <class S1Ty, class S2Ty>
bool set_is_subset(const S1Ty &S1, const S2Ty &S2) {
  if (S1.size() > S2.size())
    return false;
  for (const auto It : S1)
    if (!S2.count(It))
      return false;
  return true;
}

template <class INode> struct IList;

template <class T> struct IListNode {
  T *Next = nullptr;
  T *Prev = nullptr;
};

template <class INode> struct IList {
  INode *Head = nullptr;
  INode *Tail = nullptr;

  void push_back(INode *Node) {
    if (Tail) {
      Tail->Next = Node;
      Node->Prev = Tail;
      Tail = Node;
    } else {
      Head = Tail = Node;
    }
  }

  void push_front(INode *Node) {
    if (Head) {
      Head->Prev = Node;
      Node->Next = Head;
      Head = Node;
    } else {
      Head = Tail = Node;
    }
  }

  void push_before(INode *Before, INode *Node) {
    if (Before->Prev) {
      Before->Prev->Next = Node;
      Node->Prev = Before->Prev;
    } else {
      Head = Node;
      Node->Prev = nullptr;
    }
    Node->Next = Before;
    Before->Prev = Node;
  }

  void push_after(INode *After, INode *Node) {
    if (After->Next) {
      After->Next->Prev = Node;
      Node->Next = After->Next;
    } else {
      Tail = Node;
      Node->Next = nullptr;
    }
    Node->Prev = After;
    After->Next = Node;
  }

  void remove(INode *Node) {
    if (Node->Prev)
      Node->Prev->Next = Node->Next;
    else
      Head = Node->Next;

    if (Node->Next)
      Node->Next->Prev = Node->Prev;
    else
      Tail = Node->Prev;
  }

  bool empty() const { return Head == nullptr; }

  void clear() { Head = Tail = nullptr; }
};

} // namespace olc

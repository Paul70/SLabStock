// Generated by the protocol buffer compiler.  DO NOT EDIT!
// NO CHECKED-IN PROTOBUF GENCODE
// source: stock_info.proto
// Protobuf C++ Version: 5.27.0

#ifndef GOOGLE_PROTOBUF_INCLUDED_stock_5finfo_2eproto_2epb_2eh
#define GOOGLE_PROTOBUF_INCLUDED_stock_5finfo_2eproto_2epb_2eh

#include <limits>
#include <string>
#include <type_traits>
#include <utility>

#include "google/protobuf/runtime_version.h"
#if PROTOBUF_VERSION != 5027000
#error "Protobuf C++ gencode is built with an incompatible version of"
#error "Protobuf C++ headers/runtime. See"
#error "https://protobuf.dev/support/cross-version-runtime-guarantee/#cpp"
#endif
#include "google/protobuf/io/coded_stream.h"
#include "google/protobuf/arena.h"
#include "google/protobuf/arenastring.h"
#include "google/protobuf/generated_message_tctable_decl.h"
#include "google/protobuf/generated_message_util.h"
#include "google/protobuf/metadata_lite.h"
#include "google/protobuf/generated_message_reflection.h"
#include "google/protobuf/message.h"
#include "google/protobuf/repeated_field.h"  // IWYU pragma: export
#include "google/protobuf/extension_set.h"  // IWYU pragma: export
#include "google/protobuf/unknown_field_set.h"
// @@protoc_insertion_point(includes)

// Must be included last.
#include "google/protobuf/port_def.inc"

#define PROTOBUF_INTERNAL_EXPORT_stock_5finfo_2eproto

namespace google {
namespace protobuf {
namespace internal {
class AnyMetadata;
}  // namespace internal
}  // namespace protobuf
}  // namespace google

// Internal implementation detail -- do not use these members.
struct TableStruct_stock_5finfo_2eproto {
  static const ::uint32_t offsets[];
};
extern const ::google::protobuf::internal::DescriptorTable
    descriptor_table_stock_5finfo_2eproto;
namespace SlabStock {
namespace CPyTa {
namespace protobuf {
class StockInfo;
struct StockInfoDefaultTypeInternal;
extern StockInfoDefaultTypeInternal _StockInfo_default_instance_;
class TaResult;
struct TaResultDefaultTypeInternal;
extern TaResultDefaultTypeInternal _TaResult_default_instance_;
}  // namespace protobuf
}  // namespace CPyTa
}  // namespace SlabStock
namespace google {
namespace protobuf {
}  // namespace protobuf
}  // namespace google

namespace SlabStock {
namespace CPyTa {
namespace protobuf {

// ===================================================================


// -------------------------------------------------------------------

class TaResult final : public ::google::protobuf::Message
/* @@protoc_insertion_point(class_definition:SlabStock.CPyTa.protobuf.TaResult) */ {
 public:
  inline TaResult() : TaResult(nullptr) {}
  ~TaResult() override;
  template <typename = void>
  explicit PROTOBUF_CONSTEXPR TaResult(
      ::google::protobuf::internal::ConstantInitialized);

  inline TaResult(const TaResult& from) : TaResult(nullptr, from) {}
  inline TaResult(TaResult&& from) noexcept
      : TaResult(nullptr, std::move(from)) {}
  inline TaResult& operator=(const TaResult& from) {
    CopyFrom(from);
    return *this;
  }
  inline TaResult& operator=(TaResult&& from) noexcept {
    if (this == &from) return *this;
    if (GetArena() == from.GetArena()
#ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetArena() != nullptr
#endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _internal_metadata_.unknown_fields<::google::protobuf::UnknownFieldSet>(::google::protobuf::UnknownFieldSet::default_instance);
  }
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields()
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _internal_metadata_.mutable_unknown_fields<::google::protobuf::UnknownFieldSet>();
  }

  static const ::google::protobuf::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::google::protobuf::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::google::protobuf::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const TaResult& default_instance() {
    return *internal_default_instance();
  }
  static inline const TaResult* internal_default_instance() {
    return reinterpret_cast<const TaResult*>(
        &_TaResult_default_instance_);
  }
  static constexpr int kIndexInFileMessages = 1;
  friend void swap(TaResult& a, TaResult& b) { a.Swap(&b); }
  inline void Swap(TaResult* other) {
    if (other == this) return;
#ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetArena() != nullptr && GetArena() == other->GetArena()) {
#else   // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetArena() == other->GetArena()) {
#endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::google::protobuf::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(TaResult* other) {
    if (other == this) return;
    ABSL_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  TaResult* New(::google::protobuf::Arena* arena = nullptr) const final {
    return ::google::protobuf::Message::DefaultConstruct<TaResult>(arena);
  }
  using ::google::protobuf::Message::CopyFrom;
  void CopyFrom(const TaResult& from);
  using ::google::protobuf::Message::MergeFrom;
  void MergeFrom(const TaResult& from) { TaResult::MergeImpl(*this, from); }

  private:
  static void MergeImpl(
      ::google::protobuf::MessageLite& to_msg,
      const ::google::protobuf::MessageLite& from_msg);

  public:
  bool IsInitialized() const {
    return true;
  }
  ABSL_ATTRIBUTE_REINITIALIZES void Clear() final;
  ::size_t ByteSizeLong() const final;
  ::uint8_t* _InternalSerialize(
      ::uint8_t* target,
      ::google::protobuf::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::google::protobuf::Arena* arena);
  void SharedDtor();
  void InternalSwap(TaResult* other);
 private:
  friend class ::google::protobuf::internal::AnyMetadata;
  static ::absl::string_view FullMessageName() { return "SlabStock.CPyTa.protobuf.TaResult"; }

 protected:
  explicit TaResult(::google::protobuf::Arena* arena);
  TaResult(::google::protobuf::Arena* arena, const TaResult& from);
  TaResult(::google::protobuf::Arena* arena, TaResult&& from) noexcept
      : TaResult(arena) {
    *this = ::std::move(from);
  }
  const ::google::protobuf::Message::ClassData* GetClassData() const final;

 public:
  ::google::protobuf::Metadata GetMetadata() const;
  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------
  enum : int {
    kPriceInfoFieldNumber = 1,
  };
  // string priceInfo = 1;
  void clear_priceinfo() ;
  const std::string& priceinfo() const;
  template <typename Arg_ = const std::string&, typename... Args_>
  void set_priceinfo(Arg_&& arg, Args_... args);
  std::string* mutable_priceinfo();
  PROTOBUF_NODISCARD std::string* release_priceinfo();
  void set_allocated_priceinfo(std::string* value);

  private:
  const std::string& _internal_priceinfo() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_priceinfo(
      const std::string& value);
  std::string* _internal_mutable_priceinfo();

  public:
  // @@protoc_insertion_point(class_scope:SlabStock.CPyTa.protobuf.TaResult)
 private:
  class _Internal;
  friend class ::google::protobuf::internal::TcParser;
  static const ::google::protobuf::internal::TcParseTable<
      0, 1, 0,
      51, 2>
      _table_;

  static constexpr const void* _raw_default_instance_ =
      &_TaResult_default_instance_;

  friend class ::google::protobuf::MessageLite;
  friend class ::google::protobuf::Arena;
  template <typename T>
  friend class ::google::protobuf::Arena::InternalHelper;
  using InternalArenaConstructable_ = void;
  using DestructorSkippable_ = void;
  struct Impl_ {
    inline explicit constexpr Impl_(
        ::google::protobuf::internal::ConstantInitialized) noexcept;
    inline explicit Impl_(::google::protobuf::internal::InternalVisibility visibility,
                          ::google::protobuf::Arena* arena);
    inline explicit Impl_(::google::protobuf::internal::InternalVisibility visibility,
                          ::google::protobuf::Arena* arena, const Impl_& from,
                          const TaResult& from_msg);
    ::google::protobuf::internal::ArenaStringPtr priceinfo_;
    mutable ::google::protobuf::internal::CachedSize _cached_size_;
    PROTOBUF_TSAN_DECLARE_MEMBER
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_stock_5finfo_2eproto;
};
// -------------------------------------------------------------------

class StockInfo final : public ::google::protobuf::Message
/* @@protoc_insertion_point(class_definition:SlabStock.CPyTa.protobuf.StockInfo) */ {
 public:
  inline StockInfo() : StockInfo(nullptr) {}
  ~StockInfo() override;
  template <typename = void>
  explicit PROTOBUF_CONSTEXPR StockInfo(
      ::google::protobuf::internal::ConstantInitialized);

  inline StockInfo(const StockInfo& from) : StockInfo(nullptr, from) {}
  inline StockInfo(StockInfo&& from) noexcept
      : StockInfo(nullptr, std::move(from)) {}
  inline StockInfo& operator=(const StockInfo& from) {
    CopyFrom(from);
    return *this;
  }
  inline StockInfo& operator=(StockInfo&& from) noexcept {
    if (this == &from) return *this;
    if (GetArena() == from.GetArena()
#ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetArena() != nullptr
#endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _internal_metadata_.unknown_fields<::google::protobuf::UnknownFieldSet>(::google::protobuf::UnknownFieldSet::default_instance);
  }
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields()
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _internal_metadata_.mutable_unknown_fields<::google::protobuf::UnknownFieldSet>();
  }

  static const ::google::protobuf::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::google::protobuf::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::google::protobuf::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const StockInfo& default_instance() {
    return *internal_default_instance();
  }
  static inline const StockInfo* internal_default_instance() {
    return reinterpret_cast<const StockInfo*>(
        &_StockInfo_default_instance_);
  }
  static constexpr int kIndexInFileMessages = 0;
  friend void swap(StockInfo& a, StockInfo& b) { a.Swap(&b); }
  inline void Swap(StockInfo* other) {
    if (other == this) return;
#ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetArena() != nullptr && GetArena() == other->GetArena()) {
#else   // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetArena() == other->GetArena()) {
#endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::google::protobuf::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(StockInfo* other) {
    if (other == this) return;
    ABSL_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  StockInfo* New(::google::protobuf::Arena* arena = nullptr) const final {
    return ::google::protobuf::Message::DefaultConstruct<StockInfo>(arena);
  }
  using ::google::protobuf::Message::CopyFrom;
  void CopyFrom(const StockInfo& from);
  using ::google::protobuf::Message::MergeFrom;
  void MergeFrom(const StockInfo& from) { StockInfo::MergeImpl(*this, from); }

  private:
  static void MergeImpl(
      ::google::protobuf::MessageLite& to_msg,
      const ::google::protobuf::MessageLite& from_msg);

  public:
  bool IsInitialized() const {
    return true;
  }
  ABSL_ATTRIBUTE_REINITIALIZES void Clear() final;
  ::size_t ByteSizeLong() const final;
  ::uint8_t* _InternalSerialize(
      ::uint8_t* target,
      ::google::protobuf::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::google::protobuf::Arena* arena);
  void SharedDtor();
  void InternalSwap(StockInfo* other);
 private:
  friend class ::google::protobuf::internal::AnyMetadata;
  static ::absl::string_view FullMessageName() { return "SlabStock.CPyTa.protobuf.StockInfo"; }

 protected:
  explicit StockInfo(::google::protobuf::Arena* arena);
  StockInfo(::google::protobuf::Arena* arena, const StockInfo& from);
  StockInfo(::google::protobuf::Arena* arena, StockInfo&& from) noexcept
      : StockInfo(arena) {
    *this = ::std::move(from);
  }
  const ::google::protobuf::Message::ClassData* GetClassData() const final;

 public:
  ::google::protobuf::Metadata GetMetadata() const;
  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------
  enum : int {
    kSymbolFieldNumber = 1,
    kNameFieldNumber = 2,
    kExchangeFieldNumber = 3,
  };
  // string symbol = 1;
  void clear_symbol() ;
  const std::string& symbol() const;
  template <typename Arg_ = const std::string&, typename... Args_>
  void set_symbol(Arg_&& arg, Args_... args);
  std::string* mutable_symbol();
  PROTOBUF_NODISCARD std::string* release_symbol();
  void set_allocated_symbol(std::string* value);

  private:
  const std::string& _internal_symbol() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_symbol(
      const std::string& value);
  std::string* _internal_mutable_symbol();

  public:
  // string name = 2;
  void clear_name() ;
  const std::string& name() const;
  template <typename Arg_ = const std::string&, typename... Args_>
  void set_name(Arg_&& arg, Args_... args);
  std::string* mutable_name();
  PROTOBUF_NODISCARD std::string* release_name();
  void set_allocated_name(std::string* value);

  private:
  const std::string& _internal_name() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_name(
      const std::string& value);
  std::string* _internal_mutable_name();

  public:
  // optional string exchange = 3;
  bool has_exchange() const;
  void clear_exchange() ;
  const std::string& exchange() const;
  template <typename Arg_ = const std::string&, typename... Args_>
  void set_exchange(Arg_&& arg, Args_... args);
  std::string* mutable_exchange();
  PROTOBUF_NODISCARD std::string* release_exchange();
  void set_allocated_exchange(std::string* value);

  private:
  const std::string& _internal_exchange() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_exchange(
      const std::string& value);
  std::string* _internal_mutable_exchange();

  public:
  // @@protoc_insertion_point(class_scope:SlabStock.CPyTa.protobuf.StockInfo)
 private:
  class _Internal;
  friend class ::google::protobuf::internal::TcParser;
  static const ::google::protobuf::internal::TcParseTable<
      2, 3, 0,
      61, 2>
      _table_;

  static constexpr const void* _raw_default_instance_ =
      &_StockInfo_default_instance_;

  friend class ::google::protobuf::MessageLite;
  friend class ::google::protobuf::Arena;
  template <typename T>
  friend class ::google::protobuf::Arena::InternalHelper;
  using InternalArenaConstructable_ = void;
  using DestructorSkippable_ = void;
  struct Impl_ {
    inline explicit constexpr Impl_(
        ::google::protobuf::internal::ConstantInitialized) noexcept;
    inline explicit Impl_(::google::protobuf::internal::InternalVisibility visibility,
                          ::google::protobuf::Arena* arena);
    inline explicit Impl_(::google::protobuf::internal::InternalVisibility visibility,
                          ::google::protobuf::Arena* arena, const Impl_& from,
                          const StockInfo& from_msg);
    ::google::protobuf::internal::HasBits<1> _has_bits_;
    mutable ::google::protobuf::internal::CachedSize _cached_size_;
    ::google::protobuf::internal::ArenaStringPtr symbol_;
    ::google::protobuf::internal::ArenaStringPtr name_;
    ::google::protobuf::internal::ArenaStringPtr exchange_;
    PROTOBUF_TSAN_DECLARE_MEMBER
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_stock_5finfo_2eproto;
};

// ===================================================================




// ===================================================================


#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// -------------------------------------------------------------------

// StockInfo

// string symbol = 1;
inline void StockInfo::clear_symbol() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.symbol_.ClearToEmpty();
}
inline const std::string& StockInfo::symbol() const
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_get:SlabStock.CPyTa.protobuf.StockInfo.symbol)
  return _internal_symbol();
}
template <typename Arg_, typename... Args_>
inline PROTOBUF_ALWAYS_INLINE void StockInfo::set_symbol(Arg_&& arg,
                                                     Args_... args) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.symbol_.Set(static_cast<Arg_&&>(arg), args..., GetArena());
  // @@protoc_insertion_point(field_set:SlabStock.CPyTa.protobuf.StockInfo.symbol)
}
inline std::string* StockInfo::mutable_symbol() ABSL_ATTRIBUTE_LIFETIME_BOUND {
  std::string* _s = _internal_mutable_symbol();
  // @@protoc_insertion_point(field_mutable:SlabStock.CPyTa.protobuf.StockInfo.symbol)
  return _s;
}
inline const std::string& StockInfo::_internal_symbol() const {
  ::google::protobuf::internal::TSanRead(&_impl_);
  return _impl_.symbol_.Get();
}
inline void StockInfo::_internal_set_symbol(const std::string& value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.symbol_.Set(value, GetArena());
}
inline std::string* StockInfo::_internal_mutable_symbol() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  return _impl_.symbol_.Mutable( GetArena());
}
inline std::string* StockInfo::release_symbol() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  // @@protoc_insertion_point(field_release:SlabStock.CPyTa.protobuf.StockInfo.symbol)
  return _impl_.symbol_.Release();
}
inline void StockInfo::set_allocated_symbol(std::string* value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.symbol_.SetAllocated(value, GetArena());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        if (_impl_.symbol_.IsDefault()) {
          _impl_.symbol_.Set("", GetArena());
        }
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:SlabStock.CPyTa.protobuf.StockInfo.symbol)
}

// string name = 2;
inline void StockInfo::clear_name() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.name_.ClearToEmpty();
}
inline const std::string& StockInfo::name() const
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_get:SlabStock.CPyTa.protobuf.StockInfo.name)
  return _internal_name();
}
template <typename Arg_, typename... Args_>
inline PROTOBUF_ALWAYS_INLINE void StockInfo::set_name(Arg_&& arg,
                                                     Args_... args) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.name_.Set(static_cast<Arg_&&>(arg), args..., GetArena());
  // @@protoc_insertion_point(field_set:SlabStock.CPyTa.protobuf.StockInfo.name)
}
inline std::string* StockInfo::mutable_name() ABSL_ATTRIBUTE_LIFETIME_BOUND {
  std::string* _s = _internal_mutable_name();
  // @@protoc_insertion_point(field_mutable:SlabStock.CPyTa.protobuf.StockInfo.name)
  return _s;
}
inline const std::string& StockInfo::_internal_name() const {
  ::google::protobuf::internal::TSanRead(&_impl_);
  return _impl_.name_.Get();
}
inline void StockInfo::_internal_set_name(const std::string& value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.name_.Set(value, GetArena());
}
inline std::string* StockInfo::_internal_mutable_name() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  return _impl_.name_.Mutable( GetArena());
}
inline std::string* StockInfo::release_name() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  // @@protoc_insertion_point(field_release:SlabStock.CPyTa.protobuf.StockInfo.name)
  return _impl_.name_.Release();
}
inline void StockInfo::set_allocated_name(std::string* value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.name_.SetAllocated(value, GetArena());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        if (_impl_.name_.IsDefault()) {
          _impl_.name_.Set("", GetArena());
        }
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:SlabStock.CPyTa.protobuf.StockInfo.name)
}

// optional string exchange = 3;
inline bool StockInfo::has_exchange() const {
  bool value = (_impl_._has_bits_[0] & 0x00000001u) != 0;
  return value;
}
inline void StockInfo::clear_exchange() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.exchange_.ClearToEmpty();
  _impl_._has_bits_[0] &= ~0x00000001u;
}
inline const std::string& StockInfo::exchange() const
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_get:SlabStock.CPyTa.protobuf.StockInfo.exchange)
  return _internal_exchange();
}
template <typename Arg_, typename... Args_>
inline PROTOBUF_ALWAYS_INLINE void StockInfo::set_exchange(Arg_&& arg,
                                                     Args_... args) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_._has_bits_[0] |= 0x00000001u;
  _impl_.exchange_.Set(static_cast<Arg_&&>(arg), args..., GetArena());
  // @@protoc_insertion_point(field_set:SlabStock.CPyTa.protobuf.StockInfo.exchange)
}
inline std::string* StockInfo::mutable_exchange() ABSL_ATTRIBUTE_LIFETIME_BOUND {
  std::string* _s = _internal_mutable_exchange();
  // @@protoc_insertion_point(field_mutable:SlabStock.CPyTa.protobuf.StockInfo.exchange)
  return _s;
}
inline const std::string& StockInfo::_internal_exchange() const {
  ::google::protobuf::internal::TSanRead(&_impl_);
  return _impl_.exchange_.Get();
}
inline void StockInfo::_internal_set_exchange(const std::string& value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_._has_bits_[0] |= 0x00000001u;
  _impl_.exchange_.Set(value, GetArena());
}
inline std::string* StockInfo::_internal_mutable_exchange() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_._has_bits_[0] |= 0x00000001u;
  return _impl_.exchange_.Mutable( GetArena());
}
inline std::string* StockInfo::release_exchange() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  // @@protoc_insertion_point(field_release:SlabStock.CPyTa.protobuf.StockInfo.exchange)
  if ((_impl_._has_bits_[0] & 0x00000001u) == 0) {
    return nullptr;
  }
  _impl_._has_bits_[0] &= ~0x00000001u;
  auto* released = _impl_.exchange_.Release();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  _impl_.exchange_.Set("", GetArena());
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  return released;
}
inline void StockInfo::set_allocated_exchange(std::string* value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  if (value != nullptr) {
    _impl_._has_bits_[0] |= 0x00000001u;
  } else {
    _impl_._has_bits_[0] &= ~0x00000001u;
  }
  _impl_.exchange_.SetAllocated(value, GetArena());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        if (_impl_.exchange_.IsDefault()) {
          _impl_.exchange_.Set("", GetArena());
        }
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:SlabStock.CPyTa.protobuf.StockInfo.exchange)
}

// -------------------------------------------------------------------

// TaResult

// string priceInfo = 1;
inline void TaResult::clear_priceinfo() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.priceinfo_.ClearToEmpty();
}
inline const std::string& TaResult::priceinfo() const
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_get:SlabStock.CPyTa.protobuf.TaResult.priceInfo)
  return _internal_priceinfo();
}
template <typename Arg_, typename... Args_>
inline PROTOBUF_ALWAYS_INLINE void TaResult::set_priceinfo(Arg_&& arg,
                                                     Args_... args) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.priceinfo_.Set(static_cast<Arg_&&>(arg), args..., GetArena());
  // @@protoc_insertion_point(field_set:SlabStock.CPyTa.protobuf.TaResult.priceInfo)
}
inline std::string* TaResult::mutable_priceinfo() ABSL_ATTRIBUTE_LIFETIME_BOUND {
  std::string* _s = _internal_mutable_priceinfo();
  // @@protoc_insertion_point(field_mutable:SlabStock.CPyTa.protobuf.TaResult.priceInfo)
  return _s;
}
inline const std::string& TaResult::_internal_priceinfo() const {
  ::google::protobuf::internal::TSanRead(&_impl_);
  return _impl_.priceinfo_.Get();
}
inline void TaResult::_internal_set_priceinfo(const std::string& value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.priceinfo_.Set(value, GetArena());
}
inline std::string* TaResult::_internal_mutable_priceinfo() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  return _impl_.priceinfo_.Mutable( GetArena());
}
inline std::string* TaResult::release_priceinfo() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  // @@protoc_insertion_point(field_release:SlabStock.CPyTa.protobuf.TaResult.priceInfo)
  return _impl_.priceinfo_.Release();
}
inline void TaResult::set_allocated_priceinfo(std::string* value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.priceinfo_.SetAllocated(value, GetArena());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        if (_impl_.priceinfo_.IsDefault()) {
          _impl_.priceinfo_.Set("", GetArena());
        }
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:SlabStock.CPyTa.protobuf.TaResult.priceInfo)
}

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)
}  // namespace protobuf
}  // namespace CPyTa
}  // namespace SlabStock


// @@protoc_insertion_point(global_scope)

#include "google/protobuf/port_undef.inc"

#endif  // GOOGLE_PROTOBUF_INCLUDED_stock_5finfo_2eproto_2epb_2eh

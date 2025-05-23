// Generated by the protocol buffer compiler.  DO NOT EDIT!
// NO CHECKED-IN PROTOBUF GENCODE
// source: stock_map.proto
// Protobuf C++ Version: 5.27.0

#ifndef GOOGLE_PROTOBUF_INCLUDED_stock_5fmap_2eproto_2epb_2eh
#define GOOGLE_PROTOBUF_INCLUDED_stock_5fmap_2eproto_2epb_2eh

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
#include "google/protobuf/map.h"  // IWYU pragma: export
#include "google/protobuf/map_entry.h"
#include "google/protobuf/map_field_inl.h"
#include "google/protobuf/unknown_field_set.h"
#include "stock_info.pb.h"
// @@protoc_insertion_point(includes)

// Must be included last.
#include "google/protobuf/port_def.inc"

#define PROTOBUF_INTERNAL_EXPORT_stock_5fmap_2eproto

namespace google {
namespace protobuf {
namespace internal {
class AnyMetadata;
}  // namespace internal
}  // namespace protobuf
}  // namespace google

// Internal implementation detail -- do not use these members.
struct TableStruct_stock_5fmap_2eproto {
  static const ::uint32_t offsets[];
};
extern const ::google::protobuf::internal::DescriptorTable
    descriptor_table_stock_5fmap_2eproto;
namespace SlabStock {
namespace CPyTa {
namespace protobuf {
class StockMap;
struct StockMapDefaultTypeInternal;
extern StockMapDefaultTypeInternal _StockMap_default_instance_;
class StockMap_MapEntry_DoNotUse;
struct StockMap_MapEntry_DoNotUseDefaultTypeInternal;
extern StockMap_MapEntry_DoNotUseDefaultTypeInternal _StockMap_MapEntry_DoNotUse_default_instance_;
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

class StockMap_MapEntry_DoNotUse final
    : public ::google::protobuf::internal::MapEntry<
          StockMap_MapEntry_DoNotUse, std::string, ::SlabStock::CPyTa::protobuf::StockInfo,
          ::google::protobuf::internal::WireFormatLite::TYPE_STRING,
          ::google::protobuf::internal::WireFormatLite::TYPE_MESSAGE> {
 public:
  using SuperType = ::google::protobuf::internal::MapEntry<
      StockMap_MapEntry_DoNotUse, std::string, ::SlabStock::CPyTa::protobuf::StockInfo,
      ::google::protobuf::internal::WireFormatLite::TYPE_STRING,
      ::google::protobuf::internal::WireFormatLite::TYPE_MESSAGE>;
  StockMap_MapEntry_DoNotUse();
  template <typename = void>
  explicit PROTOBUF_CONSTEXPR StockMap_MapEntry_DoNotUse(
      ::google::protobuf::internal::ConstantInitialized);
  explicit StockMap_MapEntry_DoNotUse(::google::protobuf::Arena* arena);
  static const StockMap_MapEntry_DoNotUse* internal_default_instance() {
    return reinterpret_cast<const StockMap_MapEntry_DoNotUse*>(
        &_StockMap_MapEntry_DoNotUse_default_instance_);
  }
const ::google::protobuf::Message::ClassData* GetClassData() const final;
  friend struct ::TableStruct_stock_5fmap_2eproto;
};
// -------------------------------------------------------------------

class StockMap final : public ::google::protobuf::Message
/* @@protoc_insertion_point(class_definition:SlabStock.CPyTa.protobuf.StockMap) */ {
 public:
  inline StockMap() : StockMap(nullptr) {}
  ~StockMap() override;
  template <typename = void>
  explicit PROTOBUF_CONSTEXPR StockMap(
      ::google::protobuf::internal::ConstantInitialized);

  inline StockMap(const StockMap& from) : StockMap(nullptr, from) {}
  inline StockMap(StockMap&& from) noexcept
      : StockMap(nullptr, std::move(from)) {}
  inline StockMap& operator=(const StockMap& from) {
    CopyFrom(from);
    return *this;
  }
  inline StockMap& operator=(StockMap&& from) noexcept {
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
  static const StockMap& default_instance() {
    return *internal_default_instance();
  }
  static inline const StockMap* internal_default_instance() {
    return reinterpret_cast<const StockMap*>(
        &_StockMap_default_instance_);
  }
  static constexpr int kIndexInFileMessages = 1;
  friend void swap(StockMap& a, StockMap& b) { a.Swap(&b); }
  inline void Swap(StockMap* other) {
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
  void UnsafeArenaSwap(StockMap* other) {
    if (other == this) return;
    ABSL_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  StockMap* New(::google::protobuf::Arena* arena = nullptr) const final {
    return ::google::protobuf::Message::DefaultConstruct<StockMap>(arena);
  }
  using ::google::protobuf::Message::CopyFrom;
  void CopyFrom(const StockMap& from);
  using ::google::protobuf::Message::MergeFrom;
  void MergeFrom(const StockMap& from) { StockMap::MergeImpl(*this, from); }

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
  void InternalSwap(StockMap* other);
 private:
  friend class ::google::protobuf::internal::AnyMetadata;
  static ::absl::string_view FullMessageName() { return "SlabStock.CPyTa.protobuf.StockMap"; }

 protected:
  explicit StockMap(::google::protobuf::Arena* arena);
  StockMap(::google::protobuf::Arena* arena, const StockMap& from);
  StockMap(::google::protobuf::Arena* arena, StockMap&& from) noexcept
      : StockMap(arena) {
    *this = ::std::move(from);
  }
  const ::google::protobuf::Message::ClassData* GetClassData() const final;

 public:
  ::google::protobuf::Metadata GetMetadata() const;
  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------
  enum : int {
    kMapFieldNumber = 1,
  };
  // map<string, .SlabStock.CPyTa.protobuf.StockInfo> map = 1;
  int map_size() const;
  private:
  int _internal_map_size() const;

  public:
  void clear_map() ;
  const ::google::protobuf::Map<std::string, ::SlabStock::CPyTa::protobuf::StockInfo>& map() const;
  ::google::protobuf::Map<std::string, ::SlabStock::CPyTa::protobuf::StockInfo>* mutable_map();

  private:
  const ::google::protobuf::Map<std::string, ::SlabStock::CPyTa::protobuf::StockInfo>& _internal_map() const;
  ::google::protobuf::Map<std::string, ::SlabStock::CPyTa::protobuf::StockInfo>* _internal_mutable_map();

  public:
  // @@protoc_insertion_point(class_scope:SlabStock.CPyTa.protobuf.StockMap)
 private:
  class _Internal;
  friend class ::google::protobuf::internal::TcParser;
  static const ::google::protobuf::internal::TcParseTable<
      0, 1, 2,
      45, 2>
      _table_;

  static constexpr const void* _raw_default_instance_ =
      &_StockMap_default_instance_;

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
                          const StockMap& from_msg);
    ::google::protobuf::internal::MapField<StockMap_MapEntry_DoNotUse, std::string, ::SlabStock::CPyTa::protobuf::StockInfo,
                      ::google::protobuf::internal::WireFormatLite::TYPE_STRING,
                      ::google::protobuf::internal::WireFormatLite::TYPE_MESSAGE>
        map_;
    mutable ::google::protobuf::internal::CachedSize _cached_size_;
    PROTOBUF_TSAN_DECLARE_MEMBER
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_stock_5fmap_2eproto;
};

// ===================================================================




// ===================================================================


#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// -------------------------------------------------------------------

// -------------------------------------------------------------------

// StockMap

// map<string, .SlabStock.CPyTa.protobuf.StockInfo> map = 1;
inline int StockMap::_internal_map_size() const {
  return _internal_map().size();
}
inline int StockMap::map_size() const {
  return _internal_map_size();
}
inline const ::google::protobuf::Map<std::string, ::SlabStock::CPyTa::protobuf::StockInfo>& StockMap::_internal_map() const {
  ::google::protobuf::internal::TSanRead(&_impl_);
  return _impl_.map_.GetMap();
}
inline const ::google::protobuf::Map<std::string, ::SlabStock::CPyTa::protobuf::StockInfo>& StockMap::map() const ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_map:SlabStock.CPyTa.protobuf.StockMap.map)
  return _internal_map();
}
inline ::google::protobuf::Map<std::string, ::SlabStock::CPyTa::protobuf::StockInfo>* StockMap::_internal_mutable_map() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  return _impl_.map_.MutableMap();
}
inline ::google::protobuf::Map<std::string, ::SlabStock::CPyTa::protobuf::StockInfo>* StockMap::mutable_map() ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_mutable_map:SlabStock.CPyTa.protobuf.StockMap.map)
  return _internal_mutable_map();
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

#endif  // GOOGLE_PROTOBUF_INCLUDED_stock_5fmap_2eproto_2epb_2eh

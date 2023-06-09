// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: packet_head.proto

#ifndef PROTOBUF_packet_5fhead_2eproto__INCLUDED
#define PROTOBUF_packet_5fhead_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3004000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3004000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
namespace proto {
class DebugNotify;
class DebugNotifyDefaultTypeInternal;
extern DebugNotifyDefaultTypeInternal _DebugNotify_default_instance_;
class PacketHead;
class PacketHeadDefaultTypeInternal;
extern PacketHeadDefaultTypeInternal _PacketHead_default_instance_;
}  // namespace proto

namespace proto {

namespace protobuf_packet_5fhead_2eproto {
// Internal implementation detail -- do not call these.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[];
  static const ::google::protobuf::uint32 offsets[];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static void InitDefaultsImpl();
};
void AddDescriptors();
void InitDefaults();
}  // namespace protobuf_packet_5fhead_2eproto

enum DebugNotify_Enum {
  DebugNotify_Enum_ZERO = 0,
  DebugNotify_Enum_CMD_ID = 101,
  DebugNotify_Enum_TARGET_SERVICE = 101,
  DebugNotify_Enum_ENET_CHANNEL_ID = 2,
  DebugNotify_Enum_ENET_IS_RELIABLE = 1,
  DebugNotify_Enum_DebugNotify_Enum_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  DebugNotify_Enum_DebugNotify_Enum_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
bool DebugNotify_Enum_IsValid(int value);
const DebugNotify_Enum DebugNotify_Enum_Enum_MIN = DebugNotify_Enum_ZERO;
const DebugNotify_Enum DebugNotify_Enum_Enum_MAX = DebugNotify_Enum_CMD_ID;
const int DebugNotify_Enum_Enum_ARRAYSIZE = DebugNotify_Enum_Enum_MAX + 1;

const ::google::protobuf::EnumDescriptor* DebugNotify_Enum_descriptor();
inline const ::std::string& DebugNotify_Enum_Name(DebugNotify_Enum value) {
  return ::google::protobuf::internal::NameOfEnum(
    DebugNotify_Enum_descriptor(), value);
}
inline bool DebugNotify_Enum_Parse(
    const ::std::string& name, DebugNotify_Enum* value) {
  return ::google::protobuf::internal::ParseNamedEnum<DebugNotify_Enum>(
    DebugNotify_Enum_descriptor(), name, value);
}
enum DebugNotify_Retcode {
  DebugNotify_Retcode_SUCC = 0,
  DebugNotify_Retcode_FAIL = 1,
  DebugNotify_Retcode_DebugNotify_Retcode_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  DebugNotify_Retcode_DebugNotify_Retcode_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
bool DebugNotify_Retcode_IsValid(int value);
const DebugNotify_Retcode DebugNotify_Retcode_Retcode_MIN = DebugNotify_Retcode_SUCC;
const DebugNotify_Retcode DebugNotify_Retcode_Retcode_MAX = DebugNotify_Retcode_FAIL;
const int DebugNotify_Retcode_Retcode_ARRAYSIZE = DebugNotify_Retcode_Retcode_MAX + 1;

const ::google::protobuf::EnumDescriptor* DebugNotify_Retcode_descriptor();
inline const ::std::string& DebugNotify_Retcode_Name(DebugNotify_Retcode value) {
  return ::google::protobuf::internal::NameOfEnum(
    DebugNotify_Retcode_descriptor(), value);
}
inline bool DebugNotify_Retcode_Parse(
    const ::std::string& name, DebugNotify_Retcode* value) {
  return ::google::protobuf::internal::ParseNamedEnum<DebugNotify_Retcode>(
    DebugNotify_Retcode_descriptor(), name, value);
}
// ===================================================================

class PacketHead : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:proto.PacketHead) */ {
 public:
  PacketHead();
  virtual ~PacketHead();

  PacketHead(const PacketHead& from);

  inline PacketHead& operator=(const PacketHead& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  PacketHead(PacketHead&& from) noexcept
    : PacketHead() {
    *this = ::std::move(from);
  }

  inline PacketHead& operator=(PacketHead&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const PacketHead& default_instance();

  static inline const PacketHead* internal_default_instance() {
    return reinterpret_cast<const PacketHead*>(
               &_PacketHead_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    0;

  void Swap(PacketHead* other);
  friend void swap(PacketHead& a, PacketHead& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline PacketHead* New() const PROTOBUF_FINAL { return New(NULL); }

  PacketHead* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const PacketHead& from);
  void MergeFrom(const PacketHead& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(PacketHead* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // uint32 packet_id = 1;
  void clear_packet_id();
  static const int kPacketIdFieldNumber = 1;
  ::google::protobuf::uint32 packet_id() const;
  void set_packet_id(::google::protobuf::uint32 value);

  // uint32 user_id = 2;
  void clear_user_id();
  static const int kUserIdFieldNumber = 2;
  ::google::protobuf::uint32 user_id() const;
  void set_user_id(::google::protobuf::uint32 value);

  // uint32 user_ip = 3;
  void clear_user_ip();
  static const int kUserIpFieldNumber = 3;
  ::google::protobuf::uint32 user_ip() const;
  void set_user_ip(::google::protobuf::uint32 value);

  // uint32 user_session_id = 4;
  void clear_user_session_id();
  static const int kUserSessionIdFieldNumber = 4;
  ::google::protobuf::uint32 user_session_id() const;
  void set_user_session_id(::google::protobuf::uint32 value);

  // uint32 dispatch_ip = 5;
  void clear_dispatch_ip();
  static const int kDispatchIpFieldNumber = 5;
  ::google::protobuf::uint32 dispatch_ip() const;
  void set_dispatch_ip(::google::protobuf::uint32 value);

  // uint32 gameserver_ip = 6;
  void clear_gameserver_ip();
  static const int kGameserverIpFieldNumber = 6;
  ::google::protobuf::uint32 gameserver_ip() const;
  void set_gameserver_ip(::google::protobuf::uint32 value);

  // uint32 rpc_id = 7;
  void clear_rpc_id();
  static const int kRpcIdFieldNumber = 7;
  ::google::protobuf::uint32 rpc_id() const;
  void set_rpc_id(::google::protobuf::uint32 value);

  // uint32 enet_channel_id = 8;
  void clear_enet_channel_id();
  static const int kEnetChannelIdFieldNumber = 8;
  ::google::protobuf::uint32 enet_channel_id() const;
  void set_enet_channel_id(::google::protobuf::uint32 value);

  // uint32 enet_is_reliable = 9;
  void clear_enet_is_reliable();
  static const int kEnetIsReliableFieldNumber = 9;
  ::google::protobuf::uint32 enet_is_reliable() const;
  void set_enet_is_reliable(::google::protobuf::uint32 value);

  // uint32 nodeserver_ip = 10;
  void clear_nodeserver_ip();
  static const int kNodeserverIpFieldNumber = 10;
  ::google::protobuf::uint32 nodeserver_ip() const;
  void set_nodeserver_ip(::google::protobuf::uint32 value);

  // uint32 recv_time = 11;
  void clear_recv_time();
  static const int kRecvTimeFieldNumber = 11;
  ::google::protobuf::uint32 recv_time() const;
  void set_recv_time(::google::protobuf::uint32 value);

  // uint32 rpc_begin_time_ms = 12;
  void clear_rpc_begin_time_ms();
  static const int kRpcBeginTimeMsFieldNumber = 12;
  ::google::protobuf::uint32 rpc_begin_time_ms() const;
  void set_rpc_begin_time_ms(::google::protobuf::uint32 value);

  // uint32 target_service = 13;
  void clear_target_service();
  static const int kTargetServiceFieldNumber = 13;
  ::google::protobuf::uint32 target_service() const;
  void set_target_service(::google::protobuf::uint32 value);

  // uint32 dbgate_ip = 14;
  void clear_dbgate_ip();
  static const int kDbgateIpFieldNumber = 14;
  ::google::protobuf::uint32 dbgate_ip() const;
  void set_dbgate_ip(::google::protobuf::uint32 value);

  // uint32 custom_1 = 15;
  void clear_custom_1();
  static const int kCustom1FieldNumber = 15;
  ::google::protobuf::uint32 custom_1() const;
  void set_custom_1(::google::protobuf::uint32 value);

  // uint32 custom_2 = 16;
  void clear_custom_2();
  static const int kCustom2FieldNumber = 16;
  ::google::protobuf::uint32 custom_2() const;
  void set_custom_2(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:proto.PacketHead)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::uint32 packet_id_;
  ::google::protobuf::uint32 user_id_;
  ::google::protobuf::uint32 user_ip_;
  ::google::protobuf::uint32 user_session_id_;
  ::google::protobuf::uint32 dispatch_ip_;
  ::google::protobuf::uint32 gameserver_ip_;
  ::google::protobuf::uint32 rpc_id_;
  ::google::protobuf::uint32 enet_channel_id_;
  ::google::protobuf::uint32 enet_is_reliable_;
  ::google::protobuf::uint32 nodeserver_ip_;
  ::google::protobuf::uint32 recv_time_;
  ::google::protobuf::uint32 rpc_begin_time_ms_;
  ::google::protobuf::uint32 target_service_;
  ::google::protobuf::uint32 dbgate_ip_;
  ::google::protobuf::uint32 custom_1_;
  ::google::protobuf::uint32 custom_2_;
  mutable int _cached_size_;
  friend struct protobuf_packet_5fhead_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class DebugNotify : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:proto.DebugNotify) */ {
 public:
  DebugNotify();
  virtual ~DebugNotify();

  DebugNotify(const DebugNotify& from);

  inline DebugNotify& operator=(const DebugNotify& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  DebugNotify(DebugNotify&& from) noexcept
    : DebugNotify() {
    *this = ::std::move(from);
  }

  inline DebugNotify& operator=(DebugNotify&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const DebugNotify& default_instance();

  static inline const DebugNotify* internal_default_instance() {
    return reinterpret_cast<const DebugNotify*>(
               &_DebugNotify_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    1;

  void Swap(DebugNotify* other);
  friend void swap(DebugNotify& a, DebugNotify& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline DebugNotify* New() const PROTOBUF_FINAL { return New(NULL); }

  DebugNotify* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const DebugNotify& from);
  void MergeFrom(const DebugNotify& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(DebugNotify* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  typedef DebugNotify_Enum Enum;
  static const Enum ZERO =
    DebugNotify_Enum_ZERO;
  static const Enum CMD_ID =
    DebugNotify_Enum_CMD_ID;
  static const Enum TARGET_SERVICE =
    DebugNotify_Enum_TARGET_SERVICE;
  static const Enum ENET_CHANNEL_ID =
    DebugNotify_Enum_ENET_CHANNEL_ID;
  static const Enum ENET_IS_RELIABLE =
    DebugNotify_Enum_ENET_IS_RELIABLE;
  static inline bool Enum_IsValid(int value) {
    return DebugNotify_Enum_IsValid(value);
  }
  static const Enum Enum_MIN =
    DebugNotify_Enum_Enum_MIN;
  static const Enum Enum_MAX =
    DebugNotify_Enum_Enum_MAX;
  static const int Enum_ARRAYSIZE =
    DebugNotify_Enum_Enum_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  Enum_descriptor() {
    return DebugNotify_Enum_descriptor();
  }
  static inline const ::std::string& Enum_Name(Enum value) {
    return DebugNotify_Enum_Name(value);
  }
  static inline bool Enum_Parse(const ::std::string& name,
      Enum* value) {
    return DebugNotify_Enum_Parse(name, value);
  }

  typedef DebugNotify_Retcode Retcode;
  static const Retcode SUCC =
    DebugNotify_Retcode_SUCC;
  static const Retcode FAIL =
    DebugNotify_Retcode_FAIL;
  static inline bool Retcode_IsValid(int value) {
    return DebugNotify_Retcode_IsValid(value);
  }
  static const Retcode Retcode_MIN =
    DebugNotify_Retcode_Retcode_MIN;
  static const Retcode Retcode_MAX =
    DebugNotify_Retcode_Retcode_MAX;
  static const int Retcode_ARRAYSIZE =
    DebugNotify_Retcode_Retcode_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  Retcode_descriptor() {
    return DebugNotify_Retcode_descriptor();
  }
  static inline const ::std::string& Retcode_Name(Retcode value) {
    return DebugNotify_Retcode_Name(value);
  }
  static inline bool Retcode_Parse(const ::std::string& name,
      Retcode* value) {
    return DebugNotify_Retcode_Parse(name, value);
  }

  // accessors -------------------------------------------------------

  // string name = 2;
  void clear_name();
  static const int kNameFieldNumber = 2;
  const ::std::string& name() const;
  void set_name(const ::std::string& value);
  #if LANG_CXX11
  void set_name(::std::string&& value);
  #endif
  void set_name(const char* value);
  void set_name(const char* value, size_t size);
  ::std::string* mutable_name();
  ::std::string* release_name();
  void set_allocated_name(::std::string* name);

  // uint32 id = 1;
  void clear_id();
  static const int kIdFieldNumber = 1;
  ::google::protobuf::uint32 id() const;
  void set_id(::google::protobuf::uint32 value);

  // .proto.DebugNotify.Retcode retcode = 3;
  void clear_retcode();
  static const int kRetcodeFieldNumber = 3;
  ::proto::DebugNotify_Retcode retcode() const;
  void set_retcode(::proto::DebugNotify_Retcode value);

  // @@protoc_insertion_point(class_scope:proto.DebugNotify)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr name_;
  ::google::protobuf::uint32 id_;
  int retcode_;
  mutable int _cached_size_;
  friend struct protobuf_packet_5fhead_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// PacketHead

// uint32 packet_id = 1;
inline void PacketHead::clear_packet_id() {
  packet_id_ = 0u;
}
inline ::google::protobuf::uint32 PacketHead::packet_id() const {
  // @@protoc_insertion_point(field_get:proto.PacketHead.packet_id)
  return packet_id_;
}
inline void PacketHead::set_packet_id(::google::protobuf::uint32 value) {
  
  packet_id_ = value;
  // @@protoc_insertion_point(field_set:proto.PacketHead.packet_id)
}

// uint32 user_id = 2;
inline void PacketHead::clear_user_id() {
  user_id_ = 0u;
}
inline ::google::protobuf::uint32 PacketHead::user_id() const {
  // @@protoc_insertion_point(field_get:proto.PacketHead.user_id)
  return user_id_;
}
inline void PacketHead::set_user_id(::google::protobuf::uint32 value) {
  
  user_id_ = value;
  // @@protoc_insertion_point(field_set:proto.PacketHead.user_id)
}

// uint32 user_ip = 3;
inline void PacketHead::clear_user_ip() {
  user_ip_ = 0u;
}
inline ::google::protobuf::uint32 PacketHead::user_ip() const {
  // @@protoc_insertion_point(field_get:proto.PacketHead.user_ip)
  return user_ip_;
}
inline void PacketHead::set_user_ip(::google::protobuf::uint32 value) {
  
  user_ip_ = value;
  // @@protoc_insertion_point(field_set:proto.PacketHead.user_ip)
}

// uint32 user_session_id = 4;
inline void PacketHead::clear_user_session_id() {
  user_session_id_ = 0u;
}
inline ::google::protobuf::uint32 PacketHead::user_session_id() const {
  // @@protoc_insertion_point(field_get:proto.PacketHead.user_session_id)
  return user_session_id_;
}
inline void PacketHead::set_user_session_id(::google::protobuf::uint32 value) {
  
  user_session_id_ = value;
  // @@protoc_insertion_point(field_set:proto.PacketHead.user_session_id)
}

// uint32 dispatch_ip = 5;
inline void PacketHead::clear_dispatch_ip() {
  dispatch_ip_ = 0u;
}
inline ::google::protobuf::uint32 PacketHead::dispatch_ip() const {
  // @@protoc_insertion_point(field_get:proto.PacketHead.dispatch_ip)
  return dispatch_ip_;
}
inline void PacketHead::set_dispatch_ip(::google::protobuf::uint32 value) {
  
  dispatch_ip_ = value;
  // @@protoc_insertion_point(field_set:proto.PacketHead.dispatch_ip)
}

// uint32 gameserver_ip = 6;
inline void PacketHead::clear_gameserver_ip() {
  gameserver_ip_ = 0u;
}
inline ::google::protobuf::uint32 PacketHead::gameserver_ip() const {
  // @@protoc_insertion_point(field_get:proto.PacketHead.gameserver_ip)
  return gameserver_ip_;
}
inline void PacketHead::set_gameserver_ip(::google::protobuf::uint32 value) {
  
  gameserver_ip_ = value;
  // @@protoc_insertion_point(field_set:proto.PacketHead.gameserver_ip)
}

// uint32 rpc_id = 7;
inline void PacketHead::clear_rpc_id() {
  rpc_id_ = 0u;
}
inline ::google::protobuf::uint32 PacketHead::rpc_id() const {
  // @@protoc_insertion_point(field_get:proto.PacketHead.rpc_id)
  return rpc_id_;
}
inline void PacketHead::set_rpc_id(::google::protobuf::uint32 value) {
  
  rpc_id_ = value;
  // @@protoc_insertion_point(field_set:proto.PacketHead.rpc_id)
}

// uint32 enet_channel_id = 8;
inline void PacketHead::clear_enet_channel_id() {
  enet_channel_id_ = 0u;
}
inline ::google::protobuf::uint32 PacketHead::enet_channel_id() const {
  // @@protoc_insertion_point(field_get:proto.PacketHead.enet_channel_id)
  return enet_channel_id_;
}
inline void PacketHead::set_enet_channel_id(::google::protobuf::uint32 value) {
  
  enet_channel_id_ = value;
  // @@protoc_insertion_point(field_set:proto.PacketHead.enet_channel_id)
}

// uint32 enet_is_reliable = 9;
inline void PacketHead::clear_enet_is_reliable() {
  enet_is_reliable_ = 0u;
}
inline ::google::protobuf::uint32 PacketHead::enet_is_reliable() const {
  // @@protoc_insertion_point(field_get:proto.PacketHead.enet_is_reliable)
  return enet_is_reliable_;
}
inline void PacketHead::set_enet_is_reliable(::google::protobuf::uint32 value) {
  
  enet_is_reliable_ = value;
  // @@protoc_insertion_point(field_set:proto.PacketHead.enet_is_reliable)
}

// uint32 nodeserver_ip = 10;
inline void PacketHead::clear_nodeserver_ip() {
  nodeserver_ip_ = 0u;
}
inline ::google::protobuf::uint32 PacketHead::nodeserver_ip() const {
  // @@protoc_insertion_point(field_get:proto.PacketHead.nodeserver_ip)
  return nodeserver_ip_;
}
inline void PacketHead::set_nodeserver_ip(::google::protobuf::uint32 value) {
  
  nodeserver_ip_ = value;
  // @@protoc_insertion_point(field_set:proto.PacketHead.nodeserver_ip)
}

// uint32 recv_time = 11;
inline void PacketHead::clear_recv_time() {
  recv_time_ = 0u;
}
inline ::google::protobuf::uint32 PacketHead::recv_time() const {
  // @@protoc_insertion_point(field_get:proto.PacketHead.recv_time)
  return recv_time_;
}
inline void PacketHead::set_recv_time(::google::protobuf::uint32 value) {
  
  recv_time_ = value;
  // @@protoc_insertion_point(field_set:proto.PacketHead.recv_time)
}

// uint32 rpc_begin_time_ms = 12;
inline void PacketHead::clear_rpc_begin_time_ms() {
  rpc_begin_time_ms_ = 0u;
}
inline ::google::protobuf::uint32 PacketHead::rpc_begin_time_ms() const {
  // @@protoc_insertion_point(field_get:proto.PacketHead.rpc_begin_time_ms)
  return rpc_begin_time_ms_;
}
inline void PacketHead::set_rpc_begin_time_ms(::google::protobuf::uint32 value) {
  
  rpc_begin_time_ms_ = value;
  // @@protoc_insertion_point(field_set:proto.PacketHead.rpc_begin_time_ms)
}

// uint32 target_service = 13;
inline void PacketHead::clear_target_service() {
  target_service_ = 0u;
}
inline ::google::protobuf::uint32 PacketHead::target_service() const {
  // @@protoc_insertion_point(field_get:proto.PacketHead.target_service)
  return target_service_;
}
inline void PacketHead::set_target_service(::google::protobuf::uint32 value) {
  
  target_service_ = value;
  // @@protoc_insertion_point(field_set:proto.PacketHead.target_service)
}

// uint32 dbgate_ip = 14;
inline void PacketHead::clear_dbgate_ip() {
  dbgate_ip_ = 0u;
}
inline ::google::protobuf::uint32 PacketHead::dbgate_ip() const {
  // @@protoc_insertion_point(field_get:proto.PacketHead.dbgate_ip)
  return dbgate_ip_;
}
inline void PacketHead::set_dbgate_ip(::google::protobuf::uint32 value) {
  
  dbgate_ip_ = value;
  // @@protoc_insertion_point(field_set:proto.PacketHead.dbgate_ip)
}

// uint32 custom_1 = 15;
inline void PacketHead::clear_custom_1() {
  custom_1_ = 0u;
}
inline ::google::protobuf::uint32 PacketHead::custom_1() const {
  // @@protoc_insertion_point(field_get:proto.PacketHead.custom_1)
  return custom_1_;
}
inline void PacketHead::set_custom_1(::google::protobuf::uint32 value) {
  
  custom_1_ = value;
  // @@protoc_insertion_point(field_set:proto.PacketHead.custom_1)
}

// uint32 custom_2 = 16;
inline void PacketHead::clear_custom_2() {
  custom_2_ = 0u;
}
inline ::google::protobuf::uint32 PacketHead::custom_2() const {
  // @@protoc_insertion_point(field_get:proto.PacketHead.custom_2)
  return custom_2_;
}
inline void PacketHead::set_custom_2(::google::protobuf::uint32 value) {
  
  custom_2_ = value;
  // @@protoc_insertion_point(field_set:proto.PacketHead.custom_2)
}

// -------------------------------------------------------------------

// DebugNotify

// uint32 id = 1;
inline void DebugNotify::clear_id() {
  id_ = 0u;
}
inline ::google::protobuf::uint32 DebugNotify::id() const {
  // @@protoc_insertion_point(field_get:proto.DebugNotify.id)
  return id_;
}
inline void DebugNotify::set_id(::google::protobuf::uint32 value) {
  
  id_ = value;
  // @@protoc_insertion_point(field_set:proto.DebugNotify.id)
}

// string name = 2;
inline void DebugNotify::clear_name() {
  name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& DebugNotify::name() const {
  // @@protoc_insertion_point(field_get:proto.DebugNotify.name)
  return name_.GetNoArena();
}
inline void DebugNotify::set_name(const ::std::string& value) {
  
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:proto.DebugNotify.name)
}
#if LANG_CXX11
inline void DebugNotify::set_name(::std::string&& value) {
  
  name_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:proto.DebugNotify.name)
}
#endif
inline void DebugNotify::set_name(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:proto.DebugNotify.name)
}
inline void DebugNotify::set_name(const char* value, size_t size) {
  
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:proto.DebugNotify.name)
}
inline ::std::string* DebugNotify::mutable_name() {
  
  // @@protoc_insertion_point(field_mutable:proto.DebugNotify.name)
  return name_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* DebugNotify::release_name() {
  // @@protoc_insertion_point(field_release:proto.DebugNotify.name)
  
  return name_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void DebugNotify::set_allocated_name(::std::string* name) {
  if (name != NULL) {
    
  } else {
    
  }
  name_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), name);
  // @@protoc_insertion_point(field_set_allocated:proto.DebugNotify.name)
}

// .proto.DebugNotify.Retcode retcode = 3;
inline void DebugNotify::clear_retcode() {
  retcode_ = 0;
}
inline ::proto::DebugNotify_Retcode DebugNotify::retcode() const {
  // @@protoc_insertion_point(field_get:proto.DebugNotify.retcode)
  return static_cast< ::proto::DebugNotify_Retcode >(retcode_);
}
inline void DebugNotify::set_retcode(::proto::DebugNotify_Retcode value) {
  
  retcode_ = value;
  // @@protoc_insertion_point(field_set:proto.DebugNotify.retcode)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)


}  // namespace proto

namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::proto::DebugNotify_Enum> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::proto::DebugNotify_Enum>() {
  return ::proto::DebugNotify_Enum_descriptor();
}
template <> struct is_proto_enum< ::proto::DebugNotify_Retcode> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::proto::DebugNotify_Retcode>() {
  return ::proto::DebugNotify_Retcode_descriptor();
}

}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_packet_5fhead_2eproto__INCLUDED

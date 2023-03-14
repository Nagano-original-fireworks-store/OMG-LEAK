// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: cmd/cmd_npc.proto

#ifndef PROTOBUF_cmd_2fcmd_5fnpc_2eproto__INCLUDED
#define PROTOBUF_cmd_2fcmd_5fnpc_2eproto__INCLUDED

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
#include "define.pb.h"
// @@protoc_insertion_point(includes)
namespace proto {
class GetSceneNpcPositionReq;
class GetSceneNpcPositionReqDefaultTypeInternal;
extern GetSceneNpcPositionReqDefaultTypeInternal _GetSceneNpcPositionReq_default_instance_;
class GetSceneNpcPositionRsp;
class GetSceneNpcPositionRspDefaultTypeInternal;
extern GetSceneNpcPositionRspDefaultTypeInternal _GetSceneNpcPositionRsp_default_instance_;
class NpcTalkReq;
class NpcTalkReqDefaultTypeInternal;
extern NpcTalkReqDefaultTypeInternal _NpcTalkReq_default_instance_;
class NpcTalkRsp;
class NpcTalkRspDefaultTypeInternal;
extern NpcTalkRspDefaultTypeInternal _NpcTalkRsp_default_instance_;
}  // namespace proto

namespace proto {

namespace protobuf_cmd_2fcmd_5fnpc_2eproto {
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
}  // namespace protobuf_cmd_2fcmd_5fnpc_2eproto

enum NpcTalkReq_CmdId {
  NpcTalkReq_CmdId_NONE = 0,
  NpcTalkReq_CmdId_CMD_ID = 501,
  NpcTalkReq_CmdId_ENET_CHANNEL_ID = 0,
  NpcTalkReq_CmdId_ENET_IS_RELIABLE = 1,
  NpcTalkReq_CmdId_IS_ALLOW_CLIENT = 1,
  NpcTalkReq_CmdId_NpcTalkReq_CmdId_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  NpcTalkReq_CmdId_NpcTalkReq_CmdId_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
bool NpcTalkReq_CmdId_IsValid(int value);
const NpcTalkReq_CmdId NpcTalkReq_CmdId_CmdId_MIN = NpcTalkReq_CmdId_NONE;
const NpcTalkReq_CmdId NpcTalkReq_CmdId_CmdId_MAX = NpcTalkReq_CmdId_CMD_ID;
const int NpcTalkReq_CmdId_CmdId_ARRAYSIZE = NpcTalkReq_CmdId_CmdId_MAX + 1;

const ::google::protobuf::EnumDescriptor* NpcTalkReq_CmdId_descriptor();
inline const ::std::string& NpcTalkReq_CmdId_Name(NpcTalkReq_CmdId value) {
  return ::google::protobuf::internal::NameOfEnum(
    NpcTalkReq_CmdId_descriptor(), value);
}
inline bool NpcTalkReq_CmdId_Parse(
    const ::std::string& name, NpcTalkReq_CmdId* value) {
  return ::google::protobuf::internal::ParseNamedEnum<NpcTalkReq_CmdId>(
    NpcTalkReq_CmdId_descriptor(), name, value);
}
enum NpcTalkRsp_CmdId {
  NpcTalkRsp_CmdId_NONE = 0,
  NpcTalkRsp_CmdId_CMD_ID = 502,
  NpcTalkRsp_CmdId_ENET_CHANNEL_ID = 0,
  NpcTalkRsp_CmdId_ENET_IS_RELIABLE = 1,
  NpcTalkRsp_CmdId_NpcTalkRsp_CmdId_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  NpcTalkRsp_CmdId_NpcTalkRsp_CmdId_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
bool NpcTalkRsp_CmdId_IsValid(int value);
const NpcTalkRsp_CmdId NpcTalkRsp_CmdId_CmdId_MIN = NpcTalkRsp_CmdId_NONE;
const NpcTalkRsp_CmdId NpcTalkRsp_CmdId_CmdId_MAX = NpcTalkRsp_CmdId_CMD_ID;
const int NpcTalkRsp_CmdId_CmdId_ARRAYSIZE = NpcTalkRsp_CmdId_CmdId_MAX + 1;

const ::google::protobuf::EnumDescriptor* NpcTalkRsp_CmdId_descriptor();
inline const ::std::string& NpcTalkRsp_CmdId_Name(NpcTalkRsp_CmdId value) {
  return ::google::protobuf::internal::NameOfEnum(
    NpcTalkRsp_CmdId_descriptor(), value);
}
inline bool NpcTalkRsp_CmdId_Parse(
    const ::std::string& name, NpcTalkRsp_CmdId* value) {
  return ::google::protobuf::internal::ParseNamedEnum<NpcTalkRsp_CmdId>(
    NpcTalkRsp_CmdId_descriptor(), name, value);
}
enum GetSceneNpcPositionReq_CmdId {
  GetSceneNpcPositionReq_CmdId_NONE = 0,
  GetSceneNpcPositionReq_CmdId_CMD_ID = 504,
  GetSceneNpcPositionReq_CmdId_ENET_CHANNEL_ID = 0,
  GetSceneNpcPositionReq_CmdId_ENET_IS_RELIABLE = 1,
  GetSceneNpcPositionReq_CmdId_IS_ALLOW_CLIENT = 1,
  GetSceneNpcPositionReq_CmdId_GetSceneNpcPositionReq_CmdId_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  GetSceneNpcPositionReq_CmdId_GetSceneNpcPositionReq_CmdId_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
bool GetSceneNpcPositionReq_CmdId_IsValid(int value);
const GetSceneNpcPositionReq_CmdId GetSceneNpcPositionReq_CmdId_CmdId_MIN = GetSceneNpcPositionReq_CmdId_NONE;
const GetSceneNpcPositionReq_CmdId GetSceneNpcPositionReq_CmdId_CmdId_MAX = GetSceneNpcPositionReq_CmdId_CMD_ID;
const int GetSceneNpcPositionReq_CmdId_CmdId_ARRAYSIZE = GetSceneNpcPositionReq_CmdId_CmdId_MAX + 1;

const ::google::protobuf::EnumDescriptor* GetSceneNpcPositionReq_CmdId_descriptor();
inline const ::std::string& GetSceneNpcPositionReq_CmdId_Name(GetSceneNpcPositionReq_CmdId value) {
  return ::google::protobuf::internal::NameOfEnum(
    GetSceneNpcPositionReq_CmdId_descriptor(), value);
}
inline bool GetSceneNpcPositionReq_CmdId_Parse(
    const ::std::string& name, GetSceneNpcPositionReq_CmdId* value) {
  return ::google::protobuf::internal::ParseNamedEnum<GetSceneNpcPositionReq_CmdId>(
    GetSceneNpcPositionReq_CmdId_descriptor(), name, value);
}
enum GetSceneNpcPositionRsp_CmdId {
  GetSceneNpcPositionRsp_CmdId_NONE = 0,
  GetSceneNpcPositionRsp_CmdId_CMD_ID = 505,
  GetSceneNpcPositionRsp_CmdId_ENET_CHANNEL_ID = 0,
  GetSceneNpcPositionRsp_CmdId_ENET_IS_RELIABLE = 1,
  GetSceneNpcPositionRsp_CmdId_GetSceneNpcPositionRsp_CmdId_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  GetSceneNpcPositionRsp_CmdId_GetSceneNpcPositionRsp_CmdId_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
bool GetSceneNpcPositionRsp_CmdId_IsValid(int value);
const GetSceneNpcPositionRsp_CmdId GetSceneNpcPositionRsp_CmdId_CmdId_MIN = GetSceneNpcPositionRsp_CmdId_NONE;
const GetSceneNpcPositionRsp_CmdId GetSceneNpcPositionRsp_CmdId_CmdId_MAX = GetSceneNpcPositionRsp_CmdId_CMD_ID;
const int GetSceneNpcPositionRsp_CmdId_CmdId_ARRAYSIZE = GetSceneNpcPositionRsp_CmdId_CmdId_MAX + 1;

const ::google::protobuf::EnumDescriptor* GetSceneNpcPositionRsp_CmdId_descriptor();
inline const ::std::string& GetSceneNpcPositionRsp_CmdId_Name(GetSceneNpcPositionRsp_CmdId value) {
  return ::google::protobuf::internal::NameOfEnum(
    GetSceneNpcPositionRsp_CmdId_descriptor(), value);
}
inline bool GetSceneNpcPositionRsp_CmdId_Parse(
    const ::std::string& name, GetSceneNpcPositionRsp_CmdId* value) {
  return ::google::protobuf::internal::ParseNamedEnum<GetSceneNpcPositionRsp_CmdId>(
    GetSceneNpcPositionRsp_CmdId_descriptor(), name, value);
}
enum NpcTalkType {
  TALK_NONE = 0,
  TALK_START = 1,
  TALK_CHOOSE = 2,
  TALK_NEXT = 3,
  TALK_FINISH = 4,
  NpcTalkType_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  NpcTalkType_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
bool NpcTalkType_IsValid(int value);
const NpcTalkType NpcTalkType_MIN = TALK_NONE;
const NpcTalkType NpcTalkType_MAX = TALK_FINISH;
const int NpcTalkType_ARRAYSIZE = NpcTalkType_MAX + 1;

const ::google::protobuf::EnumDescriptor* NpcTalkType_descriptor();
inline const ::std::string& NpcTalkType_Name(NpcTalkType value) {
  return ::google::protobuf::internal::NameOfEnum(
    NpcTalkType_descriptor(), value);
}
inline bool NpcTalkType_Parse(
    const ::std::string& name, NpcTalkType* value) {
  return ::google::protobuf::internal::ParseNamedEnum<NpcTalkType>(
    NpcTalkType_descriptor(), name, value);
}
// ===================================================================

class NpcTalkReq : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:proto.NpcTalkReq) */ {
 public:
  NpcTalkReq();
  virtual ~NpcTalkReq();

  NpcTalkReq(const NpcTalkReq& from);

  inline NpcTalkReq& operator=(const NpcTalkReq& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  NpcTalkReq(NpcTalkReq&& from) noexcept
    : NpcTalkReq() {
    *this = ::std::move(from);
  }

  inline NpcTalkReq& operator=(NpcTalkReq&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const NpcTalkReq& default_instance();

  static inline const NpcTalkReq* internal_default_instance() {
    return reinterpret_cast<const NpcTalkReq*>(
               &_NpcTalkReq_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    0;

  void Swap(NpcTalkReq* other);
  friend void swap(NpcTalkReq& a, NpcTalkReq& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline NpcTalkReq* New() const PROTOBUF_FINAL { return New(NULL); }

  NpcTalkReq* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const NpcTalkReq& from);
  void MergeFrom(const NpcTalkReq& from);
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
  void InternalSwap(NpcTalkReq* other);
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

  typedef NpcTalkReq_CmdId CmdId;
  static const CmdId NONE =
    NpcTalkReq_CmdId_NONE;
  static const CmdId CMD_ID =
    NpcTalkReq_CmdId_CMD_ID;
  static const CmdId ENET_CHANNEL_ID =
    NpcTalkReq_CmdId_ENET_CHANNEL_ID;
  static const CmdId ENET_IS_RELIABLE =
    NpcTalkReq_CmdId_ENET_IS_RELIABLE;
  static const CmdId IS_ALLOW_CLIENT =
    NpcTalkReq_CmdId_IS_ALLOW_CLIENT;
  static inline bool CmdId_IsValid(int value) {
    return NpcTalkReq_CmdId_IsValid(value);
  }
  static const CmdId CmdId_MIN =
    NpcTalkReq_CmdId_CmdId_MIN;
  static const CmdId CmdId_MAX =
    NpcTalkReq_CmdId_CmdId_MAX;
  static const int CmdId_ARRAYSIZE =
    NpcTalkReq_CmdId_CmdId_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  CmdId_descriptor() {
    return NpcTalkReq_CmdId_descriptor();
  }
  static inline const ::std::string& CmdId_Name(CmdId value) {
    return NpcTalkReq_CmdId_Name(value);
  }
  static inline bool CmdId_Parse(const ::std::string& name,
      CmdId* value) {
    return NpcTalkReq_CmdId_Parse(name, value);
  }

  // accessors -------------------------------------------------------

  // uint32 npc_entity_id = 1;
  void clear_npc_entity_id();
  static const int kNpcEntityIdFieldNumber = 1;
  ::google::protobuf::uint32 npc_entity_id() const;
  void set_npc_entity_id(::google::protobuf::uint32 value);

  // .proto.NpcTalkType talk_type = 2;
  void clear_talk_type();
  static const int kTalkTypeFieldNumber = 2;
  ::proto::NpcTalkType talk_type() const;
  void set_talk_type(::proto::NpcTalkType value);

  // uint32 talk_id = 3;
  void clear_talk_id();
  static const int kTalkIdFieldNumber = 3;
  ::google::protobuf::uint32 talk_id() const;
  void set_talk_id(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:proto.NpcTalkReq)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::uint32 npc_entity_id_;
  int talk_type_;
  ::google::protobuf::uint32 talk_id_;
  mutable int _cached_size_;
  friend struct protobuf_cmd_2fcmd_5fnpc_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class NpcTalkRsp : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:proto.NpcTalkRsp) */ {
 public:
  NpcTalkRsp();
  virtual ~NpcTalkRsp();

  NpcTalkRsp(const NpcTalkRsp& from);

  inline NpcTalkRsp& operator=(const NpcTalkRsp& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  NpcTalkRsp(NpcTalkRsp&& from) noexcept
    : NpcTalkRsp() {
    *this = ::std::move(from);
  }

  inline NpcTalkRsp& operator=(NpcTalkRsp&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const NpcTalkRsp& default_instance();

  static inline const NpcTalkRsp* internal_default_instance() {
    return reinterpret_cast<const NpcTalkRsp*>(
               &_NpcTalkRsp_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    1;

  void Swap(NpcTalkRsp* other);
  friend void swap(NpcTalkRsp& a, NpcTalkRsp& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline NpcTalkRsp* New() const PROTOBUF_FINAL { return New(NULL); }

  NpcTalkRsp* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const NpcTalkRsp& from);
  void MergeFrom(const NpcTalkRsp& from);
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
  void InternalSwap(NpcTalkRsp* other);
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

  typedef NpcTalkRsp_CmdId CmdId;
  static const CmdId NONE =
    NpcTalkRsp_CmdId_NONE;
  static const CmdId CMD_ID =
    NpcTalkRsp_CmdId_CMD_ID;
  static const CmdId ENET_CHANNEL_ID =
    NpcTalkRsp_CmdId_ENET_CHANNEL_ID;
  static const CmdId ENET_IS_RELIABLE =
    NpcTalkRsp_CmdId_ENET_IS_RELIABLE;
  static inline bool CmdId_IsValid(int value) {
    return NpcTalkRsp_CmdId_IsValid(value);
  }
  static const CmdId CmdId_MIN =
    NpcTalkRsp_CmdId_CmdId_MIN;
  static const CmdId CmdId_MAX =
    NpcTalkRsp_CmdId_CmdId_MAX;
  static const int CmdId_ARRAYSIZE =
    NpcTalkRsp_CmdId_CmdId_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  CmdId_descriptor() {
    return NpcTalkRsp_CmdId_descriptor();
  }
  static inline const ::std::string& CmdId_Name(CmdId value) {
    return NpcTalkRsp_CmdId_Name(value);
  }
  static inline bool CmdId_Parse(const ::std::string& name,
      CmdId* value) {
    return NpcTalkRsp_CmdId_Parse(name, value);
  }

  // accessors -------------------------------------------------------

  // int32 retcode = 1;
  void clear_retcode();
  static const int kRetcodeFieldNumber = 1;
  ::google::protobuf::int32 retcode() const;
  void set_retcode(::google::protobuf::int32 value);

  // uint32 npc_entity_id = 2;
  void clear_npc_entity_id();
  static const int kNpcEntityIdFieldNumber = 2;
  ::google::protobuf::uint32 npc_entity_id() const;
  void set_npc_entity_id(::google::protobuf::uint32 value);

  // .proto.NpcTalkType talk_type = 3;
  void clear_talk_type();
  static const int kTalkTypeFieldNumber = 3;
  ::proto::NpcTalkType talk_type() const;
  void set_talk_type(::proto::NpcTalkType value);

  // uint32 cur_talk_id = 4;
  void clear_cur_talk_id();
  static const int kCurTalkIdFieldNumber = 4;
  ::google::protobuf::uint32 cur_talk_id() const;
  void set_cur_talk_id(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:proto.NpcTalkRsp)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::int32 retcode_;
  ::google::protobuf::uint32 npc_entity_id_;
  int talk_type_;
  ::google::protobuf::uint32 cur_talk_id_;
  mutable int _cached_size_;
  friend struct protobuf_cmd_2fcmd_5fnpc_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class GetSceneNpcPositionReq : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:proto.GetSceneNpcPositionReq) */ {
 public:
  GetSceneNpcPositionReq();
  virtual ~GetSceneNpcPositionReq();

  GetSceneNpcPositionReq(const GetSceneNpcPositionReq& from);

  inline GetSceneNpcPositionReq& operator=(const GetSceneNpcPositionReq& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  GetSceneNpcPositionReq(GetSceneNpcPositionReq&& from) noexcept
    : GetSceneNpcPositionReq() {
    *this = ::std::move(from);
  }

  inline GetSceneNpcPositionReq& operator=(GetSceneNpcPositionReq&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const GetSceneNpcPositionReq& default_instance();

  static inline const GetSceneNpcPositionReq* internal_default_instance() {
    return reinterpret_cast<const GetSceneNpcPositionReq*>(
               &_GetSceneNpcPositionReq_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    2;

  void Swap(GetSceneNpcPositionReq* other);
  friend void swap(GetSceneNpcPositionReq& a, GetSceneNpcPositionReq& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline GetSceneNpcPositionReq* New() const PROTOBUF_FINAL { return New(NULL); }

  GetSceneNpcPositionReq* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const GetSceneNpcPositionReq& from);
  void MergeFrom(const GetSceneNpcPositionReq& from);
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
  void InternalSwap(GetSceneNpcPositionReq* other);
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

  typedef GetSceneNpcPositionReq_CmdId CmdId;
  static const CmdId NONE =
    GetSceneNpcPositionReq_CmdId_NONE;
  static const CmdId CMD_ID =
    GetSceneNpcPositionReq_CmdId_CMD_ID;
  static const CmdId ENET_CHANNEL_ID =
    GetSceneNpcPositionReq_CmdId_ENET_CHANNEL_ID;
  static const CmdId ENET_IS_RELIABLE =
    GetSceneNpcPositionReq_CmdId_ENET_IS_RELIABLE;
  static const CmdId IS_ALLOW_CLIENT =
    GetSceneNpcPositionReq_CmdId_IS_ALLOW_CLIENT;
  static inline bool CmdId_IsValid(int value) {
    return GetSceneNpcPositionReq_CmdId_IsValid(value);
  }
  static const CmdId CmdId_MIN =
    GetSceneNpcPositionReq_CmdId_CmdId_MIN;
  static const CmdId CmdId_MAX =
    GetSceneNpcPositionReq_CmdId_CmdId_MAX;
  static const int CmdId_ARRAYSIZE =
    GetSceneNpcPositionReq_CmdId_CmdId_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  CmdId_descriptor() {
    return GetSceneNpcPositionReq_CmdId_descriptor();
  }
  static inline const ::std::string& CmdId_Name(CmdId value) {
    return GetSceneNpcPositionReq_CmdId_Name(value);
  }
  static inline bool CmdId_Parse(const ::std::string& name,
      CmdId* value) {
    return GetSceneNpcPositionReq_CmdId_Parse(name, value);
  }

  // accessors -------------------------------------------------------

  // repeated uint32 npc_id_list = 2;
  int npc_id_list_size() const;
  void clear_npc_id_list();
  static const int kNpcIdListFieldNumber = 2;
  ::google::protobuf::uint32 npc_id_list(int index) const;
  void set_npc_id_list(int index, ::google::protobuf::uint32 value);
  void add_npc_id_list(::google::protobuf::uint32 value);
  const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
      npc_id_list() const;
  ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
      mutable_npc_id_list();

  // uint32 scene_id = 1;
  void clear_scene_id();
  static const int kSceneIdFieldNumber = 1;
  ::google::protobuf::uint32 scene_id() const;
  void set_scene_id(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:proto.GetSceneNpcPositionReq)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::RepeatedField< ::google::protobuf::uint32 > npc_id_list_;
  mutable int _npc_id_list_cached_byte_size_;
  ::google::protobuf::uint32 scene_id_;
  mutable int _cached_size_;
  friend struct protobuf_cmd_2fcmd_5fnpc_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class GetSceneNpcPositionRsp : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:proto.GetSceneNpcPositionRsp) */ {
 public:
  GetSceneNpcPositionRsp();
  virtual ~GetSceneNpcPositionRsp();

  GetSceneNpcPositionRsp(const GetSceneNpcPositionRsp& from);

  inline GetSceneNpcPositionRsp& operator=(const GetSceneNpcPositionRsp& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  GetSceneNpcPositionRsp(GetSceneNpcPositionRsp&& from) noexcept
    : GetSceneNpcPositionRsp() {
    *this = ::std::move(from);
  }

  inline GetSceneNpcPositionRsp& operator=(GetSceneNpcPositionRsp&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const GetSceneNpcPositionRsp& default_instance();

  static inline const GetSceneNpcPositionRsp* internal_default_instance() {
    return reinterpret_cast<const GetSceneNpcPositionRsp*>(
               &_GetSceneNpcPositionRsp_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    3;

  void Swap(GetSceneNpcPositionRsp* other);
  friend void swap(GetSceneNpcPositionRsp& a, GetSceneNpcPositionRsp& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline GetSceneNpcPositionRsp* New() const PROTOBUF_FINAL { return New(NULL); }

  GetSceneNpcPositionRsp* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const GetSceneNpcPositionRsp& from);
  void MergeFrom(const GetSceneNpcPositionRsp& from);
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
  void InternalSwap(GetSceneNpcPositionRsp* other);
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

  typedef GetSceneNpcPositionRsp_CmdId CmdId;
  static const CmdId NONE =
    GetSceneNpcPositionRsp_CmdId_NONE;
  static const CmdId CMD_ID =
    GetSceneNpcPositionRsp_CmdId_CMD_ID;
  static const CmdId ENET_CHANNEL_ID =
    GetSceneNpcPositionRsp_CmdId_ENET_CHANNEL_ID;
  static const CmdId ENET_IS_RELIABLE =
    GetSceneNpcPositionRsp_CmdId_ENET_IS_RELIABLE;
  static inline bool CmdId_IsValid(int value) {
    return GetSceneNpcPositionRsp_CmdId_IsValid(value);
  }
  static const CmdId CmdId_MIN =
    GetSceneNpcPositionRsp_CmdId_CmdId_MIN;
  static const CmdId CmdId_MAX =
    GetSceneNpcPositionRsp_CmdId_CmdId_MAX;
  static const int CmdId_ARRAYSIZE =
    GetSceneNpcPositionRsp_CmdId_CmdId_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  CmdId_descriptor() {
    return GetSceneNpcPositionRsp_CmdId_descriptor();
  }
  static inline const ::std::string& CmdId_Name(CmdId value) {
    return GetSceneNpcPositionRsp_CmdId_Name(value);
  }
  static inline bool CmdId_Parse(const ::std::string& name,
      CmdId* value) {
    return GetSceneNpcPositionRsp_CmdId_Parse(name, value);
  }

  // accessors -------------------------------------------------------

  // repeated .proto.NpcPositionInfo npc_info_list = 3;
  int npc_info_list_size() const;
  void clear_npc_info_list();
  static const int kNpcInfoListFieldNumber = 3;
  const ::proto::NpcPositionInfo& npc_info_list(int index) const;
  ::proto::NpcPositionInfo* mutable_npc_info_list(int index);
  ::proto::NpcPositionInfo* add_npc_info_list();
  ::google::protobuf::RepeatedPtrField< ::proto::NpcPositionInfo >*
      mutable_npc_info_list();
  const ::google::protobuf::RepeatedPtrField< ::proto::NpcPositionInfo >&
      npc_info_list() const;

  // int32 retcode = 1;
  void clear_retcode();
  static const int kRetcodeFieldNumber = 1;
  ::google::protobuf::int32 retcode() const;
  void set_retcode(::google::protobuf::int32 value);

  // uint32 scene_id = 2;
  void clear_scene_id();
  static const int kSceneIdFieldNumber = 2;
  ::google::protobuf::uint32 scene_id() const;
  void set_scene_id(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:proto.GetSceneNpcPositionRsp)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::RepeatedPtrField< ::proto::NpcPositionInfo > npc_info_list_;
  ::google::protobuf::int32 retcode_;
  ::google::protobuf::uint32 scene_id_;
  mutable int _cached_size_;
  friend struct protobuf_cmd_2fcmd_5fnpc_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// NpcTalkReq

// uint32 npc_entity_id = 1;
inline void NpcTalkReq::clear_npc_entity_id() {
  npc_entity_id_ = 0u;
}
inline ::google::protobuf::uint32 NpcTalkReq::npc_entity_id() const {
  // @@protoc_insertion_point(field_get:proto.NpcTalkReq.npc_entity_id)
  return npc_entity_id_;
}
inline void NpcTalkReq::set_npc_entity_id(::google::protobuf::uint32 value) {
  
  npc_entity_id_ = value;
  // @@protoc_insertion_point(field_set:proto.NpcTalkReq.npc_entity_id)
}

// .proto.NpcTalkType talk_type = 2;
inline void NpcTalkReq::clear_talk_type() {
  talk_type_ = 0;
}
inline ::proto::NpcTalkType NpcTalkReq::talk_type() const {
  // @@protoc_insertion_point(field_get:proto.NpcTalkReq.talk_type)
  return static_cast< ::proto::NpcTalkType >(talk_type_);
}
inline void NpcTalkReq::set_talk_type(::proto::NpcTalkType value) {
  
  talk_type_ = value;
  // @@protoc_insertion_point(field_set:proto.NpcTalkReq.talk_type)
}

// uint32 talk_id = 3;
inline void NpcTalkReq::clear_talk_id() {
  talk_id_ = 0u;
}
inline ::google::protobuf::uint32 NpcTalkReq::talk_id() const {
  // @@protoc_insertion_point(field_get:proto.NpcTalkReq.talk_id)
  return talk_id_;
}
inline void NpcTalkReq::set_talk_id(::google::protobuf::uint32 value) {
  
  talk_id_ = value;
  // @@protoc_insertion_point(field_set:proto.NpcTalkReq.talk_id)
}

// -------------------------------------------------------------------

// NpcTalkRsp

// int32 retcode = 1;
inline void NpcTalkRsp::clear_retcode() {
  retcode_ = 0;
}
inline ::google::protobuf::int32 NpcTalkRsp::retcode() const {
  // @@protoc_insertion_point(field_get:proto.NpcTalkRsp.retcode)
  return retcode_;
}
inline void NpcTalkRsp::set_retcode(::google::protobuf::int32 value) {
  
  retcode_ = value;
  // @@protoc_insertion_point(field_set:proto.NpcTalkRsp.retcode)
}

// uint32 npc_entity_id = 2;
inline void NpcTalkRsp::clear_npc_entity_id() {
  npc_entity_id_ = 0u;
}
inline ::google::protobuf::uint32 NpcTalkRsp::npc_entity_id() const {
  // @@protoc_insertion_point(field_get:proto.NpcTalkRsp.npc_entity_id)
  return npc_entity_id_;
}
inline void NpcTalkRsp::set_npc_entity_id(::google::protobuf::uint32 value) {
  
  npc_entity_id_ = value;
  // @@protoc_insertion_point(field_set:proto.NpcTalkRsp.npc_entity_id)
}

// .proto.NpcTalkType talk_type = 3;
inline void NpcTalkRsp::clear_talk_type() {
  talk_type_ = 0;
}
inline ::proto::NpcTalkType NpcTalkRsp::talk_type() const {
  // @@protoc_insertion_point(field_get:proto.NpcTalkRsp.talk_type)
  return static_cast< ::proto::NpcTalkType >(talk_type_);
}
inline void NpcTalkRsp::set_talk_type(::proto::NpcTalkType value) {
  
  talk_type_ = value;
  // @@protoc_insertion_point(field_set:proto.NpcTalkRsp.talk_type)
}

// uint32 cur_talk_id = 4;
inline void NpcTalkRsp::clear_cur_talk_id() {
  cur_talk_id_ = 0u;
}
inline ::google::protobuf::uint32 NpcTalkRsp::cur_talk_id() const {
  // @@protoc_insertion_point(field_get:proto.NpcTalkRsp.cur_talk_id)
  return cur_talk_id_;
}
inline void NpcTalkRsp::set_cur_talk_id(::google::protobuf::uint32 value) {
  
  cur_talk_id_ = value;
  // @@protoc_insertion_point(field_set:proto.NpcTalkRsp.cur_talk_id)
}

// -------------------------------------------------------------------

// GetSceneNpcPositionReq

// uint32 scene_id = 1;
inline void GetSceneNpcPositionReq::clear_scene_id() {
  scene_id_ = 0u;
}
inline ::google::protobuf::uint32 GetSceneNpcPositionReq::scene_id() const {
  // @@protoc_insertion_point(field_get:proto.GetSceneNpcPositionReq.scene_id)
  return scene_id_;
}
inline void GetSceneNpcPositionReq::set_scene_id(::google::protobuf::uint32 value) {
  
  scene_id_ = value;
  // @@protoc_insertion_point(field_set:proto.GetSceneNpcPositionReq.scene_id)
}

// repeated uint32 npc_id_list = 2;
inline int GetSceneNpcPositionReq::npc_id_list_size() const {
  return npc_id_list_.size();
}
inline void GetSceneNpcPositionReq::clear_npc_id_list() {
  npc_id_list_.Clear();
}
inline ::google::protobuf::uint32 GetSceneNpcPositionReq::npc_id_list(int index) const {
  // @@protoc_insertion_point(field_get:proto.GetSceneNpcPositionReq.npc_id_list)
  return npc_id_list_.Get(index);
}
inline void GetSceneNpcPositionReq::set_npc_id_list(int index, ::google::protobuf::uint32 value) {
  npc_id_list_.Set(index, value);
  // @@protoc_insertion_point(field_set:proto.GetSceneNpcPositionReq.npc_id_list)
}
inline void GetSceneNpcPositionReq::add_npc_id_list(::google::protobuf::uint32 value) {
  npc_id_list_.Add(value);
  // @@protoc_insertion_point(field_add:proto.GetSceneNpcPositionReq.npc_id_list)
}
inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
GetSceneNpcPositionReq::npc_id_list() const {
  // @@protoc_insertion_point(field_list:proto.GetSceneNpcPositionReq.npc_id_list)
  return npc_id_list_;
}
inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
GetSceneNpcPositionReq::mutable_npc_id_list() {
  // @@protoc_insertion_point(field_mutable_list:proto.GetSceneNpcPositionReq.npc_id_list)
  return &npc_id_list_;
}

// -------------------------------------------------------------------

// GetSceneNpcPositionRsp

// int32 retcode = 1;
inline void GetSceneNpcPositionRsp::clear_retcode() {
  retcode_ = 0;
}
inline ::google::protobuf::int32 GetSceneNpcPositionRsp::retcode() const {
  // @@protoc_insertion_point(field_get:proto.GetSceneNpcPositionRsp.retcode)
  return retcode_;
}
inline void GetSceneNpcPositionRsp::set_retcode(::google::protobuf::int32 value) {
  
  retcode_ = value;
  // @@protoc_insertion_point(field_set:proto.GetSceneNpcPositionRsp.retcode)
}

// uint32 scene_id = 2;
inline void GetSceneNpcPositionRsp::clear_scene_id() {
  scene_id_ = 0u;
}
inline ::google::protobuf::uint32 GetSceneNpcPositionRsp::scene_id() const {
  // @@protoc_insertion_point(field_get:proto.GetSceneNpcPositionRsp.scene_id)
  return scene_id_;
}
inline void GetSceneNpcPositionRsp::set_scene_id(::google::protobuf::uint32 value) {
  
  scene_id_ = value;
  // @@protoc_insertion_point(field_set:proto.GetSceneNpcPositionRsp.scene_id)
}

// repeated .proto.NpcPositionInfo npc_info_list = 3;
inline int GetSceneNpcPositionRsp::npc_info_list_size() const {
  return npc_info_list_.size();
}
inline void GetSceneNpcPositionRsp::clear_npc_info_list() {
  npc_info_list_.Clear();
}
inline const ::proto::NpcPositionInfo& GetSceneNpcPositionRsp::npc_info_list(int index) const {
  // @@protoc_insertion_point(field_get:proto.GetSceneNpcPositionRsp.npc_info_list)
  return npc_info_list_.Get(index);
}
inline ::proto::NpcPositionInfo* GetSceneNpcPositionRsp::mutable_npc_info_list(int index) {
  // @@protoc_insertion_point(field_mutable:proto.GetSceneNpcPositionRsp.npc_info_list)
  return npc_info_list_.Mutable(index);
}
inline ::proto::NpcPositionInfo* GetSceneNpcPositionRsp::add_npc_info_list() {
  // @@protoc_insertion_point(field_add:proto.GetSceneNpcPositionRsp.npc_info_list)
  return npc_info_list_.Add();
}
inline ::google::protobuf::RepeatedPtrField< ::proto::NpcPositionInfo >*
GetSceneNpcPositionRsp::mutable_npc_info_list() {
  // @@protoc_insertion_point(field_mutable_list:proto.GetSceneNpcPositionRsp.npc_info_list)
  return &npc_info_list_;
}
inline const ::google::protobuf::RepeatedPtrField< ::proto::NpcPositionInfo >&
GetSceneNpcPositionRsp::npc_info_list() const {
  // @@protoc_insertion_point(field_list:proto.GetSceneNpcPositionRsp.npc_info_list)
  return npc_info_list_;
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS
// -------------------------------------------------------------------

// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)


}  // namespace proto

namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::proto::NpcTalkReq_CmdId> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::proto::NpcTalkReq_CmdId>() {
  return ::proto::NpcTalkReq_CmdId_descriptor();
}
template <> struct is_proto_enum< ::proto::NpcTalkRsp_CmdId> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::proto::NpcTalkRsp_CmdId>() {
  return ::proto::NpcTalkRsp_CmdId_descriptor();
}
template <> struct is_proto_enum< ::proto::GetSceneNpcPositionReq_CmdId> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::proto::GetSceneNpcPositionReq_CmdId>() {
  return ::proto::GetSceneNpcPositionReq_CmdId_descriptor();
}
template <> struct is_proto_enum< ::proto::GetSceneNpcPositionRsp_CmdId> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::proto::GetSceneNpcPositionRsp_CmdId>() {
  return ::proto::GetSceneNpcPositionRsp_CmdId_descriptor();
}
template <> struct is_proto_enum< ::proto::NpcTalkType> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::proto::NpcTalkType>() {
  return ::proto::NpcTalkType_descriptor();
}

}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_cmd_2fcmd_5fnpc_2eproto__INCLUDED
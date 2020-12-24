// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Mobile.proto

#include "Mobile.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
namespace mobile {
class GetMobileAPNRequestDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<GetMobileAPNRequest>
      _instance;
} _GetMobileAPNRequest_default_instance_;
class GetMobileAPNResponseDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<GetMobileAPNResponse>
      _instance;
} _GetMobileAPNResponse_default_instance_;
}  // namespace mobile
static void InitDefaultsscc_info_GetMobileAPNRequest_Mobile_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::mobile::_GetMobileAPNRequest_default_instance_;
    new (ptr)::mobile::GetMobileAPNRequest();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::mobile::GetMobileAPNRequest::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0>
    scc_info_GetMobileAPNRequest_Mobile_2eproto = {
        {ATOMIC_VAR_INIT(
             ::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized),
         0, 0, InitDefaultsscc_info_GetMobileAPNRequest_Mobile_2eproto},
        {}};

static void InitDefaultsscc_info_GetMobileAPNResponse_Mobile_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::mobile::_GetMobileAPNResponse_default_instance_;
    new (ptr)::mobile::GetMobileAPNResponse();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::mobile::GetMobileAPNResponse::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0>
    scc_info_GetMobileAPNResponse_Mobile_2eproto = {
        {ATOMIC_VAR_INIT(
             ::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized),
         0, 0, InitDefaultsscc_info_GetMobileAPNResponse_Mobile_2eproto},
        {}};

static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_Mobile_2eproto[2];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const**
    file_level_enum_descriptors_Mobile_2eproto = nullptr;
static const ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor*
    file_level_service_descriptors_Mobile_2eproto[1];

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_Mobile_2eproto::offsets
    [] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
        ~0u,  // no _has_bits_
        PROTOBUF_FIELD_OFFSET(::mobile::GetMobileAPNRequest,
                              _internal_metadata_),
        ~0u,  // no _extensions_
        ~0u,  // no _oneof_case_
        ~0u,  // no _weak_field_map_
        PROTOBUF_FIELD_OFFSET(::mobile::GetMobileAPNRequest, cid_),
        ~0u,  // no _has_bits_
        PROTOBUF_FIELD_OFFSET(::mobile::GetMobileAPNResponse,
                              _internal_metadata_),
        ~0u,  // no _extensions_
        ~0u,  // no _oneof_case_
        ~0u,  // no _weak_field_map_
        PROTOBUF_FIELD_OFFSET(::mobile::GetMobileAPNResponse, apn_),
        PROTOBUF_FIELD_OFFSET(::mobile::GetMobileAPNResponse, cid_),
        PROTOBUF_FIELD_OFFSET(::mobile::GetMobileAPNResponse, type_), };
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas
    [] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
        {0, -1, sizeof(::mobile::GetMobileAPNRequest)},
        {6, -1, sizeof(::mobile::GetMobileAPNResponse)}, };

static ::PROTOBUF_NAMESPACE_ID::Message const* const file_default_instances[] =
    {reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(
         &::mobile::_GetMobileAPNRequest_default_instance_),
     reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(
         &::mobile::_GetMobileAPNResponse_default_instance_), };

const char descriptor_table_protodef_Mobile_2eproto[] PROTOBUF_SECTION_VARIABLE(
    protodesc_cold) =
    "\n\014Mobile.proto\022\006mobile\"\"\n\023GetMobileAPNRe"
    "quest\022\013\n\003cid\030\002 \001(\r\">\n\024GetMobileAPNRespon"
    "se\022\013\n\003apn\030\001 \001(\t\022\013\n\003cid\030\002 "
    "\001(\r\022\014\n\004type\030\003 \001"
    "(\r2`\n\023GetMobileAPNService\022I\n\014GetMobileAP"
    "N\022\033.mobile.GetMobileAPNRequest\032\034.mobile."
    "GetMobileAPNResponseB\003\200\001\001b\006proto3";
static const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable* const
    descriptor_table_Mobile_2eproto_deps[1] = {};
static ::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase* const
    descriptor_table_Mobile_2eproto_sccs[2] = {
        &scc_info_GetMobileAPNRequest_Mobile_2eproto.base,
        &scc_info_GetMobileAPNResponse_Mobile_2eproto.base, };
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag
    descriptor_table_Mobile_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable
    descriptor_table_Mobile_2eproto = {
        false,
        false,
        descriptor_table_protodef_Mobile_2eproto,
        "Mobile.proto",
        233,
        &descriptor_table_Mobile_2eproto_once,
        descriptor_table_Mobile_2eproto_sccs,
        descriptor_table_Mobile_2eproto_deps,
        2,
        0,
        schemas,
        file_default_instances,
        TableStruct_Mobile_2eproto::offsets,
        file_level_metadata_Mobile_2eproto,
        2,
        file_level_enum_descriptors_Mobile_2eproto,
        file_level_service_descriptors_Mobile_2eproto, };

// Force running AddDescriptors() at dynamic initialization time.
static bool dynamic_init_dummy_Mobile_2eproto =
    (static_cast<void>(::PROTOBUF_NAMESPACE_ID::internal::AddDescriptors(
         &descriptor_table_Mobile_2eproto)),
     true);
namespace mobile {

// ===================================================================

void GetMobileAPNRequest::InitAsDefaultInstance() {}
class GetMobileAPNRequest::_Internal {
 public:
};

GetMobileAPNRequest::GetMobileAPNRequest(::PROTOBUF_NAMESPACE_ID::Arena* arena)
    : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor();
  RegisterArenaDtor(arena);
  // @@protoc_insertion_point(arena_constructor:mobile.GetMobileAPNRequest)
}
GetMobileAPNRequest::GetMobileAPNRequest(const GetMobileAPNRequest& from)
    : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(
      from._internal_metadata_);
  cid_ = from.cid_;
  // @@protoc_insertion_point(copy_constructor:mobile.GetMobileAPNRequest)
}

void GetMobileAPNRequest::SharedCtor() { cid_ = 0u; }

GetMobileAPNRequest::~GetMobileAPNRequest() {
  // @@protoc_insertion_point(destructor:mobile.GetMobileAPNRequest)
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

void GetMobileAPNRequest::SharedDtor() { GOOGLE_DCHECK(GetArena() == nullptr); }

void GetMobileAPNRequest::ArenaDtor(void* object) {
  GetMobileAPNRequest* _this = reinterpret_cast<GetMobileAPNRequest*>(object);
  (void)_this;
}
void GetMobileAPNRequest::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {}
void GetMobileAPNRequest::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const GetMobileAPNRequest& GetMobileAPNRequest::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(
      &::scc_info_GetMobileAPNRequest_Mobile_2eproto.base);
  return *internal_default_instance();
}

void GetMobileAPNRequest::Clear() {
  // @@protoc_insertion_point(message_clear_start:mobile.GetMobileAPNRequest)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void)cached_has_bits;

  cid_ = 0u;
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* GetMobileAPNRequest::_InternalParse(
    const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) \
  if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  ::PROTOBUF_NAMESPACE_ID::Arena* arena = GetArena();
  (void)arena;
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // uint32 cid = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(
                static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 16)) {
          cid_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
                                _internal_metadata_.mutable_unknown_fields<
                                    ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
                                ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }    // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* GetMobileAPNRequest::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target,
    ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:mobile.GetMobileAPNRequest)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void)cached_has_bits;

  // uint32 cid = 2;
  if (this->cid() != 0) {
    target = stream->EnsureSpace(target);
    target =
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt32ToArray(
            2, this->_internal_cid(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::
        InternalSerializeUnknownFieldsToArray(
            _internal_metadata_.unknown_fields<
                ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(
                ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance),
            target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:mobile.GetMobileAPNRequest)
  return target;
}

size_t GetMobileAPNRequest::ByteSizeLong() const {
  // @@protoc_insertion_point(message_byte_size_start:mobile.GetMobileAPNRequest)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void)cached_has_bits;

  // uint32 cid = 2;
  if (this->cid() != 0) {
    total_size +=
        1 + ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt32Size(
                this->_internal_cid());
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void GetMobileAPNRequest::MergeFrom(
    const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  // @@protoc_insertion_point(generalized_merge_from_start:mobile.GetMobileAPNRequest)
  GOOGLE_DCHECK_NE(&from, this);
  const GetMobileAPNRequest* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<GetMobileAPNRequest>(
          &from);
  if (source == nullptr) {
    // @@protoc_insertion_point(generalized_merge_from_cast_fail:mobile.GetMobileAPNRequest)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
    // @@protoc_insertion_point(generalized_merge_from_cast_success:mobile.GetMobileAPNRequest)
    MergeFrom(*source);
  }
}

void GetMobileAPNRequest::MergeFrom(const GetMobileAPNRequest& from) {
  // @@protoc_insertion_point(class_specific_merge_from_start:mobile.GetMobileAPNRequest)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(
      from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void)cached_has_bits;

  if (from.cid() != 0) {
    _internal_set_cid(from._internal_cid());
  }
}

void GetMobileAPNRequest::CopyFrom(
    const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  // @@protoc_insertion_point(generalized_copy_from_start:mobile.GetMobileAPNRequest)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void GetMobileAPNRequest::CopyFrom(const GetMobileAPNRequest& from) {
  // @@protoc_insertion_point(class_specific_copy_from_start:mobile.GetMobileAPNRequest)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool GetMobileAPNRequest::IsInitialized() const { return true; }

void GetMobileAPNRequest::InternalSwap(GetMobileAPNRequest* other) {
  using std::swap;
  _internal_metadata_.Swap<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(
      &other->_internal_metadata_);
  swap(cid_, other->cid_);
}

::PROTOBUF_NAMESPACE_ID::Metadata GetMobileAPNRequest::GetMetadata() const {
  return GetMetadataStatic();
}

// ===================================================================

void GetMobileAPNResponse::InitAsDefaultInstance() {}
class GetMobileAPNResponse::_Internal {
 public:
};

GetMobileAPNResponse::GetMobileAPNResponse(
    ::PROTOBUF_NAMESPACE_ID::Arena* arena)
    : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor();
  RegisterArenaDtor(arena);
  // @@protoc_insertion_point(arena_constructor:mobile.GetMobileAPNResponse)
}
GetMobileAPNResponse::GetMobileAPNResponse(const GetMobileAPNResponse& from)
    : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(
      from._internal_metadata_);
  apn_.UnsafeSetDefault(
      &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_apn().empty()) {
    apn_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
             from._internal_apn(), GetArena());
  }
  ::memcpy(&cid_, &from.cid_,
           static_cast<size_t>(reinterpret_cast<char*>(&type_) -
                               reinterpret_cast<char*>(&cid_)) +
               sizeof(type_));
  // @@protoc_insertion_point(copy_constructor:mobile.GetMobileAPNResponse)
}

void GetMobileAPNResponse::SharedCtor() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(
      &scc_info_GetMobileAPNResponse_Mobile_2eproto.base);
  apn_.UnsafeSetDefault(
      &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  ::memset(&cid_, 0, static_cast<size_t>(reinterpret_cast<char*>(&type_) -
                                         reinterpret_cast<char*>(&cid_)) +
                         sizeof(type_));
}

GetMobileAPNResponse::~GetMobileAPNResponse() {
  // @@protoc_insertion_point(destructor:mobile.GetMobileAPNResponse)
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

void GetMobileAPNResponse::SharedDtor() {
  GOOGLE_DCHECK(GetArena() == nullptr);
  apn_.DestroyNoArena(
      &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

void GetMobileAPNResponse::ArenaDtor(void* object) {
  GetMobileAPNResponse* _this = reinterpret_cast<GetMobileAPNResponse*>(object);
  (void)_this;
}
void GetMobileAPNResponse::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {}
void GetMobileAPNResponse::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const GetMobileAPNResponse& GetMobileAPNResponse::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(
      &::scc_info_GetMobileAPNResponse_Mobile_2eproto.base);
  return *internal_default_instance();
}

void GetMobileAPNResponse::Clear() {
  // @@protoc_insertion_point(message_clear_start:mobile.GetMobileAPNResponse)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void)cached_has_bits;

  apn_.ClearToEmpty(
      &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      GetArena());
  ::memset(&cid_, 0, static_cast<size_t>(reinterpret_cast<char*>(&type_) -
                                         reinterpret_cast<char*>(&cid_)) +
                         sizeof(type_));
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* GetMobileAPNResponse::_InternalParse(
    const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) \
  if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  ::PROTOBUF_NAMESPACE_ID::Arena* arena = GetArena();
  (void)arena;
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // string apn = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(
                static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          auto str = _internal_mutable_apn();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(
              str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(
              str, "mobile.GetMobileAPNResponse.apn"));
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // uint32 cid = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(
                static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 16)) {
          cid_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // uint32 type = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(
                static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 24)) {
          type_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
                                _internal_metadata_.mutable_unknown_fields<
                                    ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
                                ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }    // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* GetMobileAPNResponse::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target,
    ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:mobile.GetMobileAPNResponse)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void)cached_has_bits;

  // string apn = 1;
  if (this->apn().size() > 0) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
        this->_internal_apn().data(),
        static_cast<int>(this->_internal_apn().length()),
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
        "mobile.GetMobileAPNResponse.apn");
    target = stream->WriteStringMaybeAliased(1, this->_internal_apn(), target);
  }

  // uint32 cid = 2;
  if (this->cid() != 0) {
    target = stream->EnsureSpace(target);
    target =
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt32ToArray(
            2, this->_internal_cid(), target);
  }

  // uint32 type = 3;
  if (this->type() != 0) {
    target = stream->EnsureSpace(target);
    target =
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt32ToArray(
            3, this->_internal_type(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::
        InternalSerializeUnknownFieldsToArray(
            _internal_metadata_.unknown_fields<
                ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(
                ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance),
            target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:mobile.GetMobileAPNResponse)
  return target;
}

size_t GetMobileAPNResponse::ByteSizeLong() const {
  // @@protoc_insertion_point(message_byte_size_start:mobile.GetMobileAPNResponse)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void)cached_has_bits;

  // string apn = 1;
  if (this->apn().size() > 0) {
    total_size +=
        1 + ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
                this->_internal_apn());
  }

  // uint32 cid = 2;
  if (this->cid() != 0) {
    total_size +=
        1 + ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt32Size(
                this->_internal_cid());
  }

  // uint32 type = 3;
  if (this->type() != 0) {
    total_size +=
        1 + ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt32Size(
                this->_internal_type());
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void GetMobileAPNResponse::MergeFrom(
    const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  // @@protoc_insertion_point(generalized_merge_from_start:mobile.GetMobileAPNResponse)
  GOOGLE_DCHECK_NE(&from, this);
  const GetMobileAPNResponse* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<GetMobileAPNResponse>(
          &from);
  if (source == nullptr) {
    // @@protoc_insertion_point(generalized_merge_from_cast_fail:mobile.GetMobileAPNResponse)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
    // @@protoc_insertion_point(generalized_merge_from_cast_success:mobile.GetMobileAPNResponse)
    MergeFrom(*source);
  }
}

void GetMobileAPNResponse::MergeFrom(const GetMobileAPNResponse& from) {
  // @@protoc_insertion_point(class_specific_merge_from_start:mobile.GetMobileAPNResponse)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(
      from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void)cached_has_bits;

  if (from.apn().size() > 0) {
    _internal_set_apn(from._internal_apn());
  }
  if (from.cid() != 0) {
    _internal_set_cid(from._internal_cid());
  }
  if (from.type() != 0) {
    _internal_set_type(from._internal_type());
  }
}

void GetMobileAPNResponse::CopyFrom(
    const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  // @@protoc_insertion_point(generalized_copy_from_start:mobile.GetMobileAPNResponse)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void GetMobileAPNResponse::CopyFrom(const GetMobileAPNResponse& from) {
  // @@protoc_insertion_point(class_specific_copy_from_start:mobile.GetMobileAPNResponse)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool GetMobileAPNResponse::IsInitialized() const { return true; }

void GetMobileAPNResponse::InternalSwap(GetMobileAPNResponse* other) {
  using std::swap;
  _internal_metadata_.Swap<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(
      &other->_internal_metadata_);
  apn_.Swap(&other->apn_,
            &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
            GetArena());
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(GetMobileAPNResponse, type_) +
      sizeof(GetMobileAPNResponse::type_) -
      PROTOBUF_FIELD_OFFSET(GetMobileAPNResponse, cid_)>(
      reinterpret_cast<char*>(&cid_), reinterpret_cast<char*>(&other->cid_));
}

::PROTOBUF_NAMESPACE_ID::Metadata GetMobileAPNResponse::GetMetadata() const {
  return GetMetadataStatic();
}

// ===================================================================

GetMobileAPNService::~GetMobileAPNService() {}

const ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor*
GetMobileAPNService::descriptor() {
  ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_Mobile_2eproto);
  return file_level_service_descriptors_Mobile_2eproto[0];
}

const ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor*
GetMobileAPNService::GetDescriptor() {
  return descriptor();
}

void GetMobileAPNService::GetMobileAPN(
    ::PROTOBUF_NAMESPACE_ID::RpcController* controller,
    const ::mobile::GetMobileAPNRequest*, ::mobile::GetMobileAPNResponse*,
    ::google::protobuf::Closure* done) {
  controller->SetFailed("Method GetMobileAPN() not implemented.");
  done->Run();
}

void GetMobileAPNService::CallMethod(
    const ::PROTOBUF_NAMESPACE_ID::MethodDescriptor* method,
    ::PROTOBUF_NAMESPACE_ID::RpcController* controller,
    const ::PROTOBUF_NAMESPACE_ID::Message* request,
    ::PROTOBUF_NAMESPACE_ID::Message* response,
    ::google::protobuf::Closure* done) {
  GOOGLE_DCHECK_EQ(method->service(),
                   file_level_service_descriptors_Mobile_2eproto[0]);
  switch (method->index()) {
    case 0:
      GetMobileAPN(controller,
                   ::PROTOBUF_NAMESPACE_ID::internal::DownCast<
                       const ::mobile::GetMobileAPNRequest*>(request),
                   ::PROTOBUF_NAMESPACE_ID::internal::DownCast<
                       ::mobile::GetMobileAPNResponse*>(response),
                   done);
      break;
    default:
      GOOGLE_LOG(FATAL) << "Bad method index; this should never happen.";
      break;
  }
}

const ::PROTOBUF_NAMESPACE_ID::Message&
GetMobileAPNService::GetRequestPrototype(
    const ::PROTOBUF_NAMESPACE_ID::MethodDescriptor* method) const {
  GOOGLE_DCHECK_EQ(method->service(), descriptor());
  switch (method->index()) {
    case 0:
      return ::mobile::GetMobileAPNRequest::default_instance();
    default:
      GOOGLE_LOG(FATAL) << "Bad method index; this should never happen.";
      return *::PROTOBUF_NAMESPACE_ID::MessageFactory::generated_factory()
                  ->GetPrototype(method->input_type());
  }
}

const ::PROTOBUF_NAMESPACE_ID::Message&
GetMobileAPNService::GetResponsePrototype(
    const ::PROTOBUF_NAMESPACE_ID::MethodDescriptor* method) const {
  GOOGLE_DCHECK_EQ(method->service(), descriptor());
  switch (method->index()) {
    case 0:
      return ::mobile::GetMobileAPNResponse::default_instance();
    default:
      GOOGLE_LOG(FATAL) << "Bad method index; this should never happen.";
      return *::PROTOBUF_NAMESPACE_ID::MessageFactory::generated_factory()
                  ->GetPrototype(method->output_type());
  }
}

GetMobileAPNService_Stub::GetMobileAPNService_Stub(
    ::PROTOBUF_NAMESPACE_ID::RpcChannel* channel)
    : channel_(channel), owns_channel_(false) {}
GetMobileAPNService_Stub::GetMobileAPNService_Stub(
    ::PROTOBUF_NAMESPACE_ID::RpcChannel* channel,
    ::PROTOBUF_NAMESPACE_ID::Service::ChannelOwnership ownership)
    : channel_(channel),
      owns_channel_(ownership ==
                    ::PROTOBUF_NAMESPACE_ID::Service::STUB_OWNS_CHANNEL) {}
GetMobileAPNService_Stub::~GetMobileAPNService_Stub() {
  if (owns_channel_) delete channel_;
}

void GetMobileAPNService_Stub::GetMobileAPN(
    ::PROTOBUF_NAMESPACE_ID::RpcController* controller,
    const ::mobile::GetMobileAPNRequest* request,
    ::mobile::GetMobileAPNResponse* response,
    ::google::protobuf::Closure* done) {
  channel_->CallMethod(descriptor()->method(0), controller, request, response,
                       done);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace mobile
PROTOBUF_NAMESPACE_OPEN
template <>
PROTOBUF_NOINLINE::mobile::GetMobileAPNRequest*
Arena::CreateMaybeMessage<::mobile::GetMobileAPNRequest>(Arena* arena) {
  return Arena::CreateMessageInternal<::mobile::GetMobileAPNRequest>(arena);
}
template <>
PROTOBUF_NOINLINE::mobile::GetMobileAPNResponse*
Arena::CreateMaybeMessage<::mobile::GetMobileAPNResponse>(Arena* arena) {
  return Arena::CreateMessageInternal<::mobile::GetMobileAPNResponse>(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
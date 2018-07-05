// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: rpc_meta.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "rpc_meta.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace myrpc {
class RpcMetaDefaultTypeInternal {
public:
 ::google::protobuf::internal::ExplicitlyConstructed<RpcMeta>
     _instance;
} _RpcMeta_default_instance_;

namespace protobuf_rpc_5fmeta_2eproto {


namespace {

::google::protobuf::Metadata file_level_metadata[1];

}  // namespace

PROTOBUF_CONSTEXPR_VAR ::google::protobuf::internal::ParseTableField
    const TableStruct::entries[] GOOGLE_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  {0, 0, 0, ::google::protobuf::internal::kInvalidMask, 0, 0},
};

PROTOBUF_CONSTEXPR_VAR ::google::protobuf::internal::AuxillaryParseTableField
    const TableStruct::aux[] GOOGLE_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  ::google::protobuf::internal::AuxillaryParseTableField(),
};
PROTOBUF_CONSTEXPR_VAR ::google::protobuf::internal::ParseTable const
    TableStruct::schema[] GOOGLE_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  { NULL, NULL, 0, -1, -1, -1, -1, NULL, false },
};

const ::google::protobuf::uint32 TableStruct::offsets[] GOOGLE_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RpcMeta, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RpcMeta, service_name_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RpcMeta, method_name_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RpcMeta, data_size_),
};
static const ::google::protobuf::internal::MigrationSchema schemas[] GOOGLE_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(RpcMeta)},
};

static ::google::protobuf::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::google::protobuf::Message*>(&_RpcMeta_default_instance_),
};

namespace {

void protobuf_AssignDescriptors() {
  AddDescriptors();
  ::google::protobuf::MessageFactory* factory = NULL;
  AssignDescriptors(
      "rpc_meta.proto", schemas, file_default_instances, TableStruct::offsets, factory,
      file_level_metadata, NULL, NULL);
}

void protobuf_AssignDescriptorsOnce() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &protobuf_AssignDescriptors);
}

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::internal::RegisterAllTypes(file_level_metadata, 1);
}

}  // namespace
void TableStruct::InitDefaultsImpl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::internal::InitProtobufDefaults();
  _RpcMeta_default_instance_._instance.DefaultConstruct();
  ::google::protobuf::internal::OnShutdownDestroyMessage(
      &_RpcMeta_default_instance_);}

void InitDefaults() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &TableStruct::InitDefaultsImpl);
}
namespace {
void AddDescriptorsImpl() {
  InitDefaults();
  static const char descriptor[] GOOGLE_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
      "\n\016rpc_meta.proto\022\005myrpc\"G\n\007RpcMeta\022\024\n\014se"
      "rvice_name\030\001 \001(\t\022\023\n\013method_name\030\002 \001(\t\022\021\n"
      "\tdata_size\030\003 \001(\005b\006proto3"
  };
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
      descriptor, 104);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "rpc_meta.proto", &protobuf_RegisterTypes);
}
} // anonymous namespace

void AddDescriptors() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &AddDescriptorsImpl);
}
// Force AddDescriptors() to be called at dynamic initialization time.
struct StaticDescriptorInitializer {
  StaticDescriptorInitializer() {
    AddDescriptors();
  }
} static_descriptor_initializer;

}  // namespace protobuf_rpc_5fmeta_2eproto


// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int RpcMeta::kServiceNameFieldNumber;
const int RpcMeta::kMethodNameFieldNumber;
const int RpcMeta::kDataSizeFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

RpcMeta::RpcMeta()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  if (GOOGLE_PREDICT_TRUE(this != internal_default_instance())) {
    protobuf_rpc_5fmeta_2eproto::InitDefaults();
  }
  SharedCtor();
  // @@protoc_insertion_point(constructor:myrpc.RpcMeta)
}
RpcMeta::RpcMeta(const RpcMeta& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL),
      _cached_size_(0) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  service_name_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (from.service_name().size() > 0) {
    service_name_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.service_name_);
  }
  method_name_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (from.method_name().size() > 0) {
    method_name_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.method_name_);
  }
  data_size_ = from.data_size_;
  // @@protoc_insertion_point(copy_constructor:myrpc.RpcMeta)
}

void RpcMeta::SharedCtor() {
  service_name_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  method_name_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  data_size_ = 0;
  _cached_size_ = 0;
}

RpcMeta::~RpcMeta() {
  // @@protoc_insertion_point(destructor:myrpc.RpcMeta)
  SharedDtor();
}

void RpcMeta::SharedDtor() {
  service_name_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  method_name_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}

void RpcMeta::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* RpcMeta::descriptor() {
  protobuf_rpc_5fmeta_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_rpc_5fmeta_2eproto::file_level_metadata[kIndexInFileMessages].descriptor;
}

const RpcMeta& RpcMeta::default_instance() {
  protobuf_rpc_5fmeta_2eproto::InitDefaults();
  return *internal_default_instance();
}

RpcMeta* RpcMeta::New(::google::protobuf::Arena* arena) const {
  RpcMeta* n = new RpcMeta;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void RpcMeta::Clear() {
// @@protoc_insertion_point(message_clear_start:myrpc.RpcMeta)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  service_name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  method_name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  data_size_ = 0;
  _internal_metadata_.Clear();
}

bool RpcMeta::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:myrpc.RpcMeta)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // string service_name = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(10u /* 10 & 0xFF */)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_service_name()));
          DO_(::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
            this->service_name().data(), static_cast<int>(this->service_name().length()),
            ::google::protobuf::internal::WireFormatLite::PARSE,
            "myrpc.RpcMeta.service_name"));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // string method_name = 2;
      case 2: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(18u /* 18 & 0xFF */)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_method_name()));
          DO_(::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
            this->method_name().data(), static_cast<int>(this->method_name().length()),
            ::google::protobuf::internal::WireFormatLite::PARSE,
            "myrpc.RpcMeta.method_name"));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // int32 data_size = 3;
      case 3: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(24u /* 24 & 0xFF */)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &data_size_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, _internal_metadata_.mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:myrpc.RpcMeta)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:myrpc.RpcMeta)
  return false;
#undef DO_
}

void RpcMeta::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:myrpc.RpcMeta)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // string service_name = 1;
  if (this->service_name().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->service_name().data(), static_cast<int>(this->service_name().length()),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "myrpc.RpcMeta.service_name");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      1, this->service_name(), output);
  }

  // string method_name = 2;
  if (this->method_name().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->method_name().data(), static_cast<int>(this->method_name().length()),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "myrpc.RpcMeta.method_name");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      2, this->method_name(), output);
  }

  // int32 data_size = 3;
  if (this->data_size() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(3, this->data_size(), output);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), output);
  }
  // @@protoc_insertion_point(serialize_end:myrpc.RpcMeta)
}

::google::protobuf::uint8* RpcMeta::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:myrpc.RpcMeta)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // string service_name = 1;
  if (this->service_name().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->service_name().data(), static_cast<int>(this->service_name().length()),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "myrpc.RpcMeta.service_name");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->service_name(), target);
  }

  // string method_name = 2;
  if (this->method_name().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->method_name().data(), static_cast<int>(this->method_name().length()),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "myrpc.RpcMeta.method_name");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        2, this->method_name(), target);
  }

  // int32 data_size = 3;
  if (this->data_size() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(3, this->data_size(), target);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:myrpc.RpcMeta)
  return target;
}

size_t RpcMeta::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:myrpc.RpcMeta)
  size_t total_size = 0;

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()));
  }
  // string service_name = 1;
  if (this->service_name().size() > 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->service_name());
  }

  // string method_name = 2;
  if (this->method_name().size() > 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->method_name());
  }

  // int32 data_size = 3;
  if (this->data_size() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->data_size());
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = cached_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void RpcMeta::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:myrpc.RpcMeta)
  GOOGLE_DCHECK_NE(&from, this);
  const RpcMeta* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const RpcMeta>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:myrpc.RpcMeta)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:myrpc.RpcMeta)
    MergeFrom(*source);
  }
}

void RpcMeta::MergeFrom(const RpcMeta& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:myrpc.RpcMeta)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.service_name().size() > 0) {

    service_name_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.service_name_);
  }
  if (from.method_name().size() > 0) {

    method_name_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.method_name_);
  }
  if (from.data_size() != 0) {
    set_data_size(from.data_size());
  }
}

void RpcMeta::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:myrpc.RpcMeta)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void RpcMeta::CopyFrom(const RpcMeta& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:myrpc.RpcMeta)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool RpcMeta::IsInitialized() const {
  return true;
}

void RpcMeta::Swap(RpcMeta* other) {
  if (other == this) return;
  InternalSwap(other);
}
void RpcMeta::InternalSwap(RpcMeta* other) {
  using std::swap;
  service_name_.Swap(&other->service_name_);
  method_name_.Swap(&other->method_name_);
  swap(data_size_, other->data_size_);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata RpcMeta::GetMetadata() const {
  protobuf_rpc_5fmeta_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_rpc_5fmeta_2eproto::file_level_metadata[kIndexInFileMessages];
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// RpcMeta

// string service_name = 1;
void RpcMeta::clear_service_name() {
  service_name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
const ::std::string& RpcMeta::service_name() const {
  // @@protoc_insertion_point(field_get:myrpc.RpcMeta.service_name)
  return service_name_.GetNoArena();
}
void RpcMeta::set_service_name(const ::std::string& value) {
  
  service_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:myrpc.RpcMeta.service_name)
}
#if LANG_CXX11
void RpcMeta::set_service_name(::std::string&& value) {
  
  service_name_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:myrpc.RpcMeta.service_name)
}
#endif
void RpcMeta::set_service_name(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  service_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:myrpc.RpcMeta.service_name)
}
void RpcMeta::set_service_name(const char* value, size_t size) {
  
  service_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:myrpc.RpcMeta.service_name)
}
::std::string* RpcMeta::mutable_service_name() {
  
  // @@protoc_insertion_point(field_mutable:myrpc.RpcMeta.service_name)
  return service_name_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
::std::string* RpcMeta::release_service_name() {
  // @@protoc_insertion_point(field_release:myrpc.RpcMeta.service_name)
  
  return service_name_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
void RpcMeta::set_allocated_service_name(::std::string* service_name) {
  if (service_name != NULL) {
    
  } else {
    
  }
  service_name_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), service_name);
  // @@protoc_insertion_point(field_set_allocated:myrpc.RpcMeta.service_name)
}

// string method_name = 2;
void RpcMeta::clear_method_name() {
  method_name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
const ::std::string& RpcMeta::method_name() const {
  // @@protoc_insertion_point(field_get:myrpc.RpcMeta.method_name)
  return method_name_.GetNoArena();
}
void RpcMeta::set_method_name(const ::std::string& value) {
  
  method_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:myrpc.RpcMeta.method_name)
}
#if LANG_CXX11
void RpcMeta::set_method_name(::std::string&& value) {
  
  method_name_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:myrpc.RpcMeta.method_name)
}
#endif
void RpcMeta::set_method_name(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  method_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:myrpc.RpcMeta.method_name)
}
void RpcMeta::set_method_name(const char* value, size_t size) {
  
  method_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:myrpc.RpcMeta.method_name)
}
::std::string* RpcMeta::mutable_method_name() {
  
  // @@protoc_insertion_point(field_mutable:myrpc.RpcMeta.method_name)
  return method_name_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
::std::string* RpcMeta::release_method_name() {
  // @@protoc_insertion_point(field_release:myrpc.RpcMeta.method_name)
  
  return method_name_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
void RpcMeta::set_allocated_method_name(::std::string* method_name) {
  if (method_name != NULL) {
    
  } else {
    
  }
  method_name_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), method_name);
  // @@protoc_insertion_point(field_set_allocated:myrpc.RpcMeta.method_name)
}

// int32 data_size = 3;
void RpcMeta::clear_data_size() {
  data_size_ = 0;
}
::google::protobuf::int32 RpcMeta::data_size() const {
  // @@protoc_insertion_point(field_get:myrpc.RpcMeta.data_size)
  return data_size_;
}
void RpcMeta::set_data_size(::google::protobuf::int32 value) {
  
  data_size_ = value;
  // @@protoc_insertion_point(field_set:myrpc.RpcMeta.data_size)
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace myrpc

// @@protoc_insertion_point(global_scope)

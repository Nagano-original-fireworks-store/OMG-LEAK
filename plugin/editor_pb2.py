# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: editor.proto

import sys
_b=sys.version_info[0]<3 and (lambda x:x) or (lambda x:x.encode('latin1'))
from google.protobuf.internal import enum_type_wrapper
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor.FileDescriptor(
  name='editor.proto',
  package='proto',
  syntax='proto3',
  serialized_pb=_b('\n\x0c\x65\x64itor.proto\x12\x05proto\"a\n\x07MapInfo\x12\x0c\n\x04minx\x18\x01 \x01(\x05\x12\x0c\n\x04maxx\x18\x02 \x01(\x05\x12\x0c\n\x04minz\x18\x03 \x01(\x05\x12\x0c\n\x04maxz\x18\x04 \x01(\x05\x12\x1e\n\x05\x63\x65lls\x18\x05 \x03(\x0b\x32\x0f.proto.CellInfo\"@\n\x08\x43\x65llInfo\x12)\n\x04type\x18\x01 \x01(\x0e\x32\x1b.proto.SceneSurfaceMaterial\x12\t\n\x01y\x18\x02 \x01(\x05*k\n\x14SceneSurfaceMaterial\x12\x0b\n\x07Invalid\x10\x00\x12\t\n\x05Grass\x10\x01\x12\x08\n\x04\x44irt\x10\x02\x12\x08\n\x04Rock\x10\x03\x12\x08\n\x04Snow\x10\x04\x12\t\n\x05Water\x10\x05\x12\x08\n\x04Tile\x10\x06\x12\x08\n\x04Sand\x10\x07\x62\x06proto3')
)

_SCENESURFACEMATERIAL = _descriptor.EnumDescriptor(
  name='SceneSurfaceMaterial',
  full_name='proto.SceneSurfaceMaterial',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='Invalid', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='Grass', index=1, number=1,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='Dirt', index=2, number=2,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='Rock', index=3, number=3,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='Snow', index=4, number=4,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='Water', index=5, number=5,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='Tile', index=6, number=6,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='Sand', index=7, number=7,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=None,
  serialized_start=188,
  serialized_end=295,
)
_sym_db.RegisterEnumDescriptor(_SCENESURFACEMATERIAL)

SceneSurfaceMaterial = enum_type_wrapper.EnumTypeWrapper(_SCENESURFACEMATERIAL)
Invalid = 0
Grass = 1
Dirt = 2
Rock = 3
Snow = 4
Water = 5
Tile = 6
Sand = 7



_MAPINFO = _descriptor.Descriptor(
  name='MapInfo',
  full_name='proto.MapInfo',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='minx', full_name='proto.MapInfo.minx', index=0,
      number=1, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='maxx', full_name='proto.MapInfo.maxx', index=1,
      number=2, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='minz', full_name='proto.MapInfo.minz', index=2,
      number=3, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='maxz', full_name='proto.MapInfo.maxz', index=3,
      number=4, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='cells', full_name='proto.MapInfo.cells', index=4,
      number=5, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=23,
  serialized_end=120,
)


_CELLINFO = _descriptor.Descriptor(
  name='CellInfo',
  full_name='proto.CellInfo',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='type', full_name='proto.CellInfo.type', index=0,
      number=1, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='y', full_name='proto.CellInfo.y', index=1,
      number=2, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=122,
  serialized_end=186,
)

_MAPINFO.fields_by_name['cells'].message_type = _CELLINFO
_CELLINFO.fields_by_name['type'].enum_type = _SCENESURFACEMATERIAL
DESCRIPTOR.message_types_by_name['MapInfo'] = _MAPINFO
DESCRIPTOR.message_types_by_name['CellInfo'] = _CELLINFO
DESCRIPTOR.enum_types_by_name['SceneSurfaceMaterial'] = _SCENESURFACEMATERIAL
_sym_db.RegisterFileDescriptor(DESCRIPTOR)

MapInfo = _reflection.GeneratedProtocolMessageType('MapInfo', (_message.Message,), dict(
  DESCRIPTOR = _MAPINFO,
  __module__ = 'editor_pb2'
  # @@protoc_insertion_point(class_scope:proto.MapInfo)
  ))
_sym_db.RegisterMessage(MapInfo)

CellInfo = _reflection.GeneratedProtocolMessageType('CellInfo', (_message.Message,), dict(
  DESCRIPTOR = _CELLINFO,
  __module__ = 'editor_pb2'
  # @@protoc_insertion_point(class_scope:proto.CellInfo)
  ))
_sym_db.RegisterMessage(CellInfo)


# @@protoc_insertion_point(module_scope)

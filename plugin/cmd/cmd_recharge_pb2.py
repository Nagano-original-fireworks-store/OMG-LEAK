# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: cmd/cmd_recharge.proto

import sys
_b=sys.version_info[0]<3 and (lambda x:x) or (lambda x:x.encode('latin1'))
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


import define_pb2 as define__pb2


DESCRIPTOR = _descriptor.FileDescriptor(
  name='cmd/cmd_recharge.proto',
  package='proto',
  syntax='proto3',
  serialized_pb=_b('\n\x16\x63md/cmd_recharge.proto\x12\x05proto\x1a\x0c\x64\x65\x66ine.proto\"\x85\x01\n\x0bRechargeReq\x12\x12\n\nproduct_id\x18\x01 \x01(\t\"b\n\x05\x43mdId\x12\x08\n\x04NONE\x10\x00\x12\x0b\n\x06\x43MD_ID\x10\x85 \x12\x13\n\x0f\x45NET_CHANNEL_ID\x10\x00\x12\x14\n\x10\x45NET_IS_RELIABLE\x10\x01\x12\x13\n\x0fIS_ALLOW_CLIENT\x10\x01\x1a\x02\x10\x01\"m\n\x0bRechargeRsp\x12\x0f\n\x07retcode\x18\x01 \x01(\x05\"M\n\x05\x43mdId\x12\x08\n\x04NONE\x10\x00\x12\x0b\n\x06\x43MD_ID\x10\x86 \x12\x13\n\x0f\x45NET_CHANNEL_ID\x10\x00\x12\x14\n\x10\x45NET_IS_RELIABLE\x10\x01\x1a\x02\x10\x01\"v\n\x11OrderFinishNotify\x12\x12\n\nproduct_id\x18\x01 \x01(\t\"M\n\x05\x43mdId\x12\x08\n\x04NONE\x10\x00\x12\x0b\n\x06\x43MD_ID\x10\x87 \x12\x13\n\x0f\x45NET_CHANNEL_ID\x10\x00\x12\x14\n\x10\x45NET_IS_RELIABLE\x10\x01\x1a\x02\x10\x01\x62\x06proto3')
  ,
  dependencies=[define__pb2.DESCRIPTOR,])



_RECHARGEREQ_CMDID = _descriptor.EnumDescriptor(
  name='CmdId',
  full_name='proto.RechargeReq.CmdId',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='NONE', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='CMD_ID', index=1, number=4101,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ENET_CHANNEL_ID', index=2, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ENET_IS_RELIABLE', index=3, number=1,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='IS_ALLOW_CLIENT', index=4, number=1,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=_descriptor._ParseOptions(descriptor_pb2.EnumOptions(), _b('\020\001')),
  serialized_start=83,
  serialized_end=181,
)
_sym_db.RegisterEnumDescriptor(_RECHARGEREQ_CMDID)

_RECHARGERSP_CMDID = _descriptor.EnumDescriptor(
  name='CmdId',
  full_name='proto.RechargeRsp.CmdId',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='NONE', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='CMD_ID', index=1, number=4102,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ENET_CHANNEL_ID', index=2, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ENET_IS_RELIABLE', index=3, number=1,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=_descriptor._ParseOptions(descriptor_pb2.EnumOptions(), _b('\020\001')),
  serialized_start=215,
  serialized_end=292,
)
_sym_db.RegisterEnumDescriptor(_RECHARGERSP_CMDID)

_ORDERFINISHNOTIFY_CMDID = _descriptor.EnumDescriptor(
  name='CmdId',
  full_name='proto.OrderFinishNotify.CmdId',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='NONE', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='CMD_ID', index=1, number=4103,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ENET_CHANNEL_ID', index=2, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ENET_IS_RELIABLE', index=3, number=1,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=_descriptor._ParseOptions(descriptor_pb2.EnumOptions(), _b('\020\001')),
  serialized_start=335,
  serialized_end=412,
)
_sym_db.RegisterEnumDescriptor(_ORDERFINISHNOTIFY_CMDID)


_RECHARGEREQ = _descriptor.Descriptor(
  name='RechargeReq',
  full_name='proto.RechargeReq',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='product_id', full_name='proto.RechargeReq.product_id', index=0,
      number=1, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
    _RECHARGEREQ_CMDID,
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=48,
  serialized_end=181,
)


_RECHARGERSP = _descriptor.Descriptor(
  name='RechargeRsp',
  full_name='proto.RechargeRsp',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='retcode', full_name='proto.RechargeRsp.retcode', index=0,
      number=1, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
    _RECHARGERSP_CMDID,
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=183,
  serialized_end=292,
)


_ORDERFINISHNOTIFY = _descriptor.Descriptor(
  name='OrderFinishNotify',
  full_name='proto.OrderFinishNotify',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='product_id', full_name='proto.OrderFinishNotify.product_id', index=0,
      number=1, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
    _ORDERFINISHNOTIFY_CMDID,
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=294,
  serialized_end=412,
)

_RECHARGEREQ_CMDID.containing_type = _RECHARGEREQ
_RECHARGERSP_CMDID.containing_type = _RECHARGERSP
_ORDERFINISHNOTIFY_CMDID.containing_type = _ORDERFINISHNOTIFY
DESCRIPTOR.message_types_by_name['RechargeReq'] = _RECHARGEREQ
DESCRIPTOR.message_types_by_name['RechargeRsp'] = _RECHARGERSP
DESCRIPTOR.message_types_by_name['OrderFinishNotify'] = _ORDERFINISHNOTIFY
_sym_db.RegisterFileDescriptor(DESCRIPTOR)

RechargeReq = _reflection.GeneratedProtocolMessageType('RechargeReq', (_message.Message,), dict(
  DESCRIPTOR = _RECHARGEREQ,
  __module__ = 'cmd.cmd_recharge_pb2'
  # @@protoc_insertion_point(class_scope:proto.RechargeReq)
  ))
_sym_db.RegisterMessage(RechargeReq)

RechargeRsp = _reflection.GeneratedProtocolMessageType('RechargeRsp', (_message.Message,), dict(
  DESCRIPTOR = _RECHARGERSP,
  __module__ = 'cmd.cmd_recharge_pb2'
  # @@protoc_insertion_point(class_scope:proto.RechargeRsp)
  ))
_sym_db.RegisterMessage(RechargeRsp)

OrderFinishNotify = _reflection.GeneratedProtocolMessageType('OrderFinishNotify', (_message.Message,), dict(
  DESCRIPTOR = _ORDERFINISHNOTIFY,
  __module__ = 'cmd.cmd_recharge_pb2'
  # @@protoc_insertion_point(class_scope:proto.OrderFinishNotify)
  ))
_sym_db.RegisterMessage(OrderFinishNotify)


_RECHARGEREQ_CMDID.has_options = True
_RECHARGEREQ_CMDID._options = _descriptor._ParseOptions(descriptor_pb2.EnumOptions(), _b('\020\001'))
_RECHARGERSP_CMDID.has_options = True
_RECHARGERSP_CMDID._options = _descriptor._ParseOptions(descriptor_pb2.EnumOptions(), _b('\020\001'))
_ORDERFINISHNOTIFY_CMDID.has_options = True
_ORDERFINISHNOTIFY_CMDID._options = _descriptor._ParseOptions(descriptor_pb2.EnumOptions(), _b('\020\001'))
# @@protoc_insertion_point(module_scope)
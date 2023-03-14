# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: cmd/cmd_shopmall.proto

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
  name='cmd/cmd_shopmall.proto',
  package='proto',
  syntax='proto3',
  serialized_pb=_b('\n\x16\x63md/cmd_shopmall.proto\x12\x05proto\x1a\x0c\x64\x65\x66ine.proto\"x\n\x12GetShopmallDataReq\"b\n\x05\x43mdId\x12\x08\n\x04NONE\x10\x00\x12\x0b\n\x06\x43MD_ID\x10\xb7 \x12\x13\n\x0f\x45NET_CHANNEL_ID\x10\x00\x12\x14\n\x10\x45NET_IS_RELIABLE\x10\x01\x12\x13\n\x0fIS_ALLOW_CLIENT\x10\x01\x1a\x02\x10\x01\"\x8c\x01\n\x12GetShopmallDataRsp\x12\x0f\n\x07retcode\x18\x01 \x01(\x05\x12\x16\n\x0eshop_type_list\x18\x02 \x03(\r\"M\n\x05\x43mdId\x12\x08\n\x04NONE\x10\x00\x12\x0b\n\x06\x43MD_ID\x10\xb8 \x12\x13\n\x0f\x45NET_CHANNEL_ID\x10\x00\x12\x14\n\x10\x45NET_IS_RELIABLE\x10\x01\x1a\x02\x10\x01\"\x13\n\x11ShopmallGoodsData\"X\n\x10ShopmallShopData\x12\x11\n\tshop_type\x18\x01 \x01(\r\x12\x31\n\x0fgoods_data_list\x18\x02 \x03(\x0b\x32\x18.proto.ShopmallGoodsData\"\x8f\x01\n\x16GetShopmallShopDataReq\x12\x11\n\tshop_type\x18\x01 \x01(\r\"b\n\x05\x43mdId\x12\x08\n\x04NONE\x10\x00\x12\x0b\n\x06\x43MD_ID\x10\xb9 \x12\x13\n\x0f\x45NET_CHANNEL_ID\x10\x00\x12\x14\n\x10\x45NET_IS_RELIABLE\x10\x01\x12\x13\n\x0fIS_ALLOW_CLIENT\x10\x01\x1a\x02\x10\x01\"\xa4\x01\n\x16GetShopmallShopDataRsp\x12\x0f\n\x07retcode\x18\x01 \x01(\x05\x12*\n\tshop_data\x18\x02 \x01(\x0b\x32\x17.proto.ShopmallShopData\"M\n\x05\x43mdId\x12\x08\n\x04NONE\x10\x00\x12\x0b\n\x06\x43MD_ID\x10\xba \x12\x13\n\x0f\x45NET_CHANNEL_ID\x10\x00\x12\x14\n\x10\x45NET_IS_RELIABLE\x10\x01\x1a\x02\x10\x01\"\x8c\x01\n\x13\x42uyShopmallGoodsReq\x12\x11\n\tshop_type\x18\x01 \x01(\r\"b\n\x05\x43mdId\x12\x08\n\x04NONE\x10\x00\x12\x0b\n\x06\x43MD_ID\x10\xbb \x12\x13\n\x0f\x45NET_CHANNEL_ID\x10\x00\x12\x14\n\x10\x45NET_IS_RELIABLE\x10\x01\x12\x13\n\x0fIS_ALLOW_CLIENT\x10\x01\x1a\x02\x10\x01\"u\n\x13\x42uyShopmallGoodsRsp\x12\x0f\n\x07retcode\x18\x01 \x01(\x05\"M\n\x05\x43mdId\x12\x08\n\x04NONE\x10\x00\x12\x0b\n\x06\x43MD_ID\x10\xbc \x12\x13\n\x0f\x45NET_CHANNEL_ID\x10\x00\x12\x14\n\x10\x45NET_IS_RELIABLE\x10\x01\x1a\x02\x10\x01\x62\x06proto3')
  ,
  dependencies=[define__pb2.DESCRIPTOR,])



_GETSHOPMALLDATAREQ_CMDID = _descriptor.EnumDescriptor(
  name='CmdId',
  full_name='proto.GetShopmallDataReq.CmdId',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='NONE', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='CMD_ID', index=1, number=4151,
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
  serialized_start=69,
  serialized_end=167,
)
_sym_db.RegisterEnumDescriptor(_GETSHOPMALLDATAREQ_CMDID)

_GETSHOPMALLDATARSP_CMDID = _descriptor.EnumDescriptor(
  name='CmdId',
  full_name='proto.GetShopmallDataRsp.CmdId',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='NONE', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='CMD_ID', index=1, number=4152,
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
  serialized_start=233,
  serialized_end=310,
)
_sym_db.RegisterEnumDescriptor(_GETSHOPMALLDATARSP_CMDID)

_GETSHOPMALLSHOPDATAREQ_CMDID = _descriptor.EnumDescriptor(
  name='CmdId',
  full_name='proto.GetShopmallShopDataReq.CmdId',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='NONE', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='CMD_ID', index=1, number=4153,
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
  serialized_start=469,
  serialized_end=567,
)
_sym_db.RegisterEnumDescriptor(_GETSHOPMALLSHOPDATAREQ_CMDID)

_GETSHOPMALLSHOPDATARSP_CMDID = _descriptor.EnumDescriptor(
  name='CmdId',
  full_name='proto.GetShopmallShopDataRsp.CmdId',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='NONE', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='CMD_ID', index=1, number=4154,
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
  serialized_start=657,
  serialized_end=734,
)
_sym_db.RegisterEnumDescriptor(_GETSHOPMALLSHOPDATARSP_CMDID)

_BUYSHOPMALLGOODSREQ_CMDID = _descriptor.EnumDescriptor(
  name='CmdId',
  full_name='proto.BuyShopmallGoodsReq.CmdId',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='NONE', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='CMD_ID', index=1, number=4155,
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
  serialized_start=779,
  serialized_end=877,
)
_sym_db.RegisterEnumDescriptor(_BUYSHOPMALLGOODSREQ_CMDID)

_BUYSHOPMALLGOODSRSP_CMDID = _descriptor.EnumDescriptor(
  name='CmdId',
  full_name='proto.BuyShopmallGoodsRsp.CmdId',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='NONE', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='CMD_ID', index=1, number=4156,
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
  serialized_start=919,
  serialized_end=996,
)
_sym_db.RegisterEnumDescriptor(_BUYSHOPMALLGOODSRSP_CMDID)


_GETSHOPMALLDATAREQ = _descriptor.Descriptor(
  name='GetShopmallDataReq',
  full_name='proto.GetShopmallDataReq',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
    _GETSHOPMALLDATAREQ_CMDID,
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=47,
  serialized_end=167,
)


_GETSHOPMALLDATARSP = _descriptor.Descriptor(
  name='GetShopmallDataRsp',
  full_name='proto.GetShopmallDataRsp',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='retcode', full_name='proto.GetShopmallDataRsp.retcode', index=0,
      number=1, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='shop_type_list', full_name='proto.GetShopmallDataRsp.shop_type_list', index=1,
      number=2, type=13, cpp_type=3, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
    _GETSHOPMALLDATARSP_CMDID,
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=170,
  serialized_end=310,
)


_SHOPMALLGOODSDATA = _descriptor.Descriptor(
  name='ShopmallGoodsData',
  full_name='proto.ShopmallGoodsData',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
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
  serialized_start=312,
  serialized_end=331,
)


_SHOPMALLSHOPDATA = _descriptor.Descriptor(
  name='ShopmallShopData',
  full_name='proto.ShopmallShopData',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='shop_type', full_name='proto.ShopmallShopData.shop_type', index=0,
      number=1, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='goods_data_list', full_name='proto.ShopmallShopData.goods_data_list', index=1,
      number=2, type=11, cpp_type=10, label=3,
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
  serialized_start=333,
  serialized_end=421,
)


_GETSHOPMALLSHOPDATAREQ = _descriptor.Descriptor(
  name='GetShopmallShopDataReq',
  full_name='proto.GetShopmallShopDataReq',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='shop_type', full_name='proto.GetShopmallShopDataReq.shop_type', index=0,
      number=1, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
    _GETSHOPMALLSHOPDATAREQ_CMDID,
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=424,
  serialized_end=567,
)


_GETSHOPMALLSHOPDATARSP = _descriptor.Descriptor(
  name='GetShopmallShopDataRsp',
  full_name='proto.GetShopmallShopDataRsp',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='retcode', full_name='proto.GetShopmallShopDataRsp.retcode', index=0,
      number=1, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='shop_data', full_name='proto.GetShopmallShopDataRsp.shop_data', index=1,
      number=2, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
    _GETSHOPMALLSHOPDATARSP_CMDID,
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=570,
  serialized_end=734,
)


_BUYSHOPMALLGOODSREQ = _descriptor.Descriptor(
  name='BuyShopmallGoodsReq',
  full_name='proto.BuyShopmallGoodsReq',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='shop_type', full_name='proto.BuyShopmallGoodsReq.shop_type', index=0,
      number=1, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
    _BUYSHOPMALLGOODSREQ_CMDID,
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=737,
  serialized_end=877,
)


_BUYSHOPMALLGOODSRSP = _descriptor.Descriptor(
  name='BuyShopmallGoodsRsp',
  full_name='proto.BuyShopmallGoodsRsp',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='retcode', full_name='proto.BuyShopmallGoodsRsp.retcode', index=0,
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
    _BUYSHOPMALLGOODSRSP_CMDID,
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=879,
  serialized_end=996,
)

_GETSHOPMALLDATAREQ_CMDID.containing_type = _GETSHOPMALLDATAREQ
_GETSHOPMALLDATARSP_CMDID.containing_type = _GETSHOPMALLDATARSP
_SHOPMALLSHOPDATA.fields_by_name['goods_data_list'].message_type = _SHOPMALLGOODSDATA
_GETSHOPMALLSHOPDATAREQ_CMDID.containing_type = _GETSHOPMALLSHOPDATAREQ
_GETSHOPMALLSHOPDATARSP.fields_by_name['shop_data'].message_type = _SHOPMALLSHOPDATA
_GETSHOPMALLSHOPDATARSP_CMDID.containing_type = _GETSHOPMALLSHOPDATARSP
_BUYSHOPMALLGOODSREQ_CMDID.containing_type = _BUYSHOPMALLGOODSREQ
_BUYSHOPMALLGOODSRSP_CMDID.containing_type = _BUYSHOPMALLGOODSRSP
DESCRIPTOR.message_types_by_name['GetShopmallDataReq'] = _GETSHOPMALLDATAREQ
DESCRIPTOR.message_types_by_name['GetShopmallDataRsp'] = _GETSHOPMALLDATARSP
DESCRIPTOR.message_types_by_name['ShopmallGoodsData'] = _SHOPMALLGOODSDATA
DESCRIPTOR.message_types_by_name['ShopmallShopData'] = _SHOPMALLSHOPDATA
DESCRIPTOR.message_types_by_name['GetShopmallShopDataReq'] = _GETSHOPMALLSHOPDATAREQ
DESCRIPTOR.message_types_by_name['GetShopmallShopDataRsp'] = _GETSHOPMALLSHOPDATARSP
DESCRIPTOR.message_types_by_name['BuyShopmallGoodsReq'] = _BUYSHOPMALLGOODSREQ
DESCRIPTOR.message_types_by_name['BuyShopmallGoodsRsp'] = _BUYSHOPMALLGOODSRSP
_sym_db.RegisterFileDescriptor(DESCRIPTOR)

GetShopmallDataReq = _reflection.GeneratedProtocolMessageType('GetShopmallDataReq', (_message.Message,), dict(
  DESCRIPTOR = _GETSHOPMALLDATAREQ,
  __module__ = 'cmd.cmd_shopmall_pb2'
  # @@protoc_insertion_point(class_scope:proto.GetShopmallDataReq)
  ))
_sym_db.RegisterMessage(GetShopmallDataReq)

GetShopmallDataRsp = _reflection.GeneratedProtocolMessageType('GetShopmallDataRsp', (_message.Message,), dict(
  DESCRIPTOR = _GETSHOPMALLDATARSP,
  __module__ = 'cmd.cmd_shopmall_pb2'
  # @@protoc_insertion_point(class_scope:proto.GetShopmallDataRsp)
  ))
_sym_db.RegisterMessage(GetShopmallDataRsp)

ShopmallGoodsData = _reflection.GeneratedProtocolMessageType('ShopmallGoodsData', (_message.Message,), dict(
  DESCRIPTOR = _SHOPMALLGOODSDATA,
  __module__ = 'cmd.cmd_shopmall_pb2'
  # @@protoc_insertion_point(class_scope:proto.ShopmallGoodsData)
  ))
_sym_db.RegisterMessage(ShopmallGoodsData)

ShopmallShopData = _reflection.GeneratedProtocolMessageType('ShopmallShopData', (_message.Message,), dict(
  DESCRIPTOR = _SHOPMALLSHOPDATA,
  __module__ = 'cmd.cmd_shopmall_pb2'
  # @@protoc_insertion_point(class_scope:proto.ShopmallShopData)
  ))
_sym_db.RegisterMessage(ShopmallShopData)

GetShopmallShopDataReq = _reflection.GeneratedProtocolMessageType('GetShopmallShopDataReq', (_message.Message,), dict(
  DESCRIPTOR = _GETSHOPMALLSHOPDATAREQ,
  __module__ = 'cmd.cmd_shopmall_pb2'
  # @@protoc_insertion_point(class_scope:proto.GetShopmallShopDataReq)
  ))
_sym_db.RegisterMessage(GetShopmallShopDataReq)

GetShopmallShopDataRsp = _reflection.GeneratedProtocolMessageType('GetShopmallShopDataRsp', (_message.Message,), dict(
  DESCRIPTOR = _GETSHOPMALLSHOPDATARSP,
  __module__ = 'cmd.cmd_shopmall_pb2'
  # @@protoc_insertion_point(class_scope:proto.GetShopmallShopDataRsp)
  ))
_sym_db.RegisterMessage(GetShopmallShopDataRsp)

BuyShopmallGoodsReq = _reflection.GeneratedProtocolMessageType('BuyShopmallGoodsReq', (_message.Message,), dict(
  DESCRIPTOR = _BUYSHOPMALLGOODSREQ,
  __module__ = 'cmd.cmd_shopmall_pb2'
  # @@protoc_insertion_point(class_scope:proto.BuyShopmallGoodsReq)
  ))
_sym_db.RegisterMessage(BuyShopmallGoodsReq)

BuyShopmallGoodsRsp = _reflection.GeneratedProtocolMessageType('BuyShopmallGoodsRsp', (_message.Message,), dict(
  DESCRIPTOR = _BUYSHOPMALLGOODSRSP,
  __module__ = 'cmd.cmd_shopmall_pb2'
  # @@protoc_insertion_point(class_scope:proto.BuyShopmallGoodsRsp)
  ))
_sym_db.RegisterMessage(BuyShopmallGoodsRsp)


_GETSHOPMALLDATAREQ_CMDID.has_options = True
_GETSHOPMALLDATAREQ_CMDID._options = _descriptor._ParseOptions(descriptor_pb2.EnumOptions(), _b('\020\001'))
_GETSHOPMALLDATARSP_CMDID.has_options = True
_GETSHOPMALLDATARSP_CMDID._options = _descriptor._ParseOptions(descriptor_pb2.EnumOptions(), _b('\020\001'))
_GETSHOPMALLSHOPDATAREQ_CMDID.has_options = True
_GETSHOPMALLSHOPDATAREQ_CMDID._options = _descriptor._ParseOptions(descriptor_pb2.EnumOptions(), _b('\020\001'))
_GETSHOPMALLSHOPDATARSP_CMDID.has_options = True
_GETSHOPMALLSHOPDATARSP_CMDID._options = _descriptor._ParseOptions(descriptor_pb2.EnumOptions(), _b('\020\001'))
_BUYSHOPMALLGOODSREQ_CMDID.has_options = True
_BUYSHOPMALLGOODSREQ_CMDID._options = _descriptor._ParseOptions(descriptor_pb2.EnumOptions(), _b('\020\001'))
_BUYSHOPMALLGOODSRSP_CMDID.has_options = True
_BUYSHOPMALLGOODSRSP_CMDID._options = _descriptor._ParseOptions(descriptor_pb2.EnumOptions(), _b('\020\001'))
# @@protoc_insertion_point(module_scope)

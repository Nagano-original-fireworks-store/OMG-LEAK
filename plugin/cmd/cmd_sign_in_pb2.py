# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: cmd/cmd_sign_in.proto

import sys
_b=sys.version_info[0]<3 and (lambda x:x) or (lambda x:x.encode('latin1'))
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor.FileDescriptor(
  name='cmd/cmd_sign_in.proto',
  package='proto',
  syntax='proto3',
  serialized_pb=_b('\n\x15\x63md/cmd_sign_in.proto\x12\x05proto\"\xc0\x01\n\nSignInInfo\x12\x13\n\x0bschedule_id\x18\x01 \x01(\r\x12\x11\n\tconfig_id\x18\x02 \x01(\r\x12\x12\n\nbegin_time\x18\x03 \x01(\r\x12\x10\n\x08\x65nd_time\x18\x04 \x01(\r\x12\x19\n\x11is_cond_satisfied\x18\n \x01(\x08\x12\x15\n\rsign_in_count\x18\x0b \x01(\r\x12\x19\n\x11last_sign_in_time\x18\x0c \x01(\r\x12\x17\n\x0freward_day_list\x18\r \x03(\r\"\x92\x01\n\x13SignInAllDataNotify\x12,\n\x11sign_in_info_list\x18\x01 \x03(\x0b\x32\x11.proto.SignInInfo\"M\n\x05\x43mdId\x12\x08\n\x04NONE\x10\x00\x12\x0b\n\x06\x43MD_ID\x10\xc5\x13\x12\x13\n\x0f\x45NET_CHANNEL_ID\x10\x00\x12\x14\n\x10\x45NET_IS_RELIABLE\x10\x01\x1a\x02\x10\x01\"\x7f\n\x14SignInInfoOpenNotify\x12\x18\n\x10schedule_id_list\x18\x01 \x03(\r\"M\n\x05\x43mdId\x12\x08\n\x04NONE\x10\x00\x12\x0b\n\x06\x43MD_ID\x10\xc6\x13\x12\x13\n\x0f\x45NET_CHANNEL_ID\x10\x00\x12\x14\n\x10\x45NET_IS_RELIABLE\x10\x01\x1a\x02\x10\x01\"s\n\rSignInInfoReq\"b\n\x05\x43mdId\x12\x08\n\x04NONE\x10\x00\x12\x0b\n\x06\x43MD_ID\x10\xc7\x13\x12\x13\n\x0f\x45NET_CHANNEL_ID\x10\x00\x12\x14\n\x10\x45NET_IS_RELIABLE\x10\x01\x12\x13\n\x0fIS_ALLOW_CLIENT\x10\x01\x1a\x02\x10\x01\"\x9d\x01\n\rSignInInfoRsp\x12\x0f\n\x07retcode\x18\x01 \x01(\x05\x12,\n\x11sign_in_info_list\x18\x02 \x03(\x0b\x32\x11.proto.SignInInfo\"M\n\x05\x43mdId\x12\x08\n\x04NONE\x10\x00\x12\x0b\n\x06\x43MD_ID\x10\xc8\x13\x12\x13\n\x0f\x45NET_CHANNEL_ID\x10\x00\x12\x14\n\x10\x45NET_IS_RELIABLE\x10\x01\x1a\x02\x10\x01\"\xa1\x01\n\x12GetSignInRewardReq\x12\x13\n\x0bschedule_id\x18\x01 \x01(\r\x12\x12\n\nreward_day\x18\x02 \x01(\r\"b\n\x05\x43mdId\x12\x08\n\x04NONE\x10\x00\x12\x0b\n\x06\x43MD_ID\x10\xc9\x13\x12\x13\n\x0f\x45NET_CHANNEL_ID\x10\x00\x12\x14\n\x10\x45NET_IS_RELIABLE\x10\x01\x12\x13\n\x0fIS_ALLOW_CLIENT\x10\x01\x1a\x02\x10\x01\"\x9d\x01\n\x12GetSignInRewardRsp\x12\x0f\n\x07retcode\x18\x01 \x01(\x05\x12\'\n\x0csign_in_info\x18\x02 \x01(\x0b\x32\x11.proto.SignInInfo\"M\n\x05\x43mdId\x12\x08\n\x04NONE\x10\x00\x12\x0b\n\x06\x43MD_ID\x10\xca\x13\x12\x13\n\x0f\x45NET_CHANNEL_ID\x10\x00\x12\x14\n\x10\x45NET_IS_RELIABLE\x10\x01\x1a\x02\x10\x01\"=\n\x11\x42onusActivityInfo\x12\x19\n\x11\x62onus_activity_id\x18\x01 \x01(\r\x12\r\n\x05state\x18\x02 \x01(\r\"\xa7\x01\n\x1a\x42onusActivityAllDataNotify\x12:\n\x18\x62onus_activity_info_list\x18\x01 \x03(\x0b\x32\x18.proto.BonusActivityInfo\"M\n\x05\x43mdId\x12\x08\n\x04NONE\x10\x00\x12\x0b\n\x06\x43MD_ID\x10\xcf\x13\x12\x13\n\x0f\x45NET_CHANNEL_ID\x10\x00\x12\x14\n\x10\x45NET_IS_RELIABLE\x10\x01\x1a\x02\x10\x01\"\xa6\x01\n\x19\x42onusActivityUpdateNotify\x12:\n\x18\x62onus_activity_info_list\x18\x01 \x03(\x0b\x32\x18.proto.BonusActivityInfo\"M\n\x05\x43mdId\x12\x08\n\x04NONE\x10\x00\x12\x0b\n\x06\x43MD_ID\x10\xd0\x13\x12\x13\n\x0f\x45NET_CHANNEL_ID\x10\x00\x12\x14\n\x10\x45NET_IS_RELIABLE\x10\x01\x1a\x02\x10\x01\"z\n\x14\x42onusActivityInfoReq\"b\n\x05\x43mdId\x12\x08\n\x04NONE\x10\x00\x12\x0b\n\x06\x43MD_ID\x10\xd1\x13\x12\x13\n\x0f\x45NET_CHANNEL_ID\x10\x00\x12\x14\n\x10\x45NET_IS_RELIABLE\x10\x01\x12\x13\n\x0fIS_ALLOW_CLIENT\x10\x01\x1a\x02\x10\x01\"\xb2\x01\n\x14\x42onusActivityInfoRsp\x12\x0f\n\x07retcode\x18\x01 \x01(\x05\x12:\n\x18\x62onus_activity_info_list\x18\x02 \x03(\x0b\x32\x18.proto.BonusActivityInfo\"M\n\x05\x43mdId\x12\x08\n\x04NONE\x10\x00\x12\x0b\n\x06\x43MD_ID\x10\xd2\x13\x12\x13\n\x0f\x45NET_CHANNEL_ID\x10\x00\x12\x14\n\x10\x45NET_IS_RELIABLE\x10\x01\x1a\x02\x10\x01\"\x9a\x01\n\x19GetBonusActivityRewardReq\x12\x19\n\x11\x62onus_activity_id\x18\x01 \x01(\r\"b\n\x05\x43mdId\x12\x08\n\x04NONE\x10\x00\x12\x0b\n\x06\x43MD_ID\x10\xd3\x13\x12\x13\n\x0f\x45NET_CHANNEL_ID\x10\x00\x12\x14\n\x10\x45NET_IS_RELIABLE\x10\x01\x12\x13\n\x0fIS_ALLOW_CLIENT\x10\x01\x1a\x02\x10\x01\"\xb7\x01\n\x19GetBonusActivityRewardRsp\x12\x0f\n\x07retcode\x18\x01 \x01(\x05\x12:\n\x18\x62onus_activity_info_list\x18\x02 \x01(\x0b\x32\x18.proto.BonusActivityInfo\"M\n\x05\x43mdId\x12\x08\n\x04NONE\x10\x00\x12\x0b\n\x06\x43MD_ID\x10\xd4\x13\x12\x13\n\x0f\x45NET_CHANNEL_ID\x10\x00\x12\x14\n\x10\x45NET_IS_RELIABLE\x10\x01\x1a\x02\x10\x01\x62\x06proto3')
)



_SIGNINALLDATANOTIFY_CMDID = _descriptor.EnumDescriptor(
  name='CmdId',
  full_name='proto.SignInAllDataNotify.CmdId',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='NONE', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='CMD_ID', index=1, number=2501,
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
  serialized_start=297,
  serialized_end=374,
)
_sym_db.RegisterEnumDescriptor(_SIGNINALLDATANOTIFY_CMDID)

_SIGNININFOOPENNOTIFY_CMDID = _descriptor.EnumDescriptor(
  name='CmdId',
  full_name='proto.SignInInfoOpenNotify.CmdId',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='NONE', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='CMD_ID', index=1, number=2502,
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
  serialized_start=426,
  serialized_end=503,
)
_sym_db.RegisterEnumDescriptor(_SIGNININFOOPENNOTIFY_CMDID)

_SIGNININFOREQ_CMDID = _descriptor.EnumDescriptor(
  name='CmdId',
  full_name='proto.SignInInfoReq.CmdId',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='NONE', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='CMD_ID', index=1, number=2503,
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
  serialized_start=522,
  serialized_end=620,
)
_sym_db.RegisterEnumDescriptor(_SIGNININFOREQ_CMDID)

_SIGNININFORSP_CMDID = _descriptor.EnumDescriptor(
  name='CmdId',
  full_name='proto.SignInInfoRsp.CmdId',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='NONE', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='CMD_ID', index=1, number=2504,
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
  serialized_start=703,
  serialized_end=780,
)
_sym_db.RegisterEnumDescriptor(_SIGNININFORSP_CMDID)

_GETSIGNINREWARDREQ_CMDID = _descriptor.EnumDescriptor(
  name='CmdId',
  full_name='proto.GetSignInRewardReq.CmdId',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='NONE', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='CMD_ID', index=1, number=2505,
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
  serialized_start=846,
  serialized_end=944,
)
_sym_db.RegisterEnumDescriptor(_GETSIGNINREWARDREQ_CMDID)

_GETSIGNINREWARDRSP_CMDID = _descriptor.EnumDescriptor(
  name='CmdId',
  full_name='proto.GetSignInRewardRsp.CmdId',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='NONE', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='CMD_ID', index=1, number=2506,
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
  serialized_start=1027,
  serialized_end=1104,
)
_sym_db.RegisterEnumDescriptor(_GETSIGNINREWARDRSP_CMDID)

_BONUSACTIVITYALLDATANOTIFY_CMDID = _descriptor.EnumDescriptor(
  name='CmdId',
  full_name='proto.BonusActivityAllDataNotify.CmdId',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='NONE', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='CMD_ID', index=1, number=2511,
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
  serialized_start=1260,
  serialized_end=1337,
)
_sym_db.RegisterEnumDescriptor(_BONUSACTIVITYALLDATANOTIFY_CMDID)

_BONUSACTIVITYUPDATENOTIFY_CMDID = _descriptor.EnumDescriptor(
  name='CmdId',
  full_name='proto.BonusActivityUpdateNotify.CmdId',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='NONE', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='CMD_ID', index=1, number=2512,
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
  serialized_start=1429,
  serialized_end=1506,
)
_sym_db.RegisterEnumDescriptor(_BONUSACTIVITYUPDATENOTIFY_CMDID)

_BONUSACTIVITYINFOREQ_CMDID = _descriptor.EnumDescriptor(
  name='CmdId',
  full_name='proto.BonusActivityInfoReq.CmdId',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='NONE', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='CMD_ID', index=1, number=2513,
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
  serialized_start=1532,
  serialized_end=1630,
)
_sym_db.RegisterEnumDescriptor(_BONUSACTIVITYINFOREQ_CMDID)

_BONUSACTIVITYINFORSP_CMDID = _descriptor.EnumDescriptor(
  name='CmdId',
  full_name='proto.BonusActivityInfoRsp.CmdId',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='NONE', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='CMD_ID', index=1, number=2514,
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
  serialized_start=1734,
  serialized_end=1811,
)
_sym_db.RegisterEnumDescriptor(_BONUSACTIVITYINFORSP_CMDID)

_GETBONUSACTIVITYREWARDREQ_CMDID = _descriptor.EnumDescriptor(
  name='CmdId',
  full_name='proto.GetBonusActivityRewardReq.CmdId',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='NONE', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='CMD_ID', index=1, number=2515,
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
  serialized_start=1870,
  serialized_end=1968,
)
_sym_db.RegisterEnumDescriptor(_GETBONUSACTIVITYREWARDREQ_CMDID)

_GETBONUSACTIVITYREWARDRSP_CMDID = _descriptor.EnumDescriptor(
  name='CmdId',
  full_name='proto.GetBonusActivityRewardRsp.CmdId',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='NONE', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='CMD_ID', index=1, number=2516,
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
  serialized_start=2077,
  serialized_end=2154,
)
_sym_db.RegisterEnumDescriptor(_GETBONUSACTIVITYREWARDRSP_CMDID)


_SIGNININFO = _descriptor.Descriptor(
  name='SignInInfo',
  full_name='proto.SignInInfo',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='schedule_id', full_name='proto.SignInInfo.schedule_id', index=0,
      number=1, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='config_id', full_name='proto.SignInInfo.config_id', index=1,
      number=2, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='begin_time', full_name='proto.SignInInfo.begin_time', index=2,
      number=3, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='end_time', full_name='proto.SignInInfo.end_time', index=3,
      number=4, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='is_cond_satisfied', full_name='proto.SignInInfo.is_cond_satisfied', index=4,
      number=10, type=8, cpp_type=7, label=1,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='sign_in_count', full_name='proto.SignInInfo.sign_in_count', index=5,
      number=11, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='last_sign_in_time', full_name='proto.SignInInfo.last_sign_in_time', index=6,
      number=12, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='reward_day_list', full_name='proto.SignInInfo.reward_day_list', index=7,
      number=13, type=13, cpp_type=3, label=3,
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
  serialized_start=33,
  serialized_end=225,
)


_SIGNINALLDATANOTIFY = _descriptor.Descriptor(
  name='SignInAllDataNotify',
  full_name='proto.SignInAllDataNotify',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='sign_in_info_list', full_name='proto.SignInAllDataNotify.sign_in_info_list', index=0,
      number=1, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
    _SIGNINALLDATANOTIFY_CMDID,
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=228,
  serialized_end=374,
)


_SIGNININFOOPENNOTIFY = _descriptor.Descriptor(
  name='SignInInfoOpenNotify',
  full_name='proto.SignInInfoOpenNotify',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='schedule_id_list', full_name='proto.SignInInfoOpenNotify.schedule_id_list', index=0,
      number=1, type=13, cpp_type=3, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
    _SIGNININFOOPENNOTIFY_CMDID,
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=376,
  serialized_end=503,
)


_SIGNININFOREQ = _descriptor.Descriptor(
  name='SignInInfoReq',
  full_name='proto.SignInInfoReq',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
    _SIGNININFOREQ_CMDID,
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=505,
  serialized_end=620,
)


_SIGNININFORSP = _descriptor.Descriptor(
  name='SignInInfoRsp',
  full_name='proto.SignInInfoRsp',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='retcode', full_name='proto.SignInInfoRsp.retcode', index=0,
      number=1, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='sign_in_info_list', full_name='proto.SignInInfoRsp.sign_in_info_list', index=1,
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
    _SIGNININFORSP_CMDID,
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=623,
  serialized_end=780,
)


_GETSIGNINREWARDREQ = _descriptor.Descriptor(
  name='GetSignInRewardReq',
  full_name='proto.GetSignInRewardReq',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='schedule_id', full_name='proto.GetSignInRewardReq.schedule_id', index=0,
      number=1, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='reward_day', full_name='proto.GetSignInRewardReq.reward_day', index=1,
      number=2, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
    _GETSIGNINREWARDREQ_CMDID,
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=783,
  serialized_end=944,
)


_GETSIGNINREWARDRSP = _descriptor.Descriptor(
  name='GetSignInRewardRsp',
  full_name='proto.GetSignInRewardRsp',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='retcode', full_name='proto.GetSignInRewardRsp.retcode', index=0,
      number=1, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='sign_in_info', full_name='proto.GetSignInRewardRsp.sign_in_info', index=1,
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
    _GETSIGNINREWARDRSP_CMDID,
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=947,
  serialized_end=1104,
)


_BONUSACTIVITYINFO = _descriptor.Descriptor(
  name='BonusActivityInfo',
  full_name='proto.BonusActivityInfo',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='bonus_activity_id', full_name='proto.BonusActivityInfo.bonus_activity_id', index=0,
      number=1, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='state', full_name='proto.BonusActivityInfo.state', index=1,
      number=2, type=13, cpp_type=3, label=1,
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
  serialized_start=1106,
  serialized_end=1167,
)


_BONUSACTIVITYALLDATANOTIFY = _descriptor.Descriptor(
  name='BonusActivityAllDataNotify',
  full_name='proto.BonusActivityAllDataNotify',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='bonus_activity_info_list', full_name='proto.BonusActivityAllDataNotify.bonus_activity_info_list', index=0,
      number=1, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
    _BONUSACTIVITYALLDATANOTIFY_CMDID,
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=1170,
  serialized_end=1337,
)


_BONUSACTIVITYUPDATENOTIFY = _descriptor.Descriptor(
  name='BonusActivityUpdateNotify',
  full_name='proto.BonusActivityUpdateNotify',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='bonus_activity_info_list', full_name='proto.BonusActivityUpdateNotify.bonus_activity_info_list', index=0,
      number=1, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
    _BONUSACTIVITYUPDATENOTIFY_CMDID,
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=1340,
  serialized_end=1506,
)


_BONUSACTIVITYINFOREQ = _descriptor.Descriptor(
  name='BonusActivityInfoReq',
  full_name='proto.BonusActivityInfoReq',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
    _BONUSACTIVITYINFOREQ_CMDID,
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=1508,
  serialized_end=1630,
)


_BONUSACTIVITYINFORSP = _descriptor.Descriptor(
  name='BonusActivityInfoRsp',
  full_name='proto.BonusActivityInfoRsp',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='retcode', full_name='proto.BonusActivityInfoRsp.retcode', index=0,
      number=1, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='bonus_activity_info_list', full_name='proto.BonusActivityInfoRsp.bonus_activity_info_list', index=1,
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
    _BONUSACTIVITYINFORSP_CMDID,
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=1633,
  serialized_end=1811,
)


_GETBONUSACTIVITYREWARDREQ = _descriptor.Descriptor(
  name='GetBonusActivityRewardReq',
  full_name='proto.GetBonusActivityRewardReq',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='bonus_activity_id', full_name='proto.GetBonusActivityRewardReq.bonus_activity_id', index=0,
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
    _GETBONUSACTIVITYREWARDREQ_CMDID,
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=1814,
  serialized_end=1968,
)


_GETBONUSACTIVITYREWARDRSP = _descriptor.Descriptor(
  name='GetBonusActivityRewardRsp',
  full_name='proto.GetBonusActivityRewardRsp',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='retcode', full_name='proto.GetBonusActivityRewardRsp.retcode', index=0,
      number=1, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='bonus_activity_info_list', full_name='proto.GetBonusActivityRewardRsp.bonus_activity_info_list', index=1,
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
    _GETBONUSACTIVITYREWARDRSP_CMDID,
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=1971,
  serialized_end=2154,
)

_SIGNINALLDATANOTIFY.fields_by_name['sign_in_info_list'].message_type = _SIGNININFO
_SIGNINALLDATANOTIFY_CMDID.containing_type = _SIGNINALLDATANOTIFY
_SIGNININFOOPENNOTIFY_CMDID.containing_type = _SIGNININFOOPENNOTIFY
_SIGNININFOREQ_CMDID.containing_type = _SIGNININFOREQ
_SIGNININFORSP.fields_by_name['sign_in_info_list'].message_type = _SIGNININFO
_SIGNININFORSP_CMDID.containing_type = _SIGNININFORSP
_GETSIGNINREWARDREQ_CMDID.containing_type = _GETSIGNINREWARDREQ
_GETSIGNINREWARDRSP.fields_by_name['sign_in_info'].message_type = _SIGNININFO
_GETSIGNINREWARDRSP_CMDID.containing_type = _GETSIGNINREWARDRSP
_BONUSACTIVITYALLDATANOTIFY.fields_by_name['bonus_activity_info_list'].message_type = _BONUSACTIVITYINFO
_BONUSACTIVITYALLDATANOTIFY_CMDID.containing_type = _BONUSACTIVITYALLDATANOTIFY
_BONUSACTIVITYUPDATENOTIFY.fields_by_name['bonus_activity_info_list'].message_type = _BONUSACTIVITYINFO
_BONUSACTIVITYUPDATENOTIFY_CMDID.containing_type = _BONUSACTIVITYUPDATENOTIFY
_BONUSACTIVITYINFOREQ_CMDID.containing_type = _BONUSACTIVITYINFOREQ
_BONUSACTIVITYINFORSP.fields_by_name['bonus_activity_info_list'].message_type = _BONUSACTIVITYINFO
_BONUSACTIVITYINFORSP_CMDID.containing_type = _BONUSACTIVITYINFORSP
_GETBONUSACTIVITYREWARDREQ_CMDID.containing_type = _GETBONUSACTIVITYREWARDREQ
_GETBONUSACTIVITYREWARDRSP.fields_by_name['bonus_activity_info_list'].message_type = _BONUSACTIVITYINFO
_GETBONUSACTIVITYREWARDRSP_CMDID.containing_type = _GETBONUSACTIVITYREWARDRSP
DESCRIPTOR.message_types_by_name['SignInInfo'] = _SIGNININFO
DESCRIPTOR.message_types_by_name['SignInAllDataNotify'] = _SIGNINALLDATANOTIFY
DESCRIPTOR.message_types_by_name['SignInInfoOpenNotify'] = _SIGNININFOOPENNOTIFY
DESCRIPTOR.message_types_by_name['SignInInfoReq'] = _SIGNININFOREQ
DESCRIPTOR.message_types_by_name['SignInInfoRsp'] = _SIGNININFORSP
DESCRIPTOR.message_types_by_name['GetSignInRewardReq'] = _GETSIGNINREWARDREQ
DESCRIPTOR.message_types_by_name['GetSignInRewardRsp'] = _GETSIGNINREWARDRSP
DESCRIPTOR.message_types_by_name['BonusActivityInfo'] = _BONUSACTIVITYINFO
DESCRIPTOR.message_types_by_name['BonusActivityAllDataNotify'] = _BONUSACTIVITYALLDATANOTIFY
DESCRIPTOR.message_types_by_name['BonusActivityUpdateNotify'] = _BONUSACTIVITYUPDATENOTIFY
DESCRIPTOR.message_types_by_name['BonusActivityInfoReq'] = _BONUSACTIVITYINFOREQ
DESCRIPTOR.message_types_by_name['BonusActivityInfoRsp'] = _BONUSACTIVITYINFORSP
DESCRIPTOR.message_types_by_name['GetBonusActivityRewardReq'] = _GETBONUSACTIVITYREWARDREQ
DESCRIPTOR.message_types_by_name['GetBonusActivityRewardRsp'] = _GETBONUSACTIVITYREWARDRSP
_sym_db.RegisterFileDescriptor(DESCRIPTOR)

SignInInfo = _reflection.GeneratedProtocolMessageType('SignInInfo', (_message.Message,), dict(
  DESCRIPTOR = _SIGNININFO,
  __module__ = 'cmd.cmd_sign_in_pb2'
  # @@protoc_insertion_point(class_scope:proto.SignInInfo)
  ))
_sym_db.RegisterMessage(SignInInfo)

SignInAllDataNotify = _reflection.GeneratedProtocolMessageType('SignInAllDataNotify', (_message.Message,), dict(
  DESCRIPTOR = _SIGNINALLDATANOTIFY,
  __module__ = 'cmd.cmd_sign_in_pb2'
  # @@protoc_insertion_point(class_scope:proto.SignInAllDataNotify)
  ))
_sym_db.RegisterMessage(SignInAllDataNotify)

SignInInfoOpenNotify = _reflection.GeneratedProtocolMessageType('SignInInfoOpenNotify', (_message.Message,), dict(
  DESCRIPTOR = _SIGNININFOOPENNOTIFY,
  __module__ = 'cmd.cmd_sign_in_pb2'
  # @@protoc_insertion_point(class_scope:proto.SignInInfoOpenNotify)
  ))
_sym_db.RegisterMessage(SignInInfoOpenNotify)

SignInInfoReq = _reflection.GeneratedProtocolMessageType('SignInInfoReq', (_message.Message,), dict(
  DESCRIPTOR = _SIGNININFOREQ,
  __module__ = 'cmd.cmd_sign_in_pb2'
  # @@protoc_insertion_point(class_scope:proto.SignInInfoReq)
  ))
_sym_db.RegisterMessage(SignInInfoReq)

SignInInfoRsp = _reflection.GeneratedProtocolMessageType('SignInInfoRsp', (_message.Message,), dict(
  DESCRIPTOR = _SIGNININFORSP,
  __module__ = 'cmd.cmd_sign_in_pb2'
  # @@protoc_insertion_point(class_scope:proto.SignInInfoRsp)
  ))
_sym_db.RegisterMessage(SignInInfoRsp)

GetSignInRewardReq = _reflection.GeneratedProtocolMessageType('GetSignInRewardReq', (_message.Message,), dict(
  DESCRIPTOR = _GETSIGNINREWARDREQ,
  __module__ = 'cmd.cmd_sign_in_pb2'
  # @@protoc_insertion_point(class_scope:proto.GetSignInRewardReq)
  ))
_sym_db.RegisterMessage(GetSignInRewardReq)

GetSignInRewardRsp = _reflection.GeneratedProtocolMessageType('GetSignInRewardRsp', (_message.Message,), dict(
  DESCRIPTOR = _GETSIGNINREWARDRSP,
  __module__ = 'cmd.cmd_sign_in_pb2'
  # @@protoc_insertion_point(class_scope:proto.GetSignInRewardRsp)
  ))
_sym_db.RegisterMessage(GetSignInRewardRsp)

BonusActivityInfo = _reflection.GeneratedProtocolMessageType('BonusActivityInfo', (_message.Message,), dict(
  DESCRIPTOR = _BONUSACTIVITYINFO,
  __module__ = 'cmd.cmd_sign_in_pb2'
  # @@protoc_insertion_point(class_scope:proto.BonusActivityInfo)
  ))
_sym_db.RegisterMessage(BonusActivityInfo)

BonusActivityAllDataNotify = _reflection.GeneratedProtocolMessageType('BonusActivityAllDataNotify', (_message.Message,), dict(
  DESCRIPTOR = _BONUSACTIVITYALLDATANOTIFY,
  __module__ = 'cmd.cmd_sign_in_pb2'
  # @@protoc_insertion_point(class_scope:proto.BonusActivityAllDataNotify)
  ))
_sym_db.RegisterMessage(BonusActivityAllDataNotify)

BonusActivityUpdateNotify = _reflection.GeneratedProtocolMessageType('BonusActivityUpdateNotify', (_message.Message,), dict(
  DESCRIPTOR = _BONUSACTIVITYUPDATENOTIFY,
  __module__ = 'cmd.cmd_sign_in_pb2'
  # @@protoc_insertion_point(class_scope:proto.BonusActivityUpdateNotify)
  ))
_sym_db.RegisterMessage(BonusActivityUpdateNotify)

BonusActivityInfoReq = _reflection.GeneratedProtocolMessageType('BonusActivityInfoReq', (_message.Message,), dict(
  DESCRIPTOR = _BONUSACTIVITYINFOREQ,
  __module__ = 'cmd.cmd_sign_in_pb2'
  # @@protoc_insertion_point(class_scope:proto.BonusActivityInfoReq)
  ))
_sym_db.RegisterMessage(BonusActivityInfoReq)

BonusActivityInfoRsp = _reflection.GeneratedProtocolMessageType('BonusActivityInfoRsp', (_message.Message,), dict(
  DESCRIPTOR = _BONUSACTIVITYINFORSP,
  __module__ = 'cmd.cmd_sign_in_pb2'
  # @@protoc_insertion_point(class_scope:proto.BonusActivityInfoRsp)
  ))
_sym_db.RegisterMessage(BonusActivityInfoRsp)

GetBonusActivityRewardReq = _reflection.GeneratedProtocolMessageType('GetBonusActivityRewardReq', (_message.Message,), dict(
  DESCRIPTOR = _GETBONUSACTIVITYREWARDREQ,
  __module__ = 'cmd.cmd_sign_in_pb2'
  # @@protoc_insertion_point(class_scope:proto.GetBonusActivityRewardReq)
  ))
_sym_db.RegisterMessage(GetBonusActivityRewardReq)

GetBonusActivityRewardRsp = _reflection.GeneratedProtocolMessageType('GetBonusActivityRewardRsp', (_message.Message,), dict(
  DESCRIPTOR = _GETBONUSACTIVITYREWARDRSP,
  __module__ = 'cmd.cmd_sign_in_pb2'
  # @@protoc_insertion_point(class_scope:proto.GetBonusActivityRewardRsp)
  ))
_sym_db.RegisterMessage(GetBonusActivityRewardRsp)


_SIGNINALLDATANOTIFY_CMDID.has_options = True
_SIGNINALLDATANOTIFY_CMDID._options = _descriptor._ParseOptions(descriptor_pb2.EnumOptions(), _b('\020\001'))
_SIGNININFOOPENNOTIFY_CMDID.has_options = True
_SIGNININFOOPENNOTIFY_CMDID._options = _descriptor._ParseOptions(descriptor_pb2.EnumOptions(), _b('\020\001'))
_SIGNININFOREQ_CMDID.has_options = True
_SIGNININFOREQ_CMDID._options = _descriptor._ParseOptions(descriptor_pb2.EnumOptions(), _b('\020\001'))
_SIGNININFORSP_CMDID.has_options = True
_SIGNININFORSP_CMDID._options = _descriptor._ParseOptions(descriptor_pb2.EnumOptions(), _b('\020\001'))
_GETSIGNINREWARDREQ_CMDID.has_options = True
_GETSIGNINREWARDREQ_CMDID._options = _descriptor._ParseOptions(descriptor_pb2.EnumOptions(), _b('\020\001'))
_GETSIGNINREWARDRSP_CMDID.has_options = True
_GETSIGNINREWARDRSP_CMDID._options = _descriptor._ParseOptions(descriptor_pb2.EnumOptions(), _b('\020\001'))
_BONUSACTIVITYALLDATANOTIFY_CMDID.has_options = True
_BONUSACTIVITYALLDATANOTIFY_CMDID._options = _descriptor._ParseOptions(descriptor_pb2.EnumOptions(), _b('\020\001'))
_BONUSACTIVITYUPDATENOTIFY_CMDID.has_options = True
_BONUSACTIVITYUPDATENOTIFY_CMDID._options = _descriptor._ParseOptions(descriptor_pb2.EnumOptions(), _b('\020\001'))
_BONUSACTIVITYINFOREQ_CMDID.has_options = True
_BONUSACTIVITYINFOREQ_CMDID._options = _descriptor._ParseOptions(descriptor_pb2.EnumOptions(), _b('\020\001'))
_BONUSACTIVITYINFORSP_CMDID.has_options = True
_BONUSACTIVITYINFORSP_CMDID._options = _descriptor._ParseOptions(descriptor_pb2.EnumOptions(), _b('\020\001'))
_GETBONUSACTIVITYREWARDREQ_CMDID.has_options = True
_GETBONUSACTIVITYREWARDREQ_CMDID._options = _descriptor._ParseOptions(descriptor_pb2.EnumOptions(), _b('\020\001'))
_GETBONUSACTIVITYREWARDRSP_CMDID.has_options = True
_GETBONUSACTIVITYREWARDRSP_CMDID._options = _descriptor._ParseOptions(descriptor_pb2.EnumOptions(), _b('\020\001'))
# @@protoc_insertion_point(module_scope)

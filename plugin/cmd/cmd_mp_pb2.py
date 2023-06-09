# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: cmd/cmd_mp.proto

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
  name='cmd/cmd_mp.proto',
  package='proto',
  syntax='proto3',
  serialized_pb=_b('\n\x10\x63md/cmd_mp.proto\x12\x05proto\x1a\x0c\x64\x65\x66ine.proto\"\x9b\x01\n\x18PlayerApplyEnterMpNotify\x12\x30\n\x0fsrc_player_info\x18\x01 \x01(\x0b\x32\x17.proto.OnlinePlayerInfo\"M\n\x05\x43mdId\x12\x08\n\x04NONE\x10\x00\x12\x0b\n\x06\x43MD_ID\x10\x89\x0e\x12\x13\n\x0f\x45NET_CHANNEL_ID\x10\x00\x12\x14\n\x10\x45NET_IS_RELIABLE\x10\x01\x1a\x02\x10\x01\"\x8f\x01\n\x15PlayerApplyEnterMpReq\x12\x12\n\ntarget_uid\x18\x01 \x01(\r\"b\n\x05\x43mdId\x12\x08\n\x04NONE\x10\x00\x12\x0b\n\x06\x43MD_ID\x10\x8a\x0e\x12\x13\n\x0f\x45NET_CHANNEL_ID\x10\x00\x12\x14\n\x10\x45NET_IS_RELIABLE\x10\x01\x12\x13\n\x0fIS_ALLOW_CLIENT\x10\x01\x1a\x02\x10\x01\"\x8b\x01\n\x15PlayerApplyEnterMpRsp\x12\x0f\n\x07retcode\x18\x01 \x01(\x05\x12\x12\n\ntarget_uid\x18\x02 \x01(\r\"M\n\x05\x43mdId\x12\x08\n\x04NONE\x10\x00\x12\x0b\n\x06\x43MD_ID\x10\x8b\x0e\x12\x13\n\x0f\x45NET_CHANNEL_ID\x10\x00\x12\x14\n\x10\x45NET_IS_RELIABLE\x10\x01\x1a\x02\x10\x01\"\xf5\x02\n\x1ePlayerApplyEnterMpResultNotify\x12\x12\n\ntarget_uid\x18\x01 \x01(\r\x12\x11\n\tis_agreed\x18\x02 \x01(\x08\x12<\n\x06reason\x18\x03 \x01(\x0e\x32,.proto.PlayerApplyEnterMpResultNotify.Reason\"M\n\x05\x43mdId\x12\x08\n\x04NONE\x10\x00\x12\x0b\n\x06\x43MD_ID\x10\x8c\x0e\x12\x13\n\x0f\x45NET_CHANNEL_ID\x10\x00\x12\x14\n\x10\x45NET_IS_RELIABLE\x10\x01\x1a\x02\x10\x01\"\x9e\x01\n\x06Reason\x12\x10\n\x0cPLAYER_JUDGE\x10\x00\x12\x16\n\x12SCENE_CANNOT_ENTER\x10\x01\x12\x1a\n\x16PLAYER_CANNOT_ENTER_MP\x10\x02\x12\x10\n\x0cSYSTEM_JUDGE\x10\x03\x12\x1b\n\x17\x41LLOW_ENTER_PLAYER_FULL\x10\x04\x12\x1f\n\x1bWORLD_LEVEL_LOWER_THAN_HOST\x10\x05\"\xa7\x01\n\x1bPlayerApplyEnterMpResultReq\x12\x11\n\tapply_uid\x18\x01 \x01(\r\x12\x11\n\tis_agreed\x18\x02 \x01(\x08\"b\n\x05\x43mdId\x12\x08\n\x04NONE\x10\x00\x12\x0b\n\x06\x43MD_ID\x10\x8d\x0e\x12\x13\n\x0f\x45NET_CHANNEL_ID\x10\x00\x12\x14\n\x10\x45NET_IS_RELIABLE\x10\x01\x12\x13\n\x0fIS_ALLOW_CLIENT\x10\x01\x1a\x02\x10\x01\"\xa3\x01\n\x1bPlayerApplyEnterMpResultRsp\x12\x0f\n\x07retcode\x18\x01 \x01(\x05\x12\x11\n\tapply_uid\x18\x02 \x01(\r\x12\x11\n\tis_agreed\x18\x03 \x01(\x08\"M\n\x05\x43mdId\x12\x08\n\x04NONE\x10\x00\x12\x0b\n\x06\x43MD_ID\x10\x8e\x0e\x12\x13\n\x0f\x45NET_CHANNEL_ID\x10\x00\x12\x14\n\x10\x45NET_IS_RELIABLE\x10\x01\x1a\x02\x10\x01\"\x97\x02\n\x16PlayerQuitFromMpNotify\x12\x38\n\x06reason\x18\x01 \x01(\x0e\x32(.proto.PlayerQuitFromMpNotify.QuitReason\"M\n\x05\x43mdId\x12\x08\n\x04NONE\x10\x00\x12\x0b\n\x06\x43MD_ID\x10\x8f\x0e\x12\x13\n\x0f\x45NET_CHANNEL_ID\x10\x00\x12\x14\n\x10\x45NET_IS_RELIABLE\x10\x01\x1a\x02\x10\x01\"t\n\nQuitReason\x12\x0b\n\x07INVALID\x10\x00\x12\x18\n\x14HOST_NO_OTHER_PLAYER\x10\x01\x12\x10\n\x0cKICK_BY_HOST\x10\x02\x12\x14\n\x10\x42\x41\x43K_TO_MY_WORLD\x10\x03\x12\x17\n\x13KICK_BY_HOST_LOGOUT\x10\x04\"\xe8\x01\n\x16PlayerPreEnterMpNotify\x12\x0b\n\x03uid\x18\x01 \x01(\r\x12\x32\n\x05state\x18\x02 \x01(\x0e\x32#.proto.PlayerPreEnterMpNotify.State\x12\x10\n\x08nickname\x18\x03 \x01(\t\"M\n\x05\x43mdId\x12\x08\n\x04NONE\x10\x00\x12\x0b\n\x06\x43MD_ID\x10\x90\x0e\x12\x13\n\x0f\x45NET_CHANNEL_ID\x10\x00\x12\x14\n\x10\x45NET_IS_RELIABLE\x10\x01\x1a\x02\x10\x01\",\n\x05State\x12\x0b\n\x07INVALID\x10\x00\x12\t\n\x05START\x10\x01\x12\x0b\n\x07TIMEOUT\x10\x02\"\x84\x01\n\x1eGetPlayerMpModeAvailabilityReq\"b\n\x05\x43mdId\x12\x08\n\x04NONE\x10\x00\x12\x0b\n\x06\x43MD_ID\x10\x91\x0e\x12\x13\n\x0f\x45NET_CHANNEL_ID\x10\x00\x12\x14\n\x10\x45NET_IS_RELIABLE\x10\x01\x12\x13\n\x0fIS_ALLOW_CLIENT\x10\x01\x1a\x02\x10\x01\"\xa4\x01\n\x1eGetPlayerMpModeAvailabilityRsp\x12\x0f\n\x07retcode\x18\x01 \x01(\x05\x12\x0e\n\x06mp_ret\x18\x02 \x01(\x05\x12\x12\n\nparam_list\x18\x03 \x03(\r\"M\n\x05\x43mdId\x12\x08\n\x04NONE\x10\x00\x12\x0b\n\x06\x43MD_ID\x10\x92\x0e\x12\x13\n\x0f\x45NET_CHANNEL_ID\x10\x00\x12\x14\n\x10\x45NET_IS_RELIABLE\x10\x01\x1a\x02\x10\x01\x62\x06proto3')
  ,
  dependencies=[define__pb2.DESCRIPTOR,])



_PLAYERAPPLYENTERMPNOTIFY_CMDID = _descriptor.EnumDescriptor(
  name='CmdId',
  full_name='proto.PlayerApplyEnterMpNotify.CmdId',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='NONE', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='CMD_ID', index=1, number=1801,
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
  serialized_start=120,
  serialized_end=197,
)
_sym_db.RegisterEnumDescriptor(_PLAYERAPPLYENTERMPNOTIFY_CMDID)

_PLAYERAPPLYENTERMPREQ_CMDID = _descriptor.EnumDescriptor(
  name='CmdId',
  full_name='proto.PlayerApplyEnterMpReq.CmdId',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='NONE', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='CMD_ID', index=1, number=1802,
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
  serialized_start=245,
  serialized_end=343,
)
_sym_db.RegisterEnumDescriptor(_PLAYERAPPLYENTERMPREQ_CMDID)

_PLAYERAPPLYENTERMPRSP_CMDID = _descriptor.EnumDescriptor(
  name='CmdId',
  full_name='proto.PlayerApplyEnterMpRsp.CmdId',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='NONE', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='CMD_ID', index=1, number=1803,
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
  serialized_start=408,
  serialized_end=485,
)
_sym_db.RegisterEnumDescriptor(_PLAYERAPPLYENTERMPRSP_CMDID)

_PLAYERAPPLYENTERMPRESULTNOTIFY_CMDID = _descriptor.EnumDescriptor(
  name='CmdId',
  full_name='proto.PlayerApplyEnterMpResultNotify.CmdId',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='NONE', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='CMD_ID', index=1, number=1804,
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
  serialized_start=623,
  serialized_end=700,
)
_sym_db.RegisterEnumDescriptor(_PLAYERAPPLYENTERMPRESULTNOTIFY_CMDID)

_PLAYERAPPLYENTERMPRESULTNOTIFY_REASON = _descriptor.EnumDescriptor(
  name='Reason',
  full_name='proto.PlayerApplyEnterMpResultNotify.Reason',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='PLAYER_JUDGE', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='SCENE_CANNOT_ENTER', index=1, number=1,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PLAYER_CANNOT_ENTER_MP', index=2, number=2,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='SYSTEM_JUDGE', index=3, number=3,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ALLOW_ENTER_PLAYER_FULL', index=4, number=4,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='WORLD_LEVEL_LOWER_THAN_HOST', index=5, number=5,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=None,
  serialized_start=703,
  serialized_end=861,
)
_sym_db.RegisterEnumDescriptor(_PLAYERAPPLYENTERMPRESULTNOTIFY_REASON)

_PLAYERAPPLYENTERMPRESULTREQ_CMDID = _descriptor.EnumDescriptor(
  name='CmdId',
  full_name='proto.PlayerApplyEnterMpResultReq.CmdId',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='NONE', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='CMD_ID', index=1, number=1805,
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
  serialized_start=933,
  serialized_end=1031,
)
_sym_db.RegisterEnumDescriptor(_PLAYERAPPLYENTERMPRESULTREQ_CMDID)

_PLAYERAPPLYENTERMPRESULTRSP_CMDID = _descriptor.EnumDescriptor(
  name='CmdId',
  full_name='proto.PlayerApplyEnterMpResultRsp.CmdId',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='NONE', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='CMD_ID', index=1, number=1806,
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
  serialized_start=1120,
  serialized_end=1197,
)
_sym_db.RegisterEnumDescriptor(_PLAYERAPPLYENTERMPRESULTRSP_CMDID)

_PLAYERQUITFROMMPNOTIFY_CMDID = _descriptor.EnumDescriptor(
  name='CmdId',
  full_name='proto.PlayerQuitFromMpNotify.CmdId',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='NONE', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='CMD_ID', index=1, number=1807,
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
  serialized_start=1284,
  serialized_end=1361,
)
_sym_db.RegisterEnumDescriptor(_PLAYERQUITFROMMPNOTIFY_CMDID)

_PLAYERQUITFROMMPNOTIFY_QUITREASON = _descriptor.EnumDescriptor(
  name='QuitReason',
  full_name='proto.PlayerQuitFromMpNotify.QuitReason',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='INVALID', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='HOST_NO_OTHER_PLAYER', index=1, number=1,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='KICK_BY_HOST', index=2, number=2,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='BACK_TO_MY_WORLD', index=3, number=3,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='KICK_BY_HOST_LOGOUT', index=4, number=4,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=None,
  serialized_start=1363,
  serialized_end=1479,
)
_sym_db.RegisterEnumDescriptor(_PLAYERQUITFROMMPNOTIFY_QUITREASON)

_PLAYERPREENTERMPNOTIFY_CMDID = _descriptor.EnumDescriptor(
  name='CmdId',
  full_name='proto.PlayerPreEnterMpNotify.CmdId',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='NONE', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='CMD_ID', index=1, number=1808,
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
  serialized_start=1591,
  serialized_end=1668,
)
_sym_db.RegisterEnumDescriptor(_PLAYERPREENTERMPNOTIFY_CMDID)

_PLAYERPREENTERMPNOTIFY_STATE = _descriptor.EnumDescriptor(
  name='State',
  full_name='proto.PlayerPreEnterMpNotify.State',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='INVALID', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='START', index=1, number=1,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='TIMEOUT', index=2, number=2,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=None,
  serialized_start=1670,
  serialized_end=1714,
)
_sym_db.RegisterEnumDescriptor(_PLAYERPREENTERMPNOTIFY_STATE)

_GETPLAYERMPMODEAVAILABILITYREQ_CMDID = _descriptor.EnumDescriptor(
  name='CmdId',
  full_name='proto.GetPlayerMpModeAvailabilityReq.CmdId',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='NONE', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='CMD_ID', index=1, number=1809,
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
  serialized_start=1751,
  serialized_end=1849,
)
_sym_db.RegisterEnumDescriptor(_GETPLAYERMPMODEAVAILABILITYREQ_CMDID)

_GETPLAYERMPMODEAVAILABILITYRSP_CMDID = _descriptor.EnumDescriptor(
  name='CmdId',
  full_name='proto.GetPlayerMpModeAvailabilityRsp.CmdId',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='NONE', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='CMD_ID', index=1, number=1810,
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
  serialized_start=1939,
  serialized_end=2016,
)
_sym_db.RegisterEnumDescriptor(_GETPLAYERMPMODEAVAILABILITYRSP_CMDID)


_PLAYERAPPLYENTERMPNOTIFY = _descriptor.Descriptor(
  name='PlayerApplyEnterMpNotify',
  full_name='proto.PlayerApplyEnterMpNotify',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='src_player_info', full_name='proto.PlayerApplyEnterMpNotify.src_player_info', index=0,
      number=1, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
    _PLAYERAPPLYENTERMPNOTIFY_CMDID,
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=42,
  serialized_end=197,
)


_PLAYERAPPLYENTERMPREQ = _descriptor.Descriptor(
  name='PlayerApplyEnterMpReq',
  full_name='proto.PlayerApplyEnterMpReq',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='target_uid', full_name='proto.PlayerApplyEnterMpReq.target_uid', index=0,
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
    _PLAYERAPPLYENTERMPREQ_CMDID,
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=200,
  serialized_end=343,
)


_PLAYERAPPLYENTERMPRSP = _descriptor.Descriptor(
  name='PlayerApplyEnterMpRsp',
  full_name='proto.PlayerApplyEnterMpRsp',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='retcode', full_name='proto.PlayerApplyEnterMpRsp.retcode', index=0,
      number=1, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='target_uid', full_name='proto.PlayerApplyEnterMpRsp.target_uid', index=1,
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
    _PLAYERAPPLYENTERMPRSP_CMDID,
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=346,
  serialized_end=485,
)


_PLAYERAPPLYENTERMPRESULTNOTIFY = _descriptor.Descriptor(
  name='PlayerApplyEnterMpResultNotify',
  full_name='proto.PlayerApplyEnterMpResultNotify',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='target_uid', full_name='proto.PlayerApplyEnterMpResultNotify.target_uid', index=0,
      number=1, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='is_agreed', full_name='proto.PlayerApplyEnterMpResultNotify.is_agreed', index=1,
      number=2, type=8, cpp_type=7, label=1,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='reason', full_name='proto.PlayerApplyEnterMpResultNotify.reason', index=2,
      number=3, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
    _PLAYERAPPLYENTERMPRESULTNOTIFY_CMDID,
    _PLAYERAPPLYENTERMPRESULTNOTIFY_REASON,
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=488,
  serialized_end=861,
)


_PLAYERAPPLYENTERMPRESULTREQ = _descriptor.Descriptor(
  name='PlayerApplyEnterMpResultReq',
  full_name='proto.PlayerApplyEnterMpResultReq',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='apply_uid', full_name='proto.PlayerApplyEnterMpResultReq.apply_uid', index=0,
      number=1, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='is_agreed', full_name='proto.PlayerApplyEnterMpResultReq.is_agreed', index=1,
      number=2, type=8, cpp_type=7, label=1,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
    _PLAYERAPPLYENTERMPRESULTREQ_CMDID,
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=864,
  serialized_end=1031,
)


_PLAYERAPPLYENTERMPRESULTRSP = _descriptor.Descriptor(
  name='PlayerApplyEnterMpResultRsp',
  full_name='proto.PlayerApplyEnterMpResultRsp',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='retcode', full_name='proto.PlayerApplyEnterMpResultRsp.retcode', index=0,
      number=1, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='apply_uid', full_name='proto.PlayerApplyEnterMpResultRsp.apply_uid', index=1,
      number=2, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='is_agreed', full_name='proto.PlayerApplyEnterMpResultRsp.is_agreed', index=2,
      number=3, type=8, cpp_type=7, label=1,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
    _PLAYERAPPLYENTERMPRESULTRSP_CMDID,
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=1034,
  serialized_end=1197,
)


_PLAYERQUITFROMMPNOTIFY = _descriptor.Descriptor(
  name='PlayerQuitFromMpNotify',
  full_name='proto.PlayerQuitFromMpNotify',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='reason', full_name='proto.PlayerQuitFromMpNotify.reason', index=0,
      number=1, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
    _PLAYERQUITFROMMPNOTIFY_CMDID,
    _PLAYERQUITFROMMPNOTIFY_QUITREASON,
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=1200,
  serialized_end=1479,
)


_PLAYERPREENTERMPNOTIFY = _descriptor.Descriptor(
  name='PlayerPreEnterMpNotify',
  full_name='proto.PlayerPreEnterMpNotify',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='uid', full_name='proto.PlayerPreEnterMpNotify.uid', index=0,
      number=1, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='state', full_name='proto.PlayerPreEnterMpNotify.state', index=1,
      number=2, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='nickname', full_name='proto.PlayerPreEnterMpNotify.nickname', index=2,
      number=3, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
    _PLAYERPREENTERMPNOTIFY_CMDID,
    _PLAYERPREENTERMPNOTIFY_STATE,
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=1482,
  serialized_end=1714,
)


_GETPLAYERMPMODEAVAILABILITYREQ = _descriptor.Descriptor(
  name='GetPlayerMpModeAvailabilityReq',
  full_name='proto.GetPlayerMpModeAvailabilityReq',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
    _GETPLAYERMPMODEAVAILABILITYREQ_CMDID,
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=1717,
  serialized_end=1849,
)


_GETPLAYERMPMODEAVAILABILITYRSP = _descriptor.Descriptor(
  name='GetPlayerMpModeAvailabilityRsp',
  full_name='proto.GetPlayerMpModeAvailabilityRsp',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='retcode', full_name='proto.GetPlayerMpModeAvailabilityRsp.retcode', index=0,
      number=1, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='mp_ret', full_name='proto.GetPlayerMpModeAvailabilityRsp.mp_ret', index=1,
      number=2, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='param_list', full_name='proto.GetPlayerMpModeAvailabilityRsp.param_list', index=2,
      number=3, type=13, cpp_type=3, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
    _GETPLAYERMPMODEAVAILABILITYRSP_CMDID,
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=1852,
  serialized_end=2016,
)

_PLAYERAPPLYENTERMPNOTIFY.fields_by_name['src_player_info'].message_type = define__pb2._ONLINEPLAYERINFO
_PLAYERAPPLYENTERMPNOTIFY_CMDID.containing_type = _PLAYERAPPLYENTERMPNOTIFY
_PLAYERAPPLYENTERMPREQ_CMDID.containing_type = _PLAYERAPPLYENTERMPREQ
_PLAYERAPPLYENTERMPRSP_CMDID.containing_type = _PLAYERAPPLYENTERMPRSP
_PLAYERAPPLYENTERMPRESULTNOTIFY.fields_by_name['reason'].enum_type = _PLAYERAPPLYENTERMPRESULTNOTIFY_REASON
_PLAYERAPPLYENTERMPRESULTNOTIFY_CMDID.containing_type = _PLAYERAPPLYENTERMPRESULTNOTIFY
_PLAYERAPPLYENTERMPRESULTNOTIFY_REASON.containing_type = _PLAYERAPPLYENTERMPRESULTNOTIFY
_PLAYERAPPLYENTERMPRESULTREQ_CMDID.containing_type = _PLAYERAPPLYENTERMPRESULTREQ
_PLAYERAPPLYENTERMPRESULTRSP_CMDID.containing_type = _PLAYERAPPLYENTERMPRESULTRSP
_PLAYERQUITFROMMPNOTIFY.fields_by_name['reason'].enum_type = _PLAYERQUITFROMMPNOTIFY_QUITREASON
_PLAYERQUITFROMMPNOTIFY_CMDID.containing_type = _PLAYERQUITFROMMPNOTIFY
_PLAYERQUITFROMMPNOTIFY_QUITREASON.containing_type = _PLAYERQUITFROMMPNOTIFY
_PLAYERPREENTERMPNOTIFY.fields_by_name['state'].enum_type = _PLAYERPREENTERMPNOTIFY_STATE
_PLAYERPREENTERMPNOTIFY_CMDID.containing_type = _PLAYERPREENTERMPNOTIFY
_PLAYERPREENTERMPNOTIFY_STATE.containing_type = _PLAYERPREENTERMPNOTIFY
_GETPLAYERMPMODEAVAILABILITYREQ_CMDID.containing_type = _GETPLAYERMPMODEAVAILABILITYREQ
_GETPLAYERMPMODEAVAILABILITYRSP_CMDID.containing_type = _GETPLAYERMPMODEAVAILABILITYRSP
DESCRIPTOR.message_types_by_name['PlayerApplyEnterMpNotify'] = _PLAYERAPPLYENTERMPNOTIFY
DESCRIPTOR.message_types_by_name['PlayerApplyEnterMpReq'] = _PLAYERAPPLYENTERMPREQ
DESCRIPTOR.message_types_by_name['PlayerApplyEnterMpRsp'] = _PLAYERAPPLYENTERMPRSP
DESCRIPTOR.message_types_by_name['PlayerApplyEnterMpResultNotify'] = _PLAYERAPPLYENTERMPRESULTNOTIFY
DESCRIPTOR.message_types_by_name['PlayerApplyEnterMpResultReq'] = _PLAYERAPPLYENTERMPRESULTREQ
DESCRIPTOR.message_types_by_name['PlayerApplyEnterMpResultRsp'] = _PLAYERAPPLYENTERMPRESULTRSP
DESCRIPTOR.message_types_by_name['PlayerQuitFromMpNotify'] = _PLAYERQUITFROMMPNOTIFY
DESCRIPTOR.message_types_by_name['PlayerPreEnterMpNotify'] = _PLAYERPREENTERMPNOTIFY
DESCRIPTOR.message_types_by_name['GetPlayerMpModeAvailabilityReq'] = _GETPLAYERMPMODEAVAILABILITYREQ
DESCRIPTOR.message_types_by_name['GetPlayerMpModeAvailabilityRsp'] = _GETPLAYERMPMODEAVAILABILITYRSP
_sym_db.RegisterFileDescriptor(DESCRIPTOR)

PlayerApplyEnterMpNotify = _reflection.GeneratedProtocolMessageType('PlayerApplyEnterMpNotify', (_message.Message,), dict(
  DESCRIPTOR = _PLAYERAPPLYENTERMPNOTIFY,
  __module__ = 'cmd.cmd_mp_pb2'
  # @@protoc_insertion_point(class_scope:proto.PlayerApplyEnterMpNotify)
  ))
_sym_db.RegisterMessage(PlayerApplyEnterMpNotify)

PlayerApplyEnterMpReq = _reflection.GeneratedProtocolMessageType('PlayerApplyEnterMpReq', (_message.Message,), dict(
  DESCRIPTOR = _PLAYERAPPLYENTERMPREQ,
  __module__ = 'cmd.cmd_mp_pb2'
  # @@protoc_insertion_point(class_scope:proto.PlayerApplyEnterMpReq)
  ))
_sym_db.RegisterMessage(PlayerApplyEnterMpReq)

PlayerApplyEnterMpRsp = _reflection.GeneratedProtocolMessageType('PlayerApplyEnterMpRsp', (_message.Message,), dict(
  DESCRIPTOR = _PLAYERAPPLYENTERMPRSP,
  __module__ = 'cmd.cmd_mp_pb2'
  # @@protoc_insertion_point(class_scope:proto.PlayerApplyEnterMpRsp)
  ))
_sym_db.RegisterMessage(PlayerApplyEnterMpRsp)

PlayerApplyEnterMpResultNotify = _reflection.GeneratedProtocolMessageType('PlayerApplyEnterMpResultNotify', (_message.Message,), dict(
  DESCRIPTOR = _PLAYERAPPLYENTERMPRESULTNOTIFY,
  __module__ = 'cmd.cmd_mp_pb2'
  # @@protoc_insertion_point(class_scope:proto.PlayerApplyEnterMpResultNotify)
  ))
_sym_db.RegisterMessage(PlayerApplyEnterMpResultNotify)

PlayerApplyEnterMpResultReq = _reflection.GeneratedProtocolMessageType('PlayerApplyEnterMpResultReq', (_message.Message,), dict(
  DESCRIPTOR = _PLAYERAPPLYENTERMPRESULTREQ,
  __module__ = 'cmd.cmd_mp_pb2'
  # @@protoc_insertion_point(class_scope:proto.PlayerApplyEnterMpResultReq)
  ))
_sym_db.RegisterMessage(PlayerApplyEnterMpResultReq)

PlayerApplyEnterMpResultRsp = _reflection.GeneratedProtocolMessageType('PlayerApplyEnterMpResultRsp', (_message.Message,), dict(
  DESCRIPTOR = _PLAYERAPPLYENTERMPRESULTRSP,
  __module__ = 'cmd.cmd_mp_pb2'
  # @@protoc_insertion_point(class_scope:proto.PlayerApplyEnterMpResultRsp)
  ))
_sym_db.RegisterMessage(PlayerApplyEnterMpResultRsp)

PlayerQuitFromMpNotify = _reflection.GeneratedProtocolMessageType('PlayerQuitFromMpNotify', (_message.Message,), dict(
  DESCRIPTOR = _PLAYERQUITFROMMPNOTIFY,
  __module__ = 'cmd.cmd_mp_pb2'
  # @@protoc_insertion_point(class_scope:proto.PlayerQuitFromMpNotify)
  ))
_sym_db.RegisterMessage(PlayerQuitFromMpNotify)

PlayerPreEnterMpNotify = _reflection.GeneratedProtocolMessageType('PlayerPreEnterMpNotify', (_message.Message,), dict(
  DESCRIPTOR = _PLAYERPREENTERMPNOTIFY,
  __module__ = 'cmd.cmd_mp_pb2'
  # @@protoc_insertion_point(class_scope:proto.PlayerPreEnterMpNotify)
  ))
_sym_db.RegisterMessage(PlayerPreEnterMpNotify)

GetPlayerMpModeAvailabilityReq = _reflection.GeneratedProtocolMessageType('GetPlayerMpModeAvailabilityReq', (_message.Message,), dict(
  DESCRIPTOR = _GETPLAYERMPMODEAVAILABILITYREQ,
  __module__ = 'cmd.cmd_mp_pb2'
  # @@protoc_insertion_point(class_scope:proto.GetPlayerMpModeAvailabilityReq)
  ))
_sym_db.RegisterMessage(GetPlayerMpModeAvailabilityReq)

GetPlayerMpModeAvailabilityRsp = _reflection.GeneratedProtocolMessageType('GetPlayerMpModeAvailabilityRsp', (_message.Message,), dict(
  DESCRIPTOR = _GETPLAYERMPMODEAVAILABILITYRSP,
  __module__ = 'cmd.cmd_mp_pb2'
  # @@protoc_insertion_point(class_scope:proto.GetPlayerMpModeAvailabilityRsp)
  ))
_sym_db.RegisterMessage(GetPlayerMpModeAvailabilityRsp)


_PLAYERAPPLYENTERMPNOTIFY_CMDID.has_options = True
_PLAYERAPPLYENTERMPNOTIFY_CMDID._options = _descriptor._ParseOptions(descriptor_pb2.EnumOptions(), _b('\020\001'))
_PLAYERAPPLYENTERMPREQ_CMDID.has_options = True
_PLAYERAPPLYENTERMPREQ_CMDID._options = _descriptor._ParseOptions(descriptor_pb2.EnumOptions(), _b('\020\001'))
_PLAYERAPPLYENTERMPRSP_CMDID.has_options = True
_PLAYERAPPLYENTERMPRSP_CMDID._options = _descriptor._ParseOptions(descriptor_pb2.EnumOptions(), _b('\020\001'))
_PLAYERAPPLYENTERMPRESULTNOTIFY_CMDID.has_options = True
_PLAYERAPPLYENTERMPRESULTNOTIFY_CMDID._options = _descriptor._ParseOptions(descriptor_pb2.EnumOptions(), _b('\020\001'))
_PLAYERAPPLYENTERMPRESULTREQ_CMDID.has_options = True
_PLAYERAPPLYENTERMPRESULTREQ_CMDID._options = _descriptor._ParseOptions(descriptor_pb2.EnumOptions(), _b('\020\001'))
_PLAYERAPPLYENTERMPRESULTRSP_CMDID.has_options = True
_PLAYERAPPLYENTERMPRESULTRSP_CMDID._options = _descriptor._ParseOptions(descriptor_pb2.EnumOptions(), _b('\020\001'))
_PLAYERQUITFROMMPNOTIFY_CMDID.has_options = True
_PLAYERQUITFROMMPNOTIFY_CMDID._options = _descriptor._ParseOptions(descriptor_pb2.EnumOptions(), _b('\020\001'))
_PLAYERPREENTERMPNOTIFY_CMDID.has_options = True
_PLAYERPREENTERMPNOTIFY_CMDID._options = _descriptor._ParseOptions(descriptor_pb2.EnumOptions(), _b('\020\001'))
_GETPLAYERMPMODEAVAILABILITYREQ_CMDID.has_options = True
_GETPLAYERMPMODEAVAILABILITYREQ_CMDID._options = _descriptor._ParseOptions(descriptor_pb2.EnumOptions(), _b('\020\001'))
_GETPLAYERMPMODEAVAILABILITYRSP_CMDID.has_options = True
_GETPLAYERMPMODEAVAILABILITYRSP_CMDID._options = _descriptor._ParseOptions(descriptor_pb2.EnumOptions(), _b('\020\001'))
# @@protoc_insertion_point(module_scope)

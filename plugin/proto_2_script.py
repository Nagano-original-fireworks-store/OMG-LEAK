#!/usr/bin/python
# -*- coding: UTF-8 -*-
# author: songxy

import os
from google.protobuf.json_format import MessageToJson
# import proto here


# 获取proto文件的所有有效协议
def get_proto_list(filename, suffix):
    rs_lst = []

    module_name = filename.split('.')[0] + '_pb2'
    message_dir = eval('%s.DESCRIPTOR.message_types_by_name' % module_name)

    for proto in message_dir:
        # print(proto)
        if suffix == 'all':
            rs_lst.append(proto)
        else:
            tmp_lst = suffix.split('|')
            for tmp in tmp_lst:
                if proto.find(tmp) > -1 and proto != 'DebugNotify':
                    rs_lst.append(proto)
                    break
        # elif suffix[0] == '!' and proto.find(suffix[1:]) == -1:
        #     rs_lst.append(proto)
        # elif suffix[0] != '!' and proto.find(suffix) > -1:
        #     rs_lst.append(proto)

    return rs_lst


# 自动生成的代码
def get_auto_created_code(proto_lst, filename):
    rs_lst = []
    output_dir_0 = {}
    output_dir_1 = {}

    if filename == 'ScriptOp.cpp':
        for proto in proto_lst:
            output = 'int CG4GameScriptOp::Do%s(unsigned int dwUin, STScriptOpParam *pParam)\n' % proto
            output += '{\n\tstring data_pb;\n\n'
            output += '\tproto::%s req;\n' % proto
            output += '\tstring jsonstr = GetJsonStr("%s");\n' % proto
            output += '\tgoogle::protobuf::util::JsonStringToMessage(jsonstr, &req);\n\n'
            output += '\tunsigned short wCmdID = proto::%s_CmdId_CMD_ID;\n\n' % proto
            output += '\tPackProtobuf(dwUin, wCmdID, req, data_pb);\n'
            output += '\tstring debug_str;\n'
            output += '\tgoogle::protobuf::util::MessageToJsonString(req, &debug_str,option);\n'
            output += '\tdebug_str = "\\n<send>\\n"+string(GetCurDateTimeCStr(NULL))+" %s\\n" + debug_str + "</send>"\n;' % proto;
            output += '\tm_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());\n'
            output += '\treturn SendPkg(dwUin, wCmdID, pParam, data_pb.length());\n}\n\n'
            output_dir_0[proto] = output
        rs_lst.append(output_dir_0)

    if filename == 'ScriptOp.h':
        for proto in proto_lst:
            output_dir_0[proto] = '\tint Do%s(unsigned int dwUin, STScriptOpParam *pParam);\n' % proto
            output_dir_1[proto] = '\t\tADD_OPMAP(TRANS_%s, &CG4GameScriptOp::Do%s)\n' % (proto, proto)
        rs_lst.append(output_dir_0)
        rs_lst.append(output_dir_1)

    if filename == 'Trans.h':
        for proto in proto_lst:
            output_dir_0[proto] = '#define TRANS_%s\t"%s"\n' % (proto, proto)
        rs_lst.append(output_dir_0)

    if filename == 'PkgProcess.cpp':
        for proto in proto_lst:
            if proto[-3:] == 'Rsp':
                tmp_str = proto[:-3] + 'Req'
            else:
                tmp_str = proto
            output = 'int CG4GameProcess::On%s(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)\n' % proto
            output += '{\n\tm_poFacadePlatform->TestLog(dwUin, "On%s");\n\n' % proto
            output += '\tm_packet.parseFromArray((char *)pPkg, uPkgSize);\n\n'
            output += '\tproto::%s rsp;\n' % proto
            output += '\trsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());\n'
            output += '\tm_poFacadePlatform->SetRobotAttr(dwUin, TRANS_%s, TRANS_DEAL_SUCCESS);\n\n' % tmp_str
            output += '\tstring debug_str;\n'
            output += '\tgoogle::protobuf::util::MessageToJsonString(rsp, &debug_str,option);\n'
            output += '\tdebug_str = "\\n<recv>\\n" + string(GetCurDateTimeCStr(NULL)) + " %s\\n" + debug_str + "</recv>"; \n' % proto
            output += '\tm_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());\n'

            output += '\treturn 0;\n}\n\n'
            output_dir_0[proto] = output
        rs_lst.append(output_dir_0)

    if filename == 'PkgProcess.h':
        for proto in proto_lst:
            output_dir_0[proto] = '\tint On%s(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);\n' % proto
            output_dir_1[proto] = '\t\tADD_HANDLERMAP(proto::%s_CmdId_CMD_ID,\t&CG4GameProcess::On%s)\n' % (proto, proto)
        rs_lst.append(output_dir_0)
        rs_lst.append(output_dir_1)

    return rs_lst


# 生成文件
def generate_file(filename, auto_created_code_lst):
    rs_lst = []
    # file = open(filename, 'r', encoding='utf-8')
    file = open(filename, 'r')

    auto_code_block = 0
    code_block = 0
    line = file.readline()
    while len(line) > 0:
        # 不在auto created里面都会被copy
        if code_block != 1:
            rs_lst.append(line)
        # 在no need下面会做个小判断清掉对应的自动生成代码
        if code_block == 2:
            for key in auto_created_code_lst[auto_code_block]:
                if line.find('int CG4GameScriptOp::Do%s(' % key) > -1 \
                        or line.find('int Do%s(' % key) > -1 \
                        or line.find('ADD_OPMAP(TRANS_%s,' % key) > -1 \
                        or line.find('#define TRANS_%s\t"' % key) > -1 \
                        or line.find('int CG4GameProcess::On%s(' % key) > -1 \
                        or line.find('int On%s(' % key) > -1 \
                        or line.find('ADD_HANDLERMAP(%s_CmdId_CMD_ID,' % key) > -1:
                    auto_created_code_lst[auto_code_block][key] = ''
        # 自动生成开始
        if line.find('//auto created code start') > -1:
            code_block = 1
            for key in auto_created_code_lst[auto_code_block]:
                rs_lst.append(auto_created_code_lst[auto_code_block][key])
            auto_code_block += 1
        # 自动生成结束
        if line.find('//auto created code end') > -1:
            rs_lst.append(line)
            code_block = 0
        # 不需要自动生成的部分一定在auto created code start前面
        if line.find('//no need to auto create') > -1:
            code_block = 2
        line = file.readline()

    # file = open(filename, 'w', encoding='utf-8')
    file = open(filename, 'w')
    file.writelines(rs_lst)
    file.close()


# 生成json文件
def generate_json_file(proto_file_lst):
    parent_path = os.path.abspath('..')
    json_file_root_path = parent_path + '/bin/jsonData/'

    for proto_file in proto_file_lst:
        module_name = proto_file.split('.')[0] + '_pb2'

        message_dir = eval('%s.DESCRIPTOR.message_types_by_name' % module_name)

        for proto in message_dir:
            try:
                message = eval('%s.%s()' % (module_name, proto))
                if hasattr(message,"IS_ALLOW_CLIENT"):
                    json_str = MessageToJson(message, True, True)

                    file = open(json_file_root_path + proto, 'w')
                    file.writelines(json_str)
                    file.close()
            except Exception as e:
                print(e)


# 生成lua文件
def generate_lua_file(proto_lst):
    parent_path = os.path.abspath('..')
    json_file_root_path = parent_path + '/bin/script/cg4/autoCreated/'

    for proto in proto_lst:
        output = 'require "../testscript/common_lib.lua"\nrequire "./common_lib2.lua"\n\n'

        output += 'function Step1()\n'
        output += '\tlocal nUin = ::GetRobotUin();\n'
        output += '\tg_szActionID = "%s";\n' % proto
        output += '\t::ResetTimer(1);\n'
        output += '\t::LogRun(g_szActionID.." begin");\n'
        output += '\t::StartTrans(g_szActionID);\n'
        output += '\t::DoCommand(g_szActionID, "");\n'
        output += 'end;\n\n'

        output += 'function Step2()\n'
        output += '\tg_szActionID = "%s";\n' % proto
        output += '\tCheckResponse(g_szActionID, 100, 100);\n'
        output += 'end;\n'

        file = open(json_file_root_path + proto + '.lua', 'w')
        file.writelines(output)
        file.close()


def proto_2_script():
    proto_root_path = 'protocol/'

    proto_file_lst = []
    for root, dirs, files in os.walk(proto_root_path):
        proto_file_lst = files
    proto_file_lst.remove('define.proto')
    # proto_file_lst.remove('editor.proto')
    # proto_file_lst.remove('retcode.proto')
    # proto_file_lst.remove('packet_head.proto')

    # 生成json文件
    generate_json_file(proto_file_lst)

    # 自动生成代码的规则
    reflect_dir = {
        'Req|Notify': ['ScriptOp.cpp', 'ScriptOp.h', 'Trans.h'],
        'Rsp|Notify': ['PkgProcess.cpp', 'PkgProcess.h']
    }

    for proto_suffix in reflect_dir:
        proto_lst = []
        # 获得所有proto文件中符合条件的协议
        for proto_file in proto_file_lst:
            proto_lst += get_proto_list(proto_file, proto_suffix)
        # 生成对应文件
        for f in reflect_dir[proto_suffix]:
            auto_code = get_auto_created_code(proto_lst, f)
            generate_file(f, auto_code)
        # lua脚本的生成逻辑放在这边有风险哦，改规则这边也要同步改~
        if proto_suffix == 'Req|Notify':
            generate_lua_file(proto_lst)


if __name__ == '__main__':
    proto_2_script()

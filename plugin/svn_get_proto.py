#!/usr/bin/python
# -*- coding: UTF-8 -*-
# author: songxy

import os
import sys

# import pprint
# import svn.local

# r = svn.local.LocalClient('D:\\hk4ecode')
# info = r.update()
# pprint.pprint(info)

proto_root_dir = '/home/data/cggaps_root/proto/'
protoc_target_dir = '../plugin/'


def svn_update_proto(root_dir):
    rs_lst = []

    for file_tuple in os.walk(root_dir):
        if len(file_tuple[2]) > 0:
            for proto_file in file_tuple[2]:
                file_str = file_tuple[0] + '/' + proto_file
                file_str = file_str.replace('//', '/')
                if file_str.find('/server_only') == -1:
                    rs_lst.append(file_str)

    print(rs_lst)
    return rs_lst


def modify_create_script_file(proto_lst):
    import_str_python = ''
    import_str_h = ''
    init_dir_lst = []

    for proto in proto_lst:
        direct_path = proto.split(proto_root_dir)[1]

        module_name = direct_path.replace('/', '.').replace('.proto', '_pb2')
        import_str_python += 'import %s as %s\n' % (module_name, module_name.split('.')[-1])

        h_file_name = direct_path.replace('.proto', '.pb.h')
        import_str_h += '#include "%s"\n' % h_file_name

        init_dir = '/'.join(direct_path.split('/')[:-1])
        if init_dir not in init_dir_lst and init_dir != '':
            init_dir_lst.append(init_dir)
            os.system('touch %s/__init__.py' % init_dir)

    # import_str_python += 'import packet_head_pb2\n'
    # import_str_h += '#include "packet_head.pb.h"\n'

    rs_lst = []
    # file = open('proto_2_script.py', 'r', encoding='utf-8')
    file = open('proto_2_script.py', 'r')
    content_lst = file.readlines()
    for content in content_lst:
        if content.find('# import proto here') > -1:
            rs_lst.append('# import proto here\n')
            rs_lst.append(import_str_python)
        else:
            rs_lst.append(content)

    # file = open('1.py', 'w', encoding='utf-8')
    file = open('tmp.py', 'w')
    file.writelines(rs_lst)

    file = open('Hk4eProto.h', 'w')
    file.writelines(import_str_h)
    file.close()


def svn_get_proto():
    try:
        # svn update
        proto_lst = svn_update_proto(proto_root_dir)
        os.system('rm -rf protocol/*')

        # create python .h file
        for proto in proto_lst:
            # copy file
            os.system('cp %s protocol/' % proto)

            # create file
            direct_path = proto.split(proto_root_dir)[1]
            os.system('cd %s && protoc --proto_path=./ --python_out=%s %s' % (proto_root_dir, protoc_target_dir, direct_path))
            os.system('cd %s && protoc --proto_path=./ --cpp_out=%s %s' % (proto_root_dir, protoc_target_dir, direct_path))
        # os.system('cd protocol/ && protoc --cpp_out=../ packet_head.proto')
        # os.system('cd protocol/ && protoc --cpp_out=../ packet_head.proto')

        # modify python file and hk4eproto.h
        modify_create_script_file(proto_lst)

        # exec proto_2_script
        os.system('python tmp.py')

        # build
        os.system('make')

        sys.exit(0)
    except Exception as e:
        print e
        print('python fail????unbelievable!!!!!!!!')
        sys.exit(1)


if __name__ == '__main__':
    svn_get_proto()

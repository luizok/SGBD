import sys
import struct


if __name__ == '__main__':

    ops = {
        'REM': b'\00',
        'INC': b'\01',
        'BUS': b'\02'
    }

    with open(sys.argv[1], 'rb') as txt_file:
        with open('ops.bin', 'wb') as ops_file:
            for line in txt_file:
                op, num = line[:-1].decode('ascii').split(':')
                ops_file.write(ops[op] + struct.pack('q', int(num)))
                
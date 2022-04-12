import struct
import  os
if __name__=='__main__':
    filepath='msg1.bin'
    binfile=open(filepath,'rb')
    size=os.path.getsize(filepath)
    for i in range(size):
        data=binfile.read(1)
        num=struct.unpack('B', data)
        print(num[0])


    binfile.close()



import pefile
import os
import math

def calculate_entropy(data):
    entropy = 0
    if data:
        for x in range(256):
            p_x = float(data.count(x))/len(data)
            if p_x > 0:
                entropy += - p_x * math.log(p_x, 2)
    return round(entropy, 9)
def getFileInformation(filePath):
    allData=[];
    if os.path.exists(filePath):
        pe = pefile.PE(filePath)
    else:
        return -1
    print("yol::",filePath)
    pe=pefile.PE(filePath)
    allData.append(pe.DOS_HEADER.e_cblp)
    allData.append(pe.DOS_HEADER.e_cp)
    allData.append(pe.DOS_HEADER.e_crlc)
    allData.append(pe.DOS_HEADER.e_cparhdr)
    allData.append(pe.DOS_HEADER.e_minalloc)
    allData.append(pe.DOS_HEADER.e_maxalloc)
    allData.append(pe.DOS_HEADER.e_ss)
    allData.append(pe.DOS_HEADER.e_sp)
    allData.append(pe.DOS_HEADER.e_csum)
    allData.append(pe.DOS_HEADER.e_ip)
    allData.append(pe.DOS_HEADER.e_cs)
    allData.append(pe.DOS_HEADER.e_lfarlc)
    allData.append(0)#pe.DOS_HEADER.e_ovno)
    allData.append(pe.DOS_HEADER.e_oemid)
    allData.append(pe.DOS_HEADER.e_oeminfo)
    allData.append(pe.DOS_HEADER.e_lfanew)
    allData.append(pe.FILE_HEADER.Machine)
    allData.append(pe.FILE_HEADER.NumberOfSections)
    allData.append(1)#pe.FILE_HEADER.TimeDateStamp) #19
    allData.append(pe.FILE_HEADER.PointerToSymbolTable)
    allData.append(pe.FILE_HEADER.NumberOfSymbols)
    allData.append(pe.FILE_HEADER.SizeOfOptionalHeader)
    allData.append(pe.FILE_HEADER.Characteristics) #23

    allData.append(267)

    if hasattr(pe.OPTIONAL_HEADER, 'MajorLinkerVersion'):
        allData.append(pe.OPTIONAL_HEADER.MajorLinkerVersion)
    else:
        allData.append(0)

    if hasattr(pe.OPTIONAL_HEADER, 'MinorLinkerVersion'):
        allData.append(pe.OPTIONAL_HEADER.MinorLinkerVersion)
    else:
        allData.append(0)

    if hasattr(pe.OPTIONAL_HEADER, 'SizeOfCode'):
        allData.append(pe.OPTIONAL_HEADER.SizeOfCode)
    else:
        allData.append(0)

    if hasattr(pe.OPTIONAL_HEADER, 'SizeOfInitializedData'):
        allData.append(pe.OPTIONAL_HEADER.SizeOfInitializedData)
    else:
        allData.append(0)

    #if hasattr(pe.OPTIONAL_HEADER, 'SizeOfUninitializedData'):
    #    allData.append(pe.OPTIONAL_HEADER.SizeOfUninitializedData)
    #else:
    allData.append(0)

    #if hasattr(pe.OPTIONAL_HEADER, 'AddressOfEntryPoint'):
    #    allData.append(pe.OPTIONAL_HEADER.AddressOfEntryPoint)
    #else:
    allData.append(0)

    if hasattr(pe.OPTIONAL_HEADER, 'BaseOfCode'):
        allData.append(pe.OPTIONAL_HEADER.BaseOfCode)
    else:
        allData.append(0)

    if hasattr(pe.OPTIONAL_HEADER, 'BaseOfData'):
        allData.append(pe.OPTIONAL_HEADER.BaseOfData)
    else:
        allData.append(0)

    if hasattr(pe.OPTIONAL_HEADER, 'ImageBase'): #33
        allData.append(pe.OPTIONAL_HEADER.ImageBase)
    else:
        allData.append(0)

    if hasattr(pe.OPTIONAL_HEADER, 'SectionAlignment'):
        allData.append(pe.OPTIONAL_HEADER.SectionAlignment)
    else:
        allData.append(0)

    if hasattr(pe.OPTIONAL_HEADER, 'FileAlignment'):
        allData.append(pe.OPTIONAL_HEADER.FileAlignment)
    else:
        allData.append(0)

    if hasattr(pe.OPTIONAL_HEADER, 'MajorOperatingSystemVersion'):
        allData.append(pe.OPTIONAL_HEADER.MajorOperatingSystemVersion)
    else:
        allData.append(0)

    if hasattr(pe.OPTIONAL_HEADER, 'MinorOperatingSystemVersion'):
        allData.append(pe.OPTIONAL_HEADER.MinorOperatingSystemVersion)
    else:
        allData.append(0)

    if hasattr(pe.OPTIONAL_HEADER, 'MajorImageVersion'):
        allData.append(pe.OPTIONAL_HEADER.MajorImageVersion)
    else:
        allData.append(0)

    if hasattr(pe.OPTIONAL_HEADER, 'MinorImageVersion'):
        allData.append(pe.OPTIONAL_HEADER.MinorImageVersion)
    else:
        allData.append(0)

    if hasattr(pe.OPTIONAL_HEADER, 'MajorSubsystemVersion'):
        allData.append(pe.OPTIONAL_HEADER.MajorSubsystemVersion)
    else:
        allData.append(0)

    if hasattr(pe.OPTIONAL_HEADER, 'MinorSubsystemVersion'):
        allData.append(pe.OPTIONAL_HEADER.MinorSubsystemVersion)
    else:
        allData.append(0)

    if hasattr(pe.OPTIONAL_HEADER, 'Win32VersionValue'):
        allData.append(pe.OPTIONAL_HEADER.Win32VersionValue)
    else:
        allData.append(0)

    if hasattr(pe.OPTIONAL_HEADER, 'SizeOfImage'):
        allData.append(pe.OPTIONAL_HEADER.SizeOfImage)
    else:
        allData.append(0)

    if hasattr(pe.OPTIONAL_HEADER, 'SizeOfHeaders'):
        allData.append(pe.OPTIONAL_HEADER.SizeOfHeaders)
    else:
        allData.append(0)

    if hasattr(pe.OPTIONAL_HEADER, 'CheckSum'):
        allData.append(int(hex(pe.OPTIONAL_HEADER.CheckSum), 16))
    else:
        allData.append(0)

    if hasattr(pe.OPTIONAL_HEADER, 'Subsystem'):
        allData.append(int(hex(pe.OPTIONAL_HEADER.Subsystem), 16))
    else:
        allData.append(0)

    if hasattr(pe.OPTIONAL_HEADER, 'DllCharacteristics'):
        allData.append(int(hex(pe.OPTIONAL_HEADER.DllCharacteristics), 16))
    else:
        allData.append(0)

    if hasattr(pe.OPTIONAL_HEADER, 'SizeOfStackReserve'):
        allData.append(int(hex(pe.OPTIONAL_HEADER.SizeOfStackReserve), 16))
    else:
        allData.append(0)

    if hasattr(pe.OPTIONAL_HEADER, 'SizeOfStackCommit'):
        allData.append(int(hex(pe.OPTIONAL_HEADER.SizeOfStackCommit), 16))
    else:
        allData.append(0)

    if hasattr(pe.OPTIONAL_HEADER, 'SizeOfHeapReserve'):
        allData.append(int(hex(pe.OPTIONAL_HEADER.SizeOfHeapReserve), 16))
    else:
        allData.append(0)

    if hasattr(pe.OPTIONAL_HEADER, 'SizeOfHeapCommit'):
        allData.append(int(hex(pe.OPTIONAL_HEADER.SizeOfHeapCommit), 16))
    else:
        allData.append(0)

    if hasattr(pe.OPTIONAL_HEADER, 'LoaderFlags'):
        allData.append(int(hex(pe.OPTIONAL_HEADER.LoaderFlags), 16))
    else:
        allData.append(0)

    if hasattr(pe.OPTIONAL_HEADER, 'NumberOfRvaAndSizes'):
        allData.append(int(hex(pe.OPTIONAL_HEADER.NumberOfRvaAndSizes), 16))
    else:
        allData.append(0)


    text_text    = [0,0,0,0,0,0,0,0,0,0,0]
    text_idata   = [0,0,0,0,0,0,0,0,0,0,0]
    text_rsrc    = [0,0,0,0,0,0,0,0,0,0,0]
    text_data    = [0,0,0,0,0,0,0,0,0,0,0]
    text_bss     = [0,0,0,0,0,0,0]
    text_textbss = [0,0,0,0]
    for section in pe.sections:
        if section.Name==b'.text\x00\x00\x00':
            text_text[0]=section.Misc
            text_text[1]=section.Misc_VirtualSize
            text_text[2]=section.VirtualAddress
            text_text[3]=section.SizeOfRawData
            text_text[4]=section.PointerToRawData
            text_text[5]=section.PointerToRelocations
            text_text[6]=section.PointerToLinenumbers
            text_text[7]=section.NumberOfRelocations
            text_text[8]=section.NumberOfLinenumbers
            text_text[9]=section.Characteristics
            text_text[10]=calculate_entropy(section.get_data())
        if section.Name == b'.idata\x00\x00\x00':
            text_idata[0]=section.Misc
            text_idata[1]=section.Misc_VirtualSize
            text_idata[2]=section.VirtualAddress
            text_idata[3]=section.SizeOfRawData
            text_idata[4]=section.PointerToRawData
            text_idata[5]=section.PointerToRelocations
            text_idata[6]=section.PointerToLinenumbers
            text_idata[7]=section.NumberOfRelocations
            text_idata[8]=section.NumberOfLinenumbers
            text_idata[9]=section.Characteristics
            text_idata[10]=calculate_entropy(section.get_data())
        if section.Name == b'.rsrc\x00\x00\x00':
            text_rsrc[0]=section.Misc
            text_rsrc[1]=section.Misc_VirtualSize
            text_rsrc[2]=section.VirtualAddress
            text_rsrc[3]=section.SizeOfRawData
            text_rsrc[4]=section.PointerToRawData
            text_rsrc[5]=section.PointerToRelocations
            text_rsrc[6]=section.PointerToLinenumbers
            text_rsrc[7]=section.NumberOfRelocations
            text_rsrc[8]=section.NumberOfLinenumbers
            text_rsrc[9]=section.Characteristics
            text_rsrc[10]=calculate_entropy(section.get_data())
        if section.Name == b'.data\x00\x00\x00':
            text_data[0]=section.Misc
            text_data[1]=section.Misc_VirtualSize
            text_data[2]=section.VirtualAddress
            text_data[3]=section.SizeOfRawData
            text_data[4]=section.PointerToRawData
            text_data[5]=section.PointerToRelocations
            text_data[6]=section.PointerToLinenumbers
            text_data[7]=section.NumberOfRelocations
            text_data[8]=section.NumberOfLinenumbers
            text_data[9]=section.Characteristics
            text_data[10]=calculate_entropy(section.get_data())
        if section.Name == b'.bss\x00\x00\x00':
            text_bss[0]= section.PointerToRawData
            text_bss[1]= section.Misc_VirtualSize
            text_bss[2]= section.VirtualAddress
            text_bss[3]= section.SizeOfRawData
            text_bss[4]= section.PointerToRawData
            text_bss[5]= section.Characteristics
            text_bss[6]= calculate_entropy(section.get_data())
        if section.Name == b'.textbss\x00\x00\x00':
            text_textbss[0]=section.PointerToRawData
            text_textbss[1]=section.Misc_VirtualSize
            text_textbss[2]=section.VirtualAddress
            text_textbss[3]=section.Characteristics
    allData=allData+text_text+text_idata+text_rsrc+text_data+text_bss+text_textbss
    return allData
def machineLearning(filePath):
    return getFileInformation(filePath)

#https://zairon.wordpress.com/2008/02/15/idc-script-and-stack-frame-variables-length/

import idautils
import idaapi
import idc
import struct
import guid

g_vars = {} # Global variables
g_functions_stack = set() # Keep track of function addresses whose stack members were erased

OFFSET_WdfControlDeviceInitAllocate = 0xC8
OFFSET_WdfDeviceInitSetIoIncallerContextCallback = 0x250
OFFSET_WdfDeviceCreateDeviceInterface = 0x268
OFFSET_WdfDeviceCreateSymbolicLink = 0x280
OFFSET_WdfDriverCreate = 0x3a0
OFFSET_WdfIoQueueCreate = 0x4c0
OFFSET_WdfRequestRetrieveInputMemory = 0x858
OFFSET_WdfRequestRetrieveOutputMemory = 0x860
OFFSET_WdfRequestRetrieveInputBuffer = 0x868
OFFSET_WdfRequestRetrieveOutputBuffer = 0x870
OFFSET_WdfRequestRetrieveInputWdmMdl = 0x878
OFFSET_WdfRequestRetrieveOutputWdmMdl = 0x880
OFFSET_WdfRequestRetrieveUnsafeUserInputBuffer = 0x888
OFFSET_WdfRequestRetrieveUnsafeUserOutputBuffer = 0x890


def print_guid(guid):
    data = "GUID("
    part1 = struct.unpack("<I", guid[0:4])[0]
    data += "{:#08x},".format(part1)
    part2 = struct.unpack("<H", guid[4:6])[0]
    data += "{:#04x},".format(part2)
    part3 = struct.unpack("<H", guid[6:8])[0]
    data += "{:#04x},".format(part3)
    data += ",".join(["{:#02x}".format(_) for _ in guid[8:]])
    data += ")"
    data2 = "{"
    data2 += "{:08x}-".format(part1)
    data2 += "{:04x}-".format(part2)
    data2 += "{:04x}-".format(part3)
    part4 = struct.unpack("<H", guid[8:10])[0]
    data2 += "{:04x}-".format(part4)
    data2 += "".join(["{:02x}".format(_) for _ in guid[10:]])
    data2 += "}"
    print(data)
    print(data2)

def function_stack_erased(func_ea):
    if func_ea.startEA in g_functions_stack:
        return True
    return False

def delete_all_function_stack_members(func_ea, force=False):
    if g_vars["ERASE_STACK_MEMBERS"] or force:
        members, base = retrieve_stack_members(func_ea)
        stack_id = idc.GetFrame(func_ea.startEA)
        for k, v in members.items():
            if k != base and "arg_" not in v:
                idc.DelStrucMember(stack_id, k)
        g_functions_stack.add(func_ea.startEA)


# https://gist.github.com/nirizr/fe0ce9948b3db05555da42bbfe0e5a1e
def retrieve_stack_members(func_ea):
    members = {}
    base = None
    frame = idc.GetFrame(func_ea.startEA)
    for frame_member in idautils.StructMembers(frame):
        member_offset, member_name, _ = frame_member
        members[member_offset] = member_name
        if member_name == ' r':
            base = member_offset
    if not base:
        raise ValueError("Failed identifying the stack's base address using the return address hidden stack member")
    return members, base



def get_struct_idx(name):
    for idx in range(1, idc.GetMaxLocalType()):
        if name == idc.GetLocalTypeName(idx):
            return idx
    return None

def get_Tinfo_from_name(name):
    target_idx = 0
    for idx in range(1, idc.GetMaxLocalType()):
        if name in idc.GetLocalTypeName(idx):
            target_idx = idx
            break
    if target_idx != 0:
        #idc.GetLocalType(target_idx,0)
        return idc.GetLocalTinfo(target_idx)
    return None

def get_type_from_name(name):
    target_idx = 0
    for idx in range(1, idc.GetMaxLocalType()):
        if name in idc.GetLocalTypeName(idx):
            target_idx = idx
            break
    if target_idx != 0:
        return idc.GetLocalType(target_idx, 0)
    return None

def get_local_type_idx(name):
    for idx in range(1, idc.GetMaxLocalType()):
        if name in idc.GetLocalTypeName(idx):
            return idx
    return None

def assign_struct_to_address(address, struct_name):
    idc.ApplyType(address, get_Tinfo_from_name(struct_name))
    struct_id = idaapi.get_struc_id(struct_name)
    if struct_id != 0xffffffffffffffff:
        struct_size = idaapi.get_struc_size(struct_id)
        for i in range(struct_size):
            idc.MakeUnkn(address+i, 0)
        return idaapi.doStruct(address, struct_size, struct_id)
    return False

def find_function_arg(addr, mnemonic, operand, idx_operand):
    """
    The function looks backwards to find an specific argument
    :param addr: the address from which to start looking backwards
    :param mnemonic: the instruction mnemonic that we're looking
    :param operand: an operand to compare
    :param idx_operand: the operand idx --> mov ebx, eax -> ebx = idx0; eax = idx1
    :return: the address where the argument is being set
    """
    for _ in range(20): # looks up to 20 instructions behind
        addr = idc.prev_head(addr)
        if idc.print_insn_mnem(addr) == mnemonic and idc.print_operand(addr, idx_operand) == operand:
            return addr
    return None

def find_function_arg_with_operand_value(addr, mnemonic, register, value, idx_operand):
    """
    00000000000167FC mov     [rsp+20h], rax
    idc.get_operand_value(0x167FC, 0) ==> 0x20
    """

    for _ in range(20): # looks up to 20 instructions behind
        addr = idc.prev_head(addr)
        if idc.print_insn_mnem(addr) == mnemonic and register in idc.print_operand(addr, idx_operand)\
                and idc.get_operand_value(addr, idx_operand) == value:
            return addr
    return None


def find_wdf_callback_through_immediate(mnemonic, operand, val):
    for i in range(10):
        addr, operand_ = ida_search.find_imm(ida_ida.inf_get_min_ea(), idc.SEARCH_DOWN|idc.SEARCH_NEXT, val)
        if addr != idc.BADADDR:
            #print hex(addr), idc.GetDisasm(addr), "Operand ", operand_
            if operand_ == operand and idc.print_insn_mnem(addr) == mnemonic:
                return addr
        else:
            break
    return None

"""
    There are three cases:
    1) The driver calls the WDF Function using the WDFFUNCTION struct directly
            INIT:000000000000A129 call    Wdffunctions.pfnWdfCreateDriver

     2) The driver calls the WDF Function in an indirect way
            000000000000A106 mov     rax, cs:WdfFunctions_01015
            INIT:000000000000A122 mov     rax, [rax+3A0h]
            INIT:000000000000A129 call    cs:__guard_dispatch_icall

    3)  000000000002A50B mov     rax, cs:WDFFUNCTIONS
        000000000002A528 call    qword ptr [rax+268h]
"""
def list_xref_to_wdf_callback(function_offset):
    calls_to_pfn_list = []
    try:
        for xref in idautils.XrefsTo(g_vars["_WDFFUNCTIONS"]+function_offset):
            calls_to_pfn_list.append(xref.frm)
    except StopIteration:
        # this is case 2 or 3
        pass
    if len(calls_to_pfn_list) == 0:
        call_pfn = find_wdf_callback_through_immediate("call", 0, function_offset)
        if call_pfn != None:
            calls_to_pfn_list.append(call_pfn)
    if len(calls_to_pfn_list) == 0:
        call_pfn = find_wdf_callback_through_immediate("mov", 1,function_offset)
        if call_pfn != None:
            calls_to_pfn_list.append(call_pfn)
    return calls_to_pfn_list



def find_WdfDeviceInitSetIoInCallerContextCallback():
    function_offset = OFFSET_WdfDeviceInitSetIoIncallerContextCallback
    try:
        call_pfn = next(idautils.XrefsTo(g_vars["_WDFFUNCTIONS"]+function_offset)).frm
    except StopIteration:
        # this is case 2!
        call_pfn = find_wdf_callback_through_immediate("mov", 1,function_offset)
        if call_pfn is None:
            call_pfn = find_wdf_callback_through_immediate("call", 0, function_offset)

    if call_pfn != None:
        idc.OpStroffEx(call_pfn,0,(idaapi.get_struc_id("_WDFFUNCTIONS")),0)
        lea_addr = find_function_arg(call_pfn, "lea", "r8", 0)
        EvtWdfIoInCallerContext = idc.GetOperandValue(lea_addr, 1)
        idc.MakeName(EvtWdfIoInCallerContext, 'EvtWdfIoInCallerContext')



def find_WdfDeviceCreateDeviceInterface():
    function_offset = OFFSET_WdfDeviceCreateDeviceInterface

    calls_to_pfn_list = []
    try:
        for xref in idautils.XrefsTo(g_vars["_WDFFUNCTIONS"]+function_offset):
            call_pfnWdfDeviceCreateDeviceInterface = xref.frm
            calls_to_pfn_list.append(call_pfnWdfDeviceCreateDeviceInterface)
    except StopIteration:
        # this is case 2 or 3
        pass
    if len(calls_to_pfn_list) == 0:
        call_pfnWdfDeviceCreateDeviceInterface = find_wdf_callback_through_immediate("call", 0, function_offset)
        if call_pfnWdfDeviceCreateDeviceInterface:
            calls_to_pfn_list.append(call_pfnWdfDeviceCreateDeviceInterface)
            idc.OpStroffEx(call_pfnWdfDeviceCreateDeviceInterface,0,(idaapi.get_struc_id("_WDFFUNCTIONS")),0)

    if len(calls_to_pfn_list) == 0:
        call_pfnWdfDeviceCreateDeviceInterface = find_wdf_callback_through_immediate("mov", 1,function_offset)
        if call_pfnWdfDeviceCreateDeviceInterface:
            calls_to_pfn_list.append(call_pfnWdfDeviceCreateDeviceInterface)
            idc.OpStroffEx(call_pfnWdfDeviceCreateDeviceInterface,1,(idaapi.get_struc_id("_WDFFUNCTIONS")),0)

    for k, pfn_call in enumerate(calls_to_pfn_list):
        lea_guid = find_function_arg(pfn_call, "lea", "r8", 0)
        interface_guid = idc.GetOperandValue(lea_guid, 1)
        idc.MakeName(interface_guid, '_InterfaceGUID' + str(k))
        assign_struct_to_address(interface_guid, "GUID")
        g_vars["_InterfaceGUID" + str(k)] = interface_guid
        print("_InterfaceGUID: ", hex(interface_guid))
        guid_bytes = idc.GetManyBytes(interface_guid, 0x10)
        print_guid(guid_bytes)


def find_WdfDriverCreate():
    function_offset = OFFSET_WdfDriverCreate

    # If the XREF to wdfFunctions + function_offset exists.. then we're in case 1!
    try:
#        call_pfnWdfDriverCreate = idautils.XrefsTo(g_vars["_WDFFUNCTIONS"]+function_offset).next().frm
        call_pfnWdfDriverCreate = next(idautils.XrefsTo(g_vars["_WDFFUNCTIONS"]+function_offset)).frm
    except StopIteration:
        # this is case 2!
        call_pfnWdfDriverCreate = find_wdf_callback_through_immediate("mov", 1,function_offset)
        if call_pfnWdfDriverCreate != None:
            idc.OpStroffEx(call_pfnWdfDriverCreate,1,(idaapi.get_struc_id("_WDFFUNCTIONS")),0)
        else:
            call_pfnWdfDriverCreate = find_wdf_callback_through_immediate("call", 0, function_offset)
            idc.OpStroffEx(call_pfnWdfDriverCreate,0,(idaapi.get_struc_id("_WDFFUNCTIONS")),0)

    if call_pfnWdfDriverCreate != None:
        # First identify the RealDriverEntry :)
        current_func = idaapi.get_func(call_pfnWdfDriverCreate)
        idc.MakeName(current_func.startEA, "_DriverEntry_")

        argument_DriverConfig_addr = find_function_arg_with_operand_value(call_pfnWdfDriverCreate, "mov", "rsp", 0x20, 0)
        register_DriverConfig = idc.GetOpnd(argument_DriverConfig_addr, 1)
        lea_DriverConfig_addr = find_function_arg(argument_DriverConfig_addr, "lea", register_DriverConfig, 0)

        # Get stack and the stack operand offset
        current_func = idaapi.get_func(lea_DriverConfig_addr)
        stack_id = idc.GetFrame(current_func.startEA)
        opnd = idc.GetOpnd(lea_DriverConfig_addr, 1)
        if "rsp" in opnd:
            stack_member_offset = idc.GetOperandValue(lea_DriverConfig_addr, 1)
        elif "rbp" in opnd:
            var_x = opnd.split("+")[-1][:-1] # [rbp+57h+var_80] -> var_80
            members, _ = retrieve_stack_members(current_func)
            inverted_members = {v:k for k, v in members.items()}
            try:
                stack_member_offset = inverted_members[var_x]
            except KeyError as msg:
                print(msg)
                return

        else:
            print("+] WdfDriverCreate() Unidentified register stack layout")
            return

        #idc.SetMemberName(stack_id, stack_member_offset, "_DriverConfig")
        struct_id = idaapi.get_struc_id("_WDF_DRIVER_CONFIG")
        struct_size = idc.GetStrucSize(struct_id)

        # First check if we have already touch this function stack before
        #if function_stack_erased(current_func):
            # need to take care of the already defined structs
        #    pass
        #else:
        delete_all_function_stack_members(current_func, force=True)
        idc.AddStrucMember(stack_id, "driver_config",
                           stack_member_offset, idc.FF_BYTE|idc.FF_DATA,
                           -1, struct_size)
        idc.SetMemberType(stack_id, stack_member_offset, idc.FF_STRU|idc.FF_DATA, struct_id, 1)


def find_WdfIoQueueCreate():
    function_offset = OFFSET_WdfIoQueueCreate

    calls_to_pfn_list = []
    try:
        for xref in idautils.XrefsTo(g_vars["_WDFFUNCTIONS"]+function_offset):
            call_pfnWdfIoQueueCreate = xref.frm
            calls_to_pfn_list.append(call_pfnWdfIoQueueCreate)
    except StopIteration:
        # this is case 2 or 3
        pass
    if len(calls_to_pfn_list) == 0:
        call_pfnWdfIoQueueCreate = find_wdf_callback_through_immediate("call", 0, function_offset)
        if call_pfnWdfIoQueueCreate:
            calls_to_pfn_list.append(call_pfnWdfIoQueueCreate)
            idc.OpStroffEx(call_pfnWdfIoQueueCreate,0,(idaapi.get_struc_id("_WDFFUNCTIONS")),0)

    if len(calls_to_pfn_list) == 0:
        call_pfnWdfIoQueueCreate = find_wdf_callback_through_immediate("mov", 1,function_offset)
        if call_pfnWdfIoQueueCreate:
            calls_to_pfn_list.append(call_pfnWdfIoQueueCreate)
            idc.OpStroffEx(call_pfnWdfIoQueueCreate,1,(idaapi.get_struc_id("_WDFFUNCTIONS")),0)

    for pfn_call in calls_to_pfn_list:
        lea_argument_addr = find_function_arg(pfn_call, "lea", "r8", 0)

        # Get stack and the stack operand offset
        current_func = idaapi.get_func(lea_argument_addr)
        stack_id = idc.GetFrame(current_func.startEA)
        stack_member_offset = idc.GetOperandValue(lea_argument_addr, 1)

        struct_id = idaapi.get_struc_id("_WDF_IO_QUEUE_CONFIG")
        struct_size = idc.GetStrucSize(struct_id)

        # First check if we have already touch this function stack before
        if function_stack_erased(current_func):
            # need to take care of the already defined structs
            # If the arguments collide then this will fail
            pass
        else:
            delete_all_function_stack_members(current_func)
            print("Erased the stack members")

        idc.AddStrucMember(stack_id, "queue_config",
                           stack_member_offset, idc.FF_BYTE|idc.FF_DATA,
                           -1, struct_size)
        idc.SetMemberType(stack_id, stack_member_offset, idc.FF_STRU|idc.FF_DATA, struct_id, 1)
        print("IOQueue Creation at: " + hex(pfn_call))


def find_WdfControlDeviceInitAllocate():
    function_offset = OFFSET_WdfControlDeviceInitAllocate
    call_pfn = None
    try:
        for xref in idautils.XrefsTo(g_vars["_WDFFUNCTIONS"]+function_offset):
            if xref.frm != None:
                call_pfn = xref.frm
    except StopIteration:
        # this is case 2 or 3
        pass
    if call_pfn is None:
        call_pfn = find_wdf_callback_through_immediate("call", 0, function_offset)
        if call_pfn:
            idc.OpStroffEx(call_pfn,0,(idaapi.get_struc_id("_WDFFUNCTIONS")),0)

    if call_pfn is None:
        call_pfn = find_wdf_callback_through_immediate("mov", 1,function_offset)
        if call_pfn:
            idc.OpStroffEx(call_pfn,1,(idaapi.get_struc_id("_WDFFUNCTIONS")),0)
    if call_pfn is None:
        print("dead")
        return
    lea_sddl = find_function_arg(call_pfn, "lea", "r8", 0)
    unicode_sddl = idc.GetOperandValue(lea_sddl, 1)
    idc.MakeName(unicode_sddl, 'control_device_sddl')
    assign_struct_to_address(unicode_sddl, "_UNICODE_STRING")
    print("Control Device SDDL at: ", hex(unicode_sddl))



def assign_kmdf_structure_types(address):
    # Get the jmp to de import
    jmp_import_ea = next(idautils.XrefsTo(address)).frm
    # There is only one XREF to WdfVersionBind
    call_wdfVersionBind = next(idautils.XrefsTo(jmp_import_ea)).frm
    print(hex(call_wdfVersionBind))
    argument_WdfBindInfo = find_function_arg(call_wdfVersionBind, "lea", "r8", 0)
    if argument_WdfBindInfo is None:
        print("Error: Argument WdfBindInfo wasn't found!")
        return
    wdfBindInfo = idc.GetOperandValue(argument_WdfBindInfo, 1)
    idc.MakeName(wdfBindInfo, '_WdfBindInfo')
    print("WdfBindInfo Struct: ", hex(wdfBindInfo))
    if not assign_struct_to_address(wdfBindInfo, "_WDF_BIND_INFO"):
        print("The _WDF_BIND_INFO struct wasn't found in the database")
        return
    g_vars["_WDF_BIND_INFO"] = wdfBindInfo

    # Assign ComponentGlobals Name
    argument_WdfComponentGlobals = find_function_arg(call_wdfVersionBind, "lea", "r9", 0)
    wdfComponentGlobals = idc.GetOperandValue(argument_WdfComponentGlobals, 1)
    g_vars["_WDF_COMPONENT_GLOBALS"] = wdfComponentGlobals
    idc.SetType(wdfComponentGlobals, 'PWDF_DRIVER_GLOBALS')
    idc.MakeName(wdfComponentGlobals, '_WdfComponentGlobals')

    # Now assign the WDFFUNCTIONS to FuncTable
    wdfFunctions = idc.Qword(wdfBindInfo+0x20)
    g_vars["_WDFFUNCTIONS"] = wdfFunctions

    # get wdf version
    version = idc.Dword(wdfBindInfo + 0x14)
    print('WDF minor version ' + str(version))

    def get_wdffunctions_struct_name(version):
        name = '_WDFFUNCTIONS_V100'

        if version >= 5 and version < 9:
             name = '_WDFFUNCTIONS_V105'
        elif version >= 9 and version < 11:
            name = '_WDFFUNCTIONS_V109'
        elif version >= 11 and version < 13:
            name = '_WDFFUNCTIONS_V111'
        elif version >= 13 and version < 15:
            name = '_WDFFUNCTIONS_V113'
        elif version >= 15 and version < 19:
            name = '_WDFFUNCTIONS_V115'
        elif version >= 19 and version < 21:
            name = '_WDFFUNCTIONS_V119'
        elif version >= 21 and version < 23:
            name = '_WDFFUNCTIONS_V121'
        elif version >= 23 and version < 25:
            name = '_WDFFUNCTIONS_V123'
        elif version >= 25 and version < 31:
            name = '_WDFFUNCTIONS_V125'
        elif version >= 31:
            name = '_WDFFUNCTIONS_V131'

        return name

    struct_name = get_wdffunctions_struct_name(version)

    if version < 15:
        assign_struct_to_address(wdfFunctions, struct_name)
    else:
        idc.SetType(wdfFunctions, struct_name + ' *')

    idc.MakeName(wdfFunctions, 'g_WdfF_Functions')
    #if not assign_struct_to_address(wdfFunctions, "_WDFFUNCTIONS"):
    #    print("The _WDFFUNCTIONS struct wasn't found in the database")
    #    return

    print('Applied type %s to g_WdfF_Functions' % struct_name)

# Callback to get the EA of WdfVersionBind
def imp_cb(ea, name, ord):
    if not name:
        print("%08x: ord#%d" % (ea, ord))
    else:
        print("%08x: %s (ord#%d)" % (ea, name, ord))
    if name == "WdfVersionBind":
        assign_kmdf_structure_types(ea)
        return False
    # True -> Continue enumeration
    # False -> Stop enumeration
    return True

##############################################################################

def load_kmdf_types_into_idb():
    header_path = idautils.GetIdbDir()
    # change relative path to use more easily
    print("".join([header_path, "WDFStructsV2.h"]))
    print(__file__+"../WDFStructsV2.h")
    idaapi.idc_parse_types("".join([__file__, "/../WDFStructsV2.h"]), idc.PT_FILE)
    for idx in range(1, idc.GetMaxLocalType()):
        print(idx, idc.GetLocalTypeName(idx))
        idc.Til2Idb(idx, idc.GetLocalTypeName(idx))

##############################################################################


##############################################################################

load_kmdf_types_into_idb()
for module_idx in range(idaapi.get_import_module_qty()):
    if idaapi.get_import_module_name(module_idx) == "WDFLDR":
        idaapi.enum_import_names(module_idx, imp_cb)

if len(list_xref_to_wdf_callback(OFFSET_WdfDeviceCreateDeviceInterface)) == 0:
    print("The driver is not exposing any DeviceInterface")
if len(list_xref_to_wdf_callback(OFFSET_WdfDeviceCreateSymbolicLink)) == 0:
    print("The driver is not creating a Symbolic Link")
if len(list_xref_to_wdf_callback(OFFSET_WdfIoQueueCreate)) == 0:
    print("The driver is not creating an IOQueue")
if len(list_xref_to_wdf_callback(OFFSET_WdfDeviceInitSetIoIncallerContextCallback)) == 0:
    print("The driver is not setting an EvtInCallerContextCallback")
for i in list_xref_to_wdf_callback(OFFSET_WdfIoQueueCreate):
    print("Call To WdfIoQueueCreate: " + hex(i))
for i in list_xref_to_wdf_callback(OFFSET_WdfRequestRetrieveInputMemory):
    print("Call To WdfRequestRetrieveInputMemory: " + hex(i))
for i in list_xref_to_wdf_callback(OFFSET_WdfRequestRetrieveOutputMemory):
    print("Call To WdfRequestRetrieveOutputMemory: " + hex(i))
for i in list_xref_to_wdf_callback(OFFSET_WdfRequestRetrieveInputBuffer):
    print("Call To WdfRequestRetrieveInputBuffer: " + hex(i))
for i in list_xref_to_wdf_callback(OFFSET_WdfRequestRetrieveOutputBuffer):
    print("Call To WdfRequestRetrieveOutputBuffer: " + hex(i))
for i in list_xref_to_wdf_callback(OFFSET_WdfRequestRetrieveInputWdmMdl):
    print("Call To WdfRequestRetrieveInputWdmMdl: " + hex(i))
for i in list_xref_to_wdf_callback(OFFSET_WdfRequestRetrieveOutputWdmMdl):
    print("Call To WdfRequestRetrieveOutputWdmMdl: " + hex(i))
for i in list_xref_to_wdf_callback(OFFSET_WdfRequestRetrieveUnsafeUserInputBuffer):
    print("Call To WdfRequestRetrieveUnsafeUserInputBuffer: " + hex(i))
for i in list_xref_to_wdf_callback(OFFSET_WdfRequestRetrieveUnsafeUserOutputBuffer):
    print("Call To WdfRequestRetrieveUnsafeUserOutputBuffer: " + hex(i))


def supress_exception(cb):
    try:
#    if True:
        cb()
    except Exception as e:
        print(e)
#        pass

g_vars["ERASE_STACK_MEMBERS"] = True

supress_exception(find_WdfDriverCreate)
supress_exception(find_WdfIoQueueCreate)
supress_exception(find_WdfDeviceInitSetIoInCallerContextCallback)
supress_exception(find_WdfDeviceCreateDeviceInterface)
supress_exception(find_WdfControlDeviceInitAllocate)







"""
# 00000000167ED lea     r8, [rbp+190h+var_170]

lea_addr = 0x167ED
# Get the stack struct
current_func = idaapi.get_func(lea_addr)
stack_id = idc.GetFrame(current_func)
stack_struc = idaapi.get_struc(stack_id)

# Get the stack operand offset value and stack member
stack_member_offset = idc.GetOperandValue(lea_addr, 1)
stack_member = stack_struc.get_member(stack_member_offset)

target_struct_id = idaapi.get_struc_id("_WDF_DRIVER_CONFIG")
target_struc = idaapi.get_struc(target_struct_id )

idc.DelStrucMember(stack_id, stack_member_offset)
AddStrucMember(stack_id, "driver_config", stack_member_offset, FF_BYTE|FF_DATA, -1, GetStrucSize(target_struct_id))
idc.SetMemberType(stack_id, stack_member_offset, idc.FF_STRU|idc.FF_DATA, target_struct_id, 1)


idc.SetMemberType(stack_id, stack_member_offset, idc.FF_BYTE|idc.FF_DATA, target_struct_id, 0x20)

set_member_tinfo(None, stack_struc ,stack_member ,0, target_struc, 0, 0)



tinfo = idaapi.tinfo_t()
idaapi.parse_decl2(idaapi.cvar.idati, '_WDF_DRIVER_CONFIG;', '_WDF_DRIVER_CONFIG', tinfo, idaapi.PT_TYP)
idaapi.set_member_tinfo2(stack_struc, stack_member, 0, tinfo, idaapi.SET_MEMTI_COMPATIBLE)

"""

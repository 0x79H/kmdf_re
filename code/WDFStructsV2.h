
/*
In KMDF, the first parameter into the pfnWdfCallbacks is the WdfDriverGlobals object (goes in RCX), so when we say:

NTSTATUS pfnWdfDriverCreate(PDRIVER_OBJECT DriverObject, PCUNICODE_STRING RegistryPath, PVOID DriverAttributes, PWDF_DRIVER_CONFIG DriverConfig, PVOID WdfDriver);

WdfDriverGlobals goes in RCX
DriverObject goes in RDX
RegistryPath goes in R8
and so on


This doesn't apply to Evt*Routines like EvtIoDeviceControl.
*/

enum _MAJOR_FUNCTIONS {
	 DispatchCreate,
   DispatchCreateNamedPipe,
	 DispatchCLose,
	 DispatchRead,
	 DispatchWrite,
	 DispatchQueryInformation,
	 DispatchSetInformation,
	 DispatchQueryEA,
	 DispatchSetEA,
	 DispatchFlushBuffers,
	 DispatchQueryVolumeInformation,
	 DispatchSetVolumeInformation,
	 DispatchDirectoryControl,
	 DispatchFileSystemControl,
	 DispatchDeviceIOControl,
	 DispatchInternalDeviceControl,
	 DispatchShutdown,
	 DispatchLockControl,
	 DispatchCleanup,
	 DispatchCreateMailslot,
	 DispatchQuerySecurity,
	 DispatchSetSecurity,
	 DispatchPower,
	 DispatchSystemControl,
	 DispatchDeviceChange,
	 DispatchQueryQuota,
	 DispatchSetQuota,
	 DispatchPNP,
};

typedef _MAJOR_FUNCTIONS MAJOR_FUNCTIONS;

struct _DRIVER_OBJECT
{
  SHORT Type;
  SHORT Size;
  PVOID DeviceObject;
  ULONG Flags;
  PVOID DriverStart;
  ULONG DriverSize;
  PVOID DriverSection;
  PVOID DriverExtension;
  UNICODE_STRING DriverName;
  PUNICODE_STRING HardwareDatabase;
  PVOID FastIoDispatch;
  PVOID DriverInit;
  PVOID DriverStartIo;
  PVOID DriverUnload;
  PVOID DispatchCreate;
  PVOID DispatchCreateNamedPipe;
  PVOID DispatchClose;
  PVOID DispatchRead;
  PVOID DispatchWrite;
  PVOID DispatchQueryInformation;
  PVOID DispatchSetInformation;
  PVOID DispatchQueryEA;
  PVOID DispatchSetEA;
  PVOID DispatchFlushBuffers;
  PVOID DispatchQueryVolumeInformation;
  PVOID DispatchSetVolumeInformation;
  PVOID DispatchDirectoryControl;
  PVOID DispatchFileSystemControl;
  PVOID DispatchDeviceIOControl;
  PVOID DispatchInternalDeviceControl;
  PVOID DispatchShutdown;
  PVOID DispatchLockControl;
  PVOID DispatchCleanup;
  PVOID DispatchCreateMailslot;
  PVOID DispatchQuerySecurity;
  PVOID DispatchSetSecurity;
  PVOID DispatchPower;
  PVOID DispatchSystemControl;
  PVOID DispatchDeviceChange;
  PVOID DispatchQueryQuota;
  PVOID DispatchSetQuota;
  PVOID DispatchPNP;
};

typedef _DRIVER_OBJECT DRIVER_OBJECT;
typedef _DRIVER_OBJECT * PDRIVER_OBJECT;

typedef void * PVPB;
typedef unsigned short DEVICE_TYPE;

struct _DEVICE_OBJECT {
  CSHORT                   Type;
  USHORT                   Size;
  LONG                     ReferenceCount;
  struct _DRIVER_OBJECT    *DriverObject;
  struct _DEVICE_OBJECT    *NextDevice;
  struct _DEVICE_OBJECT    *AttachedDevice;
  struct _IRP              *CurrentIrp;
  PIO_TIMER                Timer;
  ULONG                    Flags;
  ULONG                    Characteristics;
  volatile PVPB            Vpb;
  PVOID                    DeviceExtension;
  DEVICE_TYPE              DeviceType;
  CCHAR                    StackSize;
  union {
    LIST_ENTRY         ListEntry;
    WAIT_CONTEXT_BLOCK Wcb;
  } Queue;
  ULONG                    AlignmentRequirement;
  KDEVICE_QUEUE            DeviceQueue;
  KDPC                     Dpc;
  ULONG                    ActiveThreadCount;
  PSECURITY_DESCRIPTOR     SecurityDescriptor;
  KEVENT                   DeviceLock;
  USHORT                   SectorSize;
  USHORT                   Spare1;
  struct _DEVOBJ_EXTENSION *DeviceObjectExtension;
  PVOID                    Reserved;
};

typedef _DEVICE_OBJECT DEVICE_OBJECT;
typedef _DEVICE_OBJECT * PDEVICE_OBJECT;

struct _IO_STACK_LOCATION {
  UCHAR MajorFunction;
  UCHAR MinorFunction;
  UCHAR Flags;
  UCHAR Control;
  PVOID OutputBufferLength;
  PVOID InputBufferLength;
  DWORD IOControlCode;
  PVOID Type3InputBuffer;
  PVOID DeviceObject;
  PVOID FileObject;
  PVOID CompletionRoutine;
  PVOID Context;
};

typedef _IO_STACK_LOCATION IO_STACK_LOCATION;
typedef _IO_STACK_LOCATION * PIO_STACK_LOCATION;

enum _DEVICE_REGISTRY_PROPERTY {
  DevicePropertyDeviceDescription            = 0x0,
  DevicePropertyHardwareID                   = 0x1,
  DevicePropertyCompatibleIDs                = 0x2,
  DevicePropertyBootConfiguration            = 0x3,
  DevicePropertyBootConfigurationTranslated  = 0x4,
  DevicePropertyClassName                    = 0x5,
  DevicePropertyClassGuid                    = 0x6,
  DevicePropertyDriverKeyName                = 0x7,
  DevicePropertyManufacturer                 = 0x8,
  DevicePropertyFriendlyName                 = 0x9,
  DevicePropertyLocationInformation          = 0xa,
  DevicePropertyPhysicalDeviceObjectName     = 0xb,
  DevicePropertyBusTypeGuid                  = 0xc,
  DevicePropertyLegacyBusType                = 0xd,
  DevicePropertyBusNumber                    = 0xe,
  DevicePropertyEnumeratorName               = 0xf,
  DevicePropertyAddress                      = 0x10,
  DevicePropertyUINumber                     = 0x11,
  DevicePropertyInstallState                 = 0x12,
  DevicePropertyRemovalPolicy                = 0x13,
  DevicePropertyResourceRequirements         = 0x14,
  DevicePropertyAllocatedResources           = 0x15,
  DevicePropertyContainerID                  = 0x16
};

typedef _DEVICE_REGISTRY_PROPERTY DEVICE_REGISTRY_PROPERTY;

struct _WDF_VERSION {
  UINT  Major;
  UINT  Minor;
  UINT  Build;
};

typedef _WDF_VERSION WDF_VERSION;

struct _WDF_BIND_INFO {
	ULONG             Size;
	PWCHAR            Component;
	WDF_VERSION       Version;
	ULONG             FuncCount;
	PVOID 			      FuncTable;
	PVOID             Module;     // Mgmt and diagnostic use only
};

typedef _WDF_BIND_INFO WDF_BIND_INFO;
typedef _WDF_BIND_INFO * PWDF_BIND_INFO;

/*
WdfVersionBind(
    __in    PDRIVER_OBJECT DriverObject,
    __in    PUNICODE_STRING RegistryPath,
    __inout PWDF_BIND_INFO BindInfo,
    __out   PWDF_COMPONENT_GLOBALS* ComponentGlobals
);
*/

struct _WDF_PNPPOWER_EVENT_CALLBACKS {
  ULONG                         Size;
  PVOID                         EvtDeviceD0Entry;
  PVOID                         EvtDeviceD0EntryPostInterruptsEnabled;
  PVOID                         EvtDeviceD0Exit;
  PVOID                         EvtDeviceD0ExitPreInterruptsDisabled;
  PVOID                         EvtDevicePrepareHardware;
  PVOID                         EvtDeviceReleaseHardware;
  PVOID                         EvtDeviceSelfManagedIoCleanup;
  PVOID                         EvtDeviceSelfManagedIoFlush;
  PVOID                         EvtDeviceSelfManagedIoInit;
  PVOID                         EvtDeviceSelfManagedIoSuspend;
  PVOID                         EvtDeviceSelfManagedIoRestart;
  PVOID                         EvtDeviceSurpriseRemoval;
  PVOID                         EvtDeviceQueryRemove;
  PVOID                         EvtDeviceQueryStop;
  PVOID                         EvtDeviceUsageNotification;
  PVOID                         EvtDeviceRelationsQuery;
  PVOID                         EvtDeviceUsageNotificationEx;
};

typedef _WDF_PNPPOWER_EVENT_CALLBACKS WDF_PNPPOWER_EVENT_CALLBACKS;
typedef _WDF_PNPPOWER_EVENT_CALLBACKS PWDF_PNPPOWER_EVENT_CALLBACKS;

/*
NTSTATUS EvtWdfDevicePrepareHardware(
  WDFDEVICE Device,
  WDFCMRESLIST ResourcesRaw,
  WDFCMRESLIST ResourcesTranslated
)

The EvtDevicePrepareHardware callback function accesses the device's raw and translated hardware resources by using the ResourcesRaw and ResourcesTranslated handles that it receives. The callback function can call WdfCmResourceListGetCount and WdfCmResourceListGetDescriptor to traverse the resource lists. This callback function cannot modify the resource lists.

For more information about resource lists and the order in which the resources appear, see raw and translated hardware resources.

Typically, your driver's EvtDevicePrepareHardware callback function does the following, if necessary:

- Maps physical memory addresses to virtual addresses so the driver can access memory that is assigned to the device
- Determines the device's revision number
- Configures USB devices
- Obtains driver-defined interfaces from other drivers

Optionally, EvtDevicePrepareHardware callback function might queue a work item to complete any other time-intensive configuration tasks.
*/


// pfnWdfDeviceInitSetPnpPowerEventCallbacks

struct _WDF_DRIVER_CONFIG {
  ULONG Size;
  PVOID EvtDriverDeviceAdd;
  PVOID EvtDriverUnload;
  ULONG DriverInitFlags;
  ULONG DriverPoolTag;
};

typedef _WDF_DRIVER_CONFIG WDF_DRIVER_CONFIG;
typedef _WDF_DRIVER_CONFIG * PWDF_DRIVER_CONFIG;

enum _WDF_SYNCHRONIZATION_SCOPE {
  WdfSynchronizationScopeInvalid            = 0x00,
  WdfSynchronizationScopeInheritFromParent  = 0x1,
  WdfSynchronizationScopeDevice             = 0x2,
  WdfSynchronizationScopeQueue              = 0x3,
  WdfSynchronizationScopeNone               = 0x4
};

typedef _WDF_SYNCHRONIZATION_SCOPE WDF_SYNCHRONIZATION_SCOPE;

enum _WDF_EXECUTION_LEVEL {
  WdfExecutionLevelInvalid            = 0x00,
  WdfExecutionLevelInheritFromParent  = 0x1,
  WdfExecutionLevelPassive            = 0x2,
  WdfExecutionLevelDispatch           = 0x3
};

typedef _WDF_EXECUTION_LEVEL WDF_EXECUTION_LEVEL;

struct _WDF_OBJECT_CONTEXT_TYPE_INFO {
  ULONG                          Size;
  PCHAR                          ContextName;
  UINT                         ContextSize;
  PVOID UniqueType;
  PVOID    EvtDriverGetUniqueContextType;
};

typedef _WDF_OBJECT_CONTEXT_TYPE_INFO WDF_OBJECT_CONTEXT_TYPE_INFO;
typedef _WDF_OBJECT_CONTEXT_TYPE_INFO * PWDF_OBJECT_CONTEXT_TYPE_INFO;

struct _WDF_OBJECT_ATTRIBUTES {
  ULONG                          Size;
  PVOID EvtCleanupCallback;
  PVOID EvtDestroyCallback;
  WDF_EXECUTION_LEVEL            ExecutionLevel;
  WDF_SYNCHRONIZATION_SCOPE      SynchronizationScope;
  HANDLE                      ParentObject;
  UINT                         ContextSizeOverride;
  PWDF_OBJECT_CONTEXT_TYPE_INFO ContextTypeInfo;
};

typedef _WDF_OBJECT_ATTRIBUTES WDF_OBJECT_ATTRIBUTES;
typedef _WDF_OBJECT_ATTRIBUTES * PWDF_OBJECT_ATTRIBUTES;

/*
pfnWdfObjectGetTypedContextWorker() -> receives a handle in RDX and returns a pointer into the private object context
*/

/*
NTSTATUS WdfIoQueueCreate(
        WDFDEVICE              Device,
        PWDF_IO_QUEUE_CONFIG   Config,
    PWDF_OBJECT_ATTRIBUTES QueueAttributes,
   WDFQUEUE               *Queue
);

void EvtWdfIoQueueIoDeviceControl(
  WDFQUEUE Queue,
  WDFREQUEST Request,
  UINT OutputBufferLength,
  UINT InputBufferLength,
  ULONG IoControlCode
)

void EvtWdfIoQueueIoDeviceControl(
  PVOID Queue,
  PVOID Request,
  UINT OutputBufferLength,
  UINT InputBufferLength,
  ULONG IoControlCode
)


void EvtWdfIoQueueIoRead(
  WDFQUEUE Queue,
  WDFREQUEST Request,
  size_t Length
)

void EvtWdfIoQueueIoWrite(
  WDFQUEUE Queue,
  WDFREQUEST Request,
  size_t Length
)

void EvtWdfIoQueueIoInternalDeviceControl(
  WDFQUEUE Queue,
  WDFREQUEST Request,
  size_t OutputBufferLength,
  size_t InputBufferLength,
  ULONG IoControlCode
)
*/

enum _WDF_DEVICE_IO_TYPE {
  WdfDeviceIoUndefined         = 0,
  WdfDeviceIoNeither           = 1,
  WdfDeviceIoBuffered          = 2,
  WdfDeviceIoDirect            = 3,
  WdfDeviceIoBufferedOrDirect  = 4
};

typedef _WDF_DEVICE_IO_TYPE WDF_DEVICE_IO_TYPE;
typedef _WDF_DEVICE_IO_TYPE * PWDF_DEVICE_IO_TYPE;

enum _WDF_IO_QUEUE_DISPATCH_TYPE {
  WdfIoQueueDispatchInvalid     = 0,
  WdfIoQueueDispatchSequential  = 1,
  WdfIoQueueDispatchParallel    = 2,
  WdfIoQueueDispatchManual      = 3,
  WdfIoQueueDispatchMax         = 4
};

typedef _WDF_IO_QUEUE_DISPATCH_TYPE WDF_IO_QUEUE_DISPATCH_TYPE;

enum _WDF_TRI_STATE {
  WdfFalse       = FALSE,
  WdfTrue        = TRUE,
  WdfUseDefault  = 2
};

typedef _WDF_TRI_STATE WDF_TRI_STATE;
typedef _WDF_TRI_STATE * PWDF_TRI_STATE;

struct _WDF_IO_QUEUE_CONFIG {
  ULONG Size;
  WDF_IO_QUEUE_DISPATCH_TYPE DispatchType;
  WDF_TRI_STATE PowerManaged;
  BOOLEAN AllowZeroLengthRequests;
  BOOLEAN DefaultQueue;
  PVOID EvtIoDefault;
  PVOID EvtIoRead;
  PVOID EvtIoWrite;
  PVOID EvtIoDeviceControl;
  PVOID EvtIoInternalDeviceControl;
  PVOID EvtIoStop;
  PVOID EvtIoResume;
  PVOID EvtIoCanceledOnQueue;
  union {
    struct {
      ULONG NumberOfPresentedRequests;
    } Parallel;
  } Settings;
  HANDLE Driver;
};

typedef _WDF_IO_QUEUE_CONFIG WDF_IO_QUEUE_CONFIG;
typedef _WDF_IO_QUEUE_CONFIG * PWDF_IO_QUEUE_CONFIG;

/*
VOID WdfDeviceInitSetFileObjectConfig(
       PWDFDEVICE_INIT        DeviceInit,
       PWDF_FILEOBJECT_CONFIG FileObjectConfig,
   PWDF_OBJECT_ATTRIBUTES FileObjectAttributes
);
*/

enum _WDF_FILEOBJECT_CLASS {
  WdfFileObjectInvalid                 = 0,
  WdfFileObjectNotRequired             = 1,
  WdfFileObjectWdfCanUseFsContext      = 2,
  WdfFileObjectWdfCanUseFsContext2     = 3,
  WdfFileObjectWdfCannotUseFsContexts  = 4,
  WdfFileObjectCanBeOptional           = 0x80000000
};

typedef _WDF_FILEOBJECT_CLASS WDF_FILEOBJECT_CLASS;
typedef _WDF_FILEOBJECT_CLASS * PWDF_FILEOBJECT_CLASS;

struct _WDF_FILEOBJECT_CONFIG {
  ULONG Size;
  PVOID EvtDeviceFileCreate;
  PVOID EvtFileClose;
  PVOID EvtFileCleanup;
  WDF_TRI_STATE AutoForwardCleanupClose;
  WDF_FILEOBJECT_CLASS FileObjectClass;
};

typedef _WDF_FILEOBJECT_CONFIG WDF_FILEOBJECT_CONFIG;
typedef _WDF_FILEOBJECT_CONFIG * PWDF_FILEOBJECT_CONFIG;

/*
NTSTATUS WdfRequestRetrieveInputBuffer(
        WDFREQUEST Request,
        size_t     MinimumRequiredSize,
       PVOID      *Buffer,
   size_t     *Length
);
*/

/*
WDF Request buffers (input and output) are hold in a structure like the follows
*/
struct _BuffRequest {
	PVOID InputBuffer;
	PVOID OutputBuffer;
	DWORD64 InputBuffLen;
	DWORD64 OutputBuffLen;
};

typedef _BuffRequest BuffRequest;
typedef _BuffRequest * PBuffRequest;


enum _WDF_REQUEST_TYPE {
  WdfRequestTypeCreate                  = 0x0,
  WdfRequestTypeCreateNamedPipe         = 0x1,
  WdfRequestTypeClose                   = 0x2,
  WdfRequestTypeRead                    = 0x3,
  WdfRequestTypeWrite                   = 0x4,
  WdfRequestTypeQueryInformation        = 0x5,
  WdfRequestTypeSetInformation          = 0x6,
  WdfRequestTypeQueryEA                 = 0x7,
  WdfRequestTypeSetEA                   = 0x8,
  WdfRequestTypeFlushBuffers            = 0x9,
  WdfRequestTypeQueryVolumeInformation  = 0xa,
  WdfRequestTypeSetVolumeInformation    = 0xb,
  WdfRequestTypeDirectoryControl        = 0xc,
  WdfRequestTypeFileSystemControl       = 0xd,
  WdfRequestTypeDeviceControl           = 0xe,
  WdfRequestTypeDeviceControlInternal   = 0xf,
  WdfRequestTypeShutdown                = 0x10,
  WdfRequestTypeLockControl             = 0x11,
  WdfRequestTypeCleanup                 = 0x12,
  WdfRequestTypeCreateMailSlot          = 0x13,
  WdfRequestTypeQuerySecurity           = 0x14,
  WdfRequestTypeSetSecurity             = 0x15,
  WdfRequestTypePower                   = 0x16,
  WdfRequestTypeSystemControl           = 0x17,
  WdfRequestTypeDeviceChange            = 0x18,
  WdfRequestTypeQueryQuota              = 0x19,
  WdfRequestTypeSetQuota                = 0x1A,
  WdfRequestTypePnp                     = 0x1B,
  WdfRequestTypeOther                   = 0x1C,
  WdfRequestTypeUsb                     = 0x40,
  WdfRequestTypeNoFormat                = 0xFF,
  WdfRequestTypeMax                     = 0x100
};

typedef _WDF_REQUEST_TYPE WDF_REQUEST_TYPE;


/*
WDF_REQUEST_PARAMETERS  requestParameters;

// Get the Request parameters
WDF_REQUEST_PARAMETERS_INIT(&requestParameters);
WdfRequestGetParameters(Request, &requestParameters);
*/

struct _WDF_REQUEST_PARAMETERS {
  USHORT Size;
  UCHAR MinorFunction;
  WDF_REQUEST_TYPE Type;
  union {
    struct {
      PVOID SecurityContext;
      ULONG Options;
      UINT64 FileAttributes;
      USHORT ShareAccess;
      UINT64 EaLength;
    } Create;
    struct {
      UINT Length;
      UINT64 Key;
      UINT64 DeviceOffset;
    } Read;
    struct {
      UINT Length;
      UINT64 Key;
      LONGLONG DeviceOffset;
    } Write;
    struct {
      UINT OutputBufferLength;
      UINT64 InputBufferLength;
      UINT64 IoControlCode;
      PVOID Type3InputBuffer;
    } DeviceIoControl;
    struct {
      PVOID Arg1;
      PVOID Arg2;
      UINT64 IoControlCode;
      PVOID Arg4;
    } Others;
  } Parameters;
};

typedef _WDF_REQUEST_PARAMETERS WDF_REQUEST_PARAMETERS;
typedef _WDF_REQUEST_PARAMETERS * PWDF_REQUEST_PARAMETERS;



/*
NTSTATUS WdfDeviceAddQueryInterface(
   WDFDEVICE                   Device,
   PWDF_QUERY_INTERFACE_CONFIG InterfaceConfig
);
*/

struct _INTERFACE {
  USHORT Size;
  USHORT Version;
  PVOID Context;
  PVOID InterfaceReference;
  PVOID InterfaceDereference;
};

typedef _INTERFACE INTERFACE;
typedef _INTERFACE * PINTERFACE;

struct _WDF_QUERY_INTERFACE_CONFIG {
  ULONG Size;
  PINTERFACE Interface;
  PVOID GUIDInterfaceType;
  BOOLEAN SendQueryToParentStack;
  PVOID EvtDeviceProcessQueryInterfaceRequest;
  BOOLEAN ImportInterface;
};

typedef _WDF_QUERY_INTERFACE_CONFIG WDF_QUERY_INTERFACE_CONFIG;
typedef _WDF_QUERY_INTERFACE_CONFIG * PWDF_QUERY_INTERFACE_CONFIG;

struct _WDF_WORKITEM_CONFIG {
  ULONG Size;
  PVOID EvtWorkItemFunc;
  BOOLEAN AutomaticSerialization;
};

typedef _WDF_WORKITEM_CONFIG WDF_WORKITEM_CONFIG;
typedef _WDF_WORKITEM_CONFIG * PWDF_WORKITEM_CONFIG;

/*
NTSTATUS WdfWorkItemCreate(
    PWDF_WORKITEM_CONFIG   Config,
    PWDF_OBJECT_ATTRIBUTES Attributes,
   WDFWORKITEM            *WorkItem
);

*/

/*
IO Targets:

A WDF driver can forward an I/O request or create and send a new request to another driver, called an I/O target.

The framework initializes a driver's local I/O target for a device when the driver calls WdfDeviceCreate. To retrieve a handle to a device's local I/O target, the driver calls WdfDeviceGetIoTarget.

NTSTATUS WdfDeviceCreate(
  PWDFDEVICE_INIT        *DeviceInit,
  PWDF_OBJECT_ATTRIBUTES DeviceAttributes,
  WDFDEVICE              *Device
);


Most drivers send requests only to their local I/O target.

To initialize a remote I/O target for a device, the driver must:
 1) Call WdfIoTargetCreate to create an I/O target object.
 2) Call WdfIoTargetOpen to open an I/O target so that the driver can send requests to it.


When the driver calls WdfIoTargetOpen, it typically identifies the remote I/O target by supplying a Unicode string that represents an object name. This name can identify a device, file, or device interface.

The framework sends I/O requests to the top of the driver stack that supports the object name.



NTSTATUS WdfIoTargetOpen(
   WDFIOTARGET                IoTarget,
   PWDF_IO_TARGET_OPEN_PARAMS OpenParams
);
*/


enum _WDF_IO_TARGET_OPEN_TYPE {
  WdfIoTargetOpenUndefined          = 0,
  WdfIoTargetOpenUseExistingDevice  = 1,
  WdfIoTargetOpenByName             = 2,
  WdfIoTargetOpenReopen             = 3,
  WdfIoTargetOpenLocalTargetByFile  = 4
};

typedef _WDF_IO_TARGET_OPEN_TYPE WDF_IO_TARGET_OPEN_TYPE;

struct _WDF_IO_TARGET_OPEN_PARAMS {
  ULONG Size;
  WDF_IO_TARGET_OPEN_TYPE Type;
  PVOID EvtIoTargetQueryRemove;
  PVOID EvtIoTargetRemoveCanceled;
  PVOID EvtIoTargetRemoveComplete;
  PDEVICE_OBJECT TargetDeviceObject;
  PVOID TargetFileObject;
  UNICODE_STRING TargetDeviceName;
  DWORD DesiredAccess;
  ULONG ShareAccess;
  ULONG FileAttributes;
  ULONG CreateDisposition;
  ULONG CreateOptions;
  PVOID EaBuffer;
  ULONG EaBufferLength;
  PVOID AllocationSize;
  ULONG FileInformation;
  UNICODE_STRING FileName;
};

typedef _WDF_IO_TARGET_OPEN_PARAMS WDF_IO_TARGET_OPEN_PARAMS;
typedef _WDF_IO_TARGET_OPEN_PARAMS * PWDF_IO_TARGET_OPEN_PARAMS;

struct _WDF_INTERRUPT_CONFIG {
  ULONG Size;
  PVOID SpinLock;
  WDF_TRI_STATE ShareVector;
  BOOLEAN FloatingSave;
  BOOLEAN AutomaticSerialization;
  PVOID EvtInterruptIsr;
  PVOID EvtInterruptDpc;
  PVOID EvtInterruptEnable;
  PVOID EvtInterruptDisable;
  PVOID EvtInterruptWorkItem;
  PVOID InterruptRaw;
  PVOID InterruptTranslated;
  PVOID WaitLock;
  BOOLEAN PassiveHandling;
  WDF_TRI_STATE ReportInactiveOnPowerDown;
  BOOLEAN CanWakeDevice;
};

typedef _WDF_INTERRUPT_CONFIG WDF_INTERRUPT_CONFIG;
typedef _WDF_INTERRUPT_CONFIG * PWDF_INTERRUPT_CONFIG;

/*
NTSTATUS WdfInterruptCreate(
       WDFDEVICE              Device,
       PWDF_INTERRUPT_CONFIG  Configuration,
   PWDF_OBJECT_ATTRIBUTES Attributes,
      WDFINTERRUPT           *Interrupt
);
*/


/*
The WdfFdoInitSetDefaultChildListConfig method configures a bus driver's default child list.

VOID WdfFdoInitSetDefaultChildListConfig(
  _Inout_  PWDFDEVICE_INIT        DeviceInit,
       PWDF_CHILD_LIST_CONFIG Config,
   PWDF_OBJECT_ATTRIBUTES DefaultChildListAttributes
);
*/

struct _WDF_CHILD_LIST_CONFIG {
  ULONG Size;
  ULONG IdentificationDescriptionSize;
  ULONG AddressDescriptionSize;
  PVOID EvtChildListCreateDevice;
  PVOID EvtChildListScanForChildren;
  PVOID EvtChildListIdentificationDescriptionCopy;
  PVOID EvtChildListIdentificationDescriptionDuplicate;
  PVOID EvtChildListIdentificationDescriptionCleanup;
  PVOID EvtChildListIdentificationDescriptionCompare;
  PVOID EvtChildListAddressDescriptionCopy;
  PVOID EvtChildListAddressDescriptionDuplicate;
  PVOID EvtChildListAddressDescriptionCleanup;
  PVOID EvtChildListDeviceReenumerated;
};

typedef _WDF_CHILD_LIST_CONFIG WDF_CHILD_LIST_CONFIG;
typedef _WDF_CHILD_LIST_CONFIG * PWDF_CHILD_LIST_CONFIG;


struct _WDF_CHILD_IDENTIFICATION_DESCRIPTION_HEADER {
    //
    // Size in bytes of the entire description, including this header.
    //
    // Same value as WDF_CHILD_LIST_CONFIG::IdentificationDescriptionSize
    // Used as a sanity check.
    //
    ULONG IdentificationDescriptionSize;
};

typedef _WDF_CHILD_IDENTIFICATION_DESCRIPTION_HEADER WDF_CHILD_IDENTIFICATION_DESCRIPTION_HEADER;
typedef _WDF_CHILD_IDENTIFICATION_DESCRIPTION_HEADER * PWDF_CHILD_IDENTIFICATION_DESCRIPTION_HEADER;

/*
NTSTATUS EvtWdfChildListCreateDevice(
  PVOID ChildList,
  PWDF_CHILD_IDENTIFICATION_DESCRIPTION_HEADER IdentificationDescription,
  PVOID ChildInit
)

NTSTATUS EvtWdfChildListIdentificationDescriptionDuplicate(
  PVOID ChildList,
  PWDF_CHILD_IDENTIFICATION_DESCRIPTION_HEADER SourceIdentificationDescription,
  PWDF_CHILD_IDENTIFICATION_DESCRIPTION_HEADER DestinationIdentificationDescription
)


EVT_WDF_CHILD_LIST_IDENTIFICATION_DESCRIPTION_COMPARE EvtWdfChildListIdentificationDescriptionCompare;

BOOLEAN EvtWdfChildListIdentificationDescriptionCompare(
  PVOID ChildList,
  PWDF_CHILD_IDENTIFICATION_DESCRIPTION_HEADER FirstIdentificationDescription,
  PWDF_CHILD_IDENTIFICATION_DESCRIPTION_HEADER SecondIdentificationDescription
)


void EvtWdfChildListIdentificationDescriptionCleanup(
  WDFCHILDLIST ChildList,
  PWDF_CHILD_IDENTIFICATION_DESCRIPTION_HEADER IdentificationDescription
)

*/


/*
PIRP WdfRequestWdmGetIrp(
   WDFREQUEST Request
);
Returns the WDM IRP structure that is associated with a specified framework request object.
*/


// WdfDeviceInitAssignWdmIrpPreprocessCallback
/*
NTSTATUS WdfDeviceInitAssignWdmIrpPreprocessCallback(
  PVOID                  DeviceInit,
  PVOID EvtDeviceWdmIrpPreprocess,
  UCHAR                            MajorFunction,
  PUCHAR                           MinorFunctions,
  ULONG                            NumMinorFunctions
);
*/

typedef HANDLE WDFOBJECT;
typedef HANDLE * PWDFOBJECT;

typedef HANDLE WDFDRIVER;
typedef HANDLE WDFDEVICE;
typedef HANDLE WDFWMIPROVIDER;
typedef HANDLE WDFWMIINSTANCE;
typedef HANDLE WDFQUEUE;
typedef HANDLE WDFREQUEST;
typedef HANDLE WDFFILEOBJECT;
typedef HANDLE WDFDPC;
typedef HANDLE WDFTIMER;
typedef HANDLE WDFWORKITEM;
typedef HANDLE WDFINTERRUPT;
typedef HANDLE WDFWAITLOCK;
typedef HANDLE WDFSPINLOCK;
typedef HANDLE WDFMEMORY;
typedef HANDLE WDFLOOKASIDE;
typedef HANDLE WDFIOTARGET;
typedef HANDLE WDFUSBDEVICE;
typedef HANDLE WDFUSBINTERFACE;
typedef HANDLE WDFUSBPIPE;
typedef HANDLE WDFDMAENABLER;
typedef HANDLE WDFDMATRANSACTION;
typedef HANDLE WDFCOMMONBUFFER;
typedef HANDLE WDFKEY;
typedef HANDLE WDFSTRING;
typedef HANDLE WDFCOLLECTION;
typedef HANDLE WDFCHILDLIST;
typedef HANDLE WDFIORESREQLIST;
typedef HANDLE WDFIORESLIST;
typedef HANDLE WDFCMRESLIST;
typedef HANDLE WDFCOMPANIONTARGET;

typedef HANDLE POHANDLE;

typedef ULONG  ACCESS_MASK;

enum _WDF_CHILD_LIST_RETRIEVE_DEVICE_STATUS {
  WdfChildListRetrieveDeviceUndefined,
  WdfChildListRetrieveDeviceSuccess,
  WdfChildListRetrieveDeviceNotYetCreated,
  WdfChildListRetrieveDeviceNoSuchDevice
};

typedef _WDF_CHILD_LIST_RETRIEVE_DEVICE_STATUS WDF_CHILD_LIST_RETRIEVE_DEVICE_STATUS;
typedef _WDF_CHILD_LIST_RETRIEVE_DEVICE_STATUS * PWDF_CHILD_LIST_RETRIEVE_DEVICE_STATUS;

struct _WDF_CHILD_ADDRESS_DESCRIPTION_HEADER {
  ULONG AddressDescriptionSize;
};

typedef _WDF_CHILD_ADDRESS_DESCRIPTION_HEADER WDF_CHILD_ADDRESS_DESCRIPTION_HEADER;
typedef _WDF_CHILD_ADDRESS_DESCRIPTION_HEADER * PWDF_CHILD_ADDRESS_DESCRIPTION_HEADER;

struct _WDF_CHILD_IDENTIFICATION_DESCRIPTION_HEADER {
  ULONG IdentificationDescriptionSize;
};

typedef _WDF_CHILD_IDENTIFICATION_DESCRIPTION_HEADER WDF_CHILD_IDENTIFICATION_DESCRIPTION_HEADER;
typedef _WDF_CHILD_IDENTIFICATION_DESCRIPTION_HEADER * PWDF_CHILD_IDENTIFICATION_DESCRIPTION_HEADER;

struct _WDF_CHILD_LIST_ITERATOR {
  ULONG Size;
  ULONG Flags;
  PVOID Reserved[4];
};

typedef _WDF_CHILD_LIST_ITERATOR WDF_CHILD_LIST_ITERATOR;
typedef _WDF_CHILD_LIST_ITERATOR * PWDF_CHILD_LIST_ITERATOR;


// BOOLEAN EvtWdfChildListIdentificationDescriptionCompare(
//   WDFCHILDLIST ChildList,
//   PWDF_CHILD_IDENTIFICATION_DESCRIPTION_HEADER FirstIdentificationDescription,
//   PWDF_CHILD_IDENTIFICATION_DESCRIPTION_HEADER SecondIdentificationDescription
// );

typedef BOOLEAN (__fastcall * EVT_WDF_CHILD_LIST_IDENTIFICATION_DESCRIPTION_COMPARE)(WDFCHILDLIST ChildList, PWDF_CHILD_IDENTIFICATION_DESCRIPTION_HEADER FirstIdentificationDescription, PWDF_CHILD_IDENTIFICATION_DESCRIPTION_HEADER SecondIdentificationDescription);
typedef EVT_WDF_CHILD_LIST_IDENTIFICATION_DESCRIPTION_COMPARE PFN_WDF_CHILD_LIST_IDENTIFICATION_DESCRIPTION_COMPARE;

struct _WDF_CHILD_RETRIEVE_INFO {
  ULONG Size;
  PWDF_CHILD_IDENTIFICATION_DESCRIPTION_HEADER IdentificationDescription;
  PWDF_CHILD_ADDRESS_DESCRIPTION_HEADER AddressDescription;
  WDF_CHILD_LIST_RETRIEVE_DEVICE_STATUS Status;
  PFN_WDF_CHILD_LIST_IDENTIFICATION_DESCRIPTION_COMPARE EvtChildListIdentificationDescriptionCompare;
};

typedef _WDF_CHILD_RETRIEVE_INFO WDF_CHILD_RETRIEVE_INFO;
typedef _WDF_CHILD_RETRIEVE_INFO * PWDF_CHILD_RETRIEVE_INFO;

struct _WDF_COMMON_BUFFER_CONFIG {
  ULONG Size;
  ULONG AlignmentRequirement;
};

typedef _WDF_COMMON_BUFFER_CONFIG WDF_COMMON_BUFFER_CONFIG;
typedef _WDF_COMMON_BUFFER_CONFIG * PWDF_COMMON_BUFFER_CONFIG;

struct _WDFDEVICE_INIT {
  PVOID Reserved;      // Reserved.
};

typedef _WDFDEVICE_INIT WDFDEVICE_INIT;
typedef _WDFDEVICE_INIT * PWDFDEVICE_INIT;

// void EvtWdfDeviceShutdownNotification(
//   WDFDEVICE Device
// );

typedef void (__fastcall * EVT_WDF_DEVICE_SHUTDOWN_NOTIFICATION)(WDFDEVICE Device);
typedef EVT_WDF_DEVICE_SHUTDOWN_NOTIFICATION PFN_WDF_DEVICE_SHUTDOWN_NOTIFICATION;

enum _WDF_DEVICE_SHUTDOWN_FLAGS {
  WdfDeviceShutdown,
  WdfDeviceLastChanceShutdown
};
typedef _WDF_DEVICE_SHUTDOWN_FLAGS WDF_DEVICE_SHUTDOWN_FLAGS;

enum _WDF_TRI_STATE {
  WdfFalse,
  WdfTrue,
  WdfUseDefault
};

typedef _WDF_TRI_STATE WDF_TRI_STATE;
typedef _WDF_TRI_STATE * PWDF_TRI_STATE;

struct _WDF_DEVICE_STATE {
  ULONG Size;
  WDF_TRI_STATE Disabled;
  WDF_TRI_STATE DontDisplayInUI;
  WDF_TRI_STATE Failed;
  WDF_TRI_STATE NotDisableable;
  WDF_TRI_STATE Removed;
  WDF_TRI_STATE ResourcesChanged;
};

typedef _WDF_DEVICE_STATE WDF_DEVICE_STATE;
typedef _WDF_DEVICE_STATE * PWDF_DEVICE_STATE;

enum _WDF_DEVICE_PNP_STATE {
  WdfDevStatePnpInvalid,
  WdfDevStatePnpObjectCreated,
  WdfDevStatePnpCheckForDevicePresence,
  WdfDevStatePnpEjectFailed,
  WdfDevStatePnpEjectHardware,
  WdfDevStatePnpEjectedWaitingForRemove,
  WdfDevStatePnpInit,
  WdfDevStatePnpInitStarting,
  WdfDevStatePnpInitSurpriseRemoved,
  WdfDevStatePnpHardwareAvailable,
  WdfDevStatePnpEnableInterfaces,
  WdfDevStatePnpHardwareAvailablePowerPolicyFailed,
  WdfDevStatePnpQueryRemoveAskDriver,
  WdfDevStatePnpQueryRemovePending,
  WdfDevStatePnpQueryRemoveStaticCheck,
  WdfDevStatePnpQueriedRemoving,
  WdfDevStatePnpQueryStopAskDriver,
  WdfDevStatePnpQueryStopPending,
  WdfDevStatePnpQueryStopStaticCheck,
  WdfDevStatePnpQueryCanceled,
  WdfDevStatePnpRemoved,
  WdfDevStatePnpPdoRemoved,
  WdfDevStatePnpRemovedPdoWait,
  WdfDevStatePnpRemovedPdoSurpriseRemoved,
  WdfDevStatePnpRemovingDisableInterfaces,
  WdfDevStatePnpRestarting,
  WdfDevStatePnpStarted,
  WdfDevStatePnpStartedCancelStop,
  WdfDevStatePnpStartedCancelRemove,
  WdfDevStatePnpStartedRemoving,
  WdfDevStatePnpStartingFromStopped,
  WdfDevStatePnpStopped,
  WdfDevStatePnpStoppedWaitForStartCompletion,
  WdfDevStatePnpStartedStopping,
  WdfDevStatePnpSurpriseRemove,
  WdfDevStatePnpInitQueryRemove,
  WdfDevStatePnpInitQueryRemoveCanceled,
  WdfDevStatePnpFdoRemoved,
  WdfDevStatePnpRemovedWaitForChildren,
  WdfDevStatePnpQueriedSurpriseRemove,
  WdfDevStatePnpSurpriseRemoveIoStarted,
  WdfDevStatePnpFailedPowerDown,
  WdfDevStatePnpFailedIoStarting,
  WdfDevStatePnpFailedOwnHardware,
  WdfDevStatePnpFailed,
  WdfDevStatePnpFailedSurpriseRemoved,
  WdfDevStatePnpFailedStarted,
  WdfDevStatePnpFailedWaitForRemove,
  WdfDevStatePnpFailedInit,
  WdfDevStatePnpPdoInitFailed,
  WdfDevStatePnpRestart,
  WdfDevStatePnpRestartReleaseHardware,
  WdfDevStatePnpRestartHardwareAvailable,
  WdfDevStatePnpPdoRestart,
  WdfDevStatePnpFinal,
  WdfDevStatePnpRemovedChildrenRemoved,
  WdfDevStatePnpQueryRemoveEnsureDeviceAwake,
  WdfDevStatePnpQueryStopEnsureDeviceAwake,
  WdfDevStatePnpFailedPowerPolicyRemoved,
  WdfDevStatePnpNull
};

typedef _WDF_DEVICE_PNP_STATE WDF_DEVICE_PNP_STATE;
typedef _WDF_DEVICE_PNP_STATE * PWDF_DEVICE_PNP_STATE;

enum _WDF_DEVICE_POWER_STATE {
  WdfDevStatePowerInvalid,
  WdfDevStatePowerObjectCreated,
  WdfDevStatePowerCheckDeviceType,
  WdfDevStatePowerCheckDeviceTypeNP,
  WdfDevStatePowerCheckParentState,
  WdfDevStatePowerCheckParentStateNP,
  WdfDevStatePowerEnablingWakeAtBus,
  WdfDevStatePowerEnablingWakeAtBusNP,
  WdfDevStatePowerD0,
  WdfDevStatePowerD0NP,
  WdfDevStatePowerD0BusWakeOwner,
  WdfDevStatePowerD0BusWakeOwnerNP,
  WdfDevStatePowerD0ArmedForWake,
  WdfDevStatePowerD0ArmedForWakeNP,
  WdfDevStatePowerD0DisarmingWakeAtBus,
  WdfDevStatePowerD0DisarmingWakeAtBusNP,
  WdfDevStatePowerD0Starting,
  WdfDevStatePowerD0StartingConnectInterrupt,
  WdfDevStatePowerD0StartingDmaEnable,
  WdfDevStatePowerD0StartingStartSelfManagedIo,
  WdfDevStatePowerDecideD0State,
  WdfDevStatePowerGotoD3Stopped,
  WdfDevStatePowerStopped,
  WdfDevStatePowerStartingCheckDeviceType,
  WdfDevStatePowerStartingChild,
  WdfDevStatePowerDxDisablingWakeAtBus,
  WdfDevStatePowerDxDisablingWakeAtBusNP,
  WdfDevStatePowerGotoDx,
  WdfDevStatePowerGotoDxNP,
  WdfDevStatePowerGotoDxIoStopped,
  WdfDevStatePowerGotoDxIoStoppedNP,
  WdfDevStatePowerGotoDxNPFailed,
  WdfDevStatePowerDx,
  WdfDevStatePowerDxNP,
  WdfDevStatePowerGotoDxArmedForWake,
  WdfDevStatePowerGotoDxArmedForWakeNP,
  WdfDevStatePowerGotoDxIoStoppedArmedForWake,
  WdfDevStatePowerGotoDxIoStoppedArmedForWakeNP,
  WdfDevStatePowerDxArmedForWake,
  WdfDevStatePowerDxArmedForWakeNP,
  WdfDevStatePowerCheckParentStateArmedForWake,
  WdfDevStatePowerCheckParentStateArmedForWakeNP,
  WdfDevStatePowerWaitForParentArmedForWake,
  WdfDevStatePowerWaitForParentArmedForWakeNP,
  WdfDevStatePowerStartSelfManagedIo,
  WdfDevStatePowerStartSelfManagedIoNP,
  WdfDevStatePowerStartSelfManagedIoFailed,
  WdfDevStatePowerStartSelfManagedIoFailedNP,
  WdfDevStatePowerWaitForParent,
  WdfDevStatePowerWaitForParentNP,
  WdfDevStatePowerWakePending,
  WdfDevStatePowerWakePendingNP,
  WdfDevStatePowerWaking,
  WdfDevStatePowerWakingNP,
  WdfDevStatePowerWakingConnectInterrupt,
  WdfDevStatePowerWakingConnectInterruptNP,
  WdfDevStatePowerWakingConnectInterruptFailed,
  WdfDevStatePowerWakingConnectInterruptFailedNP,
  WdfDevStatePowerWakingDmaEnable,
  WdfDevStatePowerWakingDmaEnableNP,
  WdfDevStatePowerWakingDmaEnableFailed,
  WdfDevStatePowerWakingDmaEnableFailedNP,
  WdfDevStatePowerReportPowerUpFailedDerefParent,
  WdfDevStatePowerReportPowerUpFailed,
  WdfDevStatePowerPowerFailedPowerDown,
  WdfDevStatePowerReportPowerDownFailed,
  WdfDevStatePowerInitialConnectInterruptFailed,
  WdfDevStatePowerInitialDmaEnableFailed,
  WdfDevStatePowerInitialSelfManagedIoFailed,
  WdfDevStatePowerInitialPowerUpFailedDerefParent,
  WdfDevStatePowerInitialPowerUpFailed,
  WdfDevStatePowerDxStoppedDisarmWake,
  WdfDevStatePowerDxStoppedDisarmWakeNP,
  WdfDevStatePowerGotoDxStoppedDisableInterruptNP,
  WdfDevStatePowerGotoDxStopped,
  WdfDevStatePowerDxStopped,
  WdfDevStatePowerGotoStopped,
  WdfDevStatePowerStoppedCompleteDx,
  WdfDevStatePowerDxStoppedDecideDxState,
  WdfDevStatePowerDxStoppedArmForWake,
  WdfDevStatePowerDxStoppedArmForWakeNP,
  WdfDevStatePowerFinalPowerDownFailed,
  WdfDevStatePowerFinal,
  WdfDevStatePowerGotoImplicitD3DisarmWakeAtBus,
  WdfDevStatePowerUpFailed,
  WdfDevStatePowerUpFailedDerefParent,
  WdfDevStatePowerGotoDxFailed,
  WdfDevStatePowerGotoDxStoppedDisableInterrupt,
  WdfDevStatePowerUpFailedNP,
  WdfDevStatePowerUpFailedDerefParentNP,
  WdfDevStatePowerNotifyingD0ExitToWakeInterrupts,
  WdfDevStatePowerNotifyingD0EntryToWakeInterrupts,
  WdfDevStatePowerNotifyingD0ExitToWakeInterruptsNP,
  WdfDevStatePowerNotifyingD0EntryToWakeInterruptsNP,
  WdfDevStatePowerInitialPowerUpFailedPowerDown,
  WdfDevStatePowerUpFailedPowerDown,
  WdfDevStatePowerUpFailedPowerDownNP,
  WdfDevStatePowerInitialSelfManagedIoFailedStarted,
  WdfDevStatePowerStartSelfManagedIoFailedStarted,
  WdfDevStatePowerStartSelfManagedIoFailedStartedNP,
  WdfDevStatePowerNull
};

typedef _WDF_DEVICE_POWER_STATE WDF_DEVICE_POWER_STATE;
typedef _WDF_DEVICE_POWER_STATE * PWDF_DEVICE_POWER_STATE;

enum _WDF_POWER_POLICY_S0_IDLE_CAPABILITIES {
  IdleCapsInvalid,
  IdleCannotWakeFromS0,
  IdleCanWakeFromS0,
  IdleUsbSelectiveSuspend
};

typedef _WDF_POWER_POLICY_S0_IDLE_CAPABILITIES WDF_POWER_POLICY_S0_IDLE_CAPABILITIES;

enum _DEVICE_POWER_STATE {
  PowerDeviceUnspecified,
  PowerDeviceD0,
  PowerDeviceD1,
  PowerDeviceD2,
  PowerDeviceD3,
  PowerDeviceMaximum
};

typedef _DEVICE_POWER_STATE DEVICE_POWER_STATE;
typedef _DEVICE_POWER_STATE * PDEVICE_POWER_STATE;

enum _WDF_POWER_POLICY_S0_IDLE_USER_CONTROL {
  IdleUserControlInvalid,
  IdleDoNotAllowUserControl,
  IdleAllowUserControl
};

typedef _WDF_POWER_POLICY_S0_IDLE_USER_CONTROL WDF_POWER_POLICY_S0_IDLE_USER_CONTROL;

enum _WDF_POWER_POLICY_IDLE_TIMEOUT_TYPE {
  DriverManagedIdleTimeout,
  SystemManagedIdleTimeout,
  SystemManagedIdleTimeoutWithHint
};
typedef _WDF_POWER_POLICY_IDLE_TIMEOUT_TYPE WDF_POWER_POLICY_IDLE_TIMEOUT_TYPE;
typedef _WDF_POWER_POLICY_IDLE_TIMEOUT_TYPE * PWDF_POWER_POLICY_IDLE_TIMEOUT_TYPE;

struct _WDF_DEVICE_POWER_POLICY_IDLE_SETTINGS {
  ULONG                                 Size;
  WDF_POWER_POLICY_S0_IDLE_CAPABILITIES IdleCaps;
  DEVICE_POWER_STATE                    DxState;
  ULONG                                 IdleTimeout;
  WDF_POWER_POLICY_S0_IDLE_USER_CONTROL UserControlOfIdleSettings;
  WDF_TRI_STATE                         Enabled;
  WDF_TRI_STATE                         PowerUpIdleDeviceOnSystemWake;
  WDF_POWER_POLICY_IDLE_TIMEOUT_TYPE    IdleTimeoutType;
  WDF_TRI_STATE                         ExcludeD3Cold;
};
typedef _WDF_DEVICE_POWER_POLICY_IDLE_SETTINGS WDF_DEVICE_POWER_POLICY_IDLE_SETTINGS;
typedef _WDF_DEVICE_POWER_POLICY_IDLE_SETTINGS * PWDF_DEVICE_POWER_POLICY_IDLE_SETTINGS;

enum _WDF_POWER_POLICY_SX_WAKE_USER_CONTROL {
  WakeUserControlInvalid,
  WakeDoNotAllowUserControl,
  WakeAllowUserControl
};

typedef _WDF_POWER_POLICY_SX_WAKE_USER_CONTROL WDF_POWER_POLICY_SX_WAKE_USER_CONTROL;

struct _WDF_DEVICE_POWER_POLICY_WAKE_SETTINGS {
  ULONG                                 Size;
  DEVICE_POWER_STATE                    DxState;
  WDF_POWER_POLICY_SX_WAKE_USER_CONTROL UserControlOfWakeSettings;
  WDF_TRI_STATE                         Enabled;
  BOOLEAN                               ArmForWakeIfChildrenAreArmedForWake;
  BOOLEAN                               IndicateChildWakeOnParentWake;
};

typedef _WDF_DEVICE_POWER_POLICY_WAKE_SETTINGS WDF_DEVICE_POWER_POLICY_WAKE_SETTINGS;
typedef _WDF_DEVICE_POWER_POLICY_WAKE_SETTINGS * PWDF_DEVICE_POWER_POLICY_WAKE_SETTINGS;

enum _WDF_SPECIAL_FILE_TYPE {
  WdfSpecialFileUndefined,
  WdfSpecialFilePaging,
  WdfSpecialFileHibernation,
  WdfSpecialFileDump,
  WdfSpecialFileBoot,
  WdfSpecialFileMax
};

typedef _WDF_SPECIAL_FILE_TYPE WDF_SPECIAL_FILE_TYPE;
typedef _WDF_SPECIAL_FILE_TYPE * PWDF_SPECIAL_FILE_TYPE;

enum _WDF_STATE_NOTIFICATION_TYPE {
  StateNotificationInvalid,
  StateNotificationEnterState,
  StateNotificationPostProcessState,
  StateNotificationLeaveState,
  StateNotificationAllStates
};

typedef _WDF_STATE_NOTIFICATION_TYPE WDF_STATE_NOTIFICATION_TYPE;

struct _WDF_DEVICE_PNP_NOTIFICATION_DATA {
  WDF_STATE_NOTIFICATION_TYPE Type;
  union {
    struct {
      WDF_DEVICE_PNP_STATE CurrentState;
      WDF_DEVICE_PNP_STATE NewState;
    } EnterState;
    struct {
      WDF_DEVICE_PNP_STATE CurrentState;
    } PostProcessState;
    struct {
      WDF_DEVICE_PNP_STATE CurrentState;
      WDF_DEVICE_PNP_STATE NewState;
    } LeaveState;
  } Data;
};

typedef _WDF_DEVICE_PNP_NOTIFICATION_DATA WDF_DEVICE_PNP_NOTIFICATION_DATA;
typedef _WDF_DEVICE_PNP_NOTIFICATION_DATA * PWDF_DEVICE_PNP_NOTIFICATION_DATA;

// void EvtWdfDevicePnpStateChangeNotification(
//   WDFDEVICE Device,
//   PCWDF_DEVICE_PNP_NOTIFICATION_DATA NotificationData
// );

typedef void (__fastcall * EVT_WDF_DEVICE_PNP_STATE_CHANGE_NOTIFICATION)(WDFDEVICE Device, const PWDF_DEVICE_PNP_NOTIFICATION_DATA NotificationData);
typedef EVT_WDF_DEVICE_PNP_STATE_CHANGE_NOTIFICATION PFN_WDF_DEVICE_PNP_STATE_CHANGE_NOTIFICATION;

// void EvtWdfDevicePowerStateChangeNotification(
//   WDFDEVICE Device,
//   PCWDF_DEVICE_POWER_NOTIFICATION_DATA NotificationData
// )

struct _WDF_DEVICE_POWER_NOTIFICATION_DATA {
  WDF_STATE_NOTIFICATION_TYPE Type;
  union {
    struct {
      WDF_DEVICE_POWER_STATE CurrentState;
      WDF_DEVICE_POWER_STATE NewState;
    } EnterState;
    struct {
      WDF_DEVICE_POWER_STATE CurrentState;
    } PostProcessState;
    struct {
      WDF_DEVICE_POWER_STATE CurrentState;
      WDF_DEVICE_POWER_STATE NewState;
    } LeaveState;
  } Data;
};

typedef _WDF_DEVICE_POWER_NOTIFICATION_DATA WDF_DEVICE_POWER_NOTIFICATION_DATA;
typedef _WDF_DEVICE_POWER_NOTIFICATION_DATA * PWDF_DEVICE_POWER_NOTIFICATION_DATA;

typedef void (__fastcall * EVT_WDF_DEVICE_POWER_STATE_CHANGE_NOTIFICATION)(WDFDEVICE Device, const PWDF_DEVICE_POWER_NOTIFICATION_DATA NotificationData);
typedef EVT_WDF_DEVICE_POWER_STATE_CHANGE_NOTIFICATION PFN_WDF_DEVICE_POWER_STATE_CHANGE_NOTIFICATION;

typedef enum _WDF_DEVICE_POWER_POLICY_STATE {
  WdfDevStatePwrPolInvalid,
  WdfDevStatePwrPolObjectCreated,
  WdfDevStatePwrPolStarting,
  WdfDevStatePwrPolStartingSucceeded,
  WdfDevStatePwrPolStartingFailed,
  WdfDevStatePwrPolStartingDecideS0Wake,
  WdfDevStatePwrPolStartedIdleCapable,
  WdfDevStatePwrPolTimerExpiredNoWake,
  WdfDevStatePwrPolTimerExpiredNoWakeCompletePowerDown,
  WdfDevStatePwrPolWaitingUnarmed,
  WdfDevStatePwrPolWaitingUnarmedQueryIdle,
  WdfDevStatePwrPolS0NoWakePowerUp,
  WdfDevStatePwrPolS0NoWakeCompletePowerUp,
  WdfDevStatePwrPolSystemSleepFromDeviceWaitingUnarmed,
  WdfDevStatePwrPolSystemSleepNeedWake,
  WdfDevStatePwrPolSystemSleepNeedWakeCompletePowerUp,
  WdfDevStatePwrPolSystemSleepPowerRequestFailed,
  WdfDevStatePwrPolCheckPowerPageable,
  WdfDevStatePwrPolSleepingWakeWakeArrived,
  WdfDevStatePwrPolSleepingWakeRevertArmWake,
  WdfDevStatePwrPolSystemAsleepWakeArmed,
  WdfDevStatePwrPolSystemWakeDeviceWakeEnabled,
  WdfDevStatePwrPolSystemWakeDeviceWakeEnabledWakeCanceled,
  WdfDevStatePwrPolSystemWakeDeviceWakeDisarm,
  WdfDevStatePwrPolSystemWakeDeviceWakeTriggered,
  WdfDevStatePwrPolSystemWakeDeviceWakeTriggeredS0,
  WdfDevStatePwrPolSystemWakeDeviceWokeDisarm,
  WdfDevStatePwrPolSleepingWakeWakeArrivedNP,
  WdfDevStatePwrPolSleepingWakeRevertArmWakeNP,
  WdfDevStatePwrPolSleepingWakePowerDownFailed,
  WdfDevStatePwrPolSleepingWakePowerDownFailedWakeCanceled,
  WdfDevStatePwrPolSystemAsleepWakeArmedNP,
  WdfDevStatePwrPolSystemWakeDeviceWakeEnabledNP,
  WdfDevStatePwrPolSystemWakeDeviceWakeEnabledWakeCanceledNP,
  WdfDevStatePwrPolSystemWakeDeviceWakeDisarmNP,
  WdfDevStatePwrPolSystemWakeDeviceWakeTriggeredNP,
  WdfDevStatePwrPolSystemWakeDeviceWakeTriggeredS0NP,
  WdfDevStatePwrPolSystemWakeDeviceWokeDisarmNP,
  WdfDevStatePwrPolSystemWakeDeviceWakeCompletePowerUp,
  WdfDevStatePwrPolSleeping,
  WdfDevStatePwrPolSleepingNoWakePowerDown,
  WdfDevStatePwrPolSleepingNoWakeCompletePowerDown,
  WdfDevStatePwrPolSleepingNoWakeDxRequestFailed,
  WdfDevStatePwrPolSleepingWakePowerDown,
  WdfDevStatePwrPolSleepingSendWake,
  WdfDevStatePwrPolSystemAsleepNoWake,
  WdfDevStatePwrPolSystemWakeDeviceWakeDisabled,
  WdfDevStatePwrPolSystemWakeDeviceToD0,
  WdfDevStatePwrPolSystemWakeDeviceToD0CompletePowerUp,
  WdfDevStatePwrPolSystemWakeQueryIdle,
  WdfDevStatePwrPolStartedWakeCapable,
  WdfDevStatePwrPolTimerExpiredDecideUsbSS,
  WdfDevStatePwrPolTimerExpiredWakeCapablePowerDown,
  WdfDevStatePwrPolTimerExpiredWakeCapableSendWake,
  WdfDevStatePwrPolTimerExpiredWakeCapableUsbSS,
  WdfDevStatePwrPolTimerExpiredWakeCapableWakeArrived,
  WdfDevStatePwrPolTimerExpiredWakeCapableCancelWake,
  WdfDevStatePwrPolTimerExpiredWakeCapableWakeCanceled,
  WdfDevStatePwrPolTimerExpiredWakeCapableCleanup,
  WdfDevStatePwrPolTimerExpiredWakeCapableDxAllocFailed,
  WdfDevStatePwrPolTimerExpiredWakeCompletedPowerDown,
  WdfDevStatePwrPolTimerExpiredWakeCompletedPowerUp,
  WdfDevStatePwrPolWaitingArmedUsbSS,
  WdfDevStatePwrPolWaitingArmed,
  WdfDevStatePwrPolWaitingArmedQueryIdle,
  WdfDevStatePwrPolIoPresentArmed,
  WdfDevStatePwrPolIoPresentArmedWakeCanceled,
  WdfDevStatePwrPolS0WakeDisarm,
  WdfDevStatePwrPolS0WakeCompletePowerUp,
  WdfDevStatePwrPolTimerExpiredWakeSucceeded,
  WdfDevStatePwrPolTimerExpiredWakeCompletedDisarm,
  WdfDevStatePwrPolTimerExpiredWakeCapableWakeSucceeded,
  WdfDevStatePwrPolTimerExpiredWakeCapableWakeFailed,
  WdfDevStatePwrPolWakeFailedUsbSS,
  WdfDevStatePwrPolTimerExpiredWakeCapablePowerDownFailedCancelWake,
  WdfDevStatePwrPolTimerExpiredWakeCapablePowerDownFailedWakeCanceled,
  WdfDevStatePwrPolTimerExpiredWakeCapablePowerDownFailedUsbSS,
  WdfDevStatePwrPolCancelingWakeForSystemSleep,
  WdfDevStatePwrPolCancelingWakeForSystemSleepWakeCanceled,
  WdfDevStatePwrPolDisarmingWakeForSystemSleepCompletePowerUp,
  WdfDevStatePwrPolPowerUpForSystemSleepFailed,
  WdfDevStatePwrPolWokeFromS0UsbSS,
  WdfDevStatePwrPolWokeFromS0,
  WdfDevStatePwrPolWokeFromS0NotifyDriver,
  WdfDevStatePwrPolStoppingResetDevice,
  WdfDevStatePwrPolStoppingResetDeviceCompletePowerUp,
  WdfDevStatePwrPolStoppingResetDeviceFailed,
  WdfDevStatePwrPolStoppingD0,
  WdfDevStatePwrPolStoppingD0Failed,
  WdfDevStatePwrPolStoppingDisarmWake,
  WdfDevStatePwrPolStoppingDisarmWakeCancelWake,
  WdfDevStatePwrPolStoppingDisarmWakeWakeCanceled,
  WdfDevStatePwrPolStopping,
  WdfDevStatePwrPolStoppingFailed,
  WdfDevStatePwrPolStoppingSendStatus,
  WdfDevStatePwrPolStoppingCancelTimer,
  WdfDevStatePwrPolStoppingWaitForIdleTimeout,
  WdfDevStatePwrPolStoppingCancelUsbSS,
  WdfDevStatePwrPolStoppingWaitForUsbSSCompletion,
  WdfDevStatePwrPolStoppingCancelWake,
  WdfDevStatePwrPolStopped,
  WdfDevStatePwrPolCancelUsbSS,
  WdfDevStatePwrPolStarted,
  WdfDevStatePwrPolStartedCancelTimer,
  WdfDevStatePwrPolStartedWaitForIdleTimeout,
  WdfDevStatePwrPolStartedWakeCapableCancelTimerForSleep,
  WdfDevStatePwrPolStartedWakeCapableWaitForIdleTimeout,
  WdfDevStatePwrPolStartedWakeCapableSleepingUsbSS,
  WdfDevStatePwrPolStartedIdleCapableCancelTimerForSleep,
  WdfDevStatePwrPolStartedIdleCapableWaitForIdleTimeout,
  WdfDevStatePwrPolDeviceD0PowerRequestFailed,
  WdfDevStatePwrPolDevicePowerRequestFailed,
  WdfDevStatePwrPolGotoDx,
  WdfDevStatePwrPolGotoDxInDx,
  WdfDevStatePwrPolDx,
  WdfDevStatePwrPolGotoD0,
  WdfDevStatePwrPolGotoD0InD0,
  WdfDevStatePwrPolFinal,
  WdfDevStatePwrPolSleepingPowerDownNotProcessed,
  WdfDevStatePwrPolTimerExpiredWakeCapablePowerDownNotProcessed,
  WdfDevStatePwrPolTimerExpiredNoWakePowerDownNotProcessed,
  WdfDevStatePwrPolTimerExpiredNoWakePoweredDownDisableIdleTimer,
  WdfDevStatePwrPolStoppingWaitingForImplicitPowerDown,
  WdfDevStatePwrPolStoppingPoweringUp,
  WdfDevStatePwrPolStoppingPoweringDown,
  WdfDevStatePwrPolPowerUpForSystemSleepNotSeen,
  WdfDevStatePwrPolWaitingArmedStoppingCancelUsbSS,
  WdfDevStatePwrPolWaitingArmedWakeFailedCancelUsbSS,
  WdfDevStatePwrPolWaitingArmedIoPresentCancelUsbSS,
  WdfDevStatePwrPolWaitingArmedWakeSucceededCancelUsbSS,
  WdfDevStatePwrPolCancelingUsbSSForSystemSleep,
  WdfDevStatePwrPolStoppingD0CancelUsbSS,
  WdfDevStatePwrPolStartingPoweredUp,
  WdfDevStatePwrPolIdleCapableDeviceIdle,
  WdfDevStatePwrPolDeviceIdleReturnToActive,
  WdfDevStatePwrPolDeviceIdleSleeping,
  WdfDevStatePwrPolDeviceIdleStopping,
  WdfDevStatePwrPolTimerExpiredNoWakeUndoPowerDown,
  WdfDevStatePwrPolWakeCapableDeviceIdle,
  WdfDevStatePwrPolWakeCapableUsbSSCompleted,
  WdfDevStatePwrPolTimerExpiredWakeCapableUndoPowerDown,
  WdfDevStatePwrPolTimerExpiredWakeCompletedHardwareStarted,
  WdfDevStatePwrPolStoppedRemoving,
  WdfDevStatePwrPolRemoved,
  WdfDevStatePwrPolRestarting,
  WdfDevStatePwrPolRestartingFailed,
  WdfDevStatePwrPolStartingPoweredUpFailed,
  WdfDevStatePwrPolTimerExpiredNoWakeReturnToActive,
  WdfDevStatePwrPolWaitingArmedWakeInterruptFired,
  WdfDevStatePwrPolSystemWakeDeviceWakeInterruptFired,
  WdfDevStatePwrPolSystemWakeDeviceWakeInterruptFiredNP,
  WdfDevStatePwrPolTimerExpiredWakeCapableWakeInterruptArrived,
  WdfDevStatePwrPolTimerExpiredWakeCapablePowerDownFailedWakeInterruptArrived,
  WdfDevStatePwrPolWaitingArmedWakeInterruptFiredDuringPowerDown,
  WdfDevStatePwrPolNull
};

typedef _WDF_DEVICE_POWER_POLICY_STATE WDF_DEVICE_POWER_POLICY_STATE;
typedef _WDF_DEVICE_POWER_POLICY_STATE * PWDF_DEVICE_POWER_POLICY_STATE;

typedef NTSTATUS (__fastcall *EVT_WDF_DEVICE_ARM_WAKE_FROM_S0)(WDFDEVICE Device);
typedef EVT_WDF_DEVICE_ARM_WAKE_FROM_S0 PFN_WDF_DEVICE_ARM_WAKE_FROM_S0;

typedef void (__fastcall * EVT_WDF_DEVICE_DISARM_WAKE_FROM_S0)(WDFDEVICE Device);
typedef EVT_WDF_DEVICE_DISARM_WAKE_FROM_S0 PFN_WDF_DEVICE_DISARM_WAKE_FROM_S0;

typedef void (__fastcall * EVT_WDF_DEVICE_WAKE_FROM_S0_TRIGGERED)(WDFDEVICE Device);
typedef EVT_WDF_DEVICE_WAKE_FROM_S0_TRIGGERED PFN_WDF_DEVICE_WAKE_FROM_S0_TRIGGERED;

typedef NTSTATUS (__fastcall * EVT_WDF_DEVICE_ARM_WAKE_FROM_SX)(WDFDEVICE Device);
typedef EVT_WDF_DEVICE_ARM_WAKE_FROM_SX PFN_WDF_DEVICE_ARM_WAKE_FROM_SX;

typedef void (__fastcall * EVT_WDF_DEVICE_DISARM_WAKE_FROM_SX)(WDFDEVICE Device);
typedef EVT_WDF_DEVICE_DISARM_WAKE_FROM_SX PFN_WDF_DEVICE_DISARM_WAKE_FROM_SX;

typedef void (__fastcall * EVT_WDF_DEVICE_WAKE_FROM_SX_TRIGGERED)(WDFDEVICE Device);
typedef EVT_WDF_DEVICE_WAKE_FROM_SX_TRIGGERED PFN_WDF_DEVICE_WAKE_FROM_SX_TRIGGERED;

typedef NTSTATUS (__fastcall * EVT_WDF_DEVICE_ARM_WAKE_FROM_SX_WITH_REASON)(WDFDEVICE Device, BOOLEAN DeviceWakeEnabled, BOOLEAN ChildrenArmedForWake);
typedef EVT_WDF_DEVICE_ARM_WAKE_FROM_SX_WITH_REASON PFN_WDF_DEVICE_ARM_WAKE_FROM_SX_WITH_REASON;

struct _WDF_POWER_POLICY_EVENT_CALLBACKS {
  ULONG                                       Size;
  PFN_WDF_DEVICE_ARM_WAKE_FROM_S0             EvtDeviceArmWakeFromS0;
  PFN_WDF_DEVICE_DISARM_WAKE_FROM_S0          EvtDeviceDisarmWakeFromS0;
  PFN_WDF_DEVICE_WAKE_FROM_S0_TRIGGERED       EvtDeviceWakeFromS0Triggered;
  PFN_WDF_DEVICE_ARM_WAKE_FROM_SX             EvtDeviceArmWakeFromSx;
  PFN_WDF_DEVICE_DISARM_WAKE_FROM_SX          EvtDeviceDisarmWakeFromSx;
  PFN_WDF_DEVICE_WAKE_FROM_SX_TRIGGERED       EvtDeviceWakeFromSxTriggered;
  PFN_WDF_DEVICE_ARM_WAKE_FROM_SX_WITH_REASON EvtDeviceArmWakeFromSxWithReason;
};

typedef _WDF_POWER_POLICY_EVENT_CALLBACKS WDF_POWER_POLICY_EVENT_CALLBACKS;
typedef _WDF_POWER_POLICY_EVENT_CALLBACKS * PWDF_POWER_POLICY_EVENT_CALLBACKS;

struct _WDF_DEVICE_POWER_POLICY_NOTIFICATION_DATA {
    WDF_STATE_NOTIFICATION_TYPE Type;
    union {
        struct {
            WDF_DEVICE_POWER_POLICY_STATE CurrentState;
            WDF_DEVICE_POWER_POLICY_STATE NewState;
        } EnterState;

        struct {
            WDF_DEVICE_POWER_POLICY_STATE CurrentState;
        } PostProcessState;


        struct {
            WDF_DEVICE_POWER_POLICY_STATE CurrentState;
            WDF_DEVICE_POWER_POLICY_STATE NewState;
        } LeaveState;
    } Data;
};

typedef _WDF_DEVICE_POWER_POLICY_NOTIFICATION_DATA WDF_DEVICE_POWER_POLICY_NOTIFICATION_DATA;
typedef _WDF_DEVICE_POWER_POLICY_NOTIFICATION_DATA * PWDF_DEVICE_POWER_POLICY_NOTIFICATION_DATA;
typedef const PWDF_DEVICE_POWER_POLICY_NOTIFICATION_DATA PCWDF_DEVICE_POWER_POLICY_NOTIFICATION_DATA;

typedef void (__fastcall * EVT_WDF_DEVICE_POWER_POLICY_STATE_CHANGE_NOTIFICATION)(WDFDEVICE Device, PCWDF_DEVICE_POWER_POLICY_NOTIFICATION_DATA NotificationData);
typedef EVT_WDF_DEVICE_POWER_POLICY_STATE_CHANGE_NOTIFICATION PFN_WDF_DEVICE_POWER_POLICY_STATE_CHANGE_NOTIFICATION;

struct _GUID {
  unsigned long  Data1;
  unsigned short Data2;
  unsigned short Data3;
  unsigned char  Data4[8];
};

typedef _GUID GUID;

enum _POOL_TYPE {
  NonPagedPool,
  NonPagedPoolExecute,
  PagedPool,
  NonPagedPoolMustSucceed,
  DontUseThisType,
  NonPagedPoolCacheAligned,
  PagedPoolCacheAligned,
  NonPagedPoolCacheAlignedMustS,
  MaxPoolType,
  NonPagedPoolBase,
  NonPagedPoolBaseMustSucceed,
  NonPagedPoolBaseCacheAligned,
  NonPagedPoolBaseCacheAlignedMustS,
  NonPagedPoolSession,
  PagedPoolSession,
  NonPagedPoolMustSucceedSession,
  DontUseThisTypeSession,
  NonPagedPoolCacheAlignedSession,
  PagedPoolCacheAlignedSession,
  NonPagedPoolCacheAlignedMustSSession,
  NonPagedPoolNx,
  NonPagedPoolNxCacheAligned,
  NonPagedPoolSessionNx
};

typedef _POOL_TYPE POOL_TYPE;

struct _WDF_DEVICE_PNP_CAPABILITIES {
  ULONG         Size;
  WDF_TRI_STATE LockSupported;
  WDF_TRI_STATE EjectSupported;
  WDF_TRI_STATE Removable;
  WDF_TRI_STATE DockDevice;
  WDF_TRI_STATE UniqueID;
  WDF_TRI_STATE SilentInstall;
  WDF_TRI_STATE SurpriseRemovalOK;
  WDF_TRI_STATE HardwareDisabled;
  WDF_TRI_STATE NoDisplayInUI;
  ULONG         Address;
  ULONG         UINumber;
};

typedef _WDF_DEVICE_PNP_CAPABILITIES WDF_DEVICE_PNP_CAPABILITIES;
typedef _WDF_DEVICE_PNP_CAPABILITIES * PWDF_DEVICE_PNP_CAPABILITIES;

enum _SYSTEM_POWER_STATE {
  PowerSystemUnspecified,
  PowerSystemWorking,
  PowerSystemSleeping1,
  PowerSystemSleeping2,
  PowerSystemSleeping3,
  PowerSystemHibernate,
  PowerSystemShutdown,
  PowerSystemMaximum
};

typedef _SYSTEM_POWER_STATE SYSTEM_POWER_STATE;
typedef _SYSTEM_POWER_STATE * PSYSTEM_POWER_STATE;

struct _WDF_DEVICE_POWER_CAPABILITIES {
  ULONG              Size;
  WDF_TRI_STATE      DeviceD1;
  WDF_TRI_STATE      DeviceD2;
  WDF_TRI_STATE      WakeFromD0;
  WDF_TRI_STATE      WakeFromD1;
  WDF_TRI_STATE      WakeFromD2;
  WDF_TRI_STATE      WakeFromD3;
  DEVICE_POWER_STATE DeviceState[PowerSystemMaximum];
  DEVICE_POWER_STATE DeviceWake;
  SYSTEM_POWER_STATE SystemWake;
  ULONG              D1Latency;
  ULONG              D2Latency;
  ULONG              D3Latency;
  DEVICE_POWER_STATE IdealDxStateForSx;
};

typedef _WDF_DEVICE_POWER_CAPABILITIES WDF_DEVICE_POWER_CAPABILITIES;
typedef _WDF_DEVICE_POWER_CAPABILITIES * PWDF_DEVICE_POWER_CAPABILITIES;

enum _INTERFACE_TYPE {
  InterfaceTypeUndefined,
  Internal,
  Isa,
  Eisa,
  MicroChannel,
  TurboChannel,
  PCIBus,
  VMEBus,
  NuBus,
  PCMCIABus,
  CBus,
  MPIBus,
  MPSABus,
  ProcessorInternal,
  InternalPowerBus,
  PNPISABus,
  PNPBus,
  Vmcs,
  ACPIBus,
  MaximumInterfaceType
};

typedef _INTERFACE_TYPE INTERFACE_TYPE;
typedef _INTERFACE_TYPE * PINTERFACE_TYPE;

struct _PNP_BUS_INFORMATION {
  GUID           BusTypeGuid;
  INTERFACE_TYPE LegacyBusType;
  ULONG          BusNumber;
};

typedef _PNP_BUS_INFORMATION PNP_BUS_INFORMATION;
typedef _PNP_BUS_INFORMATION * PPNP_BUS_INFORMATION;

enum _WDF_DEVICE_FAILED_ACTION {
  WdfDeviceFailedUndefined,
  WdfDeviceFailedAttemptRestart,
  WdfDeviceFailedNoRestart
};

typedef _WDF_DEVICE_FAILED_ACTION WDF_DEVICE_FAILED_ACTION;

typedef PVOID PWDF_DRIVER_GLOBALS;
typedef void VOID;

typedef NTSTATUS (__fastcall * EVT_WDFDEVICE_WDM_IRP_PREPROCESS)(
    WDFDEVICE Device,
    PIRP Irp
);

typedef EVT_WDFDEVICE_WDM_IRP_PREPROCESS * PFN_WDFDEVICE_WDM_IRP_PREPROCESS;

typedef PVOID PFN_WDF_IOCALLER_CONTEXT;

enum _WDF_DMA_PROFILE {
    WdfDmaProfileInvalid = 0,
    WdfDmaProfilePacket,
    WdfDmaProfileScatterGather,
    WdfDmaProfilePacket64,
    WdfDmaProfileScatterGather64,
    WdfDmaProfileScatterGatherDuplex,
    WdfDmaProfileScatterGather64Duplex,
    WdfDmaProfileSystem,
    WdfDmaProfileSystemDuplex,
};

typedef _WDF_DMA_PROFILE WDF_DMA_PROFILE;

typedef enum _WDF_DMA_DIRECTION {
    WdfDmaDirectionReadFromDevice = FALSE,
    WdfDmaDirectionWriteToDevice = TRUE,
};

typedef _WDF_DMA_DIRECTION WDF_DMA_DIRECTION;

typedef NTSTATUS (__fastcall * EVT_WDF_DMA_ENABLER_FILL)(
    WDFDMAENABLER DmaEnabler
);

typedef EVT_WDF_DMA_ENABLER_FILL * PFN_WDF_DMA_ENABLER_FILL;

typedef NTSTATUS (__fastcall * EVT_WDF_DMA_ENABLER_FLUSH)(
    WDFDMAENABLER DmaEnabler
);

typedef EVT_WDF_DMA_ENABLER_FLUSH * PFN_WDF_DMA_ENABLER_FLUSH;

typedef NTSTATUS EVT_WDF_DMA_ENABLER_ENABLE(
    WDFDMAENABLER DmaEnabler
);

typedef EVT_WDF_DMA_ENABLER_ENABLE * PFN_WDF_DMA_ENABLER_ENABLE;

typedef NTSTATUS EVT_WDF_DMA_ENABLER_DISABLE(
    WDFDMAENABLER DmaEnabler
);

typedef EVT_WDF_DMA_ENABLER_DISABLE * PFN_WDF_DMA_ENABLER_DISABLE;

typedef NTSTATUS EVT_WDF_DMA_ENABLER_SELFMANAGED_IO_START(
    WDFDMAENABLER DmaEnabler
);

typedef EVT_WDF_DMA_ENABLER_SELFMANAGED_IO_START * PFN_WDF_DMA_ENABLER_SELFMANAGED_IO_START;

typedef NTSTATUS (__fastcall * EVT_WDF_DMA_ENABLER_SELFMANAGED_IO_STOP)(
    WDFDMAENABLER DmaEnabler
);

typedef EVT_WDF_DMA_ENABLER_SELFMANAGED_IO_STOP * PFN_WDF_DMA_ENABLER_SELFMANAGED_IO_STOP;

struct _WDF_DMA_ENABLER_CONFIG {
    ULONG Size;
    WDF_DMA_PROFILE Profile;
    size_t MaximumLength;
    PFN_WDF_DMA_ENABLER_FILL EvtDmaEnablerFill;
    PFN_WDF_DMA_ENABLER_FLUSH EvtDmaEnablerFlush;
    PFN_WDF_DMA_ENABLER_DISABLE EvtDmaEnablerDisable;
    PFN_WDF_DMA_ENABLER_ENABLE EvtDmaEnablerEnable;
    PFN_WDF_DMA_ENABLER_SELFMANAGED_IO_START EvtDmaEnablerSelfManagedIoStart;
    PFN_WDF_DMA_ENABLER_SELFMANAGED_IO_STOP EvtDmaEnablerSelfManagedIoStop;
    ULONG AddressWidthOverride;
    ULONG WdmDmaVersionOverride;
    ULONG Flags;
};

typedef _WDF_DMA_ENABLER_CONFIG WDF_DMA_ENABLER_CONFIG;
typedef _WDF_DMA_ENABLER_CONFIG * PWDF_DMA_ENABLER_CONFIG;

typedef PVOID WDFCONTEXT;

typedef BOOLEAN (__fastcall * EVT_WDF_PROGRAM_DMA)(
    WDFDMATRANSACTION Transaction,
    WDFDEVICE Device,
    WDFCONTEXT Context,
    WDF_DMA_DIRECTION Direction,
    PSCATTER_GATHER_LIST SgList
);

typedef EVT_WDF_PROGRAM_DMA * PFN_WDF_PROGRAM_DMA;

typedef VOID (__fastcall * EVT_WDF_DPC)(
    WDFDPC Dpc
);

typedef EVT_WDF_DPC * PFN_WDF_DPC;

struct _WDF_DPC_CONFIG {
    ULONG       Size;
    PFN_WDF_DPC EvtDpcFunc;
    BOOLEAN     AutomaticSerialization;
};

typedef _WDF_DPC_CONFIG WDF_DPC_CONFIG;
typedef WDF_DPC_CONFIG * PWDF_DPC_CONFIG;

typedef NTSTATUS (__fastcall * EVT_WDF_TRACE_CALLBACK)(
    UCHAR   minorFunction,
    PVOID   dataPath,
    ULONG   bufferLength,
    PVOID   buffer,
    PVOID   context,
    PULONG  size
);

typedef EVT_WDF_TRACE_CALLBACK * PFN_WDF_TRACE_CALLBACK;

struct _WDF_DRIVER_VERSION_AVAILABLE_PARAMS {
    ULONG Size;
    ULONG MajorVersion;
    ULONG MinorVersion;

};
typedef _WDF_DRIVER_VERSION_AVAILABLE_PARAMS WDF_DRIVER_VERSION_AVAILABLE_PARAMS;
typedef _WDF_DRIVER_VERSION_AVAILABLE_PARAMS * PWDF_DRIVER_VERSION_AVAILABLE_PARAMS;

typedef NTSTATUS (__fastcall * EVT_WDF_DEVICE_FILTER_RESOURCE_REQUIREMENTS)(
    WDFDEVICE Device,
    WDFIORESREQLIST IoResourceRequirementsList
);

typedef EVT_WDF_DEVICE_FILTER_RESOURCE_REQUIREMENTS * PFN_WDF_DEVICE_FILTER_RESOURCE_REQUIREMENTS;

typedef NTSTATUS (__fastcall * EVT_WDF_DEVICE_REMOVE_ADDED_RESOURCES)(
    WDFDEVICE Device,
    WDFCMRESLIST ResourcesRaw,
    WDFCMRESLIST ResourcesTranslated
);

typedef EVT_WDF_DEVICE_REMOVE_ADDED_RESOURCES * PFN_WDF_DEVICE_REMOVE_ADDED_RESOURCES;

struct _WDF_FDO_EVENT_CALLBACKS {
    ULONG Size;
    PFN_WDF_DEVICE_FILTER_RESOURCE_REQUIREMENTS EvtDeviceFilterAddResourceRequirements;
    PFN_WDF_DEVICE_FILTER_RESOURCE_REQUIREMENTS EvtDeviceFilterRemoveResourceRequirements;
    PFN_WDF_DEVICE_REMOVE_ADDED_RESOURCES EvtDeviceRemoveAddedResources;
};

typedef _WDF_FDO_EVENT_CALLBACKS WDF_FDO_EVENT_CALLBACKS;
typedef _WDF_FDO_EVENT_CALLBACKS * PWDF_FDO_EVENT_CALLBACKS;

typedef BOOLEAN (__fastcall * EVT_WDF_INTERRUPT_SYNCHRONIZE)(
    WDFINTERRUPT Interrupt,
    WDFCONTEXT Context
);

typedef EVT_WDF_INTERRUPT_SYNCHRONIZE * PFN_WDF_INTERRUPT_SYNCHRONIZE;

enum _WDF_INTERRUPT_POLARITY {
    WdfInterruptPolarityUnknown = 0,
    WdfInterruptActiveHigh,
    WdfInterruptActiveLow,
};

typedef _WDF_INTERRUPT_POLARITY WDF_INTERRUPT_POLARITY;
typedef _WDF_INTERRUPT_POLARITY * PWDF_INTERRUPT_POLARITY;

struct _WDF_INTERRUPT_INFO {
    ULONG                  Size;
    ULONG64                Reserved1;
    KAFFINITY              TargetProcessorSet;
    ULONG                  Reserved2;
    ULONG                  MessageNumber;
    ULONG                  Vector;
    KIRQL                  Irql;
    KINTERRUPT_MODE        Mode;
    WDF_INTERRUPT_POLARITY Polarity;
    BOOLEAN                MessageSignaled;
    UCHAR                  ShareDisposition;
    __declspec(align(8)) USHORT Group;
};

typedef _WDF_INTERRUPT_INFO WDF_INTERRUPT_INFO;
typedef _WDF_INTERRUPT_INFO * PWDF_INTERRUPT_INFO;

enum _WDF_INTERRUPT_POLICY {
    WdfIrqPolicyMachineDefault = 0,
    WdfIrqPolicyAllCloseProcessors,
    WdfIrqPolicyOneCloseProcessor,
    WdfIrqPolicyAllProcessorsInMachine,
    WdfIrqPolicySpecifiedProcessors,
    WdfIrqPolicySpreadMessagesAcrossAllProcessors,
};

typedef _WDF_INTERRUPT_POLICY WDF_INTERRUPT_POLICY;
typedef _WDF_INTERRUPT_POLICY * PWDF_INTERRUPT_POLICY;

enum _WDF_INTERRUPT_PRIORITY {
    WdfIrqPriorityUndefined = 0,
    WdfIrqPriorityLow,
    WdfIrqPriorityNormal,
    WdfIrqPriorityHigh,
};

typedef _WDF_INTERRUPT_PRIORITY WDF_INTERRUPT_PRIORITY;
typedef _WDF_INTERRUPT_PRIORITY * PWDF_INTERRUPT_PRIORITY;

enum _WDF_IO_QUEUE_STATE {
    WdfIoQueueAcceptRequests = 0x01,
    WdfIoQueueDispatchRequests = 0x02,
    WdfIoQueueNoRequests = 0x04,
    WdfIoQueueDriverNoRequests = 0x08,
    WdfIoQueuePnpHeld = 0x10,
};

typedef _WDF_IO_QUEUE_STATE WDF_IO_QUEUE_STATE;

typedef VOID (__fastcall * EVT_WDF_IO_QUEUE_STATE)(
    WDFQUEUE Queue,
    WDFCONTEXT Context
);

typedef EVT_WDF_IO_QUEUE_STATE * PFN_WDF_IO_QUEUE_STATE;

enum _WDF_IO_TARGET_STATE {
    WdfIoTargetStateUndefined = 0,
    WdfIoTargetStarted,
    WdfIoTargetStopped,
    WdfIoTargetClosedForQueryRemove,
    WdfIoTargetClosed,
    WdfIoTargetDeleted,
    WdfIoTargetPurged,
};

typedef _WDF_IO_TARGET_STATE WDF_IO_TARGET_STATE;
typedef _WDF_IO_TARGET_STATE * PWDF_IO_TARGET_STATE;

enum _WDF_IO_TARGET_OPEN_TYPE {
    WdfIoTargetOpenUndefined = 0,
    WdfIoTargetOpenUseExistingDevice = 1,
    WdfIoTargetOpenByName = 2,
    WdfIoTargetOpenReopen = 3,
    WdfIoTargetOpenLocalTargetByFile = 4,
};

typedef _WDF_IO_TARGET_OPEN_TYPE WDF_IO_TARGET_OPEN_TYPE;

enum _WDF_IO_TARGET_SENT_IO_ACTION {
    WdfIoTargetSentIoUndefined = 0,
    WdfIoTargetCancelSentIo,
    WdfIoTargetWaitForSentIoToComplete,
    WdfIoTargetLeaveSentIoPending,
};

typedef _WDF_IO_TARGET_SENT_IO_ACTION WDF_IO_TARGET_SENT_IO_ACTION;

enum _WDF_IO_TARGET_PURGE_IO_ACTION {
    WdfIoTargetPurgeIoUndefined = 0,
    WdfIoTargetPurgeIoAndWait = 1,
    WdfIoTargetPurgeIo = 2,
};

typedef _WDF_IO_TARGET_PURGE_IO_ACTION WDF_IO_TARGET_PURGE_IO_ACTION;

enum _WDF_MEMORY_DESCRIPTOR_TYPE {
    WdfMemoryDescriptorTypeInvalid = 0,
    WdfMemoryDescriptorTypeBuffer,
    WdfMemoryDescriptorTypeMdl,
    WdfMemoryDescriptorTypeHandle,
};

typedef _WDF_MEMORY_DESCRIPTOR_TYPE WDF_MEMORY_DESCRIPTOR_TYPE;

struct _WDFMEMORY_OFFSET {
    size_t BufferOffset;
    size_t BufferLength;
};

typedef _WDFMEMORY_OFFSET WDFMEMORY_OFFSET;
typedef _WDFMEMORY_OFFSET * PWDFMEMORY_OFFSET;

struct _WDF_MEMORY_DESCRIPTOR {
    WDF_MEMORY_DESCRIPTOR_TYPE Type;
    union {
        struct {
            PVOID Buffer;

            ULONG Length;
        } BufferType;
        struct {
            PMDL Mdl;

            ULONG BufferLength;
        } MdlType;
        struct {
            WDFMEMORY Memory;
            PWDFMEMORY_OFFSET Offsets;
        } HandleType;
    } u;
};

typedef _WDF_MEMORY_DESCRIPTOR WDF_MEMORY_DESCRIPTOR;
typedef _WDF_MEMORY_DESCRIPTOR * PWDF_MEMORY_DESCRIPTOR;

struct _WDF_REQUEST_SEND_OPTIONS {
    ULONG Size;
    ULONG Flags;
    LONGLONG Timeout;
};

typedef _WDF_REQUEST_SEND_OPTIONS WDF_REQUEST_SEND_OPTIONS;
typedef _WDF_REQUEST_SEND_OPTIONS * PWDF_REQUEST_SEND_OPTIONS;

typedef enum _WDF_EXECUTION_LEVEL {
    WdfExecutionLevelInvalid = 0x00,
    WdfExecutionLevelInheritFromParent,
    WdfExecutionLevelPassive,
    WdfExecutionLevelDispatch,
};

typedef _WDF_EXECUTION_LEVEL WDF_EXECUTION_LEVEL;

typedef enum _WDF_SYNCHRONIZATION_SCOPE {
    WdfSynchronizationScopeInvalid = 0x00,
    WdfSynchronizationScopeInheritFromParent,
    WdfSynchronizationScopeDevice,
    WdfSynchronizationScopeQueue,
    WdfSynchronizationScopeNone,
};

typedef _WDF_SYNCHRONIZATION_SCOPE WDF_SYNCHRONIZATION_SCOPE;

typedef VOID (__fastcall * EVT_WDF_OBJECT_CONTEXT_CLEANUP)(
    WDFOBJECT Object
);

typedef EVT_WDF_OBJECT_CONTEXT_CLEANUP * PFN_WDF_OBJECT_CONTEXT_CLEANUP;

typedef VOID (__fastcall * EVT_WDF_OBJECT_CONTEXT_DESTROY)(
    WDFOBJECT Object
);

typedef EVT_WDF_OBJECT_CONTEXT_DESTROY * PFN_WDF_OBJECT_CONTEXT_DESTROY;

typedef const struct _WDF_OBJECT_CONTEXT_TYPE_INFO * PCWDF_OBJECT_CONTEXT_TYPE_INFO;

typedef NTSTATUS (__fastcall * EVT_WDF_DEVICE_RESOURCES_QUERY)(
    WDFDEVICE Device,
    WDFCMRESLIST Resources
);

typedef EVT_WDF_DEVICE_RESOURCES_QUERY * PFN_WDF_DEVICE_RESOURCES_QUERY;

typedef NTSTATUS (__fastcall * EVT_WDF_DEVICE_RESOURCE_REQUIREMENTS_QUERY)(
    WDFDEVICE Device,
    WDFIORESREQLIST IoResourceRequirementsList
);

typedef EVT_WDF_DEVICE_RESOURCE_REQUIREMENTS_QUERY * PFN_WDF_DEVICE_RESOURCE_REQUIREMENTS_QUERY;

typedef NTSTATUS (__fastcall * EVT_WDF_DEVICE_EJECT)(
    WDFDEVICE Device
);

typedef EVT_WDF_DEVICE_EJECT * PFN_WDF_DEVICE_EJECT;

typedef NTSTATUS (__fastcall * EVT_WDF_DEVICE_SET_LOCK)(
    WDFDEVICE Device,
    BOOLEAN IsLocked
);

typedef EVT_WDF_DEVICE_SET_LOCK * PFN_WDF_DEVICE_SET_LOCK;

typedef NTSTATUS (__fastcall * EVT_WDF_DEVICE_ENABLE_WAKE_AT_BUS)(
    WDFDEVICE Device,
    SYSTEM_POWER_STATE PowerState
);

typedef EVT_WDF_DEVICE_ENABLE_WAKE_AT_BUS * PFN_WDF_DEVICE_ENABLE_WAKE_AT_BUS;

typedef VOID (__fastcall * EVT_WDF_DEVICE_DISABLE_WAKE_AT_BUS)(
    WDFDEVICE Device
);

typedef EVT_WDF_DEVICE_DISABLE_WAKE_AT_BUS * PFN_WDF_DEVICE_DISABLE_WAKE_AT_BUS;

typedef VOID (__fastcall * EVT_WDF_DEVICE_REPORTED_MISSING)(
    WDFDEVICE Device
);

typedef EVT_WDF_DEVICE_REPORTED_MISSING * PFN_WDF_DEVICE_REPORTED_MISSING;

struct _WDF_PDO_EVENT_CALLBACKS {
    ULONG Size;
    PFN_WDF_DEVICE_RESOURCES_QUERY EvtDeviceResourcesQuery;
    PFN_WDF_DEVICE_RESOURCE_REQUIREMENTS_QUERY EvtDeviceResourceRequirementsQuery;
    PFN_WDF_DEVICE_EJECT EvtDeviceEject;
    PFN_WDF_DEVICE_SET_LOCK EvtDeviceSetLock;
    PFN_WDF_DEVICE_ENABLE_WAKE_AT_BUS       EvtDeviceEnableWakeAtBus;
    PFN_WDF_DEVICE_DISABLE_WAKE_AT_BUS      EvtDeviceDisableWakeAtBus;
    PFN_WDF_DEVICE_REPORTED_MISSING EvtDeviceReportedMissing;
};

typedef _WDF_PDO_EVENT_CALLBACKS WDF_PDO_EVENT_CALLBACKS;
typedef _WDF_PDO_EVENT_CALLBACKS * PWDF_PDO_EVENT_CALLBACKS;

struct _WDF_REQUEST_REUSE_PARAMS {
    ULONG Size;
    ULONG Flags;
    NTSTATUS Status;
    PIRP NewIrp;
};

typedef _WDF_REQUEST_REUSE_PARAMS WDF_REQUEST_REUSE_PARAMS;
typedef _WDF_REQUEST_REUSE_PARAMS * PWDF_REQUEST_REUSE_PARAMS;

typedef enum _WDF_REQUEST_TYPE {
    WdfRequestTypeCreate = 0x0,
    WdfRequestTypeCreateNamedPipe = 0x1,
    WdfRequestTypeClose = 0x2,
    WdfRequestTypeRead = 0x3,
    WdfRequestTypeWrite = 0x4,
    WdfRequestTypeQueryInformation = 0x5,
    WdfRequestTypeSetInformation = 0x6,
    WdfRequestTypeQueryEA = 0x7,
    WdfRequestTypeSetEA = 0x8,
    WdfRequestTypeFlushBuffers = 0x9,
    WdfRequestTypeQueryVolumeInformation = 0xa,
    WdfRequestTypeSetVolumeInformation = 0xb,
    WdfRequestTypeDirectoryControl = 0xc,
    WdfRequestTypeFileSystemControl = 0xd,
    WdfRequestTypeDeviceControl = 0xe,
    WdfRequestTypeDeviceControlInternal = 0xf,
    WdfRequestTypeShutdown = 0x10,
    WdfRequestTypeLockControl = 0x11,
    WdfRequestTypeCleanup = 0x12,
    WdfRequestTypeCreateMailSlot = 0x13,
    WdfRequestTypeQuerySecurity = 0x14,
    WdfRequestTypeSetSecurity = 0x15,
    WdfRequestTypePower = 0x16,
    WdfRequestTypeSystemControl = 0x17,
    WdfRequestTypeDeviceChange = 0x18,
    WdfRequestTypeQueryQuota = 0x19,
    WdfRequestTypeSetQuota = 0x1A,
    WdfRequestTypePnp = 0x1B,
    WdfRequestTypeOther =0x1C,
    WdfRequestTypeUsb = 0x40,
    WdfRequestTypeNoFormat = 0xFF,
    WdfRequestTypeMax,
};

typedef _WDF_REQUEST_TYPE WDF_REQUEST_TYPE;

enum _WDF_REQUEST_REUSE_FLAGS {
    WDF_REQUEST_REUSE_NO_FLAGS = 0x00000000,
    WDF_REQUEST_REUSE_SET_NEW_IRP = 0x00000001,
};

typedef _WDF_REQUEST_REUSE_FLAGS WDF_REQUEST_REUSE_FLAGS;

enum _WDF_REQUEST_STOP_ACTION_FLAGS {
    WdfRequestStopActionInvalid = 0,
    WdfRequestStopActionSuspend = 0x01,
    WdfRequestStopActionPurge = 0x2,
    WdfRequestStopRequestCancelable = 0x10000000,
};

typedef _WDF_REQUEST_STOP_ACTION_FLAGS WDF_REQUEST_STOP_ACTION_FLAGS;

enum _WDF_REQUEST_SEND_OPTIONS_FLAGS {
    WDF_REQUEST_SEND_OPTION_TIMEOUT = 0x00000001,
    WDF_REQUEST_SEND_OPTION_SYNCHRONOUS = 0x00000002,
    WDF_REQUEST_SEND_OPTION_IGNORE_TARGET_STATE = 0x00000004,
    WDF_REQUEST_SEND_OPTION_SEND_AND_FORGET = 0x00000008,
    WDF_REQUEST_SEND_OPTION_IMPERSONATE_CLIENT = 0x00010000,
    WDF_REQUEST_SEND_OPTION_IMPERSONATION_IGNORE_FAILURE = 0x00020000,
};

typedef _WDF_REQUEST_SEND_OPTIONS_FLAGS WDF_REQUEST_SEND_OPTIONS_FLAGS;

typedef VOID (__fastcall * EVT_WDF_REQUEST_CANCEL)(
    WDFREQUEST Request
);

typedef EVT_WDF_REQUEST_CANCEL * PFN_WDF_REQUEST_CANCEL;

union _WDF_USB_CONTROL_SETUP_PACKET {
    struct {
        union {
            struct {
                BYTE Recipient:2;
                BYTE Reserved:3;
                BYTE Type:2;
                BYTE Dir:1;
            } Request;
            BYTE Byte;
        } bm;
        BYTE bRequest;
        union {
            struct {
                BYTE LowByte;
                BYTE HiByte;
            } Bytes;
            USHORT Value;
        } wValue;
        union {
            struct {
                BYTE LowByte;
                BYTE HiByte;
            } Bytes;
            USHORT Value;
        } wIndex;
        USHORT wLength;
    } Packet;
    struct {
        BYTE Bytes[8];
    } Generic;
};

typedef _WDF_USB_CONTROL_SETUP_PACKET WDF_USB_CONTROL_SETUP_PACKET;
typedef _WDF_USB_CONTROL_SETUP_PACKET * PWDF_USB_CONTROL_SETUP_PACKET;

enum _WDF_USB_REQUEST_TYPE {
    WdfUsbRequestTypeInvalid = 0,
    WdfUsbRequestTypeNoFormat,
    WdfUsbRequestTypeDeviceString,
    WdfUsbRequestTypeDeviceControlTransfer,
    WdfUsbRequestTypeDeviceUrb,
    WdfUsbRequestTypePipeWrite,
    WdfUsbRequestTypePipeRead,
    WdfUsbRequestTypePipeAbort,
    WdfUsbRequestTypePipeReset,
    WdfUsbRequestTypePipeUrb,
};

typedef _WDF_USB_REQUEST_TYPE WDF_USB_REQUEST_TYPE;
typedef _WDF_USB_REQUEST_TYPE * PWDF_USB_REQUEST_TYPE;

struct _WDF_USB_REQUEST_COMPLETION_PARAMS {
    USBD_STATUS UsbdStatus;
    WDF_USB_REQUEST_TYPE Type;
    union {
        struct {
            WDFMEMORY Buffer;
            USHORT LangID;
            UCHAR StringIndex;
            UCHAR RequiredSize;
        } DeviceString;
        struct {
            WDFMEMORY Buffer;
            WDF_USB_CONTROL_SETUP_PACKET SetupPacket;
            ULONG Length;
        } DeviceControlTransfer;
        struct {
            WDFMEMORY Buffer;
        } DeviceUrb;
        struct {
            WDFMEMORY Buffer;
            size_t Length;
            size_t Offset;
        } PipeWrite;
        struct {
            WDFMEMORY Buffer;
            size_t Length;
            size_t Offset;
        } PipeRead;
        struct {
            WDFMEMORY Buffer;
        } PipeUrb;
    } Parameters;
};

typedef _WDF_USB_REQUEST_COMPLETION_PARAMS WDF_USB_REQUEST_COMPLETION_PARAMS;
typedef _WDF_USB_REQUEST_COMPLETION_PARAMS * PWDF_USB_REQUEST_COMPLETION_PARAMS;

struct _WDF_REQUEST_COMPLETION_PARAMS {
    ULONG Size;
    WDF_REQUEST_TYPE Type;
    IO_STATUS_BLOCK IoStatus;
    union {
        struct {
            WDFMEMORY Buffer;
            size_t Length;
            size_t Offset;
        } Write;
        struct {
            WDFMEMORY Buffer;
            size_t Length;
            size_t Offset;
        } Read;
        struct {
            ULONG IoControlCode;

            struct {
                WDFMEMORY Buffer;
                size_t Offset;
            } Input;
            struct {
                WDFMEMORY Buffer;
                size_t Offset;
                size_t Length;
            } Output;
        } Ioctl;
        struct {
            union {
                PVOID Ptr;
                ULONG_PTR Value;
            } Argument1;
            union {
                PVOID Ptr;
                ULONG_PTR Value;
            } Argument2;
            union {
                PVOID Ptr;
                ULONG_PTR Value;
            } Argument3;
            union {
                PVOID Ptr;
                ULONG_PTR Value;
            } Argument4;
        } Others;
        struct {
            PWDF_USB_REQUEST_COMPLETION_PARAMS Completion;
        } Usb;
    } Parameters;
};

typedef _WDF_REQUEST_COMPLETION_PARAMS WDF_REQUEST_COMPLETION_PARAMS;
typedef _WDF_REQUEST_COMPLETION_PARAMS * PWDF_REQUEST_COMPLETION_PARAMS;

typedef VOID (__fastcall * EVT_WDF_REQUEST_COMPLETION_ROUTINE)(
    WDFREQUEST Request,
    WDFIOTARGET Target,
    PWDF_REQUEST_COMPLETION_PARAMS Params,
    WDFCONTEXT Context
);

typedef EVT_WDF_REQUEST_COMPLETION_ROUTINE * PFN_WDF_REQUEST_COMPLETION_ROUTINE;

typedef LONG USBD_STATUS;

enum _WDF_USB_BMREQUEST_DIRECTION {
    BmRequestHostToDevice = BMREQUEST_HOST_TO_DEVICE,
    BmRequestDeviceToHost = BMREQUEST_DEVICE_TO_HOST,
};

typedef _WDF_USB_BMREQUEST_DIRECTION WDF_USB_BMREQUEST_DIRECTION;

enum _WDF_USB_BMREQUEST_TYPE {
    BmRequestStandard = BMREQUEST_STANDARD,
    BmRequestClass = BMREQUEST_CLASS,
    BmRequestVendor = BMREQUEST_VENDOR,
};

typedef _WDF_USB_BMREQUEST_TYPE WDF_USB_BMREQUEST_TYPE;

enum _WDF_USB_BMREQUEST_RECIPIENT {
    BmRequestToDevice = BMREQUEST_TO_DEVICE,
    BmRequestToInterface = BMREQUEST_TO_INTERFACE,
    BmRequestToEndpoint = BMREQUEST_TO_ENDPOINT,
    BmRequestToOther = BMREQUEST_TO_OTHER,
};

typedef _WDF_USB_BMREQUEST_RECIPIENT WDF_USB_BMREQUEST_RECIPIENT;

enum _WDF_USB_PIPE_TYPE {
    WdfUsbPipeTypeInvalid = 0,
    WdfUsbPipeTypeControl,
    WdfUsbPipeTypeIsochronous,
    WdfUsbPipeTypeBulk,
    WdfUsbPipeTypeInterrupt,
};

typedef _WDF_USB_PIPE_TYPE WDF_USB_PIPE_TYPE;

enum _WdfUsbTargetDeviceSelectConfigType {
    WdfUsbTargetDeviceSelectConfigTypeInvalid = 0,
    WdfUsbTargetDeviceSelectConfigTypeDeconfig = 1,
    WdfUsbTargetDeviceSelectConfigTypeSingleInterface = 2,
    WdfUsbTargetDeviceSelectConfigTypeMultiInterface = 3,
    WdfUsbTargetDeviceSelectConfigTypeInterfacesPairs = 4,
    WdfUsbTargetDeviceSelectConfigTypeInterfacesDescriptor = 5,
    WdfUsbTargetDeviceSelectConfigTypeUrb = 6,
};

typedef _WdfUsbTargetDeviceSelectConfigType WdfUsbTargetDeviceSelectConfigType;

enum _WdfUsbTargetDeviceSelectSettingType {
    WdfUsbInterfaceSelectSettingTypeDescriptor = 0x10,
    WdfUsbInterfaceSelectSettingTypeSetting = 0x11,
    WdfUsbInterfaceSelectSettingTypeUrb = 0x12,
};

typedef _WdfUsbTargetDeviceSelectSettingType WdfUsbTargetDeviceSelectSettingType;

typedef enum _WDF_USB_DEVICE_TRAITS {
    WDF_USB_DEVICE_TRAIT_SELF_POWERED =        0x00000001,
    WDF_USB_DEVICE_TRAIT_REMOTE_WAKE_CAPABLE = 0x00000002,
    WDF_USB_DEVICE_TRAIT_AT_HIGH_SPEED =       0x00000004,
};

typedef _WDF_USB_DEVICE_TRAITS WDF_USB_DEVICE_TRAITS;

typedef VOID (__fastcall * EVT_WDF_TIMER)(
    WDFTIMER Timer
);

typedef EVT_WDF_TIMER * PFN_WDF_TIMER;

struct _WDF_TIMER_CONFIG {
    ULONG Size;
    PFN_WDF_TIMER EvtTimerFunc;
    ULONG Period;
    BOOLEAN AutomaticSerialization;
    ULONG TolerableDelay;
    __declspec(align(8)) BOOLEAN UseHighResolutionTimer;
};

typedef _WDF_TIMER_CONFIG WDF_TIMER_CONFIG;
typedef _WDF_TIMER_CONFIG * PWDF_TIMER_CONFIG;

struct _USBD_VERSION_INFORMATION {
  ULONG USBDI_Version;
  ULONG Supported_USB_Version;
};

typedef _USBD_VERSION_INFORMATION USBD_VERSION_INFORMATION;
typedef _USBD_VERSION_INFORMATION * PUSBD_VERSION_INFORMATION;

struct _WDF_USB_DEVICE_INFORMATION {
    ULONG Size;
    USBD_VERSION_INFORMATION UsbdVersionInformation;
    ULONG HcdPortCapabilities;
    ULONG Traits;
};

typedef _WDF_USB_DEVICE_INFORMATION WDF_USB_DEVICE_INFORMATION;
typedef _WDF_USB_DEVICE_INFORMATION * PWDF_USB_DEVICE_INFORMATION;

struct _WDF_USB_INTERFACE_SETTING_PAIR {
    WDFUSBINTERFACE UsbInterface;
    UCHAR SettingIndex;
};

typedef _WDF_USB_INTERFACE_SETTING_PAIR WDF_USB_INTERFACE_SETTING_PAIR;
typedef _WDF_USB_INTERFACE_SETTING_PAIR * PWDF_USB_INTERFACE_SETTING_PAIR;

struct _WDF_USB_DEVICE_SELECT_CONFIG_PARAMS {
    ULONG Size;
    WdfUsbTargetDeviceSelectConfigType Type;
    union {
        struct {
            PUSB_CONFIGURATION_DESCRIPTOR ConfigurationDescriptor;
            PUSB_INTERFACE_DESCRIPTOR * InterfaceDescriptors;
            ULONG NumInterfaceDescriptors;
        } Descriptor;
        struct {
            PURB Urb;
        } Urb;
        struct {
            UCHAR   NumberConfiguredPipes;
            WDFUSBINTERFACE ConfiguredUsbInterface;
        } SingleInterface;
        struct {
            UCHAR NumberInterfaces;
            PWDF_USB_INTERFACE_SETTING_PAIR Pairs;
            UCHAR NumberOfConfiguredInterfaces;
        } MultiInterface;
    } Types;
};

typedef _WDF_USB_DEVICE_SELECT_CONFIG_PARAMS WDF_USB_DEVICE_SELECT_CONFIG_PARAMS;
typedef _WDF_USB_DEVICE_SELECT_CONFIG_PARAMS * PWDF_USB_DEVICE_SELECT_CONFIG_PARAMS;

struct _WDF_USB_PIPE_INFORMATION {
    ULONG Size;
    ULONG MaximumPacketSize;
    UCHAR EndpointAddress;
    UCHAR Interval;
    UCHAR SettingIndex;
    WDF_USB_PIPE_TYPE PipeType;
    ULONG  MaximumTransferSize;
};

typedef _WDF_USB_PIPE_INFORMATION WDF_USB_PIPE_INFORMATION;
typedef _WDF_USB_PIPE_INFORMATION * PWDF_USB_PIPE_INFORMATION;


struct _WDF_USB_INTERFACE_SELECT_SETTING_PARAMS {
    ULONG Size;
    WdfUsbTargetDeviceSelectSettingType Type;
    union {
        struct {
            PUSB_INTERFACE_DESCRIPTOR InterfaceDescriptor;
        } Descriptor;

        struct {
            UCHAR SettingIndex;
        } Interface;

        struct {
            PURB Urb;
        } Urb;
    } Types;
};

typedef _WDF_USB_INTERFACE_SELECT_SETTING_PARAMS WDF_USB_INTERFACE_SELECT_SETTING_PARAMS;
typedef _WDF_USB_INTERFACE_SELECT_SETTING_PARAMS * PWDF_USB_INTERFACE_SELECT_SETTING_PARAMS;

enum _WDF_WMI_PROVIDER_CONTROL {
    WdfWmiControlInvalid = 0,
    WdfWmiEventControl,
    WdfWmiInstanceControl,
};

typedef _WDF_WMI_PROVIDER_CONTROL WDF_WMI_PROVIDER_CONTROL;

typedef NTSTATUS (__fastcall * EVT_WDF_WMI_PROVIDER_FUNCTION_CONTROL)(
    WDFWMIPROVIDER WmiProvider,
    WDF_WMI_PROVIDER_CONTROL Control,
    BOOLEAN Enable
);

typedef EVT_WDF_WMI_PROVIDER_FUNCTION_CONTROL * PFN_WDF_WMI_PROVIDER_FUNCTION_CONTROL;

struct _WDF_WMI_PROVIDER_CONFIG {
    ULONG Size;
    GUID Guid;
    ULONG Flags;
    ULONG MinInstanceBufferSize;
    PFN_WDF_WMI_PROVIDER_FUNCTION_CONTROL EvtWmiProviderFunctionControl;
};

typedef _WDF_WMI_PROVIDER_CONFIG WDF_WMI_PROVIDER_CONFIG;
typedef _WDF_WMI_PROVIDER_CONFIG * PWDF_WMI_PROVIDER_CONFIG;

typedef NTSTATUS (__fastcall * EVT_WDF_WMI_INSTANCE_QUERY_INSTANCE)(
    WDFWMIINSTANCE WmiInstance,
    ULONG OutBufferSize,
    PVOID OutBuffer,
    PULONG BufferUsed
);

typedef EVT_WDF_WMI_INSTANCE_QUERY_INSTANCE * PFN_WDF_WMI_INSTANCE_QUERY_INSTANCE;

typedef NTSTATUS (__fastcall * EVT_WDF_WMI_INSTANCE_SET_INSTANCE)(
    WDFWMIINSTANCE WmiInstance,
    ULONG InBufferSize,
    PVOID InBuffer
);

typedef EVT_WDF_WMI_INSTANCE_SET_INSTANCE * PFN_WDF_WMI_INSTANCE_SET_INSTANCE;

typedef NTSTATUS (__fastcall * EVT_WDF_WMI_INSTANCE_SET_ITEM)(
    WDFWMIINSTANCE WmiInstance,
    ULONG DataItemId,
    ULONG InBufferSize,
    PVOID InBuffer
);

typedef EVT_WDF_WMI_INSTANCE_SET_ITEM * PFN_WDF_WMI_INSTANCE_SET_ITEM;

typedef NTSTATUS (__fastcall * EVT_WDF_WMI_INSTANCE_EXECUTE_METHOD)(
    WDFWMIINSTANCE WmiInstance,
    ULONG MethodId,
    ULONG InBufferSize,
    ULONG OutBufferSize,
    PVOID Buffer,
    PULONG BufferUsed
);

typedef EVT_WDF_WMI_INSTANCE_EXECUTE_METHOD * PFN_WDF_WMI_INSTANCE_EXECUTE_METHOD;

struct _WDF_WMI_INSTANCE_CONFIG {
    ULONG Size;
    WDFWMIPROVIDER Provider;
    PWDF_WMI_PROVIDER_CONFIG ProviderConfig;
    BOOLEAN UseContextForQuery;
    BOOLEAN Register;
    PFN_WDF_WMI_INSTANCE_QUERY_INSTANCE EvtWmiInstanceQueryInstance;
    PFN_WDF_WMI_INSTANCE_SET_INSTANCE EvtWmiInstanceSetInstance;
    PFN_WDF_WMI_INSTANCE_SET_ITEM EvtWmiInstanceSetItem;
    PFN_WDF_WMI_INSTANCE_EXECUTE_METHOD EvtWmiInstanceExecuteMethod;
};

typedef _WDF_WMI_INSTANCE_CONFIG WDF_WMI_INSTANCE_CONFIG;
typedef _WDF_WMI_INSTANCE_CONFIG * PWDF_WMI_INSTANCE_CONFIG;

struct _GROUP_AFFINITY {
  KAFFINITY Mask;
  WORD      Group;
  WORD      Reserved[3];
};

typedef _GROUP_AFFINITY GROUP_AFFINITY;
typedef _GROUP_AFFINITY * PGROUP_AFFINITY;

struct _WDF_INTERRUPT_EXTENDED_POLICY {
    ULONG                   Size;
    WDF_INTERRUPT_POLICY    Policy;
    WDF_INTERRUPT_PRIORITY  Priority;
    GROUP_AFFINITY          TargetProcessorSetAndGroup;
};

typedef _WDF_INTERRUPT_EXTENDED_POLICY WDF_INTERRUPT_EXTENDED_POLICY;
typedef _WDF_INTERRUPT_EXTENDED_POLICY * PWDF_INTERRUPT_EXTENDED_POLICY;

enum _WDF_IO_FORWARD_PROGRESS_ACTION {
    WdfIoForwardProgressActionInvalid = 0x0,
    WdfIoForwardProgressActionFailRequest,
    WdfIoForwardProgressActionUseReservedRequest
};

typedef _WDF_IO_FORWARD_PROGRESS_ACTION WDF_IO_FORWARD_PROGRESS_ACTION;

enum _WDF_IO_FORWARD_PROGRESS_RESERVED_POLICY  {
  WdfIoForwardProgressInvalidPolicy =0x0,
  WdfIoForwardProgressReservedPolicyAlwaysUseReservedRequest,
  WdfIoForwardProgressReservedPolicyUseExamine,
  WdfIoForwardProgressReservedPolicyPagingIO
};

typedef _WDF_IO_FORWARD_PROGRESS_RESERVED_POLICY WDF_IO_FORWARD_PROGRESS_RESERVED_POLICY;

typedef NTSTATUS (__fastcall * EVT_WDF_IO_ALLOCATE_RESOURCES_FOR_RESERVED_REQUEST)(
    WDFQUEUE Queue,
    WDFREQUEST Request
);

typedef EVT_WDF_IO_ALLOCATE_RESOURCES_FOR_RESERVED_REQUEST * PFN_WDF_IO_ALLOCATE_RESOURCES_FOR_RESERVED_REQUEST;

typedef NTSTATUS (__fastcall * EVT_WDF_IO_ALLOCATE_REQUEST_RESOURCES)(
    WDFQUEUE Queue,
    WDFREQUEST Request
);

typedef EVT_WDF_IO_ALLOCATE_REQUEST_RESOURCES * PFN_WDF_IO_ALLOCATE_REQUEST_RESOURCES;

typedef WDF_IO_FORWARD_PROGRESS_ACTION (__fastcall * EVT_WDF_IO_WDM_IRP_FOR_FORWARD_PROGRESS)(
    WDFQUEUE Queue,
    PIRP Irp
);

typedef EVT_WDF_IO_WDM_IRP_FOR_FORWARD_PROGRESS * PFN_WDF_IO_WDM_IRP_FOR_FORWARD_PROGRESS;

struct _WDF_IO_FORWARD_PROGRESS_RESERVED_POLICY_SETTINGS {
    union {
        struct {
          PFN_WDF_IO_WDM_IRP_FOR_FORWARD_PROGRESS     EvtIoWdmIrpForForwardProgress;
        } ExaminePolicy;
    } Policy;
};

typedef _WDF_IO_FORWARD_PROGRESS_RESERVED_POLICY_SETTINGS WDF_IO_FORWARD_PROGRESS_RESERVED_POLICY_SETTINGS;

struct _WDF_IO_QUEUE_FORWARD_PROGRESS_POLICY {
    ULONG  Size;
    ULONG TotalForwardProgressRequests;
    WDF_IO_FORWARD_PROGRESS_RESERVED_POLICY ForwardProgressReservedPolicy;
    WDF_IO_FORWARD_PROGRESS_RESERVED_POLICY_SETTINGS ForwardProgressReservePolicySettings;
    PFN_WDF_IO_ALLOCATE_RESOURCES_FOR_RESERVED_REQUEST EvtIoAllocateResourcesForReservedRequest;
    PFN_WDF_IO_ALLOCATE_REQUEST_RESOURCES  EvtIoAllocateRequestResources;
};

typedef _WDF_IO_QUEUE_FORWARD_PROGRESS_POLICY WDF_IO_QUEUE_FORWARD_PROGRESS_POLICY;
typedef _WDF_IO_QUEUE_FORWARD_PROGRESS_POLICY * PWDF_IO_QUEUE_FORWARD_PROGRESS_POLICY;

enum _WDF_REQUEST_FORWARD_OPTIONS_FLAGS {
    WDF_REQUEST_FORWARD_OPTION_SEND_AND_FORGET = 0x00000001
};

typedef _WDF_REQUEST_FORWARD_OPTIONS_FLAGS WDF_REQUEST_FORWARD_OPTIONS_FLAGS;

struct _WDF_REQUEST_FORWARD_OPTIONS {
    ULONG Size;
    ULONG Flags;
};

typedef _WDF_REQUEST_FORWARD_OPTIONS WDF_REQUEST_FORWARD_OPTIONS;
typedef _WDF_REQUEST_FORWARD_OPTIONS * PWDF_REQUEST_FORWARD_OPTIONS;

enum _WDF_REMOVE_LOCK_OPTIONS_FLAGS {
    WDF_REMOVE_LOCK_OPTION_ACQUIRE_FOR_IO = 0x00000001
};

typedef _WDF_REMOVE_LOCK_OPTIONS_FLAGS WDF_REMOVE_LOCK_OPTIONS_FLAGS;

struct _WDF_REMOVE_LOCK_OPTIONS {
    ULONG Size;
    ULONG Flags;
};

typedef _WDF_REMOVE_LOCK_OPTIONS WDF_REMOVE_LOCK_OPTIONS;
typedef _WDF_REMOVE_LOCK_OPTIONS * PWDF_REMOVE_LOCK_OPTIONS;

typedef NTSTATUS (__fastcall * EVT_WDFDEVICE_WDM_IRP_DISPATCH)(
    WDFDEVICE Device,
    UCHAR MajorFunction,
    UCHAR MinorFunction,
    ULONG Code,
    WDFCONTEXT DriverContext,
    PIRP Irp,
    WDFCONTEXT DispatchContext
);

typedef EVT_WDFDEVICE_WDM_IRP_DISPATCH * PFN_WDFDEVICE_WDM_IRP_DISPATCH;

struct _WDF_DMA_SYSTEM_PROFILE_CONFIG {
    ULONG                 Size;
    BOOLEAN               DemandMode;
    BOOLEAN               LoopedTransfer;
    DMA_WIDTH             DmaWidth;
    PHYSICAL_ADDRESS      DeviceAddress;
    PCM_PARTIAL_RESOURCE_DESCRIPTOR DmaDescriptor;
};

typedef _WDF_DMA_SYSTEM_PROFILE_CONFIG WDF_DMA_SYSTEM_PROFILE_CONFIG;
typedef _WDF_DMA_SYSTEM_PROFILE_CONFIG * PWDF_DMA_SYSTEM_PROFILE_CONFIG;

typedef BOOLEAN (__fastcall * EVT_WDF_DMA_TRANSACTION_CONFIGURE_DMA_CHANNEL)(
    WDFDMATRANSACTION DmaTransaction,
    WDFDEVICE Device,
    PVOID Context,
    PMDL Mdl, 
    size_t Offset,
    size_t Length
);

typedef EVT_WDF_DMA_TRANSACTION_CONFIGURE_DMA_CHANNEL * PFN_WDF_DMA_TRANSACTION_CONFIGURE_DMA_CHANNEL;

enum _DMA_COMPLETION_STATUS {
  DmaComplete,
  DmaAborted,
  DmaError,
  DmaCancelled
};

typedef _DMA_COMPLETION_STATUS DMA_COMPLETION_STATUS;

typedef VOID (__fastcall * EVT_WDF_DMA_TRANSACTION_DMA_TRANSFER_COMPLETE)(
    WDFDMATRANSACTION Transaction,
    WDFDEVICE Device,
    WDFCONTEXT Context,
    WDF_DMA_DIRECTION Direction,
    DMA_COMPLETION_STATUS Status
);

typedef EVT_WDF_DMA_TRANSACTION_DMA_TRANSFER_COMPLETE * PFN_WDF_DMA_TRANSACTION_DMA_TRANSFER_COMPLETE;

typedef VOID (__fastcall * EVT_WDF_RESERVE_DMA)(
    WDFDMATRANSACTION DmaTransaction,
    PVOID Context
);

typedef EVT_WDF_RESERVE_DMA * PFN_WDF_RESERVE_DMA;

struct _WDF_USB_DEVICE_CREATE_CONFIG {
    ULONG   Size;
    ULONG   USBDClientContractVersion;

};

typedef _WDF_USB_DEVICE_CREATE_CONFIG WDF_USB_DEVICE_CREATE_CONFIG;
typedef _WDF_USB_DEVICE_CREATE_CONFIG * PWDF_USB_DEVICE_CREATE_CONFIG;

typedef NTSTATUS (__fastcall * EVT_WDFDEVICE_WDM_IRP_PREPROCESS)(
    WDFDEVICE Device,
    PIRP Irp
);

typedef EVT_WDFDEVICE_WDM_IRP_PREPROCESS *PFN_WDFDEVICE_WDM_IRP_PREPROCESS;

typedef NTSTATUS (__fastcall * EVT_WDFDEVICE_WDM_IRP_DISPATCH)(
    WDFDEVICE Device,
    UCHAR MajorFunction,
    UCHAR MinorFunction,
    ULONG Code,
    WDFCONTEXT DriverContext,
    PIRP Irp,
    WDFCONTEXT DispatchContext
);

typedef EVT_WDFDEVICE_WDM_IRP_DISPATCH *PFN_WDFDEVICE_WDM_IRP_DISPATCH;

typedef VOID (__fastcall * EVT_WDF_IO_IN_CALLER_CONTEXT)(
    WDFDEVICE Device,
    WDFREQUEST Request
);

typedef EVT_WDF_IO_IN_CALLER_CONTEXT *PFN_WDF_IO_IN_CALLER_CONTEXT;

typedef NTSTATUS (__fastcall * EVT_WDFDEVICE_WDM_POST_PO_FX_REGISTER_DEVICE)(
    WDFDEVICE Device,
    POHANDLE PoHandle
);

typedef EVT_WDFDEVICE_WDM_POST_PO_FX_REGISTER_DEVICE *PFN_WDFDEVICE_WDM_POST_PO_FX_REGISTER_DEVICE;

typedef VOID (__fastcall * EVT_WDFDEVICE_WDM_PRE_PO_FX_UNREGISTER_DEVICE)(
    WDFDEVICE Device,
    POHANDLE PoHandle
);

typedef EVT_WDFDEVICE_WDM_PRE_PO_FX_UNREGISTER_DEVICE *PFN_WDFDEVICE_WDM_PRE_PO_FX_UNREGISTER_DEVICE;

struct _PO_FX_COMPONENT_IDLE_STATE {
  ULONGLONG TransitionLatency;
  ULONGLONG ResidencyRequirement;
  ULONG     NominalPower;
};

typedef _PO_FX_COMPONENT_IDLE_STATE PO_FX_COMPONENT_IDLE_STATE;
typedef _PO_FX_COMPONENT_IDLE_STATE * PPO_FX_COMPONENT_IDLE_STATE;

struct _PO_FX_COMPONENT_V1 {
  GUID                        Id;
  ULONG                       IdleStateCount;
  ULONG                       DeepestWakeableIdleState;
  PPO_FX_COMPONENT_IDLE_STATE IdleStates;
};

typedef _PO_FX_COMPONENT_V1 PO_FX_COMPONENT_V1;
typedef _PO_FX_COMPONENT_V1 * PPO_FX_COMPONENT_V1;

typedef PO_FX_COMPONENT_V1 PO_FX_COMPONENT;
typedef PPO_FX_COMPONENT_V1 PPO_FX_COMPONENT;

typedef void (__fastcall * PO_FX_COMPONENT_ACTIVE_CONDITION_CALLBACK)(
  PVOID Context,
  ULONG Component
);

typedef PO_FX_COMPONENT_ACTIVE_CONDITION_CALLBACK PPO_FX_COMPONENT_ACTIVE_CONDITION_CALLBACK;

typedef void (__fastcall * PO_FX_COMPONENT_IDLE_CONDITION_CALLBACK)(
  PVOID Context,
  ULONG Component
);

typedef PO_FX_COMPONENT_IDLE_CONDITION_CALLBACK PPO_FX_COMPONENT_IDLE_CONDITION_CALLBACK;

typedef void (__fastcall * PO_FX_COMPONENT_IDLE_STATE_CALLBACK)(
  PVOID Context,
  ULONG Component,
  ULONG State
);

typedef PO_FX_COMPONENT_IDLE_STATE_CALLBACK PPO_FX_COMPONENT_IDLE_STATE_CALLBACK;

typedef NTSTATUS (__fastcall * PO_FX_POWER_CONTROL_CALLBACK)(
  PVOID DeviceContext,
  LPCGUID PowerControlCode,
  PVOID InBuffer,
  SIZE_T InBufferSize,
  PVOID OutBuffer,
  SIZE_T OutBufferSize,
  PSIZE_T BytesReturned
);

typedef PO_FX_POWER_CONTROL_CALLBACK PPO_FX_POWER_CONTROL_CALLBACK;

struct _WDF_POWER_FRAMEWORK_SETTINGS {
    ULONG Size;
    PFN_WDFDEVICE_WDM_POST_PO_FX_REGISTER_DEVICE EvtDeviceWdmPostPoFxRegisterDevice;
    PFN_WDFDEVICE_WDM_PRE_PO_FX_UNREGISTER_DEVICE EvtDeviceWdmPrePoFxUnregisterDevice;
    PPO_FX_COMPONENT Component;
    PPO_FX_COMPONENT_ACTIVE_CONDITION_CALLBACK ComponentActiveConditionCallback;
    PPO_FX_COMPONENT_IDLE_CONDITION_CALLBACK ComponentIdleConditionCallback;
    PPO_FX_COMPONENT_IDLE_STATE_CALLBACK ComponentIdleStateCallback;
    PPO_FX_POWER_CONTROL_CALLBACK PowerControlCallback;
    PVOID PoFxDeviceContext;
};

typedef _WDF_POWER_FRAMEWORK_SETTINGS WDF_POWER_FRAMEWORK_SETTINGS;
typedef _WDF_POWER_FRAMEWORK_SETTINGS * PWDF_POWER_FRAMEWORK_SETTINGS;

enum _WDF_RELEASE_HARDWARE_ORDER_ON_FAILURE {
    WdfReleaseHardwareOrderOnFailureInvalid = 0,
    WdfReleaseHardwareOrderOnFailureEarly,
    WdfReleaseHardwareOrderOnFailureAfterDescendants,
};

typedef _WDF_RELEASE_HARDWARE_ORDER_ON_FAILURE WDF_RELEASE_HARDWARE_ORDER_ON_FAILURE;
typedef _WDF_RELEASE_HARDWARE_ORDER_ON_FAILURE * PWDF_RELEASE_HARDWARE_ORDER_ON_FAILURE;

struct _WDF_IO_TYPE_CONFIG {
    ULONG Size;
    WDF_DEVICE_IO_TYPE ReadWriteIoType;
    WDF_DEVICE_IO_TYPE DeviceControlIoType;
    ULONG DirectTransferThreshold;

};

typedef _WDF_IO_TYPE_CONFIG WDF_IO_TYPE_CONFIG;
typedef _WDF_IO_TYPE_CONFIG * PWDF_IO_TYPE_CONFIG;

typedef GUID  DEVPROPGUID, * PDEVPROPGUID;
typedef ULONG DEVPROPID, *PDEVPROPID;

struct _DEVPROPKEY {
  DEVPROPGUID fmtid;
  DEVPROPID   pid;
};

typedef _DEVPROPKEY DEVPROPKEY;
typedef _DEVPROPKEY * PDEVPROPKEY;

struct _WDF_DEVICE_PROPERTY_DATA {
    ULONG Size;
    const DEVPROPKEY * PropertyKey;
    LCID Lcid;
    ULONG Flags;
};

typedef _WDF_DEVICE_PROPERTY_DATA WDF_DEVICE_PROPERTY_DATA;
typedef _WDF_DEVICE_PROPERTY_DATA * PWDF_DEVICE_PROPERTY_DATA;

typedef ULONG DEVPROPTYPE, *PDEVPROPTYPE;

struct _WDF_TASK_SEND_OPTIONS {
    ULONG Size;
    ULONG Flags;
    LONGLONG Timeout;
};

typedef _WDF_TASK_SEND_OPTIONS WDF_TASK_SEND_OPTIONS;
typedef _WDF_TASK_SEND_OPTIONS * PWDF_TASK_SEND_OPTIONS;

typedef VOID (__fastcall * EVT_WDF_USB_READER_COMPLETION_ROUTINE)(
    WDFUSBPIPE Pipe,
    WDFMEMORY Buffer,
    size_t NumBytesTransferred,
    WDFCONTEXT Context
);

typedef EVT_WDF_USB_READER_COMPLETION_ROUTINE *PFN_WDF_USB_READER_COMPLETION_ROUTINE;

typedef BOOLEAN (__fastcall * EVT_WDF_USB_READERS_FAILED)(
    WDFUSBPIPE Pipe,
    NTSTATUS Status,
    USBD_STATUS UsbdStatus
);

typedef EVT_WDF_USB_READERS_FAILED *PFN_WDF_USB_READERS_FAILED;

struct _WDF_USB_CONTINUOUS_READER_CONFIG {
    ULONG Size;
    size_t TransferLength;
    size_t HeaderLength;
    size_t TrailerLength;
    UCHAR NumPendingReads;
    PWDF_OBJECT_ATTRIBUTES BufferAttributes;
    PFN_WDF_USB_READER_COMPLETION_ROUTINE EvtUsbTargetPipeReadComplete;
    WDFCONTEXT EvtUsbTargetPipeReadCompleteContext;
    PFN_WDF_USB_READERS_FAILED EvtUsbTargetPipeReadersFailed;
};

typedef _WDF_USB_CONTINUOUS_READER_CONFIG WDF_USB_CONTINUOUS_READER_CONFIG;
typedef _WDF_USB_CONTINUOUS_READER_CONFIG * PWDF_USB_CONTINUOUS_READER_CONFIG;

//====

typedef NTSTATUS (__fastcall * PFN_WDFCHILDLISTCREATE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device,
    PWDF_CHILD_LIST_CONFIG Config,
    PWDF_OBJECT_ATTRIBUTES ChildListAttributes,
    WDFCHILDLIST* ChildList
);

typedef WDFDEVICE (__fastcall * PFN_WDFCHILDLISTGETDEVICE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFCHILDLIST ChildList
);

typedef WDFDEVICE (__fastcall * PFN_WDFCHILDLISTRETRIEVEPDO)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFCHILDLIST ChildList,
    PWDF_CHILD_RETRIEVE_INFO RetrieveInfo
);

typedef NTSTATUS (__fastcall * PFN_WDFCHILDLISTRETRIEVEADDRESSDESCRIPTION)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFCHILDLIST ChildList,
    PWDF_CHILD_IDENTIFICATION_DESCRIPTION_HEADER IdentificationDescription,
    PWDF_CHILD_ADDRESS_DESCRIPTION_HEADER AddressDescription
);

typedef VOID (__fastcall * PFN_WDFCHILDLISTBEGINSCAN)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFCHILDLIST ChildList
);

typedef VOID (__fastcall * PFN_WDFCHILDLISTENDSCAN)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFCHILDLIST ChildList
);

typedef VOID (__fastcall * PFN_WDFCHILDLISTBEGINITERATION)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFCHILDLIST ChildList,
    PWDF_CHILD_LIST_ITERATOR Iterator
);

typedef NTSTATUS (__fastcall * PFN_WDFCHILDLISTRETRIEVENEXTDEVICE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFCHILDLIST ChildList,
    PWDF_CHILD_LIST_ITERATOR Iterator,
    WDFDEVICE* Device,
    PWDF_CHILD_RETRIEVE_INFO Info
);

typedef VOID (__fastcall * PFN_WDFCHILDLISTENDITERATION)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFCHILDLIST ChildList,
    PWDF_CHILD_LIST_ITERATOR Iterator
);

typedef NTSTATUS (__fastcall * PFN_WDFCHILDLISTADDORUPDATECHILDDESCRIPTIONASPRESENT)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFCHILDLIST ChildList,
    PWDF_CHILD_IDENTIFICATION_DESCRIPTION_HEADER IdentificationDescription,
    PWDF_CHILD_ADDRESS_DESCRIPTION_HEADER AddressDescription
);

typedef NTSTATUS (__fastcall * PFN_WDFCHILDLISTUPDATECHILDDESCRIPTIONASMISSING)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFCHILDLIST ChildList,
    PWDF_CHILD_IDENTIFICATION_DESCRIPTION_HEADER IdentificationDescription
);

typedef VOID (__fastcall * PFN_WDFCHILDLISTUPDATEALLCHILDDESCRIPTIONSASPRESENT)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFCHILDLIST ChildList
);

typedef BOOLEAN (__fastcall * PFN_WDFCHILDLISTREQUESTCHILDEJECT)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFCHILDLIST ChildList,
    PWDF_CHILD_IDENTIFICATION_DESCRIPTION_HEADER IdentificationDescription
);

typedef NTSTATUS (__fastcall * PFN_WDFCOLLECTIONCREATE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    PWDF_OBJECT_ATTRIBUTES CollectionAttributes,
    WDFCOLLECTION* Collection
);

typedef ULONG (__fastcall * PFN_WDFCOLLECTIONGETCOUNT)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFCOLLECTION Collection
);

typedef NTSTATUS (__fastcall * PFN_WDFCOLLECTIONADD)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFCOLLECTION Collection,
    WDFOBJECT Object
);

typedef VOID (__fastcall * PFN_WDFCOLLECTIONREMOVE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFCOLLECTION Collection,
    WDFOBJECT Item
);

typedef VOID (__fastcall * PFN_WDFCOLLECTIONREMOVEITEM)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFCOLLECTION Collection,
    ULONG Index
);

typedef WDFOBJECT (__fastcall * PFN_WDFCOLLECTIONGETITEM)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFCOLLECTION Collection,
    ULONG Index
);

typedef WDFOBJECT (__fastcall * PFN_WDFCOLLECTIONGETFIRSTITEM)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFCOLLECTION Collection
);

typedef WDFOBJECT (__fastcall * PFN_WDFCOLLECTIONGETLASTITEM)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFCOLLECTION Collection
);

typedef NTSTATUS (__fastcall * PFN_WDFCOMMONBUFFERCREATE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDMAENABLER DmaEnabler,
    size_t Length,
    PWDF_OBJECT_ATTRIBUTES Attributes,
    WDFCOMMONBUFFER* CommonBuffer
);

typedef PVOID (__fastcall * PFN_WDFCOMMONBUFFERGETALIGNEDVIRTUALADDRESS)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFCOMMONBUFFER CommonBuffer
);

typedef PHYSICAL_ADDRESS (__fastcall * PFN_WDFCOMMONBUFFERGETALIGNEDLOGICALADDRESS)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFCOMMONBUFFER CommonBuffer
);

typedef size_t (__fastcall * PFN_WDFCOMMONBUFFERGETLENGTH)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFCOMMONBUFFER CommonBuffer
);

typedef PWDFDEVICE_INIT (__fastcall * PFN_WDFCONTROLDEVICEINITALLOCATE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDRIVER Driver,
    const UNICODE_STRING* SDDLString
);

typedef VOID (__fastcall * PFN_WDFCONTROLDEVICEINITSETSHUTDOWNNOTIFICATION)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    PWDFDEVICE_INIT DeviceInit,
    PFN_WDF_DEVICE_SHUTDOWN_NOTIFICATION Notification,
    UCHAR Flags
);

typedef VOID (__fastcall * PFN_WDFCONTROLFINISHINITIALIZING)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device
);

typedef VOID (__fastcall * PFN_WDFDEVICEGETDEVICESTATE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device,
    PWDF_DEVICE_STATE DeviceState
);

typedef VOID (__fastcall * PFN_WDFDEVICESETDEVICESTATE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device,
    PWDF_DEVICE_STATE DeviceState
);

typedef WDFDEVICE (__fastcall * PFN_WDFWDMDEVICEGETWDFDEVICEHANDLE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    PDEVICE_OBJECT DeviceObject
);

typedef PDEVICE_OBJECT (__fastcall * PFN_WDFDEVICEWDMGETDEVICEOBJECT)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device
);

typedef PDEVICE_OBJECT (__fastcall * PFN_WDFDEVICEWDMGETATTACHEDDEVICE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device
);

typedef PDEVICE_OBJECT (__fastcall * PFN_WDFDEVICEWDMGETPHYSICALDEVICE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device
);

typedef NTSTATUS (__fastcall * PFN_WDFDEVICEWDMDISPATCHPREPROCESSEDIRP)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device,
    PIRP Irp
);

typedef NTSTATUS (__fastcall * PFN_WDFDEVICEADDDEPENDENTUSAGEDEVICEOBJECT)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device,
    PDEVICE_OBJECT DependentDevice
);

typedef NTSTATUS (__fastcall * PFN_WDFDEVICEADDREMOVALRELATIONSPHYSICALDEVICE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device,
    PDEVICE_OBJECT PhysicalDevice
);

typedef VOID (__fastcall * PFN_WDFDEVICEREMOVEREMOVALRELATIONSPHYSICALDEVICE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device,
    PDEVICE_OBJECT PhysicalDevice
);

typedef VOID (__fastcall * PFN_WDFDEVICECLEARREMOVALRELATIONSDEVICES)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device
);

typedef WDFDRIVER (__fastcall * PFN_WDFDEVICEGETDRIVER)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device
);

typedef NTSTATUS (__fastcall * PFN_WDFDEVICERETRIEVEDEVICENAME)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device,
    WDFSTRING String
);

typedef NTSTATUS (__fastcall * PFN_WDFDEVICEASSIGNMOFRESOURCENAME)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device,
    PCUNICODE_STRING MofResourceName
);

typedef WDFIOTARGET (__fastcall * PFN_WDFDEVICEGETIOTARGET)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device
);

typedef WDF_DEVICE_PNP_STATE (__fastcall * PFN_WDFDEVICEGETDEVICEPNPSTATE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device
);

typedef WDF_DEVICE_POWER_STATE (__fastcall * PFN_WDFDEVICEGETDEVICEPOWERSTATE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device
);

typedef WDF_DEVICE_POWER_POLICY_STATE (__fastcall * PFN_WDFDEVICEGETDEVICEPOWERPOLICYSTATE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device
);

typedef NTSTATUS (__fastcall * PFN_WDFDEVICEASSIGNS0IDLESETTINGS)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device,
    PWDF_DEVICE_POWER_POLICY_IDLE_SETTINGS Settings
);

typedef NTSTATUS (__fastcall * PFN_WDFDEVICEASSIGNSXWAKESETTINGS)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device,
    PWDF_DEVICE_POWER_POLICY_WAKE_SETTINGS Settings
);

typedef NTSTATUS (__fastcall * PFN_WDFDEVICEOPENREGISTRYKEY)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device,
    ULONG DeviceInstanceKeyType,
    ACCESS_MASK DesiredAccess,
    PWDF_OBJECT_ATTRIBUTES KeyAttributes,
    WDFKEY* Key
);

typedef VOID (__fastcall * PFN_WDFDEVICESETSPECIALFILESUPPORT)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device,
    WDF_SPECIAL_FILE_TYPE FileType,
    BOOLEAN FileTypeIsSupported
);

typedef VOID (__fastcall * PFN_WDFDEVICESETCHARACTERISTICS)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device,
    ULONG DeviceCharacteristics
);

typedef ULONG (__fastcall * PFN_WDFDEVICEGETCHARACTERISTICS)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device
);

typedef ULONG (__fastcall * PFN_WDFDEVICEGETALIGNMENTREQUIREMENT)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device
);

typedef VOID (__fastcall * PFN_WDFDEVICESETALIGNMENTREQUIREMENT)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device,
    ULONG AlignmentRequirement
);

typedef VOID (__fastcall * PFN_WDFDEVICEINITFREE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    PWDFDEVICE_INIT DeviceInit
);

typedef VOID (__fastcall * PFN_WDFDEVICEINITSETPNPPOWEREVENTCALLBACKS)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    PWDFDEVICE_INIT DeviceInit,
    PWDF_PNPPOWER_EVENT_CALLBACKS PnpPowerEventCallbacks
);

typedef VOID (__fastcall * PFN_WDFDEVICEINITSETPOWERPOLICYEVENTCALLBACKS)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    PWDFDEVICE_INIT DeviceInit,
    PWDF_POWER_POLICY_EVENT_CALLBACKS PowerPolicyEventCallbacks
);

typedef VOID (__fastcall * PFN_WDFDEVICEINITSETPOWERPOLICYOWNERSHIP)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    PWDFDEVICE_INIT DeviceInit,
    BOOLEAN IsPowerPolicyOwner
);

typedef NTSTATUS (__fastcall * PFN_WDFDEVICEINITREGISTERPNPSTATECHANGECALLBACK)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    PWDFDEVICE_INIT DeviceInit,
    WDF_DEVICE_PNP_STATE PnpState,
    PFN_WDF_DEVICE_PNP_STATE_CHANGE_NOTIFICATION EvtDevicePnpStateChange,
    ULONG CallbackTypes
);

typedef NTSTATUS (__fastcall * PFN_WDFDEVICEINITREGISTERPOWERSTATECHANGECALLBACK)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    PWDFDEVICE_INIT DeviceInit,
    WDF_DEVICE_POWER_STATE PowerState,
    PFN_WDF_DEVICE_POWER_STATE_CHANGE_NOTIFICATION EvtDevicePowerStateChange,
    ULONG CallbackTypes
);

typedef NTSTATUS (__fastcall * PFN_WDFDEVICEINITREGISTERPOWERPOLICYSTATECHANGECALLBACK)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    PWDFDEVICE_INIT DeviceInit,
    WDF_DEVICE_POWER_POLICY_STATE PowerPolicyState,
    PFN_WDF_DEVICE_POWER_POLICY_STATE_CHANGE_NOTIFICATION EvtDevicePowerPolicyStateChange,
    ULONG CallbackTypes
);

typedef VOID (__fastcall * PFN_WDFDEVICEINITSETIOTYPE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    PWDFDEVICE_INIT DeviceInit,
    WDF_DEVICE_IO_TYPE IoType
);

typedef VOID (__fastcall * PFN_WDFDEVICEINITSETEXCLUSIVE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    PWDFDEVICE_INIT DeviceInit,
    BOOLEAN IsExclusive
);

typedef VOID (__fastcall * PFN_WDFDEVICEINITSETPOWERNOTPAGEABLE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    PWDFDEVICE_INIT DeviceInit
);

typedef VOID (__fastcall * PFN_WDFDEVICEINITSETPOWERPAGEABLE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    PWDFDEVICE_INIT DeviceInit
);

typedef VOID (__fastcall * PFN_WDFDEVICEINITSETPOWERINRUSH)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    PWDFDEVICE_INIT DeviceInit
);

typedef VOID (__fastcall * PFN_WDFDEVICEINITSETDEVICETYPE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    PWDFDEVICE_INIT DeviceInit,
    DEVICE_TYPE DeviceType
);

typedef NTSTATUS (__fastcall * PFN_WDFDEVICEINITASSIGNNAME)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    PWDFDEVICE_INIT DeviceInit,
    PCUNICODE_STRING DeviceName
);

typedef NTSTATUS (__fastcall * PFN_WDFDEVICEINITASSIGNSDDLSTRING)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    PWDFDEVICE_INIT DeviceInit,
    PCUNICODE_STRING SDDLString
);

typedef VOID (__fastcall * PFN_WDFDEVICEINITSETDEVICECLASS)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    PWDFDEVICE_INIT DeviceInit,
    const GUID* DeviceClassGuid
);

typedef VOID (__fastcall * PFN_WDFDEVICEINITSETCHARACTERISTICS)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    PWDFDEVICE_INIT DeviceInit,
    ULONG DeviceCharacteristics,
    BOOLEAN OrInValues
);

typedef VOID (__fastcall * PFN_WDFDEVICEINITSETFILEOBJECTCONFIG)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    PWDFDEVICE_INIT DeviceInit,
    PWDF_FILEOBJECT_CONFIG FileObjectConfig,
    PWDF_OBJECT_ATTRIBUTES FileObjectAttributes
);

typedef VOID (__fastcall * PFN_WDFDEVICEINITSETREQUESTATTRIBUTES)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    PWDFDEVICE_INIT DeviceInit,
    PWDF_OBJECT_ATTRIBUTES RequestAttributes
);

typedef NTSTATUS (__fastcall * PFN_WDFDEVICEINITASSIGNWDMIRPPREPROCESSCALLBACK)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    PWDFDEVICE_INIT DeviceInit,
    PFN_WDFDEVICE_WDM_IRP_PREPROCESS EvtDeviceWdmIrpPreprocess,
    UCHAR MajorFunction,
    PUCHAR MinorFunctions,
    ULONG NumMinorFunctions
);

typedef VOID (__fastcall * PFN_WDFDEVICEINITSETIOINCALLERCONTEXTCALLBACK)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    PWDFDEVICE_INIT DeviceInit,
    PFN_WDF_IOCALLER_CONTEXT EvtIoInCallerContext
);

typedef NTSTATUS (__fastcall * PFN_WDFDEVICECREATE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    PWDFDEVICE_INIT* DeviceInit,
    PWDF_OBJECT_ATTRIBUTES DeviceAttributes,
    WDFDEVICE* Device
);

typedef VOID (__fastcall * PFN_WDFDEVICESETSTATICSTOPREMOVE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device,
    BOOLEAN Stoppable
);

typedef NTSTATUS (__fastcall * PFN_WDFDEVICECREATEDEVICEINTERFACE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device,
    const GUID* InterfaceClassGUID,
    PCUNICODE_STRING ReferenceString
);

typedef VOID ( __fastcall * PFN_WDFDEVICESETDEVICEINTERFACESTATE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device,
    const GUID* InterfaceClassGUID,
    PCUNICODE_STRING ReferenceString,
    BOOLEAN IsInterfaceEnabled
);

typedef NTSTATUS (__fastcall * PFN_WDFDEVICERETRIEVEDEVICEINTERFACESTRING)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device,
    const GUID* InterfaceClassGUID,
    PCUNICODE_STRING ReferenceString,
    WDFSTRING String
);

typedef NTSTATUS (__fastcall * PFN_WDFDEVICECREATESYMBOLICLINK)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device,
    PCUNICODE_STRING SymbolicLinkName
);

typedef NTSTATUS (__fastcall * PFN_WDFDEVICEQUERYPROPERTY)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device,
    DEVICE_REGISTRY_PROPERTY DeviceProperty,
    ULONG BufferLength,
    PVOID PropertyBuffer,
    PULONG ResultLength
);

typedef NTSTATUS (__fastcall * PFN_WDFDEVICEALLOCANDQUERYPROPERTY)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device,
    DEVICE_REGISTRY_PROPERTY DeviceProperty,
    POOL_TYPE PoolType,
    PWDF_OBJECT_ATTRIBUTES PropertyMemoryAttributes,
    WDFMEMORY* PropertyMemory
);

typedef VOID (__fastcall * PFN_WDFDEVICESETPNPCAPABILITIES)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device,
    PWDF_DEVICE_PNP_CAPABILITIES PnpCapabilities
);

typedef VOID (__fastcall * PFN_WDFDEVICESETPOWERCAPABILITIES)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device,
    PWDF_DEVICE_POWER_CAPABILITIES PowerCapabilities
);

typedef VOID (__fastcall * PFN_WDFDEVICESETBUSINFORMATIONFORCHILDREN)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device,
    PPNP_BUS_INFORMATION BusInformation
);

typedef NTSTATUS (__fastcall * PFN_WDFDEVICEINDICATEWAKESTATUS)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device,
    NTSTATUS WaitWakeStatus
);

typedef VOID (__fastcall * PFN_WDFDEVICESETFAILED)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device,
    WDF_DEVICE_FAILED_ACTION FailedAction
);

typedef NTSTATUS (__fastcall * PFN_WDFDEVICESTOPIDLENOTRACK)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device,
    BOOLEAN WaitForD0
);

typedef VOID (__fastcall * PFN_WDFDEVICERESUMEIDLENOTRACK)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device
);

typedef WDFFILEOBJECT (__fastcall * PFN_WDFDEVICEGETFILEOBJECT)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device,
    PFILE_OBJECT FileObject
);

typedef NTSTATUS (__fastcall * PFN_WDFDEVICEENQUEUEREQUEST)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device,
    WDFREQUEST Request
);


typedef WDFQUEUE (__fastcall * PFN_WDFDEVICEGETDEFAULTQUEUE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device
);


typedef NTSTATUS (__fastcall * PFN_WDFDEVICECONFIGUREREQUESTDISPATCHING)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device,
    WDFQUEUE Queue,
    WDF_REQUEST_TYPE RequestType
);

typedef NTSTATUS (__fastcall * PFN_WDFDMAENABLERCREATE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device,
    PWDF_DMA_ENABLER_CONFIG Config,
    PWDF_OBJECT_ATTRIBUTES Attributes,
    WDFDMAENABLER* DmaEnablerHandle
);

typedef size_t (__fastcall * PFN_WDFDMAENABLERGETMAXIMUMLENGTH)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDMAENABLER DmaEnabler
);

typedef size_t (__fastcall * PFN_WDFDMAENABLERGETMAXIMUMSCATTERGATHERELEMENTS)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDMAENABLER DmaEnabler
);

typedef VOID (__fastcall * PFN_WDFDMAENABLERSETMAXIMUMSCATTERGATHERELEMENTS)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDMAENABLER DmaEnabler,
    size_t MaximumFragments
);

typedef NTSTATUS (__fastcall * PFN_WDFDMATRANSACTIONCREATE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDMAENABLER DmaEnabler,
    PWDF_OBJECT_ATTRIBUTES Attributes,
    WDFDMATRANSACTION* DmaTransaction
);

typedef NTSTATUS (__fastcall * PFN_WDFDMATRANSACTIONINITIALIZE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDMATRANSACTION DmaTransaction,
    PFN_WDF_PROGRAM_DMA EvtProgramDmaFunction,
    WDF_DMA_DIRECTION DmaDirection,
    PMDL Mdl,
    PVOID VirtualAddress,
    size_t Length
);

typedef NTSTATUS (__fastcall * PFN_WDFDMATRANSACTIONINITIALIZEUSINGREQUEST)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDMATRANSACTION DmaTransaction,
    WDFREQUEST Request,
    PFN_WDF_PROGRAM_DMA EvtProgramDmaFunction,
    WDF_DMA_DIRECTION DmaDirection
);

typedef NTSTATUS (__fastcall * PFN_WDFDMATRANSACTIONEXECUTE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDMATRANSACTION DmaTransaction,
    WDFCONTEXT Context
);

typedef NTSTATUS (__fastcall * PFN_WDFDMATRANSACTIONRELEASE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDMATRANSACTION DmaTransaction
);

typedef BOOLEAN (__fastcall * PFN_WDFDMATRANSACTIONDMACOMPLETED)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDMATRANSACTION DmaTransaction,
    NTSTATUS* Status
);

typedef BOOLEAN (__fastcall * PFN_WDFDMATRANSACTIONDMACOMPLETEDWITHLENGTH)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDMATRANSACTION DmaTransaction,
    size_t TransferredLength,
    NTSTATUS* Status
);

typedef BOOLEAN (__fastcall * PFN_WDFDMATRANSACTIONDMACOMPLETEDFINAL)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDMATRANSACTION DmaTransaction,
    size_t FinalTransferredLength,
    NTSTATUS* Status
);

typedef size_t (__fastcall * PFN_WDFDMATRANSACTIONGETBYTESTRANSFERRED)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDMATRANSACTION DmaTransaction
);

typedef VOID (__fastcall * PFN_WDFDMATRANSACTIONSETMAXIMUMLENGTH)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDMATRANSACTION DmaTransaction,
    size_t MaximumLength
);

typedef WDFREQUEST (__fastcall * PFN_WDFDMATRANSACTIONGETREQUEST)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDMATRANSACTION DmaTransaction
);

typedef size_t (__fastcall * PFN_WDFDMATRANSACTIONGETCURRENTDMATRANSFERLENGTH)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDMATRANSACTION DmaTransaction
);

typedef WDFDEVICE (__fastcall * PFN_WDFDMATRANSACTIONGETDEVICE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDMATRANSACTION DmaTransaction
);

typedef NTSTATUS (__fastcall * PFN_WDFDPCCREATE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    PWDF_DPC_CONFIG Config,
    PWDF_OBJECT_ATTRIBUTES Attributes,
    WDFDPC* Dpc
);

typedef BOOLEAN (__fastcall * PFN_WDFDPCENQUEUE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDPC Dpc
);

typedef BOOLEAN (__fastcall * PFN_WDFDPCCANCEL)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDPC Dpc,
    BOOLEAN Wait
);

typedef WDFOBJECT (__fastcall * PFN_WDFDPCGETPARENTOBJECT)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDPC Dpc
);

typedef PKDPC (__fastcall * PFN_WDFDPCWDMGETDPC)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDPC Dpc
);

typedef NTSTATUS (__fastcall * PFN_WDFDRIVERCREATE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    PDRIVER_OBJECT DriverObject,
    PCUNICODE_STRING RegistryPath,
    PWDF_OBJECT_ATTRIBUTES DriverAttributes,
    PWDF_DRIVER_CONFIG DriverConfig,
    WDFDRIVER* Driver
);

typedef PWSTR (__fastcall * PFN_WDFDRIVERGETREGISTRYPATH)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDRIVER Driver
);

typedef PDRIVER_OBJECT (__fastcall * PFN_WDFDRIVERWDMGETDRIVEROBJECT)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDRIVER Driver
);

typedef NTSTATUS (__fastcall * PFN_WDFDRIVEROPENPARAMETERSREGISTRYKEY)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDRIVER Driver,
    ACCESS_MASK DesiredAccess,
    PWDF_OBJECT_ATTRIBUTES KeyAttributes,
    WDFKEY* Key
);

typedef WDFDRIVER (__fastcall * PFN_WDFWDMDRIVERGETWDFDRIVERHANDLE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    PDRIVER_OBJECT DriverObject
);

typedef NTSTATUS (__fastcall * PFN_WDFDRIVERREGISTERTRACEINFO)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    PDRIVER_OBJECT DriverObject,
    PFN_WDF_TRACE_CALLBACK EvtTraceCallback,
    PVOID ControlBlock
);

typedef NTSTATUS (__fastcall * PFN_WDFDRIVERRETRIEVEVERSIONSTRING)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDRIVER Driver,
    WDFSTRING String
);

typedef BOOLEAN (__fastcall * PFN_WDFDRIVERISVERSIONAVAILABLE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDRIVER Driver,
    PWDF_DRIVER_VERSION_AVAILABLE_PARAMS VersionAvailableParams
);

typedef PDEVICE_OBJECT (__fastcall * PFN_WDFFDOINITWDMGETPHYSICALDEVICE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    PWDFDEVICE_INIT DeviceInit
);

typedef NTSTATUS (__fastcall * PFN_WDFFDOINITOPENREGISTRYKEY)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    PWDFDEVICE_INIT DeviceInit,
    ULONG DeviceInstanceKeyType,
    ACCESS_MASK DesiredAccess,
    PWDF_OBJECT_ATTRIBUTES KeyAttributes,
    WDFKEY* Key
);

typedef NTSTATUS (__fastcall * PFN_WDFFDOINITQUERYPROPERTY)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    PWDFDEVICE_INIT DeviceInit,
    DEVICE_REGISTRY_PROPERTY DeviceProperty,
    ULONG BufferLength,
    PVOID PropertyBuffer,
    PULONG ResultLength
);

typedef NTSTATUS (__fastcall * PFN_WDFFDOINITALLOCANDQUERYPROPERTY)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    PWDFDEVICE_INIT DeviceInit,
    DEVICE_REGISTRY_PROPERTY DeviceProperty,
    POOL_TYPE PoolType,
    PWDF_OBJECT_ATTRIBUTES PropertyMemoryAttributes,
    WDFMEMORY* PropertyMemory
);

typedef VOID (__fastcall * PFN_WDFFDOINITSETEVENTCALLBACKS)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    PWDFDEVICE_INIT DeviceInit,
    PWDF_FDO_EVENT_CALLBACKS FdoEventCallbacks
);

typedef VOID (__fastcall * PFN_WDFFDOINITSETFILTER)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    PWDFDEVICE_INIT DeviceInit
);

typedef VOID (__fastcall * PFN_WDFFDOINITSETDEFAULTCHILDLISTCONFIG)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    PWDFDEVICE_INIT DeviceInit,
    PWDF_CHILD_LIST_CONFIG Config,
    PWDF_OBJECT_ATTRIBUTES DefaultChildListAttributes
);

typedef NTSTATUS (__fastcall * PFN_WDFFDOQUERYFORINTERFACE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Fdo,
    LPCGUID InterfaceType,
    PINTERFACE Interface,
    USHORT Size,
    USHORT Version,
    PVOID InterfaceSpecificData
);

typedef WDFCHILDLIST (__fastcall * PFN_WDFFDOGETDEFAULTCHILDLIST)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Fdo
);

typedef NTSTATUS (__fastcall * PFN_WDFFDOADDSTATICCHILD)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Fdo,
    WDFDEVICE Child
);

typedef VOID (__fastcall * PFN_WDFFDOLOCKSTATICCHILDLISTFORITERATION)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Fdo
);

typedef WDFDEVICE (__fastcall * PFN_WDFFDORETRIEVENEXTSTATICCHILD)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Fdo,
    WDFDEVICE PreviousChild,
    ULONG Flags
);

typedef VOID (__fastcall * PFN_WDFFDOUNLOCKSTATICCHILDLISTFROMITERATION)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Fdo
);

typedef PUNICODE_STRING (__fastcall * PFN_WDFFILEOBJECTGETFILENAME)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFFILEOBJECT FileObject
);

typedef ULONG (__fastcall * PFN_WDFFILEOBJECTGETFLAGS)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFFILEOBJECT FileObject
);

typedef WDFDEVICE (__fastcall * PFN_WDFFILEOBJECTGETDEVICE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFFILEOBJECT FileObject
);

typedef PFILE_OBJECT (__fastcall * PFN_WDFFILEOBJECTWDMGETFILEOBJECT)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFFILEOBJECT FileObject
);

typedef NTSTATUS (__fastcall * PFN_WDFINTERRUPTCREATE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device,
    PWDF_INTERRUPT_CONFIG Configuration,
    PWDF_OBJECT_ATTRIBUTES Attributes,
    WDFINTERRUPT* Interrupt
);


typedef BOOLEAN (__fastcall * PFN_WDFINTERRUPTQUEUEDPCFORISR)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFINTERRUPT Interrupt
);

typedef BOOLEAN (__fastcall * PFN_WDFINTERRUPTSYNCHRONIZE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFINTERRUPT Interrupt,
    PFN_WDF_INTERRUPT_SYNCHRONIZE Callback,
    WDFCONTEXT Context
);

typedef VOID (__fastcall * PFN_WDFINTERRUPTACQUIRELOCK)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFINTERRUPT Interrupt
);

typedef VOID (__fastcall * PFN_WDFINTERRUPTRELEASELOCK)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFINTERRUPT Interrupt
);

typedef VOID (__fastcall * PFN_WDFINTERRUPTENABLE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFINTERRUPT Interrupt
);

typedef VOID (__fastcall * PFN_WDFINTERRUPTDISABLE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFINTERRUPT Interrupt
);

typedef PKINTERRUPT (__fastcall * PFN_WDFINTERRUPTWDMGETINTERRUPT)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFINTERRUPT Interrupt
);

typedef VOID (__fastcall * PFN_WDFINTERRUPTGETINFO)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFINTERRUPT Interrupt,
    PWDF_INTERRUPT_INFO Info
);

typedef VOID (__fastcall * PFN_WDFINTERRUPTSETPOLICY)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFINTERRUPT Interrupt,
    WDF_INTERRUPT_POLICY Policy,
    WDF_INTERRUPT_PRIORITY Priority,
    KAFFINITY TargetProcessorSet
);

typedef WDFDEVICE (__fastcall * PFN_WDFINTERRUPTGETDEVICE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFINTERRUPT Interrupt
);

typedef NTSTATUS (__fastcall * PFN_WDFIOQUEUECREATE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device,
    PWDF_IO_QUEUE_CONFIG Config,
    PWDF_OBJECT_ATTRIBUTES QueueAttributes,
    WDFQUEUE* Queue
);

typedef WDF_IO_QUEUE_STATE (__fastcall * PFN_WDFIOQUEUEGETSTATE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFQUEUE Queue,
    PULONG QueueRequests,
    PULONG DriverRequests
);

typedef VOID (__fastcall * PFN_WDFIOQUEUESTART)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFQUEUE Queue
);

typedef VOID (__fastcall * PFN_WDFIOQUEUESTOP)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFQUEUE Queue,
    PFN_WDF_IO_QUEUE_STATE StopComplete,
    WDFCONTEXT Context
);

typedef VOID (__fastcall * PFN_WDFIOQUEUESTOPSYNCHRONOUSLY)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFQUEUE Queue
);

typedef WDFDEVICE (__fastcall * PFN_WDFIOQUEUEGETDEVICE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFQUEUE Queue
);

typedef NTSTATUS (__fastcall * PFN_WDFIOQUEUERETRIEVENEXTREQUEST)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFQUEUE Queue,
    WDFREQUEST* OutRequest
);

typedef NTSTATUS (__fastcall * PFN_WDFIOQUEUERETRIEVEREQUESTBYFILEOBJECT)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFQUEUE Queue,
    WDFFILEOBJECT FileObject,
    WDFREQUEST* OutRequest
);

typedef NTSTATUS (__fastcall * PFN_WDFIOQUEUEFINDREQUEST)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFQUEUE Queue,
    WDFREQUEST FoundRequest,
    WDFFILEOBJECT FileObject,
    PWDF_REQUEST_PARAMETERS Parameters,
    WDFREQUEST* OutRequest
);

typedef NTSTATUS (__fastcall * PFN_WDFIOQUEUERETRIEVEFOUNDREQUEST)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFQUEUE Queue,
    WDFREQUEST FoundRequest,
    WDFREQUEST* OutRequest
);

typedef VOID (__fastcall * PFN_WDFIOQUEUEDRAINSYNCHRONOUSLY)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFQUEUE Queue
);

typedef VOID (__fastcall * PFN_WDFIOQUEUEDRAIN)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFQUEUE Queue,
    PFN_WDF_IO_QUEUE_STATE DrainComplete,
    WDFCONTEXT Context
);

typedef VOID (__fastcall * PFN_WDFIOQUEUEPURGESYNCHRONOUSLY)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFQUEUE Queue
);


typedef VOID (__fastcall * PFN_WDFIOQUEUEPURGE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFQUEUE Queue,
    PFN_WDF_IO_QUEUE_STATE PurgeComplete,
    WDFCONTEXT Context
);

typedef NTSTATUS (__fastcall * PFN_WDFIOQUEUEREADYNOTIFY)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFQUEUE Queue,
    PFN_WDF_IO_QUEUE_STATE QueueReady,
    WDFCONTEXT Context
);

typedef NTSTATUS (__fastcall * PFN_WDFIOTARGETCREATE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device,
    PWDF_OBJECT_ATTRIBUTES IoTargetAttributes,
    WDFIOTARGET* IoTarget
);

typedef NTSTATUS (__fastcall * PFN_WDFIOTARGETOPEN)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFIOTARGET IoTarget,
    PWDF_IO_TARGET_OPEN_PARAMS OpenParams
);

typedef VOID (__fastcall * PFN_WDFIOTARGETCLOSEFORQUERYREMOVE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFIOTARGET IoTarget
);

typedef VOID (__fastcall * PFN_WDFIOTARGETCLOSE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFIOTARGET IoTarget
);

typedef NTSTATUS (__fastcall * PFN_WDFIOTARGETSTART)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFIOTARGET IoTarget
);


typedef VOID (__fastcall * PFN_WDFIOTARGETSTOP)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFIOTARGET IoTarget,
    WDF_IO_TARGET_SENT_IO_ACTION Action
);

typedef WDF_IO_TARGET_STATE (__fastcall * PFN_WDFIOTARGETGETSTATE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFIOTARGET IoTarget
);

typedef WDFDEVICE (__fastcall * PFN_WDFIOTARGETGETDEVICE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFIOTARGET IoTarget
);

typedef NTSTATUS (__fastcall * PFN_WDFIOTARGETQUERYTARGETPROPERTY)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFIOTARGET IoTarget,
    DEVICE_REGISTRY_PROPERTY DeviceProperty,
    ULONG BufferLength,

    PVOID PropertyBuffer,
    PULONG ResultLength
);

typedef NTSTATUS (__fastcall * PFN_WDFIOTARGETALLOCANDQUERYTARGETPROPERTY)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFIOTARGET IoTarget,
    DEVICE_REGISTRY_PROPERTY DeviceProperty,
    POOL_TYPE PoolType,
    PWDF_OBJECT_ATTRIBUTES PropertyMemoryAttributes,
    WDFMEMORY* PropertyMemory
);

typedef NTSTATUS (__fastcall * PFN_WDFIOTARGETQUERYFORINTERFACE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFIOTARGET IoTarget,
    LPCGUID InterfaceType,
    PINTERFACE Interface,
    USHORT Size,
    USHORT Version,
    PVOID InterfaceSpecificData
);

typedef PDEVICE_OBJECT (__fastcall * PFN_WDFIOTARGETWDMGETTARGETDEVICEOBJECT)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFIOTARGET IoTarget
);

typedef PDEVICE_OBJECT (__fastcall * PFN_WDFIOTARGETWDMGETTARGETPHYSICALDEVICE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFIOTARGET IoTarget
);

typedef PFILE_OBJECT (__fastcall * PFN_WDFIOTARGETWDMGETTARGETFILEOBJECT)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFIOTARGET IoTarget
);

typedef HANDLE (__fastcall * PFN_WDFIOTARGETWDMGETTARGETFILEHANDLE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFIOTARGET IoTarget
);

typedef NTSTATUS (__fastcall * PFN_WDFIOTARGETSENDREADSYNCHRONOUSLY)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFIOTARGET IoTarget,
    WDFREQUEST Request,
    PWDF_MEMORY_DESCRIPTOR OutputBuffer,
    PLONGLONG DeviceOffset,
    PWDF_REQUEST_SEND_OPTIONS RequestOptions,
    PULONG_PTR BytesRead
);

typedef NTSTATUS (__fastcall * PFN_WDFIOTARGETFORMATREQUESTFORREAD)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFIOTARGET IoTarget,
    WDFREQUEST Request,
    WDFMEMORY OutputBuffer,
    PWDFMEMORY_OFFSET OutputBufferOffset,
    PLONGLONG DeviceOffset
);

typedef NTSTATUS (__fastcall * PFN_WDFIOTARGETSENDWRITESYNCHRONOUSLY)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFIOTARGET IoTarget,
    WDFREQUEST Request,
    PWDF_MEMORY_DESCRIPTOR InputBuffer,
    PLONGLONG DeviceOffset,
    PWDF_REQUEST_SEND_OPTIONS RequestOptions,
    PULONG_PTR BytesWritten
);

typedef NTSTATUS (__fastcall * PFN_WDFIOTARGETFORMATREQUESTFORWRITE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFIOTARGET IoTarget,
    WDFREQUEST Request,
    WDFMEMORY InputBuffer,
    PWDFMEMORY_OFFSET InputBufferOffset,
    PLONGLONG DeviceOffset
);

typedef NTSTATUS (__fastcall * PFN_WDFIOTARGETSENDIOCTLSYNCHRONOUSLY)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFIOTARGET IoTarget,
    WDFREQUEST Request,
    ULONG IoctlCode,
    PWDF_MEMORY_DESCRIPTOR InputBuffer,
    PWDF_MEMORY_DESCRIPTOR OutputBuffer,
    PWDF_REQUEST_SEND_OPTIONS RequestOptions,
    PULONG_PTR BytesReturned
);

typedef NTSTATUS (__fastcall * PFN_WDFIOTARGETFORMATREQUESTFORIOCTL)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFIOTARGET IoTarget,
    WDFREQUEST Request,
    ULONG IoctlCode,
    WDFMEMORY InputBuffer,
    PWDFMEMORY_OFFSET InputBufferOffset,
    WDFMEMORY OutputBuffer,
    PWDFMEMORY_OFFSET OutputBufferOffset
);

typedef NTSTATUS (__fastcall * PFN_WDFIOTARGETSENDINTERNALIOCTLSYNCHRONOUSLY)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFIOTARGET IoTarget,
    WDFREQUEST Request,
    ULONG IoctlCode,
    PWDF_MEMORY_DESCRIPTOR InputBuffer,
    PWDF_MEMORY_DESCRIPTOR OutputBuffer,
    PWDF_REQUEST_SEND_OPTIONS RequestOptions,
    PULONG_PTR BytesReturned
);

typedef NTSTATUS (__fastcall * PFN_WDFIOTARGETFORMATREQUESTFORINTERNALIOCTL)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFIOTARGET IoTarget,
    WDFREQUEST Request,
    ULONG IoctlCode,
    WDFMEMORY InputBuffer,
    PWDFMEMORY_OFFSET InputBufferOffset,
    WDFMEMORY OutputBuffer,
    PWDFMEMORY_OFFSET OutputBufferOffset
);

typedef NTSTATUS (__fastcall * PFN_WDFIOTARGETSENDINTERNALIOCTLOTHERSSYNCHRONOUSLY)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFIOTARGET IoTarget,
    WDFREQUEST Request,
    ULONG IoctlCode,
    PWDF_MEMORY_DESCRIPTOR OtherArg1,
    PWDF_MEMORY_DESCRIPTOR OtherArg2,
    PWDF_MEMORY_DESCRIPTOR OtherArg4,
    PWDF_REQUEST_SEND_OPTIONS RequestOptions,
    PULONG_PTR BytesReturned
);

typedef NTSTATUS (__fastcall * PFN_WDFIOTARGETFORMATREQUESTFORINTERNALIOCTLOTHERS)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFIOTARGET IoTarget,
    WDFREQUEST Request,
    ULONG IoctlCode,
    WDFMEMORY OtherArg1,
    PWDFMEMORY_OFFSET OtherArg1Offset,
    WDFMEMORY OtherArg2,
    PWDFMEMORY_OFFSET OtherArg2Offset,
    WDFMEMORY OtherArg4,
    PWDFMEMORY_OFFSET OtherArg4Offset
);

typedef NTSTATUS (__fastcall * PFN_WDFMEMORYCREATE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    PWDF_OBJECT_ATTRIBUTES Attributes,
    POOL_TYPE PoolType,
    ULONG PoolTag,
    size_t BufferSize,
    WDFMEMORY* Memory,
    PVOID* Buffer
);

typedef NTSTATUS (__fastcall * PFN_WDFMEMORYCREATEPREALLOCATED)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    PWDF_OBJECT_ATTRIBUTES Attributes,
    PVOID Buffer,
    size_t BufferSize,
    WDFMEMORY* Memory
);

typedef PVOID (__fastcall * PFN_WDFMEMORYGETBUFFER)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFMEMORY Memory,
    size_t* BufferSize
);

typedef NTSTATUS (__fastcall * PFN_WDFMEMORYASSIGNBUFFER)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFMEMORY Memory,
    PVOID Buffer,
    size_t BufferSize
);

typedef NTSTATUS (__fastcall * PFN_WDFMEMORYCOPYTOBUFFER)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFMEMORY SourceMemory,
    size_t SourceOffset,
    PVOID Buffer,
    size_t NumBytesToCopyTo
);

typedef NTSTATUS (__fastcall * PFN_WDFMEMORYCOPYFROMBUFFER)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFMEMORY DestinationMemory,
    size_t DestinationOffset,
    PVOID Buffer,
    size_t NumBytesToCopyFrom
);

typedef NTSTATUS (__fastcall * PFN_WDFLOOKASIDELISTCREATE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    PWDF_OBJECT_ATTRIBUTES LookasideAttributes,
    size_t BufferSize,
    POOL_TYPE PoolType,
    PWDF_OBJECT_ATTRIBUTES MemoryAttributes,
    ULONG PoolTag,
    WDFLOOKASIDE* Lookaside
);

typedef NTSTATUS (__fastcall * PFN_WDFMEMORYCREATEFROMLOOKASIDE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFLOOKASIDE Lookaside,
    WDFMEMORY* Memory
);

typedef NTSTATUS (__fastcall * PFN_WDFDEVICEMINIPORTCREATE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDRIVER Driver,
    PWDF_OBJECT_ATTRIBUTES Attributes,
    PDEVICE_OBJECT DeviceObject,
    PDEVICE_OBJECT AttachedDeviceObject,
    PDEVICE_OBJECT Pdo,
    WDFDEVICE* Device
);

typedef VOID (__fastcall * PFN_WDFDRIVERMINIPORTUNLOAD)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDRIVER Driver
);

typedef PVOID (__fastcall * PFN_WDFOBJECTGETTYPEDCONTEXTWORKER)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFOBJECT Handle,
    PCWDF_OBJECT_CONTEXT_TYPE_INFO TypeInfo
);

typedef NTSTATUS (__fastcall * PFN_WDFOBJECTALLOCATECONTEXT)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFOBJECT Handle,
    PWDF_OBJECT_ATTRIBUTES ContextAttributes,
    PVOID* Context
);

typedef WDFOBJECT (__fastcall * PFN_WDFOBJECTCONTEXTGETOBJECT)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    PVOID ContextPointer
);

typedef VOID (__fastcall * PFN_WDFOBJECTREFERENCEACTUAL)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFOBJECT Handle,
    PVOID Tag,
    LONG Line,
    PCCH File
);

typedef VOID (__fastcall * PFN_WDFOBJECTDEREFERENCEACTUAL)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFOBJECT Handle,
    PVOID Tag,
    LONG Line,
    PCCH File
);

typedef NTSTATUS (__fastcall * PFN_WDFOBJECTCREATE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    PWDF_OBJECT_ATTRIBUTES Attributes,
    WDFOBJECT* Object
);

typedef VOID (__fastcall * PFN_WDFOBJECTDELETE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFOBJECT Object
);

typedef NTSTATUS (__fastcall * PFN_WDFOBJECTQUERY)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFOBJECT Object,
    const GUID* Guid,
    ULONG QueryBufferLength,
    PVOID QueryBuffer
);

typedef PWDFDEVICE_INIT (__fastcall * PFN_WDFPDOINITALLOCATE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE ParentDevice
);

typedef VOID (__fastcall * PFN_WDFPDOINITSETEVENTCALLBACKS)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    PWDFDEVICE_INIT DeviceInit,
    PWDF_PDO_EVENT_CALLBACKS DispatchTable
);

typedef NTSTATUS (__fastcall * PFN_WDFPDOINITASSIGNDEVICEID)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    PWDFDEVICE_INIT DeviceInit,
    PCUNICODE_STRING DeviceID
);

typedef NTSTATUS (__fastcall * PFN_WDFPDOINITASSIGNINSTANCEID)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    PWDFDEVICE_INIT DeviceInit,
    PCUNICODE_STRING InstanceID
);

typedef NTSTATUS (__fastcall * PFN_WDFPDOINITADDHARDWAREID)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    PWDFDEVICE_INIT DeviceInit,
    PCUNICODE_STRING HardwareID
);

typedef NTSTATUS (__fastcall * PFN_WDFPDOINITADDCOMPATIBLEID)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    PWDFDEVICE_INIT DeviceInit,
    PCUNICODE_STRING CompatibleID
);

typedef NTSTATUS (__fastcall * PFN_WDFPDOINITADDDEVICETEXT)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    PWDFDEVICE_INIT DeviceInit,
    PCUNICODE_STRING DeviceDescription,
    PCUNICODE_STRING DeviceLocation,
    LCID LocaleId
);

typedef VOID (__fastcall * PFN_WDFPDOINITSETDEFAULTLOCALE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    PWDFDEVICE_INIT DeviceInit,
    LCID LocaleId
);

typedef NTSTATUS (__fastcall * PFN_WDFPDOINITASSIGNRAWDEVICE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    PWDFDEVICE_INIT DeviceInit,
    const GUID* DeviceClassGuid
);

typedef NTSTATUS (__fastcall * PFN_WDFPDOMARKMISSING)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device
);

typedef VOID (__fastcall * PFN_WDFPDOREQUESTEJECT)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device
);

typedef WDFDEVICE (__fastcall * PFN_WDFPDOGETPARENT)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device
);

typedef NTSTATUS (__fastcall * PFN_WDFPDORETRIEVEIDENTIFICATIONDESCRIPTION)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device,
    PWDF_CHILD_IDENTIFICATION_DESCRIPTION_HEADER IdentificationDescription
);

typedef NTSTATUS (__fastcall * PFN_WDFPDORETRIEVEADDRESSDESCRIPTION)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device,
    PWDF_CHILD_ADDRESS_DESCRIPTION_HEADER AddressDescription
);

typedef NTSTATUS (__fastcall * PFN_WDFPDOUPDATEADDRESSDESCRIPTION)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device,
    PWDF_CHILD_ADDRESS_DESCRIPTION_HEADER AddressDescription
);

typedef NTSTATUS (__fastcall * PFN_WDFPDOADDEJECTIONRELATIONSPHYSICALDEVICE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device,
    PDEVICE_OBJECT PhysicalDevice
);

typedef VOID (__fastcall * PFN_WDFPDOREMOVEEJECTIONRELATIONSPHYSICALDEVICE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device,
    PDEVICE_OBJECT PhysicalDevice
);

typedef VOID (__fastcall * PFN_WDFPDOCLEAREJECTIONRELATIONSDEVICES)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device
);

typedef NTSTATUS (__fastcall * PFN_WDFDEVICEADDQUERYINTERFACE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device,
    PWDF_QUERY_INTERFACE_CONFIG InterfaceConfig
);

typedef NTSTATUS (__fastcall * PFN_WDFREGISTRYOPENKEY)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFKEY ParentKey,
    PCUNICODE_STRING KeyName,
    ACCESS_MASK DesiredAccess,
    PWDF_OBJECT_ATTRIBUTES KeyAttributes,
    WDFKEY* Key
);

typedef NTSTATUS (__fastcall * PFN_WDFREGISTRYCREATEKEY)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFKEY ParentKey,
    PCUNICODE_STRING KeyName,
    ACCESS_MASK DesiredAccess,
    ULONG CreateOptions,
    PULONG CreateDisposition,
    PWDF_OBJECT_ATTRIBUTES KeyAttributes,
    WDFKEY* Key
);

typedef VOID (__fastcall * PFN_WDFREGISTRYCLOSE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFKEY Key
);

typedef HANDLE (__fastcall * PFN_WDFREGISTRYWDMGETHANDLE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFKEY Key
);

typedef NTSTATUS (__fastcall * PFN_WDFREGISTRYREMOVEKEY)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFKEY Key
);

typedef NTSTATUS (__fastcall * PFN_WDFREGISTRYREMOVEVALUE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFKEY Key,
    PCUNICODE_STRING ValueName
);

typedef NTSTATUS (__fastcall * PFN_WDFREGISTRYQUERYVALUE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFKEY Key,
    PCUNICODE_STRING ValueName,
    ULONG ValueLength,
    PVOID Value,
    PULONG ValueLengthQueried,
    PULONG ValueType
);

typedef NTSTATUS (__fastcall * PFN_WDFREGISTRYQUERYMEMORY)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFKEY Key,
    PCUNICODE_STRING ValueName,
    POOL_TYPE PoolType,
    PWDF_OBJECT_ATTRIBUTES MemoryAttributes,
    WDFMEMORY* Memory,
    PULONG ValueType
);

typedef NTSTATUS (__fastcall * PFN_WDFREGISTRYQUERYMULTISTRING)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFKEY Key,
    PCUNICODE_STRING ValueName,
    PWDF_OBJECT_ATTRIBUTES StringsAttributes,
    WDFCOLLECTION Collection
);

typedef NTSTATUS (__fastcall * PFN_WDFREGISTRYQUERYUNICODESTRING)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFKEY Key,
    PCUNICODE_STRING ValueName,
    PUSHORT ValueByteLength,
    PUNICODE_STRING Value
);

typedef NTSTATUS (__fastcall * PFN_WDFREGISTRYQUERYSTRING)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFKEY Key,
    PCUNICODE_STRING ValueName,
    WDFSTRING String
);

typedef NTSTATUS (__fastcall * PFN_WDFREGISTRYQUERYULONG)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFKEY Key,
    PCUNICODE_STRING ValueName,
    PULONG Value
);

typedef NTSTATUS (__fastcall * PFN_WDFREGISTRYASSIGNVALUE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFKEY Key,
    PCUNICODE_STRING ValueName,
    ULONG ValueType,
    ULONG ValueLength,    
    PVOID Value
);

typedef NTSTATUS (__fastcall * PFN_WDFREGISTRYASSIGNMEMORY)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFKEY Key,
    PCUNICODE_STRING ValueName,
    ULONG ValueType,
    WDFMEMORY Memory,
    PWDFMEMORY_OFFSET MemoryOffsets
);

typedef NTSTATUS (__fastcall * PFN_WDFREGISTRYASSIGNMULTISTRING)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFKEY Key,
    PCUNICODE_STRING ValueName,
    WDFCOLLECTION StringsCollection
);

typedef NTSTATUS (__fastcall * PFN_WDFREGISTRYASSIGNUNICODESTRING)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFKEY Key,
    PCUNICODE_STRING ValueName,
    PCUNICODE_STRING Value
);

typedef NTSTATUS (__fastcall * PFN_WDFREGISTRYASSIGNSTRING)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFKEY Key,
    PCUNICODE_STRING ValueName,
    WDFSTRING String
);

typedef NTSTATUS (__fastcall * PFN_WDFREGISTRYASSIGNULONG)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFKEY Key,
    PCUNICODE_STRING ValueName,
    ULONG Value
);

typedef NTSTATUS (__fastcall * PFN_WDFREQUESTCREATE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    PWDF_OBJECT_ATTRIBUTES RequestAttributes,
    WDFIOTARGET IoTarget,
    WDFREQUEST* Request
);

typedef NTSTATUS (__fastcall * PFN_WDFREQUESTCREATEFROMIRP)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    PWDF_OBJECT_ATTRIBUTES RequestAttributes,
    PIRP Irp,
    BOOLEAN RequestFreesIrp,
    WDFREQUEST* Request
);

typedef NTSTATUS (__fastcall * PFN_WDFREQUESTREUSE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFREQUEST Request,
    PWDF_REQUEST_REUSE_PARAMS ReuseParams
);

typedef NTSTATUS (__fastcall * PFN_WDFREQUESTCHANGETARGET)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFREQUEST Request,
    WDFIOTARGET IoTarget
);

typedef VOID (__fastcall * PFN_WDFREQUESTFORMATREQUESTUSINGCURRENTTYPE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFREQUEST Request
);

typedef VOID (__fastcall * PFN_WDFREQUESTWDMFORMATUSINGSTACKLOCATION)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFREQUEST Request,
    PIO_STACK_LOCATION Stack
);

typedef BOOLEAN (__fastcall * PFN_WDFREQUESTSEND)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFREQUEST Request,
    WDFIOTARGET Target,
    PWDF_REQUEST_SEND_OPTIONS Options
);

typedef NTSTATUS (__fastcall * PFN_WDFREQUESTGETSTATUS)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFREQUEST Request
);

typedef VOID (__fastcall * PFN_WDFREQUESTMARKCANCELABLE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFREQUEST Request,
    PFN_WDF_REQUEST_CANCEL EvtRequestCancel
);

typedef NTSTATUS (__fastcall * PFN_WDFREQUESTUNMARKCANCELABLE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFREQUEST Request
);

typedef BOOLEAN (__fastcall * PFN_WDFREQUESTISCANCELED)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFREQUEST Request
);

typedef BOOLEAN (__fastcall * PFN_WDFREQUESTCANCELSENTREQUEST)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFREQUEST Request
);

typedef BOOLEAN (__fastcall * PFN_WDFREQUESTISFROM32BITPROCESS)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFREQUEST Request
);

typedef VOID (__fastcall * PFN_WDFREQUESTSETCOMPLETIONROUTINE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFREQUEST Request,
    PFN_WDF_REQUEST_COMPLETION_ROUTINE CompletionRoutine,
    WDFCONTEXT CompletionContext
);

typedef VOID (__fastcall * PFN_WDFREQUESTGETCOMPLETIONPARAMS)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFREQUEST Request,
    PWDF_REQUEST_COMPLETION_PARAMS Params
);

typedef NTSTATUS (__fastcall * PFN_WDFREQUESTALLOCATETIMER)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFREQUEST Request
);

typedef VOID (__fastcall * PFN_WDFREQUESTCOMPLETE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFREQUEST Request,
    NTSTATUS Status
);

typedef VOID (__fastcall * PFN_WDFREQUESTCOMPLETEWITHPRIORITYBOOST)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFREQUEST Request,
    NTSTATUS Status,
    CCHAR PriorityBoost
);

typedef VOID (__fastcall * PFN_WDFREQUESTCOMPLETEWITHINFORMATION)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFREQUEST Request,
    NTSTATUS Status,
    ULONG_PTR Information
);

typedef VOID (__fastcall * PFN_WDFREQUESTGETPARAMETERS)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFREQUEST Request,
    PWDF_REQUEST_PARAMETERS Parameters
);

typedef NTSTATUS (__fastcall * PFN_WDFREQUESTRETRIEVEINPUTMEMORY)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFREQUEST Request,
    WDFMEMORY* Memory
);

typedef NTSTATUS (__fastcall * PFN_WDFREQUESTRETRIEVEOUTPUTMEMORY)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFREQUEST Request,
    WDFMEMORY* Memory
);

typedef NTSTATUS (__fastcall * PFN_WDFREQUESTRETRIEVEINPUTBUFFER)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFREQUEST Request,
    size_t MinimumRequiredLength,
    PVOID* Buffer,
    size_t* Length
);

typedef NTSTATUS (__fastcall * PFN_WDFREQUESTRETRIEVEOUTPUTBUFFER)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFREQUEST Request,
    size_t MinimumRequiredSize,
    PVOID* Buffer,
    size_t* Length
);

typedef NTSTATUS (__fastcall * PFN_WDFREQUESTRETRIEVEINPUTWDMMDL)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFREQUEST Request,
    PMDL* Mdl
);

typedef NTSTATUS (__fastcall * PFN_WDFREQUESTRETRIEVEOUTPUTWDMMDL)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFREQUEST Request,
    PMDL* Mdl
);

typedef NTSTATUS (__fastcall * PFN_WDFREQUESTRETRIEVEUNSAFEUSERINPUTBUFFER)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFREQUEST Request,
    size_t MinimumRequiredLength,
    PVOID* InputBuffer,
    size_t* Length
);

typedef NTSTATUS (__fastcall * PFN_WDFREQUESTRETRIEVEUNSAFEUSEROUTPUTBUFFER)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFREQUEST Request,
    size_t MinimumRequiredLength,
    PVOID* OutputBuffer,
    size_t* Length
);

typedef VOID (__fastcall * PFN_WDFREQUESTSETINFORMATION)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFREQUEST Request,
    ULONG_PTR Information
);

typedef ULONG_PTR (__fastcall * PFN_WDFREQUESTGETINFORMATION)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFREQUEST Request
);

typedef WDFFILEOBJECT (__fastcall * PFN_WDFREQUESTGETFILEOBJECT)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFREQUEST Request
);

typedef NTSTATUS (__fastcall * PFN_WDFREQUESTPROBEANDLOCKUSERBUFFERFORREAD)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFREQUEST Request,
    PVOID Buffer,
    size_t Length,
    WDFMEMORY* MemoryObject
);

typedef NTSTATUS (__fastcall * PFN_WDFREQUESTPROBEANDLOCKUSERBUFFERFORWRITE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFREQUEST Request,
    PVOID Buffer,
    size_t Length,
    WDFMEMORY* MemoryObject
);

typedef KPROCESSOR_MODE (__fastcall * PFN_WDFREQUESTGETREQUESTORMODE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFREQUEST Request
);

typedef NTSTATUS (__fastcall * PFN_WDFREQUESTFORWARDTOIOQUEUE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFREQUEST Request,
    WDFQUEUE DestinationQueue
);

typedef WDFQUEUE (__fastcall * PFN_WDFREQUESTGETIOQUEUE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFREQUEST Request
);

typedef NTSTATUS (__fastcall * PFN_WDFREQUESTREQUEUE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFREQUEST Request
);

typedef VOID (__fastcall * PFN_WDFREQUESTSTOPACKNOWLEDGE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFREQUEST Request,
    BOOLEAN Requeue
);

typedef PIRP (__fastcall * PFN_WDFREQUESTWDMGETIRP)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFREQUEST Request
);

typedef VOID (__fastcall * PFN_WDFIORESOURCEREQUIREMENTSLISTSETSLOTNUMBER)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFIORESREQLIST RequirementsList,
    ULONG SlotNumber
);

typedef VOID (__fastcall * PFN_WDFIORESOURCEREQUIREMENTSLISTSETINTERFACETYPE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFIORESREQLIST RequirementsList,
    INTERFACE_TYPE InterfaceType
);

typedef NTSTATUS (__fastcall * PFN_WDFIORESOURCEREQUIREMENTSLISTAPPENDIORESLIST)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFIORESREQLIST RequirementsList,
    WDFIORESLIST IoResList
);

typedef NTSTATUS (__fastcall * PFN_WDFIORESOURCEREQUIREMENTSLISTINSERTIORESLIST)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFIORESREQLIST RequirementsList,
    WDFIORESLIST IoResList,
    ULONG Index
);

typedef ULONG (__fastcall * PFN_WDFIORESOURCEREQUIREMENTSLISTGETCOUNT)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFIORESREQLIST RequirementsList
);

typedef WDFIORESLIST (__fastcall * PFN_WDFIORESOURCEREQUIREMENTSLISTGETIORESLIST)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFIORESREQLIST RequirementsList,
    ULONG Index
);

typedef VOID (__fastcall * PFN_WDFIORESOURCEREQUIREMENTSLISTREMOVE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFIORESREQLIST RequirementsList,
    ULONG Index
);

typedef VOID (__fastcall * PFN_WDFIORESOURCEREQUIREMENTSLISTREMOVEBYIORESLIST)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFIORESREQLIST RequirementsList,
    WDFIORESLIST IoResList
);

typedef NTSTATUS (__fastcall * PFN_WDFIORESOURCELISTCREATE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFIORESREQLIST RequirementsList,
    PWDF_OBJECT_ATTRIBUTES Attributes,
    WDFIORESLIST* ResourceList
);

typedef NTSTATUS (__fastcall * PFN_WDFIORESOURCELISTAPPENDDESCRIPTOR)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFIORESLIST ResourceList,
    PIO_RESOURCE_DESCRIPTOR Descriptor
);

typedef NTSTATUS (__fastcall * PFN_WDFIORESOURCELISTINSERTDESCRIPTOR)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFIORESLIST ResourceList,
    PIO_RESOURCE_DESCRIPTOR Descriptor,
    ULONG Index
);

typedef VOID (__fastcall * PFN_WDFIORESOURCELISTUPDATEDESCRIPTOR)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFIORESLIST ResourceList,
    PIO_RESOURCE_DESCRIPTOR Descriptor,
    ULONG Index
);

typedef ULONG (__fastcall * PFN_WDFIORESOURCELISTGETCOUNT)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFIORESLIST ResourceList
);

typedef PIO_RESOURCE_DESCRIPTOR (__fastcall * PFN_WDFIORESOURCELISTGETDESCRIPTOR)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFIORESLIST ResourceList,
    ULONG Index
);

typedef VOID (__fastcall * PFN_WDFIORESOURCELISTREMOVE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFIORESLIST ResourceList,
    ULONG Index
);

typedef VOID (__fastcall * PFN_WDFIORESOURCELISTREMOVEBYDESCRIPTOR)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFIORESLIST ResourceList,
    PIO_RESOURCE_DESCRIPTOR Descriptor
);

typedef NTSTATUS (__fastcall * PFN_WDFCMRESOURCELISTAPPENDDESCRIPTOR)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFCMRESLIST List,
    PCM_PARTIAL_RESOURCE_DESCRIPTOR Descriptor
);

typedef NTSTATUS (__fastcall * PFN_WDFCMRESOURCELISTINSERTDESCRIPTOR)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFCMRESLIST List,
    PCM_PARTIAL_RESOURCE_DESCRIPTOR Descriptor,
    ULONG Index
);

typedef ULONG (__fastcall * PFN_WDFCMRESOURCELISTGETCOUNT)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFCMRESLIST List
);

typedef PCM_PARTIAL_RESOURCE_DESCRIPTOR (__fastcall * PFN_WDFCMRESOURCELISTGETDESCRIPTOR)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFCMRESLIST List,
    ULONG Index
);

typedef VOID (__fastcall * PFN_WDFCMRESOURCELISTREMOVE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFCMRESLIST List,
    ULONG Index
);

typedef VOID (__fastcall * PFN_WDFCMRESOURCELISTREMOVEBYDESCRIPTOR)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFCMRESLIST List,
    PCM_PARTIAL_RESOURCE_DESCRIPTOR Descriptor
);

typedef NTSTATUS (__fastcall * PFN_WDFSTRINGCREATE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    PCUNICODE_STRING UnicodeString,
    PWDF_OBJECT_ATTRIBUTES StringAttributes,
    WDFSTRING* String
);

typedef VOID (__fastcall * PFN_WDFSTRINGGETUNICODESTRING)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFSTRING String,
    PUNICODE_STRING UnicodeString
);

typedef VOID (__fastcall * PFN_WDFOBJECTACQUIRELOCK)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFOBJECT Object
);

typedef VOID (__fastcall * PFN_WDFOBJECTRELEASELOCK)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFOBJECT Object
);

typedef NTSTATUS (__fastcall * PFN_WDFWAITLOCKCREATE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    PWDF_OBJECT_ATTRIBUTES LockAttributes,
    WDFWAITLOCK* Lock
);

typedef NTSTATUS (__fastcall * PFN_WDFWAITLOCKACQUIRE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFWAITLOCK Lock,
    PLONGLONG Timeout
);

typedef VOID (__fastcall * PFN_WDFWAITLOCKRELEASE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFWAITLOCK Lock
);

typedef NTSTATUS (__fastcall * PFN_WDFSPINLOCKCREATE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    PWDF_OBJECT_ATTRIBUTES SpinLockAttributes,
    WDFSPINLOCK* SpinLock
);

typedef VOID (__fastcall * PFN_WDFSPINLOCKACQUIRE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFSPINLOCK SpinLock
);

typedef VOID (__fastcall * PFN_WDFSPINLOCKRELEASE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFSPINLOCK SpinLock
);

typedef NTSTATUS (__fastcall * PFN_WDFTIMERCREATE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    PWDF_TIMER_CONFIG Config,
    PWDF_OBJECT_ATTRIBUTES Attributes,
    WDFTIMER* Timer
);

typedef BOOLEAN (__fastcall * PFN_WDFTIMERSTART)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFTIMER Timer,
    LONGLONG DueTime
);

typedef BOOLEAN (__fastcall * PFN_WDFTIMERSTOP)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFTIMER Timer,
    BOOLEAN Wait
);

typedef WDFOBJECT (__fastcall * PFN_WDFTIMERGETPARENTOBJECT)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFTIMER Timer
);

typedef NTSTATUS (__fastcall * PFN_WDFUSBTARGETDEVICECREATE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device,
    PWDF_OBJECT_ATTRIBUTES Attributes,
    WDFUSBDEVICE* UsbDevice
);

typedef NTSTATUS (__fastcall * PFN_WDFUSBTARGETDEVICERETRIEVEINFORMATION)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFUSBDEVICE UsbDevice,
    PWDF_USB_DEVICE_INFORMATION Information
);

typedef VOID (__fastcall * PFN_WDFUSBTARGETDEVICEGETDEVICEDESCRIPTOR)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFUSBDEVICE UsbDevice,
    PUSB_DEVICE_DESCRIPTOR UsbDeviceDescriptor
);

typedef NTSTATUS (__fastcall * PFN_WDFUSBTARGETDEVICERETRIEVECONFIGDESCRIPTOR)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFUSBDEVICE UsbDevice,
    PVOID ConfigDescriptor,
    PUSHORT ConfigDescriptorLength
);

typedef NTSTATUS (__fastcall * PFN_WDFUSBTARGETDEVICEQUERYSTRING)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFUSBDEVICE UsbDevice,
    WDFREQUEST Request,
    PWDF_REQUEST_SEND_OPTIONS RequestOptions,
    PUSHORT String,
    PUSHORT NumCharacters,
    UCHAR StringIndex,
    USHORT LangID
);

typedef NTSTATUS (__fastcall * PFN_WDFUSBTARGETDEVICEALLOCANDQUERYSTRING)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFUSBDEVICE UsbDevice,
    PWDF_OBJECT_ATTRIBUTES StringMemoryAttributes,
    WDFMEMORY* StringMemory,
    PUSHORT NumCharacters,
    UCHAR StringIndex,
    USHORT LangID
);

typedef NTSTATUS (__fastcall * PFN_WDFUSBTARGETDEVICEFORMATREQUESTFORSTRING)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFUSBDEVICE UsbDevice,
    WDFREQUEST Request,
    WDFMEMORY Memory,
    PWDFMEMORY_OFFSET Offset,
    UCHAR StringIndex,
    USHORT LangID
);

typedef UCHAR (__fastcall * PFN_WDFUSBTARGETDEVICEGETNUMINTERFACES)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFUSBDEVICE UsbDevice
);

typedef NTSTATUS (__fastcall * PFN_WDFUSBTARGETDEVICESELECTCONFIG)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFUSBDEVICE UsbDevice,
    PWDF_OBJECT_ATTRIBUTES PipeAttributes,
    PWDF_USB_DEVICE_SELECT_CONFIG_PARAMS Params
);

typedef USBD_CONFIGURATION_HANDLE (__fastcall * PFN_WDFUSBTARGETDEVICEWDMGETCONFIGURATIONHANDLE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFUSBDEVICE UsbDevice
);

typedef NTSTATUS (__fastcall * PFN_WDFUSBTARGETDEVICERETRIEVECURRENTFRAMENUMBER)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFUSBDEVICE UsbDevice,
    PULONG CurrentFrameNumber
);

typedef NTSTATUS (__fastcall * PFN_WDFUSBTARGETDEVICESENDCONTROLTRANSFERSYNCHRONOUSLY)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFUSBDEVICE UsbDevice,
    WDFREQUEST Request,
    PWDF_REQUEST_SEND_OPTIONS RequestOptions,
    PWDF_USB_CONTROL_SETUP_PACKET SetupPacket,
    PWDF_MEMORY_DESCRIPTOR MemoryDescriptor,
    PULONG BytesTransferred
);

typedef NTSTATUS (__fastcall * PFN_WDFUSBTARGETDEVICEFORMATREQUESTFORCONTROLTRANSFER)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFUSBDEVICE UsbDevice,
    WDFREQUEST Request,
    PWDF_USB_CONTROL_SETUP_PACKET SetupPacket,
    WDFMEMORY TransferMemory,
    PWDFMEMORY_OFFSET TransferOffset
);

typedef NTSTATUS (__fastcall * PFN_WDFUSBTARGETDEVICEISCONNECTEDSYNCHRONOUS)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFUSBDEVICE UsbDevice
);

typedef NTSTATUS (__fastcall * PFN_WDFUSBTARGETDEVICERESETPORTSYNCHRONOUSLY)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFUSBDEVICE UsbDevice
);

typedef NTSTATUS (__fastcall * PFN_WDFUSBTARGETDEVICECYCLEPORTSYNCHRONOUSLY)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFUSBDEVICE UsbDevice
);

typedef NTSTATUS (__fastcall * PFN_WDFUSBTARGETDEVICEFORMATREQUESTFORCYCLEPORT)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFUSBDEVICE UsbDevice,
    WDFREQUEST Request
);

typedef NTSTATUS (__fastcall * PFN_WDFUSBTARGETDEVICESENDURBSYNCHRONOUSLY)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFUSBDEVICE UsbDevice,
    WDFREQUEST Request,
    PWDF_REQUEST_SEND_OPTIONS RequestOptions,
    PURB Urb
);

typedef NTSTATUS (__fastcall * PFN_WDFUSBTARGETDEVICEFORMATREQUESTFORURB)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFUSBDEVICE UsbDevice,
    WDFREQUEST Request,
    WDFMEMORY UrbMemory,
    PWDFMEMORY_OFFSET UrbMemoryOffset
);

typedef VOID (__fastcall * PFN_WDFUSBTARGETPIPEGETINFORMATION)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFUSBPIPE Pipe,
    PWDF_USB_PIPE_INFORMATION PipeInformation
);

typedef BOOLEAN (__fastcall * PFN_WDFUSBTARGETPIPEISINENDPOINT)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFUSBPIPE Pipe
);

typedef BOOLEAN (__fastcall * PFN_WDFUSBTARGETPIPEISOUTENDPOINT)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFUSBPIPE Pipe
);

typedef WDF_USB_PIPE_TYPE (__fastcall * PFN_WDFUSBTARGETPIPEGETTYPE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFUSBPIPE Pipe
);

typedef VOID (__fastcall * PFN_WDFUSBTARGETPIPESETNOMAXIMUMPACKETSIZECHECK)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFUSBPIPE Pipe
);

typedef NTSTATUS (__fastcall * PFN_WDFUSBTARGETPIPEWRITESYNCHRONOUSLY)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFUSBPIPE Pipe,
    WDFREQUEST Request,
    PWDF_REQUEST_SEND_OPTIONS RequestOptions,
    PWDF_MEMORY_DESCRIPTOR MemoryDescriptor,
    PULONG BytesWritten
);

typedef NTSTATUS (__fastcall * PFN_WDFUSBTARGETPIPEFORMATREQUESTFORWRITE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFUSBPIPE Pipe,
    WDFREQUEST Request,
    WDFMEMORY WriteMemory,
    PWDFMEMORY_OFFSET WriteOffset
);

typedef NTSTATUS (__fastcall * PFN_WDFUSBTARGETPIPEREADSYNCHRONOUSLY)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFUSBPIPE Pipe,
    WDFREQUEST Request,
    PWDF_REQUEST_SEND_OPTIONS RequestOptions,
    PWDF_MEMORY_DESCRIPTOR MemoryDescriptor,
    PULONG BytesRead
);


typedef NTSTATUS (*PFN_WDFUSBTARGETPIPEFORMATREQUESTFORREAD)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFUSBPIPE Pipe,
    WDFREQUEST Request,
    WDFMEMORY ReadMemory,
    PWDFMEMORY_OFFSET ReadOffset
);

typedef NTSTATUS (*PFN_WDFUSBTARGETPIPECONFIGCONTINUOUSREADER)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFUSBPIPE Pipe,
    PWDF_USB_CONTINUOUS_READER_CONFIG Config
);

typedef NTSTATUS (__fastcall * PFN_WDFUSBTARGETPIPEABORTSYNCHRONOUSLY)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFUSBPIPE Pipe,
    WDFREQUEST Request,
    PWDF_REQUEST_SEND_OPTIONS RequestOptions
);

typedef NTSTATUS (__fastcall * PFN_WDFUSBTARGETPIPEFORMATREQUESTFORABORT)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFUSBPIPE Pipe,
    WDFREQUEST Request
);

typedef NTSTATUS (__fastcall * PFN_WDFUSBTARGETPIPERESETSYNCHRONOUSLY)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFUSBPIPE Pipe,
    WDFREQUEST Request,
    PWDF_REQUEST_SEND_OPTIONS RequestOptions
);

typedef NTSTATUS (__fastcall * PFN_WDFUSBTARGETPIPEFORMATREQUESTFORRESET)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFUSBPIPE Pipe,
    WDFREQUEST Request
);

typedef NTSTATUS (__fastcall * PFN_WDFUSBTARGETPIPESENDURBSYNCHRONOUSLY)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFUSBPIPE Pipe,
    WDFREQUEST Request,
    PWDF_REQUEST_SEND_OPTIONS RequestOptions,
    PURB Urb
);

typedef NTSTATUS (__fastcall * PFN_WDFUSBTARGETPIPEFORMATREQUESTFORURB)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFUSBPIPE PIPE,
    WDFREQUEST Request,
    WDFMEMORY UrbMemory,
    PWDFMEMORY_OFFSET UrbMemoryOffset
);

typedef BYTE (__fastcall * PFN_WDFUSBINTERFACEGETINTERFACENUMBER)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFUSBINTERFACE UsbInterface
);

typedef BYTE (__fastcall * PFN_WDFUSBINTERFACEGETNUMENDPOINTS)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFUSBINTERFACE UsbInterface,
    UCHAR SettingIndex
);

typedef VOID (__fastcall * PFN_WDFUSBINTERFACEGETDESCRIPTOR)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFUSBINTERFACE UsbInterface,
    UCHAR SettingIndex,
    PUSB_INTERFACE_DESCRIPTOR InterfaceDescriptor
);

typedef NTSTATUS (__fastcall * PFN_WDFUSBINTERFACESELECTSETTING)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFUSBINTERFACE UsbInterface,
    PWDF_OBJECT_ATTRIBUTES PipesAttributes,
    PWDF_USB_INTERFACE_SELECT_SETTING_PARAMS Params
);

typedef VOID (__fastcall * PFN_WDFUSBINTERFACEGETENDPOINTINFORMATION)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFUSBINTERFACE UsbInterface,
    UCHAR SettingIndex,
    UCHAR EndpointIndex,
    PWDF_USB_PIPE_INFORMATION EndpointInfo
);

typedef WDFUSBINTERFACE (__fastcall * PFN_WDFUSBTARGETDEVICEGETINTERFACE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFUSBDEVICE UsbDevice,
    UCHAR InterfaceIndex
);

typedef BYTE (__fastcall * PFN_WDFUSBINTERFACEGETCONFIGUREDSETTINGINDEX)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFUSBINTERFACE Interface
);

typedef BYTE (__fastcall * PFN_WDFUSBINTERFACEGETNUMCONFIGUREDPIPES)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFUSBINTERFACE UsbInterface
);

typedef WDFUSBPIPE (__fastcall * PFN_WDFUSBINTERFACEGETCONFIGUREDPIPE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFUSBINTERFACE UsbInterface,
    UCHAR PipeIndex,
    PWDF_USB_PIPE_INFORMATION PipeInfo
);

typedef USBD_PIPE_HANDLE (__fastcall * PFN_WDFUSBTARGETPIPEWDMGETPIPEHANDLE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFUSBPIPE UsbPipe
);

typedef VOID (__fastcall * PFN_WDFVERIFIERDBGBREAKPOINT)(
    PWDF_DRIVER_GLOBALS DriverGlobals
);

typedef VOID (__fastcall * PFN_WDFVERIFIERKEBUGCHECK)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    ULONG BugCheckCode,
    ULONG_PTR BugCheckParameter1,
    ULONG_PTR BugCheckParameter2,
    ULONG_PTR BugCheckParameter3,
    ULONG_PTR BugCheckParameter4
);

typedef NTSTATUS (__fastcall * PFN_WDFWMIPROVIDERCREATE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device,
    PWDF_WMI_PROVIDER_CONFIG WmiProviderConfig,
    PWDF_OBJECT_ATTRIBUTES ProviderAttributes,
    WDFWMIPROVIDER* WmiProvider
);

typedef WDFDEVICE (__fastcall * PFN_WDFWMIPROVIDERGETDEVICE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFWMIPROVIDER WmiProvider
);

typedef BOOLEAN (__fastcall * PFN_WDFWMIPROVIDERISENABLED)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFWMIPROVIDER WmiProvider,
    WDF_WMI_PROVIDER_CONTROL ProviderControl
);

typedef ULONGLONG (__fastcall * PFN_WDFWMIPROVIDERGETTRACINGHANDLE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFWMIPROVIDER WmiProvider
);

typedef NTSTATUS (__fastcall * PFN_WDFWMIINSTANCECREATE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device,
    PWDF_WMI_INSTANCE_CONFIG InstanceConfig,
    PWDF_OBJECT_ATTRIBUTES InstanceAttributes,
    WDFWMIINSTANCE* Instance
);

typedef NTSTATUS (__fastcall * PFN_WDFWMIINSTANCEREGISTER)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFWMIINSTANCE WmiInstance
);

typedef VOID (__fastcall * PFN_WDFWMIINSTANCEDEREGISTER)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFWMIINSTANCE WmiInstance
);

typedef WDFDEVICE (__fastcall * PFN_WDFWMIINSTANCEGETDEVICE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFWMIINSTANCE WmiInstance
);

typedef WDFWMIPROVIDER (__fastcall * PFN_WDFWMIINSTANCEGETPROVIDER)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFWMIINSTANCE WmiInstance
);

typedef NTSTATUS (__fastcall * PFN_WDFWMIINSTANCEFIREEVENT)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFWMIINSTANCE WmiInstance,
    ULONG EventDataSize,    
    PVOID EventData
);

typedef NTSTATUS (__fastcall * PFN_WDFWORKITEMCREATE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    PWDF_WORKITEM_CONFIG Config,
    PWDF_OBJECT_ATTRIBUTES Attributes,
    WDFWORKITEM* WorkItem
);

typedef VOID (__fastcall * PFN_WDFWORKITEMENQUEUE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFWORKITEM WorkItem
);

typedef WDFOBJECT (__fastcall * PFN_WDFWORKITEMGETPARENTOBJECT)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFWORKITEM WorkItem
);

typedef VOID (__fastcall * PFN_WDFWORKITEMFLUSH)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFWORKITEM WorkItem
);

typedef NTSTATUS (__fastcall * PFN_WDFCOMMONBUFFERCREATEWITHCONFIG)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDMAENABLER DmaEnabler,
    size_t Length,
    PWDF_COMMON_BUFFER_CONFIG Config,
    PWDF_OBJECT_ATTRIBUTES Attributes,
    WDFCOMMONBUFFER* CommonBuffer
);

typedef size_t (__fastcall * PFN_WDFDMAENABLERGETFRAGMENTLENGTH)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDMAENABLER DmaEnabler,
    WDF_DMA_DIRECTION DmaDirection
);

typedef PDMA_ADAPTER (__fastcall * PFN_WDFDMAENABLERWDMGETDMAADAPTER)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDMAENABLER DmaEnabler,
    WDF_DMA_DIRECTION DmaDirection
);

typedef BYTE (__fastcall * PFN_WDFUSBINTERFACEGETNUMSETTINGS)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFUSBINTERFACE UsbInterface
);

typedef VOID (__fastcall * PFN_WDFDEVICEREMOVEDEPENDENTUSAGEDEVICEOBJECT)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device,
    PDEVICE_OBJECT DependentDevice
);

typedef POWER_ACTION (__fastcall * PFN_WDFDEVICEGETSYSTEMPOWERACTION)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device
);

typedef VOID (__fastcall * PFN_WDFINTERRUPTSETEXTENDEDPOLICY)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFINTERRUPT Interrupt,
    PWDF_INTERRUPT_EXTENDED_POLICY PolicyAndGroup
);

typedef NTSTATUS (__fastcall * PFN_WDFIOQUEUEASSIGNFORWARDPROGRESSPOLICY)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFQUEUE Queue,
    PWDF_IO_QUEUE_FORWARD_PROGRESS_POLICY ForwardProgressPolicy
);

typedef NTSTATUS (__fastcall * PFN_WDFPDOINITASSIGNCONTAINERID)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    PWDFDEVICE_INIT DeviceInit,
    PCUNICODE_STRING ContainerID
);

typedef VOID (__fastcall * PFN_WDFPDOINITALLOWFORWARDINGREQUESTTOPARENT)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    PWDFDEVICE_INIT DeviceInit
);

typedef NTSTATUS (__fastcall * PFN_WDFREQUESTMARKCANCELABLEEX)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFREQUEST Request,
    PFN_WDF_REQUEST_CANCEL EvtRequestCancel
);

typedef BOOLEAN (__fastcall * PFN_WDFREQUESTISRESERVED)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFREQUEST Request
);

typedef NTSTATUS (__fastcall * PFN_WDFREQUESTFORWARDTOPARENTDEVICEIOQUEUE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFREQUEST Request,
    WDFQUEUE ParentDeviceQueue,
    PWDF_REQUEST_FORWARD_OPTIONS ForwardOptions
);

typedef PVOID PFN_WDFCXDEVICEINITALLOCATE;
typedef PVOID PFN_WDFCXDEVICEINITASSIGNWDMIRPPREPROCESSCALLBACK;
typedef PVOID PFN_WDFCXDEVICEINITSETIOINCALLERCONTEXTCALLBACK;
typedef PVOID PFN_WDFCXDEVICEINITSETREQUESTATTRIBUTES;
typedef PVOID PFN_WDFCXDEVICEINITSETFILEOBJECTCONFIG;

typedef NTSTATUS (__fastcall * PFN_WDFDEVICEWDMDISPATCHIRP)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device,
    PIRP Irp,
    WDFCONTEXT DispatchContext
);

typedef NTSTATUS (__fastcall * PFN_WDFDEVICEWDMDISPATCHIRPTOIOQUEUE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device,
    PIRP Irp,
    WDFQUEUE Queue,
    ULONG Flags
);

typedef VOID (__fastcall * PFN_WDFDEVICEINITSETREMOVELOCKOPTIONS)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    PWDFDEVICE_INIT DeviceInit,
    PWDF_REMOVE_LOCK_OPTIONS Options
);

typedef NTSTATUS (__fastcall * PFN_WDFDEVICECONFIGUREWDMIRPDISPATCHCALLBACK)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device,
    WDFDRIVER Driver,
    UCHAR MajorFunction,
    PFN_WDFDEVICE_WDM_IRP_DISPATCH EvtDeviceWdmIrpDisptach,
    WDFCONTEXT DriverContext
);

typedef NTSTATUS (__fastcall * PFN_WDFDMAENABLERCONFIGURESYSTEMPROFILE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDMAENABLER DmaEnabler,
    PWDF_DMA_SYSTEM_PROFILE_CONFIG ProfileConfig,
    WDF_DMA_DIRECTION ConfigDirection
);

typedef NTSTATUS (__fastcall * PFN_WDFDMATRANSACTIONINITIALIZEUSINGOFFSET)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDMATRANSACTION DmaTransaction,
    PFN_WDF_PROGRAM_DMA EvtProgramDmaFunction,
    WDF_DMA_DIRECTION DmaDirection,
    PMDL Mdl,
    size_t Offset,
    size_t Length
);

typedef VOID (__fastcall * PFN_WDFDMATRANSACTIONGETTRANSFERINFO)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDMATRANSACTION DmaTransaction,
    ULONG* MapRegisterCount,
    ULONG* ScatterGatherElementCount
);

typedef VOID (__fastcall * PFN_WDFDMATRANSACTIONSETCHANNELCONFIGURATIONCALLBACK)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDMATRANSACTION DmaTransaction,
    PFN_WDF_DMA_TRANSACTION_CONFIGURE_DMA_CHANNEL ConfigureRoutine,
    PVOID ConfigureContext
);

typedef VOID (__fastcall * PFN_WDFDMATRANSACTIONSETTRANSFERCOMPLETECALLBACK)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDMATRANSACTION DmaTransaction,
    PFN_WDF_DMA_TRANSACTION_DMA_TRANSFER_COMPLETE DmaCompletionRoutine,
    PVOID DmaCompletionContext
);

typedef VOID (__fastcall * PFN_WDFDMATRANSACTIONSETIMMEDIATEEXECUTION)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDMATRANSACTION DmaTransaction,
    BOOLEAN UseImmediateExecution
);

typedef NTSTATUS (__fastcall * PFN_WDFDMATRANSACTIONALLOCATERESOURCES)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDMATRANSACTION DmaTransaction,
    WDF_DMA_DIRECTION DmaDirection,
    ULONG RequiredMapRegisters,
    PFN_WDF_RESERVE_DMA EvtReserveDmaFunction,
    PVOID EvtReserveDmaContext
);

typedef VOID (__fastcall * PFN_WDFDMATRANSACTIONSETDEVICEADDRESSOFFSET)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDMATRANSACTION DmaTransaction,
    ULONG Offset
);

typedef VOID (__fastcall * PFN_WDFDMATRANSACTIONFREERESOURCES)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDMATRANSACTION DmaTransaction
);

typedef BOOLEAN (__fastcall * PFN_WDFDMATRANSACTIONCANCEL)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDMATRANSACTION DmaTransaction
);

typedef PVOID (__fastcall * PFN_WDFDMATRANSACTIONWDMGETTRANSFERCONTEXT)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDMATRANSACTION DmaTransaction
);

typedef BOOLEAN (__fastcall * PFN_WDFINTERRUPTQUEUEWORKITEMFORISR)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFINTERRUPT Interrupt
);

typedef BOOLEAN (__fastcall * PFN_WDFINTERRUPTTRYTOACQUIRELOCK)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFINTERRUPT Interrupt
);

typedef VOID (__fastcall * PFN_WDFIOQUEUESTOPANDPURGE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFQUEUE Queue,
    PFN_WDF_IO_QUEUE_STATE StopAndPurgeComplete,
    WDFCONTEXT Context
);

typedef VOID (__fastcall * PFN_WDFIOQUEUESTOPANDPURGESYNCHRONOUSLY)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFQUEUE Queue
);

typedef VOID (__fastcall * PFN_WDFIOTARGETPURGE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFIOTARGET IoTarget,
    WDF_IO_TARGET_PURGE_IO_ACTION Action
);

typedef NTSTATUS (__fastcall * PFN_WDFUSBTARGETDEVICECREATEWITHPARAMETERS)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device,
    PWDF_USB_DEVICE_CREATE_CONFIG Config,
    PWDF_OBJECT_ATTRIBUTES Attributes,
    WDFUSBDEVICE* UsbDevice
);

typedef NTSTATUS (__fastcall * PFN_WDFUSBTARGETDEVICEQUERYUSBCAPABILITY)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFUSBDEVICE UsbDevice,
    const GUID* CapabilityType,
    ULONG CapabilityBufferLength,
    PVOID CapabilityBuffer,
    PULONG ResultLength
);

typedef NTSTATUS (__fastcall * PFN_WDFUSBTARGETDEVICECREATEURB)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFUSBDEVICE UsbDevice,
    PWDF_OBJECT_ATTRIBUTES Attributes,
    WDFMEMORY* UrbMemory,
    PURB* Urb
);

typedef NTSTATUS (__fastcall * PFN_WDFUSBTARGETDEVICECREATEISOCHURB)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFUSBDEVICE UsbDevice,
    PWDF_OBJECT_ATTRIBUTES Attributes,
    ULONG NumberOfIsochPackets,
    WDFMEMORY* UrbMemory,
    PURB* Urb
);

typedef NTSTATUS (__fastcall * PFN_WDFDEVICEWDMASSIGNPOWERFRAMEWORKSETTINGS)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device,
    PWDF_POWER_FRAMEWORK_SETTINGS PowerFrameworkSettings
);

typedef VOID (__fastcall * PFN_WDFDMATRANSACTIONSTOPSYSTEMTRANSFER)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDMATRANSACTION DmaTransaction
);

typedef PVOID PFN_WDFCXVERIFIERKEBUGCHECK;

typedef VOID (__fastcall * PFN_WDFINTERRUPTREPORTACTIVE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFINTERRUPT Interrupt
);

typedef VOID (__fastcall * PFN_WDFINTERRUPTREPORTINACTIVE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFINTERRUPT Interrupt
);

typedef VOID (__fastcall * PFN_WDFDEVICEINITSETRELEASEHARDWAREORDERONFAILURE)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    PWDFDEVICE_INIT DeviceInit,
    WDF_RELEASE_HARDWARE_ORDER_ON_FAILURE ReleaseHardwareOrderOnFailure
);

typedef PVOID (__fastcall * PFN_WDFGETTRIAGEINFO)(
    PWDF_DRIVER_GLOBALS DriverGlobals
);

typedef VOID (__fastcall * PFN_WDFDEVICEINITSETIOTYPEEX)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    PWDFDEVICE_INIT DeviceInit,
    PWDF_IO_TYPE_CONFIG IoTypeConfig
);

typedef NTSTATUS (__fastcall * PFN_WDFDEVICEQUERYPROPERTYEX)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device,
    PWDF_DEVICE_PROPERTY_DATA DeviceProperty,
    ULONG BufferLength,
    PVOID PropertyBuffer,
    PULONG RequiredSize,
    PDEVPROPTYPE Type
);

typedef NTSTATUS (__fastcall * PFN_WDFDEVICEALLOCANDQUERYPROPERTYEX)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device,
    PWDF_DEVICE_PROPERTY_DATA DeviceProperty,
    POOL_TYPE PoolType,
    PWDF_OBJECT_ATTRIBUTES PropertyMemoryAttributes,
    WDFMEMORY* PropertyMemory,
    PDEVPROPTYPE Type
);

typedef NTSTATUS (__fastcall * PFN_WDFDEVICEASSIGNPROPERTY)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device,
    PWDF_DEVICE_PROPERTY_DATA DeviceProperty,
    DEVPROPTYPE Type,
    ULONG Size,
    PVOID Data
);

typedef NTSTATUS (__fastcall * PFN_WDFFDOINITQUERYPROPERTYEX)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    PWDFDEVICE_INIT DeviceInit,
    PWDF_DEVICE_PROPERTY_DATA DeviceProperty,
    ULONG BufferLength,
    PVOID PropertyBuffer,
    PULONG ResultLength,
    PDEVPROPTYPE Type
);

typedef NTSTATUS (__fastcall * PFN_WDFFDOINITALLOCANDQUERYPROPERTYEX)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    PWDFDEVICE_INIT DeviceInit,
    PWDF_DEVICE_PROPERTY_DATA DeviceProperty,
    POOL_TYPE PoolType,
    PWDF_OBJECT_ATTRIBUTES PropertyMemoryAttributes,
    WDFMEMORY* PropertyMemory,
    PDEVPROPTYPE Type
);

typedef NTSTATUS (__fastcall * PFN_WDFDEVICESTOPIDLEACTUAL)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device,
    BOOLEAN WaitForD0,
    PVOID Tag,
    LONG Line,
    PCCH File
);

typedef VOID (__fastcall * PFN_WDFDEVICERESUMEIDLEACTUAL)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device,
    PVOID Tag,
    LONG Line,
    PCCH File
);

typedef PVOID PFN_WDFDEVICEGETSELFIOTARGET;
typedef PVOID PFN_WDFDEVICEINITALLOWSELFIOTARGET;
typedef PVOID PFN_WDFIOTARGETSELFASSIGNDEFAULTIOQUEUE;

typedef NTSTATUS (__fastcall * PFN_WDFDEVICEOPENDEVICEMAPKEY)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device,
    PCUNICODE_STRING KeyName,
    ACCESS_MASK DesiredAccess,
    PWDF_OBJECT_ATTRIBUTES KeyAttributes,
    WDFKEY* Key
);

typedef VOID (__fastcall * PFN_WDFDMATRANSACTIONSETSINGLETRANSFERREQUIREMENT)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDMATRANSACTION DmaTransaction,
    BOOLEAN RequireSingleTransfer
);

typedef PVOID PFN_WDFCXDEVICEINITSETPNPPOWEREVENTCALLBACKS;

typedef ULONG (__fastcall * PFN_WDFFILEOBJECTGETINITIATORPROCESSID)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFFILEOBJECT FileObject
);

typedef ULONG (__fastcall * PFN_WDFREQUESTGETREQUESTORPROCESSID)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFREQUEST Request
);

typedef NTSTATUS (__fastcall * PFN_WDFDEVICERETRIEVECOMPANIONTARGET)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDEVICE Device,
    WDFCOMPANIONTARGET* CompanionTarget
);

typedef NTSTATUS (__fastcall * PFN_WDFCOMPANIONTARGETSENDTASKSYNCHRONOUSLY)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFCOMPANIONTARGET CompanionTarget,
    USHORT TaskQueueIdentifier,
    ULONG TaskOperationCode,
    PWDF_MEMORY_DESCRIPTOR InputBuffer,
    PWDF_MEMORY_DESCRIPTOR OutputBuffer,
    PWDF_TASK_SEND_OPTIONS TaskOptions,
    PULONG_PTR BytesReturned
);

typedef PEPROCESS (__fastcall * PFN_WDFCOMPANIONTARGETWDMGETCOMPANIONPROCESS)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFCOMPANIONTARGET CompanionTarget
);

typedef NTSTATUS (__fastcall * PFN_WDFDRIVEROPENPERSISTENTSTATEREGISTRYKEY)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDRIVER Driver,
    ACCESS_MASK DesiredAccess,
    PWDF_OBJECT_ATTRIBUTES KeyAttributes,
    WDFKEY* Key
);

typedef NTSTATUS (__fastcall * PFN_WDFDRIVERERRORREPORTAPIMISSING)(
    PWDF_DRIVER_GLOBALS DriverGlobals,
    WDFDRIVER Driver,
    PCWSTR FrameworkExtensionName,
    ULONG ApiIndex,
    BOOLEAN DoesApiReturnNtstatus
);


struct _WDFFUNCTIONS_V100 {
    PFN_WDFCHILDLISTCREATE                                    pfnWdfChildListCreate;
    PFN_WDFCHILDLISTGETDEVICE                                 pfnWdfChildListGetDevice;
    PFN_WDFCHILDLISTRETRIEVEPDO                               pfnWdfChildListRetrievePdo;
    PFN_WDFCHILDLISTRETRIEVEADDRESSDESCRIPTION                pfnWdfChildListRetrieveAddressDescription;
    PFN_WDFCHILDLISTBEGINSCAN                                 pfnWdfChildListBeginScan;
    PFN_WDFCHILDLISTENDSCAN                                   pfnWdfChildListEndScan;
    PFN_WDFCHILDLISTBEGINITERATION                            pfnWdfChildListBeginIteration;
    PFN_WDFCHILDLISTRETRIEVENEXTDEVICE                        pfnWdfChildListRetrieveNextDevice;
    PFN_WDFCHILDLISTENDITERATION                              pfnWdfChildListEndIteration;
    PFN_WDFCHILDLISTADDORUPDATECHILDDESCRIPTIONASPRESENT      pfnWdfChildListAddOrUpdateChildDescriptionAsPresent;
    PFN_WDFCHILDLISTUPDATECHILDDESCRIPTIONASMISSING           pfnWdfChildListUpdateChildDescriptionAsMissing;
    PFN_WDFCHILDLISTUPDATEALLCHILDDESCRIPTIONSASPRESENT       pfnWdfChildListUpdateAllChildDescriptionsAsPresent;
    PFN_WDFCHILDLISTREQUESTCHILDEJECT                         pfnWdfChildListRequestChildEject;
    PFN_WDFCOLLECTIONCREATE                                   pfnWdfCollectionCreate;
    PFN_WDFCOLLECTIONGETCOUNT                                 pfnWdfCollectionGetCount;
    PFN_WDFCOLLECTIONADD                                      pfnWdfCollectionAdd;
    PFN_WDFCOLLECTIONREMOVE                                   pfnWdfCollectionRemove;
    PFN_WDFCOLLECTIONREMOVEITEM                               pfnWdfCollectionRemoveItem;
    PFN_WDFCOLLECTIONGETITEM                                  pfnWdfCollectionGetItem;
    PFN_WDFCOLLECTIONGETFIRSTITEM                             pfnWdfCollectionGetFirstItem;
    PFN_WDFCOLLECTIONGETLASTITEM                              pfnWdfCollectionGetLastItem;
    PFN_WDFCOMMONBUFFERCREATE                                 pfnWdfCommonBufferCreate;
    PFN_WDFCOMMONBUFFERGETALIGNEDVIRTUALADDRESS               pfnWdfCommonBufferGetAlignedVirtualAddress;
    PFN_WDFCOMMONBUFFERGETALIGNEDLOGICALADDRESS               pfnWdfCommonBufferGetAlignedLogicalAddress;
    PFN_WDFCOMMONBUFFERGETLENGTH                              pfnWdfCommonBufferGetLength;
    PFN_WDFCONTROLDEVICEINITALLOCATE                          pfnWdfControlDeviceInitAllocate;
    PFN_WDFCONTROLDEVICEINITSETSHUTDOWNNOTIFICATION           pfnWdfControlDeviceInitSetShutdownNotification;
    PFN_WDFCONTROLFINISHINITIALIZING                          pfnWdfControlFinishInitializing;
    PFN_WDFDEVICEGETDEVICESTATE                               pfnWdfDeviceGetDeviceState;
    PFN_WDFDEVICESETDEVICESTATE                               pfnWdfDeviceSetDeviceState;
    PFN_WDFWDMDEVICEGETWDFDEVICEHANDLE                        pfnWdfWdmDeviceGetWdfDeviceHandle;
    PFN_WDFDEVICEWDMGETDEVICEOBJECT                           pfnWdfDeviceWdmGetDeviceObject;
    PFN_WDFDEVICEWDMGETATTACHEDDEVICE                         pfnWdfDeviceWdmGetAttachedDevice;
    PFN_WDFDEVICEWDMGETPHYSICALDEVICE                         pfnWdfDeviceWdmGetPhysicalDevice;
    PFN_WDFDEVICEWDMDISPATCHPREPROCESSEDIRP                   pfnWdfDeviceWdmDispatchPreprocessedIrp;
    PFN_WDFDEVICEADDDEPENDENTUSAGEDEVICEOBJECT                pfnWdfDeviceAddDependentUsageDeviceObject;
    PFN_WDFDEVICEADDREMOVALRELATIONSPHYSICALDEVICE            pfnWdfDeviceAddRemovalRelationsPhysicalDevice;
    PFN_WDFDEVICEREMOVEREMOVALRELATIONSPHYSICALDEVICE         pfnWdfDeviceRemoveRemovalRelationsPhysicalDevice;
    PFN_WDFDEVICECLEARREMOVALRELATIONSDEVICES                 pfnWdfDeviceClearRemovalRelationsDevices;
    PFN_WDFDEVICEGETDRIVER                                    pfnWdfDeviceGetDriver;
    PFN_WDFDEVICERETRIEVEDEVICENAME                           pfnWdfDeviceRetrieveDeviceName;
    PFN_WDFDEVICEASSIGNMOFRESOURCENAME                        pfnWdfDeviceAssignMofResourceName;
    PFN_WDFDEVICEGETIOTARGET                                  pfnWdfDeviceGetIoTarget;
    PFN_WDFDEVICEGETDEVICEPNPSTATE                            pfnWdfDeviceGetDevicePnpState;
    PFN_WDFDEVICEGETDEVICEPOWERSTATE                          pfnWdfDeviceGetDevicePowerState;
    PFN_WDFDEVICEGETDEVICEPOWERPOLICYSTATE                    pfnWdfDeviceGetDevicePowerPolicyState;
    PFN_WDFDEVICEASSIGNS0IDLESETTINGS                         pfnWdfDeviceAssignS0IdleSettings;
    PFN_WDFDEVICEASSIGNSXWAKESETTINGS                         pfnWdfDeviceAssignSxWakeSettings;
    PFN_WDFDEVICEOPENREGISTRYKEY                              pfnWdfDeviceOpenRegistryKey;
    PFN_WDFDEVICESETSPECIALFILESUPPORT                        pfnWdfDeviceSetSpecialFileSupport;
    PFN_WDFDEVICESETCHARACTERISTICS                           pfnWdfDeviceSetCharacteristics;
    PFN_WDFDEVICEGETCHARACTERISTICS                           pfnWdfDeviceGetCharacteristics;
    PFN_WDFDEVICEGETALIGNMENTREQUIREMENT                      pfnWdfDeviceGetAlignmentRequirement;
    PFN_WDFDEVICESETALIGNMENTREQUIREMENT                      pfnWdfDeviceSetAlignmentRequirement;
    PFN_WDFDEVICEINITFREE                                     pfnWdfDeviceInitFree;
    PFN_WDFDEVICEINITSETPNPPOWEREVENTCALLBACKS                pfnWdfDeviceInitSetPnpPowerEventCallbacks;
    PFN_WDFDEVICEINITSETPOWERPOLICYEVENTCALLBACKS             pfnWdfDeviceInitSetPowerPolicyEventCallbacks;
    PFN_WDFDEVICEINITSETPOWERPOLICYOWNERSHIP                  pfnWdfDeviceInitSetPowerPolicyOwnership;
    PFN_WDFDEVICEINITREGISTERPNPSTATECHANGECALLBACK           pfnWdfDeviceInitRegisterPnpStateChangeCallback;
    PFN_WDFDEVICEINITREGISTERPOWERSTATECHANGECALLBACK         pfnWdfDeviceInitRegisterPowerStateChangeCallback;
    PFN_WDFDEVICEINITREGISTERPOWERPOLICYSTATECHANGECALLBACK    pfnWdfDeviceInitRegisterPowerPolicyStateChangeCallback;
    PFN_WDFDEVICEINITSETIOTYPE                                pfnWdfDeviceInitSetIoType;
    PFN_WDFDEVICEINITSETEXCLUSIVE                             pfnWdfDeviceInitSetExclusive;
    PFN_WDFDEVICEINITSETPOWERNOTPAGEABLE                      pfnWdfDeviceInitSetPowerNotPageable;
    PFN_WDFDEVICEINITSETPOWERPAGEABLE                         pfnWdfDeviceInitSetPowerPageable;
    PFN_WDFDEVICEINITSETPOWERINRUSH                           pfnWdfDeviceInitSetPowerInrush;
    PFN_WDFDEVICEINITSETDEVICETYPE                            pfnWdfDeviceInitSetDeviceType;
    PFN_WDFDEVICEINITASSIGNNAME                               pfnWdfDeviceInitAssignName;
    PFN_WDFDEVICEINITASSIGNSDDLSTRING                         pfnWdfDeviceInitAssignSDDLString;
    PFN_WDFDEVICEINITSETDEVICECLASS                           pfnWdfDeviceInitSetDeviceClass;
    PFN_WDFDEVICEINITSETCHARACTERISTICS                       pfnWdfDeviceInitSetCharacteristics;
    PFN_WDFDEVICEINITSETFILEOBJECTCONFIG                      pfnWdfDeviceInitSetFileObjectConfig;
    PFN_WDFDEVICEINITSETREQUESTATTRIBUTES                     pfnWdfDeviceInitSetRequestAttributes;
    PFN_WDFDEVICEINITASSIGNWDMIRPPREPROCESSCALLBACK           pfnWdfDeviceInitAssignWdmIrpPreprocessCallback;
    PFN_WDFDEVICEINITSETIOINCALLERCONTEXTCALLBACK             pfnWdfDeviceInitSetIoInCallerContextCallback;
    PFN_WDFDEVICECREATE                                       pfnWdfDeviceCreate;
    PFN_WDFDEVICESETSTATICSTOPREMOVE                          pfnWdfDeviceSetStaticStopRemove;
    PFN_WDFDEVICECREATEDEVICEINTERFACE                        pfnWdfDeviceCreateDeviceInterface;
    PFN_WDFDEVICESETDEVICEINTERFACESTATE                      pfnWdfDeviceSetDeviceInterfaceState;
    PFN_WDFDEVICERETRIEVEDEVICEINTERFACESTRING                pfnWdfDeviceRetrieveDeviceInterfaceString;
    PFN_WDFDEVICECREATESYMBOLICLINK                           pfnWdfDeviceCreateSymbolicLink;
    PFN_WDFDEVICEQUERYPROPERTY                                pfnWdfDeviceQueryProperty;
    PFN_WDFDEVICEALLOCANDQUERYPROPERTY                        pfnWdfDeviceAllocAndQueryProperty;
    PFN_WDFDEVICESETPNPCAPABILITIES                           pfnWdfDeviceSetPnpCapabilities;
    PFN_WDFDEVICESETPOWERCAPABILITIES                         pfnWdfDeviceSetPowerCapabilities;
    PFN_WDFDEVICESETBUSINFORMATIONFORCHILDREN                 pfnWdfDeviceSetBusInformationForChildren;
    PFN_WDFDEVICEINDICATEWAKESTATUS                           pfnWdfDeviceIndicateWakeStatus;
    PFN_WDFDEVICESETFAILED                                    pfnWdfDeviceSetFailed;
    PFN_WDFDEVICESTOPIDLENOTRACK                              pfnWdfDeviceStopIdleNoTrack;
    PFN_WDFDEVICERESUMEIDLENOTRACK                            pfnWdfDeviceResumeIdleNoTrack;
    PFN_WDFDEVICEGETFILEOBJECT                                pfnWdfDeviceGetFileObject;
    PFN_WDFDEVICEENQUEUEREQUEST                               pfnWdfDeviceEnqueueRequest;
    PFN_WDFDEVICEGETDEFAULTQUEUE                              pfnWdfDeviceGetDefaultQueue;
    PFN_WDFDEVICECONFIGUREREQUESTDISPATCHING                  pfnWdfDeviceConfigureRequestDispatching;
    PFN_WDFDMAENABLERCREATE                                   pfnWdfDmaEnablerCreate;
    PFN_WDFDMAENABLERGETMAXIMUMLENGTH                         pfnWdfDmaEnablerGetMaximumLength;
    PFN_WDFDMAENABLERGETMAXIMUMSCATTERGATHERELEMENTS          pfnWdfDmaEnablerGetMaximumScatterGatherElements;
    PFN_WDFDMAENABLERSETMAXIMUMSCATTERGATHERELEMENTS          pfnWdfDmaEnablerSetMaximumScatterGatherElements;
    PFN_WDFDMATRANSACTIONCREATE                               pfnWdfDmaTransactionCreate;
    PFN_WDFDMATRANSACTIONINITIALIZE                           pfnWdfDmaTransactionInitialize;
    PFN_WDFDMATRANSACTIONINITIALIZEUSINGREQUEST               pfnWdfDmaTransactionInitializeUsingRequest;
    PFN_WDFDMATRANSACTIONEXECUTE                              pfnWdfDmaTransactionExecute;
    PFN_WDFDMATRANSACTIONRELEASE                              pfnWdfDmaTransactionRelease;
    PFN_WDFDMATRANSACTIONDMACOMPLETED                         pfnWdfDmaTransactionDmaCompleted;
    PFN_WDFDMATRANSACTIONDMACOMPLETEDWITHLENGTH               pfnWdfDmaTransactionDmaCompletedWithLength;
    PFN_WDFDMATRANSACTIONDMACOMPLETEDFINAL                    pfnWdfDmaTransactionDmaCompletedFinal;
    PFN_WDFDMATRANSACTIONGETBYTESTRANSFERRED                  pfnWdfDmaTransactionGetBytesTransferred;
    PFN_WDFDMATRANSACTIONSETMAXIMUMLENGTH                     pfnWdfDmaTransactionSetMaximumLength;
    PFN_WDFDMATRANSACTIONGETREQUEST                           pfnWdfDmaTransactionGetRequest;
    PFN_WDFDMATRANSACTIONGETCURRENTDMATRANSFERLENGTH          pfnWdfDmaTransactionGetCurrentDmaTransferLength;
    PFN_WDFDMATRANSACTIONGETDEVICE                            pfnWdfDmaTransactionGetDevice;
    PFN_WDFDPCCREATE                                          pfnWdfDpcCreate;
    PFN_WDFDPCENQUEUE                                         pfnWdfDpcEnqueue;
    PFN_WDFDPCCANCEL                                          pfnWdfDpcCancel;
    PFN_WDFDPCGETPARENTOBJECT                                 pfnWdfDpcGetParentObject;
    PFN_WDFDPCWDMGETDPC                                       pfnWdfDpcWdmGetDpc;
    PFN_WDFDRIVERCREATE                                       pfnWdfDriverCreate;
    PFN_WDFDRIVERGETREGISTRYPATH                              pfnWdfDriverGetRegistryPath;
    PFN_WDFDRIVERWDMGETDRIVEROBJECT                           pfnWdfDriverWdmGetDriverObject;
    PFN_WDFDRIVEROPENPARAMETERSREGISTRYKEY                    pfnWdfDriverOpenParametersRegistryKey;
    PFN_WDFWDMDRIVERGETWDFDRIVERHANDLE                        pfnWdfWdmDriverGetWdfDriverHandle;
    PFN_WDFDRIVERREGISTERTRACEINFO                            pfnWdfDriverRegisterTraceInfo;
    PFN_WDFDRIVERRETRIEVEVERSIONSTRING                        pfnWdfDriverRetrieveVersionString;
    PFN_WDFDRIVERISVERSIONAVAILABLE                           pfnWdfDriverIsVersionAvailable;
    PFN_WDFFDOINITWDMGETPHYSICALDEVICE                        pfnWdfFdoInitWdmGetPhysicalDevice;
    PFN_WDFFDOINITOPENREGISTRYKEY                             pfnWdfFdoInitOpenRegistryKey;
    PFN_WDFFDOINITQUERYPROPERTY                               pfnWdfFdoInitQueryProperty;
    PFN_WDFFDOINITALLOCANDQUERYPROPERTY                       pfnWdfFdoInitAllocAndQueryProperty;
    PFN_WDFFDOINITSETEVENTCALLBACKS                           pfnWdfFdoInitSetEventCallbacks;
    PFN_WDFFDOINITSETFILTER                                   pfnWdfFdoInitSetFilter;
    PFN_WDFFDOINITSETDEFAULTCHILDLISTCONFIG                   pfnWdfFdoInitSetDefaultChildListConfig;
    PFN_WDFFDOQUERYFORINTERFACE                               pfnWdfFdoQueryForInterface;
    PFN_WDFFDOGETDEFAULTCHILDLIST                             pfnWdfFdoGetDefaultChildList;
    PFN_WDFFDOADDSTATICCHILD                                  pfnWdfFdoAddStaticChild;
    PFN_WDFFDOLOCKSTATICCHILDLISTFORITERATION                 pfnWdfFdoLockStaticChildListForIteration;
    PFN_WDFFDORETRIEVENEXTSTATICCHILD                         pfnWdfFdoRetrieveNextStaticChild;
    PFN_WDFFDOUNLOCKSTATICCHILDLISTFROMITERATION              pfnWdfFdoUnlockStaticChildListFromIteration;
    PFN_WDFFILEOBJECTGETFILENAME                              pfnWdfFileObjectGetFileName;
    PFN_WDFFILEOBJECTGETFLAGS                                 pfnWdfFileObjectGetFlags;
    PFN_WDFFILEOBJECTGETDEVICE                                pfnWdfFileObjectGetDevice;
    PFN_WDFFILEOBJECTWDMGETFILEOBJECT                         pfnWdfFileObjectWdmGetFileObject;
    PFN_WDFINTERRUPTCREATE                                    pfnWdfInterruptCreate;
    PFN_WDFINTERRUPTQUEUEDPCFORISR                            pfnWdfInterruptQueueDpcForIsr;
    PFN_WDFINTERRUPTSYNCHRONIZE                               pfnWdfInterruptSynchronize;
    PFN_WDFINTERRUPTACQUIRELOCK                               pfnWdfInterruptAcquireLock;
    PFN_WDFINTERRUPTRELEASELOCK                               pfnWdfInterruptReleaseLock;
    PFN_WDFINTERRUPTENABLE                                    pfnWdfInterruptEnable;
    PFN_WDFINTERRUPTDISABLE                                   pfnWdfInterruptDisable;
    PFN_WDFINTERRUPTWDMGETINTERRUPT                           pfnWdfInterruptWdmGetInterrupt;
    PFN_WDFINTERRUPTGETINFO                                   pfnWdfInterruptGetInfo;
    PFN_WDFINTERRUPTSETPOLICY                                 pfnWdfInterruptSetPolicy;
    PFN_WDFINTERRUPTGETDEVICE                                 pfnWdfInterruptGetDevice;
    PFN_WDFIOQUEUECREATE                                      pfnWdfIoQueueCreate;
    PFN_WDFIOQUEUEGETSTATE                                    pfnWdfIoQueueGetState;
    PFN_WDFIOQUEUESTART                                       pfnWdfIoQueueStart;
    PFN_WDFIOQUEUESTOP                                        pfnWdfIoQueueStop;
    PFN_WDFIOQUEUESTOPSYNCHRONOUSLY                           pfnWdfIoQueueStopSynchronously;
    PFN_WDFIOQUEUEGETDEVICE                                   pfnWdfIoQueueGetDevice;
    PFN_WDFIOQUEUERETRIEVENEXTREQUEST                         pfnWdfIoQueueRetrieveNextRequest;
    PFN_WDFIOQUEUERETRIEVEREQUESTBYFILEOBJECT                 pfnWdfIoQueueRetrieveRequestByFileObject;
    PFN_WDFIOQUEUEFINDREQUEST                                 pfnWdfIoQueueFindRequest;
    PFN_WDFIOQUEUERETRIEVEFOUNDREQUEST                        pfnWdfIoQueueRetrieveFoundRequest;
    PFN_WDFIOQUEUEDRAINSYNCHRONOUSLY                          pfnWdfIoQueueDrainSynchronously;
    PFN_WDFIOQUEUEDRAIN                                       pfnWdfIoQueueDrain;
    PFN_WDFIOQUEUEPURGESYNCHRONOUSLY                          pfnWdfIoQueuePurgeSynchronously;
    PFN_WDFIOQUEUEPURGE                                       pfnWdfIoQueuePurge;
    PFN_WDFIOQUEUEREADYNOTIFY                                 pfnWdfIoQueueReadyNotify;
    PFN_WDFIOTARGETCREATE                                     pfnWdfIoTargetCreate;
    PFN_WDFIOTARGETOPEN                                       pfnWdfIoTargetOpen;
    PFN_WDFIOTARGETCLOSEFORQUERYREMOVE                        pfnWdfIoTargetCloseForQueryRemove;
    PFN_WDFIOTARGETCLOSE                                      pfnWdfIoTargetClose;
    PFN_WDFIOTARGETSTART                                      pfnWdfIoTargetStart;
    PFN_WDFIOTARGETSTOP                                       pfnWdfIoTargetStop;
    PFN_WDFIOTARGETGETSTATE                                   pfnWdfIoTargetGetState;
    PFN_WDFIOTARGETGETDEVICE                                  pfnWdfIoTargetGetDevice;
    PFN_WDFIOTARGETQUERYTARGETPROPERTY                        pfnWdfIoTargetQueryTargetProperty;
    PFN_WDFIOTARGETALLOCANDQUERYTARGETPROPERTY                pfnWdfIoTargetAllocAndQueryTargetProperty;
    PFN_WDFIOTARGETQUERYFORINTERFACE                          pfnWdfIoTargetQueryForInterface;
    PFN_WDFIOTARGETWDMGETTARGETDEVICEOBJECT                   pfnWdfIoTargetWdmGetTargetDeviceObject;
    PFN_WDFIOTARGETWDMGETTARGETPHYSICALDEVICE                 pfnWdfIoTargetWdmGetTargetPhysicalDevice;
    PFN_WDFIOTARGETWDMGETTARGETFILEOBJECT                     pfnWdfIoTargetWdmGetTargetFileObject;
    PFN_WDFIOTARGETWDMGETTARGETFILEHANDLE                     pfnWdfIoTargetWdmGetTargetFileHandle;
    PFN_WDFIOTARGETSENDREADSYNCHRONOUSLY                      pfnWdfIoTargetSendReadSynchronously;
    PFN_WDFIOTARGETFORMATREQUESTFORREAD                       pfnWdfIoTargetFormatRequestForRead;
    PFN_WDFIOTARGETSENDWRITESYNCHRONOUSLY                     pfnWdfIoTargetSendWriteSynchronously;
    PFN_WDFIOTARGETFORMATREQUESTFORWRITE                      pfnWdfIoTargetFormatRequestForWrite;
    PFN_WDFIOTARGETSENDIOCTLSYNCHRONOUSLY                     pfnWdfIoTargetSendIoctlSynchronously;
    PFN_WDFIOTARGETFORMATREQUESTFORIOCTL                      pfnWdfIoTargetFormatRequestForIoctl;
    PFN_WDFIOTARGETSENDINTERNALIOCTLSYNCHRONOUSLY             pfnWdfIoTargetSendInternalIoctlSynchronously;
    PFN_WDFIOTARGETFORMATREQUESTFORINTERNALIOCTL              pfnWdfIoTargetFormatRequestForInternalIoctl;
    PFN_WDFIOTARGETSENDINTERNALIOCTLOTHERSSYNCHRONOUSLY       pfnWdfIoTargetSendInternalIoctlOthersSynchronously;
    PFN_WDFIOTARGETFORMATREQUESTFORINTERNALIOCTLOTHERS        pfnWdfIoTargetFormatRequestForInternalIoctlOthers;
    PFN_WDFMEMORYCREATE                                       pfnWdfMemoryCreate;
    PFN_WDFMEMORYCREATEPREALLOCATED                           pfnWdfMemoryCreatePreallocated;
    PFN_WDFMEMORYGETBUFFER                                    pfnWdfMemoryGetBuffer;
    PFN_WDFMEMORYASSIGNBUFFER                                 pfnWdfMemoryAssignBuffer;
    PFN_WDFMEMORYCOPYTOBUFFER                                 pfnWdfMemoryCopyToBuffer;
    PFN_WDFMEMORYCOPYFROMBUFFER                               pfnWdfMemoryCopyFromBuffer;
    PFN_WDFLOOKASIDELISTCREATE                                pfnWdfLookasideListCreate;
    PFN_WDFMEMORYCREATEFROMLOOKASIDE                          pfnWdfMemoryCreateFromLookaside;
    PFN_WDFDEVICEMINIPORTCREATE                               pfnWdfDeviceMiniportCreate;
    PFN_WDFDRIVERMINIPORTUNLOAD                               pfnWdfDriverMiniportUnload;
    PFN_WDFOBJECTGETTYPEDCONTEXTWORKER                        pfnWdfObjectGetTypedContextWorker;
    PFN_WDFOBJECTALLOCATECONTEXT                              pfnWdfObjectAllocateContext;
    PFN_WDFOBJECTCONTEXTGETOBJECT                             pfnWdfObjectContextGetObject;
    PFN_WDFOBJECTREFERENCEACTUAL                              pfnWdfObjectReferenceActual;
    PFN_WDFOBJECTDEREFERENCEACTUAL                            pfnWdfObjectDereferenceActual;
    PFN_WDFOBJECTCREATE                                       pfnWdfObjectCreate;
    PFN_WDFOBJECTDELETE                                       pfnWdfObjectDelete;
    PFN_WDFOBJECTQUERY                                        pfnWdfObjectQuery;
    PFN_WDFPDOINITALLOCATE                                    pfnWdfPdoInitAllocate;
    PFN_WDFPDOINITSETEVENTCALLBACKS                           pfnWdfPdoInitSetEventCallbacks;
    PFN_WDFPDOINITASSIGNDEVICEID                              pfnWdfPdoInitAssignDeviceID;
    PFN_WDFPDOINITASSIGNINSTANCEID                            pfnWdfPdoInitAssignInstanceID;
    PFN_WDFPDOINITADDHARDWAREID                               pfnWdfPdoInitAddHardwareID;
    PFN_WDFPDOINITADDCOMPATIBLEID                             pfnWdfPdoInitAddCompatibleID;
    PFN_WDFPDOINITADDDEVICETEXT                               pfnWdfPdoInitAddDeviceText;
    PFN_WDFPDOINITSETDEFAULTLOCALE                            pfnWdfPdoInitSetDefaultLocale;
    PFN_WDFPDOINITASSIGNRAWDEVICE                             pfnWdfPdoInitAssignRawDevice;
    PFN_WDFPDOMARKMISSING                                     pfnWdfPdoMarkMissing;
    PFN_WDFPDOREQUESTEJECT                                    pfnWdfPdoRequestEject;
    PFN_WDFPDOGETPARENT                                       pfnWdfPdoGetParent;
    PFN_WDFPDORETRIEVEIDENTIFICATIONDESCRIPTION               pfnWdfPdoRetrieveIdentificationDescription;
    PFN_WDFPDORETRIEVEADDRESSDESCRIPTION                      pfnWdfPdoRetrieveAddressDescription;
    PFN_WDFPDOUPDATEADDRESSDESCRIPTION                        pfnWdfPdoUpdateAddressDescription;
    PFN_WDFPDOADDEJECTIONRELATIONSPHYSICALDEVICE              pfnWdfPdoAddEjectionRelationsPhysicalDevice;
    PFN_WDFPDOREMOVEEJECTIONRELATIONSPHYSICALDEVICE           pfnWdfPdoRemoveEjectionRelationsPhysicalDevice;
    PFN_WDFPDOCLEAREJECTIONRELATIONSDEVICES                   pfnWdfPdoClearEjectionRelationsDevices;
    PFN_WDFDEVICEADDQUERYINTERFACE                            pfnWdfDeviceAddQueryInterface;
    PFN_WDFREGISTRYOPENKEY                                    pfnWdfRegistryOpenKey;
    PFN_WDFREGISTRYCREATEKEY                                  pfnWdfRegistryCreateKey;
    PFN_WDFREGISTRYCLOSE                                      pfnWdfRegistryClose;
    PFN_WDFREGISTRYWDMGETHANDLE                               pfnWdfRegistryWdmGetHandle;
    PFN_WDFREGISTRYREMOVEKEY                                  pfnWdfRegistryRemoveKey;
    PFN_WDFREGISTRYREMOVEVALUE                                pfnWdfRegistryRemoveValue;
    PFN_WDFREGISTRYQUERYVALUE                                 pfnWdfRegistryQueryValue;
    PFN_WDFREGISTRYQUERYMEMORY                                pfnWdfRegistryQueryMemory;
    PFN_WDFREGISTRYQUERYMULTISTRING                           pfnWdfRegistryQueryMultiString;
    PFN_WDFREGISTRYQUERYUNICODESTRING                         pfnWdfRegistryQueryUnicodeString;
    PFN_WDFREGISTRYQUERYSTRING                                pfnWdfRegistryQueryString;
    PFN_WDFREGISTRYQUERYULONG                                 pfnWdfRegistryQueryULong;
    PFN_WDFREGISTRYASSIGNVALUE                                pfnWdfRegistryAssignValue;
    PFN_WDFREGISTRYASSIGNMEMORY                               pfnWdfRegistryAssignMemory;
    PFN_WDFREGISTRYASSIGNMULTISTRING                          pfnWdfRegistryAssignMultiString;
    PFN_WDFREGISTRYASSIGNUNICODESTRING                        pfnWdfRegistryAssignUnicodeString;
    PFN_WDFREGISTRYASSIGNSTRING                               pfnWdfRegistryAssignString;
    PFN_WDFREGISTRYASSIGNULONG                                pfnWdfRegistryAssignULong;
    PFN_WDFREQUESTCREATE                                      pfnWdfRequestCreate;
    PFN_WDFREQUESTCREATEFROMIRP                               pfnWdfRequestCreateFromIrp;
    PFN_WDFREQUESTREUSE                                       pfnWdfRequestReuse;
    PFN_WDFREQUESTCHANGETARGET                                pfnWdfRequestChangeTarget;
    PFN_WDFREQUESTFORMATREQUESTUSINGCURRENTTYPE               pfnWdfRequestFormatRequestUsingCurrentType;
    PFN_WDFREQUESTWDMFORMATUSINGSTACKLOCATION                 pfnWdfRequestWdmFormatUsingStackLocation;
    PFN_WDFREQUESTSEND                                        pfnWdfRequestSend;
    PFN_WDFREQUESTGETSTATUS                                   pfnWdfRequestGetStatus;
    PFN_WDFREQUESTMARKCANCELABLE                              pfnWdfRequestMarkCancelable;
    PFN_WDFREQUESTUNMARKCANCELABLE                            pfnWdfRequestUnmarkCancelable;
    PFN_WDFREQUESTISCANCELED                                  pfnWdfRequestIsCanceled;
    PFN_WDFREQUESTCANCELSENTREQUEST                           pfnWdfRequestCancelSentRequest;
    PFN_WDFREQUESTISFROM32BITPROCESS                          pfnWdfRequestIsFrom32BitProcess;
    PFN_WDFREQUESTSETCOMPLETIONROUTINE                        pfnWdfRequestSetCompletionRoutine;
    PFN_WDFREQUESTGETCOMPLETIONPARAMS                         pfnWdfRequestGetCompletionParams;
    PFN_WDFREQUESTALLOCATETIMER                               pfnWdfRequestAllocateTimer;
    PFN_WDFREQUESTCOMPLETE                                    pfnWdfRequestComplete;
    PFN_WDFREQUESTCOMPLETEWITHPRIORITYBOOST                   pfnWdfRequestCompleteWithPriorityBoost;
    PFN_WDFREQUESTCOMPLETEWITHINFORMATION                     pfnWdfRequestCompleteWithInformation;
    PFN_WDFREQUESTGETPARAMETERS                               pfnWdfRequestGetParameters;
    PFN_WDFREQUESTRETRIEVEINPUTMEMORY                         pfnWdfRequestRetrieveInputMemory;
    PFN_WDFREQUESTRETRIEVEOUTPUTMEMORY                        pfnWdfRequestRetrieveOutputMemory;
    PFN_WDFREQUESTRETRIEVEINPUTBUFFER                         pfnWdfRequestRetrieveInputBuffer;
    PFN_WDFREQUESTRETRIEVEOUTPUTBUFFER                        pfnWdfRequestRetrieveOutputBuffer;
    PFN_WDFREQUESTRETRIEVEINPUTWDMMDL                         pfnWdfRequestRetrieveInputWdmMdl;
    PFN_WDFREQUESTRETRIEVEOUTPUTWDMMDL                        pfnWdfRequestRetrieveOutputWdmMdl;
    PFN_WDFREQUESTRETRIEVEUNSAFEUSERINPUTBUFFER               pfnWdfRequestRetrieveUnsafeUserInputBuffer;
    PFN_WDFREQUESTRETRIEVEUNSAFEUSEROUTPUTBUFFER              pfnWdfRequestRetrieveUnsafeUserOutputBuffer;
    PFN_WDFREQUESTSETINFORMATION                              pfnWdfRequestSetInformation;
    PFN_WDFREQUESTGETINFORMATION                              pfnWdfRequestGetInformation;
    PFN_WDFREQUESTGETFILEOBJECT                               pfnWdfRequestGetFileObject;
    PFN_WDFREQUESTPROBEANDLOCKUSERBUFFERFORREAD               pfnWdfRequestProbeAndLockUserBufferForRead;
    PFN_WDFREQUESTPROBEANDLOCKUSERBUFFERFORWRITE              pfnWdfRequestProbeAndLockUserBufferForWrite;
    PFN_WDFREQUESTGETREQUESTORMODE                            pfnWdfRequestGetRequestorMode;
    PFN_WDFREQUESTFORWARDTOIOQUEUE                            pfnWdfRequestForwardToIoQueue;
    PFN_WDFREQUESTGETIOQUEUE                                  pfnWdfRequestGetIoQueue;
    PFN_WDFREQUESTREQUEUE                                     pfnWdfRequestRequeue;
    PFN_WDFREQUESTSTOPACKNOWLEDGE                             pfnWdfRequestStopAcknowledge;
    PFN_WDFREQUESTWDMGETIRP                                   pfnWdfRequestWdmGetIrp;
    PFN_WDFIORESOURCEREQUIREMENTSLISTSETSLOTNUMBER            pfnWdfIoResourceRequirementsListSetSlotNumber;
    PFN_WDFIORESOURCEREQUIREMENTSLISTSETINTERFACETYPE         pfnWdfIoResourceRequirementsListSetInterfaceType;
    PFN_WDFIORESOURCEREQUIREMENTSLISTAPPENDIORESLIST          pfnWdfIoResourceRequirementsListAppendIoResList;
    PFN_WDFIORESOURCEREQUIREMENTSLISTINSERTIORESLIST          pfnWdfIoResourceRequirementsListInsertIoResList;
    PFN_WDFIORESOURCEREQUIREMENTSLISTGETCOUNT                 pfnWdfIoResourceRequirementsListGetCount;
    PFN_WDFIORESOURCEREQUIREMENTSLISTGETIORESLIST             pfnWdfIoResourceRequirementsListGetIoResList;
    PFN_WDFIORESOURCEREQUIREMENTSLISTREMOVE                   pfnWdfIoResourceRequirementsListRemove;
    PFN_WDFIORESOURCEREQUIREMENTSLISTREMOVEBYIORESLIST        pfnWdfIoResourceRequirementsListRemoveByIoResList;
    PFN_WDFIORESOURCELISTCREATE                               pfnWdfIoResourceListCreate;
    PFN_WDFIORESOURCELISTAPPENDDESCRIPTOR                     pfnWdfIoResourceListAppendDescriptor;
    PFN_WDFIORESOURCELISTINSERTDESCRIPTOR                     pfnWdfIoResourceListInsertDescriptor;
    PFN_WDFIORESOURCELISTUPDATEDESCRIPTOR                     pfnWdfIoResourceListUpdateDescriptor;
    PFN_WDFIORESOURCELISTGETCOUNT                             pfnWdfIoResourceListGetCount;
    PFN_WDFIORESOURCELISTGETDESCRIPTOR                        pfnWdfIoResourceListGetDescriptor;
    PFN_WDFIORESOURCELISTREMOVE                               pfnWdfIoResourceListRemove;
    PFN_WDFIORESOURCELISTREMOVEBYDESCRIPTOR                   pfnWdfIoResourceListRemoveByDescriptor;
    PFN_WDFCMRESOURCELISTAPPENDDESCRIPTOR                     pfnWdfCmResourceListAppendDescriptor;
    PFN_WDFCMRESOURCELISTINSERTDESCRIPTOR                     pfnWdfCmResourceListInsertDescriptor;
    PFN_WDFCMRESOURCELISTGETCOUNT                             pfnWdfCmResourceListGetCount;
    PFN_WDFCMRESOURCELISTGETDESCRIPTOR                        pfnWdfCmResourceListGetDescriptor;
    PFN_WDFCMRESOURCELISTREMOVE                               pfnWdfCmResourceListRemove;
    PFN_WDFCMRESOURCELISTREMOVEBYDESCRIPTOR                   pfnWdfCmResourceListRemoveByDescriptor;
    PFN_WDFSTRINGCREATE                                       pfnWdfStringCreate;
    PFN_WDFSTRINGGETUNICODESTRING                             pfnWdfStringGetUnicodeString;
    PFN_WDFOBJECTACQUIRELOCK                                  pfnWdfObjectAcquireLock;
    PFN_WDFOBJECTRELEASELOCK                                  pfnWdfObjectReleaseLock;
    PFN_WDFWAITLOCKCREATE                                     pfnWdfWaitLockCreate;
    PFN_WDFWAITLOCKACQUIRE                                    pfnWdfWaitLockAcquire;
    PFN_WDFWAITLOCKRELEASE                                    pfnWdfWaitLockRelease;
    PFN_WDFSPINLOCKCREATE                                     pfnWdfSpinLockCreate;
    PFN_WDFSPINLOCKACQUIRE                                    pfnWdfSpinLockAcquire;
    PFN_WDFSPINLOCKRELEASE                                    pfnWdfSpinLockRelease;
    PFN_WDFTIMERCREATE                                        pfnWdfTimerCreate;
    PFN_WDFTIMERSTART                                         pfnWdfTimerStart;
    PFN_WDFTIMERSTOP                                          pfnWdfTimerStop;
    PFN_WDFTIMERGETPARENTOBJECT                               pfnWdfTimerGetParentObject;
    PFN_WDFUSBTARGETDEVICECREATE                              pfnWdfUsbTargetDeviceCreate;
    PFN_WDFUSBTARGETDEVICERETRIEVEINFORMATION                 pfnWdfUsbTargetDeviceRetrieveInformation;
    PFN_WDFUSBTARGETDEVICEGETDEVICEDESCRIPTOR                 pfnWdfUsbTargetDeviceGetDeviceDescriptor;
    PFN_WDFUSBTARGETDEVICERETRIEVECONFIGDESCRIPTOR            pfnWdfUsbTargetDeviceRetrieveConfigDescriptor;
    PFN_WDFUSBTARGETDEVICEQUERYSTRING                         pfnWdfUsbTargetDeviceQueryString;
    PFN_WDFUSBTARGETDEVICEALLOCANDQUERYSTRING                 pfnWdfUsbTargetDeviceAllocAndQueryString;
    PFN_WDFUSBTARGETDEVICEFORMATREQUESTFORSTRING              pfnWdfUsbTargetDeviceFormatRequestForString;
    PFN_WDFUSBTARGETDEVICEGETNUMINTERFACES                    pfnWdfUsbTargetDeviceGetNumInterfaces;
    PFN_WDFUSBTARGETDEVICESELECTCONFIG                        pfnWdfUsbTargetDeviceSelectConfig;
    PFN_WDFUSBTARGETDEVICEWDMGETCONFIGURATIONHANDLE           pfnWdfUsbTargetDeviceWdmGetConfigurationHandle;
    PFN_WDFUSBTARGETDEVICERETRIEVECURRENTFRAMENUMBER          pfnWdfUsbTargetDeviceRetrieveCurrentFrameNumber;
    PFN_WDFUSBTARGETDEVICESENDCONTROLTRANSFERSYNCHRONOUSLY    pfnWdfUsbTargetDeviceSendControlTransferSynchronously;
    PFN_WDFUSBTARGETDEVICEFORMATREQUESTFORCONTROLTRANSFER     pfnWdfUsbTargetDeviceFormatRequestForControlTransfer;
    PFN_WDFUSBTARGETDEVICEISCONNECTEDSYNCHRONOUS              pfnWdfUsbTargetDeviceIsConnectedSynchronous;
    PFN_WDFUSBTARGETDEVICERESETPORTSYNCHRONOUSLY              pfnWdfUsbTargetDeviceResetPortSynchronously;
    PFN_WDFUSBTARGETDEVICECYCLEPORTSYNCHRONOUSLY              pfnWdfUsbTargetDeviceCyclePortSynchronously;
    PFN_WDFUSBTARGETDEVICEFORMATREQUESTFORCYCLEPORT           pfnWdfUsbTargetDeviceFormatRequestForCyclePort;
    PFN_WDFUSBTARGETDEVICESENDURBSYNCHRONOUSLY                pfnWdfUsbTargetDeviceSendUrbSynchronously;
    PFN_WDFUSBTARGETDEVICEFORMATREQUESTFORURB                 pfnWdfUsbTargetDeviceFormatRequestForUrb;
    PFN_WDFUSBTARGETPIPEGETINFORMATION                        pfnWdfUsbTargetPipeGetInformation;
    PFN_WDFUSBTARGETPIPEISINENDPOINT                          pfnWdfUsbTargetPipeIsInEndpoint;
    PFN_WDFUSBTARGETPIPEISOUTENDPOINT                         pfnWdfUsbTargetPipeIsOutEndpoint;
    PFN_WDFUSBTARGETPIPEGETTYPE                               pfnWdfUsbTargetPipeGetType;
    PFN_WDFUSBTARGETPIPESETNOMAXIMUMPACKETSIZECHECK           pfnWdfUsbTargetPipeSetNoMaximumPacketSizeCheck;
    PFN_WDFUSBTARGETPIPEWRITESYNCHRONOUSLY                    pfnWdfUsbTargetPipeWriteSynchronously;
    PFN_WDFUSBTARGETPIPEFORMATREQUESTFORWRITE                 pfnWdfUsbTargetPipeFormatRequestForWrite;
    PFN_WDFUSBTARGETPIPEREADSYNCHRONOUSLY                     pfnWdfUsbTargetPipeReadSynchronously;
    PFN_WDFUSBTARGETPIPEFORMATREQUESTFORREAD                  pfnWdfUsbTargetPipeFormatRequestForRead;
    PFN_WDFUSBTARGETPIPECONFIGCONTINUOUSREADER                pfnWdfUsbTargetPipeConfigContinuousReader;
    PFN_WDFUSBTARGETPIPEABORTSYNCHRONOUSLY                    pfnWdfUsbTargetPipeAbortSynchronously;
    PFN_WDFUSBTARGETPIPEFORMATREQUESTFORABORT                 pfnWdfUsbTargetPipeFormatRequestForAbort;
    PFN_WDFUSBTARGETPIPERESETSYNCHRONOUSLY                    pfnWdfUsbTargetPipeResetSynchronously;
    PFN_WDFUSBTARGETPIPEFORMATREQUESTFORRESET                 pfnWdfUsbTargetPipeFormatRequestForReset;
    PFN_WDFUSBTARGETPIPESENDURBSYNCHRONOUSLY                  pfnWdfUsbTargetPipeSendUrbSynchronously;
    PFN_WDFUSBTARGETPIPEFORMATREQUESTFORURB                   pfnWdfUsbTargetPipeFormatRequestForUrb;
    PFN_WDFUSBINTERFACEGETINTERFACENUMBER                     pfnWdfUsbInterfaceGetInterfaceNumber;
    PFN_WDFUSBINTERFACEGETNUMENDPOINTS                        pfnWdfUsbInterfaceGetNumEndpoints;
    PFN_WDFUSBINTERFACEGETDESCRIPTOR                          pfnWdfUsbInterfaceGetDescriptor;
    PFN_WDFUSBINTERFACESELECTSETTING                          pfnWdfUsbInterfaceSelectSetting;
    PFN_WDFUSBINTERFACEGETENDPOINTINFORMATION                 pfnWdfUsbInterfaceGetEndpointInformation;
    PFN_WDFUSBTARGETDEVICEGETINTERFACE                        pfnWdfUsbTargetDeviceGetInterface;
    PFN_WDFUSBINTERFACEGETCONFIGUREDSETTINGINDEX              pfnWdfUsbInterfaceGetConfiguredSettingIndex;
    PFN_WDFUSBINTERFACEGETNUMCONFIGUREDPIPES                  pfnWdfUsbInterfaceGetNumConfiguredPipes;
    PFN_WDFUSBINTERFACEGETCONFIGUREDPIPE                      pfnWdfUsbInterfaceGetConfiguredPipe;
    PFN_WDFUSBTARGETPIPEWDMGETPIPEHANDLE                      pfnWdfUsbTargetPipeWdmGetPipeHandle;
    PFN_WDFVERIFIERDBGBREAKPOINT                              pfnWdfVerifierDbgBreakPoint;
    PFN_WDFVERIFIERKEBUGCHECK                                 pfnWdfVerifierKeBugCheck;
    PFN_WDFWMIPROVIDERCREATE                                  pfnWdfWmiProviderCreate;
    PFN_WDFWMIPROVIDERGETDEVICE                               pfnWdfWmiProviderGetDevice;
    PFN_WDFWMIPROVIDERISENABLED                               pfnWdfWmiProviderIsEnabled;
    PFN_WDFWMIPROVIDERGETTRACINGHANDLE                        pfnWdfWmiProviderGetTracingHandle;
    PFN_WDFWMIINSTANCECREATE                                  pfnWdfWmiInstanceCreate;
    PFN_WDFWMIINSTANCEREGISTER                                pfnWdfWmiInstanceRegister;
    PFN_WDFWMIINSTANCEDEREGISTER                              pfnWdfWmiInstanceDeregister;
    PFN_WDFWMIINSTANCEGETDEVICE                               pfnWdfWmiInstanceGetDevice;
    PFN_WDFWMIINSTANCEGETPROVIDER                             pfnWdfWmiInstanceGetProvider;
    PFN_WDFWMIINSTANCEFIREEVENT                               pfnWdfWmiInstanceFireEvent;
    PFN_WDFWORKITEMCREATE                                     pfnWdfWorkItemCreate;
    PFN_WDFWORKITEMENQUEUE                                    pfnWdfWorkItemEnqueue;
    PFN_WDFWORKITEMGETPARENTOBJECT                            pfnWdfWorkItemGetParentObject;
    PFN_WDFWORKITEMFLUSH                                      pfnWdfWorkItemFlush;
};

struct _WDFFUNCTIONS_V101 {
    _WDFFUNCTIONS_V100                                        v100;
    PFN_WDFCOMMONBUFFERCREATEWITHCONFIG                       pfnWdfCommonBufferCreateWithConfig;
    PFN_WDFDMAENABLERGETFRAGMENTLENGTH                        pfnWdfDmaEnablerGetFragmentLength;
    PFN_WDFDMAENABLERWDMGETDMAADAPTER                         pfnWdfDmaEnablerWdmGetDmaAdapter;
};

struct _WDFFUNCTIONS_V105 {
    _WDFFUNCTIONS_V101                                        v101;
    PFN_WDFUSBINTERFACEGETNUMSETTINGS                         pfnWdfUsbInterfaceGetNumSettings;
};

struct _WDFFUNCTIONS_V109 {
    _WDFFUNCTIONS_V105                                        v105;
    PFN_WDFDEVICEREMOVEDEPENDENTUSAGEDEVICEOBJECT             pfnWdfDeviceRemoveDependentUsageDeviceObject;
    PFN_WDFDEVICEGETSYSTEMPOWERACTION                         pfnWdfDeviceGetSystemPowerAction;
    PFN_WDFINTERRUPTSETEXTENDEDPOLICY                         pfnWdfInterruptSetExtendedPolicy;
    PFN_WDFIOQUEUEASSIGNFORWARDPROGRESSPOLICY                 pfnWdfIoQueueAssignForwardProgressPolicy;
    PFN_WDFPDOINITASSIGNCONTAINERID                           pfnWdfPdoInitAssignContainerID;
    PFN_WDFPDOINITALLOWFORWARDINGREQUESTTOPARENT              pfnWdfPdoInitAllowForwardingRequestToParent;
    PFN_WDFREQUESTMARKCANCELABLEEX                            pfnWdfRequestMarkCancelableEx;
    PFN_WDFREQUESTISRESERVED                                  pfnWdfRequestIsReserved;
    PFN_WDFREQUESTFORWARDTOPARENTDEVICEIOQUEUE                pfnWdfRequestForwardToParentDeviceIoQueue;
};

struct _WDFFUNCTIONS_V111 {
    _WDFFUNCTIONS_V109                                        v109;
    PFN_WDFCXDEVICEINITALLOCATE                               pfnWdfCxDeviceInitAllocate;
    PFN_WDFCXDEVICEINITASSIGNWDMIRPPREPROCESSCALLBACK         pfnWdfCxDeviceInitAssignWdmIrpPreprocessCallback;
    PFN_WDFCXDEVICEINITSETIOINCALLERCONTEXTCALLBACK           pfnWdfCxDeviceInitSetIoInCallerContextCallback;
    PFN_WDFCXDEVICEINITSETREQUESTATTRIBUTES                   pfnWdfCxDeviceInitSetRequestAttributes;
    PFN_WDFCXDEVICEINITSETFILEOBJECTCONFIG                    pfnWdfCxDeviceInitSetFileObjectConfig;
    PFN_WDFDEVICEWDMDISPATCHIRP                               pfnWdfDeviceWdmDispatchIrp;
    PFN_WDFDEVICEWDMDISPATCHIRPTOIOQUEUE                      pfnWdfDeviceWdmDispatchIrpToIoQueue;
    PFN_WDFDEVICEINITSETREMOVELOCKOPTIONS                     pfnWdfDeviceInitSetRemoveLockOptions;
    PFN_WDFDEVICECONFIGUREWDMIRPDISPATCHCALLBACK              pfnWdfDeviceConfigureWdmIrpDispatchCallback;
    PFN_WDFDMAENABLERCONFIGURESYSTEMPROFILE                   pfnWdfDmaEnablerConfigureSystemProfile;
    PFN_WDFDMATRANSACTIONINITIALIZEUSINGOFFSET                pfnWdfDmaTransactionInitializeUsingOffset;
    PFN_WDFDMATRANSACTIONGETTRANSFERINFO                      pfnWdfDmaTransactionGetTransferInfo;
    PFN_WDFDMATRANSACTIONSETCHANNELCONFIGURATIONCALLBACK      pfnWdfDmaTransactionSetChannelConfigurationCallback;
    PFN_WDFDMATRANSACTIONSETTRANSFERCOMPLETECALLBACK          pfnWdfDmaTransactionSetTransferCompleteCallback;
    PFN_WDFDMATRANSACTIONSETIMMEDIATEEXECUTION                pfnWdfDmaTransactionSetImmediateExecution;
    PFN_WDFDMATRANSACTIONALLOCATERESOURCES                    pfnWdfDmaTransactionAllocateResources;
    PFN_WDFDMATRANSACTIONSETDEVICEADDRESSOFFSET               pfnWdfDmaTransactionSetDeviceAddressOffset;
    PFN_WDFDMATRANSACTIONFREERESOURCES                        pfnWdfDmaTransactionFreeResources;
    PFN_WDFDMATRANSACTIONCANCEL                               pfnWdfDmaTransactionCancel;
    PFN_WDFDMATRANSACTIONWDMGETTRANSFERCONTEXT                pfnWdfDmaTransactionWdmGetTransferContext;
    PFN_WDFINTERRUPTQUEUEWORKITEMFORISR                       pfnWdfInterruptQueueWorkItemForIsr;
    PFN_WDFINTERRUPTTRYTOACQUIRELOCK                          pfnWdfInterruptTryToAcquireLock;
    PFN_WDFIOQUEUESTOPANDPURGE                                pfnWdfIoQueueStopAndPurge;
    PFN_WDFIOQUEUESTOPANDPURGESYNCHRONOUSLY                   pfnWdfIoQueueStopAndPurgeSynchronously;
    PFN_WDFIOTARGETPURGE                                      pfnWdfIoTargetPurge;
    PFN_WDFUSBTARGETDEVICECREATEWITHPARAMETERS                pfnWdfUsbTargetDeviceCreateWithParameters;
    PFN_WDFUSBTARGETDEVICEQUERYUSBCAPABILITY                  pfnWdfUsbTargetDeviceQueryUsbCapability;
    PFN_WDFUSBTARGETDEVICECREATEURB                           pfnWdfUsbTargetDeviceCreateUrb;
    PFN_WDFUSBTARGETDEVICECREATEISOCHURB                      pfnWdfUsbTargetDeviceCreateIsochUrb;
    PFN_WDFDEVICEWDMASSIGNPOWERFRAMEWORKSETTINGS              pfnWdfDeviceWdmAssignPowerFrameworkSettings;
    PFN_WDFDMATRANSACTIONSTOPSYSTEMTRANSFER                   pfnWdfDmaTransactionStopSystemTransfer;
    PFN_WDFCXVERIFIERKEBUGCHECK                               pfnWdfCxVerifierKeBugCheck;
    PFN_WDFINTERRUPTREPORTACTIVE                              pfnWdfInterruptReportActive;
    PFN_WDFINTERRUPTREPORTINACTIVE                            pfnWdfInterruptReportInactive;
    PFN_WDFDEVICEINITSETRELEASEHARDWAREORDERONFAILURE         pfnWdfDeviceInitSetReleaseHardwareOrderOnFailure;
    PFN_WDFGETTRIAGEINFO                                      pfnWdfGetTriageInfo;
};

struct _WDFFUNCTIONS_V113 {
    _WDFFUNCTIONS_V111                                        v111;
    PFN_WDFDEVICEINITSETIOTYPEEX                              pfnWdfDeviceInitSetIoTypeEx;
    PFN_WDFDEVICEQUERYPROPERTYEX                              pfnWdfDeviceQueryPropertyEx;
    PFN_WDFDEVICEALLOCANDQUERYPROPERTYEX                      pfnWdfDeviceAllocAndQueryPropertyEx;
    PFN_WDFDEVICEASSIGNPROPERTY                               pfnWdfDeviceAssignProperty;
    PFN_WDFFDOINITQUERYPROPERTYEX                             pfnWdfFdoInitQueryPropertyEx;
    PFN_WDFFDOINITALLOCANDQUERYPROPERTYEX                     pfnWdfFdoInitAllocAndQueryPropertyEx;
};

struct _WDFFUNCTIONS_V115 {
    _WDFFUNCTIONS_V113                                        v113;
    PFN_WDFDEVICESTOPIDLEACTUAL                               pfnWdfDeviceStopIdleActual;
    PFN_WDFDEVICERESUMEIDLEACTUAL                             pfnWdfDeviceResumeIdleActual;
    PFN_WDFDEVICEGETSELFIOTARGET                              pfnWdfDeviceGetSelfIoTarget;
    PFN_WDFDEVICEINITALLOWSELFIOTARGET                        pfnWdfDeviceInitAllowSelfIoTarget;
    PFN_WDFIOTARGETSELFASSIGNDEFAULTIOQUEUE                   pfnWdfIoTargetSelfAssignDefaultIoQueue;
    PFN_WDFDEVICEOPENDEVICEMAPKEY                             pfnWdfDeviceOpenDevicemapKey;
};

struct _WDFFUNCTIONS_V119 {
    _WDFFUNCTIONS_V115                                        v115;
    PFN_WDFDMATRANSACTIONSETSINGLETRANSFERREQUIREMENT         pfnWdfDmaTransactionSetSingleTransferRequirement;
    PFN_WDFCXDEVICEINITSETPNPPOWEREVENTCALLBACKS              pfnWdfCxDeviceInitSetPnpPowerEventCallbacks;
};

struct _WDFFUNCTIONS_V121 {
    _WDFFUNCTIONS_V119                                        v119;
    PFN_WDFFILEOBJECTGETINITIATORPROCESSID                    pfnWdfFileObjectGetInitiatorProcessId;
    PFN_WDFREQUESTGETREQUESTORPROCESSID                       pfnWdfRequestGetRequestorProcessId;
};

struct _WDFFUNCTIONS_V123 {
    _WDFFUNCTIONS_V121                                        v121;
    PFN_WDFDEVICERETRIEVECOMPANIONTARGET                      pfnWdfDeviceRetrieveCompanionTarget;
    PFN_WDFCOMPANIONTARGETSENDTASKSYNCHRONOUSLY               pfnWdfCompanionTargetSendTaskSynchronously;
    PFN_WDFCOMPANIONTARGETWDMGETCOMPANIONPROCESS              pfnWdfCompanionTargetWdmGetCompanionProcess;
};

struct _WDFFUNCTIONS_V125 {
    _WDFFUNCTIONS_V123                                        v123;
    PFN_WDFDRIVEROPENPERSISTENTSTATEREGISTRYKEY               pfnWdfDriverOpenPersistentStateRegistryKey;
    PFN_WDFDRIVERERRORREPORTAPIMISSING                        pfnWdfDriverErrorReportApiMissing;
};

#define FILE_DEVICE_8042_PORT           0x00000027
#define FILE_DEVICE_ACPI                0x00000032
#define FILE_DEVICE_BATTERY             0x00000029
#define FILE_DEVICE_BEEP                0x00000001
#define FILE_DEVICE_BUS_EXTENDER        0x0000002a
#define FILE_DEVICE_CD_ROM              0x00000002
#define FILE_DEVICE_CD_ROM_FILE_SYSTEM  0x00000003
#define FILE_DEVICE_CHANGER             0x00000030
#define FILE_DEVICE_CONTROLLER          0x00000004
#define FILE_DEVICE_DATALINK            0x00000005
#define FILE_DEVICE_DFS                 0x00000006
#define FILE_DEVICE_DFS_FILE_SYSTEM     0x00000035
#define FILE_DEVICE_DFS_VOLUME          0x00000036
#define FILE_DEVICE_DISK                0x00000007
#define FILE_DEVICE_DISK_FILE_SYSTEM    0x00000008
#define FILE_DEVICE_DVD                 0x00000033
#define FILE_DEVICE_FILE_SYSTEM         0x00000009
#define FILE_DEVICE_FIPS                0x0000003a
#define FILE_DEVICE_FULLSCREEN_VIDEO    0x00000034
#define FILE_DEVICE_INPORT_PORT         0x0000000a
#define FILE_DEVICE_KEYBOARD            0x0000000b
#define FILE_DEVICE_KS                  0x0000002f
#define FILE_DEVICE_KSEC                0x00000039
#define FILE_DEVICE_MAILSLOT            0x0000000c
#define FILE_DEVICE_MASS_STORAGE        0x0000002d
#define FILE_DEVICE_MIDI_IN             0x0000000d
#define FILE_DEVICE_MIDI_OUT            0x0000000e
#define FILE_DEVICE_MODEM               0x0000002b
#define FILE_DEVICE_MOUSE               0x0000000f
#define FILE_DEVICE_MULTI_UNC_PROVIDER  0x00000010
#define FILE_DEVICE_NAMED_PIPE          0x00000011
#define FILE_DEVICE_NETWORK             0x00000012
#define FILE_DEVICE_NETWORK_BROWSER     0x00000013
#define FILE_DEVICE_NETWORK_FILE_SYSTEM 0x00000014
#define FILE_DEVICE_NETWORK_REDIRECTOR  0x00000028
#define FILE_DEVICE_NULL                0x00000015
#define FILE_DEVICE_PARALLEL_PORT       0x00000016
#define FILE_DEVICE_PHYSICAL_NETCARD    0x00000017
#define FILE_DEVICE_PRINTER             0x00000018
#define FILE_DEVICE_SCANNER             0x00000019
#define FILE_DEVICE_SCREEN              0x0000001c
#define FILE_DEVICE_SERENUM             0x00000037
#define FILE_DEVICE_SERIAL_MOUSE_PORT   0x0000001a
#define FILE_DEVICE_SERIAL_PORT         0x0000001b
#define FILE_DEVICE_SMARTCARD           0x00000031
#define FILE_DEVICE_SMB                 0x0000002e
#define FILE_DEVICE_SOUND               0x0000001d
#define FILE_DEVICE_STREAMS             0x0000001e
#define FILE_DEVICE_TAPE                0x0000001f
#define FILE_DEVICE_TAPE_FILE_SYSTEM    0x00000020
#define FILE_DEVICE_TERMSRV             0x00000038
#define FILE_DEVICE_TRANSPORT           0x00000021
#define FILE_DEVICE_UNKNOWN             0x00000022
#define FILE_DEVICE_VDM                 0x0000002c
#define FILE_DEVICE_VIDEO               0x00000023
#define FILE_DEVICE_VIRTUAL_DISK        0x00000024
#define FILE_DEVICE_WAVE_IN             0x00000025
#define FILE_DEVICE_WAVE_OUT            0x00000026

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
  _In_      WDFDEVICE              Device,
  _In_      PWDF_IO_QUEUE_CONFIG   Config,
  _In_opt_  PWDF_OBJECT_ATTRIBUTES QueueAttributes,
  _Out_opt_ WDFQUEUE               *Queue
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
  _In_     PWDFDEVICE_INIT        DeviceInit,
  _In_     PWDF_FILEOBJECT_CONFIG FileObjectConfig,
  _In_opt_ PWDF_OBJECT_ATTRIBUTES FileObjectAttributes
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
  _In_      WDFREQUEST Request,
  _In_      size_t     MinimumRequiredSize,
  _Out_     PVOID      *Buffer,
  _Out_opt_ size_t     *Length
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
  _In_ WDFDEVICE                   Device,
  _In_ PWDF_QUERY_INTERFACE_CONFIG InterfaceConfig
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
  _In_  PWDF_WORKITEM_CONFIG   Config,
  _In_  PWDF_OBJECT_ATTRIBUTES Attributes,
  _Out_ WDFWORKITEM            *WorkItem
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
  _In_ WDFIOTARGET                IoTarget,
  _In_ PWDF_IO_TARGET_OPEN_PARAMS OpenParams
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
  _In_     WDFDEVICE              Device,
  _In_     PWDF_INTERRUPT_CONFIG  Configuration,
  _In_opt_ PWDF_OBJECT_ATTRIBUTES Attributes,
  _Out_    WDFINTERRUPT           *Interrupt
);
*/


/*
The WdfFdoInitSetDefaultChildListConfig method configures a bus driver's default child list.

VOID WdfFdoInitSetDefaultChildListConfig(
  _Inout_  PWDFDEVICE_INIT        DeviceInit,
  _In_     PWDF_CHILD_LIST_CONFIG Config,
  _In_opt_ PWDF_OBJECT_ATTRIBUTES DefaultChildListAttributes
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
  _In_ WDFREQUEST Request
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

typedef HANDLE WDFCHILDLIST;
typedef HANDLE WDFCOLLECTION;
typedef HANDLE WDFOBJECT;
typedef HANDLE WDFDMAENABLER;
typedef HANDLE WDFSTRING;
typedef HANDLE WDFIOTARGET;
typedef HANDLE WDFKEY;
typedef HANDLE WDFMEMORY;

typedef PVOID WDFDRIVER;
typedef PVOID WDFDEVICE;
typedef PVOID WDFCOMMONBUFFER;

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

typedef void (__fascall * EVT_WDF_DEVICE_POWER_POLICY_STATE_CHANGE_NOTIFICATION)(WDFDEVICE Device, PCWDF_DEVICE_POWER_POLICY_NOTIFICATION_DATA NotificationData);
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

// Stripped version of this structure so it fits most binaries out there
// NOTE : ADD _WDFFUNCTIONS FOR ALL VERSION
struct _WDFFUNCTIONS {
    NTSTATUS                      (__fastcall * pfnWdfChildListCreate)(__int64 pWdfComponentGlobals, __int64 Device, PWDF_CHILD_LIST_CONFIG Config, PWDF_OBJECT_ATTRIBUTES ChildListAttributes, WDFCHILDLIST ChildList);
    __int64                       (__fastcall * pfnWdfChildListGetDevice)(__int64 pWdfComponentGlobals, WDFCHILDLIST ChildList);
    __int64                       (__fastcall * pfnWdfChildListRetrievePdo)(__int64 pWdfComponentGlobals, WDFCHILDLIST ChildList, PWDF_CHILD_RETRIEVE_INFO RetrieveInfo);
    NTSTATUS                      (__fastcall * pfnWdfChildListRetrieveAddressDescription)(__int64 pWdfComponentGlobals, WDFCHILDLIST ChildList, PWDF_CHILD_IDENTIFICATION_DESCRIPTION_HEADER IdentificationDescription, PWDF_CHILD_ADDRESS_DESCRIPTION_HEADER AddressDescription);
    void                          (__fastcall * pfnWdfChildListBeginScan)(__int64 pWdfComponentGlobals, WDFCHILDLIST ChildList);
    void                          (__fastcall * pfnWdfChildListEndScan)(__int64 pWdfComponentGlobals, WDFCHILDLIST ChildList);
    void                          (__fastcall * pfnWdfChildListBeginIteration)(__int64 pWdfComponentGlobals, WDFCHILDLIST ChildList, PWDF_CHILD_LIST_ITERATOR Iterator);
    NTSTATUS                      (__fastcall * pfnWdfChildListRetrieveNextDevice)(__int64 pWdfComponentGlobals, WDFCHILDLIST ChildList, PWDF_CHILD_LIST_ITERATOR Iterator, WDFDEVICE *Device, PWDF_CHILD_RETRIEVE_INFO Info);
    NTSTATUS                      (__fastcall * pfnWdfChildListEndIteration)(__int64 pWdfComponentGlobals, WDFCHILDLIST ChildList, PWDF_CHILD_LIST_ITERATOR Iterator, __int64 Device, PWDF_CHILD_RETRIEVE_INFO Info);
    NTSTATUS                      (__fastcall * pfnWdfChildListAddOrUpdateChildDescriptionAsPresent)(__int64 pWdfComponentGlobals, WDFCHILDLIST ChildList, PWDF_CHILD_IDENTIFICATION_DESCRIPTION_HEADER IdentificationDescription, PWDF_CHILD_ADDRESS_DESCRIPTION_HEADER AddressDescription);
    NTSTATUS                      (__fastcall * pfnWdfChildListUpdateChildDescriptionAsMissing)(__int64 pWdfComponentGlobals, WDFCHILDLIST ChildList, PWDF_CHILD_IDENTIFICATION_DESCRIPTION_HEADER IdentificationDescription);
    NTSTATUS                      (__fastcall * pfnWdfChildListUpdateAllChildDescriptionsAsPresent)(__int64 pWdfComponentGlobals, WDFCHILDLIST ChildList);
    NTSTATUS                      (__fastcall * pfnWdfChildListRequestChildEject)(__int64 pWdfComponentGlobals, WDFCHILDLIST ChildList, PWDF_CHILD_IDENTIFICATION_DESCRIPTION_HEADER IdentificationDescription);
    NTSTATUS                      (__fastcall * pfnWdfCollectionCreate)(__int64 pWdfComponentGlobals, PWDF_OBJECT_ATTRIBUTES CollectionAttributes, WDFCOLLECTION *Collection);
    ULONG                         (__fastcall * pfnWdfCollectionGetCount)(__int64 pWdfComponentGlobals, WDFCOLLECTION Collection);
    NTSTATUS                      (__fastcall * pfnWdfCollectionAdd)(__int64 pWdfComponentGlobals, WDFCOLLECTION Collection, WDFOBJECT Object);
    NTSTATUS                      (__fastcall * pfnWdfCollectionRemove)(__int64 pWdfComponentGlobals, WDFCOLLECTION Collection, WDFOBJECT Item);
    void                          (__fastcall * pfnWdfCollectionRemoveItem)(__int64 pWdfComponentGlobals, WDFCOLLECTION Collection, ULONG Index);
    WDFOBJECT                     (__fastcall * pfnWdfCollectionGetItem)(__int64 pWdfComponentGlobals, WDFCOLLECTION Collection, ULONG Index);
    WDFOBJECT                     (__fastcall * pfnWdfCollectionGetFirstItem)(__int64 pWdfComponentGlobals, WDFCOLLECTION Collection);
    WDFOBJECT                     (__fastcall * pfnWdfCollectionGetLastItem)(__int64 pWdfComponentGlobals, WDFCOLLECTION Collection);
    NTSTATUS                      (__fastcall * pfnWdfCommonBufferCreate)(__int64 pWdfComponentGlobals, WDFDMAENABLER DmaEnabler, size_t Length, PWDF_OBJECT_ATTRIBUTES Attributes, WDFCOMMONBUFFER *CommonBuffer);
    PVOID                         (__fastcall * pfnWdfCommonBufferGetAlignedVirtualAddress)(__int64 pWdfComponentGlobals, WDFCOMMONBUFFER CommonBuffer);
    PHYSICAL_ADDRESS              (__fastcall * pfnWdfCommonBufferGetAlignedLogicalAddress)(__int64 pWdfComponentGlobals, WDFCOMMONBUFFER CommonBuffer);
    size_t                        (__fastcall * pfnWdfCommonBufferGetLength)(__int64 pWdfComponentGlobals, WDFCOMMONBUFFER CommonBuffer);
    NTSTATUS                      (__fastcall * pfnWdfControlDeviceInitAllocate)(__int64 pWdfComponentGlobals, WDFDRIVER Driver, const UNICODE_STRING *SDDLString); // 0xC8
    NTSTATUS                      (__fastcall * pfnWdfControlDeviceInitSetShutdownNotification)(__int64 pWdfComponentGlobals, PWDFDEVICE_INIT DeviceInit, PFN_WDF_DEVICE_SHUTDOWN_NOTIFICATION Notification, UCHAR Flags);
    void                          (__fastcall * pfnWdfControlFinishInitializing)(__int64 pWdfComponentGlobals, WDFDEVICE Device);
    void                          (__fastcall * pfnWdfDeviceGetDeviceState)(__int64 pWdfComponentGlobals, WDFDEVICE Device, PWDF_DEVICE_STATE DeviceState);
    void                          (__fastcall * pfnWdfDeviceSetDeviceState)(__int64 pWdfComponentGlobals, WDFDEVICE Device, PWDF_DEVICE_STATE DeviceState);
    WDFDEVICE                     (__fastcall * pfnWdfWdmDeviceGetWdfDeviceHandle)(__int64 pWdfComponentGlobals, PDEVICE_OBJECT DeviceObject);
    PDEVICE_OBJECT                (__fastcall * pfnWdfDeviceWdmGetDeviceObject)(__int64 pWdfComponentGlobals, WDFDEVICE Device);
    PDEVICE_OBJECT                (__fastcall * pfnWdfDeviceWdmGetAttachedDevice)(__int64 pWdfComponentGlobals, WDFDEVICE Device);
    PDEVICE_OBJECT                (__fastcall * pfnWdfDeviceWdmGetPhysicalDevice)(__int64 pWdfComponentGlobals, WDFDEVICE Device);
    NTSTATUS                      (__fastcall * pfnWdfDeviceWdmDispatchPreprocessedIrp)(__int64 pWdfComponentGlobals, WDFDEVICE Device, PIRP Irp);
    NTSTATUS                      (__fastcall * pfnWdfDeviceAddDependentUsageDeviceObject)(__int64 pWdfComponentGlobals, WDFDEVICE Device, PDEVICE_OBJECT DependentDevice);
    NTSTATUS                      (__fastcall * pfnWdfDeviceAddRemovalRelationsPhysicalDevice)(__int64 pWdfComponentGlobals, WDFDEVICE Device, PDEVICE_OBJECT PhysicalDevice);
    void                          (__fastcall * pfnWdfDeviceRemoveRemovalRelationsPhysicalDevice)(__int64 pWdfComponentGlobals, WDFDEVICE Device, PDEVICE_OBJECT PhysicalDevice);
    void                          (__fastcall * pfnWdfDeviceClearRemovalRelationsDevices)(__int64 pWdfComponentGlobals, WDFDEVICE Device);
    WDFDRIVER                     (__fastcall * pfnWdfDeviceGetDriver)(__int64 pWdfComponentGlobals, WDFDEVICE Device);
    NTSTATUS                      (__fastcall * pfnWdfDeviceRetrieveDeviceName)(__int64 pWdfComponentGlobals, WDFDEVICE Device, WDFSTRING String);
    NTSTATUS                      (__fastcall * pfnWdfDeviceAssignMofResourceName)(__int64 pWdfComponentGlobals, WDFDEVICE Device, const PUNICODE_STRING MofResourceName);
    WDFIOTARGET                   (__fastcall * pfnWdfDeviceGetIoTarget)(__int64 pWdfComponentGlobals, WDFDEVICE Device);
    WDF_DEVICE_PNP_STATE          (__fastcall * pfnWdfDeviceGetDevicePnpState)(__int64 pWdfComponentGlobals, WDFDEVICE Device);
    WDF_DEVICE_POWER_STATE        (__fastcall * pfnWdfDeviceGetDevicePowerState)(__int64 pWdfComponentGlobals, WDFDEVICE Device);
    WDF_DEVICE_POWER_POLICY_STATE (__fastcall * pfnWdfDeviceGetDevicePowerPolicyState)(__int64 pWdfComponentGlobals, WDFDEVICE Device);
    NTSTATUS                      (__fastcall * pfnWdfDeviceAssignS0IdleSettings)(__int64 pWdfComponentGlobals, WDFDEVICE Device, PWDF_DEVICE_POWER_POLICY_IDLE_SETTINGS Settings);
    NTSTATUS                      (__fastcall * pfnWdfDeviceAssignSxWakeSettings)(__int64 pWdfComponentGlobals, WDFDEVICE Device, PWDF_DEVICE_POWER_POLICY_WAKE_SETTINGS Settings);
    NTSTATUS                      (__fastcall * pfnWdfDeviceOpenRegistryKey)(__int64 pWdfComponentGlobals, WDFDEVICE Device, ULONG DeviceInstanceKeyType, ACCESS_MASK DesiredAccess, PWDF_OBJECT_ATTRIBUTES KeyAttributes, WDFKEY *Key);
    void                          (__fastcall * pfnWdfDeviceSetSpecialFileSupport)(__int64 pWdfComponentGlobals, WDFDEVICE Device, WDF_SPECIAL_FILE_TYPE FileType, BOOLEAN FileTypeIsSupported);
    void                          (__fastcall * pfnWdfDeviceSetCharacteristics)(__int64 pWdfComponentGlobals, WDFDEVICE Device, ULONG DeviceCharacteristics);
    ULONG                         (__fastcall * pfnWdfDeviceGetCharacteristics)(WDFDEVICE Device);
    ULONG                         (__fastcall * pfnWdfDeviceGetAlignmentRequirement)(__int64 pWdfComponentGlobals, WDFDEVICE Device);
    void                          (__fastcall * pfnWdfDeviceSetAlignmentRequirement)(__int64 pWdfComponentGlobals, WDFDEVICE Device, ULONG AlignmentRequirement);
    void                          (__fastcall * pfnWdfDeviceInitFree)(__int64 pWdfComponentGlobals, PWDFDEVICE_INIT DeviceInit);
    void                          (__fastcall * pfnWdfDeviceInitSetPnpPowerEventCallbacks)(__int64 pWdfComponentGlobals, PWDFDEVICE_INIT DeviceInit, PWDF_PNPPOWER_EVENT_CALLBACKS PnpPowerEventCallbacks);
    void                          (__fastcall * pfnWdfDeviceInitSetPowerPolicyEventCallbacks)(__int64 pWdfComponentGlobals, PWDFDEVICE_INIT DeviceInit, PWDF_POWER_POLICY_EVENT_CALLBACKS PowerPolicyEventCallbacks);
    void                          (__fastcall * pfnWdfDeviceInitSetPowerPolicyOwnership)(__int64 pWdfComponentGlobals, PWDFDEVICE_INIT DeviceInit, BOOLEAN IsPowerPolicyOwner);
    NTSTATUS                      (__fastcall * pfnWdfDeviceInitRegisterPnpStateChangeCallback)(__int64 pWdfComponentGlobals, PWDFDEVICE_INIT DeviceInit, WDF_DEVICE_PNP_STATE PnpState, PFN_WDF_DEVICE_PNP_STATE_CHANGE_NOTIFICATION EvtDevicePnpStateChange, ULONG CallbackTypes);
    NTSTATUS                      (__fastcall * pfnWdfDeviceInitRegisterPowerStateChangeCallback)(__int64 pWdfComponentGlobals, PWDFDEVICE_INIT DeviceInit, WDF_DEVICE_POWER_STATE PowerState, PFN_WDF_DEVICE_POWER_STATE_CHANGE_NOTIFICATION EvtDevicePowerStateChange, ULONG CallbackTypes);
    NTSTATUS                      (__fastcall * pfnWdfDeviceInitRegisterPowerPolicyStateChangeCallback)(__int64 pWdfComponentGlobals, PWDFDEVICE_INIT DeviceInit, WDF_DEVICE_POWER_POLICY_STATE PowerPolicyState, PFN_WDF_DEVICE_POWER_POLICY_STATE_CHANGE_NOTIFICATION EvtDevicePowerPolicyStateChange, ULONG CallbackTypes);
    void                          (__fastcall * pfnWdfDeviceInitSetIoType)(__int64 pWdfComponentGlobals, PWDFDEVICE_INIT DeviceInit, WDF_DEVICE_IO_TYPE IoType);
    void                          (__fastcall * pfnWdfDeviceInitSetExclusive)(__int64 pWdfComponentGlobals, PWDFDEVICE_INIT DeviceInit, BOOLEAN IsExclusive);
    void                          (__fastcall * pfnWdfDeviceInitSetPowerNotPageable)(__int64 pWdfComponentGlobals, PWDFDEVICE_INIT DeviceInit);
    void                          (__fastcall * pfnWdfDeviceInitSetPowerPageable)(__int64 pWdfComponentGlobals, PWDFDEVICE_INIT DeviceInit);
    void                          (__fastcall * pfnWdfDeviceInitSetPowerInrush)(__int64 pWdfComponentGlobals, PWDFDEVICE_INIT DeviceInit);
    void                          (__fastcall * pfnWdfDeviceInitSetDeviceType)(__int64 pWdfComponentGlobals, PWDFDEVICE_INIT DeviceInit, DEVICE_TYPE DeviceType);
    NTSTATUS                      (__fastcall * pfnWdfDeviceInitAssignName)(__int64 pWdfComponentGlobals, PWDFDEVICE_INIT DeviceInit, const PUNICODE_STRING DeviceName);
    NTSTATUS                      (__fastcall * pfnWdfDeviceInitAssignSDDLString)(__int64 pWdfComponentGlobals, PWDFDEVICE_INIT DeviceInit, PCUNICODE_STRING SDDLString); //0x220
    void                          (__fastcall * pfnWdfDeviceInitSetDeviceClass)(__int64 pWdfComponentGlobals, PWDFDEVICE_INIT DeviceInit, const GUID *DeviceClassGuid);
    void                          (__fastcall * pfnWdfDeviceInitSetCharacteristics)(__int64 pWdfComponentGlobals, PWDFDEVICE_INIT DeviceInit, ULONG DeviceCharacteristics, BOOLEAN OrInValues);
    void                          (__fastcall * pfnWdfDeviceInitSetFileObjectConfig)(__int64 pWdfComponentGlobals, PWDFDEVICE_INIT DeviceInit, PWDF_FILEOBJECT_CONFIG FileObjectConfig, PWDF_OBJECT_ATTRIBUTES FileObjectAttributes);
    void                          (__fastcall * pfnWdfDeviceInitSetRequestAttributes)(__int64 pWdfComponentGlobals, ...);
    void                          (__fastcall * pfnWdfDeviceInitAssignWdmIrpPreprocessCallback)(__int64 pWdfComponentGlobals, PWDFDEVICE_INIT DeviceInit, PWDF_OBJECT_ATTRIBUTES RequestAttributes); // 248h
    void                          (__fastcall * pfnWdfDeviceInitSetIoInCallerContextCallback)(__int64 pWdfComponentGlobals, PWDFDEVICE_INIT DeviceInit, PFN_WDF_IO_IN_CALLER_CONTEXT EvtIoInCallerContext); // 250h
    NTSTATUS                      (__fastcall * pfnWdfDeviceCreate)(__int64 pWdfComponentGlobals, PWDFDEVICE_INIT *DeviceInit, PWDF_OBJECT_ATTRIBUTES DeviceAttributes, WDFDEVICE *Device); // 258h
    void                          (__fastcall * pfnWdfDeviceSetStaticStopRemove)(__int64 pWdfComponentGlobals, WDFDEVICE Device, BOOLEAN Stoppable);
    NTSTATUS                      (__fastcall * pfnWdfDeviceCreateDeviceInterface)(__int64 pWdfComponentGlobals, WDFDEVICE Device, const GUID *InterfaceClassGUID, const PUNICODE_STRING ReferenceString); // 268h
    void                          (__fastcall * pfnWdfDeviceSetDeviceInterfaceState)(__int64 pWdfComponentGlobals, WDFDEVICE Device, const GUID *InterfaceClassGUID, const PUNICODE_STRING ReferenceString, BOOLEAN IsInterfaceEnabled);
    NTSTATUS                      (__fastcall * pfnWdfDeviceRetrieveDeviceInterfaceString)(__int64 pWdfComponentGlobals, WDFDEVICE Device, const GUID *InterfaceClassGUID, const PUNICODE_STRING ReferenceString, WDFSTRING String);
    NTSTATUS                      (__fastcall * pfnWdfDeviceCreateSymbolicLink)(__int64 pWdfComponentGlobals, WDFDEVICE Device, const PUNICODE_STRING SymbolicLinkName); // 0x280
    NTSTATUS                      (__fastcall * pfnWdfDeviceQueryProperty)(__int64 pWdfComponentGlobals, WDFDEVICE Device, DEVICE_REGISTRY_PROPERTY DeviceProperty, ULONG BufferLength, PVOID PropertyBuffer, PULONG ResultLength);
    NTSTATUS                      (__fastcall * pfnWdfDeviceAllocAndQueryProperty)(__int64 pWdfComponentGlobals, WDFDEVICE Device, DEVICE_REGISTRY_PROPERTY DeviceProperty, POOL_TYPE PoolType, PWDF_OBJECT_ATTRIBUTES PropertyMemoryAttributes, WDFMEMORY *PropertyMemory);
    void                          (__fastcall * pfnWdfDeviceSetPnpCapabilities)(__int64 pWdfComponentGlobals, WDFDEVICE Device, PWDF_DEVICE_PNP_CAPABILITIES PnpCapabilities);
    void                          (__fastcall * pfnWdfDeviceSetPowerCapabilities)(__int64 pWdfComponentGlobals, WDFDEVICE Device, PWDF_DEVICE_POWER_CAPABILITIES PowerCapabilities);
    void                          (__fastcall * pfnWdfDeviceSetBusInformationForChildren)(__int64 pWdfComponentGlobals, WDFDEVICE Device, PPNP_BUS_INFORMATION BusInformation);
    NTSTATUS                      (__fastcall * pfnWdfDeviceIndicateWakeStatus)(__int64 pWdfComponentGlobals, WDFDEVICE Device, NTSTATUS  WaitWakeStatus);
    void                          (__fastcall * pfnWdfDeviceSetFailed)(__int64 pWdfComponentGlobals, WDFDEVICE Device, WDF_DEVICE_FAILED_ACTION FailedAction);
    NTSTATUS                      (__fastcall * pfnWdfDeviceStopIdleNoTrack)(__int64 pWdfComponentGlobals, PWDF_OBJECT_ATTRIBUTES CollectionAttributes, WDFCOLLECTION * Collection);
    NTSTATUS                      (__fastcall * pfnWdfDeviceResumeIdleNoTrack)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfDeviceGetFileObject)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfDeviceEnqueueRequest)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfDeviceGetDefaultQueue)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfDeviceConfigureRequestDispatching)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfDmaEnablerCreate)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfDmaEnablerGetMaximumLength)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfDmaEnablerGetMaximumScatterGatherElements)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfDmaEnablerSetMaximumScatterGatherElements)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfDmaTransactionCreate)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfDmaTransactionInitialize)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfDmaTransactionInitializeUsingRequest)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfDmaTransactionExecute)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfDmaTransactionRelease)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfDmaTransactionDmaCompleted)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfDmaTransactionDmaCompletedWithLength)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfDmaTransactionDmaCompletedFinal)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfDmaTransactionGetBytesTransferred)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfDmaTransactionSetMaximumLength)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfDmaTransactionGetRequest)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfDmaTransactionGetCurrentDmaTransferLength)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfDmaTransactionGetDevice)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfDpcCreate)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfDpcEnqueue)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfDpcCancel)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfDpcGetParentObject)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfDpcWdmGetDpc)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfDriverCreate)(__int64 pWdfComponentGlobals, PDRIVER_OBJECT DriverObject, const UNICODE_STRING *RegistryPath, PWDF_OBJECT_ATTRIBUTES DriverAttributes, PWDF_DRIVER_CONFIG DriverConfig, __int64 *Driver);
    NTSTATUS                      (__fastcall * pfnWdfDriverGetRegistryPath)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfDriverWdmGetDriverObject)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfDriverOpenParametersRegistryKey)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfWdmDriverGetWdfDriverHandle)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfDriverRegisterTraceInfo)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfDriverRetrieveVersionString)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfDriverIsVersionAvailable)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfFdoInitWdmGetPhysicalDevice)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfFdoInitOpenRegistryKey)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfFdoInitQueryProperty)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfFdoInitAllocAndQueryProperty)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfFdoInitSetEventCallbacks)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfFdoInitSetFilter)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfFdoInitSetDefaultChildListConfig)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfFdoQueryForInterface)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfFdoGetDefaultChildList)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfFdoAddStaticChild)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfFdoLockStaticChildListForIteration)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfFdoRetrieveNextStaticChild)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfFdoUnlockStaticChildListFromIteration)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfFileObjectGetFileName)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfFileObjectGetFlags)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfFileObjectGetDevice)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfFileObjectWdmGetFileObject)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfInterruptCreate)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfInterruptQueueDpcForIsr)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfInterruptSynchronize)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfInterruptAcquireLock)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfInterruptReleaseLock)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfInterruptEnable)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfInterruptDisable)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfInterruptWdmGetInterrupt)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfInterruptGetInfo)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfInterruptSetPolicy)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfInterruptGetDevice)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfIoQueueCreate)(__int64 pWdfComponentGlobals, ...); // 4C0h
    NTSTATUS                      (__fastcall * pfnWdfIoQueueGetState)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfIoQueueStart)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfIoQueueStop)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfIoQueueStopSynchronously)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfIoQueueGetDevice)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfIoQueueRetrieveNextRequest)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfIoQueueRetrieveRequestByFileObject)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfIoQueueFindRequest)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfIoQueueRetrieveFoundRequest)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfIoQueueDrainSynchronously)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfIoQueueDrain)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfIoQueuePurgeSynchronously)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfIoQueuePurge)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfIoQueueReadyNotify)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfIoTargetCreate)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfIoTargetOpen)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfIoTargetCloseForQueryRemove)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfIoTargetClose)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfIoTargetStart)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfIoTargetStop)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfIoTargetGetState)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfIoTargetGetDevice)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfIoTargetQueryTargetProperty)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfIoTargetAllocAndQueryTargetProperty)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfIoTargetQueryForInterface)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfIoTargetWdmGetTargetDeviceObject)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfIoTargetWdmGetTargetPhysicalDevice)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfIoTargetWdmGetTargetFileObject)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfIoTargetWdmGetTargetFileHandle)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfIoTargetSendReadSynchronously)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfIoTargetFormatRequestForRead)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfIoTargetSendWriteSynchronously)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfIoTargetFormatRequestForWrite)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfIoTargetSendIoctlSynchronously)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfIoTargetFormatRequestForIoctl)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfIoTargetSendInternalIoctlSynchronously)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfIoTargetFormatRequestForInternalIoctl)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfIoTargetSendInternalIoctlOthersSynchronously)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfIoTargetFormatRequestForInternalIoctlOthers)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfMemoryCreate)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfMemoryCreatePreallocated)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfMemoryGetBuffer)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfMemoryAssignBuffer)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfMemoryCopyToBuffer)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfMemoryCopyFromBuffer)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfLookasideListCreate)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfMemoryCreateFromLookaside)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfDeviceMiniportCreate)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfDriverMiniportUnload)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfObjectGetTypedContextWorker)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfObjectAllocateContext)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfObjectContextGetObject)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfObjectReferenceActual)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfObjectDereferenceActual)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfObjectCreate)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfObjectDelete)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfObjectQuery)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfPdoInitAllocate)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfPdoInitSetEventCallbacks)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfPdoInitAssignDeviceID)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfPdoInitAssignInstanceID)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfPdoInitAddHardwareID)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfPdoInitAddCompatibleID)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfPdoInitAddDeviceText)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfPdoInitSetDefaultLocale)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfPdoInitAssignRawDevice)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfPdoMarkMissing)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfPdoRequestEject)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfPdoGetParent)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfPdoRetrieveIdentificationDescription)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfPdoRetrieveAddressDescription)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfPdoUpdateAddressDescription)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfPdoAddEjectionRelationsPhysicalDevice)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfPdoRemoveEjectionRelationsPhysicalDevice)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfPdoClearEjectionRelationsDevices)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfDeviceAddQueryInterface)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfRegistryOpenKey)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfRegistryCreateKey)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfRegistryClose)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfRegistryWdmGetHandle)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfRegistryRemoveKey)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfRegistryRemoveValue)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfRegistryQueryValue)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfRegistryQueryMemory)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfRegistryQueryMultiString)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfRegistryQueryUnicodeString)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfRegistryQueryString)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfRegistryQueryULong)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfRegistryAssignValue)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfRegistryAssignMemory)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfRegistryAssignMultiString)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfRegistryAssignUnicodeString)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfRegistryAssignString)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfRegistryAssignULong)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfRequestCreate)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfRequestCreateFromIrp)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfRequestReuse)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfRequestChangeTarget)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfRequestFormatRequestUsingCurrentType)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfRequestWdmFormatUsingStackLocation)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfRequestSend)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfRequestGetStatus)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfRequestMarkCancelable)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfRequestUnmarkCancelable)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfRequestIsCanceled)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfRequestCancelSentRequest)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfRequestIsFrom32BitProcess)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfRequestSetCompletionRoutine)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfRequestGetCompletionParams)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfRequestAllocateTimer)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfRequestComplete)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfRequestCompleteWithPriorityBoost)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfRequestCompleteWithInformation)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfRequestGetParameters)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfRequestRetrieveInputMemory)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfRequestRetrieveOutputMemory)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfRequestRetrieveInputBuffer)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfRequestRetrieveOutputBuffer)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfRequestRetrieveInputWdmMdl)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfRequestRetrieveOutputWdmMdl)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfRequestRetrieveUnsafeUserInputBuffer)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfRequestRetrieveUnsafeUserOutputBuffer)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfRequestSetInformation)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfRequestGetInformation)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfRequestGetFileObject)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfRequestProbeAndLockUserBufferForRead)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfRequestProbeAndLockUserBufferForWrite)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfRequestGetRequestorMode)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfRequestForwardToIoQueue)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfRequestGetIoQueue)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfRequestRequeue)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfRequestStopAcknowledge)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfRequestWdmGetIrp)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfIoResourceRequirementsListSetSlotNumber)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfIoResourceRequirementsListSetInterfaceType)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfIoResourceRequirementsListAppendIoResList)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfIoResourceRequirementsListInsertIoResList)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfIoResourceRequirementsListGetCount)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfIoResourceRequirementsListGetIoResList)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfIoResourceRequirementsListRemove)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfIoResourceRequirementsListRemoveByIoResList)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfIoResourceListCreate)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfIoResourceListAppendDescriptor)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfIoResourceListInsertDescriptor)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfIoResourceListUpdateDescriptor)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfIoResourceListGetCount)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfIoResourceListGetDescriptor)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfIoResourceListRemove)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfIoResourceListRemoveByDescriptor)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfCmResourceListAppendDescriptor)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfCmResourceListInsertDescriptor)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfCmResourceListGetCount)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfCmResourceListGetDescriptor)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfCmResourceListRemove)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfCmResourceListRemoveByDescriptor)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfStringCreate)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfStringGetUnicodeString)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfObjectAcquireLock)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfObjectReleaseLock)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfWaitLockCreate)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfWaitLockAcquire)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfWaitLockRelease)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfSpinLockCreate)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfSpinLockAcquire)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfSpinLockRelease)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfTimerCreate)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfTimerStart)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfTimerStop)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfTimerGetParentObject)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfUsbTargetDeviceCreate)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfUsbTargetDeviceRetrieveInformation)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfUsbTargetDeviceGetDeviceDescriptor)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfUsbTargetDeviceRetrieveConfigDescriptor)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfUsbTargetDeviceQueryString)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfUsbTargetDeviceAllocAndQueryString)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfUsbTargetDeviceFormatRequestForString)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfUsbTargetDeviceGetNumInterfaces)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfUsbTargetDeviceSelectConfig)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfUsbTargetDeviceWdmGetConfigurationHandle)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfUsbTargetDeviceRetrieveCurrentFrameNumber)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfUsbTargetDeviceSendControlTransferSynchronously)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfUsbTargetDeviceFormatRequestForControlTransfer)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfUsbTargetDeviceIsConnectedSynchronous)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfUsbTargetDeviceResetPortSynchronously)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfUsbTargetDeviceCyclePortSynchronously)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfUsbTargetDeviceFormatRequestForCyclePort)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfUsbTargetDeviceSendUrbSynchronously)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfUsbTargetDeviceFormatRequestForUrb)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfUsbTargetPipeGetInformation)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfUsbTargetPipeIsInEndpoint)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfUsbTargetPipeIsOutEndpoint)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfUsbTargetPipeGetType)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfUsbTargetPipeSetNoMaximumPacketSizeCheck)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfUsbTargetPipeWriteSynchronously)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfUsbTargetPipeFormatRequestForWrite)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfUsbTargetPipeReadSynchronously)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfUsbTargetPipeFormatRequestForRead)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfUsbTargetPipeConfigContinuousReader)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfUsbTargetPipeAbortSynchronously)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfUsbTargetPipeFormatRequestForAbort)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfUsbTargetPipeResetSynchronously)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfUsbTargetPipeFormatRequestForReset)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfUsbTargetPipeSendUrbSynchronously)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfUsbTargetPipeFormatRequestForUrb)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfUsbInterfaceGetInterfaceNumber)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfUsbInterfaceGetNumEndpoints)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfUsbInterfaceGetDescriptor)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfUsbInterfaceSelectSetting)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfUsbInterfaceGetEndpointInformation)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfUsbTargetDeviceGetInterface)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfUsbInterfaceGetConfiguredSettingIndex)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfUsbInterfaceGetNumConfiguredPipes)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfUsbInterfaceGetConfiguredPipe)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfUsbTargetPipeWdmGetPipeHandle)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfVerifierDbgBreakPoint)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfVerifierKeBugCheck)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfWmiProviderCreate)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfWmiProviderGetDevice)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfWmiProviderIsEnabled)(__int64 pWdfComponentGlobals, ...);
    NTSTATUS                      (__fastcall * pfnWdfWmiProviderGetTracingHandle)(__int64 pWdfComponentGlobals, ...);
};

// NOTE: ONCE _WDFFUNCTIONS IS ADDED FOR ALL VERSION, DECLARE THESE TYPEDEFS DYNAMICALLY
typedef _WDFFUNCTIONS WDFFUNCTIONS;
typedef _WDFFUNCTIONS * PWDFFUNCTIONS;


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
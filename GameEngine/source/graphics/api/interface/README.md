# RenderDevice
The **RenderDevice** object is the central interface in the API and the graphics hardware itself. The RenderDevice object is created using a **RenderDeviceDescriptor**. The *RenderDeviceDescriptor* object serves as a tempory data structure to hold the data nessecary for the *RenderDevice* to be created. The *RenderDevice* is created using the RenderDevice::Create() function. The user has further 

### API Selection
At creation of the **RenderDevice** the user is obliged to specify which GraphicsAPI to run the current render setup in. It is not possible to switch *Graphics API's* on an allocated *RenderDevice* object. If the user want's to switch *Graphics API's* he should either reload the application or recreate all resources using a *RenderDevice* with the new *Graphics API* selected.

Supported Graphics API's:
* VULKAN

### Debug mode
At creation of the *RenderDevice* the user must also specify a *DebugMode* that they want to use with this instance of the application. This is simular to Vulkan's validation layer, or D3D's debug layer. The parameter only specifies when the *DebugMode* should be active.

Supported parameters:
 * Always
 * Never
 * Debug Only

### Dealocation
The user has ownership over the pointer returned by the RenderDevice::Create() function, and should handle the dealocation. Note: The *RenderDevice* object should be the first 'Graphics' object to be allocated, and the last one to be delete (no living graphics resources should remain after dealocation).
```cpp
// Dealocate RenderDevice ptr
delete m_RenderDevice;
```

#ifndef udContext_h__
#define udContext_h__

//! @file udContext.h
//! The **udContext** object provides an interface to connect and communicate with a Euclideon udServer.
//! Once instantiated, the **udContext** can be passed into many udSDK functions to provide a context to operate within.

#include "udDLLExport.h"
#include "udError.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

//!
//! @struct udContext
//! Stores the internal state of the udSDK system
//!
struct udContext;

//!
//! This structure stores information about the current session
//!
struct udSessionInfo
{
  uint32_t isOffline; //!< Is not 0 if this is an offline session (dongle or other offline license)
  uint32_t isDomain; //!< If this is not 0 then this is a domain session (0 is non-domain session)
  uint32_t isPremium; //!< If this session will have access to premium features

  double expiresTimestamp; //!< The timestamp in UTC when the session will automatically end
  char displayName[1024]; //!< The null terminated display name of the user
};

//!
//! Establishes a connection to a Euclideon udServer and creates a new udContext object.
//!
//! @param ppContext A pointer to a location in which the new udContext object is stored.
//! @param pURL A URL to a Euclideon udServer to connect to.
//! @param pApplicationName The name of the application connecting to the Euclideon udServer.
//! @param pEmail The email address of the user connecting to the Euclideon udServer.
//! @param pPassword The password of the user connecting to the Euclideon udServer.
//! @return A udError value based on the result of the connection creation.
//! @note The application should call **udContext_Disconnect** with `ppContext` to destroy the object once it's no longer needed.
//!
UDSDKDLL_API enum udError udContext_Connect(struct udContext **ppContext, const char *pURL, const char *pApplicationName, const char *pEmail, const char *pPassword);

//!
//! Establishes a connection to a Euclideon udServer and creates a new udContext object.
//!
//! @param ppContext A pointer to a location in which the new udContext object is stored.
//! @param pServerURL A URL to a Euclideon udServer to connect to.
//! @param pApplicationName The name of the application connecting to the Euclideon udServer.
//! @return A udError value based on the result of the connection creation.
//! @note The application should call **udContext_Disconnect** with `ppContext` to destroy the object once it's no longer needed.
//! @warning This connect function is specific to the Emscripten/WebAssembly builds and will return udE_Unsupported on all other platforms
//!
UDSDKDLL_API enum udError udContext_ConnectFromDomain(struct udContext **ppContext, const char *pServerURL, const char *pApplicationName);

//!
//! Attempts to reestablish a connection to a Euclideon udServer (or run offline with an offline context) and creates a new udContext object.
//!
//! @param ppContext A pointer to a location in which the new udContext object is stored.
//! @param pURL A URL to a Euclideon udServer to connect to.
//! @param pApplicationName The name of the application connecting to the Euclideon udServer.
//! @param pUsername The username of the user connecting to the Euclideon udServer.
//! @param tryDongle If 0, the dongle will not be checked (on platforms that support dongles).
//! @return A udError value based on the result of the connection creation.
//! @warning The application should call udContext_Disconnect with `ppContext` to destroy the object once it's no longer needed.
//! @warning This function can crash with some debuggers attached when trying to read from a dongle. If debugging, ensure that tryDongle is set to 0.
//! @note This function will try use a session from a dongle first if that is supported; passing null to pURL, pApplicationName and pUsername will test the dongle but will otherwise be invalid
//!
UDSDKDLL_API enum udError udContext_TryResume(struct udContext **ppContext, const char *pURL, const char *pApplicationName, const char *pUsername, uint32_t tryDongle);

//!
//! Disconnects and destroys a udContext object that was created using **udContext_Connect**.
//!
//! @param ppContext A pointer to a udContext object which is to be disconnected and destroyed.
//! @param endSession Not 0 if the session will be ended (cannot be resumed)
//! @return A udError value based on the result of the connection destruction. 
//! @note The value of `ppContext` will be set to `NULL`.
//! @warning If other resources are still referencing this context this will return udE_NotAllowed until those resources are destroyed first
//!
UDSDKDLL_API enum udError udContext_Disconnect(struct udContext **ppContext, uint32_t endSession);

//!
//! Get the session information from an active udContext.
//!
//! @param pContext The udContext to get the session info for.
//! @param pInfo The preallocated structure to copy the info into.
//! @return A udError value based on the result of copying the structure
//!
UDSDKDLL_API enum udError udContext_GetSessionInfo(struct udContext *pContext, struct udSessionInfo *pInfo);

#ifdef __cplusplus
}
#endif

#endif // udContext_h__

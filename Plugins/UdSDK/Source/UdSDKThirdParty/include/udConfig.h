#ifndef udConfig_h__
#define udConfig_h__

//! @file udConfig.h
//! The **udConfig** functions all set global configuration options for the entire loaded shared library.

#include "udDLLExport.h"
#include "udError.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

//!
//! This function can be used to override the internal proxy auto-detection used by cURL.
//!
//! @param pProxyAddress This is a null terminated string, can include port number and protocol. `192.168.0.1`, `169.123.123.1:80`, `https://10.4.0.1:8081` or `https://proxy.example.com`. Setting this to either `NULL` or (empty string) `""` will reset to attempting auto-detection.
//! @return A udError value based on the result of forcing the proxy.
//! @note By default the proxy is attempted to be auto-detected. This fails in many proxy configurations.
//!
UDSDKDLL_API enum udError udConfig_ForceProxy(const char *pProxyAddress);

//!
//! This function is used in conjunction with `udConfig_ForceProxy` or the auto-detect proxy system to forward info from the user for their proxy details.
//!
//! @param pProxyUsername This is a null terminated string of the username of the user for the proxy.
//! @param pProxyPassword This is a null terminated string of the password of the user for the proxy.
//! @return A udError value based on the result of setting the proxy authentication.
//! @note This is usually called after another udSDK function returns `udE_ProxyAuthRequired`.
//!
UDSDKDLL_API enum udError udConfig_SetProxyAuth(const char *pProxyUsername, const char *pProxyPassword);

//!
//! Allows udSDK to connect to server with an unrecognized certificate authority, sometimes required for self-signed certificates or poorly configured proxies.
//!
//! @param ignore `0` if verification is to be processed, all other values if certificate verification should be skipped.
//! @return A udError value based on the result of ignoring the certificate verification.
//! @warning Ignoring certificate verification is very high risk. Do not enable this option by default and display clearly to the user that this setting will reduce the security of the entire system and they should only enable the setting if their system administrator has instructed them to do so.
//! @note By default certificate verification is run (not ignored).
//!
UDSDKDLL_API enum udError udConfig_IgnoreCertificateVerification(uint32_t ignore);

//!
//! This function can be used to override the user agent used by cURL.
//!
//! @param pUserAgent This is a null terminated string of the user agent.
//! @return A udError value based on the result of setting the user agent.
//!
UDSDKDLL_API enum udError udConfig_SetUserAgent(const char *pUserAgent);

//!
//! This function can be used to override the location that udSDK will save it's configuration files.
//!
//! @param pLocation This is a null terminated string specifying a directory to save configurations files.
//! @return A udError value based on the result of setting the configuration location.
//! @note By default, udSDK will attempt to use some known platform locations, in some cases failing to save entirely.
//! @note This location will have `/euclideon/udsdk` appending to the end.
//!
UDSDKDLL_API enum udError udConfig_SetConfigLocation(const char *pLocation);

#ifdef __cplusplus
}
#endif

#endif // udConfig_h__

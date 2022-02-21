#ifndef udPointBuffer_h__
#define udPointBuffer_h__

//! @file udPointBuffer.h
//! The udPointBuffer object provides an interface to add or get points from udPointClouds

#include "udDLLExport.h"
#include "udAttributes.h"
#include "udError.h"

#ifdef __cplusplus
extern "C" {
#endif

//!
//! @struct udPointBufferF64
//! Stores a set of points and their attributes that have positions as double (64bit float) values
//!
struct udPointBufferF64
{
  double *pPositions; //!< Flat array of XYZ positions in the format XYZXYZXYZXYZXYZXYZXYZ...
  uint8_t *pAttributes; //!< Byte array of attribute data ordered as specified in `attributes`
  struct udAttributeSet attributes; //!< Information on the attributes that are available in this point buffer
  uint32_t positionStride; //!< Total bytes between the start of one position and the start of the next (currently always 24 (8 bytes per double * 3 doubles))
  uint32_t attributeStride; //!< Total number of bytes between the start of the attibutes of one point and the first byte of the next attribute
  uint32_t pointCount; //!< How many points are currently contained in this buffer
  uint32_t pointsAllocated; //!< Total number of points that can fit in this udPointBufferF64
  uint32_t _reserved; //!< Reserved for internal use
};

//!
//! @struct udPointBufferI64
//! Stores a set of points and their attributes that have positions as Int64 values
//!
struct udPointBufferI64
{
  int64_t *pPositions;  //!< Flat array of XYZ positions in the format XYZXYZXYZXYZXYZXYZXYZ...
  uint8_t *pAttributes; //!< Byte array of attribute data ordered as specified in `attributes`
  struct udAttributeSet attributes; //!< Information on the attributes that are available in this point buffer
  uint32_t positionStride; //!< Total bytes between the start of one position and the start of the next (currently always 24 (8 bytes per int64 * 3 int64))
  uint32_t attributeStride; //!< Total number of bytes between the start of the attibutes of one point and the first byte of the next attribute
  uint32_t pointCount; //!< How many points are currently contained in this buffer
  uint32_t pointsAllocated; //!< Total number of points that can fit in this udPointBufferF64
  uint32_t _reserved; //!< Reserved for internal use
};

//!
//! Create a 64bit floating point, point buffer object
//!
//! @param ppBuffer The pointer pointer of the udPointBufferF64. This will allocate an instance of `udPointBufferF64` into `ppBuffer`.
//! @param maxPoints The maximum number of points that this buffer will contain (these are preallocated to avoid allocations later)
//! @param pAttributes The pointer to the udAttributeSet containing information on the attributes that will be available in this point buffer; NULL will have no attributes. An internal copy is made of this attribute set.
//! @return A udError value based on creation status.
//! @note The application should call **udPointBufferF64_Destroy** with `ppBuffer` to destroy the point buffer object once it's no longer needed.
//!
UDSDKDLL_API enum udError udPointBufferF64_Create(struct udPointBufferF64 **ppBuffer, uint32_t maxPoints, struct udAttributeSet *pAttributes);

//!
//! Destroys the udPointBufferF64.
//!
//! @param ppBuffer The pointer pointer of the ppBuffer. This will deallocate any memory used.
//! @return A udError value based on the result of the destruction.
//! @note The value of `ppBuffer` will be set to `NULL`.
//!
UDSDKDLL_API enum udError udPointBufferF64_Destroy(struct udPointBufferF64 **ppBuffer);

//!
//! Create a 64bit integer, point buffer object
//!
//! @param ppBuffer The pointer pointer of the udPointBufferI64. This will allocate an instance of `udPointBufferI64` into `ppBuffer`.
//! @param maxPoints The maximum number of points that this buffer will contain (these are preallocated to avoid allocations later)
//! @param pAttributes The pointer to the udAttributeSet containing information on the attributes that will be available in this point buffer; NULL will have no attributes. An internal copy is made of this attribute set.
//! @return A udError value based on creation status.
//! @note The application should call **udPointBufferI64_Destroy** with `ppBuffer` to destroy the point buffer object once it's no longer needed.
//!
UDSDKDLL_API enum udError udPointBufferI64_Create(struct udPointBufferI64 **ppBuffer, uint32_t maxPoints, struct udAttributeSet *pAttributes);

//!
//! Destroys the udPointBufferI64.
//!
//! @param ppBuffer The pointer pointer of the ppBuffer. This will deallocate any memory used.
//! @return A udError value based on the result of the destruction.
//! @note The value of `ppBuffer` will be set to `NULL`.
//!
UDSDKDLL_API enum udError udPointBufferI64_Destroy(struct udPointBufferI64 **ppBuffer);

#ifdef __cplusplus
}
#endif

#endif // udPointBuffer_h__

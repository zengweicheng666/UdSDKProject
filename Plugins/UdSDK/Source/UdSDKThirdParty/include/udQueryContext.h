#ifndef udQueryContext_h__
#define udQueryContext_h__

//! @file udQueryContext.h
//! The udQueryContext object provides an interface to query or filter pointclouds.

#include <stdint.h>

#include "udDLLExport.h"
#include "udError.h"
#include "udPointCloud.h"
#include "udPointBuffer.h"

#ifdef __cplusplus
extern "C" {
#endif

  struct udQueryContext;
  struct udQueryFilter;

  struct udRenderInstance; // From udRenderContext.h
  struct udGeometry; // From udGeometry.h

  //!
  //! Create an instance of a udQueryFilter.
  //!
  //! @param ppQueryFilter The pointer pointer of the udQueryFilter. This will allocate an instance of udQueryFilter into `ppQueryFilter`.
  //! @return A udError value based on the result of the udQueryFilter creation.
  //!
  UDSDKDLL_API enum udError udQueryFilter_Create(struct udQueryFilter **ppQueryFilter);

  //!
  //! Destroy the instance of udQueryFilter.
  //!
  //! @param ppQueryFilter The pointer pointer of the udQueryFilter. This will deallocate the instance of udQueryFilter.
  //! @return A udError value based on the result of the udQueryFilter destruction.
  //!
  UDSDKDLL_API enum udError udQueryFilter_Destroy(struct udQueryFilter **ppQueryFilter);

  //!
  //! Invert the result of a udQueryFilter.
  //!
  //! @param pQueryFilter The udQueryFilter to configure.
  //! @param inverted Not 0 if the filter should be inverted, 0 if it should behave as default.
  //! @return A udError value based on the result of the operation.
  //! @note Different filters may behave differently when inverted, see notes on each type.
  //!
  UDSDKDLL_API enum udError udQueryFilter_SetInverted(struct udQueryFilter *pQueryFilter, uint32_t inverted);

  //!
  //! Set the udQueryFilter to find voxels within a box.
  //!
  //! @param pQueryFilter The udQueryFilter to configure.
  //! @param centrePoint The world space {X,Y,Z} array for the center point.
  //! @param halfSize The local space {X,Y,Z} half size of the box (the world space axis are defined by yawPitchRoll).
  //! @param yawPitchRoll The rotation of the model (in radians). Applied in YPR order.
  //! @return A udError value based on the result of the operation.
  //! @note When inverted, this filter will return all points outside the box.
  //!
  UDSDKDLL_API enum udError udQueryFilter_SetAsBox(struct udQueryFilter *pQueryFilter, const double centrePoint[3], const double halfSize[3], const double yawPitchRoll[3]);

  //!
  //! Set the udQueryFilter to find voxels within a cylinder.
  //!
  //! @param pQueryFilter The udQueryFilter to configure.
  //! @param centrePoint The world space {X,Y,Z} array for the center point of the cylinder.
  //! @param radius The radius of the cylinder (the world space axis are defined by yawPitchRoll) the circle exists in local axis XY extruded along Z.
  //! @param halfHeight The half-height of the cylinder (the world space axis are defined by yawPitchRoll) the circle exists in local axis XY extruded along Z.
  //! @param yawPitchRoll The rotation of the cylinder (in radians). Applied in YPR order.
  //! @return A udError value based on the result of the operation.
  //! @note When inverted, this filter will return all points outside the cylinder.
  //!
  UDSDKDLL_API enum udError udQueryFilter_SetAsCylinder(struct udQueryFilter *pQueryFilter, const double centrePoint[3], const double radius, const double halfHeight, const double yawPitchRoll[3]);

  //!
  //! Set the udQueryFilter to find voxels within a sphere.
  //!
  //! @param pQueryFilter The udQueryFilter to configure.
  //! @param centrePoint The world space {X,Y,Z} array for the center point.
  //! @param radius The radius from the centerPoint to the edge of the sphere.
  //! @return A udError value based on the result of the operation.
  //! @note When inverted, this filter will return all points outside the sphere.
  //!
  UDSDKDLL_API enum udError udQueryFilter_SetAsSphere(struct udQueryFilter *pQueryFilter, const double centrePoint[3], const double radius);

  //!
  //! Set the udQueryFilter to find voxels using a udGeometry structure.
  //!
  //! @param pQueryFilter The udQueryFilter to configure.
  //! @param pGeometry The udGeometry filter to use.
  //! @return A udError value based on the result of the operation.
  //! @note pGeometry is referenced (not copied) so must exist for as long as this query filter.
  //! @warning udQueryFilter_SetInverted will not work with this method- an udGeometry Inverse filter should be used instead
  //!
  UDSDKDLL_API enum udError udQueryFilter_SetFromGeometry(struct udQueryFilter *pQueryFilter, struct udGeometry *pGeometry);

  //!
  //! Get the udGeometry structure used in a given udQueryFilter.
  //!
  //! @param pQueryFilter The udQueryFilter to inspect.
  //! @param pGeometry The pointer pointer to a udGeometry filter.
  //! @return A udError value based on the result of the operation.
  //!
  UDSDKDLL_API enum udError udQueryFilter_GetGeometry(struct udQueryFilter *pQueryFilter, struct udGeometry **ppGeometry);

  //!
  //! Create an instance of a udQueryContext with a specific model.
  //!
  //! @param pContext The context to be used to create the query context.
  //! @param ppQueryCtx The pointer pointer of the udQueryContext. This will allocate an instance of udQueryContext into `ppQuery`.
  //! @param pPointCloud The point cloud to run the query on, it is located at its storedMatrix location (this can be changed using udQueryContext_ChangePointCloud).
  //! @param pFilter The filter to use in this query (this can be changed using udQueryContext_ChangeFilter).
  //! @return A udError value based on the result of the udQueryContext creation.
  //! @note A future release will add multiple model support and non-storedMatrix locations.
  //!
  UDSDKDLL_API enum udError udQueryContext_Create(struct udContext *pContext, struct udQueryContext **ppQueryCtx, struct udPointCloud *pPointCloud, const struct udQueryFilter *pFilter);

  //!
  //! Resets the udQueryContext and uses a new filter.
  //!
  //! @param pQueryCtx The udQueryContext item previously created using udQueryContext_Create.
  //! @param pFilter The new filter to use in this query.
  //! @return A udError value based on the result of the operation.
  //! @note This will reset the query, any existing progress will be lost.
  //!
  UDSDKDLL_API enum udError udQueryContext_ChangeFilter(struct udQueryContext *pQueryCtx, const struct udQueryFilter *pFilter);

  //!
  //! Resets the udQueryContext and uses a different model.
  //!
  //! @param pQueryCtx The udQueryContext item previously created using udQueryContext_Create.
  //! @param pPointCloud The new model to use in this query.
  //! @return A udError value based on the result of the operation.
  //! @note This will reset the query, any existing progress will be lost.
  //!
  UDSDKDLL_API enum udError udQueryContext_ChangePointCloud(struct udQueryContext *pQueryCtx, const struct udPointCloud *pPointCloud);

  //!
  //! Gets the next set of points from an existing udQueryContext.
  //!
  //! @param pQueryCtx The udQueryContext to execute.
  //! @param pPointBuffer The point buffer to write found points to.
  //! @return A udError value based on the result of the operation. 
  //! @note This should continue to be called until it returns udE_NotFound indicating the query has completed.
  //!
  UDSDKDLL_API enum udError udQueryContext_ExecuteF64(struct udQueryContext *pQueryCtx, struct udPointBufferF64 *pPointBuffer);

  //!
  //! Gets the next set of points from an existing udQueryContext.
  //!
  //! @param pQueryCtx The udQueryContext to execute.
  //! @param pPointBuffer The point buffer to write found points to.
  //! @return A udError value based on the result of the operation.
  //! @note This should continue to be called until it returns udE_NotFound indicating the query has completed.
  //!
  UDSDKDLL_API enum udError udQueryContext_ExecuteI64(struct udQueryContext *pQueryCtx, struct udPointBufferI64 *pPointBuffer);

  //!
  //! Destroy the instance of udQueryContext.
  //!
  //! @param ppQueryCtx The pointer pointer of the udQueryContext. This will destroy the instance of udQueryContext in `ppQuery` and set it to NULL.
  //! @return A udError value based on the result of the udQueryFilter destruction.
  //!
  UDSDKDLL_API enum udError udQueryContext_Destroy(struct udQueryContext **ppQueryCtx);

#ifdef __cplusplus
}
#endif

#endif // udQueryContext_h__

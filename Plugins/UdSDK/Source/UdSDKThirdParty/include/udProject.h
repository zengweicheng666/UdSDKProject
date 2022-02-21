#ifndef udProject_h__
#define udProject_h__

//! @file udProject.h
//! The udProject and udProjectNode objects provide an interface for storing and syncronising geolocated projects between udSDK sessions
//! @note The GeoJSON provided by this implementation is not fully compliant with RFC7946
//! @warning Antimeridian Cutting (Section 3.1.9) and handling the poles (Secion 5.3) are not fully working in this implementation
//! @warning This module does not currently expose the functionality to sync with the server. This will be added in a future release.

#include "udDLLExport.h"
#include "udError.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

  struct udContext;

  //!
  //! @struct udProject
  //! Stores the internal state of the project
  //!
  struct udProject;

  //!
  //! @struct udInternalProjectNode
  //! Stores the internal state of a udProjectNode
  //!
  struct udInternalProjectNode;

  //!
  //! These are the geometry types for nodes
  //!
  enum udProjectGeometryType
  {
    udPGT_None, //!< There is no geometry associated with this node

    udPGT_Point, //!< pCoordinates is a single 3D position
    udPGT_MultiPoint, //!< Array of udPGT_Point, pCoordinates is an array of 3D positions
    udPGT_LineString, //!< pCoordinates is an array of 3D positions forming an open line
    udPGT_MultiLineString, //!< Array of udPGT_LineString; pCoordinates is NULL and children will be present
    udPGT_Polygon, //!< pCoordinates will be a closed linear ring (the outside), there MAY be children that are interior as pChildren udPGT_MultiLineString items, these should be counted as islands of the external ring.
    udPGT_MultiPolygon, //!< pCoordinates is null, children will be udPGT_Polygon (which still may have internal islands)
    udPGT_GeometryCollection, //!< Array of geometries; pCoordinates is NULL and children may be present of any type

    udPGT_Count, //!< Total number of geometry types. Used internally but can be used as an iterator max when displaying different type modes.

    udPGT_Internal, //!< Used internally when calculating other types. Do not use.
  };

  //!
  //! This represents the type of data stored in the node.
  //! @note The `itemtypeStr` in the udProjectNode is a string version. This enum serves to simplify the reading of standard types. The the string in brackets at the end of the comment is the string.
  //!
  enum udProjectNodeType
  {
    udPNT_Custom, //!< Need to check the itemtypeStr string manually

    udPNT_PointCloud, //!< A Euclideon Unlimited Detail Point Cloud file ("UDS")
    udPNT_PointOfInterest, //!< A point, line or region describing a location of interest ("POI")
    udPNT_Folder, //!< A folder of other nodes ("Folder")
    udPNT_Media, //!< An Image, Movie, Audio file or other media object ("Media")
    udPNT_Viewpoint, //!< An Camera Location & Orientation ("Camera")
    udPNT_VisualisationSettings, //!< Visualisation settings (itensity, map height etc) ("VizSet")
    udPNT_I3S, //!< An Indexed 3d Scene Layer (I3S) or Scene Layer Package (SLPK) dataset ("I3S")
    udPNT_Water, //!< A region describing the location of a body of water ("Water")
    udPNT_ViewShed, //!< A point describing where to generate a view shed from ("ViewMap")
    udPNT_Polygon, //!< A polygon model, usually an OBJ or FBX ("Polygon")
    udPNT_QueryFilter, //!< A query filter to be applied to all PointCloud types in the scene ("QFilter")
    udPNT_Places, //!< A collection of places that can be grouped together at a distance ("Places")
    udPNT_HeightMeasurement, //!< A height measurement object ("MHeight")
    udPNT_GTFS, //!< A General Transit Feed Specification object ("GTFS")
    udPNT_Count //!< Total number of node types. Used internally but can be used as an iterator max when displaying different type modes.
  };

  //!
  //! @struct udProjectNode
  //! Stores the state of a node.
  //! @warning This struct is exposed to avoid having a huge API of accessor functions but it should be treated as read only with the exception of `pUserData`. Making changes to the internal data will cause issues syncronising data
  //!
  struct udProjectNode
  {
    // Node header data
    int isVisible; //!< Non-zero if the node is visible and should be drawn in the scene
    char UUID[37]; //!< Unique identifier for this node "id"
    double lastUpdate; //!< The last time this node was updated in UTC

    enum udProjectNodeType itemtype; //!< The type of this node, see udProjectNodeType for more information
    char itemtypeStr[8]; //!< The string representing the type of node. If its a known type during node creation `itemtype` will be set to something other than udPNT_Custom

    const char *pName; //!< Human readable name of the item
    const char *pURI; //!< The address or filename that the resource can be found.

    uint32_t hasBoundingBox; //!< Set to not 0 if this nodes boundingBox item is filled out
    double boundingBox[6]; //!< The bounds of this model, ordered as [West, South, Floor, East, North, Ceiling]

    // Geometry Info
    enum udProjectGeometryType geomtype; //!< Indicates what geometry can be found in this model. See the udProjectGeometryType documentation for more information.
    int geomCount; //!< How many geometry items can be found on this model
    double *pCoordinates; //!< The positions of the geometry of this node (NULL this this node doesn't have points). The format is [X0,Y0,Z0,...Xn,Yn,Zn]

    // Next nodes
    struct udProjectNode *pNextSibling; //!< This is the next item in the project (NULL if no further siblings)
    struct udProjectNode *pFirstChild; //!< Some types ("folder", "collection", "polygon"...) have children nodes, NULL if there are no children.

    // Node Data
    void *pUserData; //!< This is application specific user data. The application should traverse the tree to release these before releasing the udProject
    struct udInternalProjectNode *pInternalData; //!< Internal udSDK specific state for this node
  };

  //!
  //! This represents where the project was loaded from/saved to most recently and where future calls to udProject_Save will go
  //!
  enum udProjectLoadSource
  {
    udProjectLoadSource_Memory, //!< The project source exists in memory; udProject_CreateInMemory, udProject_LoadFromMemory or udProject_SaveToMemory
    udProjectLoadSource_Server, //!< The project source exists from the server; udProject_CreateInServer, udProject_LoadFromServer or udProject_SaveToServer
    udProjectLoadSource_URI, //!< The project source exists from a file or URL; udProject_CreateInFile, udProject_LoadFromFile or udProject_SaveToFile

    udProjectLoadSource_Count //!< Total number of source types. Used internally but can be used as an iterator max when displaying different source types.
  };

  //!
  //! Create an empty, local only, instance of `udProject`.
  //!
  //! @param ppProject The pointer pointer of the udProject. This will allocate an instance of udProject into `ppProject`.
  //! @param pName The name of the project, this will be the name of the root item.
  //! @return A udError value based on the result of the project creation.
  //!
  UDSDKDLL_API enum udError udProject_CreateInMemory(struct udContext *pContext, struct udProject **ppProject, const char *pName);

  //!
  //! Create an empty, local only, instance of `udProject`.
  //!
  //! @param ppProject The pointer pointer of the udProject. This will allocate an instance of udProject into `ppProject`.
  //! @param pName The name of the project, this will be the name of the root item.
  //! @param pFilename The path to create the project at.
  //! @return A udError value based on the result of the project creation.
  //!
  UDSDKDLL_API enum udError udProject_CreateInFile(struct udContext *pContext, struct udProject **ppProject, const char *pName, const char *pFilename);

  //!
  //! Create an empty project in the server and the local instance of `udProject`.
  //!
  //! @param pContext The pointer to the udContext of the session to use to load the project, read/write permissions will be based on the current session.
  //! @param ppProject The pointer pointer of the udProject. This will allocate an instance of udProject into `ppProject`.
  //! @param pName The name of the project, this will be the name of the root item.
  //! @param pGroupID The UUID of the group this project will belong to
  //! @return A udError value based on the result of the project creation.
  //!
  UDSDKDLL_API enum udError udProject_CreateInServer(struct udContext *pContext, struct udProject **ppProject, const char *pName, const char *pGroupID);

  //!
  //! Create a local only instance of `udProject` filled in with the contents of a GeoJSON string.
  //!
  //! @param ppProject The pointer pointer of the udProject. This will allocate an instance of udProject into `ppProject`.
  //! @param pGeoJSON The GeoJSON string of the project, this will be unpacked into udProjectNode items.
  //! @return A udError value based on the result of the project creation.
  //!
  UDSDKDLL_API enum udError udProject_LoadFromMemory(struct udContext *pContext, struct udProject **ppProject, const char *pGeoJSON);

  //!
  //! Create a local only instance of `udProject` filled in with the contents of the specified project file.
  //!
  //! @param ppProject The pointer pointer of the udProject. This will allocate an instance of udProject into `ppProject`.
  //! @param pFilename The project file URL.
  //! @return A udError value based on the result of the project creation.
  //!
  UDSDKDLL_API enum udError udProject_LoadFromFile(struct udContext *pContext, struct udProject **ppProject, const char *pFilename);

  //!
  //! Create a local instance of `udProject` filled in from the server.
  //!
  //! @param pContext The pointer to the udContext of the session to use to load the project, read/write permissions will be based on the current session.
  //! @param ppProject The pointer pointer of the udProject. This will allocate an instance of udProject into `ppProject`.
  //! @param pProjectUUID The UUID for the project that is being requested
  //! @return A udError value based on the result of the project creation.
  //!
  UDSDKDLL_API enum udError udProject_LoadFromServer(struct udContext *pContext, struct udProject **ppProject, const char *pProjectUUID);

  //!
  //! Destroy the instance of the project.
  //!
  //! @param ppProject The pointer pointer of the udProject. This will deallocate the instance of the project as well as destroying all nodes.
  //! @return A udError value based on the result of the project destruction.
  //! @warning The pUserData item should be already released from every node before calling this.
  //!
  UDSDKDLL_API enum udError udProject_Release(struct udProject **ppProject);

  //!
  //! Export a project to where it was loaded from (server or file).
  //!
  //! @param pProject The pointer to a valid udProject that will saved. This will fail immediately for projects loaded from memory
  //! @return A udError value based on the result of the project save
  //!
  UDSDKDLL_API enum udError udProject_Save(struct udProject *pProject);

  //!
  //! Export a project to a GeoJSON string in memory.
  //!
  //! @param pContext The pointer to the udContext of the session to use to save the project to memory.
  //! @param pProject The pointer to a valid udProject that will be exported as GeoJSON.
  //! @param ppMemory The pointer pointer to a string that will contain the exported GeoJSON.
  //! @return A udError value based on the result of the project export.
  //! @warning The memory is stored in the udProject and subsequent calls will destroy older versions, the buffer is released when the project is released.
  //!
  UDSDKDLL_API enum udError udProject_SaveToMemory(struct udContext *pContext, struct udProject *pProject, const char **ppMemory);

  //!
  //! Create an project in the server from an existing udProject
  //!
  //! @param pContext The pointer to the udContext of the session to use to upload the project, write permissions will be based on the current session.
  //! @param pProject The udProject to upload.
  //! @param pGroupID The UUID of the group this project will belong to
  //! @return A udError value based on the result of the project creation.
  //! @note pProject will point to the newly created project if this is successful
  //!
  UDSDKDLL_API enum udError udProject_SaveToServer(struct udContext *pContext, struct udProject *pProject, const char *pGroupID);

  //!
  //! Create an project in the server from an existing udProject
  //!
  //! @param pContext The pointer to the udContext of the session to use to save the project to file.
  //! @param pProject The udProject to save out.
  //! @param pPath The new path to save the project to
  //! @return A udError value based on the result of the project creation.
  //! @note pProject will point to the newly created file if this is successful
  //!
  UDSDKDLL_API enum udError udProject_SaveToFile(struct udContext *pContext, struct udProject *pProject, const char *pPath);

  //!
  //! Get the project root node.
  //!
  //! @param pProject The pointer to a valid udProject.
  //! @param ppRootNode The pointer pointer to a node that will contain the node. The node ownership still belongs to the pProject.
  //! @return A udError value based on the result of getting the root node.
  //! @note This node will always have itemtype of type udPNT_Folder and cannot (and will not) have sibling nodes.
  //! @note The name of the project is the name of the returned root node.
  //!
  UDSDKDLL_API enum udError udProject_GetProjectRoot(struct udProject *pProject, struct udProjectNode **ppRootNode);

  //!
  //! Get the project UUID (for server projects).
  //!
  //! @param pProject The pointer to a valid udProject.
  //! @param ppProjectUUID The pointer pointer to memory that will contain the project UUID. The ownership still belongs to the pProject.
  //! @return A udError value based on the result of getting the root node.
  //! @note Returns udE_NotFound for non-server projects
  //!
  UDSDKDLL_API enum udError udProject_GetProjectUUID(struct udProject *pProject, const char **ppProjectUUID);

  //!
  //! Get the state of unsaved local changes
  //!
  //! @param pProject The pointer to a valid udProject.
  //! @return udE_Success if there a unsaved changes, udE_NotFound when no local changes exist and other udError values for errors
  //!
  UDSDKDLL_API enum udError udProject_HasUnsavedChanges(struct udProject *pProject);

  //!
  //! Gets the current source of a given udProject
  //!
  //! @param pProject The pointer to a valid udProject.
  //! @param pSource The pointer to memory to write the source of pProject to
  //! @return udE_Success if wrote source, error otherwise
  //!
  UDSDKDLL_API enum udError udProject_GetLoadSource(struct udProject *pProject, enum udProjectLoadSource *pSource);

  //!
  //! Create a node in a project
  //!
  //! @param pProject The pointer to a valid udProject.
  //! @param ppNode A pointer pointer to the node that will be created. This can be NULL if getting the node back isn't required.
  //! @param pParent The parent node of the item.
  //! @param pType The string representing the type of the item. This can be a defined string provided by udProject_GetTypeName or a custom type. Cannot be NULL.
  //! @param pName A human readable name for the item. If this item is NULL it will attempt to generate a name from the pURI or the pType strings.
  //! @param pURI The URL, filename or other URI containing where to find this item. These should be absolute paths where applicable (preferably HTTPS) to ensure maximum interop with other packages.
  //! @param pUserData A pointer to data provided by the application to store in the `pUserData` item in the udProjectNode.
  //! @return A udError value based on the result of the node being created in the project.
  //!
  UDSDKDLL_API enum udError udProjectNode_Create(struct udProject *pProject, struct udProjectNode **ppNode, struct udProjectNode *pParent, const char *pType, const char *pName, const char *pURI, void *pUserData);

  //!
  //! Move a node to reorder within the current parent or move to a different parent.
  //!
  //! @param pProject The pointer to a valid udProject.
  //! @param pCurrentParent The current parent of pNode.
  //! @param pNewParent The intended new parent of pNode.
  //! @param pNode The node to move.
  //! @param pInsertBeforeChild The node that will be after pNode after the move. Set as NULL to be the last child of pNewParent.
  //! @return A udError value based on the result of the move.
  //!
  UDSDKDLL_API enum udError udProjectNode_MoveChild(struct udProject *pProject, struct udProjectNode *pCurrentParent, struct udProjectNode *pNewParent, struct udProjectNode *pNode, struct udProjectNode *pInsertBeforeChild);

  //!
  //! Remove a node from the project.
  //!
  //! @param pProject The pointer to a valid udProject.
  //! @param pParentNode The parent of the node to be removed.
  //! @param pNode The node to remove from the project.
  //! @return A udError value based on the result of removing the node.
  //! @warning Ensure that the pUserData point of pNode has been released before calling this.
  //!
  UDSDKDLL_API enum udError udProjectNode_RemoveChild(struct udProject *pProject, struct udProjectNode *pParentNode, struct udProjectNode *pNode);

  //!
  //! Set the human readable name of a node.
  //!
  //! @param pProject The pointer to a valid udProject.
  //! @param pNode The node to change the name of.
  //! @param pNodeName The new name of the node. This is duplicated internally.
  //! @return A udError value based on the result of setting the name.
  //!
  UDSDKDLL_API enum udError udProjectNode_SetName(struct udProject *pProject, struct udProjectNode *pNode, const char *pNodeName);

  //!
  //! Set the visibility of the node
  //!
  //! @param pNode The node to change the visibility.
  //! @param visibility The new visibility of the node (non-zero for visible).
  //! @return A udError value based on the result of updating the visibility.
  //!
  UDSDKDLL_API enum udError udProjectNode_SetVisibility(struct udProjectNode *pNode, int visibility);

  //!
  //! Set the URI of a node.
  //!
  //! @param pProject The pointer to a valid udProject.
  //! @param pNode The node to change the name of.
  //! @param pNodeURI The new URI of the node. This is duplicated internally.
  //! @return A udError value based on the result of setting the URI.
  //!
  UDSDKDLL_API enum udError udProjectNode_SetURI(struct udProject *pProject, struct udProjectNode *pNode, const char *pNodeURI);

  //!
  //! Set the new geometry of a node.
  //!
  //! @param pProject The pointer to a valid udProject.
  //! @param pNode The node to change the name of.
  //! @param nodeType The new type of the geometry
  //! @param geometryCount How many coordinates are being added
  //! @param pCoordinates A pointer to the new coordinates (this is an array that should be 3x the length of geometryCount). Ordered in [ longitude0, latitude0, altitude0, ..., longitudeN, latitudeN, altitudeN ] order.
  //! @return A udError value based on the result of setting the geometry.
  //!
  UDSDKDLL_API enum udError udProjectNode_SetGeometry(struct udProject *pProject, struct udProjectNode *pNode, enum udProjectGeometryType nodeType, int geometryCount, double *pCoordinates);

  //!
  //! Get a metadata item of a node as an integer.
  //!
  //! @param pNode The node to get the metadata from.
  //! @param pMetadataKey The name of the metadata key.
  //! @param pInt The pointer to the memory to write the metadata to
  //! @param defaultValue The value to write to pInt if the metadata item isn't in the udProjectNode or if it isn't of an integer type
  //! @return A udError value based on the result of reading the metadata into pInt.
  //!
  UDSDKDLL_API enum udError udProjectNode_GetMetadataInt(struct udProjectNode *pNode, const char *pMetadataKey, int32_t *pInt, int32_t defaultValue);

  //!
  //! Set a metadata item of a node from an integer.
  //!
  //! @param pNode The node to get the metadata from.
  //! @param pMetadataKey The name of the metadata key.
  //! @param iValue The integer value to write to the metadata key
  //! @return A udError value based on the result of writing the metadata into the node.
  //!
  UDSDKDLL_API enum udError udProjectNode_SetMetadataInt(struct udProjectNode *pNode, const char *pMetadataKey, int32_t iValue);

  //!
  //! Get a metadata item of a node as an unsigned integer.
  //!
  //! @param pNode The node to get the metadata from.
  //! @param pMetadataKey The name of the metadata key.
  //! @param pInt The pointer to the memory to write the metadata to
  //! @param defaultValue The value to write to pInt if the metadata item isn't in the udProjectNode or if it isn't of an integer type
  //! @return A udError value based on the result of reading the metadata into pInt.
  //!
  UDSDKDLL_API enum udError udProjectNode_GetMetadataUint(struct udProjectNode *pNode, const char *pMetadataKey, uint32_t *pInt, uint32_t defaultValue);

  //!
  //! Set a metadata item of a node from an unsigned integer.
  //!
  //! @param pNode The node to get the metadata from.
  //! @param pMetadataKey The name of the metadata key.
  //! @param iValue The unsigned integer value to write to the metadata key
  //! @return A udError value based on the result of writing the metadata into the node.
  //!
  UDSDKDLL_API enum udError udProjectNode_SetMetadataUint(struct udProjectNode *pNode, const char *pMetadataKey, uint32_t iValue);

  //!
  //! Get a metadata item of a node as a 64 bit integer.
  //!
  //! @param pNode The node to get the metadata from.
  //! @param pMetadataKey The name of the metadata key.
  //! @param pInt64 The pointer to the memory to write the metadata to
  //! @param defaultValue The value to write to pInt64 if the metadata item isn't in the udProjectNode or if it isn't of an integer type
  //! @return A udError value based on the result of reading the metadata into pInt64.
  //!
  UDSDKDLL_API enum udError udProjectNode_GetMetadataInt64(struct udProjectNode *pNode, const char *pMetadataKey, int64_t *pInt64, int64_t defaultValue);

  //!
  //! Set a metadata item of a node from a 64 bit integer.
  //!
  //! @param pNode The node to get the metadata from.
  //! @param pMetadataKey The name of the metadata key.
  //! @param i64Value The integer value to write to the metadata key
  //! @return A udError value based on the result of writing the metadata into the node.
  //!
  UDSDKDLL_API enum udError udProjectNode_SetMetadataInt64(struct udProjectNode *pNode, const char *pMetadataKey, int64_t i64Value);

  //!
  //! Get a metadata item of a node as a double.
  //!
  //! @param pNode The node to get the metadata from.
  //! @param pMetadataKey The name of the metadata key.
  //! @param pDouble The pointer to the memory to write the metadata to
  //! @param defaultValue The value to write to pDouble if the metadata item isn't in the udProjectNode or if it isn't of an integer or floating point type
  //! @return A udError value based on the result of reading the metadata into pDouble.
  //!
  UDSDKDLL_API enum udError udProjectNode_GetMetadataDouble(struct udProjectNode *pNode, const char *pMetadataKey, double *pDouble, double defaultValue);

  //!
  //! Set a metadata item of a node from a double.
  //!
  //! @param pNode The node to get the metadata from.
  //! @param pMetadataKey The name of the metadata key.
  //! @param doubleValue The double value to write to the metadata key
  //! @return A udError value based on the result of writing the metadata into the node.
  //!
  UDSDKDLL_API enum udError udProjectNode_SetMetadataDouble(struct udProjectNode *pNode, const char *pMetadataKey, double doubleValue);

  //!
  //! Get a metadata item of a node as a boolean.
  //!
  //! @param pNode The node to get the metadata from.
  //! @param pMetadataKey The name of the metadata key.
  //! @param pBool The pointer to the memory to write the metadata to (0=false, !0=true)
  //! @param defaultValue The value to write to pBool if the metadata item isn't in the udProjectNode or if it isn't of a boolean type
  //! @return A udError value based on the result of reading the metadata into pBool.
  //!
  UDSDKDLL_API enum udError udProjectNode_GetMetadataBool(struct udProjectNode *pNode, const char *pMetadataKey, uint32_t *pBool, uint32_t defaultValue);

  //!
  //! Set a metadata item of a node from a boolean.
  //!
  //! @param pNode The node to get the metadata from.
  //! @param pMetadataKey The name of the metadata key.
  //! @param boolValue The boolean value to write to the metadata key (0=false, !0=true)
  //! @return A udError value based on the result of writing the metadata into the node.
  //!
  UDSDKDLL_API enum udError udProjectNode_SetMetadataBool(struct udProjectNode *pNode, const char *pMetadataKey, uint32_t boolValue);

  //!
  //! Get a metadata item of a node as a string.
  //!
  //! @param pNode The node to get the metadata from.
  //! @param pMetadataKey The name of the metadata key.
  //! @param ppString The pointer pointer to the memory of the string. This is owned by the udProjectNode and should be copied if required to be stored for a long period.
  //! @param pDefaultValue The value to write to ppString if the metadata item isn't in the udProjectNode or if it isn't of a string type
  //! @return A udError value based on the result of reading the metadata into ppString.
  //!
  UDSDKDLL_API enum udError udProjectNode_GetMetadataString(struct udProjectNode *pNode, const char *pMetadataKey, const char **ppString, const char *pDefaultValue);

  //!
  //! Set a metadata item of a node from a string.
  //!
  //! @param pNode The node to get the metadata from.
  //! @param pMetadataKey The name of the metadata key.
  //! @param pString The string to write to the metadata key. This is duplicated internally.
  //! @return A udError value based on the result of writing the metadata into the node.
  //!
  UDSDKDLL_API enum udError udProjectNode_SetMetadataString(struct udProjectNode *pNode, const char *pMetadataKey, const char *pString);

  //!
  //! Get the standard type string name for an itemtype
  //!
  //! @param itemtype The udProjectNodeType value
  //! @return A string containing the standard name for the item in the udProjectNodeType enum. This is internal and should not be freed.
  //!
  UDSDKDLL_API const char* udProject_GetTypeName(enum udProjectNodeType itemtype); // Might return NULL

  //!
  //! Deletes a project from the server
  //!
  //! @param pContext The udContext to use to communicate with the server
  //! @param pProjectUUID The UUID of the project to delete
  //! @return A udError result (udE_Success if it was deleted, other status codes depending on result)
  //!
  UDSDKDLL_API enum udError udProject_DeleteServerProject(struct udContext *pContext, const char *pProjectUUID);

  //!
  //! Sets the share status of a project on the server
  //!
  //! @param pContext The udContext to use to communicate with the server
  //! @param pProjectUUID The UUID of the project to update the share status of
  //! @param isSharableToAnyoneWithTheLink Not 0 if the project should be able to be loaded by anyone with the link, 0 otherwise
  //! @return A udError result (udE_Success if it was updated, other status codes depending on result)
  //!
  UDSDKDLL_API enum udError udProject_SetLinkShareStatus(struct udContext *pContext, const char *pProjectUUID, uint32_t isSharableToAnyoneWithTheLink);

#ifdef __cplusplus
}
#endif

#endif // udProject_h__

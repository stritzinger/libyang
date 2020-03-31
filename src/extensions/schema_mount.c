/**
 * @file schema_mount.c
 * @author Peer Stritzinger <peer@stritzinger.com>
 * @brief libyang extension plugin - SCHEMA_MOUNT (RFC 8528)
 *
 * Copyright (c) 2016-2017 CESNET, z.s.p.o.
 *
 * This source code is licensed under BSD 3-Clause License (the "License").
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://opensource.org/licenses/BSD-3-Clause
 */

#ifdef __GNUC__
#  define UNUSED(x) UNUSED_ ## x __attribute__((__unused__))
#else
#  define UNUSED(x) UNUSED_ ## x
#endif

#include <stdlib.h>

#include "../extensions.h"

/**
 * @brief Storage for ID used to check plugin API version compatibility.
 */
LYEXT_VERSION_CHECK

/**
 * @brief Callback to check that the SCHEMA_MOUNT extension can be instantiated inside the provided node
 *
 * @param[in] parent The parent of the instantiated extension.
 * @param[in] parent_type The type of the structure provided as \p parent.
 * @param[in] substmt_type libyang does not store all the extension instances in the structures where they are
 *                         instantiated in the module. In some cases (see #LYEXT_SUBSTMT) they are stored in parent
 *                         structure and marked with flag to know in which substatement of the parent the extension
 *                         was originally instantiated.
 * @return 0 - ok
 *         1 - error
 */
int schema_mount_position(const void * UNUSED(parent), LYEXT_PAR UNUSED(parent_type), LYEXT_SUBSTMT UNUSED(substmt_type))
{
  return 0;
}

/**
 * @brief Callback to decide whether the extension will be inherited into the provided schema node. The extension
 * instance is always from some of the node's parents.
 *
 * @param[in] ext Extension instance to be inherited.
 * @param[in] node Schema node where the node is supposed to be inherited.
 * @return 0 - yes
 *         1 - no (do not process the node's children)
 *         2 - no, but continue with children
 */
int schema_mount_inherit(struct lys_ext_instance *UNUSED(ext), struct lys_node * UNUSED(node))
{
    /* libyang already checks if there is explicit instance of the extension already present,
     * in such a case the extension is never inherited and we don't need to check it here */

  return 2;
}

/**
 * @brief Callback to check that the extension instance is correct - have
 * the valid argument, cardinality, etc.
 *
 * In SCHEMA_MOUNT case, we are checking only the cardinality.
 *
 * @param[in] ext Extension instance to be checked.
 * @return 0 - ok
 *         1 - error
 */
int
schema_mount_cardinality(struct lys_ext_instance * UNUSED(ext))
{
  return 0;
}

/**
 * @brief Plugin for the SCHEMA_MOUNT's schema-mount extension
 */
struct lyext_plugin schema_mount_ext = {
    .type = LYEXT_FLAG,
    .flags = LYEXT_OPT_INHERIT,
    .check_position = &schema_mount_position,
    .check_result = &schema_mount_cardinality,
    .check_inherit = &schema_mount_inherit
};


/**
 * @brief list of all extension plugins implemented here
 *
 * MANDATORY object for all libyang extension plugins, the name must match the <name>.so
 */
struct lyext_plugin_list schema_mount[] = {
    {"ietf-yang-schema-mount", "2017-10-09", "schema-mount", &schema_mount_ext},
    {NULL, NULL, NULL, NULL} /* terminating item */
};

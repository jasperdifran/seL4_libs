/*
 * Copyright 2017, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <sel4bench/kernel_logging.h>
// #include <sel4/sel4.h>
// #include <sel4/sel4_arch/mapping.h>

// #define KS_LOG_PPTR (0xffffffffffe00000ul - 0x200000ul)

// /**
//  * Retypes and maps a page table into the root servers page global directory
//  * @param cspace that the cptrs refer to
//  * @param vaddr  the virtual address of the mapping
//  * @param ut     a 4k untyped object
//  * @param empty  an empty slot to retype into a pt
//  * @return 0 on success
//  */
// static seL4_Error retype_map_pt(cspace_t *cspace, seL4_CPtr vspace, seL4_Word vaddr, seL4_CPtr ut, seL4_CPtr empty)
// {

//     seL4_Error err = cspace_untyped_retype(cspace, ut, empty, seL4_ARM_PageTableObject, seL4_PageBits);
//     if (err)
//     {
//         return err;
//     }

//     return seL4_ARM_PageTable_Map(empty, vspace, vaddr, seL4_ARM_Default_VMAttributes);
// }

// /**
//  * Retypes and maps a page directory into the root servers page global directory
//  * @param cspace that the cptrs refer to
//  * @param vaddr  the virtual address of the mapping
//  * @param ut     a 4k untyped object
//  * @param empty  an empty slot to retype into a pd
//  * @return 0 on success
//  */
// static seL4_Error retype_map_pd(cspace_t *cspace, seL4_CPtr vspace, seL4_Word vaddr, seL4_CPtr ut, seL4_CPtr empty)
// {

//     seL4_Error err = cspace_untyped_retype(cspace, ut, empty, seL4_ARM_PageDirectoryObject, seL4_PageBits);
//     if (err)
//     {
//         return err;
//     }

//     return seL4_ARM_PageDirectory_Map(empty, vspace, vaddr, seL4_ARM_Default_VMAttributes);
// }

// /**
//  * Retypes and maps a page upper directory into the root servers page global directory
//  * @param cspace that the cptrs refer to
//  * @param vaddr  the virtual address of the mapping
//  * @param ut     a 4k untyped object
//  * @param empty  an empty slot to retype into a pud
//  * @return 0 on success
//  */
// static seL4_Error retype_map_pud(cspace_t *cspace, seL4_CPtr vspace, seL4_Word vaddr, seL4_CPtr ut,
//                                  seL4_CPtr empty)
// {

//     seL4_Error err = cspace_untyped_retype(cspace, ut, empty, seL4_ARM_PageUpperDirectoryObject, seL4_PageBits);
//     if (err)
//     {
//         return err;
//     }
//     return seL4_ARM_PageUpperDirectory_Map(empty, vspace, vaddr, seL4_ARM_Default_VMAttributes);
// }

// static seL4_Error map_frame_impl(cspace_t *cspace, seL4_CPtr frame_cap, seL4_CPtr vspace, seL4_Word vaddr,
//                                  seL4_CapRights_t rights, seL4_ARM_VMAttributes attr,
//                                  seL4_CPtr *free_slots, seL4_Word *used)
// {
//     /* Attempt the mapping */
//     seL4_Error err = seL4_ARM_Page_Map(frame_cap, vspace, vaddr, rights, attr);
//     for (size_t i = 0; i < MAPPING_SLOTS && err == seL4_FailedLookup; i++)
//     {
//         /* save this so nothing else trashes the message register value */
//         seL4_Word failed = seL4_MappingFailedLookupLevel();

//         /* Assume the error was because we are missing a paging structure */
//         ut_t *ut = vk(NULL);
//         if (ut == NULL)
//         {
//             ZF_LOGE("Out of 4k untyped");
//             return -1;
//         }

//         /* figure out which cptr to use to retype into*/
//         seL4_CPtr slot;
//         if (used != NULL)
//         {
//             slot = free_slots[i];
//             *used |= BIT(i);
//         }
//         else
//         {
//             slot = cspace_alloc_slot(cspace);
//         }

//         if (slot == seL4_CapNull)
//         {
//             ZF_LOGE("No cptr to alloc paging structure");
//             return -1;
//         }

//         switch (failed)
//         {
//         case SEL4_MAPPING_LOOKUP_NO_PT:
//             err = retype_map_pt(cspace, vspace, vaddr, ut->cap, slot);
//             break;
//         case SEL4_MAPPING_LOOKUP_NO_PD:
//             err = retype_map_pd(cspace, vspace, vaddr, ut->cap, slot);
//             break;

//         case SEL4_MAPPING_LOOKUP_NO_PUD:
//             err = retype_map_pud(cspace, vspace, vaddr, ut->cap, slot);
//             break;
//         }

//         if (!err)
//         {
//             /* Try the mapping again */
//             err = seL4_ARM_Page_Map(frame_cap, vspace, vaddr, rights, attr);
//         }
//     }

//     return err;
// }

#if CONFIG_MAX_NUM_TRACE_POINTS > 0
unsigned int
kernel_logging_sync_log(void *log_buffer, kernel_log_entry_t log[], unsigned int n)
{

    kernel_log_entry_t *ksLog = (kernel_log_entry_t *)log_buffer;
    for (int i = 0; i < n; i++)
    {
        log[i] = ksLog[i];
    }

    return n;
}
#endif

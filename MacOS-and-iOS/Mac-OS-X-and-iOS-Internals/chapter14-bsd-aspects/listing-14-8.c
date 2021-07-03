// Listing 14-8: Audit worker thread record processing

/*
 * Given a kernel audit record, process as required.  Kernel audit records
 * are converted to one, or possibly two, BSM records, depending on whether
 * there is a user audit record present also.  Kernel records need be
 * converted to BSM before they can be written out.  Both types will be
 * written to disk, and audit pipes.
 */

static void audit_worker_process_record(struct kaudit_record *ar)
{
    // …
    // Convert to BSM record format
    error = kaudit_to_bsm(ar, &bsm);
    switch (error) {
     /// error handling on all codes is basically a goto out
    } 
    //
    // Write directly to the file. The audit_vp is the vnode of the audit file
    //
    if (ar->k_ar_commit & AR_PRESELECT_TRAIL) {
          AUDIT_WORKER_SX_ASSERT();
          audit_record_write(audit_vp, &audit_ctx, bsm->data, bsm->len);
      }
    //
    // Send to any /dev/auditpipe instances
    //
    if (ar->k_ar_commit & AR_PRESELECT_PIPE)
          audit_pipe_submit(auid, event, class, sorf,
          ar->k_ar_commit & AR_PRESELECT_TRAIL, bsm->data,
          bsm->len);
    //
    // Send to any /dev/auditsessions device instances (new in Lion)
    //
    if (ar->k_ar_commit & AR_PRESELECT_FILTER) {
        /*
         *  XXXss - This needs to be generalized so new filters can
         *  be easily plugged in.
         */
        audit_sdev_submit(auid, ar->k_ar.ar_subj_asid, bsm->data,
        bsm->len);
    }
        kau_free(bsm);
    out:
        if (trail_locked)
            AUDIT_WORKER_SX_XUNLOCK();
}
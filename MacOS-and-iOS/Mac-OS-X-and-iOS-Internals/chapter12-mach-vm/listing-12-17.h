// Listing 12-17: page_crypt_info structure from osfmk/kern/page_decrypt.h

/*
 *Interface for text decryption family
 */

struct pager_crypt_info {
    /* Decrypt one page */
    int (*page_decrypt)(const void *src_vaddr, void *dst_vaddr,
                        unsigned long long src_offset, void *crypt_ops);
    /* Pager using this crypter terminates - crypt module not needed anymore */
    void (*crypt_end)(void *crypt_ops);
    /* Private data for the crypter */
    void *crypt_ops;
};
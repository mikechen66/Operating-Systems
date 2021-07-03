// Listing 15-1: The standard disk ioctl codes from <sys/disk.h>

 /* Definitions
 /*
 /* ioctl                                 description
 /* ------------------------------------- ---------------------------------------
 /* DKIOCEJECT                            eject media
 /* DKIOCSYNCHRONIZECACHE                 flush media
 /*
 /* DKIOCFORMAT                           format media
 /* DKIOCGETFORMATCAPACITIES              get media's formattable capacities
 /*
 /* DKIOCGETBLOCKSIZE                     get media's block size
 /* DKIOCGETBLOCKCOUNT                    get media's block count
 /* DKIOCGETFIRMWAREPATH                  get media's firmware path
 /*
 /* DKIOCISFORMATTED                      is media formatted?
 /* DKIOCISWRITABLE                       is media writable?
 /*
 /* DKIOCREQUESTIDLE                      idle media
 /* DKIOCDISCARD                          delete unused data
 /*
 /* DKIOCGETMAXBLOCKCOUNTREAD             get maximum block count for reads
 /* DKIOCGETMAXBLOCKCOUNTWRITE            get maximum block count for writes
 /* DKIOCGETMAXSEGMENTCOUNTREAD           get maximum segment count for reads
 /* DKIOCGETMAXSEGMENTCOUNTWRITE          get maximum segment count for writes
 /* DKIOCGETMAXSEGMENTBYTECOUNTREAD       // get max segment byte count, reads
 /* DKIOCGETMAXSEGMENTBYTECOUNTWRITE      // get max segment byte count, writes
 /*
 /* DKIOCGETMINSEGMENTALIGNMENTBYTECOUNT  get minimum segment alignment in bytes
 /* DKIOCGETMAXSEGMENTADDRESSABLEBITCOUNT get maximum segment width in bits
 /*
 /* DKIOCGETPHYSICALBLOCKSIZE             get device's block size
 /* DKIOCGETCOMMANDPOOLSIZE               get device's queue depth
 /*/
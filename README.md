# LeoDB


## Fence Pointer Mapping
Data for the the Root is stored as follows:

* **Bytes 0 - 7:** Current Level
* **Bytes 8 - 15:** Metadata Offset (how many block can I jump by, i.e. N)
* **Bytes 16 - 23:** Level 0 (i.e. save the int 0)
* **Bytes 24 - 31:** Current Run (i.e. save 1)
* **Bytes 32 - 39:** Level 1 (i.e. save the int 1)
* **Bytes 40 - 47:** Current Run (i.e. save 2)
* ...

Where: 

* **N**: 16 bytes
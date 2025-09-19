# ARM Vector Floating-point Unit (VFP)


The VFP unit exists on 3DS ARM11.

- [ARM VFP Floating Point Registers](./armvfpfloatingpointregisters.md)
- [ARM VFP Floating Point Control/StatusRegisters](./armvfpfloatingpointcontrolstatusregisters.md)
- [ARM VFP Floating Point OpcodeEncoding](./armvfpfloatingpointopcodeencoding.md)
- [ARM VFP Floating Point MathsOpcodes](./armvfpfloatingpointmathsopcodes.md)
- [ARM VFP Floating Point Load/StoreOpcodes](./armvfpfloatingpointloadstoreopcodes.md)

**Floating Point**
The floating point hardware is called VFPv2 (Vector Floating-point).

```
+-----------------------------------------------------------------------+
|      A                                                                |
| RM DDI 0100I ARM Architecture Reference Manual (for ARMv6 wirh VFPv2) |
|      ARM D                                                            |
| DI 0360F ARM11 MPCore r2p0, contains more (mostly useless) VFPv2 info |
+-----------------------------------------------------------------------+
```

The Fxxxx floating point opcodes are aliases for CP10/CP11 copressor
numbers; CP10 used for single, and CP11 for double precision
instructions.




# 3DS Crypto - RSA sighax


sighax is a set of fake RSA signatures which are causing the bootrom to
always pass RSA checks.

**How it works**
derrek\'s sighax relies on some bugs in the bootrom RSA signatur
verification. RSA doesn\'t throw errors when decrypting a wron
signature with wrong key (instead, it does just output \"random\
gibberish). The decrypted signature should normally consist of leading
FFh-padding bytes, a header, and a SHA checksum.
However, the 3DS bootrom doesn\'t insist on the padding bytes, and i
does ignore most of the header bytes. Finally, it does allow the header
size to be as large as occupying the whole 100h-byte signature area,
which results in the SHA value being read from next higher address AFTER
the signature area - and the bootrom happens to store the computed SHA
at that location (causing the bootrom to compare the computed SHA
against itself, instead of against of what should have been the
decrypted SHA value).
Alltogether, brute-forcing requires only 6 specific bytes in the
decrypted signature (and the remaining 250 bytes are don\'t care).

The bootrom uses three RSA keys for different retail signatures, and
another three RSA keys for debug version.

**NCSD Signature (in eMMC)**
The eMMC\'s NCSD Header is unencrypted, and can be changed withou
needing any AES keys (however, booting custom code requires to change
FIRM, not NCSD).

```
+-----------------------------------------------------------------------+
|                                                                       |
|   6CF52F89F378120BFA4E1061D7361634D9A254A4F57AA5BD9F2C30934F0E68CB ;\ 
|                                                                       |
|    E6611D90D74CAAACB6A995565647333DC17092D320131089CCCD6331CB3A595D ; |
|       1BA2                                                            |
| 99A32FF4D8E5DD1EB46A2A57935F6FE637322D3BC4F67CFED6C2254C089C ; retail |
|       62FA1                                                           |
| 1D0824A844C79EE5A4F273D46C23BBBF0A2AF6ACADBE646F46B86D1289C ; version |
|                                                                       |
|    7FF7E816CFDA4BC33DFF9D175AC69F72406C071B51F45A1ACB87F168C177CB9B ; |
|                                                                       |
|    E6C392F0341849AE5D510D26EEC1097BEBFB9D144A1647301BEAF9520D22C55A ; |
|                                                                       |
|    F46D49284CC7F9FBBA371A6D6E4C55F1E536D6237FFF54B3E9C11A20CFCCAC0C ; |
|                                                                       |
|   6B06F695766ACEB18BE33299A94CFCA7E258818652F7526B306B52E0AED04218 ;/ |
|                                                                       |
|   53CB0E4EB1A6FF84284BE0E7385AB4A686A8BBCBC16102479280E0583655D271 ;\ 
|                                                                       |
|    3FE506FAEE74F8D10F1220441CC2FF5D6DDE99BE79C19B386CAF68D5EB8CED1A ; |
|       AB4                                                             |
| D243C5F398680D31CD2E3C9DD5670F2A88D563B8F65F5B234FD2EBB3BE44A ; debug |
|       3B6C3                                                           |
| 02722A2ADFB56AE3E1F6417BDEC1E5A86AABBAFBE9419ACA8FDCD45E2CD ; version |
|                                                                       |
|    F1EB695F6EA87816122D7BE98EEF92C0814B16B215B31D8C813BB355CEA8138F ; |
|                                                                       |
|    B3BF2374246842CD91E1F9AAFF76878617CE02064777AEA0876A2C245C784341 ; |
|                                                                       |
|    CDEE90D691745908A6FF9CE781166796F9F1238F884C84D6F1EEBB2E40B4BCA0 ; |
|                                                                       |
|   0A7B1E913E0980D29FF6061D8AA944C663F2638127F7CCAB6FC71538471A5138 ;/ |
+-----------------------------------------------------------------------+
```


**FIRM Signature (in eMMC)**
The eMMC\'s FIRM Header is encrypted via console-specific AES keys
Patching this area requires access to the corresponding AES keyslot (or
knowing the OTP seed value that was used to generate that key).
Alternately, knowing the decrypted content of the currently installed
firmware version will also help (then one can simply XOR the encrypted
bytes by old & new unencrypted bytes).

```
+-----------------------------------------------------------------------+
|                                                                       |
|   B6724531C448657A2A2EE306457E350A10D544B42859B0E5B0BED27534CCCC2A ;\ 
|                                                                       |
|    4D47EDEA60A7DD99939950A6357B1E35DFC7FAC773B7E12E7C1481234AF141B3 ; |
|       1CF0                                                            |
| 8E9F62293AA6BAAE246C15095F8B78402A684D852C680549FA5B3F14D9E8 ; retail |
|       38A2F                                                           |
| B9C09A15ABB40DCA25E40A3DDC1F58E79CEC901974363A946E99B4346E8 ; version |
|                                                                       |
|    A372B6CD55A707E1EAB9BEC0200B5BA0B661236A8708D704517F43C6C38EE956 ; |
|                                                                       |
|    0111E1405E5E8ED356C49C4FF6823D1219AFAEEB3DF3C36B62BBA88FC15BA864 ; |
|                                                                       |
|    8F9333FD9FC092B8146C3D908F73155D48BE89D72612E18E4AA8EB9B7FD2A5F7 ; |
|                                                                       |
|   328C4ECBFB0083833CBD5C983A25CEB8B941CC68EB017CE87F5D793ACA09ACF7 ;/ |
|                                                                       |
|   88697CDCA9D1EA318256FCD9CED42964C1E98ABC6486B2F128EC02E71C5AE35D ;\ 
|                                                                       |
|    63D3BF1246134081AF68754787FCB922571D7F61A30DE4FCFA8293A9DA512396 ; |
|       F13                                                             |
| 19A364968464CA9806E0A52567486754CDDD4C3A62BDCE255E0DEEC230129 ; debug |
|       C1BAE                                                           |
| 1AE95D786865637C1E65FAE83EDF8E7B07D17C0AADA8F055B640D45AB0B ; version |
|                                                                       |
|    AC76FF7B3439F5A4BFE8F7E0E103BCE995FAD913FB729D3D030B2644EC483964 ; |
|                                                                       |
|    24E0563A1B3E6A1F680B39FC1461886FA7A60B6B56C5A846554AE648FC46E30E ; |
|                                                                       |
|    24678FAF1DC3CEB10C2A950F4FFA2083234ED8DCC3587A6D751A7E9AFA061569 ; |
|                                                                       |
|   55084FF2725B698EB17454D9B02B6B76BE47ABBE206294366987A4CAB42CBD0B ;/ |
+-----------------------------------------------------------------------+
```


**FIRM Signature (in WifiFlash or NtrCard)**
These FIRM Headers are encrypted via fixed AES keys, and can be thus
generated without knowing console-specific keys. However, there are some
hardware requirements:
WifiFlash must have the write-protect pin disabled, and offset 400h must
be writeable (this does require a SPI flash chip with 128Kbyte or more;
and won\'t work with the normal built-in 4Kbyte chip). And, the eMM
firm sections must be \'destroyed\' to trigger WifiFlash booting.
NtrCard requires a NDS flashcart, and support for rewriting its
\"bootmenu\" memory region. And, key combination Start+Select+X wit
shell closed is needed to trigger NtrCard booting.

```
+-----------------------------------------------------------------------+
|                                                                       |
|   37E96B10BAF28C74A710EF35824C93F5FBB341CEE4FB446CE4D290ABFCEFACB0 ;\ 
|                                                                       |
|    63A9B55B3E8A65511D900C5A6E9403AAB5943CEF3A1E882B77D2347942B9E9EB ; |
|       0D75                                                            |
| 66370F0CB7310C38CB4AC940D1A6BB476BCC2C487D1C532120F1D2A37DDB ; retail |
|       3E36F                                                           |
| 8A2945BD8B16FB354980384998ECC380CD5CF8530F1DAD2FD74BA35ACB9 ; version |
|                                                                       |
|    C9DA2C131CB295736AE7EFA0D268EE01872EF033058ABA07B5C684EAD60D76EA ; |
|                                                                       |
|    84A18D866307AAAAB764786E396F2F8B630E60E30E3F1CD8A67D02F0A88152DE ; |
|                                                                       |
|    7A9E0DD5E64AB7593A3701E4846B6F338D22FD455D45DF212C5577266AA8C367 ; |
|                                                                       |
|   AE6E4CE89DF41691BF1F7FE58F2261F5D251DF36DE9F5AF1F368E650D576810B ;/ |
|                                                                       |
|   18722BC76DC3602E2C0171F3BCA12AB40EA6D112AEFBECF4BE7A2A58FF759058 ;\ 
|                                                                       |
|    A93C95CDA9B3B676D09A4E4C9E842E5C68229A6A9D77FAC76445E78EB5B363F8 ; |
|       C66                                                             |
| B166BE65AFAE40A1485A364C2C13B855CEEDE3DFEACEC68DD6B8687DD6DF8 ; debug |
|       B6D32                                                           |
| 13F72252E7C03C027EE6079F9C5E0290E5DB8CA0BBCF30FCAD72EB637A1 ; version |
|                                                                       |
|    70C4A2F41D96BF7D517A2F4F335930DC5E9792D78EDFB51DC79AD9D7A4E7F1ED ; |
|                                                                       |
|    4D5A5C621B6245A7F1652256011DC32C49B955304A423009E2B78072CEBC12B3 ; |
|                                                                       |
|    85B72F926F19318D64075F09278FBA8448FD2484B82654A55D064542A8F5D9F9 ; |
|                                                                       |
|   828CDA5E60D31A40CF8EF18D027310DA4F807988BC753C1EB3B3FC06207E84DE ;/ |
+-----------------------------------------------------------------------+
```


**SIGHAX.BIN**
This signature is for unknown purpose (probably Retail eMMC FIRM, too):

```
+-----------------------------------------------------------------------+
|                                                                       |
|      6EFF209C8F4AF61F062413D602CA6B4DA1EB5AB9B6F1A2AB226A711DA2CCC27C |
|                                                                       |
|      74DE1741143BF69058284CAF444F92A45AAFD5A068043323D48AF1D0EC05564E |
|                                                                       |
|      BC79B55134E91A86C3788C97BC29D5A58A8A45255843B89122C7804542F72677 |
|                                                                       |
|      C8DA5EB7429BAF18F7A8B02E8BB940FE990E9DC97EDCF49DDB18092C28206E74 |
|                                                                       |
|      6753CC7C6E92362AA8D546B38D9E8D4311A6B1930DA14897807E304B5E1EC085 |
|                                                                       |
|      6EEFD62CEAEEF28B08BD80397A181560AE6FCE39D09C39DC3DED8C870AB6ABCE |
|                                                                       |
|      2894940C0E9C4174F0131A0DA0747C4A7A42C9EC3487F109E252B7A9B865AE47 |
|                                                                       |
|      7895E8D6A42A0717C40BCCC7A735F33B1E3766AB0E4B5D681BAB410734AB62B0 |
+-----------------------------------------------------------------------+
```


**Links & Credits**
<http://www.sighax.com/> ;one signature, and some general info
<http://gist.github.com/SciresM/cdd2266efb80175d37eabbe86f9d8c52> ;six
signatures




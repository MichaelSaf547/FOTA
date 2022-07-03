/*
 * Nvic.h
 *
 *  Created on: July 1, 2022
 *      Author: FOTA | ITI_42
 */

#ifndef NVIC_H_
#define NVIC_H_

//******************New Types******************//


//*******************Defines*******************//
#define IRQ0         0
#define IRQ1         1
#define IRQ2         2
#define IRQ3         3
#define IRQ4         4
#define IRQ5         5
#define IRQ6         6
#define IRQ7         7
#define IRQ8         8
#define IRQ9         9
#define IRQ10        10
#define IRQ11        11
#define IRQ12        12
#define IRQ13        13
#define IRQ14        14
#define IRQ15        15
#define IRQ16        16
#define IRQ17        17
#define IRQ18        18
#define IRQ19        19
#define IRQ20        20
#define IRQ21        21
#define IRQ22        22
#define IRQ23        23
#define IRQ24        24
#define IRQ25        25
#define IRQ26        26
#define IRQ27        27
#define IRQ28        28
#define IRQ29        29
#define IRQ30        30
#define IRQ31        31
#define IRQ32        32
#define IRQ33        33
#define IRQ34        34
#define IRQ35        35
#define IRQ36        36
#define IRQ37        37
#define IRQ38        38
#define IRQ39        39
#define IRQ40        40
#define IRQ41        41
#define IRQ42        42
#define IRQ43        43
#define IRQ44        44
#define IRQ45        45
#define IRQ46        46
#define IRQ47        47
#define IRQ48        48
#define IRQ49        49
#define IRQ50        50
#define IRQ51        51
#define IRQ52        52
#define IRQ53        53
#define IRQ54        54
#define IRQ55        55
#define IRQ56        56
#define IRQ57        57
#define IRQ58        58
#define IRQ59        59
#define IRQ60        60
#define IRQ61        61
#define IRQ62        62
#define IRQ63        63
#define IRQ64        64
#define IRQ65        65
#define IRQ66        66
#define IRQ67        67
#define IRQ68        68
#define IRQ69        69
#define IRQ70        70
#define IRQ71        71
#define IRQ72        72
#define IRQ73        73
#define IRQ74        74
#define IRQ75        75
#define IRQ76        76
#define IRQ77        77
#define IRQ78        78
#define IRQ79        79
#define IRQ80        80
#define IRQ81        81
#define IRQ82        82
#define IRQ83        83
#define IRQ84        84
#define IRQ85        85
#define IRQ86        86
#define IRQ87        87
#define IRQ88        88
#define IRQ89        89
#define IRQ90        90
#define IRQ91        91
#define IRQ92        92
#define IRQ93        93
#define IRQ94        94
#define IRQ95        95
#define IRQ96        96
#define IRQ97        97
#define IRQ98        98
#define IRQ99        99
#define IRQ100       100
#define IRQ101       101
#define IRQ102       102
#define IRQ103       103
#define IRQ104       104
#define IRQ105       105
#define IRQ106       106
#define IRQ107       107
#define IRQ108       108
#define IRQ109       109
#define IRQ110       110
#define IRQ111       111
#define IRQ112       112
#define IRQ113       113
#define IRQ114       114
#define IRQ115       115
#define IRQ116       116
#define IRQ117       117
#define IRQ118       118
#define IRQ119       119
#define IRQ120       120
#define IRQ121       121
#define IRQ122       122
#define IRQ123       123
#define IRQ124       124
#define IRQ125       125
#define IRQ126       126
#define IRQ127       127
#define IRQ128       128
#define IRQ129       129
#define IRQ130       130
#define IRQ131       131
#define IRQ132       132
#define IRQ133       133
#define IRQ134       134
#define IRQ135       135
#define IRQ136       136
#define IRQ137       137
#define IRQ138       138
#define IRQ139       139
#define IRQ140       140
#define IRQ141       141
#define IRQ142       142
#define IRQ143       143
#define IRQ144       144
#define IRQ145       145
#define IRQ146       146
#define IRQ147       147
#define IRQ148       148
#define IRQ149       149
#define IRQ150       150
#define IRQ151       151
#define IRQ152       152
#define IRQ153       153
#define IRQ154       154
#define IRQ155       155
#define IRQ156       156
#define IRQ157       157
#define IRQ158       158
#define IRQ159       159
#define IRQ160       160
#define IRQ161       161
#define IRQ162       162
#define IRQ163       163
#define IRQ164       164
#define IRQ165       165
#define IRQ166       166
#define IRQ167       167
#define IRQ168       168
#define IRQ169       169
#define IRQ170       170
#define IRQ171       171
#define IRQ172       172
#define IRQ173       173
#define IRQ174       174
#define IRQ175       175
#define IRQ176       176
#define IRQ177       177
#define IRQ178       178
#define IRQ179       179
#define IRQ180       180
#define IRQ181       181
#define IRQ182       182
#define IRQ183       183
#define IRQ184       184
#define IRQ185       185
#define IRQ186       186
#define IRQ187       187
#define IRQ188       188
#define IRQ189       189
#define IRQ190       190
#define IRQ191       191
#define IRQ192       192
#define IRQ193       193
#define IRQ194       194
#define IRQ195       195
#define IRQ196       196
#define IRQ197       197
#define IRQ198       198
#define IRQ199       199
#define IRQ200       200
#define IRQ201       201
#define IRQ202       202
#define IRQ203       203
#define IRQ204       204
#define IRQ205       205
#define IRQ206       206
#define IRQ207       207
#define IRQ208       208
#define IRQ209       209
#define IRQ210       210
#define IRQ211       211
#define IRQ212       212
#define IRQ213       213
#define IRQ214       214
#define IRQ215       215
#define IRQ216       216
#define IRQ217       217
#define IRQ218       218
#define IRQ219       219
#define IRQ220       220
#define IRQ221       221
#define IRQ222       222
#define IRQ223       223
#define IRQ224       224
#define IRQ225       225
#define IRQ226       226
#define IRQ227       227
#define IRQ228       228
#define IRQ229       229
#define IRQ230       230
#define IRQ231       231
#define IRQ232       232
#define IRQ233       233
#define IRQ234       234
#define IRQ235       235
#define IRQ236       236
#define IRQ237       237
#define IRQ238       238
#define IRQ239       239

//*************Function prototypes*************//
/*
 * Purpose : Enable Peripheral Interrupt , this function takes 1 argument and return void
 *
 * Arguments : Peripheral name (IRQx) x : 0-->239
 *
 * Return : void
 */
void Nvic_EnableIRQ(u16 Irq_type);

/*
 * Purpose : Disable Peripheral Interrupt , this function takes 1 argument and return void
 *
 * Arguments : Peripheral name (IRQx) x : 0-->239
 *
 * Return : void
 */
void Nvic_DisableIRQ(u16 Irq_type);

/*
 * Purpose : Set pending of peripheral interrupt by software , this function takes 1 argument and
 * 			 return void
 *
 * Arguments : Peripheral name (IRQx) x : 0-->239
 *
 * Return : void
 */
void Nvic_SetPendingIRQ(u16 Irq_type);

/*
 * Purpose : Set software interrupt , this function takes number of peripheral and return void
 *
 * Argument : u16 IRQ(x) x : 0-->239
 *
 * Return : void
 */
void Nvic_SetSWInterrupt(u16 Irq_type);

/*
 * Purpose : Clear pending of peripheral interrupt , this function takes 1 argument and
 * 			 return void
 *
 * Arguments : Peripheral name (IRQx) x : 0-->239
 *
 * Return : void
 */
void Nvic_ClearPendingIRQ(u16 Irq_type);

/*
 * Purpose : Get active status of peripheral interrupt , this function takes 1 argument and return Active status
 *
 * Arguments : Peripheral name (IRQx) x : 0-->239
 *
 * Return : Active status : Active , NotActive
 */
u8 Nvic_GetActiveStatusTRQ(u16 Irq_type);

/*
 * Purpose : set priority of peripheral , this function takes 2 arguments and return void
 *
 * Arguments : Peripheral name (IRQx) x : 0-->239
 * 			   Priority
 *
 * Return : void
 */
void Nvic_SetPriorityIRQ(u16 Irq_type,u32 priority);

/*
 * Purpose : Set subgroup priority of peripheral , this function takes 1 arguments and return void
 *
 * Arguments : Peripheral name (IRQx) x : 0-->239
 * 			   Subgroup priority
 *
 * Return : void
 */
void Nvic_SetSubgroupPriority(u8 subgroup);

/*
 * Purpose : Encode Priority , this function takes the priority and subgroup priority and number of bits
 * 			 used in subgroup and it return the value of register
 *
 * Arguments : u8 subgroup , u8 priority, u8 number of subgroup bits
 *
 * Return u8 : value of priority register
 */
u8 Nvic_EncodePriority(u8 subgroup , u8 priority , u8 num_of_bits);

/*
 * Purpose : Enable all Interrupts
 *
 * Arguments : void
 *
 * Return : void
 */
void Nvic_EnableInterupts();

/*
 * Purpose : Disable all Interrupts
 *
 * Arguments : void
 *
 * Return : void
 */
void Nvic_DisableInterupts();

/*
 * Purpose : Enable all Interrupts with fault
 *
 * Arguments : void
 *
 * Return : void
 */
void Nvic_EnableInterupts_Faults();

/*
 * Purpose : Disable all Interrupts with fault
 *
 * Arguments : void
 *
 * Return : void
 */
void Nvic_DisableInterupts_Faults();

/*
 * Purpose : Disable Interrupts with higher priority
 *
 * Arguments : u8 Priority
 *
 * Return : void
 */
void Nvic_DisableLowerPriority(u8 Priority);



//CPSID i ; Disable interrupts and configurable fault handlers (set PRIMASK)
//CPSID f ; Disable interrupts and all fault handlers (set FAULTMASK)
//CPSIE i ; Enable interrupts and configurable fault handlers(clear PRIMASK)
//CPSIE f ; Enable interrupts and fault handlers (clear FAULTMASK)

#endif /* NVIC_H_ */

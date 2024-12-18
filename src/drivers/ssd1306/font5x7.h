/**
 * @file font5x7.h
 * @brief Таблица шрифтов для 5x7 символов, хранимая во FLASH
 *
 * Данный файл содержит массив шрифта для отображения символов размером 5x7.
 * Каждый символ занимает 5 байт (столбцов), где каждый байт описывает 7 вертикальных пикселей (бит).
 */

#ifndef FONT5X7_H
#define FONT5X7_H

/**
 * @brief Таблица шрифта 5x7
 *
 * Массив содержит битмапы для символов, начиная с ASCII 32 (пробел) и заканчивая ASCII 126.
 * Каждый символ представлен набором из 5 байт, соответствующих 5 столбцам.
 */
const unsigned char font5x7[][5] = {
    /** @brief Пробел [32] */
    {0x00, 0x00, 0x00, 0x00, 0x00},
    /** @brief ! [33] */
    {0x00, 0x00, 0x5F, 0x00, 0x00},
    /** @brief " [34] (кавычки) */
    {0x00, 0x07, 0x00, 0x07, 0x00},
    /** @brief # [35] */
    {0x14, 0x7F, 0x14, 0x7F, 0x14},
    /** @brief $ [36] */
    {0x24, 0x2E, 0x7B, 0x2A, 0x12},
    /** @brief % [37] */
    {0x23, 0x13, 0x08, 0x64, 0x62},
    /** @brief & [38] */
    {0x36, 0x49, 0x55, 0x22, 0x50},
    /** @brief ' [39] (одинарная кавычка) */
    {0x00, 0x05, 0x03, 0x00, 0x00},
    /** @brief ( [40] */
    {0x00, 0x1C, 0x22, 0x41, 0x00},
    /** @brief ) [41] */
    {0x00, 0x41, 0x22, 0x1C, 0x00},
    /** @brief * [42] */
    {0x14, 0x08, 0x3E, 0x08, 0x14},
    /** @brief + [43] */
    {0x08, 0x08, 0x3E, 0x08, 0x08},
    /** @brief , [44] */
    {0x00, 0x50, 0x30, 0x00, 0x00},
    /** @brief - [45] */
    {0x08, 0x08, 0x08, 0x08, 0x08},
    /** @brief . [46] */
    {0x00, 0x60, 0x60, 0x00, 0x00},
    /** @brief / [47] */
    {0x20, 0x10, 0x08, 0x04, 0x02},
    /** @brief 0 [48] */
    {0x3E, 0x51, 0x49, 0x45, 0x3E},
    /** @brief 1 [49] */
    {0x00, 0x42, 0x7F, 0x40, 0x00},
    /** @brief 2 [50] */
    {0x42, 0x61, 0x51, 0x49, 0x46},
    /** @brief 3 [51] */
    {0x21, 0x41, 0x45, 0x4B, 0x31},
    /** @brief 4 [52] */
    {0x18, 0x14, 0x12, 0x7F, 0x10},
    /** @brief 5 [53] */
    {0x27, 0x45, 0x45, 0x45, 0x39},
    /** @brief 6 [54] */
    {0x3C, 0x4A, 0x49, 0x49, 0x30},
    /** @brief 7 [55] */
    {0x01, 0x71, 0x09, 0x05, 0x03},
    /** @brief 8 [56] */
    {0x36, 0x49, 0x49, 0x49, 0x36},
    /** @brief 9 [57] */
    {0x06, 0x49, 0x49, 0x29, 0x1E},
    /** @brief : [58] */
    {0x00, 0x36, 0x36, 0x00, 0x00},
    /** @brief ; [59] */
    {0x00, 0x56, 0x36, 0x00, 0x00},
    /** @brief < [60] */
    {0x08, 0x14, 0x22, 0x41, 0x00},
    /** @brief = [61] */
    {0x14, 0x14, 0x14, 0x14, 0x14},
    /** @brief > [62] */
    {0x00, 0x41, 0x22, 0x14, 0x08},
    /** @brief ? [63] */
    {0x02, 0x01, 0x51, 0x09, 0x06},
    /** @brief @ [64] */
    {0x32, 0x49, 0x79, 0x41, 0x3E},
    /** @brief A [65] */
    {0x7E, 0x11, 0x11, 0x11, 0x7E},
    /** @brief B [66] */
    {0x7F, 0x49, 0x49, 0x49, 0x36},
    /** @brief C [67] */
    {0x3E, 0x41, 0x41, 0x41, 0x22},
    /** @brief D [68] */
    {0x7F, 0x41, 0x41, 0x22, 0x1C},
    /** @brief E [69] */
    {0x7F, 0x49, 0x49, 0x49, 0x41},
    /** @brief F [70] */
    {0x7F, 0x09, 0x09, 0x09, 0x01},
    /** @brief G [71] */
    {0x3E, 0x41, 0x49, 0x49, 0x7A},
    /** @brief H [72] */
    {0x7F, 0x08, 0x08, 0x08, 0x7F},
    /** @brief I [73] */
    {0x00, 0x41, 0x7F, 0x41, 0x00},
    /** @brief J [74] */
    {0x20, 0x40, 0x41, 0x3F, 0x01},
    /** @brief K [75] */
    {0x7F, 0x08, 0x14, 0x22, 0x41},
    /** @brief L [76] */
    {0x7F, 0x40, 0x40, 0x40, 0x40},
    /** @brief M [77] */
    {0x7F, 0x02, 0x0C, 0x02, 0x7F},
    /** @brief N [78] */
    {0x7F, 0x04, 0x08, 0x10, 0x7F},
    /** @brief O [79] */
    {0x3E, 0x41, 0x41, 0x41, 0x3E},
    /** @brief P [80] */
    {0x7F, 0x09, 0x09, 0x09, 0x06},
    /** @brief Q [81] */
    {0x3E, 0x41, 0x51, 0x21, 0x5E},
    /** @brief R [82] */
    {0x7F, 0x09, 0x19, 0x29, 0x46},
    /** @brief S [83] */
    {0x46, 0x49, 0x49, 0x49, 0x31},
    /** @brief T [84] */
    {0x01, 0x01, 0x7F, 0x01, 0x01},
    /** @brief U [85] */
    {0x3F, 0x40, 0x40, 0x40, 0x3F},
    /** @brief V [86] */
    {0x1F, 0x20, 0x40, 0x20, 0x1F},
    /** @brief W [87] */
    {0x3F, 0x40, 0x38, 0x40, 0x3F},
    /** @brief X [88] */
    {0x63, 0x14, 0x08, 0x14, 0x63},
    /** @brief Y [89] */
    {0x07, 0x08, 0x70, 0x08, 0x07},
    /** @brief Z [90] */
    {0x61, 0x51, 0x49, 0x45, 0x43},
    /** @brief [ [91] */
    {0x00, 0x7F, 0x41, 0x41, 0x00},
    /** @brief \ [92] */
    {0x02, 0x04, 0x08, 0x10, 0x20},
    /** @brief ] [93] */
    {0x00, 0x41, 0x41, 0x7F, 0x00},
    /** @brief ^ [94] */
    {0x04, 0x02, 0x01, 0x02, 0x04},
    /** @brief _ [95] */
    {0x40, 0x40, 0x40, 0x40, 0x40},
    /** @brief ` [96] */
    {0x00, 0x01, 0x02, 0x04, 0x00},
    /** @brief a [97] */
    {0x20, 0x54, 0x54, 0x54, 0x78},
    /** @brief b [98] */
    {0x7F, 0x48, 0x44, 0x44, 0x38},
    /** @brief c [99] */
    {0x38, 0x44, 0x44, 0x44, 0x20},
    /** @brief d [100] */
    {0x38, 0x44, 0x44, 0x48, 0x7F},
    /** @brief e [101] */
    {0x38, 0x54, 0x54, 0x54, 0x18},
    /** @brief f [102] */
    {0x08, 0x7E, 0x09, 0x01, 0x02},
    /** @brief g [103] */
    {0x0C, 0x52, 0x52, 0x52, 0x3E},
    /** @brief h [104] */
    {0x7F, 0x08, 0x04, 0x04, 0x78},
    /** @brief i [105] */
    {0x00, 0x44, 0x7D, 0x40, 0x00},
    /** @brief j [106] */
    {0x20, 0x40, 0x44, 0x3D, 0x00},
    /** @brief k [107] */
    {0x7F, 0x10, 0x28, 0x44, 0x00},
    /** @brief l [108] */
    {0x00, 0x41, 0x7F, 0x40, 0x00},
    /** @brief m [109] */
    {0x7C, 0x04, 0x18, 0x04, 0x78},
    /** @brief n [110] */
    {0x7C, 0x08, 0x04, 0x04, 0x78},
    /** @brief o [111] */
    {0x38, 0x44, 0x44, 0x44, 0x38},
    /** @brief p [112] */
    {0x7C, 0x14, 0x14, 0x14, 0x08},
    /** @brief q [113] */
    {0x08, 0x14, 0x14, 0x18, 0x7C},
    /** @brief r [114] */
    {0x7C, 0x08, 0x04, 0x04, 0x08},
    /** @brief s [115] */
    {0x48, 0x54, 0x54, 0x54, 0x20},
    /** @brief t [116] */
    {0x04, 0x3F, 0x44, 0x40, 0x20},
    /** @brief u [117] */
    {0x3C, 0x40, 0x40, 0x20, 0x7C},
    /** @brief v [118] */
    {0x1C, 0x20, 0x40, 0x20, 0x1C},
    /** @brief w [119] */
    {0x3C, 0x40, 0x30, 0x40, 0x3C},
    /** @brief x [120] */
    {0x44, 0x28, 0x10, 0x28, 0x44},
    /** @brief y [121] */
    {0x0C, 0x50, 0x50, 0x50, 0x3C},
    /** @brief z [122] */
    {0x44, 0x64, 0x54, 0x4C, 0x44},
    /** @brief { [123] */
    {0x00, 0x08, 0x36, 0x41, 0x00},
    /** @brief | [124] */
    {0x00, 0x00, 0x7F, 0x00, 0x00},
    /** @brief } [125] */
    {0x00, 0x41, 0x36, 0x08, 0x00},
    /** @brief стрелка вправо [126] */
    {0x08, 0x08, 0x2A, 0x1C, 0x08}};

#endif /* FONT5X7_H */
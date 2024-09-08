/* GStreamer
 *  Copyright (C) 2024 Intel Corporation
 *     Author: He Junyan <junyan.he@intel.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the0
 * Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include <gst/check/gstcheck.h>
#include <gst/codecparsers/gstvp9bitwriter.h>

/* *INDENT-OFF* */
static const guint8 vp9_frames[][1024] = {
  {
    0x84, 0x00, 0x40, 0x00, 0x00, 0x1f, 0xc0, 0x17, 0xd2, 0x03, 0x8e, 0x02, 0x02, 0x02, 0x02, 0x02,
    0x00, 0xb8, 0x00, 0x00, 0x60, 0x70, 0x00, 0x00, 0x15, 0x0f, 0x42, 0x89, 0x0d, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x06, 0x54, 0xdd, 0x00, 0xdf, 0x96, 0xe6, 0xe6, 0x3a, 0xe3, 0x19, 0xfd, 0x8f, 0xb2,
    0x4c, 0x5d, 0xc5, 0x7f, 0xff, 0xe8, 0xaf, 0x16, 0xda, 0xfb, 0xd4, 0x63, 0x20, 0x0d, 0xa3, 0x8e,
    0x5e, 0x20, 0xd3, 0x3c, 0x97, 0x19, 0x93, 0xea, 0x5e, 0x50, 0x36, 0x76, 0xea, 0xf4, 0x91, 0x68,
    0x33, 0xa1, 0x21, 0xd1, 0xca, 0x42, 0x84, 0x8c, 0x20, 0x34, 0xf8, 0xdb, 0x8f, 0x2d, 0x3c, 0xce,
    0x22, 0x3c, 0xd4, 0x6f, 0x19, 0x54, 0x0a, 0x07, 0x7d, 0x01, 0x89, 0xe6, 0xcb, 0xd5, 0xec, 0x2b,
    0x24, 0xb0, 0x83, 0x7f, 0xc9, 0xc5, 0xf1, 0xcc, 0xb7, 0xa4, 0x7d, 0x3e, 0x02, 0xf3, 0xb7, 0x6f,
    0xec, 0xf6, 0xe9, 0xf3, 0xaf, 0xb6, 0x3b, 0xca, 0xda, 0xc0, 0x2b, 0x46, 0xba, 0x41, 0x55, 0x74,
    0xf5, 0x7f, 0xfa, 0x91, 0x9e, 0xbc, 0x72, 0xfc, 0x12, 0x8f, 0x16, 0x8a, 0x4f, 0xa4, 0x19, 0xdc,
    0x7c, 0x22, 0x40, 0xff, 0xf3, 0x1e, 0x9f, 0xfe, 0x13, 0x9c, 0xe3, 0x66, 0x18, 0x53, 0x02, 0xa3,
    0xff, 0xff, 0x35, 0x0a, 0x6c, 0xbd, 0xb1, 0xde, 0xf5, 0x82, 0xa4, 0xb9, 0xa2, 0xf4, 0x18, 0x54,
    0x92, 0xe9, 0xf0, 0x86, 0x77, 0x87, 0xbf, 0x71, 0xfd, 0xbd, 0x52, 0xf4, 0xc5, 0x5e, 0x32, 0x67,
    0xb5, 0xb1, 0xcc, 0x3f, 0xd1, 0x2e, 0x89, 0x71, 0x01, 0x26, 0xde, 0xa8, 0x29, 0xff, 0xf1, 0xac,
    0x52, 0xbd, 0x58, 0xfc, 0x64, 0x0d, 0x87, 0x80, 0x13, 0x7b, 0x9f, 0xbf, 0x35, 0x78, 0x6f, 0xa2,
    0xc7, 0x84, 0x0f, 0xa8, 0xf0, 0x61, 0x6c, 0x07, 0x70, 0x21, 0xdf, 0xef, 0xf1, 0xc7, 0xdd, 0xb1,
    0x4c, 0x2f, 0x62, 0x70, 0x4a, 0x11, 0xe6, 0xeb, 0xc1, 0x70, 0xbb, 0x20, 0x9e, 0x4b, 0xa1, 0xc1,
    0x2e, 0x99, 0x3f, 0x23, 0x88, 0xff, 0xca, 0xfe, 0x1f, 0xde, 0x04, 0x75, 0x51, 0x06, 0x93, 0x0f,
    0x5c, 0xfc, 0xf7, 0x43, 0xff, 0xb7, 0x16, 0x5d, 0x9e, 0x73, 0x43, 0x86, 0xff, 0x94, 0xce, 0x89,
    0x97, 0xd8, 0xe4, 0x0e, 0xba, 0xe4, 0xca, 0xff, 0xf3, 0x38, 0x03, 0x46, 0x13, 0xf8, 0x61, 0xec,
    0xbb, 0x43, 0x18, 0x05, 0x14, 0x39, 0xdc, 0x7c, 0x85, 0x37, 0x70, 0x70, 0x4c, 0x5f, 0xff, 0xfd,
    0xf7, 0x08, 0xcc, 0x10, 0xf4, 0x05, 0xd6, 0x4b, 0xad, 0xad, 0x55, 0x47, 0xfc, 0x25, 0x3c, 0x9d,
    0xca, 0xfe, 0x7f, 0xff, 0xf9, 0x50, 0xa7, 0xfb, 0x40, 0x34, 0xf8, 0x8e, 0x2b, 0xb7, 0x82, 0x1f,
    0x71, 0xff, 0x6c, 0x77, 0xb5, 0x54, 0xa7, 0xf4, 0x10, 0x4d, 0xcd, 0xdd, 0x8e, 0x23, 0x90, 0x43,
    0x4e, 0xdf, 0x6b, 0xc8, 0xf6, 0x43, 0x5c, 0x5f, 0x46, 0x64, 0xc3, 0x81, 0xde, 0xe1, 0x3b, 0x83,
    0x56, 0x35, 0x6c, 0xa1, 0xe8, 0x88, 0x5b, 0x25, 0x58, 0x02, 0x59, 0xd8, 0x6d, 0x95, 0x47, 0x08,
    0xdd, 0xa5, 0xbe, 0x75, 0xcf, 0x3f, 0xfb, 0x0f, 0xfe, 0x5c, 0xfc, 0x2e, 0xa6, 0xff, 0xfc, 0x0b,
    0xd9, 0x62, 0xc3, 0xfa, 0x05, 0xf2, 0x9e, 0xf1, 0xbc, 0x32, 0x4c, 0x26, 0x2d, 0x1d, 0x15, 0x92,
    0xf5, 0xc7, 0xc2, 0x42, 0xe8, 0x83, 0x3d, 0xbb, 0x9e, 0xe4, 0x5b, 0xdc, 0x0f, 0xfc, 0x60, 0x4f,
    0xff, 0x7f, 0xff, 0xff, 0x49, 0x48, 0x89, 0x22, 0x8f, 0xad, 0xf1, 0x6f, 0xf4, 0x66, 0xfe, 0xd4,
    0x7f, 0xf3, 0xc8, 0xcc, 0x41, 0x1f, 0x9b, 0x23, 0x6e, 0x42, 0xc7, 0x19, 0x4e, 0x6f, 0xab, 0x06,
    0xa2, 0x16, 0x46, 0x05, 0xe3, 0x68, 0x0f, 0x07, 0x6d, 0x18, 0xb8, 0xf1, 0x6b, 0x08, 0xa0, 0x02,
    0x88, 0xc2, 0x0d, 0x43, 0x0a, 0x72, 0x42, 0x7c, 0xb8, 0x77, 0xea, 0x53, 0xbb, 0x17, 0x9d, 0x8e,
    0x7d, 0x61, 0xcf, 0x7e, 0xd9, 0x9c, 0xb2, 0x33, 0xbe, 0x04, 0xf6, 0xb7, 0x07, 0xff, 0x91, 0x20,
    0x71, 0xd7, 0x34, 0x41, 0x1e, 0xc0, 0xf8, 0x9c, 0xef, 0x5e, 0xff, 0x7a, 0x8f, 0x5b, 0x23, 0x94,
    0x0e, 0x9a, 0x70, 0x39, 0x20, 0x71, 0xde, 0xa7, 0xbd, 0xfb, 0xab, 0xac, 0xfe, 0xd1, 0x97, 0xff,
    0xec, 0x34, 0x6f, 0x06, 0xf5, 0x49, 0xbf, 0xff, 0xfc, 0x1b, 0x1f, 0x9e, 0x05, 0xa7, 0xe4, 0x0f,
    0x45, 0xdf, 0xe9, 0xc5, 0xc8, 0xc3, 0xfe, 0xc4, 0x08, 0x4f, 0x10, 0x3e, 0xcc, 0x62, 0x08, 0x02,
    0x67, 0x8f, 0xbe, 0x26, 0x3e, 0x11, 0x64, 0x86, 0x4f, 0xb4, 0xa3, 0xbf, 0xfb, 0x08, 0x87, 0x5d,
    0xd9, 0xbd, 0xf2, 0x05, 0xf6, 0x7b, 0xf8, 0xb9, 0x84, 0xd8, 0x5c, 0x34, 0xaf, 0xf5, 0xe3, 0xea,
    0x55, 0x95, 0x14, 0x0d, 0xfb, 0x65, 0xec, 0x06, 0x5f, 0x8b, 0xe5, 0xf1, 0x59, 0x8f, 0x07, 0x09,
    0x8b, 0xfe, 0x12, 0x18, 0xb4, 0xa0, 0x07, 0xe2, 0x4d, 0x21, 0x94, 0x28, 0x34, 0x37, 0xfc, 0x2a,
    0x8a, 0x87, 0xb2, 0x13, 0x67, 0x42, 0x6a, 0xb1, 0x07, 0xf7, 0x0c, 0xff, 0x16, 0x27, 0x1a, 0x83,
    0xf3, 0x90, 0x7a, 0xee, 0x2f, 0xfe, 0xd2, 0xa1, 0x76, 0x0c, 0xc9, 0x4f, 0x49, 0x27, 0xb4, 0xfa,
    0xf8, 0xd6, 0x46, 0xc0, 0xbb, 0xc1, 0x44, 0xbf, 0xe3, 0xa7, 0xf7, 0x76, 0xe0
  },
  { 
    0x84, 0x00, 0x80, 0x04, 0x00, 0x1f, 0xc0, 0x17, 0xd2, 0x04, 0x8e, 0x02, 0x02, 0x02, 0x02, 0x02,
    0x00, 0xe4, 0x00, 0x00, 0x60, 0x70, 0x00, 0x00, 0x59, 0x96, 0x81, 0xe3, 0xf0, 0x88, 0x27, 0x48,
    0xff, 0xfe, 0xf3, 0x22, 0xd1, 0x8d, 0xfb, 0xcc, 0xdf, 0xff, 0x9f, 0x63, 0xc7, 0xfd, 0x7b, 0xc6,
    0x98, 0xd0, 0xff, 0xf8, 0x90, 0xb7, 0xff, 0xee, 0x03, 0xd7, 0xf9, 0x3e, 0x0e, 0xdd, 0xac, 0x22,
    0x73, 0xf0, 0x07, 0xf6, 0x7f, 0x8b, 0x12, 0x9e, 0xd2, 0x8e, 0xc3, 0x9f, 0xad, 0xa1, 0x2f, 0xff,
    0xda, 0xb9, 0x8a, 0x8b, 0xfd, 0xbf, 0xd0, 0xb5, 0xa7, 0xfc, 0xac, 0x68, 0xa8, 0x84, 0xc1, 0xfc,
    0x44, 0x84, 0x46, 0x2b, 0x8e, 0x85, 0x02, 0x57, 0x8d, 0x56, 0x58, 0xca, 0x4e, 0x5c, 0x1d, 0xeb,
    0xd0, 0xd8, 0xc5, 0x8e, 0x7f, 0xff, 0x7e, 0x5f, 0x7c, 0x6f, 0x05, 0x93, 0xb2, 0x6e, 0xb8, 0xa8,
    0x6b, 0x47, 0x58, 0x57, 0xbf, 0xf7, 0xae, 0x73, 0xb1, 0x58, 0x4e, 0xe8, 0x42, 0xb6, 0xfc, 0x45,
    0x0c, 0x05, 0xc3, 0xff, 0xcb, 0x7c, 0xf0, 0x8a, 0xa0, 0x50, 0xf7, 0xd8, 0x4b, 0xb3, 0x4f, 0xae,
    0x01, 0x27, 0x0a, 0x8e, 0x74, 0x21, 0x6b, 0x90, 0x55, 0x90, 0xdd, 0x44, 0xd9, 0x77, 0x75, 0x83,
    0xcd, 0x69, 0x13, 0x45, 0xcb, 0x5f, 0x85, 0xdd, 0xbf, 0xff, 0xff, 0x26, 0x9b, 0xe7, 0x1f, 0x9c,
    0x72, 0x98, 0x5e, 0x15, 0xb1, 0xf3, 0x36, 0xde, 0xca, 0x89, 0xc7, 0x5f, 0x47, 0x4f, 0x5e, 0x4b,
    0x3b, 0xf9, 0xd0, 0x4a, 0x37, 0xbc, 0x46, 0xe6, 0xc9, 0x8c, 0x45, 0x66, 0x30, 0x2f, 0x5d, 0xc3,
    0xf9, 0x85, 0xaa, 0x84, 0x6f, 0x6a, 0xb4, 0x2b, 0xff, 0x5e, 0x83, 0x2b, 0x76, 0xd6, 0x13, 0xbe,
    0xc2, 0x62, 0x3a, 0xc6, 0x67, 0x6d, 0x0a, 0x14, 0xfc, 0xbf, 0x46, 0x24, 0x95, 0xf9, 0x38, 0x22,
    0x7f, 0xe0, 0x0e, 0x5f, 0xff, 0x1b, 0x92, 0x30, 0x12, 0x05, 0xd7, 0x64, 0x60, 0x39, 0xb7, 0x9c,
    0x4d, 0xb3, 0x55, 0x7d, 0x30, 0xaf, 0xd1, 0x44, 0x9c, 0x5d, 0xfc, 0x28, 0x89, 0x28, 0x6b, 0xbe,
    0xf5, 0x3e, 0xb0, 0x29, 0x40, 0xa6, 0x6f, 0x96, 0x4c, 0x5e, 0x23, 0xbd, 0xe3, 0xba, 0x9e, 0xca,
    0xaf, 0x49, 0x77, 0xfe, 0x7d, 0x19, 0xf6, 0x12, 0xec, 0xd2, 0x77, 0x6d, 0x43, 0x5e, 0xab, 0xdb,
    0x1f, 0xb9, 0x14, 0x74, 0x3d, 0x14, 0x00, 0x47, 0x64, 0x2f, 0x80, 0x31, 0xfd, 0x47, 0xf3, 0xec,
    0x53, 0x98, 0xcd, 0x38, 0x45, 0xfd, 0xa7, 0x02, 0x45, 0xfe, 0x74, 0xe1, 0x41, 0xf3, 0x9a, 0x72,
    0x90, 0x16, 0x7b, 0xff, 0xd4, 0x24, 0x50, 0x9f, 0xce, 0x98, 0x7f, 0xff, 0x80, 0x70, 0xad, 0xd9,
    0x5c, 0x65, 0xa5, 0x6f, 0x2d, 0xd9, 0xdd, 0x48, 0x32, 0x75, 0x9b, 0x4f, 0x66, 0xa3, 0xff, 0xfa,
    0x0e, 0xfe, 0xdc, 0xe5, 0xab, 0x0b, 0xa7, 0x8e, 0x15, 0x08, 0x5a, 0x14, 0x4c, 0xef, 0x2f, 0x77,
    0x8e, 0xf6, 0x45, 0x7c, 0x23, 0xff, 0xce, 0x11, 0x5f, 0x8d, 0x25, 0xaa, 0x7a, 0x1c, 0x4f, 0x88,
    0xba, 0xc2, 0xd5, 0x6c, 0xe9, 0x9e, 0xd8, 0x6e, 0x31, 0x95, 0x4f, 0x9f, 0xe5, 0x1a, 0xa1, 0xae,
    0x50, 0x13, 0x3f, 0x2a, 0x7d, 0x10, 0xf7, 0x7b, 0xc0, 0x32, 0xbe, 0x11, 0x4d, 0x44, 0xca, 0x78,
    0x95, 0xae, 0x90, 0xb0, 0xf9, 0xcd, 0x5f, 0xff, 0x8c, 0xf0, 0xcf, 0xd3, 0x57, 0x7c, 0x43, 0x1e,
    0xb0, 0xe5, 0x27, 0x54, 0x37, 0x9e, 0x76, 0x87, 0x4a, 0x94, 0x59, 0x6e, 0xe0, 0x4f, 0x4b, 0x0d,
    0xdc, 0x4e, 0xc6, 0x9d, 0x2b, 0xe9, 0x74, 0x5e, 0xce, 0xdb, 0x66, 0xd2, 0x3f, 0xc0, 0x7d, 0xba,
    0x0d, 0x26, 0x83, 0xf9, 0x2a, 0x29, 0x4d, 0x38, 0xfc, 0x4d, 0xf9, 0xb9, 0x30, 0x09, 0x84, 0x8f,
    0x19, 0x7f, 0x1b, 0xe7, 0xaf, 0xf0, 0x45, 0x30, 0x41, 0xdf, 0x13, 0x54, 0x48, 0xf1, 0xfe, 0x17,
    0xef, 0x75, 0xea, 0xe2, 0x44, 0x4a, 0x7f, 0x0c, 0x09, 0x9f, 0xdf, 0x90, 0x9e, 0xef, 0x84, 0x04,
    0xb8, 0x48, 0x0d, 0x45, 0x30, 0x79, 0x33, 0x85, 0x39, 0xe3, 0xee, 0xc8, 0xbd, 0xfe, 0xc5, 0x7e,
    0xb1, 0x96, 0xb2, 0x40, 0xe6, 0x55, 0x1b, 0xbf, 0x76, 0xa2, 0xf1, 0x97, 0xff, 0xa4, 0xbf, 0xb9,
    0xd0, 0x70, 0x01, 0xc9, 0xac, 0x84, 0xfb, 0x52, 0xe9, 0xf0, 0x74, 0x2b, 0x04, 0xb4, 0xe6, 0xa4,
    0xec, 0x38, 0x99, 0xb9, 0x6d, 0xa5, 0x02, 0xc5, 0x5e, 0x94, 0xd2, 0x95, 0x5f, 0xeb, 0x61, 0x37,
    0x0f, 0xf8, 0xe3, 0x1a, 0xff, 0x9f, 0x65, 0x0a, 0x3d, 0x5a, 0x90, 0x6b, 0x8f, 0x45, 0x30, 0xd1,
    0xd4, 0x16, 0x94, 0x4c, 0x01, 0x6a, 0x3f, 0xdb, 0x62, 0xf1, 0x60, 0x50, 0x52, 0x3e, 0x6e, 0x17,
    0xca, 0xa0, 0xf7, 0xfd, 0xac, 0x6e, 0x3b, 0x2a, 0xff, 0x19, 0x2b, 0x31, 0x15, 0x0f, 0x47, 0x1e,
    0x0c, 0x7f, 0x8c, 0xc0, 0xff, 0xcd, 0x8d, 0xb4, 0xd6, 0xf8, 0x4d, 0xe6, 0x19, 0x9f, 0x7e, 0xdd,
    0x80
  },
  { 
    0x84, 0x01, 0x00, 0x08, 0x00, 0x1f, 0xc0, 0x17, 0xd2, 0x04, 0x8e, 0x02, 0x02, 0x02, 0x02, 0x02,
    0x00, 0xdc, 0x00, 0x00, 0x60, 0x70, 0x00, 0x00, 0x59, 0x96, 0x81, 0xe3, 0xf0, 0x4a, 0xb6, 0x22,
    0xff, 0xff, 0xdf, 0xef, 0xd8, 0x06, 0xe9, 0xe7, 0x2b, 0x02, 0x9e, 0xc3, 0xfd, 0xef, 0x85, 0x28,
    0x29, 0xc0, 0x5a, 0x82, 0x2d, 0x5f, 0x37, 0xa9, 0x8a, 0x98, 0x3e, 0xb9, 0xd2, 0x74, 0x65, 0x2e,
    0xdd, 0x57, 0xfc, 0x47, 0xff, 0xd6, 0x3f, 0xf3, 0x88, 0xdf, 0x1c, 0xb6, 0xb8, 0x39, 0xb8, 0xd8,
    0x04, 0x06, 0x30, 0xe8, 0xe9, 0x60, 0xff, 0x99, 0xd4, 0x8d, 0x73, 0xff, 0xf3, 0x82, 0xf9, 0x5f,
    0xd4, 0xcf, 0xf1, 0x35, 0x49, 0x21, 0x66, 0x85, 0xcd, 0xa7, 0xff, 0x8b, 0xfe, 0xb1, 0xf6, 0x5e,
    0x12, 0x73, 0xf0, 0xe6, 0xe3, 0xf9, 0xb7, 0x3f, 0x5e, 0xbd, 0x16, 0x19, 0xcc, 0x17, 0xe3, 0xe3,
    0x2e, 0x26, 0x38, 0x54, 0xc5, 0x8f, 0x5a, 0x1a, 0xfc, 0x50, 0x1a, 0xea, 0x7c, 0x63, 0x14, 0x38,
    0x3b, 0x06, 0x56, 0x9f, 0xf1, 0x34, 0x2d, 0x8e, 0xdf, 0x6d, 0xc9, 0x42, 0xbc, 0xfa, 0x81, 0xda,
    0xa3, 0x12, 0x19, 0x33, 0xf0, 0x86, 0x42, 0x56, 0x8c, 0x2c, 0x79, 0xa8, 0xf3, 0xe6, 0xd7, 0xf6,
    0x0f, 0xd5, 0xc6, 0xf2, 0x7c, 0x75, 0x40, 0x07, 0x90, 0xa1, 0x5f, 0xff, 0xe0, 0x76, 0xe9, 0xe9,
    0x60, 0x24, 0x48, 0xe7, 0x68, 0x42, 0x6c, 0x4d, 0xe8, 0x5f, 0xfe, 0x57, 0x2c, 0x63, 0x5c, 0xe6,
    0x37, 0xff, 0x09, 0x91, 0x06, 0x93, 0x22, 0x62, 0xe7, 0xf8, 0x86, 0xb3, 0xcc, 0xac, 0x42, 0xef,
    0x86, 0x4c, 0xff, 0x59, 0xfe, 0x60, 0xc0, 0x9f, 0x87, 0x07, 0xf6, 0x01, 0xba, 0xb3, 0xc8, 0x4f,
    0x48, 0xd5, 0x6d, 0xf6, 0x1e, 0x76, 0x15, 0xa3, 0x5b, 0xe6, 0x28, 0xd8, 0xd3, 0x6c, 0xc4, 0x90,
    0xb2, 0xec, 0x3f, 0x42, 0xf1, 0xbc, 0x11, 0x58, 0xa1, 0x61, 0xcf, 0xbd, 0xe1, 0xad, 0xe2, 0x70,
    0x8b, 0xdd, 0xb1, 0x02, 0x37, 0x85, 0xf2, 0xcd, 0xb8, 0x35, 0x8b, 0x5a, 0x75, 0x96, 0x39, 0x7f,
    0xdc, 0xf9, 0x9e, 0x86, 0x7b, 0xcd, 0xd0, 0x1b, 0xc7, 0xfc, 0x8b, 0x9f, 0xb9, 0xd5, 0xed, 0xbc,
    0xf4, 0xcb, 0x74, 0x36, 0xe8, 0x7c, 0xa9, 0xe1, 0x85, 0x4d, 0x14, 0x21, 0x39, 0xfd, 0x36, 0x59,
    0x8e, 0x65, 0xb5, 0xc9, 0x65, 0x27, 0x02, 0xf6, 0x92, 0x54, 0xbf, 0xc3, 0xf7, 0xa3, 0xc4, 0xfc,
    0x6c, 0xb0, 0x99, 0x68, 0x27, 0x6e, 0x29, 0x1f, 0xe6, 0x51, 0xff, 0xd7, 0xfe, 0xad, 0xf4, 0xe0,
    0xca, 0xdf, 0xf6, 0xe4, 0x5f, 0x8b, 0x33, 0xb5, 0xcc, 0x9e, 0xa7, 0xd8, 0x0f, 0xce, 0x90, 0x9d,
    0x31, 0xaf, 0x17, 0xf7, 0xfb, 0x99, 0xda, 0xd1, 0x90, 0xdc, 0x07, 0x29, 0xea, 0xb6, 0x43, 0xf4,
    0xd3, 0xae, 0x42, 0x51, 0x83, 0xea, 0xd8, 0xf6, 0x65, 0xb4, 0xf0, 0x99, 0x1e, 0x39, 0x6f, 0xa9,
    0xee, 0x07, 0xfd, 0xfb, 0xff, 0x0f, 0xfc, 0xa3, 0xfc, 0x40, 0xeb, 0x65, 0xb7, 0x29, 0xa1, 0xff,
    0xdc, 0x44, 0x41, 0xe0, 0x5f, 0xb9, 0x6b, 0xc6, 0x6d, 0xac, 0xfe, 0x7e, 0x77, 0x4d, 0xff, 0x84,
    0xe3, 0xf3, 0xdf, 0x15, 0x72, 0xd7, 0x99, 0x51, 0xe4, 0x4c, 0xb8, 0x03, 0x94, 0x8c, 0x1c, 0xc8,
    0x94, 0x18, 0x58, 0x4d, 0x80, 0x0e, 0xa1, 0x9c, 0xdd, 0x55, 0x5f, 0xfd, 0xb5, 0xcb, 0xde, 0x26,
    0x91, 0xbe, 0x70, 0x5b, 0xeb, 0xde, 0x90, 0x31, 0x7e, 0x84, 0x0b, 0x2f, 0xbf, 0x4a, 0xcd, 0x92,
    0x7c, 0xbb, 0x85, 0xbd, 0xd5, 0x82, 0xe8, 0xba, 0xe9, 0xe3, 0xf7, 0x84, 0xdd, 0x2c, 0x13, 0xe6,
    0x0d, 0x11, 0x03, 0xc5, 0x69, 0x55, 0x71, 0xb4, 0x4d, 0xbb, 0x65, 0x0a, 0x41, 0xcb, 0xcc, 0x24,
    0xff, 0xdb, 0xad, 0xf1, 0x83, 0x0b, 0x17, 0x84, 0x43, 0x29, 0x4e, 0x90, 0xe1, 0x39, 0x30, 0x30,
    0x4e, 0x99, 0x82, 0xbf, 0xfe, 0x0b, 0xc3, 0x12, 0xc4, 0x48, 0x14, 0x5f, 0x6b, 0x95, 0xe6, 0x4d,
    0xb8, 0x5e, 0x26, 0x69, 0x35, 0x67, 0x1c, 0x0f, 0x32, 0x6c, 0x41, 0x77, 0xcd, 0x62, 0xf4, 0x04,
    0xeb, 0x7a, 0xaa, 0xee, 0xc9, 0xd1, 0x19, 0xf4, 0x81, 0x9e, 0x04, 0xb6, 0x1c, 0x66, 0x47, 0xaf,
    0x2b, 0x62, 0xf8, 0x04, 0x4f, 0x1c, 0xaa, 0x49, 0x69, 0x19, 0x01, 0x8b, 0x96, 0x2a, 0x7d, 0x9f,
    0x47, 0x16, 0x0b, 0xd9, 0x35, 0xbf, 0xe3, 0xd3, 0xfe, 0xdc, 0xbb, 0x97, 0x64, 0x68, 0xfc, 0xb0,
    0xa1, 0xa8, 0xf4, 0x7f, 0x70, 0x3e, 0x3b, 0xc5, 0xd5, 0x80, 0x59, 0xf0, 0x7a, 0xb3, 0x68, 0x56,
    0x57, 0x6b, 0x2e, 0xb5, 0x34, 0xb8, 0x7b, 0x65, 0xfe, 0x40, 0x91, 0x5f, 0x43, 0x7f, 0xfd, 0xba,
    0xc1, 0xfe, 0xfd, 0x44, 0x95, 0x97, 0xb5, 0xdf, 0x73, 0x9f, 0xc9, 0x80, 0xe6, 0xbf, 0xfc, 0x77,
    0xac, 0x02, 0x7a, 0xf2, 0xb6, 0xc7, 0xa3, 0x4a, 0x8e, 0x9e, 0xf8, 0x54, 0x00
  },
  {
    0x86, 0x04, 0x00, 0x18, 0x00, 0x3f, 0x80, 0x2f, 0xa4, 0x08, 0x1c, 0x04, 0x04, 0x04, 0x04, 0x04,
    0x01, 0xa8, 0x00, 0x00, 0xc0, 0x70, 0x00, 0x00, 0x15, 0x0e, 0x2b, 0x60, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x0f, 0xb2, 0xdd, 0xd3, 0x68, 0xa2, 0x00, 0xfe, 0xc5, 0xbf, 0xfc, 0x4a, 0xe4, 0x48, 0x96,
    0xc2, 0x04, 0x79, 0x8b, 0xa0, 0x8f, 0x01, 0x1a, 0xdf, 0xc2, 0x81, 0xcb, 0x23, 0x74, 0x49, 0x4e,
    0x9d, 0xbf, 0x69, 0xfe, 0x89, 0xdf, 0xff, 0xf8, 0x69, 0x4f, 0xf2, 0x7f, 0x98, 0xa6, 0x01, 0x97,
    0xfa, 0xcf, 0xcc, 0xaf, 0xa5, 0x56, 0xea, 0x7f, 0xbf, 0x09, 0x1b, 0xdd, 0x2a, 0xf2, 0xba, 0x30,
    0x4b, 0xd1, 0xd0, 0xf6, 0xb4, 0xe9, 0xe4, 0x09, 0xe2, 0xfe, 0x72, 0x2e, 0xd0, 0xe5, 0x9e, 0xdf,
    0xdc, 0x1f, 0x05, 0x9a, 0x2f, 0xf7, 0xdb, 0xff, 0xea, 0xf4, 0xe2, 0xef, 0x3c, 0x0c, 0x38, 0x7e,
    0x0a, 0xb9, 0xa7, 0xe7, 0x3b, 0xa6, 0x71, 0x7f, 0x7f, 0xb4, 0xe7, 0xfe, 0x31, 0x7a, 0x56, 0xb6,
    0x36, 0x1e, 0x8c, 0xa9, 0xec, 0xcf, 0x71, 0x43, 0x40, 0x80, 0x4c, 0x5b, 0x20, 0xc1, 0xfe, 0xce,
    0x5f, 0xf4, 0xd8, 0x0b, 0x3f, 0xff, 0x9b, 0x7a, 0xb8, 0x6a, 0x2f, 0x5b, 0x75, 0xbf, 0xfa, 0xf1,
    0xf2, 0xe0, 0x33, 0x6b, 0x1f, 0xff, 0x9f, 0x1e, 0x41, 0x86, 0xa9, 0x27, 0x01, 0x51, 0x79, 0x0d,
    0xe5, 0x1d, 0xcf, 0x57, 0x54, 0x90, 0x79, 0x84, 0x08, 0xc9, 0xb7, 0xc6, 0x97, 0x1c, 0x77, 0x9f,
    0x79, 0x8b, 0xdc, 0x72, 0xaf, 0x48, 0xe8, 0x43, 0x52, 0xf9, 0x7c, 0x90, 0x9b, 0xb7, 0x0a, 0x51,
    0x1f, 0xdb, 0x04, 0x52, 0x23, 0xff, 0x99, 0xbd, 0x79, 0x60, 0x26, 0xfe, 0x51, 0xf7, 0xe7, 0x6c,
    0x1d, 0x14, 0xb7, 0xfe, 0x23, 0x09, 0xad, 0x7f, 0xd0, 0x9c, 0x3f, 0x6d, 0x41, 0xc1, 0xef, 0x9e,
    0x8c, 0x07, 0xa3, 0x15, 0x76, 0x6a, 0x94, 0xe4, 0xba, 0xe6, 0xc6, 0x3f, 0x87, 0x99, 0x50, 0xcf,
    0x25, 0x99, 0xb2, 0x5f, 0x2f, 0xe3, 0x1a, 0x96, 0x35, 0x64, 0xbe, 0xcc, 0xdc, 0x72, 0xed, 0xc6,
    0x11, 0x99, 0xfe, 0x62, 0x7f, 0xd9, 0x1f, 0xf5, 0xe7, 0x6b, 0xc6, 0xf6, 0xe8, 0x97, 0x69, 0xc2,
    0x61, 0xfc, 0x59, 0x36, 0x9a, 0xdd, 0x2a, 0x27, 0x9d, 0xa3, 0x28, 0x5e, 0xfe, 0xf7, 0xba, 0x1b,
    0x42, 0x10, 0xdc, 0x6b, 0xbc, 0xbf, 0x37, 0x98, 0xfe, 0x7f, 0xf0, 0x92, 0xfe, 0xea, 0x86, 0xff,
    0xb9, 0x7f, 0x96, 0x7f, 0x3b, 0x91, 0xd3, 0x34, 0x09, 0x3a, 0x28, 0xc3, 0x6f, 0xfd, 0xe6, 0xca,
    0xe8, 0xcd, 0x9d, 0x3b, 0x20, 0x4f, 0xff, 0x8a, 0x66, 0x87, 0xfe, 0x23, 0x27, 0x6c, 0x34, 0x3d,
    0x12, 0x4a, 0x48, 0x3e, 0x92, 0xa3, 0x98, 0x30, 0xa6, 0xad, 0x3a, 0x78, 0x40, 0x5b, 0xcb, 0xae,
    0x2d, 0xfd, 0x68, 0x2c, 0x7d, 0x3b, 0xeb, 0x92, 0x93, 0xff, 0xac, 0xd4, 0xc6, 0x05, 0xf2, 0x00,
    0x62, 0x67, 0x00, 0x73, 0xbb, 0x7d, 0x7c, 0x37, 0xdc, 0x5c, 0xff, 0xfc, 0xc8, 0xcb, 0x77, 0x1f,
    0xff, 0x86, 0xca, 0xd2, 0x1b, 0xb7, 0x4c, 0x36, 0x87, 0xd1, 0xb8, 0xe4, 0x37, 0x21, 0x7c, 0x08,
    0xe2, 0x98, 0xec, 0xcc, 0xaa, 0xbe, 0xbb, 0x5b, 0xa8, 0xa7, 0x1f, 0x48, 0x8f, 0xa9, 0x3e, 0x43,
    0x30, 0x39, 0x7b, 0x75, 0x0f, 0x58, 0xfe, 0xfc, 0x2e, 0x5f, 0xa8, 0x42, 0x57, 0x67, 0x06, 0x6f,
    0xd3, 0xe3, 0x2f, 0x8b, 0x53, 0xef, 0x2c, 0xae, 0x2d, 0x73, 0x1b, 0x77, 0xd1, 0x71, 0x4d, 0xcb,
    0xba, 0xfd, 0x6f, 0xc0, 0x59, 0xf1, 0xa4, 0x6a, 0x55, 0xdc, 0x67, 0xdc, 0xff, 0xf2, 0xa2, 0x97,
    0xa3, 0x26, 0xc6, 0x7e, 0x4e, 0x51, 0xe0, 0x7a, 0x47, 0x57, 0xc4, 0xbb, 0x69, 0x5d, 0x4f, 0x8b,
    0xf5, 0x74, 0xd1, 0xb9, 0x94, 0xab, 0x1b, 0x7c, 0xbd, 0xc8, 0x64, 0x5f, 0xa5, 0xa0, 0x82, 0x5f,
    0x45, 0xef, 0xce, 0x24, 0xdc, 0x4b, 0x31, 0x0e, 0xb0, 0x9b, 0xdf, 0xa6, 0x90, 0xcf, 0xd6, 0x6f,
    0xff, 0xfb, 0x95, 0x7f, 0xa3, 0x9b, 0x5f, 0xfb, 0xe6, 0x02, 0x3d, 0xb0, 0x37, 0x76, 0x5b, 0xf6,
    0x28, 0x33, 0xbf, 0x8f, 0xaa, 0xc8, 0x95, 0x14, 0x27, 0x32, 0xc7, 0xef, 0xa0, 0xcb, 0x44, 0xf0,
    0x9d, 0x3f, 0x48, 0x11, 0x37, 0x88, 0x2f, 0x2d, 0x4f, 0x06, 0x13, 0xe8, 0xac, 0xea, 0xa1, 0x98,
    0xff, 0xff, 0xf5, 0xf3, 0x4e, 0x96, 0xff, 0xff, 0xc3, 0x6d, 0x32, 0xf2, 0x32, 0xe6, 0x26, 0xe0,
    0xa7, 0x03, 0xcd, 0x20, 0xb2, 0xd5, 0xdd, 0x09, 0x06, 0x6f, 0xf9, 0x30, 0x44, 0x76, 0x6d, 0x86,
    0x7f, 0xec, 0x2f, 0xb4, 0x3d, 0xe9, 0x40, 0xc8, 0x44, 0x2d, 0xf5, 0xf7, 0x09, 0x8d, 0xbb, 0x64,
    0x9b, 0xb2, 0x70, 0x8c, 0xe8, 0x3a, 0x4f, 0xeb, 0xc6, 0x99, 0x5d, 0x9d, 0xcd, 0x94, 0x1d, 0x2d,
    0x23, 0x32, 0x0f, 0x82, 0x19, 0xf7, 0x76, 0x01, 0x81, 0x48, 0x59, 0x77, 0x1c, 0xe4, 0xc0, 0x92,
    0xe2, 0xc2, 0x10, 0x82, 0x34, 0xc1, 0x39, 0xf1, 0x23, 0xec, 0x6b, 0x7c, 0x9c, 0xbd, 0x21, 0xa9,
    0x22, 0x83, 0xde, 0x6f, 0xf8, 0x8b, 0xef, 0xcf, 0x00, 0x00
  },
};

static const gint vp9_frames_size[] = {
  717, 673, 669, 698
};
/* *INDENT-ON* */

GST_START_TEST (test_vp9_bitwriter_superframe)
{
  GstVp9BitWriterResult ret;
  GstVp9ParserResult parser_ret;
  GstVp9Parser *const parser = gst_vp9_parser_new ();
  GstVp9SuperframeInfo superframe_info;
  guint size;
  guint8 data[4096];
  guint offset;
  gint i;

  offset = 0;
  for (i = 0; i < 4; i++) {
    memcpy (data + offset, vp9_frames[i], vp9_frames_size[i]);
    offset += vp9_frames_size[i];
  }

  size = sizeof (data);
  ret = gst_vp9_bit_writer_superframe_info (4, vp9_frames_size, data, &size);
  fail_if (ret != GST_VP9_BIT_WRITER_OK);

  parser_ret = gst_vp9_parser_parse_superframe_info (parser,
      &superframe_info, data, size);
  fail_if (parser_ret != GST_VP9_PARSER_OK);

  assert_equals_int (superframe_info.bytes_per_framesize, 4);
  assert_equals_int (superframe_info.frames_in_superframe, 4);
  assert_equals_int (superframe_info.superframe_index_size, 18);

  for (i = 0; i < 4; i++)
    assert_equals_int (superframe_info.frame_sizes[i], vp9_frames_size[i]);

  offset = 0;
  for (i = 0; i < superframe_info.frames_in_superframe; i++) {
    guint32 frame_size;
    GstVp9FrameHdr frame_hdr = { 0, };

    frame_size = superframe_info.frame_sizes[i];
    parser_ret = gst_vp9_parser_parse_frame_header (parser, &frame_hdr,
        data + offset, frame_size);
    fail_if (parser_ret != GST_VP9_PARSER_OK);

    offset += frame_size;
  }

  gst_vp9_parser_free (parser);
}

GST_END_TEST;

static Suite *
vp9bitwriter_suite (void)
{
  Suite *s = suite_create ("vp9 bitwriter library");

  TCase *tc_chain = tcase_create ("general");

  suite_add_tcase (s, tc_chain);

  tcase_add_test (tc_chain, test_vp9_bitwriter_superframe);

  return s;
}

GST_CHECK_MAIN (vp9bitwriter);

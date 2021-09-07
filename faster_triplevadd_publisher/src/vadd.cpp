/*
      ____  ____
     /   /\/   /
    /___/  \  /   Copyright (c) 2021, Xilinx®.
    \   \   \/    Author: Víctor Mayoral Vilches <victorma@xilinx.com>
     \   \
     /   /
    /___/   /\
    \   \  /  \
     \___\/\___\

Inspired by the Vector-Add example.
See https://github.com/Xilinx/Vitis-Tutorials/blob/master/Getting_Started/Vitis

*/

#define DATA_SIZE 4096
// TRIPCOUNT identifier
const int c_size = DATA_SIZE;

// triplevadd kernel
extern "C" {
    void vadd(
            const unsigned int *in1,  // Read-Only Vector 1
            const unsigned int *in2,  // Read-Only Vector 2
            unsigned int *out,        // Output Result
            int size                  // Size in integer
            )
    {
#pragma HLS INTERFACE m_axi port=in1 bundle=aximm1
#pragma HLS INTERFACE m_axi port=in2 bundle=aximm2
#pragma HLS INTERFACE m_axi port=out bundle=aximm1

        for (int z = 0; z < size; ++z) { // stupidly iterate over
                                         // it to generate load
        #pragma HLS loop_tripcount min = c_size max = c_size
            // for (int j = 0; j < size; ++j) {
            for (int j = 0; j < (size/16)*16; ++j) {
            #pragma HLS UNROLL factor = 16
            #pragma HLS loop_tripcount min = c_size max = c_size
                for (int i = 0; i < (size/16)*16; ++i) {
                #pragma HLS UNROLL factor = 16
                #pragma HLS loop_tripcount min = c_size max = c_size
                    out[i] = in1[i] + in2[i];
                }
            }
        }
    }
}

//  // doublevadd kernel
// extern "C" {
//     void vadd(
//             const unsigned int *in1,  // Read-Only Vector 1
//             const unsigned int *in2,  // Read-Only Vector 2
//             unsigned int *out,        // Output Result
//             int size                  // Size in integer
//             )
//     {
// #pragma HLS INTERFACE m_axi port=in1 bundle=aximm1
// #pragma HLS INTERFACE m_axi port=in2 bundle=aximm2
// #pragma HLS INTERFACE m_axi port=out bundle=aximm1

//         for (int j = 0; j <size; ++j) {  // stupidly iterate over
//                                           // it to generate load
//         #pragma HLS loop_tripcount min = c_size max = c_size
//             for (int i = 0; i<(size/16)*16; ++i) {
//             #pragma HLS UNROLL factor=16
//             #pragma HLS loop_tripcount min = c_size max = c_size
//               out[i] = in1[i] + in2[i];
//             }
//         }
//     }
// }
